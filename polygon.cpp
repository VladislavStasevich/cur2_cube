#include "stdafx.h"
#include "Polygon.h"

using namespace cube;

void DrawIndexedPrimitive(
    HDC hdc,
    int*        indexBuffer,       // index buffer
    int         primitiveCounter,  // primitive counter
    Vector*     vertexBuffer)      // vertex buffer
{
    int   i1, i2;
    int   counter = 0;

    for (int i = 0; i < primitiveCounter; ++i)
    {
		// get index
        i1 = indexBuffer[counter];
        i2 = indexBuffer[counter+1];

		// draw line
        MoveToEx( hdc, int(vertexBuffer[i1].x),
            int(vertexBuffer[i1].y), NULL );
        LineTo( hdc, int(vertexBuffer[i2].x),
            int(vertexBuffer[i2].y) );

		// advance to next primitive
        counter += 2;
    }
}

Polygon::Polygon()
{
    sizeIndex  = 0;
    sizeVertex = 0;
}

Polygon::~Polygon()
{
}

void Polygon::SetIndexBuffer()
{
    int buffer[] = {0,1,1,2,2,3,3,0,4,5,5,6,6,7,7,4,0,4,1,5,2,6,3,7};
    for (int i = 0; i < sizeof(buffer); ++i)
    {
        indexBuffer[i] = buffer[i];
    }
    sizeIndex = 24;
}

void Polygon::SetVertexBuffer()
{
    vertexBuffer[0] = Vector( -50.f,  50.f, -50.f);
    vertexBuffer[1] = Vector( -50.f, -50.f, -50.f);
    vertexBuffer[2] = Vector(  50.f, -50.f, -50.f);
    vertexBuffer[3] = Vector(  50.f,  50.f, -50.f);
    vertexBuffer[4] = Vector( -50.f,  50.f,  50.f);
    vertexBuffer[5] = Vector( -50.f, -50.f,  50.f);
    vertexBuffer[6] = Vector(  50.f, -50.f,  50.f);
    vertexBuffer[7] = Vector(  50.f,  50.f,  50.f);
    
    sizeVertex = 8;
}

void Polygon::Render(HDC hdc)
{
    ::DrawIndexedPrimitive(
        hdc,
        indexBuffer,     // index buffer
        12,              // primitive counter
        vertexBuffer     // vertex buffer
    );
}

void Polygon::DebugRender(HDC hdc)
{
    float
        left = vertexBuffer[0].x,
        top = vertexBuffer[0].y,
        right = vertexBuffer[0].x,
        bottom = vertexBuffer[0].y;
    for (int i = 0; i < sizeVertex; i++) 
    {
        if (left > vertexBuffer[i].x) left = vertexBuffer[i].x;
        if (right < vertexBuffer[i].x) right = vertexBuffer[i].x;
        if (top < vertexBuffer[i].y) top = vertexBuffer[i].y;
        if (bottom > vertexBuffer[i].y) bottom = vertexBuffer[i].y;
    }

    MoveToEx(hdc, left, bottom, NULL);
    LineTo(hdc, left, top);

    MoveToEx(hdc, left, bottom, NULL);
    LineTo(hdc, right, bottom);

    MoveToEx(hdc, right, bottom, NULL);
    LineTo(hdc, right, top);

    MoveToEx(hdc, right, top, NULL);
    LineTo(hdc, left, top);
}

void Polygon::RotateX(float theta)
{
    for (int i = 0; i < sizeVertex; ++i)
    {
        vertexBuffer[i].RotateX(theta);
    }
}

void Polygon::RotateY(float theta)
{
    for (int i = 0; i < sizeVertex; ++i)
    {
        vertexBuffer[i].RotateY(theta);
    }
}

void Polygon::Translate(float tx, float ty, float tz)
{
    for (int i = 0; i < sizeVertex; ++i)
    {
        vertexBuffer[i].Translate(tx, ty, tz);
    }
}

void Polygon::Transform(Matrix& mat)
{
    for (int i=0; i < sizeVertex; ++i)
    {
        vertexBuffer[i] = mat * vertexBuffer[i];
    }
}

void Polygon::Projection(Matrix& mat)
{
    float d = mat(0,0);
    float z;

    for (int i = 0; i < sizeVertex; ++i)
    {
        z = vertexBuffer[i].z;
        vertexBuffer[i] = mat * vertexBuffer[i];
        vertexBuffer[i].x /= (z+d);
        vertexBuffer[i].y /= (z+d);
    }
}

void Polygon::ApplyViewport( float xOrigin, float yOrigin )
{
    for(int i = 0; i < sizeVertex; ++i) 
    {
        vertexBuffer[ i ].x += xOrigin;
        vertexBuffer[ i ].y += yOrigin;
    }
}

