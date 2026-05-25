/*
Implementation of mathematics needed in OpenGL. 
This is a header-only library.

This library will handle all the math needed by opengl, such as vector and matrix multiplications,normalization etc.

Created on 13 May 2026

*/    
#pragma once

#ifndef GL_MATH
#define GL_MATH
#include <cmath>

namespace glMath{
#include "constants.hpp"
#include "structs.hpp"

//To find the magnitude of a vector. T is the type of data, and N is the size of the vec to pass
template<typename T, int N>
inline float magnitude(const vec<T, N> &A){
    float r = 0.0f;
    for(int i = 0; i < N ; i++){
        r += (A[i]*A[i]);
    }
    return sqrt(r);
}
/*
Normalizes A. The elements will be floats between 0.0 and 1.0. More useful for vectors than matrices. If you ask for a vector with magnitude 0 to be normalized, I am sincerely concerned for you :|
*/
template<typename T, int N>
constexpr vec<T, N> normalize(const vec<T, N> &A, T mag = 0.0f){
    static_assert(((T != float) || (T != double)), "Check normalize");
    vec<T, N> result = vec<T, N>();
    T r;
    if(mag == 0.0f) r = magnitude<T, N>(A);
    else r = mag;

    if(r <= glMath::Epsilonf )return A;
    else{
        T inr = T(1)/r;
        for(int i = 0; i < N ; i++){
            result.data[i] = (A[i]) * inr;
        }
    }
    return result;
}
/*
Finds the dot product between A and B.
*/
template<typename T, int N>
constexpr inline T dot(const vec<T, N> &A, const vec<T, N> &B){
    return (A * B);
}
/*
Finds the cross product between vectors A and B, in that order. Exclusively for vec3.
*/
constexpr inline vec3 cross(const vec3 &A, const vec3 &B){
    vec3 crossprod = vec3();
    crossprod[0] = (A[1]*B[2]) - (A[2]*B[1]);
    crossprod[1] = (A[2]*B[0]) - (A[0]*B[2]);
    crossprod[2] = (A[0]*B[1]) - (A[1]*B[0]);
    return crossprod;
}
/*
Finds the angle between two vectors in radians.
*/
template<typename T, int N>
inline float angle(const vec<T, N> &A, const vec<T, N> &B){
    T Angle = 0.0f;
    T magA = magnitude<T, N>(A);
    T magB = magnitude<T, N>(B);
    if((magA == 0)||(magB == 0)) return 0.0f;
    T cosval = (dot<T, N>(A, B))/(magA*magB);
    Angle = acos(clamp(cosval, -1.0, 1.0));
    return Angle;
}
/*
Returns a translation matrix. N must be the matrix size you want returned, and trans will be set to a vec with size N-1.
*/
template<typename T, int N>
mat<T, N, N> translate(const vec<T, N> &trans){
    mat<T, N, N> A = mat<T, N, N>();
    for(int i = 0; i < N; i++){
        A.data[N][i] = trans[i];
    }
    return A;
}

/*
Changes Vector rotated by Angle around the axis given. Uses the Rodriguez formula to compute the rotated vector. Use to rotationMatrix for rotation matrices
*/
vec3 rotate(const vec3 &Vector, const double Angle, const vec3 &axis){
    vec3 result{};
    auto rotaxis = normalize<float, 3>(axis, 0.0f);
    vec3 crossProdcomponent = cross(rotaxis, Vector) * sin(Angle);
    vec3 dotProdComponent = rotaxis * dot<float, 3>(Vector, axis);
    dotProdComponent = dotProdComponent*(1-cos(Angle));
    for(int row = 0; row < 3;row++){
        result[row] = (Vector[row]*cos(Angle)) + dotProdComponent[row] + crossProdcomponent[row];
    }
    return result;
}

/*
Returns a rotation matrix for given angle and axis. Axis should be x, y, z. Uses the general 3D rotation matrices. For rotating a vector, use rotate.
*/
template<typename T>
mat<T, 3, 3> rotationMatrix(const double Angle, const char axis){
    mat<T, 3, 3> result = mat<T, 3, 3>();
    switch ((int)axis)
    {
    case 'x':
        result[0][0] = T(1);
        result[1][1] = cos(Angle);result[2][1] = -sin(Angle);
        result[1][2] = sin(Angle);result[2][2] = cos(Angle);
        break;
    case 'y':
        result[1][1] = T(1);
        result[0][0] = cos(Angle);result[2][0] = sin(Angle);
        result[0][2] = -sin(Angle);result[2][2] = cos(Angle);
        break;
    case 'z':
        result[2][2] = T(1);
        result[0][0] = cos(Angle);result[1][0] = -sin(Angle);
        result[0][1] = sin(Angle);result[1][1] = cos(Angle);
        break;
    default:
        printf("Invalid axis");
        break;
    }
    return result;
}

/*
Returns a lookAt matrix. These convert world coords of an object into coords as if the camera were the origin. The UpDir variable assumes it is the up direction of the camera. Do not give (0, 0, 1) unless you know what you are doing. ForwardDir is the direction the camera is actually looking at.
*/
mat<float, 4, 4> lookAt(const vec3 CameraPos, const vec3 ForwardDir, const vec3 UpDir, const vec3 RightDir){
    mat<float, 4, 4> result = 
    mat<float, 4, 4>({
        {RightDir[0], UpDir[0], ForwardDir[0], CameraPos[0]},
        {RightDir[1], UpDir[1], ForwardDir[1], CameraPos[1]},
        {RightDir[2], UpDir[2], ForwardDir[2], CameraPos[2]},
        {0.0f, 0.0f, 0.0f, 1.0f}});
    return result;
}

/*
Returns a perspective matrix. Involves clipping vertices outside the camera frustum, shrinking further objects to give depth. T should not be bool or void.
*/
template<typename T>
mat<T, 4, 4> perspective(const T FOV, const T aspect, const T near, const T farthest){
    static_assert((T == bool) || (T == void), "Perspective matrix data type is invalid.");
    mat<T, 4, 4> result = mat<T, 4, 4>();
    result[0][0] = 1/(tan(FOV/2)*aspect);
    result[1][1] = 1/tan(FOV);
    result[2][2] = (farthest+near)/(near-farthest);
    result[3][2] = (2/(near-farthest))*(farthest*near)
    result[2][3] = -1;
    return result;
}

/*
Returns the transpose matrix of A.
*/
template<typename T, int c, int r>
mat<T, c, r> transpose(const mat<T, c, r> &A){
    mat<T, c, r> result = mat<T, c, r>();
    for(int col = 0; col < c; col++){
        for(int row = 0; row < r; row++){
            result[col][row] = A[row][col];
        }
    }
    return result;
}

#endif
}; // namespace glMath