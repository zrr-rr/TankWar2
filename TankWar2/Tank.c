#include "Tank.h"
#include "Bullet.h"
#include "View.h"

/*�ж�̹���Ƿ����*/
/*̹�˳����򷵻�1�����򷵻�0*/
/*����̹������ָ�롢̹�����ڵ�Ԫ������*/
int IsTankOOB(PTANK pTankArr, int nNum)
{
	if (pTankArr[nNum].nX< 2 || pTankArr[nNum].nX + 3> MAPCOL)
	{
		return 1;
	}
	if (pTankArr[nNum].nY < 2 || pTankArr[nNum].nY + 3 > MAPROW)
	{
		return 1;
	}

	return 0;
}

/*��ĳһ̹�����*/
/*����̹������ָ�롢̹�����ڵ�Ԫ������*/
void TankShot(PTANK pTankArr, int nNum)
{
	if (pTankArr[nNum].nBullet <= 0)//û�ӵ��򷵻�
		return;

	pTankArr[nNum].nBullet -= 1;

	
	//����̹�������е��ӵ����ҵ������ǿ�
	int Tmp = 0;
	while (pTankArr[nNum].pBulletArr[Tmp].nIsVisible == 1 && Tmp < MAXBULLET)
		++Tmp;

	pTankArr[nNum].pBulletArr[Tmp].nIsVisible = 1;
	pTankArr[nNum].pBulletArr[Tmp].nDirect = pTankArr[nNum].nDirect;

	int nX = pTankArr[nNum].nX, nY = pTankArr[nNum].nY;

	//�����ӵ��ķ���������ʱ�ӵ�λ��
	switch (pTankArr[nNum].nDirect)
	{
	default:
		break;
	case UP:
		nY -= 2;
		break;
	case DOWN:
		nY += 2;
		break;
	case LEFT:
		nX -= 2;
		break;
	case RIGHT:
		nX += 2;
		break;
	}

	//�ж���ʱ�ӵ��Ƿ���磬���������ظ��ӵ�����ԭ̹�˿����ӵ���
	if (IsXYOOB(nX, nY))
	{
		pTankArr[nNum].nBullet += 1;
		pTankArr[nNum].pBulletArr[Tmp].nIsVisible = 0;
		return;
	}

	/*�ӵ��������������ӵ����ָ��ӵ����ڵ�̹�˵��ӵ�����*/
	/*����̹�˷���*/
	if (g_cMap[nY][nX] == MAP_BOX)
	{
		g_cMap[nY][nX] = MAP_NONE;
		pTankArr[nNum].pBulletArr[Tmp].nIsVisible = 0;
		pTankArr[nNum].nBullet += 1;
		pTankArr[nNum].nScore += 1;

	}

	/*�ӵ���Χǽ�������ӵ����ָ��ӵ����ڵ�̹�˵��ӵ�����*/
	if (g_cMap[nY][nX] == MAP_WALL)
	{
		pTankArr[nNum].pBulletArr[Tmp].nIsVisible = 0;
		pTankArr[nNum].nBullet += 1;

	}

	/*�ж�һ��ǹ�Ƿ��Ѵ��жԷ�*/
	/*������۶Է�Ѫ�����ָ��ҷ�״̬*/
	PTANK pTmp = InWhichTank(nX, nY, pTankArr, nNum);
	if (pTmp!=NULL)
	{
		if (pTankArr[nNum].nCam != pTmp->nCam)//��ͬ��Ӫʱ��ִ��
		{
			pTmp->nLife -= 10;
			pTankArr[nNum].nBullet += 1;
			pTankArr[nNum].pBulletArr[Tmp].nIsVisible = 0;
			if (pTmp->nLife <= 0)//Ŀ��̹������
			{
				DrawTankArr(pTankArr, SZ_SPACE, g_hOut);
				pTmp->nIsVisible = 0;
				DrawTankArr(pTankArr, SZ_TANK, g_hOut);
			}
		}
	}

	

	//��ʱ�ӵ�����������ֵ�������ӵ�
	pTankArr[nNum].pBulletArr[Tmp].nX = nX;
	pTankArr[nNum].pBulletArr[Tmp].nY = nY;
}


/*��������̹��Ԫ��*/
/*����ָ��Ŀ����������̹�˵�ָ��*/
/*����X��Y���꣬����Ԫ������ΪSkip��̹�ˡ�*/
/*��nSkip��Ϊ<0��ֵ��������X��Y������һ̹�����򷵻�NULL*/
PTANK InWhichTank(int nX, int nY, PTANK pTankArr, int nSkip)
{
	for (int i = 0; i < MAXTANK; ++i)
	{
		//����̹�˲��ɼ���ָ��Ҫ�ӹ���Ԫ��ʱ������
		if ((!pTankArr[i].nIsVisible) || i == nSkip)
			continue;
		switch (pTankArr[i].nDirect)
		{
		default:
			break;
		case UP:
			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY - 1))//ͷ
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX - 1) &&
				(nY == pTankArr[i].nY))//����
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY))//����
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX + 1) &&
				(nY == pTankArr[i].nY))//����
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX - 1) &&
				(nY == pTankArr[i].nY + 1))//��β
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX + 1) &&
				(nY == pTankArr[i].nY + 1))//��β
				return &(pTankArr[i]);

			break;
		case DOWN:
			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY + 1))//ͷ
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX - 1) &&
				(nY == pTankArr[i].nY))//����
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY))//����
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX + 1) &&
				(nY == pTankArr[i].nY))//����
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX - 1) &&
				(nY == pTankArr[i].nY - 1))//��β
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX + 1) &&
				(nY == pTankArr[i].nY - 1))//��β
				return &(pTankArr[i]);

			break;
		case LEFT:

			if ((nX == pTankArr[i].nX - 1) &&
				(nY == pTankArr[i].nY))//ͷ
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY + 1))//����
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY))//����
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY - 1))//����
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX + 1) &&
				(nY == pTankArr[i].nY + 1))//��β
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX + 1) &&
				(nY == pTankArr[i].nY - 1))//��β
				return &(pTankArr[i]);

			break;
		case RIGHT:

			if ((nX == pTankArr[i].nX + 1) &&
				(nY == pTankArr[i].nY))//ͷ
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY - 1))//����
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY))//����
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY + 1))//����
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX - 1) &&
				(nY == pTankArr[i].nY - 1))//��β
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX - 1) &&
				(nY == pTankArr[i].nY + 1))//��β
				return &(pTankArr[i]);
			break;
		}
	}

	/*������һ̹���ڣ����ؿ�*/
	return NULL;
}


/*��������̹��Ԫ��*/
/*�����򷵻�1�����򷵻�0*/
/*̹�˵��Ƿ�������һ��̹��,����̹������ָ�롢̹�����ڵ�Ԫ������*/
int IsTankCrash(PTANK pTankArr, int nNum)
{
	/*ͨ��̹��ͷ�������������̹���˶���������ж�*/
	switch (pTankArr[nNum].nDirect)
	{
	default:
		break;
	case UP:
		if (NULL != InWhichTank(pTankArr[nNum].nX, pTankArr[nNum].nY - 1, pTankArr, nNum))//ͷ
			return 1;
		if (NULL != InWhichTank(pTankArr[nNum].nX - 1, pTankArr[nNum].nY, pTankArr, nNum))//����
			return 1;
		if (NULL != InWhichTank(pTankArr[nNum].nX + 1, pTankArr[nNum].nY, pTankArr, nNum))//����
			return 1;
		break;
	case DOWN:

		if (NULL != InWhichTank(pTankArr[nNum].nX, pTankArr[nNum].nY + 1, pTankArr, nNum))//ͷ
			return 1;
		if (NULL != InWhichTank(pTankArr[nNum].nX - 1, pTankArr[nNum].nY, pTankArr, nNum))//����
			return 1;
		if (NULL != InWhichTank(pTankArr[nNum].nX + 1, pTankArr[nNum].nY, pTankArr, nNum))//����
			return 1;

		break;
	case LEFT:

		if (NULL != InWhichTank(pTankArr[nNum].nX - 1, pTankArr[nNum].nY, pTankArr, nNum))//ͷ
			return 1;
		if (NULL != InWhichTank(pTankArr[nNum].nX, pTankArr[nNum].nY + 1, pTankArr, nNum))//����
			return 1;
		if (NULL != InWhichTank(pTankArr[nNum].nX, pTankArr[nNum].nY - 1, pTankArr, nNum))//����
			return 1;

		break;
	case RIGHT:

		if (NULL != InWhichTank(pTankArr[nNum].nX + 1, pTankArr[nNum].nY, pTankArr, nNum))//ͷ
			return 1;
		if (NULL != InWhichTank(pTankArr[nNum].nX, pTankArr[nNum].nY - 1, pTankArr, nNum))//����
			return 1;
		if (NULL != InWhichTank(pTankArr[nNum].nX, pTankArr[nNum].nY + 1, pTankArr, nNum))//����
			return 1;

		break;
	}

	/*ͨ��̹��ͷ�������������̹���˶���������ж�*/
	switch (pTankArr[nNum].nDirect)
	{
	default:
		break;
	case UP:
		if (g_cMap[pTankArr[nNum].nY - 1][pTankArr[nNum].nX] != MAP_NONE)//ͷ
			return 1;
		if (g_cMap[pTankArr[nNum].nY][pTankArr[nNum].nX - 1] != MAP_NONE)//����
			return 1;
		if (g_cMap[pTankArr[nNum].nY][pTankArr[nNum].nX + 1] != MAP_NONE)//����
			return 1;
		break;
	case DOWN:

		if (g_cMap[pTankArr[nNum].nY + 1][pTankArr[nNum].nX]!= MAP_NONE)//ͷ
			return 1;
		if (g_cMap[pTankArr[nNum].nY][pTankArr[nNum].nX - 1] != MAP_NONE)//����
			return 1;
		if (g_cMap[pTankArr[nNum].nY][pTankArr[nNum].nX + 1] != MAP_NONE)//����
			return 1;

		break;
	case LEFT:

		if (g_cMap[pTankArr[nNum].nY][pTankArr[nNum].nX - 1] != MAP_NONE)//ͷ
			return 1;
		if (g_cMap[pTankArr[nNum].nY + 1][pTankArr[nNum].nX] != MAP_NONE)//����
			return 1;
		if (g_cMap[pTankArr[nNum].nY - 1][pTankArr[nNum].nX] != MAP_NONE)//����
			return 1;

		break;
	case RIGHT:

		if (g_cMap[pTankArr[nNum].nY][pTankArr[nNum].nX + 1] != MAP_NONE)//ͷ
			return 1;
		if (g_cMap[pTankArr[nNum].nY - 1][pTankArr[nNum].nX] != MAP_NONE)//����
			return 1;
		if (g_cMap[pTankArr[nNum].nY + 1][pTankArr[nNum].nX] != MAP_NONE)//����
			return 1;

		break;
	}

	
	/*û����������0*/
	return 0;
}


/*��ĳһ̹�����н�����ǰ��*/
/*����̹������ָ�롢�н�����̹�����ڵ�Ԫ������*/
void TankMove(PTANK pTankArr, int nDirect, int nNum)
{
	int nX = pTankArr[nNum].nX, nY = pTankArr[nNum].nY;

	switch (nDirect)
	{
	default:
		break;
	case UP:
		pTankArr[nNum].nY -= 1;
		break;
	case DOWN:
		pTankArr[nNum].nY += 1;
		break;
	case LEFT:
		pTankArr[nNum].nX -= 1;
		break;
	case RIGHT:
		pTankArr[nNum].nX += 1;
		break;
	}

	/*̹�˳�����ԭ���겢�˳�*/
	if (IsTankOOB(pTankArr, nNum))
	{
		pTankArr[nNum].nX = nX;
		pTankArr[nNum].nY = nY;
		return;
	}


	/*ײ������̹����ԭ���겢�˳�*/
	if (IsTankCrash(pTankArr, nNum))
	{
		pTankArr[nNum].nX = nX;
		pTankArr[nNum].nY = nY;
		return;
	}

	pTankArr[nNum].nDirect = nDirect;

}

