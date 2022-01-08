#include "mainwindow.h"
#include <QApplication>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <iostream>
#include "rtplot.h"
#include "drawingview.h"


typedef struct datas {
  int count;
  char str[20];
} datas;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Simd::Pixel::Bgr24 color(0,0,255);
    View view1 = View(200,200, FORMAT);
    Simd::Fill(view1,255);
    //drw::RenderText(view1,"Hello World!",10,100,20,color);

    View view2 = View(87,80, FORMAT);
    for(int i = 0 ; i < 87*80; i+=1)
    {
        view2.data[i*4] = 255;
        view2.data[i*4+1] = 0;
        view2.data[i*4+2] = 0;
        view2.data[i*4+3] = 255;
    }
    drw::Overlay(view1,150,50,view2);


    w.setImage(200 ,200, (uchar*) view1.data);

/*
    View view = View(300,300, FORMAT);
    Simd::Fill(view,255);
    //gly::TextRendering render = gly::TextRendering();
    Simd::Pixel::Bgr24 color(0,0,255);
    drw::RenderText(view,"Test Viewport",10,100,20,color);
    drw::DrawLine(view,0,0,300,300,5,color);
    drw::DrawCircle(view,150,150,140,color);
    w.setImage(view.width ,view.height, (uchar*) view.data);

*/
    /*
    rtplot plot(500, 400);
    w.setImage(plot.getWidth() ,plot.getHeight(), (uchar*) plot.getBitmap());
    */
/*
    plot.view = View(300, 300,300*4, FORMAT, ad);
    Simd::Fill(plot.view,255);
    drw::DrawLine(plot.view,0,0,300,300,5,color);
    w.setImage(plot.view.width ,plot.view.height, (uchar*) plot.view.data);
    */

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
