#pragma once
#include "Data.h"

/*����̹�˺��ӵ���Ϣ*/
void SaveTanknBullet(PTANK pTankArr, FILE *pFile);

/*����̹�˺��ӵ���Ϣ*/
void LoadTanknBullet(PTANK *ppTankArr, FILE *pFile);

/*�����ͼ��Ϣ*/
void SaveMap(FILE *pFile);

/*���ص�ͼ��Ϣ*/
void LoadMap(FILE *pFile);

/*�����ļ�*/
void SaveFile();

/*�����ļ�*/
void LoadFile();