#pragma once
#include "Data.h"

/*在标题处输出鼠标的X坐标，Y坐标*/
void OutPutPos(int nX, int nY);

/*响应鼠标消息的函数，只在编辑状态下被调用*/
void OnMouse(MOUSE_EVENT_RECORD mer);

/*编辑状态下的消息循环*/
void MapEditLoop();

/*输出右下角侧的提示信息*/
void MapRankMenu();