#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED


int verifyplacement(int mat[10][10],int mat1[5][5],int size1,int size3,int size2);

int getmaxlarg(int mat1[5][5]);

int getmaxlong(int mat1[5][5]);

void linestodelete(int grille[10][10],int list[10]);

void columnstodelete(int grille[][10],int list[10]);

int countblocks(int piece[][5]);

void calcul_bonus(int *score, int lignes[NB_BLOCS], int columns[NB_BLOCS]);

place verifyscore(int grille[][NB_BLOCS], int piece[][NB_PIECES], int score);

#endif // SCORE_H_INCLUDED
