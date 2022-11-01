#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "pieces.h"
#include "jeu.h"
#include "fichier.h"

void save_jeu(int grille[][NB_BLOCS], int *num_piece1, int *num_piece2, int *num_piece3, int *score)
{
    FILE *fichierG = NULL,  *fichierP = NULL;
    int i = 0, j = 0;

    fichierG = fopen("grille.save", "w+");
    if (fichierG != NULL)
    {
        for (i = 0 ; i < NB_BLOCS ; i++)
        {
            for (j = 0 ; j < NB_BLOCS ; j++)
            {
                fprintf(fichierG, "%d", grille[j][i]);
            }
        }
    }

    fclose(fichierG);

    fichierP = fopen("pieces.save", "w+");
    if (fichierP != NULL)
    {
        fprintf(fichierP,"%d %d %d %d",*num_piece1,*num_piece2,*num_piece3,*score);
    }


    fclose(fichierP);

}

void charger_jeu(int grille[][NB_BLOCS], int *num_piece1, int *num_piece2, int *num_piece3, int *score)
{
    int i,j;
    char ligneFichier[NB_BLOCS * NB_BLOCS + 1] = {0};
    FILE *fichierG = NULL, *fichierP = NULL;

    fichierG = fopen("grille.save", "r");
    if (fichierG != NULL)
    {
        fgets(ligneFichier, NB_BLOCS * NB_BLOCS + 1, fichierG);

        for (i = 0 ; i < NB_BLOCS ; i++)
        {
        for (j = 0 ; j < NB_BLOCS ; j++)
        {
            switch (ligneFichier[(i * NB_BLOCS) + j])
            {
                case '0':
                    grille[j][i] = VIDE;
                    break;
                case '1':
                    grille[j][i] = ROUGE;
                    break;
                case '2':
                    grille[j][i] = VERT;
                    break;
                case '3':
                    grille[j][i] = BLEU;
                    break;
                case '4':
                    grille[j][i] = JAUNE;
                    break;
                case '5':
                    grille[j][i] = ORANGE;
                    break;
                case '6':
                    grille[j][i] = VIOLET;
            }
        }
        }
    }

    fclose(fichierG);

    fichierP = fopen("pieces.save", "r");
    if (fichierP != NULL)
    {
        fscanf(fichierP,"%d %d %d %d", num_piece1, num_piece2, num_piece3, score);
    }

    fclose(fichierP);

}
