#pragma once
#include "Data.h"


/*��ָ��λ����ָ����ɫ��ӡָ���ַ�*/
/*����XY���ꡢ��ӡ���ַ�����ӡ����ɫ������̨���*/
void DrawChar(int nX, int nY, char* pChar, WORD wArr, HANDLE hOutPut);

/*���ϽǴ�����ʾ��*/
void DrawErrorBox(HANDLE hOut);

/*��ָ��λ���������*/
void Error(char* szErr);

/*������½�����*/
void DrawRank(HANDLE hOut);

/*������½Ǵ�����ʾ��*/
void DrawRankMenu(HANDLE hOut);

/*��ӡ��ͼ���������̨���*/
void DrawMap(HANDLE hOutPut);

/*����̹������ָ�롢̹�����ڵ�Ԫ�����С�����̨�����Ҫ��ӡ���ַ���״*/
void DrawTank(PTANK pTankArr, int nNum, HANDLE hOutPut, char* pChar);

/*����̹������ָ�롢Ҫ��ӡ���ַ���������̨������ú�������ӡ������ȫ���ɼ����ӵ�*/
void DrawBullet(PTANK pTankArr, char* pChar, HANDLE hOutPut);

/*����̹������ָ�룬�ú�������ӡ������ȫ���ɼ���̹��*/
void DrawTankArr(PTANK pTankArr, char* pChar, HANDLE hOutPut);

