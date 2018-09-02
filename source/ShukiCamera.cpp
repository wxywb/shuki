#include<ShukiCamera.h>
#include<cmath>
#include<windows.h>
namespace shuki {

Camera::Camera(Vector3f & pos,int phi,int theta, float speed)
     :  m_pos(pos), m_speed(speed), m_phi(phi),m_theta(theta)
{
    m_front = calculateFront();
    m_right = -vmath::cross( Vector3f(0.0, 1.0f, 0.0), m_front );
    m_up = vmath::cross(m_front, m_right);
} 

Camera::Camera(Vector3f & eye, Vector3f & center, Vector3f & up) {

}

void 
Camera::move(Vector3f & direction)
{  
    m_pos += m_speed * direction;
}

mat4
Camera::getMatirxMatrix() 
{
    vec3 worldup(0.0f, 1.0f, 0.0f);
    vec3 front = calculateFront();
    vec3 nfront = vec3(0, 0, -1);
    return lookat(m_pos, m_pos + front, worldup);
}

Vector3f 
Camera::getfront() 
{
    return m_front;
}

Vector3f 
Camera::getup() 
{
    return m_up;
}

Vector3f 
Camera::getright() 
{
    return -cross(vec3(0.0f,1.0f,0.0f),m_front);
}

Vector3f
Camera::getPosition() 
{
    return m_pos;
}

void 
Camera::point(float pX, float pY) 
{
    static float old_pX = 0;
    static float old_pY = 0;
    int angular_velocity = 1;
    float Nphi = m_phi + angular_velocity * (pX - old_pX > 0 ? 0.25f : -0.25f);
    if (Nphi > 180.0f)
        Nphi -= 180.0f;
    else if (Nphi < -180.0f)
        Nphi += 180.0f;
    else

        m_phi = Nphi;
    float Ntheta = m_theta + angular_velocity * (pY-old_pY > 0 ? -0.25f : 0.25f);
    if (Ntheta > -80 && Ntheta < 80)
        m_theta = Ntheta;
    old_pX = pX;
    old_pY = pY;
}

Vector3f 
Camera::calculateFront() {
    
    return normalize(Vector3f(sin(radians(m_phi)),sin(radians(m_theta)),-cos(radians(m_phi))));
}

}