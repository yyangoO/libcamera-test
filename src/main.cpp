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
#include <iostream>
#include <memory>

#include "libcamera/libcamera.h"

#include "utils.h"

using namespace std;
using namespace libcamera;


// the camera device
static shared_ptr<Camera> camera;


int main(void)
{
    string camera_id = "";
    unique_ptr<CameraManager> cm = make_unique<CameraManager>();

    cm->start();

    // check do we have camera device or not
    if (cm->cameras().empty()) 
    {
        cout << colored_str("[errpr]--> no cameras device. ", "red", true) << endl;
        cm->stop();
        return EXIT_FAILURE;
    }
    // list all camera device ID
    for (auto const &camera : cm->cameras())
    {
        cout << colored_str("[camera device id]--> ", "yellow") << camera->id() << endl;
    }

    // acquire a camera
    camera_id = cm->cameras()[0]->id();
    camera = cm->get(camera_id);
    camera->acquire();


    // release the camera and camera manager
	camera->release();
	camera.reset();
	cm->stop();

    return 0;
}