#pragma once
#include <iostream>
#include <vector>
#include <stdarg.h>
#include "drawingview.h"
#ifndef RTPLOT_H
#define RTPLOT_H

#define DEFAULT_FONT "Ubuntu-L.ttf"
#define DEFAULT_FONT_SIZE 12

//Color Preset
#define COLOR_DARK Simd::Pixel::Bgr24(0,0,0)


typedef unsigned char Flag;

//위치 및 크기 관련 struct
struct Margin {
    int top = 20;
    int right = 20;
    int bottom = 20;
    int left = 20;
};

struct Size {
    int width = 0;
    int height = 0;
};

struct Position {
    int x = 0;
    int y = 0;
};


//Text 관련 struct
struct TextAttribute {
    std::string font = DEFAULT_FONT;
    float size = DEFAULT_FONT_SIZE;
    Simd::Pixel::Bgr24 color = COLOR_DARK;
};


struct Title {
    std::string text;
    TextAttribute text_attribute;
    Size size = {100,50};
    Position position;
};

//Axis 관련 enum
enum class AxisType {
    NUMERICAL,
    LEGEND,
    SCALE
};

enum class Dock {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

//Data 관련
template<typename T>
struct Data {
    int id;
    std::vector<T> values;
};


class DataSet {
private:
    std::string name;
    std::vector<Data<std::string>> sdatas;
    std::vector<Data<float>> fdatas;
    std::vector<Data<int>> idatas;
    int counter = 0;

public:
    DataSet() : name("new dataset") {}
    DataSet(std::string name) : name(name){}

    template<typename U>
    void addData(const std::vector<U> vector);

    void addDatai(int length, ...);
    void addDataf(int length, ...);

    void deleteData(int id);
    void deleteAll();

    template<typename U>
    std::vector<Data<U>> getDataById(int id);
    int getID(int index);
    int getLength();

    void printData(int id);
};

class Axis {
private:
    /*
     * 초기화 시 size에서 major_interval_pixel_min과 max의 중간값으로  major_ticks 산출 -> increment계산 후 major_ticks개수 만큼 draw
     * scale 변경 시 increment를 scale에 맞추어 줄임 -> major_ticks 계산 -> 계산 값에 맞게 draw
     */

    //Common

    //NUMERICAL
    float max_value = 1.0f; // 계산값
    float min_value = 0.0f; // 계산값
    float increment;
    int major_ticks;
    int minor_ticks;
    float offset;
    float scale;
    float major_interval_pixel_min = 100;
    float major_interval_pixel_max = 300;

    //LEGEND
    std::vector<std::string> legend;
    int legend_count;

    //SCALE


    //Axis
    View view_axis;
    void* view_axis_memory;

    std::string id;

    Dock dock;

    std::string title;
    TextAttribute text_attribute;
    Size size_plot;
    Size size;
public:
    Axis(std::string id,Dock dock, Size size_plot, AxisType axis_type);
    //~Axis();

    //Init
    bool Init();

    //View
    const View& getView();
    const uint8_t* getBitmap();

    //Attribute
    void setDock(Dock dock);
    void setTitle(std::string title);
    void setFont(std::string font);
    void setFontSize(float size);
    void setFontColor(Simd::Pixel::Bgr24 color);
    Size getSize();

    //Function
    void TransformScale(float scale);
    void TransformOffset(float offset);
};

class plot2D {
private:
    //Layout
    Size size_chart; // chart size
    Size size_plot;
    Position pos_plot;

    Margin margins;

    //plot2D
    View view_chart;
    View view_plot;
    void* view_chart_memory;
    void* view_plot_memory;

    std::vector<Axis> axis;

    DataSet dataset;

    Title title;

public:
    plot2D();
    plot2D(int width,int height);
    ~plot2D();

    bool init();
    void render();
    int getWidth();
    int getHeight();

    void TitleVisible(bool);

    const View& getPlot();
    const uint8_t* getBitmap();
};


#endif // RTPLOT_H
