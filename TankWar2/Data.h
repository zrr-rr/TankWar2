#pragma once

#include "Windows.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define KEYDOWN(vk_code)((GetAsyncKeyState(vk_code)&0x8000)?1:0)
#define KEYUP(vk_code)((GetAsyncKeyState(vk_code)&0x8000)?0:1)

/*定义地图行、宽度*/

#define MAPROW 60                 //行，横
#define MAPCOL 50                //列，纵

/*定义方向*/

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

/*定义阵营*/

#define RED 1
#define BLUE 2

/*定义地图中物件类型*/

#define MAP_WALL 'W'
#define MAP_RIVER 'R'
#define MAP_GRASS 'G'
#define MAP_BOX 'B'
#define MAP_NONE 'N'
/*#define MAP_SANDY 'S'*/



/*定义地图物件对应字符图像*/

#define SZ_WALL "墙"
#define SZ_RIVER "河"
#define SZ_GRASS "草"
#define SZ_BOX "箱"
#define SZ_SPACE "  "
/*#define SZ_SANDY "沙"*/

/*定义坦克字符图像*/
#define SZ_TANK "█"

/*定义子弹字符图像*/
#define SZ_BULLET "◎"

/*定义最多在场坦克数,含玩家*/
#define MAXTANK 4

/*定义每台坦克最高子弹数*/
#define MAXBULLET 20

#define FILEPATH "TankWar.dat"


typedef struct _BULLET
{
	int nIsVisible;//是否可见:0为不可见、1为可见
	int nX, nY;//中心点坐标
/*	int nSpeed;//子弹的速度*/
	int nCam;//子弹的阵营
	int nDirect;//子弹的运动方向

}BULLET,*PBULLET;//子弹结构信息

typedef struct _TANK
{
	char szName[10];//坦克名字
	int nDirect;//坦克运动方向
	int nCam;//坦克阵营
	int nLife;//生命值
	int nScore;//得分
	int nX, nY;//中心点坐标
/*	int nSpeed;//坦克速度*/
	int nIsVisible;//是否可见:0为不可见、1为可见
	int nBullet;//当前子弹存量
	PBULLET pBulletArr;//坦克所带有的子弹

}TANK, *PTANK;//坦克的结构

PTANK g_pTankArr;

HANDLE g_hOut, g_hIn;

char g_cMap[MAPROW][MAPCOL];