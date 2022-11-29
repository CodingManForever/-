#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define HEIGHT 25   //������Ϸ�߿�
#define WIDTH 50

#define ENEMY_MAX 10//�л�����

enum Option			
{
	EXIT,
	PLAY,
	GUIDE,
};

enum Condition      //��ʾ��ϷĻ���ϵ����
{
	backspace,
	enemy,
	bullet,
};

int canvas[HEIGHT][WIDTH]; //��ϷĻ���洢��Ӧ����Ϣ
int score;
int x, y;				   //�ɻ�ͷ������
int Std_Speed;		       //�л���׼�����ٶ�
int Std_Time;		       //�л����ɵı�׼�ٶ�
int HP;                    //�������ֵ
int enemy_num;
int times;

void gotoxy(int x, int y)				//��������
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor()					   //������غ���
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Initgame()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)		//��Ļ�����ȳ�ʼ��Ϊ�ո�
			canvas[i][j] = backspace;
	}
	HP = 3;
	score = 0;
	x = WIDTH / 2;							//��ʼ���ɻ�λ��
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
			if (i == y && j == x)			//��ӡ�ɻ�
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
			else if (canvas[i][j] == bullet)	// ��ӡ�ӵ�
				printf("|");
			else if (canvas[i][j] == enemy)
				printf("@");
			else
				printf(" ");
		}
		printf("|\n");	//��ӡ��Ϸ�߿�
	}
	for (int j = 0; j < WIDTH; j++)   //��ӡ��Ϸ�߿�
		printf("-");
	printf("\n[�÷�:>%d\n", score);	  //��ӡ��Ϸ������Ѫ��
	printf("[����ֵ:>%d\n", HP);
}


int updateWithinput()
{
	if (_kbhit())
	{
		int input = _getch();
		switch (input)
		{
		case 'w': if (y > 0)			//��ֹ�ɻ��ɳ���Ϸ�߽�
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
		case 27: system("pause"); break;	//ESC��ascll��ֵΪ27
		case ' ': if (y > 0)
			canvas[y - 1][x] = bullet;
			break;
		case 'q': return 1;					//�˳���Ϸ
		}
	}
	return 0;
}

int enemy_update()
{
	static int enemy_speed = 0;
	static int enemy_time = 0;
	int flag = 0;
	if (enemy_speed < Std_Speed)				//����ѭ�������Ƹ����ٶ�
		enemy_speed++;


	if (enemy_time < Std_Time)
		enemy_time++;

	if (enemy_num < ENEMY_MAX && enemy_time >= Std_Time)
	{
		int i, j;
		do
		{
			i = rand() % (HEIGHT / 5);
			j = rand() % (WIDTH - 4) + 2;		//j�ķ�Χ:[2, width - 3]
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
			if (canvas[i][j] == enemy)			//�����л������
			{
				if (i == HEIGHT - 1)			//�л��ɵ��߽�
				{
					score--;
					HP--;
					if (HP == 0)
						return 1;
					enemy_num--;
					canvas[i][j] = backspace;
				}
				else if (i < HEIGHT - 1 && canvas[i + 1][j] == bullet)//����Ƿ��ӵ�����
				{
					score++;
					printf("\a");
					enemy_num--;
					if (score % 5 == 0 && Std_Speed >= 12) //��������һ���̶Ⱥ�����ӿ�,���ɼӿ�
					{
						Std_Speed -= 3;			//����ӿ�
						Std_Time -= 3;			//�����ٶȼӿ�
					}
					canvas[i][j] = backspace;
				}
				else if (flag)					//flagΪ1���µл�λ��
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
	for (int i = 0; i < HEIGHT; i++)			//�����ӵ����ƶ�
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
					if (score % 5 == 0 && Std_Speed >= 6) //��������һ���̶Ⱥ�����ӿ�,���ɼӿ�
					{
						Std_Speed -= 3;			//����ӿ�
						Std_Time -= 3;			//�����ٶȼӿ�
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
			printf("[������Ϸ����:>");
			system("pause");
			break;
		}
	}
}


void menu()
{
	printf("*****************\n");
	printf("**  �ɻ���Ϸ   **\n");
	printf("**-------------**\n");
	printf("**   1.PLAY    **\n");
	printf("**   2.GUIDE   **\n");
	printf("**   0.EXIT    **\n");
	printf("*****************\n");
}

void guide()
{
	printf("******************\n");
	printf("** ��Ϸ����ָ�� **\n");
	printf("**--------------**\n");
	printf("**    w->����   **\n");
	printf("**    s->����   **\n");
	printf("**    a->����   **\n");
	printf("**    d->����   **\n");
	printf("**    q->����   **\n");
	printf("**   ESC->��ͣ  **\n");
	printf("**   �ո�->��� **\n");
	printf("******************\n\n\n");
}

int main()
{
	int input = 0;
	do
	{
		menu();
		printf("[��ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
		case PLAY: gamebody(); break;
		case GUIDE: guide(); break;
		case EXIT: printf("�ɹ��˳���Ϸ��\n"); break;
		default: printf("�������������ѡ��\n");
		}
	} while (input);
	return 0;
}
