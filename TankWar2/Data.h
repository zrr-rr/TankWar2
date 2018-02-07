#pragma once

#include "Windows.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define KEYDOWN(vk_code)((GetAsyncKeyState(vk_code)&0x8000)?1:0)
#define KEYUP(vk_code)((GetAsyncKeyState(vk_code)&0x8000)?0:1)

/*�����ͼ�С����*/

#define MAPROW 60                 //�У���
#define MAPCOL 50                //�У���

/*���巽��*/

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

/*������Ӫ*/

#define RED 1
#define BLUE 2

/*�����ͼ���������*/

#define MAP_WALL 'W'
#define MAP_RIVER 'R'
#define MAP_GRASS 'G'
#define MAP_BOX 'B'
#define MAP_NONE 'N'
/*#define MAP_SANDY 'S'*/



/*�����ͼ�����Ӧ�ַ�ͼ��*/

#define SZ_WALL "ǽ"
#define SZ_RIVER "��"
#define SZ_GRASS "��"
#define SZ_BOX "��"
#define SZ_SPACE "  "
/*#define SZ_SANDY "ɳ"*/

/*����̹���ַ�ͼ��*/
#define SZ_TANK "��"

/*�����ӵ��ַ�ͼ��*/
#define SZ_BULLET "��"

/*��������ڳ�̹����,�����*/
#define MAXTANK 4

/*����ÿ̨̹������ӵ���*/
#define MAXBULLET 20

#define FILEPATH "TankWar.dat"


typedef struct _BULLET
{
	int nIsVisible;//�Ƿ�ɼ�:0Ϊ���ɼ���1Ϊ�ɼ�
	int nX, nY;//���ĵ�����
/*	int nSpeed;//�ӵ����ٶ�*/
	int nCam;//�ӵ�����Ӫ
	int nDirect;//�ӵ����˶�����

}BULLET,*PBULLET;//�ӵ��ṹ��Ϣ

typedef struct _TANK
{
	char szName[10];//̹������
	int nDirect;//̹���˶�����
	int nCam;//̹����Ӫ
	int nLife;//����ֵ
	int nScore;//�÷�
	int nX, nY;//���ĵ�����
/*	int nSpeed;//̹���ٶ�*/
	int nIsVisible;//�Ƿ�ɼ�:0Ϊ���ɼ���1Ϊ�ɼ�
	int nBullet;//��ǰ�ӵ�����
	PBULLET pBulletArr;//̹�������е��ӵ�

}TANK, *PTANK;//̹�˵Ľṹ

PTANK g_pTankArr;

HANDLE g_hOut, g_hIn;

char g_cMap[MAPROW][MAPCOL];