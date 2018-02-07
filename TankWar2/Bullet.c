#include "Bullet.h"
#include "Tank.h"
#include "View.h"

/*X,Y坐标是否出界，是返回1，否为0*/
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

/*子弹飞行逻辑*/
/*函数遍历子弹，对子弹数组中每个子弹进行操作*/
/*传入子弹数组的指针,子弹数组所属的坦克的数组指针,坦克属于的元素序列*/
void BulletFly(PBULLET pBulletArr, PTANK pTankArr, int nNum)
{
	for (int i = 0; i < MAXBULLET; ++i)
	{
		/*判断是否可见、不可见则不操作此子弹*/
		if (pBulletArr[i].nIsVisible == 1)
		{
			/*让子弹根据运行方向进行移动*/
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

			/*子弹出界则隐藏子弹，恢复子弹属于的坦克的子弹存量*/
			if (IsXYOOB(pBulletArr[i].nX, pBulletArr[i].nY))
			{
				pBulletArr[i].nIsVisible = 0;
				pTankArr[nNum].nBullet += 1;
			}
			
			/*子弹打到箱子则隐藏子弹，恢复子弹属于的坦克的子弹存量*/
			/*增加坦克分数*/
			if (g_cMap[pBulletArr[i].nY][pBulletArr[i].nX ] == MAP_BOX)
			{
				g_cMap[pBulletArr[i].nY][pBulletArr[i].nX ] = MAP_NONE;
				pBulletArr[i].nIsVisible = 0;
				pTankArr[nNum].nBullet += 1;
				pTankArr[nNum].nScore += 1;

			}

			/*子弹打到围墙则隐藏子弹，恢复子弹属于的坦克的子弹存量*/
			if (g_cMap[pBulletArr[i].nY][pBulletArr[i].nX] == MAP_WALL)
			{
				pBulletArr[i].nIsVisible = 0;
				pTankArr[nNum].nBullet += 1;

			}

			/*检查子弹是否在坦克体内*/
			PTANK pTmp = InWhichTank(pBulletArr[i].nX, pBulletArr[i].nY, pTankArr, nNum);

			/*子弹在坦克体内则执行*/
			if (pTmp != NULL)
			{
				/*子弹与坦克的阵营不同则做如下操作*/
				if (pBulletArr[i].nCam != pTmp->nCam)
				{
					pBulletArr[i].nIsVisible = 0;
					pTankArr[nNum].nScore += 10;
					pTankArr[nNum].nBullet += 1;
					pTmp->nLife -= 10;//敌方
					if (pTmp->nLife<=0)//目标坦克死了
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