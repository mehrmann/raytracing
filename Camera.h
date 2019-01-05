#ifndef CAMERAH
#define CAMERAH

#include "Ray.h"
#include "Util.h"

class Camera {
public:
    Camera() : lowerLeftCorner(-2.0, -1.0, -1.0), 
               horizontal(4.0, 0.0, 0.0),
               vertical(0.0, 2.0, 0.0),
               origin(0.0, 0.0, 0.0) {}
    
    Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 up, float vfov, float aspect, float aperture, float focusDistance) {
        lens_radius = aperture / 2;
        float theta = vfov*M_PI/180;
        float halfHeight = tan(theta/2);
        float halfWidth = aspect * halfHeight;
        origin = lookFrom;
        w = unitVector(lookFrom - lookAt);
        u = unitVector(cross(up, w));
        v = cross(w, u);
        lowerLeftCorner = origin - halfWidth*focusDistance*u - halfHeight*focusDistance*v - focusDistance*w;
        horizontal = 2*halfWidth*focusDistance*u;
        vertical = 2*halfHeight*focusDistance*v;
    }

    Ray getRay(float x, float y) {
        Vec3 rd = lens_radius * randomInUnitDisk();
        Vec3 offset = u * rd.x + v * rd.y;
        return Ray(origin + offset, lowerLeftCorner + x*horizontal + y*vertical - origin - offset);
    }

    Vec3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 origin;
    Vec3 u, v, w;
    float lens_radius;
};

#endif