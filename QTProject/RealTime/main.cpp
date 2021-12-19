#include "mainwindow.h"
#include <QApplication>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <iostream>
#include "Simd/SimdLib.hpp"

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
    View view(300,300, View::Bgr24);
    for(int i = 0 ; i < 30000; i++) {
        view.data[i] = 0;
    }
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
