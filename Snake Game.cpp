#include<bits/stdc++.h>
#include<conio.h>
using namespace std;

const int height = 20, width = 20;

class snake{
    public :
        bool gameover;
        int x, y, fruitX, fruitY, score = 0;
        enum direction
        {
            stop = 0,
            Left,
            Right,
            Up,
            Down
        };
        direction dir;
        int arrX[width * height];
        int arrY[width * height];

        void setup();
        void draw();
        void input();
        void logic();
};



void delay(int t)
{
    for(int i =0; i<t*1000000;i++){}
}
void snake :: setup()
{
    for(int i=0;i<width * height ; i++)
        arrX[i] = 0 , arrY[i] = 0;

    gameover = false;
    dir = stop;
    arrX[0] = (x = width/2);
    arrY[0] = (y = height/2);
    fruitX = rand() % width;
    fruitY = rand() % height;
}
void snake :: draw()
{
    system("cls");
    cout<<endl;
    cout<<"SCORE : "<<score<<"\n\n";
    cout<<endl;
    for(int i = 0 ; i < width + 2 ; i++)
    {
        cout<<"#";
    }
    cout<<endl;
    for(int i = 0 ; i <= height ; i++)
    {
        for(int j = -1 ; j <= width ; j++ )
        {
                if(j == -1 || j == width)
                {
                    cout<<"#";
                }
                else if(j == x && i == y)
                {
                    cout<<"O";
                }
                else if(j == fruitX &&  i == fruitY)
                {
                    cout<<"+";
                }
                else
                {
                    bool Print = true;
                    for(int k = 1; k <= score ; k++)
                    {
                        if(j == arrX[k] && i == arrY[k])
                        {
                            cout<<"o";
                            Print = false;
                        }
                    }
                    if(Print == true )
                    {
                        cout<<" ";
                    }
                }
        }
        cout<<endl;
    }
    for(int i = 0 ; i < width + 2 ; i++)
    {
        cout<<"#";
    }


}
void snake :: input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'w':
            dir = Up;
            break;
            case 's':
            dir = Down;
            break;
            case 'a':
            dir = Left;
            break;
            case 'd':
            dir = Right;
            break;
            case 'x':
            gameover = true;
            break;
            default:
            {}
        }
    }
}
void snake :: logic()
{
    arrX[0] = x;
    arrY[0] = y;
    switch(dir)
    {
        case Up:
        y--;
        break;
        case Down:
        y++;
        break;
        case Left:
        x--;
        break;
        case Right:
        x++;
        break;
        default:
        {}
    }
    for(int k = 1; k <= score ; k++)
    {
        if(arrX[k] == x && arrY[k] == y)
        {
            gameover = true;
        }
    }
    /*if(x >= width || x < 0 || y > height || y < 0)
    {
        gameover = true;
    }*/
    if(x >= width)
    {
        x=0;
    }
    else if(x < 0)
    {
        x = width- 1;
    }
    if(y > height)
    {
        y = 0;
    }
    else if(y < 0)
    {
        y = height;
    }

    if(x == fruitX && y == fruitY)
    {
        score++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
    for(int i=score; i > 0 ; i--)
    {
        arrX[i]=arrX[i-1];
        arrY[i]=arrY[i-1];
    }
    arrX[0] = x;
    arrY[0] = y;
}
int main()
{

    snake obj;
    obj.setup();


    while(!obj.gameover)
    {
        obj.draw();
        obj.input();
        obj.logic();
        delay(50);
    }
    obj.draw();
    cout<<endl;
    cout<<"GAME OVER !"<<endl;
    cout << "Your scores have been stored in the file" << endl;

    // Score = obj.score;

    ofstream score_file;
    score_file.open("scores.txt");

    score_file << "Your score is " << obj.score << '\n';

    score_file.close();

return 0;
}
