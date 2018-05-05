#pragma once

#include "Vector.h"
#include "Matrix.h"

#define POLYGON_MAX_ELEMENTS 100

namespace cube
{
    class Polygon
    {
    public:
        Polygon();
        virtual ~Polygon();

        int     indexBuffer[POLYGON_MAX_ELEMENTS];
        int     sizeIndex;
        Vector  vertexBuffer[POLYGON_MAX_ELEMENTS];
        int     sizeVertex;

        void SetIndexBuffer();
        void SetVertexBuffer();
        void Render(HDC hdc);

        void RotateX(float theta);
        void RotateY(float theta);
        void Translate(float tx, float ty, float tz);

        void Transform(Matrix& mat);
        void Projection(Matrix& mat);
        void ApplyViewport(float xOrigin, float yOrigin);
    };
}