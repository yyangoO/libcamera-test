/**
 * @file                    main.cpp
 * @author                  yyang yyangoO@outlook.com & sjtu_yangyang@sjtu.edu.cn
 * @version                 1.0.0
 * @date                    5-APR-2022
 * @section                 description
 *                          main function
 * @section                 logs
 * <table>
 * <tr><th>date             <th>version     <th>author      <th>description     </tr>
 * <tr><td>2022.04.5        <td>1.0.0       <td>yyang       <td>initial version </tr>
 * </tr>
 */


#include <iomanip>
#include <memory>

#include "libcamera/libcamera.h"

#include "utils.h"
#include "eventloop.h"


#define TIMEOUT_SEC     (5)


using namespace std;
using namespace libcamera;


// the camera device
static shared_ptr<Camera> camera;
static EventLoop event_loop;


/**
 * @brief process the request for stream
 * This function process the request for stream.
 * @param request       the request of stream
 */
 static void process_request(Request *request);

/**
 * @brief handle request complate
 * This function handle request complate signal emmitted from camera. 
 * @param request       the request of stream
 */
static void request_complete(Request *request)
{
    // if we cancle the request, just return
	if (request->status() == Request::RequestCancelled)
    {
        cout << colored_str("[request cancelled]--> return. ", "red") << endl;
        return;
    }
    // push the request to the loop
	event_loop.call_later(bind(&process_request, request));
}

static void process_request(Request *request)
{
    cout << colored_str("[processing request]--> ", "green") 
         << request->toString() << endl;

    // get the request's metadata
    const ControlList &request_metadata = request->metadata();
    for (const auto &ctrl : request_metadata)
    {
        const ControlId *id = controls::controls.at(ctrl.first);
        const ControlValue &value = ctrl.second;

        cout << colored_str("    > [request]--> ", "cyan");
        cout << colored_str(id->name(), "white", false, true);
        cout << " " << value.toString() << endl;
    }

    // get the buffers' metadata
    const Request::BufferMap &buffers = request->buffers();
    for (auto buffer_pair : buffers)
    {
        FrameBuffer *buffer = buffer_pair.second;
        const FrameMetadata &frame_metadata = buffer->metadata();
        cout << colored_str("    > [buffer]--> ", "cyan");
        cout << colored_str("Sequence", "white", false, true);
        cout << " " << frame_metadata.sequence << endl;

        cout << colored_str("    > [buffer]--> ", "cyan");
        cout << colored_str("Timestamp", "white", false, true);
        cout << " " << frame_metadata.timestamp << endl;

        unsigned int n_plane = 0;
        cout << colored_str("    > [buffer]--> ", "cyan");
        cout << colored_str("BytesUsed", "white", false, true);
		for (const FrameMetadata::Plane &plane : frame_metadata.planes())
		{
            cout << " " << plane.bytesused;
            if (++n_plane < frame_metadata.planes().size())
            {
                cout << " /";
            }
		}
        cout << endl;
    }

    request->reuse(Request::ReuseBuffers);
	camera->queueRequest(request);
}


int main(void)
{
    string cam_id = "";
    unique_ptr<CameraManager> cam_mgr = make_unique<CameraManager>();

    // start camera manager
    cam_mgr->start();

    // check do we have camera device or not
    if (cam_mgr->cameras().empty()) 
    {
        cout << colored_str("[error]--> no cameras device. ", "red", true) << endl;
        cam_mgr->stop();
        return EXIT_FAILURE;
    }
    // list all camera device ID
    for (auto const &camera : cam_mgr->cameras())
    {
        cout << colored_str("[camera device id]--> ", "yellow") << camera->id() << endl;
    }

    // acquire a camera
    cam_id = cam_mgr->cameras()[0]->id();
    camera = cam_mgr->get(cam_id);
    camera->acquire();

    // get the default configuration & validate it & set to camera
    unique_ptr<CameraConfiguration> cam_cfg = camera->generateConfiguration({StreamRole::Viewfinder});
    StreamConfiguration &strm_cfg = cam_cfg->at(0);
    cout << colored_str("[defalut viewfinder configuration]--> ", "blue") << strm_cfg.toString() << endl;
    strm_cfg.size.width = 640;
    strm_cfg.size.height = 480;
    CameraConfiguration::Status viewfinder_cfg_ret = cam_cfg->validate();
    if (CameraConfiguration::Status::Invalid == viewfinder_cfg_ret)
    {
        cout << colored_str("[error]--> stream configuration invalid. ", "red", true) << endl;
    }
    else if (CameraConfiguration::Status::Adjusted == viewfinder_cfg_ret)
    {
        cout << colored_str("[adjust viewfinder configuration]--> ", "blue") << strm_cfg.toString() << endl;
    }
    else
    {
        cout << colored_str("[validate viewfinder configuration]--> ", "blue") << strm_cfg.toString() << endl;
    }
    camera->configure(cam_cfg.get());

    // get the framebuffer's allocator
    FrameBufferAllocator *allocator = new FrameBufferAllocator(camera);
    for (StreamConfiguration &cfg : *cam_cfg)
    {
        int ret = allocator->allocate(cfg.stream());
        if (ret < 0)
        {
            cout << colored_str("[error]--> can't allocator buffer. ", "red", true) << endl;
            return -ENOMEM;
        }
        size_t allocated = allocator->buffers(cfg.stream()).size();
        cout << colored_str("[allocated buffer size for stream]--> ", "blue") << allocated << endl;
    }

    // frame requists & frame capture
    Stream *stream = strm_cfg.stream();
    const std::vector<std::unique_ptr<FrameBuffer>> &buffers = allocator->buffers(stream);
    std::vector<std::unique_ptr<Request>> requests;
    for (long unsigned int i = 0; i < buffers.size(); ++i)
    {
        unique_ptr<Request> request = camera->createRequest();
        if (!request)
        {
            cout << colored_str("[error]--> can't create request for camera. ", "red", true) << endl;
            return -ENOMEM;
        }
        const std::unique_ptr<FrameBuffer> &buffer = buffers[i];
        int ret = request->addBuffer(stream, buffer.get());
        if (ret < 0)
        {
            cout << colored_str("[error]--> can't add buffer to request. ", "red", true) << endl;
            return -ENOMEM;
        }
        requests.push_back(move(request));
    }

    // set signal & slots
    camera->requestCompleted.connect(request_complete);
    
    // start capture
    camera->start();
    for (unique_ptr<Request> & request : requests)
    {
        camera->queueRequest(request.get());
    }

    // runu event loop
    int ret = -1;
    event_loop.timeout(TIMEOUT_SEC);
    ret = event_loop.exec();
    if (ret < 0)
    {
        cout << colored_str("[finished]--> capture ran for " + to_string(TIMEOUT_SEC) + \
                " seconds and stopped with exit status: " + to_string(ret), "yellow") << endl;
    }

    // release the camera and camera manager resources
    camera->stop();
    allocator->free(stream);
    delete allocator;
	camera->release();
	camera.reset();
	cam_mgr->stop();

    return 0;
}