#include "Doc.h"
#include "View.h"

/*保存坦克和子弹信息*/
void SaveTanknBullet(PTANK pTankArr,FILE *pFile) 
{
	if (pFile==NULL)
	{
		Error("文件保存失败");
		return ;
	}

	//写入全部坦克的资料
	if (MAXTANK != fwrite(pTankArr, sizeof(TANK),
		MAXTANK, pFile))
	{
		Error("坦克保存失败");
		return ;
	}

	//写入每个坦克的子弹组
	for (int i=0;i<MAXTANK;++i)
	{
		if (MAXBULLET != fwrite((pTankArr[i].pBulletArr),
			sizeof(BULLET), MAXBULLET, pFile))
		{
			Error("子弹保存失败");
			return ;
		}
	}

	Error("文件保存成功");
	return ;
}

/*加载坦克和子弹信息*/
void LoadTanknBullet(PTANK *ppTankArr, FILE *pFile)
{
	if (pFile == NULL)
	{
		Error("文件加载失败");
		return ;
	}

	//申请全部坦克的堆空间
	PTANK pTank = (PTANK)malloc(sizeof(TANK)*MAXTANK);
	if (pTank==NULL)
	{
		Error("申请缓存失败");
		return ;
	}
	

	//加载全部坦克的资料
	if (MAXTANK != fread_s(pTank, sizeof(TANK)*MAXTANK, 
		sizeof(TANK), MAXTANK, pFile))
	{
		free(pTank);
		Error("坦克加载失败");
		return ;
	}

	/*给每辆坦克申请子弹*/
	for (int i = 0; i < MAXTANK; ++i)
	{

		PBULLET pBullet = (PBULLET)malloc(sizeof(BULLET)*MAXBULLET);
		if (pBullet == NULL)
		{
			Error("申请缓存失败");
			return ;
		}
		if (MAXBULLET != fread_s(pBullet, sizeof(BULLET)*MAXBULLET,
			sizeof(BULLET), MAXBULLET, pFile))
		{
			free(pBullet);
			Error("子弹加载失败");
			return ;
		}

		pTank[i].pBulletArr = pBullet;
	}

	if (*ppTankArr != NULL)
		free(*ppTankArr);

	*ppTankArr = pTank;

	Error("文件加载成功");
	return ;
}

/*保存地图信息*/
void SaveMap(FILE *pFile)
{
	if (pFile == NULL)
	{
		Error("地图保存失败");
		return;
	}
	//写入全部地图的信息
	for (int i=1;i<MAPROW-1;++i)
	{
		for (int j = 1; j < MAPCOL-1; ++j)
		{
			if (1 != fwrite(&(g_cMap[i][j]), sizeof(char),1, pFile))//逐个写入
			{
				Error("地图元素保存失败");
				return;
			}
		}
	}
}

/*加载地图信息*/
void LoadMap(FILE *pFile)
{
	if (pFile == NULL)
	{
		Error("地图读取失败");
		return;
	}
	//写入全部地图的信息
	for (int i = 1; i < MAPROW-1; ++i)
	{
		for (int j = 1; j < MAPCOL-1; ++j)
		{
			if (1 != fread_s(&(g_cMap[i][j]), sizeof(char), sizeof(char), 1, pFile))//逐行读取
			{
				Error("地图元素读取失败");
				return;
			}
		}
	}
}

/*保存文件*/
void SaveFile()
{
	FILE* pFile;
	fopen_s(&pFile, FILEPATH, "wb+");
	if (pFile==NULL)
	{
		Error("文件打开失败");
		return;
	}

	SaveTanknBullet(g_pTankArr, pFile);
	SaveMap(pFile);

	fclose(pFile);
}

/*加载文件*/
void LoadFile()
{
	FILE* pFile;
	fopen_s(&pFile, FILEPATH, "rb+");
	if (pFile == NULL)
	{
		Error("文件打开失败");
		return;
	}

	LoadTanknBullet(&g_pTankArr, pFile);
	LoadMap(pFile);

	fclose(pFile);
}