#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>

using namespace std;

#define N 6 // 矩阵的大小为 NxN
#define FILENAME "F:\\CppMiniProject\\list.txt" // 存放单词的文件

typedef struct Point { // 矩阵中每个点都是 Point 类型的
    int value; // 点的数值，从0到9随机取值
    char letter; // 该点被选中时替换的字母，默认为 '0'
    bool flag; // 标志该点是否被占用，没有为 false，否则为 true
}Point;

typedef struct Word { // 每个从外部文件读取的单词都存放在为改类型
    int num; // 单词的序号
    string str; // 单词的字符串
    bool flag; // 标志该单词是否被占用，没有为 false，否则为 true
}Word;

typedef struct Command { // 用户输入的指令格式例如：3 v (2,3)
    int num; // 选择的单词的序号
    char dir; // 单词摆放的方向，横着：h，竖着：v
    int x; // 矩阵的行坐标
    int y; // 矩阵的列坐标
}Command;

/* 从文件中读取单词
    @ fName：文件名
    @ list：空的单词（Word）列表
    @ nb：单词的数量
    @ 无返回值
*/
void readWords( string fName, Word * list, int nb );

/* 获得单词的数量
    @ fName：文件名
    @ 返回单词的数量
*/
int numberWords( string fName );

/* 生成游戏用的矩阵（大小为 NxN）
    @ mat：一个指向 Point 类型的二维数组首元素的指针
    @ 无返回值
*/
Point ** generateMatrix( int n );

/* 打印出游戏用的矩阵
    @ mat：该矩阵
    @ 无返回值
*/
void showMatrix( Point ** mat );

/* 打印出供玩家选择的单词列表
    @ list：存放单词的数组
    @ 无返回值
*/
void showWordsList( Word * list );

/* 让用户输入，并从中读取游戏控制指令
    @ nb：单词的数量
    @ 返回一个 Command 类型的变量，即用户的指令
*/
Command inputCommand( int nb );

/* 判断输入的指令是否合法
    @ cmd：用户输入的指令
    @ list：单词列表
    @ mat：游戏用的矩阵
    @ 指令合法返回 true，否则返回 false
*/
bool isCommandValid( Command cmd, Word * list, Point ** mat );

/* 将矩阵中的数字替换为字母
    @ cmd：用户输入的指令
    @ mat：游戏用的矩阵
    @ list：存放单词的数组
    @ 无返回值
*/
void gameProcess( Command cmd, Point ** mat, Word * list );

/* 计算游戏得分
    @ mat：游戏用的矩阵
    @ 返回游戏的得分
*/
int gameScore( Point ** mat );

/* 判断游戏是否结束
    @ mat：游戏用的矩阵
    @ list：存放单词的数组
    @ 游戏结束返回 true，否则返回 false
*/
bool isGameOver( Point ** mat, Word * list );

/* 释放游戏用的矩阵的内存
    @ mat：矩阵
    @ 无返回值
*/
void freeMatrix( Point ** mat );

#endif
