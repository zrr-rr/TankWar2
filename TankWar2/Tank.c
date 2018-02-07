#include "Tank.h"
#include "Bullet.h"
#include "View.h"

/*判断坦克是否出界*/
/*坦克出界则返回1，否则返回0*/
/*传入坦克数组指针、坦克属于的元素序列*/
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

/*让某一坦克射击*/
/*传入坦克数组指针、坦克属于的元素序列*/
void TankShot(PTANK pTankArr, int nNum)
{
	if (pTankArr[nNum].nBullet <= 0)//没子弹则返回
		return;

	pTankArr[nNum].nBullet -= 1;

	
	//遍历坦克所持有的子弹，找到可用那颗
	int Tmp = 0;
	while (pTankArr[nNum].pBulletArr[Tmp].nIsVisible == 1 && Tmp < MAXBULLET)
		++Tmp;

	pTankArr[nNum].pBulletArr[Tmp].nIsVisible = 1;
	pTankArr[nNum].pBulletArr[Tmp].nDirect = pTankArr[nNum].nDirect;

	int nX = pTankArr[nNum].nX, nY = pTankArr[nNum].nY;

	//根据子弹的方向生成临时子弹位置
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

	//判断临时子弹是否出界，出界则隐藏该子弹，还原坦克可用子弹数
	if (IsXYOOB(nX, nY))
	{
		pTankArr[nNum].nBullet += 1;
		pTankArr[nNum].pBulletArr[Tmp].nIsVisible = 0;
		return;
	}

	/*子弹打到箱子则隐藏子弹，恢复子弹属于的坦克的子弹存量*/
	/*增加坦克分数*/
	if (g_cMap[nY][nX] == MAP_BOX)
	{
		g_cMap[nY][nX] = MAP_NONE;
		pTankArr[nNum].pBulletArr[Tmp].nIsVisible = 0;
		pTankArr[nNum].nBullet += 1;
		pTankArr[nNum].nScore += 1;

	}

	/*子弹打到围墙则隐藏子弹，恢复子弹属于的坦克的子弹存量*/
	if (g_cMap[nY][nX] == MAP_WALL)
	{
		pTankArr[nNum].pBulletArr[Tmp].nIsVisible = 0;
		pTankArr[nNum].nBullet += 1;

	}

	/*判断一开枪是否已打中对方*/
	/*打中则扣对方血，并恢复我方状态*/
	PTANK pTmp = InWhichTank(nX, nY, pTankArr, nNum);
	if (pTmp!=NULL)
	{
		if (pTankArr[nNum].nCam != pTmp->nCam)//不同阵营时才执行
		{
			pTmp->nLife -= 10;
			pTankArr[nNum].nBullet += 1;
			pTankArr[nNum].pBulletArr[Tmp].nIsVisible = 0;
			if (pTmp->nLife <= 0)//目标坦克死了
			{
				DrawTankArr(pTankArr, SZ_SPACE, g_hOut);
				pTmp->nIsVisible = 0;
				DrawTankArr(pTankArr, SZ_TANK, g_hOut);
			}
		}
	}

	

	//临时子弹运行正常赋值给正常子弹
	pTankArr[nNum].pBulletArr[Tmp].nX = nX;
	pTankArr[nNum].pBulletArr[Tmp].nY = nY;
}


/*遍历所有坦克元素*/
/*返回指向目标坐标所在坦克的指针*/
/*传入X、Y坐标，跳过元素序列为Skip的坦克。*/
/*将nSkip设为<0的值则不跳过，X、Y不在任一坦克内则返回NULL*/
PTANK InWhichTank(int nX, int nY, PTANK pTankArr, int nSkip)
{
	for (int i = 0; i < MAXTANK; ++i)
	{
		//遇到坦克不可见或指定要逃过的元素时，跳过
		if ((!pTankArr[i].nIsVisible) || i == nSkip)
			continue;
		switch (pTankArr[i].nDirect)
		{
		default:
			break;
		case UP:
			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY - 1))//头
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX - 1) &&
				(nY == pTankArr[i].nY))//左翼
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY))//中心
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX + 1) &&
				(nY == pTankArr[i].nY))//右翼
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX - 1) &&
				(nY == pTankArr[i].nY + 1))//左尾
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX + 1) &&
				(nY == pTankArr[i].nY + 1))//右尾
				return &(pTankArr[i]);

			break;
		case DOWN:
			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY + 1))//头
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX - 1) &&
				(nY == pTankArr[i].nY))//左翼
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY))//中心
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX + 1) &&
				(nY == pTankArr[i].nY))//右翼
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX - 1) &&
				(nY == pTankArr[i].nY - 1))//左尾
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX + 1) &&
				(nY == pTankArr[i].nY - 1))//右尾
				return &(pTankArr[i]);

			break;
		case LEFT:

			if ((nX == pTankArr[i].nX - 1) &&
				(nY == pTankArr[i].nY))//头
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY + 1))//左翼
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY))//中心
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY - 1))//右翼
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX + 1) &&
				(nY == pTankArr[i].nY + 1))//左尾
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX + 1) &&
				(nY == pTankArr[i].nY - 1))//右尾
				return &(pTankArr[i]);

			break;
		case RIGHT:

			if ((nX == pTankArr[i].nX + 1) &&
				(nY == pTankArr[i].nY))//头
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY - 1))//左翼
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY))//中心
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX) &&
				(nY == pTankArr[i].nY + 1))//右翼
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX - 1) &&
				(nY == pTankArr[i].nY - 1))//左尾
				return &(pTankArr[i]);

			if ((nX == pTankArr[i].nX - 1) &&
				(nY == pTankArr[i].nY + 1))//右尾
				return &(pTankArr[i]);
			break;
		}
	}

	/*不在任一坦克内，返回空*/
	return NULL;
}


/*遍历所有坦克元素*/
/*碰到则返回1，否则返回0*/
/*坦克的是否碰到另一个坦克,传入坦克数组指针、坦克属于的元素序列*/
int IsTankCrash(PTANK pTankArr, int nNum)
{
	/*通过坦克头、左翼、右翼，结合坦克运动方向进行判断*/
	switch (pTankArr[nNum].nDirect)
	{
	default:
		break;
	case UP:
		if (NULL != InWhichTank(pTankArr[nNum].nX, pTankArr[nNum].nY - 1, pTankArr, nNum))//头
			return 1;
		if (NULL != InWhichTank(pTankArr[nNum].nX - 1, pTankArr[nNum].nY, pTankArr, nNum))//左翼
			return 1;
		if (NULL != InWhichTank(pTankArr[nNum].nX + 1, pTankArr[nNum].nY, pTankArr, nNum))//右翼
			return 1;
		break;
	case DOWN:

		if (NULL != InWhichTank(pTankArr[nNum].nX, pTankArr[nNum].nY + 1, pTankArr, nNum))//头
			return 1;
		if (NULL != InWhichTank(pTankArr[nNum].nX - 1, pTankArr[nNum].nY, pTankArr, nNum))//左翼
			return 1;
		if (NULL != InWhichTank(pTankArr[nNum].nX + 1, pTankArr[nNum].nY, pTankArr, nNum))//右翼
			return 1;

		break;
	case LEFT:

		if (NULL != InWhichTank(pTankArr[nNum].nX - 1, pTankArr[nNum].nY, pTankArr, nNum))//头
			return 1;
		if (NULL != InWhichTank(pTankArr[nNum].nX, pTankArr[nNum].nY + 1, pTankArr, nNum))//左翼
			return 1;
		if (NULL != InWhichTank(pTankArr[nNum].nX, pTankArr[nNum].nY - 1, pTankArr, nNum))//右翼
			return 1;

		break;
	case RIGHT:

		if (NULL != InWhichTank(pTankArr[nNum].nX + 1, pTankArr[nNum].nY, pTankArr, nNum))//头
			return 1;
		if (NULL != InWhichTank(pTankArr[nNum].nX, pTankArr[nNum].nY - 1, pTankArr, nNum))//左翼
			return 1;
		if (NULL != InWhichTank(pTankArr[nNum].nX, pTankArr[nNum].nY + 1, pTankArr, nNum))//右翼
			return 1;

		break;
	}

	/*通过坦克头、左翼、右翼，结合坦克运动方向进行判断*/
	switch (pTankArr[nNum].nDirect)
	{
	default:
		break;
	case UP:
		if (g_cMap[pTankArr[nNum].nY - 1][pTankArr[nNum].nX] != MAP_NONE)//头
			return 1;
		if (g_cMap[pTankArr[nNum].nY][pTankArr[nNum].nX - 1] != MAP_NONE)//左翼
			return 1;
		if (g_cMap[pTankArr[nNum].nY][pTankArr[nNum].nX + 1] != MAP_NONE)//右翼
			return 1;
		break;
	case DOWN:

		if (g_cMap[pTankArr[nNum].nY + 1][pTankArr[nNum].nX]!= MAP_NONE)//头
			return 1;
		if (g_cMap[pTankArr[nNum].nY][pTankArr[nNum].nX - 1] != MAP_NONE)//左翼
			return 1;
		if (g_cMap[pTankArr[nNum].nY][pTankArr[nNum].nX + 1] != MAP_NONE)//右翼
			return 1;

		break;
	case LEFT:

		if (g_cMap[pTankArr[nNum].nY][pTankArr[nNum].nX - 1] != MAP_NONE)//头
			return 1;
		if (g_cMap[pTankArr[nNum].nY + 1][pTankArr[nNum].nX] != MAP_NONE)//左翼
			return 1;
		if (g_cMap[pTankArr[nNum].nY - 1][pTankArr[nNum].nX] != MAP_NONE)//右翼
			return 1;

		break;
	case RIGHT:

		if (g_cMap[pTankArr[nNum].nY][pTankArr[nNum].nX + 1] != MAP_NONE)//头
			return 1;
		if (g_cMap[pTankArr[nNum].nY - 1][pTankArr[nNum].nX] != MAP_NONE)//左翼
			return 1;
		if (g_cMap[pTankArr[nNum].nY + 1][pTankArr[nNum].nX] != MAP_NONE)//右翼
			return 1;

		break;
	}

	
	/*没有碰到返回0*/
	return 0;
}


/*让某一坦克往行进方向前进*/
/*传入坦克数组指针、行进方向、坦克属于的元素序列*/
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

	/*坦克出界则还原坐标并退出*/
	if (IsTankOOB(pTankArr, nNum))
	{
		pTankArr[nNum].nX = nX;
		pTankArr[nNum].nY = nY;
		return;
	}


	/*撞到其他坦克则还原坐标并退出*/
	if (IsTankCrash(pTankArr, nNum))
	{
		pTankArr[nNum].nX = nX;
		pTankArr[nNum].nY = nY;
		return;
	}

	pTankArr[nNum].nDirect = nDirect;

}

