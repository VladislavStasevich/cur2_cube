#pragma once

namespace cube 
{
    class Vector
    {
    public:
        Vector();
        virtual ~Vector();

        Vector(float x, float y, float z);

        float x;
        float y;
        float z;

        void Translate(float tx, float ty, float tz);
        void Scale(float sx, float sy, float sz);
        void RotateX(float theta);
        void RotateY(float theta);
        void RotateZ(float theta);
    };
}
