#include <graphics.h> 
#include <conio.h>
#include<stdio.h>
#include<easyx.h>
#include "Interface_Bace.h"
using namespace std;

void button(int x, int y, int w, int h, TCHAR* text)//��ť���ú���
{
    setbkmode(TRANSPARENT);
    setfillcolor(GREEN);
    fillroundrect(x, y, x + w, y + h, 10, 10);
    // ����ַ�����MBCS �ַ�����
    TCHAR s1[] = L"����";
    settextstyle(30, 0, s1);
    TCHAR s[50] = L"hello";

    int tx = x + (w - textwidth(text)) / 2;
    int ty = y + (h - textheight(text)) / 2;

    outtextxy(tx, ty, text);

}
void Interface_Bace::opening_menu()
{
    initgraph(640, 480);    // ������ͼ���ڣ���СΪ 640x480 ����
    IMAGE back_img;
    loadimage(&back_img, _T("�ļ�·��"), 640, 480, true);
    putimage(0, 0, &back_img);

    TCHAR s1[50] = L"����ģ��";
    TCHAR s2[50] = L"ѧϰģ��";
    TCHAR s3[50] = L"����";

    button(440, 150, 170, 50, s1);
    button(440, 250, 170, 50, s2);
    button(440, 350, 170, 50, s3);

    //������
    ExMessage msg;
    while (true) {
        if (peekmessage(&msg, EM_MOUSE)) {

            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x >= 440 && msg.x <= 440 + 170 && msg.y >= 150 && msg.y <= 150 + 50)//��������Ϊ:����+�����ϣ���+��
                {
                    //outtextxy(200, 200, s1);
                    Interface_Bace::Entertainment_module();//ҳ����ת��˵ʵ���Ҳ������ôʵ�֡�
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
    initgraph(640, 480);    // ������ͼ���ڣ���СΪ 640x480 ����
    IMAGE back_img;         // ��Ϸҳ���ͼƬ���о�����Ӧ�ÿ���
    loadimage(&back_img, _T("�ļ�·��"), 640, 480, true);
    putimage(0, 0, &back_img);

    //���ð�ť
    TCHAR s1[50] = L"����ģ��";
    TCHAR s2[50] = L"ѧϰģ��";

    button(240, 450, 170, 50, s1);
    button(440, 450, 170, 50, s2);

    //������
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