#include "rtplot.h"


template<>
int DataSet::addData<DataType::DINT>(void* values) {
    datas.push_back(Data{counter,DataType::DINT, static_cast<std::vector<int>*>(values)});
    return counter++;
}
template<>
int DataSet::addData<DataType::DFLOAT>(void* values) {
    datas.push_back(Data{counter,DataType::DFLOAT, static_cast<std::vector<float>*>(values)});
    return counter++;
}
template<>
int DataSet::addData<DataType::DSTRING>(void* values) {
    datas.push_back(Data{counter,DataType::DSTRING, static_cast<std::vector<std::string>*>(values)});
    return counter++;
}

template<>
std::vector<int> createVector<int>(int length, ...) {
    va_list vl;

    va_start(vl, length);

    std::vector<int> temp;
    for(int i = 0; i < length; ++i) {
        temp.push_back(va_arg(vl,int));
    }
    //datas.push_back(Data{counter,DataType::DINT, static_cast<std::vector<int>*>(&temp)});
    //++counter;
    return temp;
}

template<>
std::vector<float> createVector<float>(int length, ...) {
    va_list vl;

    va_start(vl, length);

    std::vector<float> temp;
    for(int i = 0; i < length; ++i) {
        temp.push_back((float)va_arg(vl,double));
    }
    //datas.push_back(Data{counter,DataType::DINT, static_cast<std::vector<int>*>(&temp)});
    //++counter;
    return temp;
}


/*
void DataSet::addDataf(int length, ...) {
    va_list vl;

    va_start(vl, length);

    std::vector<float> temp;
    for(int i = 0; i < length; ++i) {
        temp.push_back((float) va_arg(vl,double));
    }
    datas.push_back(Data{counter,DataType::DFLOAT, static_cast<std::vector<float>*>(&temp)});
    ++counter;
}
*/
void DataSet::deleteData(int id) {
    ITER(Data,datas) {
        if((*iter).id == id) {
            datas.erase(iter);
            break;
        }
    }
}

Data* DataSet::getDataByID(int id) {
    ITER(Data, datas) {
        if((*iter).id == id) {
            return &(*iter);
        }
    }
    return nullptr;
}

void DataSet::printData(Data* data){
    std::cout << "Data ID : " << data->id << "/ Data Type : ";

    switch (data->type) {
    case DataType::DINT:
        std::cout << "int / ";
        printVector(static_cast<std::vector<int>*>(data->values));
        break;
    case DataType::DFLOAT:
        std::cout << "float / ";
        printVector(static_cast<std::vector<float>*>(data->values));
        break;
    case DataType::DSTRING:
        std::cout << "string / ";
        printVector(static_cast<std::vector<std::string>*>(data->values));
        break;
    }
}

void DataSet::printData(int index){
    printData(&datas[index]);
}

void DataSet::printData() {
    ITER(Data,datas) {
        printData(&(*iter));
    }
}

/*
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



*/



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

