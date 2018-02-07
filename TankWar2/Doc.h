#pragma once
#include "Data.h"

/*保存坦克和子弹信息*/
void SaveTanknBullet(PTANK pTankArr, FILE *pFile);

/*加载坦克和子弹信息*/
void LoadTanknBullet(PTANK *ppTankArr, FILE *pFile);

/*保存地图信息*/
void SaveMap(FILE *pFile);

/*加载地图信息*/
void LoadMap(FILE *pFile);

/*保存文件*/
void SaveFile();

/*加载文件*/
void LoadFile();