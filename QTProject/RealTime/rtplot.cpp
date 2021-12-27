#include "rtplot.h"

plot::plot() {

}

plot::plot(int width,int height) {
    size_figure.width = width;
    size_figure.height = height;
    if(init()) {
        render();
    }
}

bool plot::init() {
    if(size_figure.height <= 0 || size_figure.width <= 0)
    {
        return false;
    }
    size_plot.width = (size_figure.width - margin_outer.left - margin_outer.right)*0.6;
    size_plot.height = (size_figure.height - margin_outer.top - margin_outer.bottom)*0.8;
    //view = View(size_plot.width, size_plot.height, FORMAT);
    //Simd::Fill(view,255);
    return true;
}

void plot::render() {


}

int plot::getWidth(){ return size_figure.width; }
int plot::getHeight(){return size_figure.height; }

const View& plot::getView() {
    return view;
}
rtplot::rtplot(int width,int height) : plot(width,height){

}

uint8_t* rtplot::getBitmap() {
    return getView().data;
}
