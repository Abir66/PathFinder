# include "iGraphics.h"
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back

int screenWidth = 1280;
int screenHeight = 720;


int boxLength = 20;
int araX = screenWidth/boxLength;
int araY = screenHeight/boxLength;

int ara[70][40] = {0};

int boxType = 1;
int redx = 1280-160+10;
int bluex = 1280-160+10+50;
int blackx = 1280-160+10+100;

int gotblue = 0;
int gotred = 0;
int redxx = -1,redyy = -1, bluexx = -1, blueyy = -1;
int rightdown  = 0;


int checker = 0;
int checkerMessage = 0;
int oncePressed = 0;


vector<pair<int,int> > v;
int parentx[75][45] = {0};
int parenty[75][45] = {0};
int pathfound = 0;
int drawn = 0;
int vecsize = 0;
int taskFailed = 0;

void pathDraw()
{

    if(pathfound)
    {
        drawn = drawn + 2;
        drawn = min(drawn,vecsize);
    }

}


void bfspath(int vx, int vy)
{

    if(vx == bluexx && vy==blueyy)
        v.pb(mp(vx,vy));

    else
    {
        bfspath(parentx[vx][vy],parenty[vx][vy]);
        v.pb(mp(vx,vy));
    }

}

void bfs()
{

    int vis[75][45]= {0};
    int a[] = {0,0,1,-1};
    int b[] = {1,-1,0,0};

    queue<pair<int,int> > q;

    q.push(mp(bluexx,blueyy));
    vis[bluexx][blueyy] = 1;

    while(!q.empty())
    {

        int ux = q.front().first;
        int uy = q.front().second;
        q.pop();

        for(int i=0; i<4; i++)
        {

            if(ux+a[i]>=0 && uy+b[i]>=0 && ux+a[i]<araX && uy+b[i]<araY)
            {
                if(vis[ux+a[i]][uy+b[i]] == 0 && ara[ux+a[i]][uy+b[i]] != 1)
                {
                    int vx = ux+a[i];
                    int vy = uy+b[i];
                    vis[vx][vy] = 1;
                    q.push(mp(vx,vy));

                    parentx[vx][vy] = ux;
                    parenty[vx][vy] = uy;
                }
            }
        }

        if(vis[redxx][redyy]==1)
            break;

    }



    if(vis[redxx][redyy]==0)
    {
        pathfound = 0;
        taskFailed = 1;
    }
    else
    {
        pathfound = 1;
        bfspath(redxx,redyy);
        vecsize = v.size();

    }


}





void initializer()
{
    int i,j;
    for(i=0; i<araX; i++)
    {
        for(j=0; j<araY; j++)
        {
            ara[i][j] = 0;
        }
    }
    gotblue = 0;
    gotred = 0;
    redxx = -1,redyy = -1, bluexx = -1, blueyy = -1;
    rightdown  = 0;
    v.clear();
    pathfound = 0;
    drawn = 0;
    vecsize = 0;
    checker = 0;
    checkerMessage = 0;
    oncePressed = 0;
    taskFailed = 0;
}

int posConv(int a)
{
    return a/20;
}

void check()
{

    if(redxx == bluexx && redyy == blueyy)
    {
        gotblue = 0;
        bluexx = -1;
        blueyy = -1;
    }

    if(gotred && gotblue)
    {
        //trigger bfs here
        bfs();
    }
    else
    {
        pathfound = 0;
        checkerMessage = 1;
    }


}

void drawAra()
{
    int i,j;
    for(i=0; i<araX; i++)
    {
        for(j=0; j<araY; j++)
        {
            if(ara[i][j]==1)
            {
                iSetColor(50,50,50);
                iFilledRectangle(i*boxLength,j*boxLength,boxLength,boxLength);
            }
        }
    }


    if(gotblue)
    {
        iSetColor(52,152,219);
        iFilledRectangle(bluexx*boxLength,blueyy*boxLength,boxLength,boxLength);
    }

    if(gotred)
    {
        iSetColor(255,73,34);
        iFilledRectangle(redxx*boxLength,redyy*boxLength,boxLength,boxLength);
    }


}

void iDraw()
{
    iClear();

    //background
    iSetColor(255,255,255);
    iFilledRectangle(0,0,screenWidth,screenHeight);
    iSetColor(200,200,200);
    for(int i=0; i<=screenWidth; i = i+boxLength)
    {
        if(i<=screenHeight)
        {
            iLine(0,i,1280,i);
        }
        iLine(i,0,i,720);
    }


    iFilledRectangle(1280-160,0,160,60);
    iSetColor(244,208,63);
    iFilledRectangle(1270-50*boxType,0,60,60);
    iSetColor(255,73,34);
    iFilledRectangle(redx,10,40,40);
    //iSetColor(40,180,99);
    iSetColor(52,152,219);
    iFilledRectangle(bluex,10,40,40);
    iSetColor(50,50,50);
    iFilledRectangle(blackx,10,40,40);


    drawAra();

    if(checkerMessage)
    {
        iSetColor(0,0,0);
        if(!gotred && !gotblue)
            iText(10,10,"No Starting or Ending Point :(");
        else if(!gotblue)
            iText(10,10,"No starting point :(");
        else if(!gotred)
            iText(10,10,"No ending point :(");
        else if(!pathfound)
            iText(10,10,"Press Enter to find path");
    }

    if(oncePressed)
    {

        if(pathfound)
        {
            iSetColor(0,0,0);
            iText(10,10,"Press r to reset");
            iSetColor(255,0,0);
            int i,x,y;
            for(i=0; i<drawn; i++)
            {
                x = v[i].first*20;
                y = v[i].second*20;

                iFilledRectangle(x,y,20,20);

            }
        }
        else if(taskFailed)
        {
            iSetColor(0,0,0);
            iText(10,10,"sorry No path found");
        }
    }



}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{

    if(!(mx>=1280-160 && my<=60))
    {


        if(rightdown)
        {
            int x = posConv(mx);
            int y = posConv(my);

            ara[x][y] = 0;
            if(x==bluexx && y==blueyy)
            {
                gotblue = 0;
                bluexx = -1;
                blueyy = -1;
            }
            if(x==redxx && y==redyy)
            {
                gotred = 0;
                redxx = -1;
                redyy = -1;
            }

        }
        else if(boxType == 1)
        {
            ara[posConv(mx)][posConv(my)] = boxType;
        }

        else if(boxType == 2)
        {
            bluexx = posConv(mx);
            blueyy = posConv(my);
            gotblue = 1;
        }

        else if(boxType == 3)
        {
            redxx = posConv(mx);
            redyy = posConv(my);
            gotred = 1;
        }

    }

    taskFailed = 0;
    if(oncePressed)
    {
        v.clear();
        drawn = 0;
        check();
    }
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {


        if(!(mx>=1280-160 && my<=60))
        {

            if(boxType == 1)
            {
                if(ara[posConv(mx)][posConv(my)]==0)
                    ara[posConv(mx)][posConv(my)] = boxType;
            }

            else if(boxType == 2)
            {
                bluexx = posConv(mx);
                blueyy = posConv(my);
                gotblue = 1;
            }

            else if(boxType == 3)
            {
                redxx = posConv(mx);
                redyy = posConv(my);
                gotred = 1;

            }

        }

        else
        {

            if(mx>=redx && mx<=redx+40 && my>=10 && my<=50)
            {
                boxType = 3;
            }
            if(mx>=bluex && mx<=bluex+40 && my>=10 && my<=50)
            {
                boxType = 2;
            }
            if(mx>=blackx && mx<=blackx+40 && my>=10 && my<=50)
            {
                boxType = 1;
            }


        }


        taskFailed = 0;
        if(oncePressed)
        {
            v.clear();
            drawn = 0;
            check();
        }
    }

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {

        //place your codes here
        rightdown = 1;
        if(!(mx>=1280-160 && my<=60))
        {
            int x = posConv(mx);
            int y = posConv(my);

            ara[x][y] = 0;
            if(x==bluexx && y==blueyy)
            {
                gotblue = 0;
                bluexx = -1;
                blueyy = -1;
            }
            if(x==redxx && y==redyy)
            {
                gotred = 0;
                redxx = -1;
                redyy = -1;
            }

        }

        taskFailed = 0;
        if(oncePressed)
        {
            v.clear();
            drawn = 0;
            check();
        }
    }

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
    {
        if(rightdown)
        {
            rightdown = 0;
            boxType = 1;
        }
    }


}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(key == 13)
    {
        check();
        oncePressed = 1;
    }
    else if(key=='r' || key == 'R')
    {
        initializer();
    }
    else if(key == ' '){
        oncePressed = (oncePressed+1)%2;
    }
    else if(key==27){
        exit(0);
    }

}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{



    //place your codes for other keys here
}

int main()
{
    iSetTimer(25,pathDraw);
    iInitialize(screenWidth,screenHeight, "Path Finder");
    return 0;
}

