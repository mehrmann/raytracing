#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <stdio.h>
#include <time.h>

#define XSIZE 500
#define YSIZE 500
#define UPDATE_RATE 0.05     // update rate in seconds

// Demonstrate how to display a pixel buffer in FLTK

// WINDOW CLASS TO HANDLE DRAWING IMAGE
class MyWindow : public Fl_Double_Window {
    
    std::shared_ptr<unsigned char> pixels;

    // FLTK DRAW METHOD
    void draw() {
        fl_draw_image(pixels.get(), 0, 0, w(), h(), 3, w()*3);
    }

    static void RenderImage_CB(void *userdata) {
        MyWindow *win = (MyWindow*)userdata;
        win->RenderImage();
        Fl::repeat_timeout(UPDATE_RATE, RenderImage_CB, userdata);
    }

public:
    // CTOR
    MyWindow(std::shared_ptr<unsigned char> p, int w, int h, const char *name=0) : pixels(p), Fl_Double_Window(w,h,name) {
        end();
        RenderImage();
        Fl::add_timeout(UPDATE_RATE, RenderImage_CB, (void*)this);
    }

    void RenderImage() {
        redraw();
    }
};

int showWindow(std::shared_ptr<unsigned char> pixels, int width, int height) {
    Fl::visual(FL_RGB);         // prevents dithering on some systems
    MyWindow *win = new MyWindow(pixels, width, height);
    win->show();
    return(Fl::run());
}