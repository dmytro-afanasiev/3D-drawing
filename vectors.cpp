#include <math.h>


struct vec2
{
    float x;
    float y;
    vec2(float x, float y) {
        this->x = x;
        this->y = y;
    };
    vec2(float x):vec2(x, x){};

    vec2 operator +(const vec2 & another){
        return vec2(x+another.x, y+another.y);
    };
    vec2 operator -(const vec2 & another){
        return vec2(x-another.x, y-another.y);
    };
    vec2 operator *(const vec2 & another){
        return vec2(x*another.x, y*another.y);
    };
    vec2 operator /(const vec2 & another){
        return vec2(x/another.x, y/another.y);
    };
    float length(){
        return sqrt(x*x + y*y);
    }
    vec2 norm(){
        float len = this->length();
        return vec2(x/len, y/len);
    }
    float dot(vec2 & another){
        return x*another.x + y*another.y;
    }
};

struct vec3
{
    float x;
    float y;
    float z;
    vec3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    };
    vec3(float x):vec3(x, x, x){};

    vec3(float x, vec2 & another): vec3(x, another.x, another.y){};

    vec3 operator +(const vec3 & another){
        return vec3(x+another.x, y+another.y, z+another.z);
    };
    vec3 operator -(const vec3 & another){
        return vec3(x-another.x, y-another.y, z-another.z);
    };
    vec3 operator *(const vec3 & another){
        return vec3(x*another.x, y*another.y, z*another.z);
    };
    vec3 operator /(const vec3 & another){
        return vec3(x/another.x, y/another.y, z/another.z);
    };
    float length(){
        return sqrt(x*x + y*y + z*z);
    }
    vec3 norm(){
        float len = this->length();
        return vec3(x/len, y/len, z/len);
    }
    float dot(vec3 & another){
        return x*another.x + y*another.y+z*another.z;
    }
};

vec2 sphIntersect(vec3 & ro, vec3 & rd, vec3 & ce, float ra)
{
    vec3 oc = ro - ce;
    float b = oc.dot(rd);
    float c = oc.dot(oc) - ra*ra;
    float h = b*b - c;
    if( h<0.0 ) return vec2(-1.0); // no intersection
    h = sqrt( h );
    return vec2( -b-h, -b+h );
}
