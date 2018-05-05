#include "stdafx.h"
#include "Matrix.h"
#include <math.h>

using namespace cube;

Matrix::Matrix()
{
    SetIdentity();
}

Matrix::~Matrix()
{
}

float& Matrix::operator()(int iRow, int iCol)
{
    return matrix[iRow][iCol];
}

Matrix Matrix::operator*(Matrix& mRight)
{
    Matrix mRet;

    mRet.SetZero();
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            for (int k = 0; k < 4; ++k)
            {
                mRet(i, j) += matrix[i][k] * mRight(k, j);
            }
        }
    }

    return mRet;
}

Vector Matrix::operator*(Vector& vLeft)
{
    Vector vRet;

    vRet.x = vLeft.x * matrix[0][0] +
             vLeft.y * matrix[0][1] +
             vLeft.z * matrix[0][2] +
             matrix[0][3];
    vRet.y = vLeft.x * matrix[1][0] +
             vLeft.y * matrix[1][1] +
             vLeft.z * matrix[1][2] +
             matrix[1][3];
    vRet.z = vLeft.x * matrix[2][0] +
             vLeft.y * matrix[2][1] +
             vLeft.z * matrix[2][2] +
             matrix[2][3];
    return vRet;
}

Matrix Matrix::operator+(Matrix& mRight)
{
    Matrix mRet;

    for (int i=0; i<4; ++i)
    {
        for (int j=0; j<4; ++j)
        {
            mRet(i,j) = matrix[i][j] + mRight(i,j);
        }
    }

    return mRet;
}

Matrix& Matrix::operator=(Matrix mRight)
{
    memcpy( matrix, mRight.matrix, sizeof(matrix) );
    return *this;
}

Matrix Matrix::SetZero()
{
    memset( matrix, 0, sizeof(matrix) );

    return *this;
}

Matrix Matrix::SetIdentity()
{
    SetZero();

    matrix[0][0] =
    matrix[1][1] =
    matrix[2][2] =
    matrix[3][3] = 1.f;

    return *this;
}

Matrix Matrix::SetRotationX(float fRadian)
{
    SetIdentity();
    matrix[1][1] = cosf(fRadian);
    matrix[1][2] = -sinf(fRadian);
    matrix[2][1] = sinf(fRadian);
    matrix[2][2] = cosf(fRadian);
    return *this;
}

Matrix Matrix::SetRotationY(float fRadian)
{
    SetIdentity();
    matrix[0][0] = cosf(fRadian);
    matrix[0][2] = sinf(fRadian);
    matrix[2][0] = -sinf(fRadian);
    matrix[2][2] = cosf(fRadian);
    return *this;
}

Matrix Matrix::SetRotationZ(float fRadian)
{
    SetIdentity();
    matrix[0][0] = cosf(fRadian);
    matrix[0][1] = -sinf(fRadian);
    matrix[1][0] = sinf(fRadian);
    matrix[1][1] = cosf(fRadian);
    return *this;
}

Matrix Matrix::SetScale(float fxScale, float fyScale, float fzScale)
{
    SetIdentity();
    matrix[0][0] = fxScale;
    matrix[1][1] = fyScale;
    matrix[2][2] = fzScale;

    return *this;
}

Matrix Matrix::SetTranslation(float x, float y, float z)
{
    SetIdentity();
    matrix[0][3] = x;
    matrix[1][3] = y;
    matrix[2][3] = z;

    return *this;
}

Matrix Matrix::SetProjection(float d)
{
    SetZero();
    matrix[0][0] = d;
    matrix[1][1] = d;
    matrix[3][2] = 1;
    matrix[3][3] = d;

    return *this;
}
