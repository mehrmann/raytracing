#include <iostream>
#include <limits>
#include <vector>
#include <future>

#include "Vec3.h"
#include "Ray.h"
#include "ObjectList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "Window.h"

Vec3 color(const ObjectList& world, const Ray& r, int depth) {
    Hit rec;

    if (world.hit(r, 0.001, std::numeric_limits<float>::max(), rec)) {
        
        Ray scattered;
        Vec3 attenuation;
        if (depth < 50 && rec.material->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(world, scattered, depth+1);
        } else {
            return Vec3(0,0,0);
        }
    } else {
        //didn't hit any object
        Vec3 unitDirection = unitVector(r.direction());
        float t = 0.5 * (unitDirection.y + 1.0);
        return lerp(Vec3(1.0,1.0,1.0), Vec3(0.5,0.7,1.0), t);
    }
}

void createSpheres(ObjectList& world) {
    for (int x=-10; x<10; x++) {
        for (int z=-10; z<10; z++) {
            float mat = drand48();
            Vec3 pos(x + 0.9 * drand48(), 0.2, z + 0.9 * drand48());
            if (mat < 0.75) {
                Vec3 col = Vec3(drand48() * drand48(), drand48() * drand48(), drand48() * drand48());
                world.push_back(std::make_shared<Sphere>(pos, 0.2, std::make_shared<Lambert>(col)));
            } else if (mat < 0.95) {
                Vec3 col = Vec3(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48()));
                world.push_back(std::make_shared<Sphere>(pos, 0.2, std::make_shared<Metal>(col, 0.5*drand48())));
            } else {
                world.push_back(std::make_shared<Sphere>(pos, 0.2, std::make_shared<Dielectric>(1.5)));
            }
        }    
    }
}

   
void trace(const ObjectList& world, std::shared_ptr<Vec3> rawData, std::shared_ptr<unsigned char> pixels, int nx, int ny, int startX, int endX, int startY, int endY) {
    int ns = 256;

    Vec3 lookFrom(6, 1.5, 2);
    Vec3 lookAt(0,0.5,-1);
    float distToFocus = (lookFrom - lookAt).length();
    float aperture = 0.5;
    Camera cam(lookFrom, lookAt, Vec3(0,1,0), 20, nx/ny, aperture, distToFocus);

    for (int s=0; s<ns; s++) {
        for (int y=startY; y<endY; y++) {
            for (int x=startX; x<endX; x++) {
                float u = float(x + drand48() ) / float(nx);
                float v = float(y + drand48() ) / float(ny);
                rawData.get()[y*nx + x] += color(world, cam.getRay(u, v), 0);
                //multisampling correction
                Vec3 col = rawData.get()[y*nx + x] / ns;
                //gamma correction
                col = Vec3(sqrt(col.r), sqrt(col.g), sqrt(col.b));
                col *= 255.99;
                int offset = (nx * (ny - y) + x) * 3;
                pixels.get()[offset] = (int)col.r;
                pixels.get()[offset + 1] = (int)col.g;
                pixels.get()[offset + 2] = (int)col.b;
            }
        }
    }
    std::cerr << "done." << std::endl;
}

int main(int argc, const char * argv[]) {
    
    int nx = 400;
    int ny = 200;
    std::shared_ptr<unsigned char> pixels(new unsigned char[nx * ny * 3], std::default_delete<unsigned char[]>());
    std::shared_ptr<Vec3> rawData(new Vec3[nx*ny]);
 
    ObjectList world;
    //createSpheres(world);
    world.push_back(std::make_shared<Sphere>(Vec3(0.0, 0.4, -0.0), 0.4f, std::make_shared<Lambert>(Vec3(0.1,0.2,0.5))));
    world.push_back(std::make_shared<Sphere>(Vec3(0.0, 1.6, -1.0), 0.4f, std::make_shared<Lambert>(Vec3(0.5,0.2,0.1))));
    world.push_back(std::make_shared<Sphere>(Vec3(0.0, 0.8, -2.0), 0.4f, std::make_shared<Lambert>(Vec3(0.1,0.5,0.2))));
    world.push_back(std::make_shared<Sphere>(Vec3(-2.5, 1.0, -2.0), 1.0f, std::make_shared<Metal>(Vec3(0.8,0.6,0.2), 0.1)));
    world.push_back(std::make_shared<Sphere>(Vec3( 1.5, 0.5, -1.0), 0.5f, std::make_shared<Dielectric>(1.5)));
    world.push_back(std::make_shared<Sphere>(Vec3(0.0, -1000, -1.0), 1000, std::make_shared<Lambert>(Vec3(0.5,0.5,0.5))));

    int numThreads = 8;
    std::list< std::thread > threads;
    int sliceWidth = nx/numThreads;
    for (int t=0; t<numThreads; t++) {
        threads.push_back(std::thread(trace, world, rawData, pixels, nx, ny, t * sliceWidth , (t+1)*sliceWidth, 0, ny));
    }
    
    showWindow(pixels, nx, ny);

    for(std::thread& thread : threads)
    {
       thread.join(); 
    }

    return 0;
}
