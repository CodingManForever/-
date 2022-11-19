#include<stdio.h>
#include<graphics.h>
/************************第二次项目架构**************************/
//可能会用到的头文件
//#include <iostream>
//#include <string>
//#include <vector>
//#include <graphics.h>	
//#include <conio.h>
//using namespace std;

/*******************全局变量*****************/
//#define MAX_N 1000000
//vector<string> str[1000000];	//定义动态字符串数组
//int i = 0;

/*
负责人：Master
各种操作的基类

//以下是切换界面函数
class Interface_Bace
{
private:
	初始化一个字符串对象String xxx;
	该对象定义 来定义文件所在路径
public:
	void login_interface();		//登陆界面
	void opening_menu();		//开始菜单
	void Learning_module();		//进入学习模块
	void Entertainment_module();//进入娱乐模块
	void Notepad();				//进入记事本
	void Todolist_Interface();	//切换待办界面按钮
	void Learning_clock();		//进入学习钟
	void Calculator_moudule();	//计算器模块  （算拓展）

}interface;//实例化


//文字操作的基类
class Operation_Bace
{
private:
	初始化一个QFont
public:
	//以下需要Qt来实现
	int QTimer();				//计时器模块
	String SetFont_Bold();		//设置字体加粗
	String SetFont_Italic();	//设置字体斜体
	String SetFont_Underline();	//设置字体下划线



};
*/


/*******************以下重写基类中的各个函数*********************/
/*
加载学习模块的函数 Learning_module
负责人：twelve
参数：无
返回：无
	void Interface_Bace::Learning_module()
	{
		//初始化鼠标对象
		ExMessage ex = getmessage(EM_MOUSE);
		while(true)
		{
			if(鼠标左键点击==笔记本)
				返回笔记本模块
			if(鼠标左键点击==记事本)
				返回记事本模块
			if(鼠标左键点击==学习钟)
				返回学习钟模块
			if(鼠标左键点击==计算器)
				返回计算器模块
		}
	}
*/
/*
鼠标接收范围函数
负责人:twelve
定义一个内联函数(为啥要用一个内联函数，自己查一下原因)
inline bool JudegView(short mouse_x,short mouse_y,int left,int top,int right,int bottom){
	if(鼠标x坐标>=矩形左侧&&鼠标x坐标<=矩形右侧&&鼠标y坐标<=下侧&&鼠标y坐标>=上侧)
		返回真
	否则 返回假
}
*/
inline bool JudegView(short mouse_x, short mouse_y, int left, int top, int right, int bottom) //判断鼠标坐标是否在规定范围
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
void button(int x, int y, int w, int h,const char* text)//创建按键
{
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(117, 249, 253));
	fillroundrect(x, y, x + w, y + h, 10, 10);
	//字体穿透 天蓝底色 圆角矩形

	settextstyle(30, 0, "黑体");
	int tx = x + (w - textwidth(text))/ 2;
	int ty = y + (h - textheight(text))/ 2;
	outtextxy(tx, ty, text);
}
void Learning_module()//学习模块界面
{
	//背景图显示
	IMAGE img;
	loadimage(&img, "./学习界面背景图.png", 700, 600);
	putimage(0, 0, &img);
	//按键显示
	button(250, 150, 200, 50, "笔记本");
	button(250, 250, 200, 50, "记事本");
	button(250, 350, 200, 50, "学习钟");
	button(250, 450, 200, 50, "计算器");
	//鼠标监听
	while (true)
	{
		ExMessage msg;
		if (peekmessage(&msg, EM_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN)//如果鼠标点击左键
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

//int main()//调试函数
//{
//	//初始化（测试显示）
//	initgraph(700, 600, EW_SHOWCONSOLE);
//	//背景图显示
//	IMAGE img;
//	loadimage(&img, "./学习界面背景图.png", 700, 600);
//	putimage(0, 0, &img);
//	//按键显示
//	button(250, 150, 200, 50, "笔记本");
//	button(250, 250, 200, 50, "记事本");
//	button(250, 350, 200, 50, "学习钟");
//	button(250, 450, 200, 50, "计算器");
//	getchar();
//	return 0;
//}

