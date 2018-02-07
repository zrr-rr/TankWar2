#pragma once
#include "Data.h"


/*判断坦克是否出界*/
/*坦克出界则返回1，否则返回0*/
/*传入坦克数组指针、坦克属于的元素序列*/
int IsTankOOB(PTANK pTankArr, int nNum);

/*让某一坦克射击*/
/*传入坦克数组指针、坦克属于的元素序列*/
void TankShot(PTANK pTankArr, int nNum);

/*遍历所有坦克元素*/
/*返回指向目标坐标所在坦克的指针*/
/*传入X、Y坐标，跳过元素序列为Skip的坦克。*/
/*将nSkip设为<0的值则不跳过，X、Y不在任一坦克内则返回NULL*/
PTANK InWhichTank(int nX, int nY, PTANK pTankArr, int nSkip);

/*遍历所有坦克元素*/
/*碰到则返回1，否则返回0*/
/*坦克的是否碰到另一个坦克,传入坦克数组指针、坦克属于的元素序列*/
int IsTankCrash(PTANK pTankArr, int nNum);

/*让某一坦克往行进方向前进*/
/*传入坦克数组指针、行进方向、坦克属于的元素序列*/
void TankMove(PTANK pTankArr, int nDirect, int nNum);
