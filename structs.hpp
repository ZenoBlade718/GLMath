#pragma once
/*
Contains the structs for the data used in the library.
*/
template<typename T, int size>
struct vec{
    static_assert(size > 0, "Vec size cannot be 0 or negative");
    static_assert((T != void), "Vec type cannot be bool or void");
    T data[size];
    constexpr vec<T, size> operator+(const vec<T, size> &B) const{
        vec result{};
        for(int row = 0; row < size ; row++){
            result.data[row] = data[row] + B.data[row];
        }
        return result;
    }
    constexpr vec<T, size> operator-(const vec<T, size> &B) const{
        vec<T, size> result{};
        for(int row = 0; row < size ; row++){
            result.data[row] = data[row] - B.data[row];
        }
        return result;
    }
    constexpr vec<T, size> operator*(const T B) const{
        vec<T, size> result{};
        for(int row = 0; row < size ; row++){
            result.data[row] = data[row] * B;
        }
        return result;
    }
    constexpr vec<T, size> operator/(const T B) const{
        static_assert(!((T == float) || (T == double) || (T == void)), "Check vec divisions");
        vec<T, size> result{};
        T inB = 1/B;
        for(int row = 0; row < size ; row++){
            result.data[row] = data[row] * inB;
        }
        return result;
    }
    constexpr T operator*(const vec<T, size> &B)const{
        T dot {};
        for(int i = 0; i < size; i++){
            dot += data[i]*B[i];
        }
        return dot;
    }
    constexpr bool operator==(const vec<T, size> &B) const{
        for(int i = 0; i < size;i++){
            if(!glMath::NearlyEqual(data[i], B[i])){return false;}
        }
        return true;
    }
    constexpr bool operator!=(const vec<T, size> &B) const{
        return !(*this == B);
    }
    constexpr const T& operator[](const int B)const{
        return data[B];
    }
    constexpr T& operator[](int B){
        return data[B];
    }

    constexpr vec(){for(int i = 0; i< size ;i++){data[i] = T{};}}
    constexpr vec(const T &A[size]){for(int i = 0; i < size ; i++){data[i] = A[i];}}
};

template<typename T, int r, int c>
struct mat{
    T data[c][r];
    static_assert((r > 0) && (c > 0), "Mat r or c cannot be 0 or negative");
    static_assert((T != bool) || (T != void), "Mat type cannot be bool of void");
    constexpr mat<T, c, r> operator+(const mat<T, c, r> &B) const{
        mat<T, c, r> result{};
        for(int Col = 0; Col < c ; Col++){
            for(int Row = 0; Row < r ; Row++){
                result.data[Col][Row] = data[Col][Row] + B.data[Col][Row];
            }
        }
        return result;
    }
    constexpr mat<T, c, r>& operator+=(const mat<T, c, r> &B){
        for(int Col = 0; Col < c ; Col++){
            for(int Row = 0; Row < r ; Row++){
                data[Col][Row] = data[Col][Row] + B.data[Col][Row];
            }
        }
        return *this;
    }
    constexpr mat<T, c, r> operator-(const mat<T, c, r> &B) const{
        mat<T, c, r> result{};
        for(int Row = 0; Row < r ; Row++){
            for(int Col = 0; Col < c ; Col++){
                result.data[Col][Row] = data[Col][Row] - B.data[Col][Row];
            }
        }
        return result;
    }
    constexpr mat<T, c, r>& operator-=(const mat<T, c, r> &B){
        for(int Col = 0; Col < c ; Col++){
            for(int Row = 0; Row < r ; Row++){
                data[Col][Row] = data[Col][Row] - B.data[Col][Row];
            }
        }
        return *this;
    }
    constexpr mat<T, c, r> operator*(const T B) const{
        mat<T, c, r> result{};
        for(int Row = 0; Row < r ; Row++){
            for(int Col = 0; Col < c ; Col++){
                result.data[Col][Row] = data[Col][Row] * B;
            }
        }
        return result;
    }
    constexpr mat<T, c, r>& operator*=(const T B) {
        for(int Row = 0; Row < r ; Row++){
            for(int Col = 0; Col < c ; Col++){
                data[Col][Row] = data[Col][Row] * B;
            }
        }
        return *this;
    }
    constexpr vec<T, r> operator*(const vec<T, c> &B){
        vec<T, r> result{};
        for(int Row = 0; Row < r; Row++){
            for(int Col = 0; Col < c ;Col++){
                result[Row] += data[Row][Col]*B[Col];
            }
        }
        return result;
    }
    constexpr mat<T, r, n> operator*(const mat<T, c, n> &B)const {
        mat<T, r, n> result{};
        for(int Row = 0; Row < r; Row++){
            for(int Col = 0; Col < c ;Col++){
                for(int k = 0; (k<c) ;k++){
                    result[Row][Col] += data[Row][k]*B[k][Col];
                }
            }
        }
        return result;
    }
    constexpr mat<T, c, r> operator/(const T B) const{
        static_assert(!((T == float) || (T == double) || (T == void)), "Check matrix divisions");
        mat<T, c, r> result{};
        T inB = 1/B;
        for(int Row = 0; Row < r ; Row++){
            for(int Col = 0; Col < c ; Col++){
                result.data[Col][Row] = data[Col][Row] * inB;
            }
        }
        return result;
    }
    constexpr mat<T, c, r>& operator/=(const T B){
        static_assert(!((T == float) || (T == double) || (T == void)), "Check matrix divisions");
        T inB = 1/B;
        for(int Row = 0; Row < r ; Row++){
            for(int Col = 0; Col < c ; Col++){
                data[Col][Row] = data[Col][Row] * inB;
            }
        }
        return *this;
    }
    constexpr bool operator==(const mat<T, c, r> &B) const{
        for(int row = 0; row < r;row++){
            for(int col = 0; col < c ; col++){
                if(!glMath::NearlyEqual(data[row][col], B[row][col])){return false;}
            }
        }
        return true;
    }
    constexpr bool operator!=(const mat<T, c, r> &B) const{
        return !(*this == B);
    }
    
    constexpr mat<T, r, c>(){
        if constexpr (r == c){
            for(int row = 0; row < r; row++){
                for(int col = 0; col < c; col++){
                    data[row][col] = (col == row) ? T(1) : T(0.0);
                }
            }
        }
        else {
            for(int row = 0; row < r; row++){
                for(int col = 0; col < c; col++){
                    data[row][col] = T(0);
                }
            }
        }
    }
    constexpr mat<T, c, r>(const T (&A)[c][r]){
        for(int col = 0; col < c; col++){
            for(int row = 0; row < r; row++){
                data[col][row] = A[col][row];
            }
        }
    }
    //This uses column-major construction
    constexpr mat<T, c, r>(const vec<T, r> (&A)[c]){
        for(int col = 0; col<c;col++){
            for(int row = 0; row<r;row++){
                data[col][row] = A[row].data[col];
            }
        }
    }
};
//Commonly used types
using vec2 = vec<float, 2>;
using vec3 = vec<float, 3>;
using vec4 = vec<float, 4>;
using mat2 = mat<float, 2, 2>;
using mat3 = mat<float, 3, 3>;
using mat4 = mat<float, 4, 4>;