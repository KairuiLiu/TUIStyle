#ifndef TUISTYLE_H
#define TUISTYLE_H
#include <iostream>
#include <cstdio>
#include <stack>
#include <cmath>
#include "stdio.h"
#include "string.h"
#include "TUIStyle.h"
#if defined(linux)
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#else
#include <windows.h>
#include <conio.h>
#endif
using namespace std;

// 珊格布局
int col_lg_width = 168;
int col_md_width = 120;
int col_sm_width = 72;
int col_lg_min = 187;
int col_md_min = 134;
int col_sm_min = 80;
int cur_len = 0;
int cur_Width_12, cur_Width_11, cur_Width_10,
cur_Width_9, cur_Width_8, cur_Width_7,
cur_Width_6, cur_Width_5, cur_Width_4,
cur_Width_3, cur_Width_2, cur_Width_1;

bool table_Mode, lst_Line,vswaring=true;

string out_Hor_Symbol = "=", out_Ver_Symbol = "‖", out_Con_Symbol = "×",
inn_Hor_Symbol = "-", inn_Ver_Symbol = "|", inn_Con_Symbol = "+";
string out_Hor_line, inn_Hor_line;

// ＋

// 珊格系统组件
string text_L(string text_String, int padding = 0, int lg_Width = -1, int md_Width = -1, int sm_Width = -1);
string text_M(string text_String, int padding = 0, int lg_Width = -1, int md_Width = -1, int sm_Width = -1);
string text_R(string text_String, int padding = 0, int lg_Width = -1, int md_Width = -1, int sm_Width = -1);

string begin_Table();
string end_Table();
string make_Outline();
string make_Inrline();
string new_Line();
string col_Check(int);

// 列表
stack<pair<int, int> >sig_Stake;
string begin_List(string type);
string end_List();
string make_List(string);

// 描述
bool discrib_Mode = false;
string make_Describ(string, string);
string make_Long_Describ(string, string);

// 输入框
string load_Input(string key = "", string type = "normal", int length = -1);

// 选框
string make_Check_Box(string title, string msg, string butA = "", string butB = "", string butC = "", string butD = "");

// 简陋的菜单
// Todo 下个版本迭代函数指针(希望不大)
int load_Menu(string menu[], int);

// 基本操作
pair<int, int> get_Tty_Size();
int media_Quary();
inline string text_Rep(string, int);
void load_Init(int);
string make_Text(string);
void load_Pause();
void load_Clear();
int str_Pain_Width(string);
string int_To_String(int);
int string_To_Int(string);
char mygetch();
string menu_Notes[20]{
    "Input Number To Choose"
};
#endif // TUISTYLE_H