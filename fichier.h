#ifndef FICHIER_H_INCLUDED
#define FICHIER_H_INCLUDED

void save_jeu(int grille[][NB_BLOCS], int *num_piece1, int *num_piece2, int *num_piece3, int *score);

void charger_jeu(int grille[][NB_BLOCS], int *num_piece1, int *num_piece2, int *num_piece3, int *score);

#endif // FICHIER_H_INCLUDED
