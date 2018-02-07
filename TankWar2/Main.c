#include "Data.h"
#include"Ctrl.h"
#include"View.h"
#include "Doc.h"
#include "Map.h"



int main()
{
	g_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	g_hIn = GetStdHandle(STD_INPUT_HANDLE);

	int nChoice = -1, nExit = 1;
	while (nExit)
	{
		SetWindows();
		nChoice = MainMenu(g_hOut);
		//根据用户选择进行相关操作
		switch (nChoice)
		{
		default:
			break;
		case 1:
			InitGame();//创建新游戏
			DrawMap(g_hOut);
			DrawRankMenu(g_hOut);
			DrawTankArr(g_pTankArr, SZ_TANK, g_hOut);
			DrawBullet(g_pTankArr, SZ_BULLET, g_hOut);
			DrawErrorBox(g_hOut);
			GameLoop();
			ReleaseAll();
			break;
		case 2:
			InitGame();//加载游戏
			LoadFile();
			DrawMap(g_hOut);
			DrawRankMenu(g_hOut);
			DrawTankArr(g_pTankArr, SZ_TANK, g_hOut);
			DrawBullet(g_pTankArr, SZ_BULLET, g_hOut);
			Sleep(1000);//挂起一下缓解闪退感
			DrawErrorBox(g_hOut);
			GameLoop();
			ReleaseAll();
			break;
		case 3:
			InitGame();//创捷新游戏
			DrawMap(g_hOut);
			DrawTankArr(g_pTankArr, SZ_TANK, g_hOut);
			DrawErrorBox(g_hOut);
			MapRankMenu();
			MapEditLoop();
			ReleaseAll();
			break;
		case 4:
			nExit = 0;
			Sleep(800);//挂起一下缓解闪退感
			break;
		}

		SetConsoleTextAttribute(g_hOut, 15);
		system("cls");
	
		

	}
	ReleaseAll();
	return 0;
}