#pragma once
#include "Data.h"


/*���ô�����Ϣ*/
void SetWindows();

/*��ʼ����Ϸ*/
void InitGame();

/*�ͷų�ʼ��ʱ����Ķѿռ�*/
void ReleaseAll();

/*��Ϸѭ����*/
void GameLoop();

/*��ʾ��Ϸ���˵�����,�����û�ѡ��*/
int MainMenu(HANDLE hOut);