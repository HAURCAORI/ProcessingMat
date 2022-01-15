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


void* DataSet::getData(int index) {
    return &sdatas[index].values;
}

template<>
int DataSet::getLength<std::string>() {
    return sdatas.size();
}

template<>
int DataSet::getLength<int>() {
    return idatas.size();
}


template<>
int DataSet::getLength<float>() {
    return fdatas.size();
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
//----------Axis----------
Axis::Axis() {

}

Axis::Axis(int id, void* values, Type type, Dock dock, Size* size_plot) :id(id),values(values),type(type),dock(dock),size_plot(size_plot) {
    if(dock == Dock::LEFT || dock == Dock::RIGHT) {
        size.height = size_plot->height;
        size.width = default_size;
    } else {
        size.height = default_size;
        size.width = size_plot->width;
    }
    view_axis_memory = Simd::Allocator::Allocate(size.width*size.height*CHANNEL, 16);
    view_axis = View(size.width, size.height, FORMAT, view_axis_memory);
    Simd::Fill(view_axis,200);

    if(type == Type::INT) {
        std::vector<int>* temp = (std::vector<int>*) values;
        std::cout << "size : " << temp->size() << std::endl;
    }
}

Axis::~Axis() {
    Simd::Allocator::Free(view_axis_memory);
}

View& Axis::getView() {
    return view_axis;
}


int Axis::getWidth(){ return size.width; }
int Axis::getHeight(){return size.height; }



plot2D::plot2D(int width,int height) {
    size_chart.width = width;
    size_chart.height = height;
    if(init()) {
        render();
    }
}
plot2D::plot2D(int width,int height, DataSet data) {
    size_chart.width = width;
    size_chart.height = height;
    dataset = data;
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


    size_plot.width = (size_chart.width) - (margins.left + margins.right) - 60;
    size_plot.height = (size_chart.height) - (margins.top + margins.bottom) - (title.size.height);

    view_chart_memory = Simd::Allocator::Allocate(size_chart.width*size_chart.height*CHANNEL, 16);
    view_chart = View(size_chart.width, size_chart.height, FORMAT, view_chart_memory);
    Simd::Fill(view_chart,255);

    view_plot_memory = Simd::Allocator::Allocate(size_plot.width*size_plot.height*CHANNEL, 16);
    view_plot = View(size_plot.width, size_plot.height, FORMAT, view_plot_memory);
    Simd::Fill(view_plot,50);

    pos_plot.x = 60 + margins.left;
    pos_plot.y = margins.top + title.size.height;
    if(dataset.getLength() >= 2) {
        if(dataset.getLength<int>()) {
            Data<int>& temp =dataset.getDataByIndex<int>(0);
            Axis a(temp.id, &temp.values, Type::INT, Dock::LEFT, &size_plot);
            axis.push_back(a);
        }
    }
    return true;
}

void plot2D::render() {
    drw::Overlay(view_chart,pos_plot.x,pos_plot.y,view_plot);
    ITER(Axis, axis) {
        drw::Overlay(view_chart,pos_plot.x-(*iter).getWidth(),pos_plot.y, (*iter).getView());
    }
}

int plot2D::getWidth(){ return size_chart.width; }
int plot2D::getHeight(){return size_chart.height; }

const View& plot2D::getPlot() {
    return view_chart;
}

const uint8_t* plot2D::getBitmap() {
    return view_chart.data;
}

