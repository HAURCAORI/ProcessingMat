#pragma once
#include <iostream>
#include "drawingview.h"
#ifndef RTPLOT_H
#define RTPLOT_H

#define FONT_SIZE 12

typedef unsigned char Flag;

struct Margin {
    int top = 0;
    int right = 0;
    int bottom = 0;
    int left = 0;
};

struct Size {
    int width = 0;
    int height = 0;
};

struct Position {
    int x = 0;
    int y = 0;
};

struct Axis {
    bool visible;
    std::string content;
    float font_size = FONT_SIZE;
};

struct Title {
    bool visible;
    std::string content;
    float font_size = FONT_SIZE;
};

class plot {
private:

    Size size_figure; //figure size
    Size size_plot; // plot area size
    Size size_legend; // legend size
    Margin margin_outer;
    Axis axis_x;
    Axis axis_y;

public:
    View view;
    plot();
    plot(int width,int height);
    bool init();
    void render();
    int getWidth();
    int getHeight();
    const View& getView();
};

class rtplot : public plot {

public:
   rtplot(int width,int height);

   uint8_t* getBitmap();
};

#endif // RTPLOT_H
