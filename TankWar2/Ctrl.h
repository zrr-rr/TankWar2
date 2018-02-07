#pragma once
#include "Data.h"


/*设置窗口信息*/
void SetWindows();

/*初始化游戏*/
void InitGame();

/*释放初始化时申请的堆空间*/
void ReleaseAll();

/*游戏循环体*/
void GameLoop();

/*显示游戏主菜单界面,返回用户选择*/
int MainMenu(HANDLE hOut);