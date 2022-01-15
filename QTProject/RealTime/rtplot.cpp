#include "rtplot.h"

//DataSet
template<>
void DataSet::addData<std::string>(const std::vector<std::string> vector) {
    sdatas.push_back(Data<std::string>{counter,vector});
    ++counter;
}

template<>
void DataSet::addData<float>(const std::vector<float> vector) {
    fdatas.push_back(Data<float>{counter,vector});
    ++counter;
}

template<>
void DataSet::addData<int>(const std::vector<int> vector) {
    idatas.push_back(Data<int>{counter,vector});
    ++counter;
}

void DataSet::addDatai(int length, ...) {
    va_list vl;

    va_start(vl, length);

    std::vector<int> temp;
    for(int i = 0; i < length; ++i) {
        temp.push_back(va_arg(vl,int));
    }
    idatas.push_back(Data<int>{counter,temp});
    ++counter;

}

void DataSet::addDataf(int length, ...) {
    va_list vl;

    va_start(vl, length);

    std::vector<float> temp;
    for(int i = 0; i < length; ++i) {
        temp.push_back((float) va_arg(vl,double));
    }
    fdatas.push_back(Data<float>{counter,temp});
    ++counter;
}

void DataSet::deleteData(int id) {
    //for(std::vector<Data<std::string>>::iterator iter = sdatas.begin(); iter != sdatas.end(); ++iter) {
    ITER(Data<std::string>,sdatas) {
        if((*iter).id == id) {
            sdatas.erase(iter);
            return;
        }
    }
    ITER(Data<int>,idatas) {
        if((*iter).id == id) {
            idatas.erase(iter);
            return;
        }
    }
    ITER(Data<float>,fdatas) {
        if((*iter).id == id) {
            fdatas.erase(iter);
            return;
        }
    }
}

void DataSet::deleteAll(){
    sdatas.clear();
    idatas.clear();
    fdatas.clear();
}

template <>
Data<int>& DataSet::getDataByIndex<int>(int index) {
    return idatas[index];
}
template <>
Data<float>& DataSet::getDataByIndex<float>(int index) {
    return fdatas[index];
}
template <>
Data<std::string>& DataSet::getDataByIndex<std::string>(int index) {
    return sdatas[index];
}


int DataSet::getLength() {
    return sdatas.size() + fdatas.size() + idatas.size();
}

void DataSet::printData() {
    std::cout << "===== " + name + " =====" << "\n";
    for (size_t i = 0; i < sdatas.size(); ++i) {
        std::cout << "[StringDataSet " << i << "] : ";
        printDataSet(sdatas[i]);
    }
    for (size_t i = 0; i < fdatas.size(); ++i) {
        std::cout << "[FloatDataSet " << i << "] : ";
        printDataSet(fdatas[i]);
    }
    for (size_t i = 0; i < idatas.size(); ++i) {
        std::cout << "[IntDataSet " << i << "] : ";
        printDataSet(idatas[i]);
    }
    std::cout << "====================" << "\n";
}


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


    size_plot.width = (size_chart.width) - (margins.left + margins.right);
    size_plot.height = (size_chart.height) - (margins.top + margins.bottom) - (title.size.height);

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

