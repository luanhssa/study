#include "camera.h"

Camera::Camera()
{
    this->eye = Vec3(1.5f, 1.5f, -2.0f);
    this->view = Vec3(2.2f, 1.0f, 0.0f);
    this->up = Vec3(0.0f, 1.0f, 0.0f);
}

void Camera::moveCamera(int direction)
{
    GLdouble speed = direction * MOVESPEED;
    GLdouble aux_x = view.x - eye.x;
    GLdouble aux_z = view.z - eye.z;


    eye.x  = eye.x  + aux_x * speed;
    eye.z  = eye.z  + aux_z * speed;
    view.x = view.x + aux_x * speed;
    view.z = view.z + aux_z * speed;
}

void Camera::rotateView(GLdouble speed)
{
    GLdouble aux_x = view.x - eye.x;
    GLdouble aux_z = view.z - eye.z;

    view.z = (float)(eye.z + sin(speed)*aux_x + cos(speed)*aux_z);
    view.x = (float)(eye.x + cos(speed)*aux_x - sin(speed)*aux_z);
}

void Camera::moveMouse(int x, int y, int width, int height)
{
    int mid_x = width  >> 1;
    int mid_y = height >> 1;
    float angle_y  = 0.0f;
    float angle_z  = 0.0f;

    if( (x == mid_x) && (y == mid_y) ) return;

    // Get the direction from the mouse cursor, set a resonable maneuvering speed
    angle_y = (float)( (mid_x - x) ) / 10000;
    angle_z = (float)( (mid_y - y) ) / 10000;

    // The higher the value is the faster the camera looks around.
    view.y += angle_z * 0.01;

    // limit the rotation around the x-axis
    int limit = 10000;
    if((view.y - eye.y) > limit)  view.y = eye.y + limit;
    if((view.y - eye.y) < -limit)  view.y = eye.y - limit;

    rotateView(-angle_y); // Rotate
}

void Camera::moveSideways(int direction)
{
    GLdouble speed = direction * MOVESPEED;
    GLdouble aux_x = view.x - eye.x;
    GLdouble aux_z = view.z - eye.z;
    GLdouble ortho_x = -aux_z;
    GLdouble ortho_z = aux_x;

    eye.x  = eye.x  + ortho_x * speed;
    eye.z  = eye.z  + ortho_z * speed;
    view.x = view.x + ortho_x * speed;
    view.z = view.z + ortho_z * speed;
}
