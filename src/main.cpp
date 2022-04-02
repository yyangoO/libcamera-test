#include <iomanip>
#include <iostream>
#include <memory>

#include <libcamera/libcamera.h>

using namespace std;
using namespace libcamera;


static shared_ptr<Camera> camera;


int main(void)
{
    string camera_id = "";
    unique_ptr<CameraManager> cm = make_unique<CameraManager>();

    cm->start();

    if (cm->cameras().empty()) 
    {
        cout << "[no cameras were identified on the system.]" << endl;
        cm->stop();
        return EXIT_FAILURE;
    }

    cout << "[camera device list begin]" << endl;
    for (auto const &camera : cm->cameras())
    {
        cout << camera->id() << endl;
    }
    cout << "[camera device list end]" << endl;

    camera_id = cm->cameras()[0]->id();
    camera = cm->get(camera_id);
    camera->acquire();

    cm->stop();

    return 0;
}