// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <udpbox.h>
#include <iostream>
#include <GL/glut.h>
#include <component/Scene.h>
#include <network/Dispatcher.h>
#include <network/Matcher.h>
#include <opengl/ContextMenu.h>
#include <opengl/Display.h>
#include <opengl/KeyboardController.h>
#include <opengl/MouseController.h>
#include <sensor/Sensor.h>


template <typename OnLoadCallback>
int main_opengl(int argc, char** argv, OnLoadCallback onLoadCallback)
{
    const int WIN_WIDTH = 800;
    const int WIN_HEIGHT = 800;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("opengl-stickyman");

    OrbitCamera::resetCamera();
    Display::intialization();
    glutReshapeFunc(Display::rashape);
    glutDisplayFunc(Display::display);
    glutMotionFunc(MouseController::pressedMouseCallback);
    glutMouseFunc(MouseController::mouseCallback);
    glutPassiveMotionFunc(MouseController::passiveMouseCallback);
    ContextMenu::createContextMenu();
    glutKeyboardFunc(KeyboardController::keyboardCallback);
    Display::redisplay();
    onLoadCallback();
    glutMainLoop();
    return 0;
}


int main(int argc, char** argv)
{
    model::Model sampleModel;
    sampleModel.emplace(std::make_pair(bio::Segment::Head, sensor::Sensor()));

    udpbox::Server server(1234);
    server.setOnDatagramCallback([&](udpbox::Datagram&& datagram) {
        std::string payload{datagram.payload.begin(), datagram.payload.end() - 1};

        bio::Segment segment = network::Matcher::match(datagram);
        sensorFusion::SensorData sensorData = network::Dispatcher::dispatch(datagram);
        sampleModel.at(segment).update(sensorData);

        /*        std::cout << "[" << datagram.sender << "]: ["
                  << data.accelerometer[X] << ", "
                  << data.accelerometer[Y] << ", "
                  << data.accelerometer[Z] << "]" << std::endl;*/
        openGLContext.scene.apply(sampleModel.getLayout());
        Display::redisplay();
    });

    main_opengl(argc, argv, [&server]() {
        server.start();
    });

    return 0;
}
