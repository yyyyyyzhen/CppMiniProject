#include <iostream>
#include "Game.h"

using namespace std;

int main( void ){
    /*常数 FILENAME 和 N 在 Game.h 文件中 */
    int nb = numberWords( FILENAME ); // 获得单词的个数
    Word list[nb]; // 声明一个 Word 型数组用来存放单词
    readWords( FILENAME, list ); // 将单词存入 list 数组

    Point ** mat = generateMatrix( N ); // 生成游戏用的矩阵并保存在 mat 中
    Command cmd; // 声明一个用于保存用户指令的变量 cmd
    int score = 0; // 声明并初始化得分，开始时为0分
    bool isBegin = false; // 指示游戏是否已经开始（可有可无）

    do{ // 游戏开始
        showMatrix( mat ); // 打印矩阵
        showWordsList( list ); // 打印单词列表
        if( isBegin ) // 第一次运行的时候不打印这句话（可有可无）
            cout << "Your score is " << score << endl; // 显示当前得分
        cmd = inputCommand( nb ); // 请求用户输入指令
        while( !isCommandValid( cmd, list, mat ) ){ // 输入的指令无效时运行 while 中的语句
            cout << "The command is invalid!" << endl;
            cmd = inputCommand( nb ); // 重新输入
        }
        gameProcess( cmd, mat, list ); // 修改矩阵
        score = gameScore( mat ); // 计算得分
        isBegin = true;
    }while( !isGameOver( mat, list ) ); // 游戏达到结束条件时退出 while 循环
    //showMatrix( mat );
    //showWordsList( list );
    cout << "The game is over, your final score is " << score << endl; // 输出最终得分，游戏结束
    freeMatrix( mat ); // 释放矩阵的内存

    return 0;
}
