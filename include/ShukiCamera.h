#include<ShukiMath.h>

#ifndef SHUKI_CAMERA_H
#define SHUKI_CAMERA_H

namespace shuki {

class Camera
{
public:
    Camera(Vector3f & pos, int phi, int theta, float speed);
    
    Camera(Vector3f & eye, Vector3f & center, Vector3f & up);

    void move(Vector3f & direction);

    mat4 getMatirxMatrix();

    Vector3f getfront();
    
    Vector3f getup();

    Vector3f getright();

    Vector3f getPosition();
    
    inline Vector3f calculateFront();

    void point(float pX, float pY);
private:

    Vector3f  m_up;
    Vector3f  m_front;
    Vector3f  m_right;
    Vector3f  m_pos;
    float     m_theta;
    float     m_phi;
    float     m_speed;
};

}



#endif