#pragma once

#include<iostream>
#include <GL/freeglut.h>
#include <ShukiCamera.h>
#include <ShukiApp.h>
#include<ShukiModel.h>

extern shuki::Camera       * gCamera;
extern shuki::App          * global_app;
extern shuki::ShaderManger * global_sm;
extern shuki::Model * global_model;
extern shuki::ShaderManger * global_sm2;


void RenderSceneCB();
static void UpdateCameraProjMat() {

    GLint CameraLoc = glGetUniformLocation(global_sm->getprogram(), "CameraMat");
   // GLint CameraLoc = global_sm->get_uniform_loc("CameraMat");//glGetUniformLocation(global_sm->getprogram(), "CameraMat");
    auto CameraProjMat = gCamera->getMatirxMatrix();
    glUniformMatrix4fv(CameraLoc, 1, false, CameraProjMat);

}

static void 
PassiveMouseCB(int x, int y)
{
    int width = global_app->_width;
    int height = global_app->_height;
    float normalized_x = 2 * ((float)x / (float)width - 0.5);
    float normalized_y = 2 * ((float)y / (float)height - 0.5);
    gCamera->point(normalized_x, normalized_y);
    RenderSceneCB();

}

static void 
SpecialKeys(int key, int x, int y)
{
    vec3 direction;
    switch (key) {
        case GLUT_KEY_UP:
            direction = gCamera->getfront();
            gCamera->move(direction);
            break;
        case GLUT_KEY_DOWN:
            direction = gCamera->getfront() * -1;
            gCamera->move(direction);
            break;

        case GLUT_KEY_CTRL_L:
            std::cout << "change shader" << std::endl;
            global_sm2->use();
            break;
        case GLUT_KEY_LEFT:
            direction = gCamera->getright() * -1;
            gCamera->move(direction);
            break;
        case GLUT_KEY_RIGHT:
            direction = gCamera->getright();
            gCamera->move(direction);
            break;
    }
    glutPostRedisplay();
}

