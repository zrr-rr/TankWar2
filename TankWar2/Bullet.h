#pragma once
#include "Data.h"

/*X,Y坐标是否出界，是返回1，否为0*/
int IsXYOOB(int nX,int nY);

/*子弹飞行逻辑*/
/*函数遍历子弹，对子弹数组中每个子弹进行操作*/
/*传入子弹数组的指针,子弹数组所属的坦克的数组指针,坦克属于的元素序列*/
void BulletFly(PBULLET pBulletArr, PTANK pTankArr, int nNum);
