#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#define m 30
#define n 40

struct snake {          //控制蛇的结构体
	int x;
	int y;
	struct snake * before;
}*head, *s1, *s2, *tail;


int score = 0;
int food_x = 0, food_y = 0;             //全局可见的变量，分数与食物坐标

void HideCursor()   //隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void gotoxy(int x, int y) //调至指定位置
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

int main()
{
	void start(int);
	void paint(int);
	int speedup(int,int);
	char control(char,int,int*);
	int dead(int);
	void save(int);
	char mov;    //移动方向
	int speed;
	int choice;    //关卡选择
	int num;        //初始选择
	int again = 0;   //判断是否是第一次游戏

	system("title snakes eat eat!");
	system("color 0B");

	loop: //循环点
	while(1)
    {
        gotoxy(5,5);
        printf("WELCOME MY FRIEND!!!");
        gotoxy(5,6);
        printf("WHICH????");
        gotoxy(5,7);
        printf("1.start MY MICE!!\n     2.most mice\n     3.I don't like mouse...\n"     );

        scanf("%d",&num);
        system("cls");
        fflush(stdin);
        if(num==1||num==2||num==3)
        {
            break;
        }
    }
    if(num==1)
    {
        while(1)
        {
            gotoxy(5,5);
            printf("welcome to MY RICE!!!");
            gotoxy(5,6);
            printf("How hard do you want? 1 to 3.so:");

            scanf("%d",&choice);

            if(choice == 1||choice == 2||choice == 3)
                break;
                system("cls");
                fflush(stdin);
        }

        system("cls");

        switch (choice)
        {
            case 1:speed = 150;break;
            case 2:speed = 145;break;
            case 3:speed = 140;
            default:break;
        }

        start(choice);  //初始化数据与地图
        mov = 'a';
        score = 3;

        while (1)
        {
            HideCursor();
            mov = control(mov,choice,&again); //移动方向，关卡选择，是否为第一次

            if (!(score % 8)) //加速
            {
                speed = speedup(speed,choice);
            }

            paint(choice);  //根据关卡打印蛇
            if (dead(choice))    //判断是否死亡
            {
                break;
            }
            Sleep(speed);  //速度控制
        }
        save(choice);
        gotoxy(n + 5, 6);
        printf("you have a cat and ...where are the %d mice?\n",score);
        gotoxy(n + 5, 7);
        printf("good job! mice all over!! \n");
        _getch();
        gotoxy(n + 5, 8);
        system("cls");
        again = 1;
        goto loop;
    }
    else if(num==2)  //打印得分
    {
        FILE *p;
        int a,b,c;
        p=fopen("1.DAT","r");
        fscanf(p,"%d %d %d",&a,&b,&c);
        gotoxy(5,5);
        printf("level 1:%d %d %d",a,b,c);
        p=fopen("2.DAT","r");
        fscanf(p,"%d %d %d",&a,&b,&c);
        gotoxy(5,6);
        printf("level 2:%d %d %d",a,b,c);
        p=fopen("3.DAT","r");
        fscanf(p,"%d %d %d",&a,&b,&c);
        gotoxy(5,7);
        printf("level 3:%d %d %d",a,b,c);
        _getch();
        system("cls");
        goto loop;
    }
    else if(num==3);  //退出
    return 0;
}


void start(int choice)
{
	head = (struct snake *)malloc(sizeof(struct snake));
	s1 = (struct snake *)malloc(sizeof(struct snake));
	s2 = (struct snake *)malloc(sizeof(struct snake));
	head->x = n / 2;
	head->y = m / 2;
	head->before = NULL;
	s1->x = head->x + 1;
	s1->y = head->y;
	s1->before = head;
	s2->x = head->x + 2;
	s2->y = s1->y;
	s2->before = s1;
	tail = s2;
	s1 = NULL, s2 = NULL;  //初始化蛇体

	int i, j, k;   //地图障碍物初始化
	for (i = 0; i < m; i++)
	{
		j = 0, k = n - 1;
		gotoxy(j, i); printf("*");
		gotoxy(k, i); printf("*");
	}
	for (j = 0; j < n; j++)
	{
		i = 0, k = m - 1;
		gotoxy(j, i); printf("*");
		gotoxy(j, k); printf("*");
	}
	if(choice == 1);
	else if(choice == 2)
    {
        for(i = m/4,j = 3*m/4,k = 2*n/5; k < 3*n/5; k++)
        {
            gotoxy(k, i); printf("*");
            gotoxy(k, j); printf("*");
        }
    }
    else if(choice == 3)
    {
        int u = 7;
        j = u, k = n - u;
        for (i = u; i < m - u; i++)
        {
            if(i!=m/2&&i!=m/2-1&&i!=m/2+1)
            {
                gotoxy(j, i); printf("*");
                gotoxy(k, i); printf("*");
            }
        }
        i = u, k = m - u;
        for (j = u; j <= n - u; j++)
        {
            if(j!=n/2&&j!=1+n/2&&j!=n/2-1&&j!=2+n/2)
            {
                gotoxy(j, i); printf("*");
                gotoxy(j, k); printf("*");
            }
        }
    }
}

void paint(int choice)
{
	for (s1 = tail; s1 != head; s1 = s1->before)  //打印蛇身
	{
		gotoxy(s1->x, s1->y);
		printf("0");
	}

	gotoxy(head->x, head->y);  //打印蛇头
	printf("@");

	gotoxy(n + 5, 4);
	printf("now it is %d level ^@^", choice);
	gotoxy(n + 5, 6);
	printf("there are %d mice stealing your rice....", score);
	s1 = NULL;
}

char control(char once,int choice,int * again)
{
	static int flag = 0;  //是否按下任意键开始
	char key, s;
	int x0, y0;
	void food(int);
	static int ifeat = 1;  //是否吃到食物

	if(*again)  //是否是第一次游戏
    {
        *again = 0;
        ifeat = 1;
        flag = 0;
    }

	if (_kbhit())
	{
		s = _getch();
		if (s == 'a' || s == 's' || s == 'w' || s == 'd')
		{
			key = s;
			once = key;
		}
		flag = 1;
	}
	else key = once;  //蛇走的方向，asdw或上次方向

	if (flag)
	{
		x0 = tail->x, y0 = tail->y;       //蛇整体移动
		gotoxy(x0, y0);
		printf(" ");
		s1 = tail, s2 = tail->before;
		while (s2)
		{
			s1->x = s2->x, s1->y = s2->y;
			s2 = s2->before;
			s1 = s1->before;
		}
		s1 = NULL, s2 = NULL;

		switch (key)                 //蛇头移动
		{
		case 'w':head->y -= 1; break;
		case 's':head->y += 1; break;
		case 'a':head->x -= 1; break;
		case 'd':head->x += 1; break;
		default:break;
		}

		if (head->x == food_x && head->y == food_y)  //head是否与食物坐标重叠
		{
			ifeat = 1;
			s1 = (struct snake *)malloc(sizeof(struct snake));  //蛇身加长
			s1->x = x0, s1->y = y0, s1->before = tail;
			tail = s1;
			s1 = NULL;
			++score;
		}

		if (ifeat)  // 如果吃到了食物
		{
			food(choice);  //生成新的食物
			ifeat = 0;   //是否吃食物置为0
		}
	}
	return once;  //用于下一次移动时的方向
}

void food(int choice) //生成并打印食物
{
	int flag;
	int i,j,k;

	srand((unsigned)time(0));
	while (1)
	{
	    flag = 1;
		s1 = tail;
		food_x = 1 + rand() % (n - 3);
		food_y = 1 + rand() % (m - 3);  //食物坐标生成

		while (s1)  //食物坐标检查是否合适
		{
			if (food_x == s1->x&&food_y == s1->y)
			{
				flag = 0;
				break;
			}
			s1 = s1->before;
		}

		if (flag == 0)continue;

		if (choice == 1)break;
		else if (choice == 2)
        {
            for(i = m/4,j = 3*m/4,k = 2*n/5; k < 3*n/5; k++)
            {
                if(food_x == k&&food_y == i)
                {
                    flag = 0;
                    break;
                }
                else if(food_x == k&&food_y ==j)
                {
                    flag = 0;
                    break;
                }
            }
        }
        else if (choice == 3)
        {
            int u = 7;
            j = u, k = n - u;

            for (i = u,j = u,k = n - u; i < m - u; i++)
            {
                if(food_x == j&&food_y == i)
                {
                    flag = 0;
                    break;
                }
                else if(food_x == k&&food_y == i)
                {
                    flag = 0;
                    break;
                }
            }

            for (j = u,i = u, k = m - u; j <= n - u; j++)
            {
                if(food_x == j&&food_y == i)
                {
                    flag = 0;
                    break;
                }
                else if(food_x == j&&food_y == k)
                {
                    flag = 0;
                    break;
                }
            }
        }
		if (flag == 1)break;
	}

	gotoxy(food_x, food_y);
	printf("#");
}

int speedup(int speed,int choice)
{
    switch (choice)
    {
        case 1:
            {
                switch (score)
                {
                    case 8:speed = 140;break;
                    case 16:speed = 130;break;
                    case 24:speed = 120;
                    default:break;
                }
            }
            break;
        case 2:
            {
                switch (score)
                {
                    case 8:speed = 125;break;
                    case 16:speed = 105;break;
                    case 24:speed = 95;
                    default:break;
                }
            }
            break;
        case 3:
            {
                switch (score)
                {
                    case 8:speed = 120;break;
                    case 16:speed = 100;break;
                    case 24:speed = 80;
                    default:break;
                }
            }
        default:break;
    }
	return speed;
}

int dead(int choice)
{
        s1 = tail;
	int x0 = head->x, y0 = head->y;
	int i,k,j;

	while (s1 != head)//是否咬到自己
	{
		if (s1->x == x0 && s1->y == y0)
		{
			return 1;
		}
		s1 = s1->before;
	}

	if (head->x == 0 || head->y == 0 || head->x == n - 1 || head->y == m - 1)//是否撞墙
		return 1;

    if(choice == 2) //是否撞到障碍物及墙在2、3模式下
    {
        for(i = m/4,j = 3*m/4,k = 2*n/5; k < 3*n/5; k++)
        {
            if(head->x == k&&head->y == i)
            {
                return 1;
            }
            else if(head->x == k&&head->y ==j)
            {
                return 1;
            }
        }
    }
    else if(choice == 3)
    {
        int u = 7;
        j = u, k = n - u;
        for (i = u; i < m - u; i++)
        {
            if(i!=m/2&&i!=m/2-1&&i!=m/2+1)
            {
                if(head->x == j&&head->y == i)
                {
                    return 1;
                }
                else if(head->x == k&&head->y == i)
                {
                    return 1;
                }
            }
        }

        i = u, k = m - u;

        for (j = u; j <= n - u; j++)
        {
            if(j!=n/2-1&&j!=n/2&&j!=1+n/2&&j!=2+n/2)
            {
                if(head->x == j&&head->y == i)
                {
                    return 1;
                }
                else if(head->x == j&&head->y == k)
                {
                    return 1;
                }
            }
        }
    }
	return 0;
}
void save(int choice) //存储分数
{
    FILE *p;
    char s[7];

    switch (choice) //s用来保存文件名称
    {
    case 1:p=fopen("1.DAT","a+");strcpy(s,"1.DAT");break;
    case 2:p=fopen("2.DAT","a+");strcpy(s,"2.DAT");break;
    case 3:p=fopen("3.DAT","a+");strcpy(s,"3.DAT");
    }

    if(p)
    {
        int a,b,c;

        fscanf(p,"%d %d %d",&a,&b,&c);

        if(score>=a) //分数高写入记录
        {
            c=b,b=a,a=score;
        }
        else if(score>=b)
        {
            c=b,b=score;
        }
        else if(score>=c)
            c=score;

        fclose(p);

        p=fopen(s,"w");

        if(p) //写入新的文件
        {
            fprintf(p,"%d %d %d",a,b,c);
            fclose(p);
        }
    }
}
