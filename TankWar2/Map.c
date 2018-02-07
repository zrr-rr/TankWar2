#include "Map.h"
#include "View.h"
#include "Tank.h"
#include "Doc.h"

/*�ڱ��⴦�������X���꣬Y����*/
void OutPutPos(int nX, int nY)
{
	char szBuf[60] = { 0 };
	sprintf_s(szBuf, sizeof(szBuf), 
		"ԭʼ���� x=%3d , y=%3d  ��ͼ����  x=%3d , y=%3d ",
		nX, nY, nX/2, nY);
	SetConsoleTitleA(szBuf);
}

/*��Ӧ�����Ϣ�ĺ�����ֻ�ڱ༭״̬�±�����*/
void OnMouse(MOUSE_EVENT_RECORD mer)
{
	switch (mer.dwEventFlags)
	{
	default:
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//���
		{
			/*�ж��Ƿ��ڵ�ͼ�����*/
			if (mer.dwMousePosition.X < (MAPCOL - 1) * 2 && mer.dwMousePosition.X>1)
			{
				if (mer.dwMousePosition.Y < MAPROW - 1 && mer.dwMousePosition.Y>0)
				{
					/*�ж��Ƿ�����һ̨̹������*/
					if (NULL == InWhichTank(mer.dwMousePosition.X / 2,
						mer.dwMousePosition.Y, g_pTankArr, -1))
					{
						/*�ж�Ŀ���״̬����������ÿգ�û�����������*/
						if (g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] != MAP_NONE)
						{
							DrawChar(mer.dwMousePosition.X / 2,
								mer.dwMousePosition.Y, SZ_SPACE, 0, g_hOut);
							//д���ͼ
							g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = MAP_NONE;
						}
						else
						{
							DrawChar(mer.dwMousePosition.X / 2,
								mer.dwMousePosition.Y, SZ_BOX, 14, g_hOut);
							//д���ͼ
							g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = MAP_BOX;
						}
					}
				}
			}

		}
		if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//�һ�
		{
			/*�ж��Ƿ��ڵ�ͼ�����*/
			if (mer.dwMousePosition.X < (MAPCOL - 1) * 2 && mer.dwMousePosition.X>1)
			{
				if (mer.dwMousePosition.Y < MAPROW - 1 && mer.dwMousePosition.Y>0)
				{
					/*�ж��Ƿ�����һ̨̹������*/
					if (NULL == InWhichTank(mer.dwMousePosition.X / 2,
						mer.dwMousePosition.Y, g_pTankArr, -1))
					{
						/*�ж�Ŀ���״̬����������ÿգ�û�����������*/
						if (g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] != MAP_NONE)
						{
							DrawChar(mer.dwMousePosition.X / 2,
								mer.dwMousePosition.Y, SZ_SPACE, 0, g_hOut);
							//д���ͼ
							g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = MAP_NONE;
						}
						else
						{
							DrawChar(mer.dwMousePosition.X / 2,
								mer.dwMousePosition.Y, SZ_WALL, 135, g_hOut);
							//д���ͼ
							g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = MAP_WALL;
						}
					}
				}
			}
		}
		break;
	case DOUBLE_CLICK://˫��
		break;
	case MOUSE_MOVED://����ƶ�
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//���
		{
			/*�ж��Ƿ��ڵ�ͼ�����*/
			if (mer.dwMousePosition.X < (MAPCOL - 1) * 2 && mer.dwMousePosition.X>1)
			{
				if (mer.dwMousePosition.Y < MAPROW - 1 && mer.dwMousePosition.Y>0)
				{
					/*�ж��Ƿ�����һ̨̹������*/
					if (NULL == InWhichTank(mer.dwMousePosition.X / 2,
						mer.dwMousePosition.Y, g_pTankArr, -1))
					{
						/*�ж�Ŀ���״̬����������ÿգ�û�����������*/
						if (g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] != MAP_NONE)
						{
							DrawChar(mer.dwMousePosition.X / 2,
								mer.dwMousePosition.Y, SZ_SPACE, 0, g_hOut);
							//д���ͼ
							g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = MAP_NONE;
						}
						else
						{
							DrawChar(mer.dwMousePosition.X / 2,
								mer.dwMousePosition.Y, SZ_BOX, 14, g_hOut);
							//д���ͼ
							g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = MAP_BOX;
						}
					}
				}
			}
		}
		if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//�һ�
		{
			/*�ж��Ƿ��ڵ�ͼ�����*/
			if (mer.dwMousePosition.X < (MAPCOL - 1) * 2 && mer.dwMousePosition.X>1)
			{
				if (mer.dwMousePosition.Y < MAPROW - 1 && mer.dwMousePosition.Y>0)
				{
					/*�ж��Ƿ�����һ̨̹������*/
					if (NULL == InWhichTank(mer.dwMousePosition.X / 2,
						mer.dwMousePosition.Y, g_pTankArr, -1))
					{
						/*�ж�Ŀ���״̬����������ÿգ�û�����������*/
						if (g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] != MAP_NONE)
						{
							DrawChar(mer.dwMousePosition.X / 2,
								mer.dwMousePosition.Y, SZ_SPACE, 0, g_hOut);
							//д���ͼ
							g_cMap[mer.dwMousePosition.Y][mer.dwMousePosition.X / 2] = MAP_NONE;
						}
						else
						{
							DrawChar(mer.dwMousePosition.X / 2,
								mer.dwMousePosition.Y, SZ_WALL, 135, g_hOut);
							//д���ͼ
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

/*�༭״̬�µ���Ϣѭ��*/
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
				//������Ϣ
			}

		}
		if (stcRecord.EventType == MOUSE_EVENT)
		{
			OnMouse(stcRecord.Event.MouseEvent);
		}

	}
}

/*������½ǲ����ʾ��Ϣ*/
void MapRankMenu()
{
	COORD loc;
	loc.X = 105;
	loc.Y = 20;

	SetConsoleTextAttribute(g_hOut, 15);

	SetConsoleCursorPosition(g_hOut, loc);
	printf(" F9�����ͼ[������ܷ������˵�]������\n");
	loc.Y += 2;


	/*�ҷ�̹��ͼ��*/
	DrawChar(loc.X / 2, loc.Y, SZ_TANK, 9, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":�ҷ�̹�ˣ��� ");
	loc.X -= 4;

	loc.Y += 2;

	/*�з�̹��ͼ��*/
	DrawChar(loc.X / 2, loc.Y, SZ_TANK, 12, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":�з�̹�ˣ��� ");
	loc.X -= 4;

	loc.Y += 2;

	DrawChar(loc.X/2,loc.Y, SZ_WALL, 135, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":����Ҽ�����ϰ����� \n");
	loc.X -= 4;
	loc.Y += 2;

	DrawChar(loc.X/2, loc.Y, SZ_BOX, 14, g_hOut);
	
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":������������ӣ��� \n");
	loc.X -= 4;
	loc.Y += 2;

	SetConsoleTextAttribute(g_hOut, 15);
}