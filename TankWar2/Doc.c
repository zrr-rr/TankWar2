#include "Doc.h"
#include "View.h"

/*����̹�˺��ӵ���Ϣ*/
void SaveTanknBullet(PTANK pTankArr,FILE *pFile) 
{
	if (pFile==NULL)
	{
		Error("�ļ�����ʧ��");
		return ;
	}

	//д��ȫ��̹�˵�����
	if (MAXTANK != fwrite(pTankArr, sizeof(TANK),
		MAXTANK, pFile))
	{
		Error("̹�˱���ʧ��");
		return ;
	}

	//д��ÿ��̹�˵��ӵ���
	for (int i=0;i<MAXTANK;++i)
	{
		if (MAXBULLET != fwrite((pTankArr[i].pBulletArr),
			sizeof(BULLET), MAXBULLET, pFile))
		{
			Error("�ӵ�����ʧ��");
			return ;
		}
	}

	Error("�ļ�����ɹ�");
	return ;
}

/*����̹�˺��ӵ���Ϣ*/
void LoadTanknBullet(PTANK *ppTankArr, FILE *pFile)
{
	if (pFile == NULL)
	{
		Error("�ļ�����ʧ��");
		return ;
	}

	//����ȫ��̹�˵Ķѿռ�
	PTANK pTank = (PTANK)malloc(sizeof(TANK)*MAXTANK);
	if (pTank==NULL)
	{
		Error("���뻺��ʧ��");
		return ;
	}
	

	//����ȫ��̹�˵�����
	if (MAXTANK != fread_s(pTank, sizeof(TANK)*MAXTANK, 
		sizeof(TANK), MAXTANK, pFile))
	{
		free(pTank);
		Error("̹�˼���ʧ��");
		return ;
	}

	/*��ÿ��̹�������ӵ�*/
	for (int i = 0; i < MAXTANK; ++i)
	{

		PBULLET pBullet = (PBULLET)malloc(sizeof(BULLET)*MAXBULLET);
		if (pBullet == NULL)
		{
			Error("���뻺��ʧ��");
			return ;
		}
		if (MAXBULLET != fread_s(pBullet, sizeof(BULLET)*MAXBULLET,
			sizeof(BULLET), MAXBULLET, pFile))
		{
			free(pBullet);
			Error("�ӵ�����ʧ��");
			return ;
		}

		pTank[i].pBulletArr = pBullet;
	}

	if (*ppTankArr != NULL)
		free(*ppTankArr);

	*ppTankArr = pTank;

	Error("�ļ����سɹ�");
	return ;
}

/*�����ͼ��Ϣ*/
void SaveMap(FILE *pFile)
{
	if (pFile == NULL)
	{
		Error("��ͼ����ʧ��");
		return;
	}
	//д��ȫ����ͼ����Ϣ
	for (int i=1;i<MAPROW-1;++i)
	{
		for (int j = 1; j < MAPCOL-1; ++j)
		{
			if (1 != fwrite(&(g_cMap[i][j]), sizeof(char),1, pFile))//���д��
			{
				Error("��ͼԪ�ر���ʧ��");
				return;
			}
		}
	}
}

/*���ص�ͼ��Ϣ*/
void LoadMap(FILE *pFile)
{
	if (pFile == NULL)
	{
		Error("��ͼ��ȡʧ��");
		return;
	}
	//д��ȫ����ͼ����Ϣ
	for (int i = 1; i < MAPROW-1; ++i)
	{
		for (int j = 1; j < MAPCOL-1; ++j)
		{
			if (1 != fread_s(&(g_cMap[i][j]), sizeof(char), sizeof(char), 1, pFile))//���ж�ȡ
			{
				Error("��ͼԪ�ض�ȡʧ��");
				return;
			}
		}
	}
}

/*�����ļ�*/
void SaveFile()
{
	FILE* pFile;
	fopen_s(&pFile, FILEPATH, "wb+");
	if (pFile==NULL)
	{
		Error("�ļ���ʧ��");
		return;
	}

	SaveTanknBullet(g_pTankArr, pFile);
	SaveMap(pFile);

	fclose(pFile);
}

/*�����ļ�*/
void LoadFile()
{
	FILE* pFile;
	fopen_s(&pFile, FILEPATH, "rb+");
	if (pFile == NULL)
	{
		Error("�ļ���ʧ��");
		return;
	}

	LoadTanknBullet(&g_pTankArr, pFile);
	LoadMap(pFile);

	fclose(pFile);
}