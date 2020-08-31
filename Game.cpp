#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Game.h"

using namespace std;

void readWords( string fName, Word * list, int nb ){
    ifstream infile;
    int counter = 0;
    infile.open( fName, ios :: in );
    if ( !infile ){
        cout << "Open file fail!" << endl;
        exit(1);
    }
    else{
        while( !infile.eof( ) && counter != nb ){
            getline( infile, list[counter].str );
            list[counter].num = counter + 1;
            list[counter].flag = false;
            counter++;
        }
    }
    infile.close( );
}

int numberWords( string fName ){
    ifstream infile;
    string s;
    int counter = 0;
    infile.open( fName, ios :: in );
    if ( !infile ){
        cout << "Open file fail!" << endl;
        exit( 1 );
    }
    else{
        while( !infile.eof( ) ){
            getline( infile, s );
            counter++;
        }
    }
    infile.close( );
    return counter;
}

Point ** generateMatrix( int n ){
    Point ** mat;
    mat = ( Point ** )malloc( n * sizeof( Point ) );
    for( int i = 0; i < N; i++ )
        mat[i] = ( Point * )malloc( n * sizeof( Point ) );
    srand( ( unsigned )time( NULL ) );
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            mat[i][j].value = rand( ) % 10 + 0; // 生成0到9的随机数
            mat[i][j].letter = 0;
            mat[i][j].flag = false;
        }
    }
    return mat;
}

void freeMatrix( Point ** mat){
    for( int i = 0; i < N; i++ )
        free( mat[i] );
    free( mat );
}

void showMatrix( Point ** mat ){
    for( int i = 0; i < N; i++ ){
        cout << "| ";
        for( int j = 0; j < N; j++ ){
            if( mat[i][j].flag )
                cout << mat[i][j].letter << " ";
            else
                cout << mat[i][j].value << " ";
        }
        cout << "|" << endl;
    }
}

void showWordsList( Word * list ){
    int l = numberWords( FILENAME );
    for( int i = 0; i < l; i++ ){
        if( !list[i].flag ){
            string str = ( i != l - 1 ) ? ", " : "\n";
            cout << "(" << list[i].num << ")" << list[i].str << str;
        }
    }
}

Command inputCommand( int nb ){
    Command cmd;
    int num, x, y;
    char dir;
    bool isValid;
    cout << "Please input your command";
    do{
        cout << "(word number(1~" << numberWords(FILENAME) << "), display mode(v/h), ";
        cout << "numbers of row and column" << "(0~" << N - 1 << ")):" << endl;
        cin >> num >> dir >> x >> y;
        /* 检查输入指令的格式和范围是否正确 */
        if( (num < 1 || num > nb) || (dir != 'v' && dir != 'h') || (x < 0 || x > N - 1) || (y < 0 || y > N - 1) ){
            isValid = false;
            cout << "The command is invalid!" << endl << "Please input your command";
        }
        else
            isValid = true;
    }while( !isValid );
    cmd.num = num; cmd.dir = dir; cmd.x = x; cmd.y = y;
    return cmd;
}

bool isCommandValid( Command cmd, Word * list, Point ** mat ){
    bool isValid = false;
    /* 判断是否选择了重复的单词 */
    if( list[cmd.num - 1].flag )
        return isValid;
    if( cmd.dir == 'v' ){
        /* 判断选中的单词会不会超出矩阵的范围 */
        if( ( unsigned )( N - cmd.x ) < list[cmd.num - 1].str.length( ) )
            return isValid;
        /* 判断选中的单词会不会与已经在矩阵中的单词重叠 */
        else{
            for( unsigned int i = cmd.x; i < list[cmd.num - 1].str.length( ); i++ ){
                if( mat[i][cmd.y].flag )
                    return isValid;
            }
        }
    }
    else{
        if( ( unsigned )( N - cmd.y ) < list[cmd.num - 1].str.length( ) )
            return isValid;
        else{
            for( unsigned int i = cmd.y; i < list[cmd.num - 1].str.length( ); i++ ){
                if( mat[cmd.x][i].flag )
                    return isValid;
            }
        }
    }
    isValid = true;
    return isValid;
}

void gameProcess( Command cmd, Point ** mat, Word * list ){
    list[cmd.num - 1].flag = true;
    if( cmd.dir == 'v' ){
        int j = 0;
        for( unsigned int i = cmd.x; i < ( list[cmd.num - 1].str.length( ) + cmd.x ); i++ ){
            mat[i][cmd.y].letter = list[cmd.num - 1].str[j];
            mat[i][cmd.y].flag = true;
            j++;
        }
    }
    else{
        int j = 0;
        for( unsigned int i = cmd.y; i < ( list[cmd.num - 1].str.length( ) + cmd.y ); i++ ){
            mat[cmd.x][i].letter = list[cmd.num - 1].str[j];
            mat[cmd.x][i].flag = true;
            j++;
        }
    }
}

int gameScore( Point ** mat ){
    int score = 0;
    for( int i = 0; i < N; i++ ){
        for( int j = 0; j < N; j++ ){
            if( mat[i][j].flag )
                score += mat[i][j].value;
        }
    }
    return score;
}

int minWord( Word * list, int nb ){
    unsigned int min = 0;
    int i = 0;
    while( list[i].flag && i != nb )
        i++;
    min = list[i].str.length( );
    for( int i = 0; i < nb; i++ ){
        if( !list[i].flag ){
            if( min >= list[i].str.length( ) )
                min = list[i].str.length( );
        }
    }
    return min;
}

bool isAllWordsUsed( Word * list, int nb ){
    int counter = 0;
    for( int i = 0; i < nb; i++ ){
        if( list[i].flag )
            counter++;
    }
    return ( counter == nb ) ? true : false;
}

int maxLineInter( Point * mat ){
    int max = 0;
    int counter = 0;
    for( int i = 0; i <= N; i++ ){
        if( !mat[i].flag && i != N )
            counter++;
        else{
            if( max <= counter )
                max = counter;
            counter = 0;
        }
    }
    return max;
}
int maxInterHorizontal( Point ** mat ){
    int max = 0;
    for( int i = 0; i < N; i++ ){
        int maxL = maxLineInter( mat[i] );
        if( max <= maxL )
            max = maxL;
    }
    return max;
}

int maxInterVertical( Point ** mat ){
    int max = 0;
    Point temp[N];
    for( int i = 0; i < N; i++ ){
        for( int j = 0; j < N; j++ )
            temp[j] = mat[j][i];
        int maxC = maxLineInter( temp );
        if( max <= maxC )
            max = maxC;
    }
    return max;
}

int maxInterval( Point ** mat ){
    int hmax = maxInterHorizontal( mat );
    int vmax = maxInterVertical( mat );
    return ( hmax > vmax ) ? hmax : vmax;
}

bool isGameOver( Point ** mat, Word * list ){
    bool isEnd = false;
    int nb = numberWords( FILENAME );
    if( ( maxInterval( mat ) < minWord( list, nb ) ) || isAllWordsUsed( list, nb ) )
        isEnd = true;
    return isEnd;
}
