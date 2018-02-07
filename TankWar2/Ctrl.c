#include "Ctrl.h"
#include "Tank.h"
#include "View.h"
#include "Bullet.h"
#include "Doc.h"

/*设置窗口信息*/
void SetWindows()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleTitle(TEXT("TankWar"));//设置标题

	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);//设置光标大小

	SetConsoleMode(hIn, ENABLE_INSERT_MODE |
		ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);


	SMALL_RECT rect;
	rect.Left = 200;
	rect.Top = 25;
	rect.Bottom = 355;
	rect.Right = 520;
	SetConsoleWindowInfo(hOut, TRUE, &rect);

	system("mode con cols=150 lines=60");//设置窗口大小

}

/*初始化游戏*/
void InitGame()
{
	SetWindows();

	/*初始化地图*/

	for (int i = 0; i < MAPROW; ++i)//行
	{
		for (int j = 0; j < MAPCOL; ++j)//列
		{
			
			if ((i == 0) || (i == MAPROW - 1))
			{
				g_cMap[i][j] = MAP_WALL;
			}
			if ((j == 0) || (j == MAPCOL - 1))
			{
				g_cMap[i][j] = MAP_WALL;
			}
		}
	}


	/*初始化玩家坦克*/
	if (g_pTankArr != NULL)//指针不为空先释放资源
	{
		ReleaseAll();
	}
		g_pTankArr = (PTANK)malloc(sizeof(TANK)*MAXTANK);
	

	if (g_pTankArr == NULL)
	{
		Error("初始化坦克失败!");
		return;
	}

	strcpy_s(g_pTankArr[0].szName, 10, "Player");
	g_pTankArr[0].nBullet = MAXBULLET;
	g_pTankArr[0].nCam = BLUE;
	g_pTankArr[0].nDirect = UP;
	g_pTankArr[0].nIsVisible = 1;
	g_pTankArr[0].nX = 25;
	g_pTankArr[0].nY = 57;
	g_pTankArr[0].nLife = 100;
	g_pTankArr[0].nScore = 0;

	g_pTankArr[0].pBulletArr = (PBULLET)malloc(sizeof(BULLET)*MAXBULLET);

	if (g_pTankArr[0].pBulletArr == NULL)
	{
		Error("初始化子弹失败!");
		return;
	}

	/*初始化玩家的子弹*/
	for (int i = 0; i < MAXBULLET; ++i)
	{
		g_pTankArr[0].pBulletArr[i].nIsVisible = 0;
		g_pTankArr[0].pBulletArr[i].nCam = BLUE;
	}

	/*初始化电脑坦克*/
	for (int i = 1; i < MAXTANK; ++i)
	{
		sprintf_s(g_pTankArr[i].szName, 10, "NPC%2d", i);
		g_pTankArr[i].nBullet = MAXBULLET;
		g_pTankArr[i].nCam = RED;
		g_pTankArr[i].nDirect = DOWN;
		g_pTankArr[i].nIsVisible = 1;
		g_pTankArr[i].nX = (MAPCOL/MAXTANK)*i;
		g_pTankArr[i].nY = 2;
		g_pTankArr[i].nLife = 100;
		g_pTankArr[i].nScore = 0;

		g_pTankArr[i].pBulletArr = (PBULLET)malloc(sizeof(BULLET)*MAXBULLET);

		if (g_pTankArr[i].pBulletArr == NULL)
		{
			Error("初始化子弹失败!");
			return;
		}

		/*初始化每颗子弹*/
		for (int j = 0; j < MAXBULLET; ++j)
		{
			g_pTankArr[i].pBulletArr[j].nIsVisible = 0;
			g_pTankArr[i].pBulletArr[j].nCam = RED;
		}

	}
}

/*释放初始化时申请的堆空间*/
void ReleaseAll()
{
	/*逐个释放堆空间*/
	if (g_pTankArr != NULL)
	{
		for (int i = 0; i < MAXTANK; ++i)
		{
			if (g_pTankArr[i].pBulletArr != NULL)
				free(g_pTankArr[i].pBulletArr);

			g_pTankArr[i].pBulletArr = NULL;
		}

		free(g_pTankArr);
		g_pTankArr = NULL;
	}
}

/*消息循环体*/
void GameLoop() 
{
	srand((unsigned int)time(NULL));
	time_t respontime = clock(), bulletime = clock();
	time_t shotime = clock();
	time_t flushtime = clock(), keytime = clock();
	while (1)
	{

		if (clock() - respontime > 100)
		{

			if (KEYDOWN(0x41) || KEYDOWN(VK_LEFT))//A或←
			{
				if (clock() - keytime > 100)
				{
					DrawTank(g_pTankArr, 0, g_hOut, SZ_SPACE);
					TankMove(g_pTankArr, LEFT, 0);
					DrawTank(g_pTankArr, 0, g_hOut, SZ_TANK);
					keytime = clock();
					continue;
				}
			}
			if (KEYDOWN(0x44) || KEYDOWN(VK_RIGHT))//D或→
			{
				if (clock() - keytime > 100)
				{
					DrawTank(g_pTankArr, 0, g_hOut, SZ_SPACE);
					TankMove(g_pTankArr, RIGHT, 0);
					DrawTank(g_pTankArr, 0, g_hOut, SZ_TANK);
					keytime = clock();
					continue;
				}
			}
			if (KEYDOWN(0x53) || KEYDOWN(VK_DOWN))//S或↓
			{
				if (clock() - keytime > 100)
				{
					DrawTank(g_pTankArr, 0, g_hOut, SZ_SPACE);
					TankMove(g_pTankArr, DOWN, 0);
					DrawTank(g_pTankArr, 0, g_hOut, SZ_TANK);
					keytime = clock();
					continue;
				}
			}
			if (KEYDOWN(0x57) || KEYDOWN(VK_UP))//W或↑
			{
				if (clock() - keytime > 100)
				{
					DrawTank(g_pTankArr, 0, g_hOut, SZ_SPACE);
					TankMove(g_pTankArr, UP, 0);
					DrawTank(g_pTankArr, 0, g_hOut, SZ_TANK);
					keytime = clock();
					continue;
				}
			}
			if (KEYDOWN(VK_SPACE))//空格
			{
				if (clock() - shotime > 100)
				{
					TankShot(g_pTankArr, 0);
					shotime = clock();
				}
			}


			if (KEYDOWN(VK_ESCAPE))//Esc键返回主界面、退出
			{
				SaveFile();
				Sleep(1000);//暂停一下让人看清楚情况
				break;
			}


			DrawBullet(g_pTankArr, SZ_BULLET, g_hOut);

			DrawTankArr(g_pTankArr, SZ_SPACE, g_hOut);

			//敌方坦克随机走
			for (int i = 1, nDir = 0; i < MAXTANK; ++i)
			{
				if (g_pTankArr[i].nIsVisible == 1)
				{
					nDir = g_pTankArr[i].nDirect;
					if (!(rand() % 8))//八分一机会改变方向
						nDir = ((rand() % 4) + 1);

					TankMove(g_pTankArr, nDir, i);
				}
			}

			DrawTankArr(g_pTankArr, SZ_TANK, g_hOut);

			respontime = clock();
		}

		if (clock() - bulletime > 50)
		{
		
			DrawBullet(g_pTankArr, SZ_SPACE, g_hOut);

			BulletFly(g_pTankArr[0].pBulletArr, g_pTankArr, 0);

			//敌方坦克随机射击
			for (int i = 1; i < MAXTANK; ++i)
			{
				BulletFly(g_pTankArr[i].pBulletArr, g_pTankArr, i);
				if (g_pTankArr[i].nIsVisible==1)
				{
					if (!(rand() % 20))//二十分一机会射击
						TankShot(g_pTankArr, i);
				}
			}

			DrawBullet(g_pTankArr, SZ_BULLET, g_hOut);

			bulletime = clock();
		}

		if (clock()-flushtime>800)
		{
			DrawMap(g_hOut);
			DrawErrorBox(g_hOut);
			DrawRank(g_hOut);
			flushtime = clock();
		}
	}
}

/*显示游戏主菜单界面,返回用户选择*/
int MainMenu(HANDLE hOut)
{
	COORD loc;
	loc.X = MAPCOL - 7;
	loc.Y = MAPROW / 4;
	SetConsoleTextAttribute(hOut, 15);
	SetConsoleCursorPosition(hOut, loc);
	printf("欢迎进入坦克大战的世界！");
	loc.X = MAPCOL;
	loc.Y += 2;
	SetConsoleCursorPosition(hOut, loc);
	printf("开始游戏");
	loc.Y += 2;
	SetConsoleCursorPosition(hOut, loc);
	printf("继续游戏");
	loc.Y += 2;
	SetConsoleCursorPosition(hOut, loc);
	printf("编辑地图");
	loc.Y += 2;
	SetConsoleCursorPosition(hOut, loc);
	printf("退出游戏");

	int nChoice = -1;/*用户选择1为开始游戏，2为继续游戏，3为编辑地图，4为退出游戏*/
	time_t keytime = clock(), flushtime = clock();
	while (1)
	{
		if (KEYDOWN(0x53) || KEYDOWN(VK_DOWN))//S或↓
		{
			if (clock() - keytime > 200)
			{
				if (nChoice == -1)//用户第一次选择初始化为第一项
				{
					nChoice = 1;
					keytime = clock();
					continue;
				}

				nChoice += 1;
				if (nChoice > 4)
				{
					nChoice = 1;
					keytime = clock();
					continue;
				}
				keytime = clock();
				continue;
			}
		}
		if (KEYDOWN(0x57) || KEYDOWN(VK_UP))//W或↑
		{
			if (clock() - keytime > 200)
			{
				if (nChoice == -1)//用户第一次选择初始化为第一项
				{
					nChoice = 1;
					keytime = clock();
					continue;
				}

				nChoice -= 1;
				if (nChoice <= 0)
				{
					nChoice = 4;
					keytime = clock();
					continue;
				}
				keytime = clock();
				continue;
			}
		}
		if (KEYDOWN(VK_RETURN))
		{
			if (clock() - keytime > 400)
			{
				if (nChoice != -1)//用户未选择则不退出
					break;
				keytime = clock();
			}
		}

		if (clock() - flushtime > 400)
		{
			loc.X = MAPCOL;
			loc.Y = (MAPROW / 4) + 2;
			SetConsoleCursorPosition(hOut, loc);
			if (nChoice == 1)
			{
				SetConsoleTextAttribute(hOut, 16);
			}
			else
			{
				SetConsoleTextAttribute(hOut, 15);
			}
			printf("开始游戏");

			loc.Y += 2;
			SetConsoleCursorPosition(hOut, loc);
			if (nChoice == 2)
			{
				SetConsoleTextAttribute(hOut, 16);
			}
			else
			{
				SetConsoleTextAttribute(hOut, 15);
			}
			printf("继续游戏");

			loc.Y += 2;
			SetConsoleCursorPosition(hOut, loc);
			if (nChoice == 3)
			{
				SetConsoleTextAttribute(hOut, 16);
			}
			else
			{
				SetConsoleTextAttribute(hOut, 15);
			}
			printf("编辑地图");

			loc.Y += 2;
			SetConsoleCursorPosition(hOut, loc);
			if (nChoice == 4)
			{
				SetConsoleTextAttribute(hOut, 16);
			}
			else
			{
				SetConsoleTextAttribute(hOut, 15);
			}
			printf("退出游戏");

			SetConsoleTextAttribute(hOut, 15);

			flushtime = clock();
		}
	}

	system("cls");

	return nChoice;
}
