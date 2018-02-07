#include "View.h"

/*��ָ��λ����ָ����ɫ��ӡָ���ַ�*/
/*����XY���ꡢ��ӡ���ַ�����ӡ����ɫ������̨���*/
void DrawChar(int nX, int nY, char* pChar, WORD wArr, HANDLE hOutPut)
{
	SetConsoleTextAttribute(hOutPut, wArr);
	COORD loc;
	loc.X = nX * 2;
	loc.Y = nY;
	SetConsoleCursorPosition(hOutPut, loc);
	printf(pChar);
}

/*������ϽǴ�����ʾ��*/
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

/*��ָ��λ���������*/
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

/*������½�����*/
void DrawRank(HANDLE hOut)
{
	
	COORD loc;
	loc.X = 105;
	loc.Y = 18;

	SetConsoleTextAttribute(g_hOut, 15);

	SetConsoleCursorPosition(g_hOut, loc);
	printf(" Esc�������˵�����");
	loc.Y += 4;

	/*�ҷ�̹��ͼ��*/
	DrawChar(loc.X / 2, loc.Y, SZ_TANK, 9, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":�ҷ�̹�ˣ��� ");

	loc.X += 20;
	DrawChar(loc.X / 2, loc.Y, SZ_BULLET, 13, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":�ҷ��ӵ����� ");
	loc.X -= 4;
	loc.X -= 20;
	loc.X -= 4;

	loc.Y += 2;

	/*�з�̹��ͼ��*/
	DrawChar(loc.X / 2, loc.Y, SZ_TANK, 12, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":�з�̹�ˣ��� ");

	loc.X += 20;
	DrawChar(loc.X / 2, loc.Y, SZ_BULLET, 14, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":�з��ӵ����� ");
	loc.X -= 4;
	loc.X -= 20;
	loc.X -= 4;

	loc.Y += 2;

	/*����ͼ��*/
	DrawChar(loc.X / 2, loc.Y, SZ_BOX, 14, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":���ӿɻ��ã���");
	loc.X -= 4;
	loc.Y += 2;

	/*����ͼ��*/
	DrawChar(loc.X / 2, loc.Y, SZ_WALL, 135, g_hOut);
	SetConsoleTextAttribute(g_hOut, 15);
	loc.X += 4;
	SetConsoleCursorPosition(g_hOut, loc);
	printf(":Χǽ�����ã���");
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
		
		printf("%s : �÷�:%3d ����ֵ:%3d\n", g_pTankArr[i].szName,
			g_pTankArr[i].nScore, g_pTankArr[i].nLife);
	}
	//Ѱ��δ���ĵ���
	int Tmp=1;
	while (g_pTankArr[Tmp].nIsVisible != 1&&Tmp<MAXTANK)
		++Tmp;

	if (Tmp==MAXTANK)//����������
	{
		SetConsoleTextAttribute(hOut, 156);
		loc.Y += 2;
		SetConsoleCursorPosition(hOut, loc);
		printf("������������Ӯ�ˣ���������\n");
	}
	else
	{
		if (g_pTankArr[0].nLife <= 0)//�������
		{
			SetConsoleTextAttribute(hOut, 192);
			loc.Y += 2;
			SetConsoleCursorPosition(hOut, loc);
			printf("���������������ˣ���������\n");
		}
	}

	SetConsoleTextAttribute(hOut, 15);
}

/*������½�������ʾ��*/
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


/*��ӡ��ͼ���������̨���*/
void DrawMap(HANDLE hOutPut)
{
	/*��ӡ��ͼ*/
	for (int i = 0; i < MAPROW; ++i)//��
	{
		for (int j = 0; j < MAPCOL; ++j)//��
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

/*����̹������ָ�롢̹�����ڵ�Ԫ�����С�����̨�����Ҫ��ӡ���ַ���״*/
void DrawTank(PTANK pTankArr,int nNum,HANDLE hOutPut,char* pChar)
{

	/*����̹����ɫ*/
	WORD wArr = 0;
	if (pTankArr[nNum].nCam == BLUE)//����Ӫ
	{
		wArr = 9;
	}
	else//�ж���Ӫ
	{
		wArr = 12;
	}

	/*���ݷ����ӡ̹��*/
	switch (pTankArr[nNum].nDirect)
	{
	default:
		break;
	case UP:
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY - 1,
			pChar, wArr, hOutPut);//ͷ
		DrawChar(pTankArr[nNum].nX - 1, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//����
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//����
		DrawChar(pTankArr[nNum].nX + 1, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//����
		DrawChar(pTankArr[nNum].nX - 1, pTankArr[nNum].nY + 1,
			pChar, wArr, hOutPut);//��β
		DrawChar(pTankArr[nNum].nX + 1, pTankArr[nNum].nY + 1,
			pChar, wArr, hOutPut);//��β
		break;
	case DOWN:
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY + 1,
			pChar, wArr, hOutPut);//ͷ
		DrawChar(pTankArr[nNum].nX - 1, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//����
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//����
		DrawChar(pTankArr[nNum].nX + 1, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//����
		DrawChar(pTankArr[nNum].nX - 1, pTankArr[nNum].nY - 1,
			pChar, wArr, hOutPut);//��β
		DrawChar(pTankArr[nNum].nX + 1, pTankArr[nNum].nY - 1,
			pChar, wArr, hOutPut);//��β
		break;
	case LEFT:
		DrawChar(pTankArr[nNum].nX - 1, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//ͷ
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY + 1,
			pChar, wArr, hOutPut);//����
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//����
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY - 1,
			pChar, wArr, hOutPut);//����
		DrawChar(pTankArr[nNum].nX + 1, pTankArr[nNum].nY + 1,
			pChar, wArr, hOutPut);//��β
		DrawChar(pTankArr[nNum].nX + 1, pTankArr[nNum].nY - 1,
			pChar, wArr, hOutPut);//��β
		break;
	case RIGHT:
		DrawChar(pTankArr[nNum].nX + 1, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//ͷ
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY - 1,
			pChar, wArr, hOutPut);//����
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY,
			pChar, wArr, hOutPut);//����
		DrawChar(pTankArr[nNum].nX, pTankArr[nNum].nY + 1,
			pChar, wArr, hOutPut);//����
		DrawChar(pTankArr[nNum].nX - 1, pTankArr[nNum].nY - 1,
			pChar, wArr, hOutPut);//��β
		DrawChar(pTankArr[nNum].nX - 1, pTankArr[nNum].nY + 1,
			pChar, wArr, hOutPut);//��β
		break;
	}

}

/*����̹������ָ�롢Ҫ��ӡ���ַ���������̨������ú�������ӡȫ���ɼ����ӵ�*/
void DrawBullet(PTANK pTankArr,char* pChar,HANDLE hOutPut)
{
	
	WORD wArr;

	/*��ӡ����ȫ���ɼ����ӵ�*/

	for (int i = 0; i < MAXTANK; ++i)
	{
		/*�����ӵ���ɫ*/
		if (pTankArr[i].nCam == BLUE)//����Ӫ
		{
			wArr = 13;
		}
		else//�ж���Ӫ
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

/*����̹������ָ�롢Ҫ��ӡ���ַ���������̨������ú�������ӡ������ȫ���ɼ���̹��*/
void DrawTankArr(PTANK pTankArr, char* pChar,HANDLE hOutPut)
{
	/*��ӡ̹��*/
	for (int i = 0; i < MAXTANK; ++i)
	{
		if (!pTankArr[i].nIsVisible)//���ɼ���̹����������
			continue;

		DrawTank(pTankArr,i,hOutPut,pChar);
	}
}

