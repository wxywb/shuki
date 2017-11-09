//#pragma once

#ifndef SHUKIMATH_H
#define SHUKIMATH_H

#include <vmath.h>

using namespace vmath;
//template<class T, int n>
//struct VectorProtype {
//    T data[n];
//
//    T& operator[](int idx) {
//        return data[idx];
//    }
//   
//     VectorProtype() {
//        memset(data, 0, sizeof(data));
//    }
//
//
//    T operator+ (VectorProtype<T, n> rhs) {
//        VectorProtype<T, n> res(*this);
//        for (int i = 0; i < n; i++)
//        {
//            res.data[i] += rhs.data[i];
//        }
//        return res;
//    }
//     
//    void
//     show() {
//         for (int i = 0; i < n; i++) 
//         {
//             cout << data[i] << ' ';
//         }
//         cout << std::endl;
//     }
//
//    VectorProtype(T f1, T f2, T f3) {
//        
//        data[0] = f1;
//        data[1] = f2;
//        data[2] = f3;
//    };
//    VectorProtype(T f1, T f2) {
//   
//        data[0] = f1;
//        data[1] = f2;
//    
//    };
//
//};
//
//
//
//typedef VectorProtype<float, 3> Vector3f;
//typedef VectorProtype<float, 2> Vector2f;
//typedef VectorProtype<double, 3> Vector3d;
//typedef VectorProtype<double, 2> Vector2d;
//typedef VectorProtype<int, 3> Vector3i;
//typedef VectorProtype<int, 2> Vector2i;


typedef vec3    Vector3f;
typedef vec2    Vector2f;
typedef ivec3   Vector3i;
typedef ivec2   Vector2i;

namespace vmath {
    static inline mat4  perspective_red(float width, float height, float near, float far)
    {
        float q = near / (width / 2);
        float A = near / (height / 2);
        float B = - (far + near) / (far - near);
        float C = 2 * far * near / (far - near);

        mat4 result;

        result[0] = vec4(q, 0.0f, 0.0f, 0.0f);
        result[1] = vec4(0.0f, A, 0.0f, 0.0f);
        result[2] = vec4(0.0f, 0.0f, B, C);
        result[3] = vec4(0.0f, 0.0f, 1.0f, 0.0f);
        return result;
    }
}

#endif 