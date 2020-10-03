// ifyou can't see the charactors Please SWITCH ENCODING to UTF-8 or UNINSTALL the ANCIENT EDITOR
// 这是一段测试字符：‖ × ■ □ ● ○ 

#include <iostream>
#include <cstdio>
#include <stack>
#include <cmath>
#include "stdio.h"
#include "TUIStyle.h"
#include "string.h"
#if defined(linux)
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#else
#include <windows.h>
#include <conio.h>
#endif
using namespace std;

// 珊格布局系统
string text_L(string text_String,int padding,int lg_Width,int md_Width,int sm_Width){
    int state=media_Quary(),col_Width;
    string res="";
    bool end_Flag=false;
    // 计算容器宽度
    if((state==1&&lg_Width<0)||
        (state==2&&md_Width<0)||
        (state==3&&sm_Width<0)
    )col_Width=cur_Width_12;
    else if(state==1)col_Width=cur_Width_1*lg_Width;
    else if(state==2)col_Width=cur_Width_1*md_Width;
    else col_Width=cur_Width_1*sm_Width;
    if((cur_len+col_Width==cur_Width_12)&&table_Mode)
        end_Flag=true;
    col_Width=col_Width-table_Mode+(end_Flag&&table_Mode);
    if(padding<0){
        res+=text_Rep("\b",-padding);
        col_Width-=padding;
        padding=0;
    }
    // 打印文字与容器宽度不够的处理
    if(1.0*text_String.length()+padding>col_Width){
        if(1.0*text_String.length()>col_Width)
            res=res+text_String.substr(0,col_Width-3)+"...";
        else
            res=res+text_Rep(" ",col_Width-1.0*text_String.length())+text_String;
    }
    else
        res=res+text_Rep(" ",padding)+text_String+text_Rep(" ",col_Width-padding-1.0*text_String.length());
    res+=(!end_Flag&&table_Mode)?inn_Ver_Symbol:"";
    res=make_Text(res);
    return res;
}

string text_M(string text_String,int padding,int lg_Width,int md_Width,int sm_Width){
    int state=media_Quary(),col_Width;
    bool end_Flag=false;
    string res="";
    // 计算容器宽度
    if((state==1&&lg_Width<0)||
        (state==2&&md_Width<0)||
        (state==3&&sm_Width<0)
    )col_Width=cur_Width_12;
    else if(state==1)col_Width=cur_Width_1*lg_Width;
    else if(state==2)col_Width=cur_Width_1*md_Width;
    else col_Width=cur_Width_1*sm_Width;
    if((cur_len+col_Width==cur_Width_12)&&table_Mode)
        end_Flag=true;
    col_Width=col_Width-table_Mode+(end_Flag&&table_Mode);
    if(1.0*text_String.length()+padding>col_Width){
        if(1.0*text_String.length()>col_Width)
            res=res+text_String.substr(0,col_Width-3)+"...";
        else
            res=res+text_Rep(" ",col_Width-1.0*text_String.length())+text_String;
    }
    else{
        // 构造左空格
        res+=text_Rep(" ",floor((col_Width-1.0*text_String.length())/2));
        res+=text_Rep(" ",padding);
        res+=text_String;
        col_Width-=padding+floor((col_Width-1.0*text_String.length())/2)+1.0*text_String.length();
        res+=text_Rep(" ",col_Width);
    }
    res+=(!end_Flag&&table_Mode)?inn_Ver_Symbol:"";
    res=make_Text(res);
    return res;
}

string text_R(string text_String,int padding,int lg_Width,int md_Width,int sm_Width){
    int state=media_Quary(),col_Width;
    bool end_Flag=false;
    string res="";
    // 计算容器宽度
    if((state==1&&lg_Width<0)||
        (state==2&&md_Width<0)||
        (state==3&&sm_Width<0)
    )col_Width=cur_Width_12;
    else if(state==1)col_Width=cur_Width_1*lg_Width;
    else if(state==2)col_Width=cur_Width_1*md_Width;
    else col_Width=cur_Width_1*sm_Width;
    if((cur_len+col_Width==cur_Width_12)&&table_Mode)
        end_Flag=true;
    col_Width=col_Width-table_Mode+(end_Flag&&table_Mode);
    if(padding==0&&1.0*text_String.length()>col_Width)
        res=res+text_String.substr(0,col_Width-3)+"...";
    else if(padding>0)
        res=text_Rep(" ",col_Width-1.0*text_String.length()-padding)+text_String+text_Rep(" ",padding);
    else
        res=text_Rep(" ",col_Width-1.0*text_String.length()-padding)+text_String+text_Rep(" ",padding);
    res+=(!end_Flag&&table_Mode)?inn_Ver_Symbol:"";
    res=make_Text(res);
    return res;
}

string begin_Table(){
    string res="";
    table_Mode=true;
    if(cur_len!=0)res=res+"\n";
    res=res+out_Ver_Symbol;
    cur_len=0;
    res=res+make_Outline();
    return res;
}

string end_Table(){
    string res="";
    if(cur_len!=0)res=res+new_Line();
    res=res+make_Outline();
    table_Mode=false;
    #if defined(linux)
        res=res+"\b";
    #else
        res=res+"\b\b";
    #endif
    return res;
}

string make_Outline(){
    string res="";
    media_Quary();
    #if defined(linux)
        res=res+"\b";
    #else
        res=res+"\b\b";
    #endif
    if(table_Mode)res=res+out_Con_Symbol+out_Hor_line+out_Con_Symbol;
    else res=res+out_Hor_Symbol+out_Hor_line+out_Hor_Symbol;
    lst_Line=true;
    cur_len=cur_Width_12;
    res=res+new_Line();
    return res;
}

string make_Inrline(){
    string res="";
    media_Quary();
    #if defined(linux)
        res=res+"\b";
    #else
        res=res+"\b\b";
    #endif
    if(table_Mode)res=res+inn_Con_Symbol+inn_Hor_line+inn_Con_Symbol;
    else res=res+inn_Hor_Symbol+inn_Hor_line+inn_Hor_Symbol;
    lst_Line=true;
    cur_len=cur_Width_12;
    res=res+new_Line();
    return res;
}

string new_Line(){
    string res;
    media_Quary();
    res=res+text_Rep(" ",cur_Width_12-cur_len);
    if(table_Mode&&!lst_Line)res=res+out_Ver_Symbol;
    lst_Line=false;
    res=res+"\n";
    if(table_Mode)res=res+out_Ver_Symbol;
    cur_len=0;
    return res;
}

string col_Check(int len){
    media_Quary();
    string res="";
    if(cur_len+len>cur_Width_12&&!discrib_Mode)res=res+new_Line();
    return res;
}

// 列表系统
string begin_List(string type){
    string res="";
    if(cur_len!=0)res+=new_Line();
    int deep=sig_Stake.empty()?0:sig_Stake.top().first+1;
    int num=type=="ul"?-1:0;
    sig_Stake.push(make_pair(deep,num));
    return res;
}

string end_List(){
    if(!sig_Stake.empty())sig_Stake.pop();
    else cout<<"!***Pairing Failed***!"<<endl;
    return "";
}

string make_List(string v){
    if(sig_Stake.empty())return "!***Missing list environment***!\n";
    pair<int,int> top=sig_Stake.top();
    sig_Stake.pop();
    if(top.second!=-1)top.second++;
    sig_Stake.push(top);
    string res="";
    res=res+text_Rep("    ",top.first);
    if(top.second==-1){
        if(top.first==0)res+="■ ";
        else if(top.first==1)res+="□ ";
        else if(top.first==2)res+="● ";
        else if(top.first==3)res+="○ ";
        else res+="~ ";
    }
    else
        res+=int_To_String(top.second)+". ";
    res=res+v+"\n";
    return res;
}

// 定义or描述
string make_Describ(string words,string discrib){
    string res="";
    discrib_Mode=true;
    int state=media_Quary();
    res=res+new_Line();
    while (true){
        res+=text_L(words,0,1,1,2);
        words="";
        if(state==3){
            if(discrib.length()<=cur_Width_10){
                res=res+text_L(discrib,0,11,11,10)+"\n";
                break;
            }
            res=res+text_L(discrib.substr(0,cur_Width_10),0,11,11,10);
            discrib=discrib.substr(cur_Width_10);
            res+="\n";
        }
        else {
            if(discrib.length()<=cur_Width_11){
                res=res+text_L(discrib,0,11,11,11)+"\n";
                break;
            }
            res=res+text_L(discrib.substr(0,cur_Width_11),11,11,10);
            discrib=discrib.substr(cur_Width_11);
            res+="\n";
        }
    }
    discrib_Mode=false;

    return res;
}

string make_Long_Describ(string words,string discrib){
    new_Line();
    discrib_Mode=true;
    string res=text_L(words,0,12,12,12)+"\n";
    while (true){
        if(discrib.length()<=cur_Width_12){
            res=res+text_L(discrib,0,12,12,12)+"\n";
            break;
        }
        res=res+text_L(discrib.substr(0,cur_Width_12));
        discrib=discrib.substr(cur_Width_12+1);
        res+="\n";
    }
    discrib_Mode=false;
    return res;
}

// 输入框
string load_Input(string key,string type,int len){
    media_Quary();
    len=cur_Width_4;
    string sym=" ",res="";
    if(type=="normal")sym="   ";
    else if(type=="username")sym=" @ ";
    else if(type=="password")sym=" $ ";
    else sym=" "+type+" ";
    if(key!="")res+=text_L(key,0,1,2,2);
    res+=sym;
    cout<<res;res="";
    if(type=="password"){
        char tmp;
        while (true){
            #if defined(linux)
                tmp=mygetch();
            #else
                tmp=getch();
            #endif
            if(tmp=='\n'||tmp=='\r'){cout<<endl;break;}
            res+=tmp;
            cout<<"*";
        }
    }
    else cin>>res;
    return res;
}

// 选框
string make_Check_Box(string title,string msg,string butA,string butB,string butC,string butD){
    int lg_old=col_lg_width;
    int md_old=col_md_width;
    int sm_old=col_sm_width;
    col_lg_width=col_lg_width/4+6;
    col_md_width=col_md_width/3-4;
    col_sm_width=col_sm_width/2;
    int state=media_Quary();
    string res="";
    res=res+begin_Table();
    res=res+text_L(title,0,12,12,12);res=res+new_Line();res=res+make_Outline();
    while (true){
        if(msg.length()<=cur_Width_12){
            res=res+text_L(msg);
            res=res+new_Line();
            break;
        }
        res=res+text_L(msg.substr(0,cur_Width_12));
        msg=msg.substr(cur_Width_11+1);
        res+=new_Line();
    }
    if(butA=="");
    else if(butB==""){
        res=res+make_Inrline();
        res=res+text_M(butA,0,12,12,12);
    }
    else if(butC==""){
        res=res+make_Inrline();
        res=res+text_M(butA,0,6,6,6);
        res=res+text_M(butB,0,6,6,6);
    }
    else if(butD==""){
        res=res+make_Inrline();
        res=res+text_M(butA,0,4,4,4);
        res=res+text_M(butB,0,4,4,4);
        res=res+text_M(butC,0,4,4,4);
    }
    else {
        res=res+make_Inrline();
        res=res+text_M(butA,0,3,3,3);
        res=res+text_M(butB,0,3,3,3);
        res=res+text_M(butC,0,3,3,3);
        res=res+text_M(butC,0,3,3,3);
    }
    res=res+new_Line();
    res=res+end_Table();
    col_lg_width=lg_old;
    col_md_width=md_old;
    col_sm_width=sm_old;
    return res;
}

// 菜单
int load_Menu(string menu[],int len){
    while (true){
        load_Clear();
        int num;
        cout<<begin_Table()<<text_L(menu_Notes[0],0,12,12,12)<<new_Line()<<make_Inrline();
        for (num=1;num<=len&&menu[num-1].length()!=0;num++)
            cout<<text_L(int_To_String(num)+". "+menu[num-1],0,12,12,12)<<new_Line();
        cout<<end_Table();
        int res=string_To_Int(load_Input(">>>","normal",10));
        if(res>num||res<=0){new_Line();continue;}
        return res;
    }
}

// 其他组件
#if defined(linux)
pair<int,int> get_Tty_Size(){
    struct winsize w;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&w);
    return make_pair(w.ws_row,w.ws_col);
}
#else
pair<int,int> get_Tty_Size(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns,rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
    columns=csbi.srWindow.Right-csbi.srWindow.Left+1;
    rows=csbi.srWindow.Bottom-csbi.srWindow.Top+1;
    return make_pair(rows,columns);
}
#endif

int media_Quary(){
    int tty_Width=get_Tty_Size().second;
    if(tty_Width>=col_lg_min){load_Init(col_lg_width);return 1;}
    else if(tty_Width>=col_md_min){load_Init(col_md_width);return 2;}
    else if(tty_Width>=col_sm_min){load_Init(col_sm_width);return 3;}
    else {
        cout<<"Current Window is TOO Small to Show Program"<<endl
            <<"Window Width="<<tty_Width<<"<"<<col_sm_min<<endl
            <<"Please Resize And Press Enter"<<endl;
        load_Pause();
        return media_Quary();
    }
}

inline string text_Rep(string s,int num){
    string res="";
    if(num<0){s=text_Rep("\b",s.length());num=-num;}
    for (int i=0;i<num;i++)
        res+=s;
    return res;
}

void load_Init(int width){
    cur_Width_1=width/12;
    cur_Width_2=cur_Width_1*2;
    cur_Width_3=cur_Width_1*3;
    cur_Width_4=cur_Width_1*4;
    cur_Width_5=cur_Width_1*5;
    cur_Width_6=cur_Width_1*6;
    cur_Width_7=cur_Width_1*7;
    cur_Width_8=cur_Width_1*8;
    cur_Width_9=cur_Width_1*9;
    cur_Width_10=cur_Width_1*10;
    cur_Width_11=cur_Width_1*11;
    cur_Width_12=cur_Width_1*12;
    inn_Hor_line=text_Rep(inn_Hor_Symbol,width);
    out_Hor_line=text_Rep(out_Hor_Symbol,width);
    return;
}

string make_Text(string s){
    int pain_Width=str_Pain_Width(s);
    s=col_Check(str_Pain_Width(s))+s;
    cur_len+=pain_Width;
    return s;
}

void load_Pause(){
    #if defined(linux)
        cout<<"Press Enter Continue";
        getchar();getchar();
    #elif defined(Q_OS_MAC)
        getchar();
        system("pause");
    #elif defined(Q_WS_WIN)
        getchar();
        system("pause");
    #else
        // 兜底
        cout<<"Press Enter Continue";
        getchar();getchar();
    #endif
    return;
}

void load_Clear(){
    #if defined(linux)
        system("clear");
    #elif defined(Q_OS_MAC)
        system("clear");
    #elif defined(Q_WS_WIN)
        system("cls");
    #else
        system("cls");
    #endif
        media_Quary();
    return;
}

int str_Pain_Width(string s){
    int res=s.length();
    for (int i=0;i<1.0*s.length();i++)
        if(s[i]=='\b')
            res -= 2;
    return res;
}

string int_To_String(int v){
    if(v==0)return "0";
    string s="";
    bool f=v<0;v=abs(v);
    while (v){
        s=char('0'+v % 10)+s;
        v/=10;
    }
    return (f?"-":"")+s;
}

int string_To_Int(string s){
    int res=0,f=1,cur=0;
    for (cur=0;cur<s.length()&&s[cur]!='-'&&s[cur]<'0'&&s[cur]>'9';cur++);
    if(s[cur]=='-'){f=-1;cur++;}
    for (;cur<s.length()&&s[cur]>='0'&&s[cur]<='9';cur++)
        res=res*10+s[cur]-'0';
    return res*f;
}

#if defined(linux)
char mygetch(){
    struct termios oldt,newt;
    int ch;
    tcgetattr(STDIN_FILENO,&oldt);
    newt=oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&newt);
    ch=getchar();
    tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
    return ch;
}
#endif

// 都0202年,Windows 的powerShell,cmd,Terminal(UWP)还是默认gb2312,尊贵的linux怎么会有这种问题呢
void encode_Fix(){
    #if defined(linux)
        return;
    #endif
    system("chcp 65001");
    // 下面这一行是是处理Windows适配的，其中
    // 外边框角设置为 "﹢" Terminal(UWP)不适配 powershell不适配  cmd不适配 直接运行程序适配
    // 外边框角设置为 "×"  Terminal(UWP)  适配 powershell不适配 cmd适配 直接运行程序适配
    inn_Con_Symbol="﹢";
    load_Clear();
    #if defined(_MSC_VER)
    if (vswaring) {
        cout << "Because Visual Studio uses its unique compiler, even if I try to improve the compatibility of the style library, the style library still cannot run normally, please change the editor or use g++ to compile, for example" << endl;
        cout << "g++ *.cc *.cpp -o main\nThis prompt will be displayed here only once, if you need to permanently shield the definition, please call `vswaring=false` before calling `encode_Fix()`"<<endl;
        load_Pause();
        load_Clear();
    }
    #endif
}

// examples
int demo_1(){
    cout<<make_Text("Grid layout automatically avoids context");
    cout
        <<begin_Table()
                <<text_M("Here is a demo for Grid layout",0,12,12,12)
            <<new_Line()
            <<make_Inrline()
                <<text_M("different width",0,12,12,12)
            <<new_Line()
                <<text_L("1/12",0,1,1,1)
                <<text_L("1/6",0,2,2,2)
                <<text_L("1/3",0,4,4,4)
                <<text_L("5/12",0,5,5,5)
            <<new_Line()
            <<make_Inrline()
                <<text_M("different Position",0,12,12,12)
            <<new_Line()
                <<text_L("Left",0,4,4,4)
                <<text_M("Middle",0,4,4,4)
                <<text_R("Right",0,4,4,4)
            <<new_Line()
            <<make_Inrline()
                <<text_M("Postive&negative offset",0,12,12,12)
            <<new_Line()
                <<text_M("Middle -2",-2,3,3,3)
                <<text_M("Middle +2",2,3,3,3)
                <<text_M("Space",0,3,3,3)
                <<text_L("Left -2",-2,3,3,3)
                <<text_L("Left +2",2,3,3,3)
                <<text_R("Right +2",2,3,3,3)
                <<text_R("Right -2",-2,3,3,3)
                <<text_M("bound Allow",0,3,3,3)
            <<new_Line()
            <<make_Inrline()
                <<text_M("overfall hide & auto complete & auto wrap",0,12,12,12)
                <<text_L("Long Text Long Text Long Text Long Text Long Text ",0,4,4,4)
                <<text_L("Long Text Long Text Long Text Long Text Long Text ",0,4,4,4)
                <<text_L("Auto Wrap Auto Wrap Auto Wrap Auto Wrap Auto Wrap  ",0,4,4,4)
                <<text_L("auto complete auto complete auto complete auto complete",0,4,4,4)
        <<end_Table();
    return 0;
}

int demo_2(){
    cout<<make_Text("Grid layout automatically avoids context");
    cout
        <<begin_List("ul")
            <<make_List("aaaaaaaaaaaaa")
            <<make_List("bbbbbbbbbbbbb")
            <<begin_List("ol")
                <<make_List("cccccccccccc")
                <<make_List("dddddddddddd")
                <<begin_List("ul")
                    <<make_List("eeeeeeeeeeee")
                    <<make_List("ffffffffffff")
                    <<make_List("gggggggggggg")
                    <<make_List("hhhhhhhhhhhh")
                <<end_List()
                <<make_List("iiiiiiiiiiii")
                <<make_List("jjjjjjjjjjjj")
            <<end_List()
            <<make_List("kkkkkkkkkkk")
            <<make_List("lllllllllll")
        <<end_List();
    return 0;
}

int demo_3(){
    cout<<make_Describ("BootStrap","A free and open-source CSS framework directed at responsive, mobile-first front-end web development. It contains CSS- and (optionally) JavaScript-based design templates for typography, forms, buttons, navigation, and other interface components.Bootstrap is the seventh-most-starred project on GitHub, with more than 142,000 stars, behind freeCodeCamp (almost 312,000 stars) and marginally behind Vue.js framework.[2]");
    cout<<make_Long_Describ("BootStrap","Bootstrap is a web framework that focuses on simplifying the development of informative web pages (as opposed to web apps). The primary purpose of adding it to a web project is to apply Bootstrap's choices of color, size, font and layout to that project. As such, the primary factor is whether the developers in charge find those choices to their liking. Once added to a project, Bootstrap provides basic style defin");
    return 0;
}

int demo_4(){
    string a,b,c,d;
    a=load_Input("PassWord","password",10);
    b=load_Input("Name","username",10);
    c=load_Input("text","normal",10);
    d=load_Input("Addr","&",10);
    cout<<a<<"\t"<<b<<"\t"<<b<<"\t"<<d<<endl;
    return 0;
}

int demo_5(){
    cout<<make_Check_Box("Waring","This library cannot run perfectly on the lc compilation of Visual Studio!! This library cannot run perfectly on the lc compilation of Visual Studio!! This library cannot run perfectly on the lc compilation of Visual Studio!!","OK","Why","Not Show");
    return 0;
}

int demo_6(){
    string tmp[]={
        "You can choose me",
        "You can choose me",
        "You can choose me",
        "You can choose me",
        "You can choose me",
        "You can choose me",
    };
    cout<<load_Menu(tmp,6);
    return 0;
}

// int main(){
//     encode_Fix();
//     demo_();
//     load_Pause();
// }