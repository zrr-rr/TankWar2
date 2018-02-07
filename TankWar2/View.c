#include "View.h"

/*在指定位置用指定颜色打印指定字符*/
/*传入XY坐标、打印的字符、打印的颜色、控制台句柄*/
void DrawChar(int nX, int nY, char* pChar, WORD wArr, HANDLE hOutPut)
{
	SetConsoleTextAttribute(hOutPut, wArr);
	COORD loc;
	loc.X = nX * 2;
	loc.Y = nY;
	SetConsoleCursorPosition(hOutPut, loc);
	printf(pChar);
}

/*输出右上角错误显示框*/
void DrawErrorBox(HANDLE hOut)
{
	for (int i = MAPCOL-1; i < 75; ++i)
	{
		for (int j=MAPROW/4;j>=0;--j)
		{
			if (((i == MAPCOL-1) || (i == 74)) ||
				((j == MAPROW / 4) || (j == 0)))
			{
				DrawChar(i, j, SZ_WALL, 135, hOut);
			}
			else
			{
				DrawChar(i, j, SZ_SPACE, 0, hOut);
			}
		}
	}
}

/*在指定位置输出错误*/
void Error(char* szErr)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DrawErrorBox(hOut);
	SetConsoleTextAttribute(hOut, 15);
	COORD loc;
	loc.X = 120;
	loc.Y = 5;
	SetConsoleCursorPosition(hOut, loc);
	printf(szErr);
}

/*输出右下角排名*/
void DrawRank(HANDLE hOut)
{
	
	COORD loc;
	loc.X = 105;
	loc.Y = 18;

	SetConsoleTextAttribute(g_hOut, 15);

	SetConsoleCursorPosition(g_hOut, loc);
	printf(" Esc返回主菜单！！");
	loc.Y += 4;

	/*我方坦克图例*/
	DrawChar(loc.X / 2, loc.Y, SZ_TANK, 9, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":我方坦克！！ ");

	loc.X += 20;
	DrawChar(loc.X / 2, loc.Y, SZ_BULLET, 13, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":我方子弹！！ ");
	loc.X -= 4;
	loc.X -= 20;
	loc.X -= 4;

	loc.Y += 2;

	/*敌方坦克图例*/
	DrawChar(loc.X / 2, loc.Y, SZ_TANK, 12, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":敌方坦克！！ ");

	loc.X += 20;
	DrawChar(loc.X / 2, loc.Y, SZ_BULLET, 14, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":敌方子弹！！ ");
	loc.X -= 4;
	loc.X -= 20;
	loc.X -= 4;

	loc.Y += 2;

	/*箱子图例*/
	DrawChar(loc.X / 2, loc.Y, SZ_BOX, 14, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":箱子可击烂！！");
	loc.X -= 4;
	loc.Y += 2;

	/*箱子图例*/
	DrawChar(loc.X / 2, loc.Y, SZ_WALL, 135, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":围墙击不烂！！");
	loc.X -= 4;
	

	SetConsoleTextAttribute(g_hOut, 15);

	for (int i = 0; i < MAXTANK; ++i)
	{
		SetConsoleTextAttribute(hOut, 15);
		if (g_pTankArr[i].nIsVisible==0)
		{
			SetConsoleTextAttribute(hOut, 28);
		}
		loc.Y += 2;
		SetConsoleCursorPosition(hOut, loc);
		
		printf("%s : 得分:%3d 生命值:%3d\n", g_pTankArr[i].szName,
			g_pTankArr[i].nScore, g_pTankArr[i].nLife);
	}
	//寻找未死的电脑
	int Tmp=1;
	while (g_pTankArr[Tmp].nIsVisible != 1&&Tmp<MAXTANK)
		++Tmp;

	if (Tmp==MAXTANK)//电脑死光了
	{
		SetConsoleTextAttribute(hOut, 156);
		loc.Y += 2;
		SetConsoleCursorPosition(hOut, loc);
		printf("！！！！！您赢了！！！！！\n");
	}
	else
	{
		if (g_pTankArr[0].nLife <= 0)//玩家死了
		{
			SetConsoleTextAttribute(hOut, 192);
			loc.Y += 2;
			SetConsoleCursorPosition(hOut, loc);
			printf("！！！！！您输了！！！！！\n");
		}
	}

	SetConsoleTextAttribute(hOut, 15);
}

/*输出右下角排名显示框*/
void DrawRankMenu(HANDLE hOut)
{
	for (int i = MAPCOL - 1; i < 75; ++i)
	{
		for (int j = MAPROW / 4; j < MAPROW; ++j)
		{
			if (((i == MAPCOL - 1) || (i == 74)) ||
				((j == MAPROW-1) || (j == MAPROW / 4)))
			{
				DrawChar(i, j, SZ_WALL, 135, hOut);
			}
			else
			{
				DrawChar(i, j, SZ_SPACE, 0, hOut);
			}
		}
	}
	
	DrawRank(hOut);
}


/*打印地图，传入控制台句柄*/
void DrawMap(HANDLE hOutPut)
{
	/*打印地图*/
	for (int i = 0; i < MAPROW; ++i)//行
	{
		for (int j = 0; j < MAPCOL; ++j)//列
		{
			switch (g_cMap[i][j])
			{
			case MAP_WALL:
				DrawChar(j, i, SZ_WALL, 135, hOutPut);
				break;
			case MAP_GRASS:
				DrawChar(j, i, SZ_GRASS, 10, hOutPut);
				break;
			case MAP_RIVER:
				DrawChar(j, i, SZ_RIVER, 11, hOutPut);
				break;
			case MAP_BOX:
				DrawChar(j, i, SZ_BOX, 14, hOutPut);
				break;
			default:
				break;
			}
		}
	}

}

/*传入坦克数组指针、坦克属于的元素序列、控制台句柄、要打印的字符形状*/
void DrawTank(PTANK pTankArr,int nNum,HANDLE hOutPut,char* pChar)
{

	/*设置坦克颜色*/
	WORD wArr = 0;
	if (pTankArr[nNum].nCam == BLUE)//本阵营
	{
		wArr = 9;
	}
	else//敌对阵营
	{
		wArr = 12;
	}

	/*根据方向打印坦克*/
	switch (pTankArr[nNum].nDirect)
	{
	default:
		break;
	case UP:
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY - 1,
			pChar, wArr, hOutPut);//头
		DrawChar(pTankArr[nNum].nX - 1, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//左翼
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//中心
		DrawChar(pTankArr[nNum].nX + 1, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//右翼
		DrawChar(pTankArr[nNum].nX - 1, pTankArr[nNum].nY + 1,
			pChar, wArr, hOutPut);//左尾
		DrawChar(pTankArr[nNum].nX + 1, pTankArr[nNum].nY + 1,
			pChar, wArr, hOutPut);//右尾
		break;
	case DOWN:
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY + 1,
			pChar, wArr, hOutPut);//头
		DrawChar(pTankArr[nNum].nX - 1, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//左翼
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//中心
		DrawChar(pTankArr[nNum].nX + 1, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//右翼
		DrawChar(pTankArr[nNum].nX - 1, pTankArr[nNum].nY - 1,
			pChar, wArr, hOutPut);//左尾
		DrawChar(pTankArr[nNum].nX + 1, pTankArr[nNum].nY - 1,
			pChar, wArr, hOutPut);//右尾
		break;
	case LEFT:
		DrawChar(pTankArr[nNum].nX - 1, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//头
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY + 1,
			pChar, wArr, hOutPut);//左翼
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//中心
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY - 1,
			pChar, wArr, hOutPut);//右翼
		DrawChar(pTankArr[nNum].nX + 1, pTankArr[nNum].nY + 1,
			pChar, wArr, hOutPut);//左尾
		DrawChar(pTankArr[nNum].nX + 1, pTankArr[nNum].nY - 1,
			pChar, wArr, hOutPut);//右尾
		break;
	case RIGHT:
		DrawChar(pTankArr[nNum].nX + 1, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//头
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY - 1,
			pChar, wArr, hOutPut);//左翼
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//中心
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY + 1,
			pChar, wArr, hOutPut);//右翼
		DrawChar(pTankArr[nNum].nX - 1, pTankArr[nNum].nY - 1,
			pChar, wArr, hOutPut);//左尾
		DrawChar(pTankArr[nNum].nX - 1, pTankArr[nNum].nY + 1,
			pChar, wArr, hOutPut);//右尾
		break;
	}

}

/*传入坦克数组指针、要打印的字符串、控制台句柄，该函数将打印全部可见的子弹*/
void DrawBullet(PTANK pTankArr,char* pChar,HANDLE hOutPut)
{
	
	WORD wArr;

	/*打印下属全部可见的子弹*/

	for (int i = 0; i < MAXTANK; ++i)
	{
		/*设置子弹颜色*/
		if (pTankArr[i].nCam == BLUE)//本阵营
		{
			wArr = 13;
		}
		else//敌对阵营
		{
			wArr = 14;
		}

		for (int j = 0; j < MAXBULLET; ++j)
		{
			if (pTankArr[i].pBulletArr[j].nIsVisible)
			{
				DrawChar(pTankArr[i].pBulletArr[j].nX,
					pTankArr[i].pBulletArr[j].nY, pChar, wArr, hOutPut);
			}
		}
	}

}

/*传入坦克数组指针、要打印的字符串、控制台句柄，该函数将打印该数组全部可见的坦克*/
void DrawTankArr(PTANK pTankArr, char* pChar,HANDLE hOutPut)
{
	/*打印坦克*/
	for (int i = 0; i < MAXTANK; ++i)
	{
		if (!pTankArr[i].nIsVisible)//不可见的坦克跳过生成
			continue;

		DrawTank(pTankArr,i,hOutPut,pChar);
	}
}

