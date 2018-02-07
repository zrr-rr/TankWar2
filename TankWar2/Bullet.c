#include "Bullet.h"
#include "Tank.h"
#include "View.h"

/*X,Y�����Ƿ���磬�Ƿ���1����Ϊ0*/
int IsXYOOB(int nX, int nY) 
{
	if (nX< 1 || nX > MAPCOL - 2)
	{
		return 1;
	}
	if (nY < 1 || nY  > MAPROW - 2)
	{
		return 1;
	}
	return 0;
}

/*�ӵ������߼�*/
/*���������ӵ������ӵ�������ÿ���ӵ����в���*/
/*�����ӵ������ָ��,�ӵ�����������̹�˵�����ָ��,̹�����ڵ�Ԫ������*/
void BulletFly(PBULLET pBulletArr, PTANK pTankArr, int nNum)
{
	for (int i = 0; i < MAXBULLET; ++i)
	{
		/*�ж��Ƿ�ɼ������ɼ��򲻲������ӵ�*/
		if (pBulletArr[i].nIsVisible == 1)
		{
			/*���ӵ��������з�������ƶ�*/
			switch (pBulletArr[i].nDirect)
			{
			default:
				break;
			case UP:
				pBulletArr[i].nY -= 1;
				break;
			case DOWN:
				pBulletArr[i].nY += 1;
				break;
			case LEFT:
				pBulletArr[i].nX -= 1;
				break;
			case RIGHT:
				pBulletArr[i].nX += 1;
				break;
			}

			/*�ӵ������������ӵ����ָ��ӵ����ڵ�̹�˵��ӵ�����*/
			if (IsXYOOB(pBulletArr[i].nX, pBulletArr[i].nY))
			{
				pBulletArr[i].nIsVisible = 0;
				pTankArr[nNum].nBullet += 1;
			}
			
			/*�ӵ��������������ӵ����ָ��ӵ����ڵ�̹�˵��ӵ�����*/
			/*����̹�˷���*/
			if (g_cMap[pBulletArr[i].nY][pBulletArr[i].nX ] == MAP_BOX)
			{
				g_cMap[pBulletArr[i].nY][pBulletArr[i].nX ] = MAP_NONE;
				pBulletArr[i].nIsVisible = 0;
				pTankArr[nNum].nBullet += 1;
				pTankArr[nNum].nScore += 1;

			}

			/*�ӵ���Χǽ�������ӵ����ָ��ӵ����ڵ�̹�˵��ӵ�����*/
			if (g_cMap[pBulletArr[i].nY][pBulletArr[i].nX] == MAP_WALL)
			{
				pBulletArr[i].nIsVisible = 0;
				pTankArr[nNum].nBullet += 1;

			}

			/*����ӵ��Ƿ���̹������*/
			PTANK pTmp = InWhichTank(pBulletArr[i].nX, pBulletArr[i].nY, pTankArr, nNum);

			/*�ӵ���̹��������ִ��*/
			if (pTmp != NULL)
			{
				/*�ӵ���̹�˵���Ӫ��ͬ�������²���*/
				if (pBulletArr[i].nCam != pTmp->nCam)
				{
					pBulletArr[i].nIsVisible = 0;
					pTankArr[nNum].nScore += 10;
					pTankArr[nNum].nBullet += 1;
					pTmp->nLife -= 10;//�з�
					if (pTmp->nLife<=0)//Ŀ��̹������
					{
						DrawTankArr(pTankArr, SZ_SPACE, g_hOut);
						pTmp->nIsVisible = 0;
						DrawTankArr(pTankArr, SZ_TANK, g_hOut);
					}

				}

			}
		}
	}

}