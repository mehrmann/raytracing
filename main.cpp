#include <iostream>
#include <limits>
#include "vec3.h"
#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

typedef vec3<double> vec3f;
typedef ray<double> rayf;
typedef sphere<double> spheref;
typedef hitable<double> hitablef;
typedef hit_record<double> hit_recordf;
typedef hitable_list<double> hitable_listf;
typedef camera<double> cameraf;
typedef material<double> materialf;
typedef lambertian<double> lambertianf;
typedef metal<double> metalf;



vec3f color(const hitable_listf& world, const rayf& r, int depth) {
    hit_recordf rec;

    if (world.hit(r, 0.001, std::numeric_limits<double>::max(), rec)) {
        
        rayf scattered;
        vec3f attenuation;
        if (depth < 50 && rec.material->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(world, scattered, depth+1);
        } else {
            return vec3f(0,0,0);
        }
    } else {
        //didn't hit any object
        vec3f unitDirection = unitVector(r.direction());
        double t = 0.5 * (unitDirection.y() + 1.0);
        return lerp(vec3f(1.0,1.0,1.0), vec3f(0.5,0.7,1.0), t);
    }
}

int main(int argc, const char * argv[]) {
    int nx = 200;
    int ny = 100;
    int ns = 16;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    cameraf cam;

    hitable_listf world;
    world.push_back(new spheref(vec3f(0.0, 0.0, -1.0), 0.5f, new lambertianf(vec3f(0.8,0.3,0.3))));
    world.push_back(new spheref(vec3f(1.0, 0.0, -1.0), 0.5f, new metalf(vec3f(0.8,0.8,0.8))));
    world.push_back(new spheref(vec3f(0.0, -100.5, -1.0), 100, new lambertianf(vec3f(0.3,0.8,0.3))));

    for (int j=ny-1; j>=0; j--) {
        for (int i=0; i<nx; i++) {
            vec3f col = vec3f(0,0,0);
            for (int s=0; s<ns; s++) {
                double u = double(i + drand48() ) / double(nx);
                double v = double(j + drand48() ) / double(ny);
                col += color(world, cam.getRay(u, v), 0);
            }
            //multisampling correction
            col /= ns;
            //gamma correction
            col = vec3f(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            
            col *= 255.99;
            std::cout << (int)col.r() << " " << (int)col.g() << " " << (int)col.b() << "\n";
        }
    }
    return 0;
}