# raytracing
A simple ray tracer

[![Build Status](https://travis-ci.com/mehrmann/raytracing.svg?branch=master)](https://travis-ci.com/mehrmann/raytracing)

![result](result.png)


## Building on Linux
###Install dependencies
```
sudo apt install build-essentials cmake
sudo apt install libfltk1.3-dev fluid
sudo apt install freeglut3 freeglut3-dev libglew1.5 libglew1.5-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx libgl1-mesa-dev
```

###Build
```
mkdir build
cd build
cmake ..
make
```

###Run
```
./raytracing
```
