#pragma once
#include "Data.h"


/*在指定位置用指定颜色打印指定字符*/
/*传入XY坐标、打印的字符、打印的颜色、控制台句柄*/
void DrawChar(int nX, int nY, char* pChar, WORD wArr, HANDLE hOutPut);

/*右上角错误显示框*/
void DrawErrorBox(HANDLE hOut);

/*在指定位置输出错误*/
void Error(char* szErr);

/*输出右下角排名*/
void DrawRank(HANDLE hOut);

/*输出右下角错误显示框*/
void DrawRankMenu(HANDLE hOut);

/*打印地图，传入控制台句柄*/
void DrawMap(HANDLE hOutPut);

/*传入坦克数组指针、坦克属于的元素序列、控制台句柄、要打印的字符形状*/
void DrawTank(PTANK pTankArr, int nNum, HANDLE hOutPut, char* pChar);

/*传入坦克数组指针、要打印的字符串、控制台句柄，该函数将打印该数组全部可见的子弹*/
void DrawBullet(PTANK pTankArr, char* pChar, HANDLE hOutPut);

/*传入坦克数组指针，该函数将打印该数组全部可见的坦克*/
void DrawTankArr(PTANK pTankArr, char* pChar, HANDLE hOutPut);

