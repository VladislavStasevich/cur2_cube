#include "stdafx.h"
#include "Vector.h"
#include <math.h> 

using namespace cube;

Vector::Vector()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector::~Vector()
{
}

Vector::Vector(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector::Translate(float tx, float ty, float tz)
{
    x += tx;
    y += ty;
    z += tz;
}

void Vector::Scale(float sx, float sy, float sz)
{
    x *= sx;
    y *= sy;
    z *= sz;
}

void Vector::RotateX(float theta)
{
    float tx = x;
    float ty = y*cosf(theta) - z*sinf(theta);
    float tz = y*sinf(theta) + z*cosf(theta);

    y = ty;
    z = tz;
}

void Vector::RotateY(float theta)
{
    float tx =  x * cosf(theta) + z * sinf(theta);
    float ty =  y;
    float tz = -x * sinf(theta) + z * cosf(theta);

    x = tx;
    z = tz;
}

void Vector::RotateZ(float theta)
{
    float tx = x * cosf(theta) - y * sinf(theta);
    float ty = x * sinf(theta) + y * cosf(theta);
    float tz = z;

    x = tx;
    y = ty;
}
