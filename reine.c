#include <stdio.h>
#include "echiq.h"
 
int x,y;        // variables pour les boucles de l'affichage du tableau
 
void Init(pointeur *l)
{
     l->premier = NULL;
     l->dernier = NULL;
}
 
void Ajout(pointeur *l, int dames[8][8])
{
   int i,j;
   echiq *nouv = malloc(sizeof(echiq));
   if(!nouv) return;
   for(i=0;i<8;i++)
   {
        for(j=0;j<8;j++)
        {
             nouv->tab_dames[i][j] = dames[i][j];
        }
   }
   nouv->prec = l->dernier;
   nouv->suiv = NULL;
   if(l->dernier) l->dernier->suiv = nouv;
   else l->premier = nouv;
   l->dernier = nouv;
}
 
void placedame(int numligne, int point[8][8],  int ligne[8], int e[8])
{
    for (ligne[numligne] = e[numligne]; ligne[numligne] < 8; ligne[numligne]++)
    {
        if (point[ligne[numligne]][numligne] == 0)
        {
            e[numligne] = ligne[numligne] + 1;
            dame(numligne, ligne[numligne], 2, point);
            if (numligne < 7)
            {
                placedame(numligne+1, point, ligne, e);
            }
            if (numligne == 7)
            {
                dame(numligne, ligne[numligne], -2, point);
                dame(numligne-1, ligne[numligne-1], -2, point);
                placedame(numligne-1, point, ligne, e);
            }
        }
    }
    if (numligne !=0)
    {
        if (ligne[numligne] >= 8)
        {
            for (x=numligne; x < 8; x++)
            {
                e[x]=0;
            }
            dame(numligne-1, ligne[numligne-1], -2, point);
            placedame(numligne - 1, point, ligne, e);
        }
    }
}
 
 
void dame(int a,int b,int num, int point[8][8])
{
    for (x=0; x < 8; x++)
    {
        if (x != a)
        {
            point[b][x] += num;
        }
        if (x !=b)
        {
            point[x][a] += num;
        }
    }
    for (x=1; x < 8; x++)
    {
        if (a + x < 8 && b + x < 8)
        {
            point[b+x][a+x] += num;
        }
        if (a - x >= 0 && b - x >= 0)
        {
            point[b-x][a-x] += num;
        }
        if (a - x >= 0 && b + x < 8)
        {
            point[b+x][a-x] += num;
        }
        if (a + x < 8 && b + x >= 0)
        {
            point[b-x][a+x] += num;
        }
    }
    if (num > 0)
    {
        point[b][a] += 1;
    }
    if (num < 0)
    {
        point[b][a] -= 1;
     }
}
 
void main(void)
{
    int amorce[8], ligne[8];
    int i,j,k;
    int point[8][8];
    for(i = 0; i < 8; i++)
    {
        amorce[i] = 0;
        ligne[i] = 0;
    }
    pointeur ListEchiq;
    Init(&ListEchiq);
    for(i = 0; i < 92; i++)
    {
        for(j = 0; j < 8; j++)
        {
            for(k = 0; k < 8; k++)
            {
                point[j][k] = 0;
            }
            amorce[j] = 0;
        }
        placedame(0, point, ligne, amorce);
        for(j = 0; j < 8; j++)
        {
            for(k = 0; k < 8; k++)
            {
                printf("%d  ", point[j][k]);
            }
            printf("\n");
        }
        Ajout(&ListEchiq, point);
    }
 
}
