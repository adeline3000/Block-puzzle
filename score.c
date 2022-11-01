#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "pieces.h"
#include "jeu.h"
#include "fichier.h"
#include "score.h"

int verifyplacement(int mat[10][10],int mat1[5][5],int size1,int size3,int size2)
{

int i=0,j=0,l=0,p=0;
while (i<size1-size2+1&&p==0)
    {
        j=0;
        while (j<size1-size3+1&&p==0)
            {
                int next=0;
                for (int k=0;k<size2&&next==0;k++)
                {
                    for (l=0;l<size3&&next==0;l++)
                    {

                       if (mat[i+k][j+l]!=0&&mat1[k][l]!=0) next=1;
                    }
               }
               if (next==0) p=1;
               else j++;
            }
            i++;
        }


return p;

}

int getmaxlarg(int mat1[5][5])
{
    int max=1;
      for (int k=0;k<5;k++){
         for (int l=0;l<5;l++){
        if (mat1[l][k]!=0&&(k+1)>max) max=k+1;
      }

      }
      return max;

}
int getmaxlong(int mat1[5][5])
{

    int max=1;
      for (int k=0;k<5;k++){
         for (int l=0;l<5;l++){
        if (mat1[k][l]!=0&&(k+1)>max) max=k+1;
      }

      }
    return max;

}

void linestodelete(int grille[10][10],int list[10])
{


    int k=0;
    for (int i=0;i<10;i++)
        {
            int p=0;
            for (int j=0;j<10;j++)
            {
                if (grille[i][j]==0) p=1;
            }
            if (p==0)
            {
               list[k]=i; k++;
            }
         }

}

void columnstodelete(int grille[][10],int list[10])
{
    int k=0;
    for (int i=0;i<10;i++)
        {
            int p=0;
            for (int j=0;j<10;j++)
            {
               int m=grille[j][i];
               if (m==0) p=1;
            }
            if (p==0)
            {
               list[k]=i; k++;
            }
        }


}

int countblocks(int piece[][5])
{

int count=0;
for (int i=0;i<5;i++){
    for (int j=0;j<5;j++){
        if (piece[i][j]!=0) count++;
    }
}

return count;

}

void calcul_bonus(int *score, int lignes[NB_BLOCS], int columns[NB_BLOCS])
{
     int a=0;
        while (lignes[a]!=-1)
        {
            a++;
        }
        int b=0;
        while (columns[b]!=-1)
        {
            b++;
        }
        if (a==1)
         {
           *score +=100;
         }
        if (a==2)
        {
           *score +=300;
        }
        if (a==3)
        {
           *score +=600;
        }
        if (a==4)
        {
           *score +=1000;
        }
        if (a==5)
        {
           *score +=1500;
        }
        if (b==1){
           *score +=100;
        }
        if (b==2)
        {
           *score +=300;
        }
        if (b==3)
        {
           *score +=600;
        }
        if (b==4)
        {
           *score +=1000;
        }
        if (b==5)
        {
           *score +=1500;
        }

}

place verifyscore(int grille[][NB_BLOCS], int piece[][NB_PIECES], int score)
{
    int copygrille[NB_BLOCS][NB_BLOCS]={VIDE};
    int lignes[NB_BLOCS], columns[NB_BLOCS];
    int i,j,b,k;
    int copyscore = score;
    place p;
    p.vide = 1;
    p.score = score;

    for(i=0;i<(NB_BLOCS - getmaxlong(piece)+1);i++)
    {
        for(j=0;j<(NB_BLOCS - getmaxlarg(piece)+1);j++)
            {
                copier_grille(grille, copygrille); //effacer la piece qu'on a essayé
                copyscore = score; //reinitialiser le score
                b = verifycoordo(copygrille,i,j,piece);//si on peut placer la piece dans cet endroit
                if(b==1)
                {
                    placer_piece(copygrille, i, j, piece);
                    copyscore = copyscore+countblocks(piece)*10;

                    for (k=0;k<10;k++)//initialiser lignes à -1
                        {
                          lignes[k]=-1;
                        }

                    for (k=0;k<10;k++)//initialiser columns à -1
                        {
                            columns[k]=-1;
                        }
                        linestodelete(copygrille,lignes);//retourne les lignes à supprimer
                        columnstodelete(copygrille,columns);//retourne les colonnes à supprimer
                        calcul_bonus(&copyscore,lignes,columns);

                        if((p.vide == 1) || (copyscore > p.score)) //on a pas encore initialisé la place
                        {                                          // p ou la nouvelle place a un score plus grand
                            p.vide = 0;
                            p.col = j;
                            p.lig = i;
                            p.nb = pieces_dispo(copygrille);// nbre de pieces qu'on pourrait mettre après
                            p.score = copyscore;
                        }
                        else
                        {
                            if(copyscore == p.score)
                            {
                              if (pieces_dispo(copygrille) > p.nb)//si dans cette nouvelle position
                              {
                                 p.vide = 0;                                    // on aurra plus de places
                                 p.col = j;
                                 p.lig = i;
                                 p.nb = pieces_dispo(copygrille);
                                 p.score = copyscore;
                              }
                            }
                        }
                }
            }
    }
    return(p);
}
