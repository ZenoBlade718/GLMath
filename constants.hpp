#pragma once
/*
Contains the constants and simple functions(less than 3 lines to work), used elsewhere in the library.
*/
//Constants
constexpr float PIf = 3.14159265358979323846f;
constexpr double PId = 3.14159265358979323846;
constexpr float Tauf = 2*PIf;
constexpr double Taud = 2*PId;
constexpr float ef = 2.718281828459045235360287471352f;
constexpr double ed = 2.718281828459045235360287471352;
constexpr float Epsilonf = 1e-7f;
constexpr double Epsilond = 1e-14;

//Functions that do simple operations. Optimizable with constexpr
//Converts degrees to radians.
[[nodiscard]]
constexpr inline float rad(float degrees){return degrees*(PIf/180.0f);}
constexpr inline double rad(double degrees){return degrees*(PId/180.0);}
//Converts rads to degrees.
[[nodiscard]]
constexpr inline float deg(float radians){return radians *(180.0f/PIf);}
constexpr inline double deg(double radians){return radians *(180.0/PId);}

//Returns absolute of value passed
[[nodiscard]]
constexpr float abs(float value){return (value < 0) ? -value : value;}
constexpr double abs(double value){return (value < 0) ? -value : value;}

/*Returns smaller or larger of the two values passed.
If MinMax is true, will perform min, otherwise max*/
[[nodiscard]]
constexpr float MinMax(float A, float B, bool MinMax){
    if(MinMax)return (A < B) ? A : B;
    else return (A > B) ? A : B;
}
constexpr double MinMax(double A, double B, bool MinMax){
    if(MinMax)return (A < B) ? A : B;
    else return (A > B) ? A : B;
}

//Clamps the value x between min and max. Returns x only if it is between min and max. Defaults min and max to 0 and 1 respectively
[[nodiscard]]
constexpr float clamp(float x, float min = 0.0, float max = 1.0){
    return  (x < min) ? min:
            (x > max) ? max:
            x;
}
constexpr double clamp(double x, double min = 0.0, double max = 1.0){
    return  (x < min) ? min:
            (x > max) ? max:
            x;
}

/*Linearly interpolates between A and B to find T
T is the percentage in decimals for how far along the range to return*/
[[nodiscard]]
constexpr inline float lerp(float start, float end, float T){return start+T*(end-start);}
constexpr inline double lerp(double start, double end, double T){return start+T*(end-start);}

/*Same as lerp but smooths the start and end. More computationally expensive, but smoother results than lerp. x is the value you want to interpolate with. x will be clamped.
smoothStep returns a value between 0.0 and 1.0, which can be used elsewhere.*/
[[nodiscard]]
constexpr float smoothStep(float start, float end, float x){
    if(start == end) return 0.0f;
    float t = clamp((x-start)/(end-start));
    return (t*t)*(3.0f - t*2.0f);
}
constexpr double smoothStep(double start, double end, double x){
    if(start == end) return 0.0;
    double t = clamp((x-start)/(end-start));
    return (t*t)*(3.0f - t*2.0f);
}

/*
Compares A and B and checks if the difference is less than Epsilonf. This is needed since floating point values get inaccurate as they extend in length.
Not really sure, too lazy to test. Got it from ChatGPT. Oh well, this function is here now.
*/
[[nodiscard]]
constexpr inline bool NearlyEqual(float A, float B){return ((abs(A-B)) <= Epsilonf) ? true : false;}
constexpr inline bool NearlyEqual(double A, double B){return ((abs(A-B)) <= Epsilond) ? true : false;}