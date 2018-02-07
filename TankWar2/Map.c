#include "Map.h"
#include "View.h"
#include "Tank.h"
#include "Doc.h"

/*在标题处输出鼠标的X坐标，Y坐标*/
void OutPutPos(int nX, int nY)
{
	char szBuf[60] = { 0 };
	sprintf_s(szBuf, sizeof(szBuf), 
		"原始坐标 x=%3d , y=%3d  画图坐标  x=%3d , y=%3d ",
		nX, nY, nX/2, nY);
	SetConsoleTitleA(szBuf);
}

/*响应鼠标消息的函数，只在编辑状态下被调用*/
void OnMouse(MOUSE_EVENT_RECORD mer)
{
	switch (mer.dwEventFlags)
	{
	default:
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//左击
		{
			/*判断是否在地图框架内*/
			if (mer.dwMousePosition.X < (MAPCOL - 1) * 2 && mer.dwMousePosition.X>1)
			{
				if (mer.dwMousePosition.Y < MAPROW - 1 && mer.dwMousePosition.Y>0)
				{
					/*判断是否在任一台坦克身上*/
					if (NULL == InWhichTank(mer.dwMousePosition.X / 2,
						mer.dwMousePosition.Y, g_pTankArr, -1))
					{
						/*判断目标点状态，有物件则置空，没物件则添加物件*/
						if (g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] != MAP_NONE)
						{
							DrawChar(mer.dwMousePosition.X / 2,
								mer.dwMousePosition.Y, SZ_SPACE, 0, g_hOut);
							//写入地图
							g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = MAP_NONE;
						}
						else
						{
							DrawChar(mer.dwMousePosition.X / 2,
								mer.dwMousePosition.Y, SZ_BOX, 14, g_hOut);
							//写入地图
							g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = MAP_BOX;
						}
					}
				}
			}

		}
		if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//右击
		{
			/*判断是否在地图框架内*/
			if (mer.dwMousePosition.X < (MAPCOL - 1) * 2 && mer.dwMousePosition.X>1)
			{
				if (mer.dwMousePosition.Y < MAPROW - 1 && mer.dwMousePosition.Y>0)
				{
					/*判断是否在任一台坦克身上*/
					if (NULL == InWhichTank(mer.dwMousePosition.X / 2,
						mer.dwMousePosition.Y, g_pTankArr, -1))
					{
						/*判断目标点状态，有物件则置空，没物件则添加物件*/
						if (g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] != MAP_NONE)
						{
							DrawChar(mer.dwMousePosition.X / 2,
								mer.dwMousePosition.Y, SZ_SPACE, 0, g_hOut);
							//写入地图
							g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = MAP_NONE;
						}
						else
						{
							DrawChar(mer.dwMousePosition.X / 2,
								mer.dwMousePosition.Y, SZ_WALL, 135, g_hOut);
							//写入地图
							g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = MAP_WALL;
						}
					}
				}
			}
		}
		break;
	case DOUBLE_CLICK://双击
		break;
	case MOUSE_MOVED://鼠标移动
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//左击
		{
			/*判断是否在地图框架内*/
			if (mer.dwMousePosition.X < (MAPCOL - 1) * 2 && mer.dwMousePosition.X>1)
			{
				if (mer.dwMousePosition.Y < MAPROW - 1 && mer.dwMousePosition.Y>0)
				{
					/*判断是否在任一台坦克身上*/
					if (NULL == InWhichTank(mer.dwMousePosition.X / 2,
						mer.dwMousePosition.Y, g_pTankArr, -1))
					{
						/*判断目标点状态，有物件则置空，没物件则添加物件*/
						if (g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] != MAP_NONE)
						{
							DrawChar(mer.dwMousePosition.X / 2,
								mer.dwMousePosition.Y, SZ_SPACE, 0, g_hOut);
							//写入地图
							g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = MAP_NONE;
						}
						else
						{
							DrawChar(mer.dwMousePosition.X / 2,
								mer.dwMousePosition.Y, SZ_BOX, 14, g_hOut);
							//写入地图
							g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = MAP_BOX;
						}
					}
				}
			}
		}
		if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//右击
		{
			/*判断是否在地图框架内*/
			if (mer.dwMousePosition.X < (MAPCOL - 1) * 2 && mer.dwMousePosition.X>1)
			{
				if (mer.dwMousePosition.Y < MAPROW - 1 && mer.dwMousePosition.Y>0)
				{
					/*判断是否在任一台坦克身上*/
					if (NULL == InWhichTank(mer.dwMousePosition.X / 2,
						mer.dwMousePosition.Y, g_pTankArr, -1))
					{
						/*判断目标点状态，有物件则置空，没物件则添加物件*/
						if (g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] != MAP_NONE)
						{
							DrawChar(mer.dwMousePosition.X / 2,
								mer.dwMousePosition.Y, SZ_SPACE, 0, g_hOut);
							//写入地图
							g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = MAP_NONE;
						}
						else
						{
							DrawChar(mer.dwMousePosition.X / 2,
								mer.dwMousePosition.Y, SZ_WALL, 135, g_hOut);
							//写入地图
							g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = MAP_WALL;
						}
					}
				}
			}

		}
		OutPutPos(mer.dwMousePosition.X, mer.dwMousePosition.Y);
		break;
	}
}

/*编辑状态下的消息循环*/
void MapEditLoop()
{
	SetConsoleMode(g_hIn, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	INPUT_RECORD stcRecord = { 0 };
	DWORD dwRead;
	while (1)
	{
		ReadConsoleInput(g_hIn, &stcRecord, 1, &dwRead);
		if (stcRecord.EventType == KEY_EVENT)
		{
			if (stcRecord.Event.KeyEvent.bKeyDown == TRUE)
			{
				if (stcRecord.Event.KeyEvent.wVirtualKeyCode==VK_F9)
				{
					SaveFile();
					Sleep(1000);
					break;
				}
				//键盘信息
			}

		}
		if (stcRecord.EventType == MOUSE_EVENT)
		{
			OnMouse(stcRecord.Event.MouseEvent);
		}

	}
}

/*输出右下角侧的提示信息*/
void MapRankMenu()
{
	COORD loc;
	loc.X = 105;
	loc.Y = 20;

	SetConsoleTextAttribute(g_hOut, 15);

	SetConsoleCursorPosition(g_hOut, loc);
	printf(" F9保存地图[保存才能返回主菜单]！！！\n");
	loc.Y += 2;


	/*我方坦克图例*/
	DrawChar(loc.X / 2, loc.Y, SZ_TANK, 9, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":我方坦克！！ ");
	loc.X -= 4;

	loc.Y += 2;

	/*敌方坦克图例*/
	DrawChar(loc.X / 2, loc.Y, SZ_TANK, 12, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":敌方坦克！！ ");
	loc.X -= 4;

	loc.Y += 2;

	DrawChar(loc.X/2,loc.Y, SZ_WALL, 135, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":鼠标右键添加障碍！！ \n");
	loc.X -= 4;
	loc.Y += 2;

	DrawChar(loc.X/2, loc.Y, SZ_BOX, 14, g_hOut);
	
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":鼠标左键添加箱子！！ \n");
	loc.X -= 4;
	loc.Y += 2;

	SetConsoleTextAttribute(g_hOut, 15);
}