#pragma once
#include "Data.h"

/*X,Y�����Ƿ���磬�Ƿ���1����Ϊ0*/
int IsXYOOB(int nX,int nY);

/*�ӵ������߼�*/
/*���������ӵ������ӵ�������ÿ���ӵ����в���*/
/*�����ӵ������ָ��,�ӵ�����������̹�˵�����ָ��,̹�����ڵ�Ԫ������*/
void BulletFly(PBULLET pBulletArr, PTANK pTankArr, int nNum);
