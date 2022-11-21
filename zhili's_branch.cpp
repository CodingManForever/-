#include <graphics.h> 
#include <conio.h>
#include<stdio.h>
#include<easyx.h>
#include "Interface_Bace.h"
using namespace std;

void button(int x, int y, int w, int h, TCHAR* text)//按钮设置函数
{
    setbkmode(TRANSPARENT);
    setfillcolor(GREEN);
    fillroundrect(x, y, x + w, y + h, 10, 10);
    // 输出字符串（MBCS 字符集）
    TCHAR s1[] = L"黑体";
    settextstyle(30, 0, s1);
    TCHAR s[50] = L"hello";

    int tx = x + (w - textwidth(text)) / 2;
    int ty = y + (h - textheight(text)) / 2;

    outtextxy(tx, ty, text);

}
void Interface_Bace::opening_menu()
{
    initgraph(640, 480);    // 创建绘图窗口，大小为 640x480 像素
    IMAGE back_img;
    loadimage(&back_img, _T("文件路径"), 640, 480, true);
    putimage(0, 0, &back_img);

    TCHAR s1[50] = L"娱乐模块";
    TCHAR s2[50] = L"学习模块";
    TCHAR s3[50] = L"返回";

    button(440, 150, 170, 50, s1);
    button(440, 250, 170, 50, s2);
    button(440, 350, 170, 50, s3);

    //鼠标操作
    ExMessage msg;
    while (true) {
        if (peekmessage(&msg, EM_MOUSE)) {

            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x >= 440 && msg.x <= 440 + 170 && msg.y >= 150 && msg.y <= 150 + 50)//数据依次为:左，左+长，上，上+宽
                {
                    //outtextxy(200, 200, s1);
                    Interface_Bace::Entertainment_module();//页面跳转，说实话我不清楚怎么实现。
                }
                if (msg.x >= 440 && msg.x <= 440 + 170 && msg.y >= 250 && msg.y <= 250 + 50)
                {
                    //outtextxy(200, 200, s2);
                    Interface_Bace::Learning_module();
                }
                if (msg.x >= 440 && msg.x <= 440 + 170 && msg.y >= 350 && msg.y <= 350 + 50)
                {
                    //outtextxy(200, 200, s3);
                    Interface_Bace::login_interface();
                }
                break;
            default:
                break;
            }
        }
    }
    return;
}

void Entertainment_module()
{
    initgraph(640, 480);    // 创建绘图窗口，大小为 640x480 像素
    IMAGE back_img;         // 游戏页面的图片，感觉截屏应该可以
    loadimage(&back_img, _T("文件路径"), 640, 480, true);
    putimage(0, 0, &back_img);

    //设置按钮
    TCHAR s1[50] = L"娱乐模块";
    TCHAR s2[50] = L"学习模块";

    button(240, 450, 170, 50, s1);
    button(440, 450, 170, 50, s2);

    //鼠标操作
    ExMessage msg;
    while (true) {
        if (peekmessage(&msg, EM_MOUSE)) {

            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x >= 240 && msg.x <= 240 + 170 && msg.y >= 450 && msg.y <= 450 + 50)
                    firstgame();
                if (msg.x >= 440 && msg.x <= 440 + 170 && msg.y >= 450 && msg.y <= 450 + 50)
                    secondgame();
                break;
            default:
                break;
            }
        }
    }
    return;
}