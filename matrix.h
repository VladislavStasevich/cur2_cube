#pragma once

#include "Vector.h"

namespace cube 
{
    class Matrix
    {
    public:
        float   matrix[4][4];

	    Matrix();
	    ~Matrix();

        float& operator()(int iRow, int iCol);
        Matrix operator*(Matrix& mRight);
        Vector operator*(Vector& vRight);
        Matrix operator+(Matrix& mRight);
        Matrix& operator=(Matrix mRight);

        Matrix SetZero();
        Matrix SetIdentity();
        Matrix SetRotationX(float fRadian);
        Matrix SetRotationY(float fRadian);
        Matrix SetRotationZ(float fRadian);
        Matrix SetScale(float fxScale, float fyScale, float fzScale);
        Matrix SetTranslation(float x, float y, float z);

        Matrix SetProjection(float d);
    };
}
