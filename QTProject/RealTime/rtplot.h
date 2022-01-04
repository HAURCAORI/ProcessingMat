#pragma once
#include <iostream>
#include<vector>
#include "drawingview.h"
#ifndef RTPLOT_H
#define RTPLOT_H

#define DEFAULT_FONT_SIZE 12

typedef unsigned char Flag;


enum Origin {
    ORIGIN_CENTER,
    ORIGIN_TOP,
    ORIGIN_RIGHT,
    ORIGIN_BOTTOM,
    ORIGIN_LEFT,
    ORIGIN_TOP_RIGHT,
    ORIGIN_TOP_LEFT,
    ORIGIN_BOTTOM_RIGHT,
    ORIGIN_BOTTOM_LEFT
};

enum ChartAttribute {
    TITLE = (0x01 << 0), // 1
    AXIS_X = (0x01 << 1), // 2
    AXIS_Y = (0x01 << 2), // 4
    LEGEND = (0x01 << 3), // 8
};

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


struct Text {
    std::string value;
    std::string font;
    float size = DEFAULT_FONT_SIZE;
};

struct Axis {
    Text text;
    Size size;
    Position position;
    Origin origin = ORIGIN_CENTER;
};

struct Title {
    Text text;
    Size size;
    Position position;
    Origin origin = ORIGIN_CENTER;
};

class plot {
private:
    Size size_chart; // chart size

    Size size_plot;
    Position pos_plot;
    Origin plot_origin = ORIGIN_TOP_LEFT;

    Margin margins;

    ChartAttribute attribute;
    Title title;
    Axis axis_x;
    Axis axis_y;
    View view_chart;
    View view_plot;

    void* view_chart_memory;
    void* view_plot_memory;

public:
    plot();
    plot(int width,int height);
    ~plot();

    bool init();
    void render();
    int getWidth();
    int getHeight();

    void TitleVisible(bool);

    const View& getPlot();
    const uint8_t* getBitmap();
};

class rtplot : public plot {

public:
   rtplot(int width,int height);
};

#endif // RTPLOT_H
