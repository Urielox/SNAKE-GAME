#include<iostream>
#include<windows.h>
#include<time.h>
#include<conio.h>
//Estableciendo perimetro de el chessboard
#define H 22
#define W 22
using namespace std;

//Declaraciones
class chessboard
{
public:
    char qp[H][W];
    int i,j,x1,y1;
    chessboard();
    void food();
    void prt(int grade,int score,int gamespeed);
 };
chessboard::chessboard()
{
    //Construyendo el chessboard 
    for(i=1;i<=H-2;i++)
        for(j=1;j<=W-2;j++)
            qp[i][j]=' ';
    for(i=0;i<=H-1;i++)
        qp[0][i] = qp[H-1][i] = '#';
    for(i=1;i<=H-2;i++)
        qp[i][0] = qp[i][W-1] = '#';
    food();
}
void chessboard::food()
//Estableciendo el comportamiento de la comida
{
    srand(time(0));
    do
    {
        x1=rand()%W-2+1;
        y1=rand()%H-2+1;
    }
    while(qp[x1][y1]!=' ');
    qp[x1][y1]='$';
}
void chessboard::prt(int grade,int score,int gamespeed)
//Estableciendo el nivel, el score y la velocidad del juego
{
    system("cls");
    cout << endl;
    for(i=0;i<H;i++)
    {
        cout << "\t";
        for(j=0;j<W;j++)
            cout<<qp[i][j]<<' ';
        if(i==0) cout << "\tNivel:" << grade;
        if(i==2) cout << "\tScore:" << score;
        if(i==4) cout << "\tVelocidad Automatica:";
        if(i==5) cout << "\tIntervalo de tiempo " << gamespeed << "ms";
        cout<<endl;
    }
}
class snake:public chessboard
//Creando la clase snake dentro del chessboard
{
public:
    int zb[2][100];
    long start;
    int head,tail,grade,score,gamespeed,length,timeover,x,y;
    char direction;
    bool play_again = true;
    snake();
    void move();
 };
snake::snake()
//Parametros iniciales de la snake
{
    cout<<"\n\n\t\tEl juego esta por comenzar"<<endl;
    for(i=3;i>=0;i--)
    {
        start=clock();
        while(clock()-start<=1000);
        system("cls");
        if(i>0)
        cout << "\n\n\t\tCuenta atras: " << i << endl;
    }
    for(i=1;i<=3;i++)
        qp[1][i]='*';
    qp[1][4]='@';
    for(i=0; i<4; i++)
    {
        zb[0][i] = 1;
        zb[1][i] = i + 1;
    }
}
void snake::move()
//estableciendo el movimiento de la snake
{
    score=0;
    head = 3,tail = 0;
    grade = 1, length = 4;
    gamespeed = 500;
    direction = 77;
    while(1)
    {
        timeover = 1;
        start = clock();
        while((timeover=(clock()-start<=gamespeed))&&!kbhit());
        if(timeover)
        {
            getch();
            direction = getch();
        }
        switch(direction)
        {
        case 72: x= zb[0][head]-1; y= zb[1][head];break;
        case 80: x= zb[0][head]+1; y= zb[1][head];break;
        case 75: x= zb[0][head]; y= zb[1][head]-1;break;
        case 77: x= zb[0][head]; y= zb[1][head]+1;break;
        }
        if(x==0 || x==21 ||y==0 || y==21)
        {
            cout << "\tGame over!" << endl;
            break;
        }
        if(qp[x][y]!=' '&&!(x==x1&&y==y1))
        {
            cout << "\tGame over!" << endl;
                break;
        }
        if(x==x1 && y==y1)
        {
            length ++;
            score=score+100;
            if(length>=8)
            {
                length -= 8;
                grade ++;
                if(gamespeed>=200)
                    gamespeed = 550 - grade * 50;
            }
            qp[x][y]= '@';
            qp[zb[0][head]][zb[1][head]] = '*';
            head = (head+1)%100;
            zb[0][head] = x;
            zb[1][head] = y;
            food();
            prt(grade,score,gamespeed);
        }
        else
        {
            qp[zb[0][tail]][zb[1][tail]]=' ';
            tail=(tail+1)%100;
            qp[zb[0][head]][zb[1][head]]='*';
            head=(head+1)%100;
            zb[0][head]=x;
            zb[1][head]=y;
            qp[zb[0][head]][zb[1][head]]='@';
            prt(grade,score,gamespeed);
        }
    }
}
int main()
//La funcion main donde todo se manda a llamar y se ejecuta
{
    chessboard cb;
    snake s;
    s.move();

    //El do while para volver a jugar
    bool play_again = true;
  while (play_again)
  {
    cout << "\nWant to play again (y / n)?" <<endl;
    char answer;
    std::cin >> answer;
    if (tolower(answer) == 'y')
    {
        chessboard cb;
        snake s;
        s.move();
    }
    if (tolower(answer) == 'n')
    {
        exit(EXIT_SUCCESS);   
    }
    else
    {
        cout << " That's not a valid option" << endl;
    }
  }
  return 0;
    
}
