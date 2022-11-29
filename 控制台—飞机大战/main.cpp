#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define HEIGHT 25   //设置游戏边框
#define WIDTH 50

#define ENEMY_MAX 10//敌机数量

enum Option			
{
	EXIT,
	PLAY,
	GUIDE,
};

enum Condition      //表示游戏幕布上的情况
{
	backspace,
	enemy,
	bullet,
};

int canvas[HEIGHT][WIDTH]; //游戏幕布存储对应的信息
int score;
int x, y;				   //飞机头部坐标
int Std_Speed;		       //敌机标准下落速度
int Std_Time;		       //敌机生成的标准速度
int HP;                    //玩家生命值
int enemy_num;
int times;

void gotoxy(int x, int y)				//清屏函数
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor()					   //光标隐藏函数
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Initgame()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)		//将幕布上先初始化为空格
			canvas[i][j] = backspace;
	}
	HP = 3;
	score = 0;
	x = WIDTH / 2;							//初始化飞机位置
	y = HEIGHT / 2;
	enemy_num = 0;
	Std_Speed = 60;
	Std_Time = 60;
}

void show()
{
	gotoxy(0, 0);
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (i == y && j == x)			//打印飞机
				printf("*");
			else if (i == y + 1 && j == x - 2)
			{
				printf("*****");
				j += 4;
			}
			else if (i == y + 2 && j == x - 1)
			{
				printf("* *");
				j += 2;
			}
			else if (canvas[i][j] == bullet)	// 打印子弹
				printf("|");
			else if (canvas[i][j] == enemy)
				printf("@");
			else
				printf(" ");
		}
		printf("|\n");	//打印游戏边框
	}
	for (int j = 0; j < WIDTH; j++)   //打印游戏边框
		printf("-");
	printf("\n[得分:>%d\n", score);	  //打印游戏分数和血量
	printf("[生命值:>%d\n", HP);
}


int updateWithinput()
{
	if (_kbhit())
	{
		int input = _getch();
		switch (input)
		{
		case 'w': if (y > 0)			//防止飞机飞出游戏边界
			y--;
			break;
		case 's': if (y < HEIGHT - 3)
			y++;
			break;
		case 'a': if (x > 2)
			x--;
			break;
		case 'd': if (x < WIDTH - 3)
			x++;
			break;
		case 27: system("pause"); break;	//ESC的ascll码值为27
		case ' ': if (y > 0)
			canvas[y - 1][x] = bullet;
			break;
		case 'q': return 1;					//退出游戏
		}
	}
	return 0;
}

int enemy_update()
{
	static int enemy_speed = 0;
	static int enemy_time = 0;
	int flag = 0;
	if (enemy_speed < Std_Speed)				//依靠循环来控制更新速度
		enemy_speed++;


	if (enemy_time < Std_Time)
		enemy_time++;

	if (enemy_num < ENEMY_MAX && enemy_time >= Std_Time)
	{
		int i, j;
		do
		{
			i = rand() % (HEIGHT / 5);
			j = rand() % (WIDTH - 4) + 2;		//j的范围:[2, width - 3]
		} while (canvas[i][j] != backspace);
		canvas[i][j] = enemy;
		enemy_num++;
		enemy_time = 0;
	}

	if (enemy_speed >= Std_Speed)
	{
		flag = 1;
		enemy_speed = 0;
	}

	for (int i = HEIGHT - 1; i >= 0; i--)
	{
		for (int j = WIDTH - 1; j >= 0; j--)
		{
			if (canvas[i][j] == enemy)			//遇到敌机的情况
			{
				if (i == HEIGHT - 1)			//敌机飞到边界
				{
					score--;
					HP--;
					if (HP == 0)
						return 1;
					enemy_num--;
					canvas[i][j] = backspace;
				}
				else if (i < HEIGHT - 1 && canvas[i + 1][j] == bullet)//检测是否被子弹击中
				{
					score++;
					printf("\a");
					enemy_num--;
					if (score % 5 == 0 && Std_Speed >= 12) //分数到达一定程度后下落加快,生成加快
					{
						Std_Speed -= 3;			//下落加快
						Std_Time -= 3;			//生成速度加快
					}
					canvas[i][j] = backspace;
				}
				else if (flag)					//flag为1更新敌机位置
				{
					canvas[i + 1][j] = enemy;
					canvas[i][j] = backspace;
				}

			}
		}

	}

	return 0;
}


void bullet_update()
{
	for (int i = 0; i < HEIGHT; i++)			//控制子弹的移动
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (canvas[i][j] == bullet)
			{
				if (i > 0 && canvas[i - 1][j] == enemy)
				{
					score++;
					printf("\a");
					enemy_num--;
					if (score % 5 == 0 && Std_Speed >= 6) //分数到达一定程度后下落加快,生成加快
					{
						Std_Speed -= 3;			//下落加快
						Std_Time -= 3;			//生成速度加快
					}
					canvas[i - 1][j] = bullet;
				}
				else if (i > 0)
					canvas[i - 1][j] = bullet;
				canvas[i][j] = backspace;
			}
		}
	}
}

void gamebody()
{
	system("cls");
	Initgame();
	HideCursor();
	srand((unsigned int)time(NULL));
	while (1)
	{
		show();
		bullet_update();
		if (updateWithinput() || enemy_update())
		{
			show();
			printf("[本次游戏结束:>");
			system("pause");
			break;
		}
	}
}


void menu()
{
	printf("*****************\n");
	printf("**  飞机游戏   **\n");
	printf("**-------------**\n");
	printf("**   1.PLAY    **\n");
	printf("**   2.GUIDE   **\n");
	printf("**   0.EXIT    **\n");
	printf("*****************\n");
}

void guide()
{
	printf("******************\n");
	printf("** 游戏操作指南 **\n");
	printf("**--------------**\n");
	printf("**    w->上移   **\n");
	printf("**    s->下移   **\n");
	printf("**    a->左移   **\n");
	printf("**    d->右移   **\n");
	printf("**    q->返回   **\n");
	printf("**   ESC->暂停  **\n");
	printf("**   空格->射击 **\n");
	printf("******************\n\n\n");
}

int main()
{
	int input = 0;
	do
	{
		menu();
		printf("[请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case PLAY: gamebody(); break;
		case GUIDE: guide(); break;
		case EXIT: printf("成功退出游戏！\n"); break;
		default: printf("输入错误，请重新选择\n");
		}
	} while (input);
	return 0;
}
