#pragma once
#include "Data.h"


/*�ж�̹���Ƿ����*/
/*̹�˳����򷵻�1�����򷵻�0*/
/*����̹������ָ�롢̹�����ڵ�Ԫ������*/
int IsTankOOB(PTANK pTankArr, int nNum);

/*��ĳһ̹�����*/
/*����̹������ָ�롢̹�����ڵ�Ԫ������*/
void TankShot(PTANK pTankArr, int nNum);

/*��������̹��Ԫ��*/
/*����ָ��Ŀ����������̹�˵�ָ��*/
/*����X��Y���꣬����Ԫ������ΪSkip��̹�ˡ�*/
/*��nSkip��Ϊ<0��ֵ��������X��Y������һ̹�����򷵻�NULL*/
PTANK InWhichTank(int nX, int nY, PTANK pTankArr, int nSkip);

/*��������̹��Ԫ��*/
/*�����򷵻�1�����򷵻�0*/
/*̹�˵��Ƿ�������һ��̹��,����̹������ָ�롢̹�����ڵ�Ԫ������*/
int IsTankCrash(PTANK pTankArr, int nNum);

/*��ĳһ̹�����н�����ǰ��*/
/*����̹������ָ�롢�н�����̹�����ڵ�Ԫ������*/
void TankMove(PTANK pTankArr, int nDirect, int nNum);
