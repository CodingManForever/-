#include<stdio.h>
#include<graphics.h>
/************************�ڶ�����Ŀ�ܹ�**************************/
//���ܻ��õ���ͷ�ļ�
//#include <iostream>
//#include <string>
//#include <vector>
//#include <graphics.h>	
//#include <conio.h>
//using namespace std;

/*******************ȫ�ֱ���*****************/
//#define MAX_N 1000000
//vector<string> str[1000000];	//���嶯̬�ַ�������
//int i = 0;

/*
�����ˣ�Master
���ֲ����Ļ���

//�������л����溯��
class Interface_Bace
{
private:
	��ʼ��һ���ַ�������String xxx;
	�ö����� �������ļ�����·��
public:
	void login_interface();		//��½����
	void opening_menu();		//��ʼ�˵�
	void Learning_module();		//����ѧϰģ��
	void Entertainment_module();//��������ģ��
	void Notepad();				//������±�
	void Todolist_Interface();	//�л�������水ť
	void Learning_clock();		//����ѧϰ��
	void Calculator_moudule();	//������ģ��  ������չ��

}interface;//ʵ����


//���ֲ����Ļ���
class Operation_Bace
{
private:
	��ʼ��һ��QFont
public:
	//������ҪQt��ʵ��
	int QTimer();				//��ʱ��ģ��
	String SetFont_Bold();		//��������Ӵ�
	String SetFont_Italic();	//��������б��
	String SetFont_Underline();	//���������»���



};
*/


/*******************������д�����еĸ�������*********************/
/*
����ѧϰģ��ĺ��� Learning_module
�����ˣ�twelve
��������
���أ���
	void Interface_Bace::Learning_module()
	{
		//��ʼ��������
		ExMessage ex = getmessage(EM_MOUSE);
		while(true)
		{
			if(���������==�ʼǱ�)
				���رʼǱ�ģ��
			if(���������==���±�)
				���ؼ��±�ģ��
			if(���������==ѧϰ��)
				����ѧϰ��ģ��
			if(���������==������)
				���ؼ�����ģ��
		}
	}
*/
/*
�����շ�Χ����
������:twelve
����һ����������(ΪɶҪ��һ�������������Լ���һ��ԭ��)
inline bool JudegView(short mouse_x,short mouse_y,int left,int top,int right,int bottom){
	if(���x����>=�������&&���x����<=�����Ҳ�&&���y����<=�²�&&���y����>=�ϲ�)
		������
	���� ���ؼ�
}
*/
inline bool JudegView(short mouse_x, short mouse_y, int left, int top, int right, int bottom) //�ж���������Ƿ��ڹ涨��Χ
{
	if (mouse_x >= (left) && mouse_x <= (right) && mouse_y >= (bottom) && mouse_y <= (top))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void button(int x, int y, int w, int h,const char* text)//��������
{
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(117, 249, 253));
	fillroundrect(x, y, x + w, y + h, 10, 10);
	//���崩͸ ������ɫ Բ�Ǿ���

	settextstyle(30, 0, "����");
	int tx = x + (w - textwidth(text))/ 2;
	int ty = y + (h - textheight(text))/ 2;
	outtextxy(tx, ty, text);
}
void Learning_module()//ѧϰģ�����
{
	//����ͼ��ʾ
	IMAGE img;
	loadimage(&img, "./ѧϰ���汳��ͼ.png", 700, 600);
	putimage(0, 0, &img);
	//������ʾ
	button(250, 150, 200, 50, "�ʼǱ�");
	button(250, 250, 200, 50, "���±�");
	button(250, 350, 200, 50, "ѧϰ��");
	button(250, 450, 200, 50, "������");
	//������
	while (true)
	{
		ExMessage msg;
		if (peekmessage(&msg, EM_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)//�����������
			{
				if (JudegView(msg.x, msg.y, 250, 150, 450, 200) == 1)
					notbook();
				if (JudegView(msg.x, msg.y, 250, 250, 450, 300) == 1)
					Notepad();
				if (JudegView(msg.x, msg.y, 250, 350, 450, 400) == 1)
					Learning_clock();
				if (JudegView(msg.x, msg.y, 250, 450, 450, 500) == 1)
					Calculator_moudule();
			}
		}
	}
}

//int main()//���Ժ���
//{
//	//��ʼ����������ʾ��
//	initgraph(700, 600, EW_SHOWCONSOLE);
//	//����ͼ��ʾ
//	IMAGE img;
//	loadimage(&img, "./ѧϰ���汳��ͼ.png", 700, 600);
//	putimage(0, 0, &img);
//	//������ʾ
//	button(250, 150, 200, 50, "�ʼǱ�");
//	button(250, 250, 200, 50, "���±�");
//	button(250, 350, 200, 50, "ѧϰ��");
//	button(250, 450, 200, 50, "������");
//	getchar();
//	return 0;
//}

