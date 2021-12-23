#include "mainwindow.h"
#include <QApplication>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <iostream>
#include "Simd/SimdLib.hpp"
#include "drawingview.h"

#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct datas {
  int count;
  char str[20];
} datas;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    typedef Simd::View<Simd::Allocator> View;

    View view(300,300, View::Bgra32);
    Simd::Fill(view,255);

    //gly::TextRendering render = gly::TextRendering();
    Simd::Pixel::Bgr24 color(0,0,0);
    drw::RenderText(view,"Test Viewport",10,100,20,color);


    w.setImage(view.width ,view.height, (uchar*) view.data);
    /*
    int shmid;
    datas *d;
    key_t key = 987654;
    void *memory_segment = NULL;

    if ((shmid = shmget(key, sizeof(datas), IPC_CREAT | 0666)) == -1)
    {
        printf("shmget failed\n");
        exit(0);
    }

    if ((memory_segment = shmat(shmid, NULL, 0)) == (void *)-1)
    {
        printf("shmat failed\n");
        exit(0);
    }

    d = (struct datas *)memory_segment;
    std::cout << "value : " << (*d).count << " & text : " << (*d).str << std::endl ;
    w.setLabel("aaa");
    */
    return a.exec();
}
