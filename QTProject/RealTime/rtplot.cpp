#include "rtplot.h"

plot2D::plot2D() {

}

plot2D::plot2D(int width,int height) {
    size_chart.width = width;
    size_chart.height = height;
    if(init()) {
        render();
    }
}

plot2D::~plot2D() {
    Simd::Allocator::Free(view_chart_memory);
    Simd::Allocator::Free(view_plot_memory);
}

bool plot2D::init() {
    if(size_chart.height <= 0 || size_chart.width <= 0)
    {
        return false;
    }
    size_plot.width = (size_chart.width);
    size_plot.height = (size_chart.height)*0.8;

    view_chart_memory = Simd::Allocator::Allocate(size_chart.width*size_chart.height*4, 16);
    view_chart = View(size_chart.width, size_chart.height, FORMAT, view_chart_memory);
    Simd::Fill(view_chart,255);

    view_plot_memory = Simd::Allocator::Allocate(size_plot.width*size_plot.height*4, 16);
    view_plot = View(size_plot.width, size_plot.height, FORMAT, view_plot_memory);
    Simd::Fill(view_plot,255);
    return true;
}

void plot2D::render() {


}

int plot2D::getWidth(){ return size_chart.width; }
int plot2D::getHeight(){return size_chart.height; }

const View& plot2D::getPlot() {
    return view_chart;
}

const uint8_t* plot2D::getBitmap() {
    return view_chart.data;
}

