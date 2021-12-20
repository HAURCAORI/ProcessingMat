#include "mainwindow.h"
#include <QApplication>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <iostream>
#include "Simd/SimdLib.hpp"


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
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return false;
    }

    FT_Face face;
    if (FT_New_Face(ft, "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return false;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);


    {
        unsigned char c = 60;
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER | FT_LOAD_MONOCHROME ))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        }
        // generate texture
        View view(face->glyph->bitmap.width,face->glyph->bitmap.rows, View::Bgra32);
        view.data = face->glyph->bitmap.buffer;
        w.setImage(view.width ,view.height, (uchar*) view.data);
    }

/*
    typedef Simd::View<Simd::Allocator> View;
    View view(300,300, View::Bgr24);
    for(int i = 0 ; i < 30000; i++) {
        view.data[i] = 0;
    }
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
