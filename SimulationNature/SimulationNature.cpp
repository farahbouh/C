#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <Grapic.h>

using namespace grapic;
using namespace std;

const int DIMW = 200;
const float dt = 0.4;
const float friction = 0.9;
const int MAX=DIMW;

struct Color
{
    unsigned char r,g,b;
};

Color operator+(Color a, Color b)
{
    Color c;

    c.r=a.r+b.r;
    c.g=a.g+b.g;
    c.b=a.b+b.b;
    return c;
}

Color operator*(Color a, Color b)
{
    Color c;
    c.r=a.r*b.r;
    c.g=a.g*b.g;
    c.b=a.b*b.b;
    return c;
}

Color operator*(Color a, float b)
{
    Color c;
    c.r=a.r*b;
    c.g=a.g*b;
    c.b=a.b*b;
    return c;
}

Color operator/(Color a, Color b)
{
    Color c;
    c.r=a.r/b.r;
    c.g=a.g/b.g;
    c.b=a.b/b.b;
    return c;
}

Color make_color(unsigned r, unsigned g, unsigned b)
{
    Color c;
    c.r=r;
    c.g=g;
    c.b=b;
    return c;
}

/////////////////////////////////////////////////////////
struct element
{
    // 0 aire   1 gaz     2 liquide 3 solide
    // 4 plante 5 terre   6 mort
    // 7 rocher 8 abeille 9 fleur   10 lave
    float etat;
    float t=0; // temps passé
    Color c;
};

struct world
{
    element t[MAX][MAX];
    int nb;
    int dx, dy;
};

//////////////// fonctions annexes ////////////////////
void etat(element &e)
{
    int t;
    Color a, b, c;
    if (e.etat==0) // aire
    {
        e.c=make_color(0, 0, 0);
    }

    if (e.etat==2) // liquide
    {
        e.c=make_color(0, 0, 254);
    }

    if (e.etat==1) // gaz
    {
        e.c=make_color(105,238,238);
    }

    if (e.etat==3) // solide
    {
        e.c=make_color(255, 255,255);
    }
    if (e.etat==4) // plante
    {
        e.c=make_color(0,128,0);
    }
    if (e.etat==5) // terre (ajout de rand = relief)
    {
        a=make_color(139,69,19);
        b=make_color(160,82,45);
        c=make_color(205,133,63);
        t=rand()%3;

        if (t==0)
        {
            e.c=a;
        }
        if (t==1)
        {
            e.c=b;
        }
        if (t==2)
        {
            e.c=c;
        }
    }
    if (e.etat==6) //mort
    {
        a=make_color(184,134,11);
        c=make_color(255,140,0);
        b=make_color(255,165,0);
        t=rand()%2;

        if (t==0)
        {
            e.c=a;
        }
        if (t==1)
        {
            e.c=b;
        }
        if (t==2)
        {
            e.c=c;
        }
    }
    if (e.etat==8) // abeille
    {
        e.c=make_color(255,255,0);
    }
    if (e.etat==9) // fleur
    {
        e.c=make_color(255,182,193);
    }
}
void newetat(element &e, int newetat)
{
    e.etat=newetat;
    etat(e);
}


void contactinter(element &a, element &b)
{
    // si a gazeuse et b liquide alors 2 b liquide
    if ((a.etat==1) and (b.etat==2))
    {
        newetat(b, 2);
        newetat(a, 2);
    }

    // si a liquide et b solide alors a solide ou liquide
    if ((a.etat==2) and (b.etat==3))
    {
        if ((rand()%2)==0)
        {
            newetat(a, 3);
            a.t+=1;
        }
        if ((rand()%3)==1)
        {
            newetat(b, 2);
        }
    }

    // si a solide et b gazeuse alors b liquide et a liquide
    if ((a.etat==3) and (b.etat==1))
    {
        newetat(a, 2);
        newetat(b, 2);
    }

    // si a solide et b plante alors b dead et a aire
    if ((a.etat==3) and (b.etat==4))
    {
        newetat(a, 0);
        newetat(b, 6);
    }

    // si a mort et b plante alors b mort (1 chance sur 100)
    if ((a.etat==6) and (b.etat==4))
    {
        if (rand()%1000==2)
        {
            newetat(b, 6);
        }
    }
    if ((a.etat==8) and (b.etat==4))
    {
        newetat(b, 9);
    }
}

////////////////////////////////////////////INITIALISATION/
void initgrille(world &w)
{
    int j, i;
    w.dx = 40;
    w.dy = 40;

    // remplissage de terre
    for (i=0; i<w.dy; i++)
    {
        for (j=0; j<w.dx/9; j++)
        {
            w.t[i][j].etat=5;
            etat(w.t[i][j]);
        }
    }
    // remplissage d'aire
    for (i=0; i<w.dy; i++)
    {
        for (j=w.dx/9; j<w.dx; j++)
        {
            w.t[i][j].etat=0;
            etat(w.t[i][j]);
        }
    }
}

void initw(world &w, int nb)
{
    element e;
    int i, x, y;
    w.nb = nb;

    initgrille(w);

    for (i=0; i<w.nb; i++)
    {
        e.etat=rand()%4;
        x=rand()%w.dx ;
        y=rand()%w.dy + w.dy/9;

        etat(e);

        if (e.etat!=0)
        {
            w.nb=w.nb+1;
        }
        w.t[x][y]=e;
        if ((rand()%70)==4)
        {
            newetat(w.t[rand()%w.dx][rand()%w.dy+ w.dy/9], 8);
        }
    }


}

/////////////////////////////////////////////////////////
void draww(world& w)
{
    int i,j ;
    int H = 5, L = 5;
    for (i=0; i <w.dx; i++)
    {
        for (j=0; j <w.dy; j++)
        {
            color(w.t[i][j].c.r, w.t[i][j].c.g, w.t[i][j].c.b);
            rectangleFill( i*L, j*H, (i+1)*L, (j+1)*H);
        }

    }
}

void collision(world &w)
{
    world wnew;
    wnew = w;
    int j, i, c, b;
    for(i=0; i<w.dx; i++)
    {
        for(j=0; j<w.dy; j++)
        {
            if (wnew.t[i][j].etat == 1)
            {

            }

            if (wnew.t[i][j].etat == 2)
            {

            }
            if (wnew.t[i][j].etat == 3)
            {

            }
            if (wnew.t[i][j].etat == 4)
            {

            }
            if (wnew.t[i][j].etat == 5)
            {

            }
            // chgts d'etat non précis des cellules voisines
            for (c=-1; c<=3; c++)
            {
                for (b=-1; b<=3; b++)
                {
                    contactinter(wnew.t[i][j], wnew.t[i+b][j+c]);
                }
            }
        }
    }
}
void updatew(world& w)
{
    world wnew;
    wnew = w;
    int j, i, c, b;

    for(i=0; i<w.dx; i++)
    {
        for(j=0; j<w.dy; j++)
        {
            // chgts d'etat non précis des cellules voisines
            for (c=-1; c<=3; c++)
            {
                for (b=-1; b<=3; b++)
                {
                    contactinter(wnew.t[i][j], wnew.t[i+b][j+c]);
                }
            }
            //decongele(wnew.t[i][j]);
//  8 abeille + plante = 9 fleur + mort de l'abeille (deviens aire)
            for (c=-1; c<=3; c++)
            {
                for (b=-1; b<=3; b++)
                {
                    if ((wnew.t[i][j].etat == 8 ) and ((wnew.t[b][c].etat == 3) or (wnew.t[b][c].etat == 2)))
                    {
                        newetat(wnew.t[b][b], 0);
                        newetat(wnew.t[i][j], 0);
                    }
                }
            }
            if (wnew.t[i][j].etat == 4 )
            {
                if ((wnew.t[i-1][j].etat == 8) or (wnew.t[i+1][j].etat == 8))
                {
                    newetat(wnew.t[i][j], 9);
                    newetat(wnew.t[i+1][j], 0);
                    newetat(wnew.t[i-1][j], 0);
                }
            }
            // eau + terre = plante
            if ((wnew.t[i][j].etat == 5) and (wnew.t[i][j+1].etat == 2))
            {
                newetat(wnew.t[i][j+1], 4);
            }

            // plante + eau = plante+
            if ((wnew.t[i][j].etat == 4) and (wnew.t[i][j+1].etat == 2))
            {
                newetat(wnew.t[i][j+1], 4);
            }

            if ((rand()%20)==5)
            {
                if (wnew.t[i][j].etat == 4)
                {
                    newetat(wnew.t[i][j+1], 4);
                    if ((rand()%50)==2)
                    {
                        newetat(wnew.t[i+1][j+1], 4);
                    }
                    if ((rand()%50)==7)
                    {
                        newetat(wnew.t[i-1][j+1], 4);
                    }
                }
            }

            if (wnew.t[i][j].etat == 2)
            {
                if (wnew.t[i][j-1].etat == 0)
                {
                    newetat(wnew.t[i][j], 0);
                    newetat(wnew.t[i][j-1], 2);
                }
                if ((wnew.t[i][j-1].etat != 0) and (wnew.t[i+1][j-1].etat != 0))
                {
                    if (wnew.t[i-1][j-1].etat == 0)
                    {
                        newetat(wnew.t[i-1][j-1], 2);
                        newetat(wnew.t[i][j], 0 );
                        newetat(wnew.t[i-1][j], 0 );
                    }

                    if (wnew.t[i+1][j-1].etat == 0)
                    {
                        newetat(wnew.t[i+1][j-1], 2);
                        newetat(wnew.t[i][j], 0 );
                        newetat(wnew.t[i+1][j-1], 0 );
                    }
                }
            }
        }
        w=wnew;
    }
}
// [i-1][j+1] [i][j+1]  [i+1][j+1]
// [i-1][j]   [i][j]    [i+1][j]
// [i-1][j-1] [i][j-1]  [i+1][j-1]


int main(int, char** )
{
    bool stop=false;
    winInit("bac", DIMW, DIMW);
    backgroundColor(0,0,0);

    world w;
    initw(w, 50);

    while(!stop)
    {
        winClear();

        draww(w);
        updatew(w);
        stop = winDisplay();
    }
    winQuit();
    return 0;
}