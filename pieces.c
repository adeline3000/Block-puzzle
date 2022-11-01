#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "pieces.h"
#include "score.h"

//construire une piece
void construire_piece(int piece[][NB_PIECES], int num_piece)
{
    int i,j;


    for(i=0; i<NB_PIECES; i++)
    {
        for(j=0; j<NB_PIECES; j++)
        {
                piece[i][j]=0;
                piece[i][j]=0;
        }
    }

    switch (num_piece)
    {
    case 0:
        piece[0][0]=VERT;
        break;
    case 1:
        piece[0][0]=BLEU;
        piece[0][1]=BLEU;
        break;
    case 2:
        piece[0][0]=BLEU;
        piece[1][0]=BLEU;
        break;
    case 3:
        piece[0][0]=JAUNE;
        piece[0][1]=JAUNE;
        piece[0][2]=JAUNE;
        break;
    case 4:
        piece[0][0]=JAUNE;
        piece[1][0]=JAUNE;
        piece[2][0]=JAUNE;
        break;
    case 5:
        piece[0][0]=JAUNE;
        piece[0][1]=JAUNE;
        piece[1][1]=JAUNE;
        break;
    case 6:
         piece[0][0]=JAUNE;
         piece[1][0]=JAUNE;
         piece[1][1]=JAUNE;
         break;
    case 7:
         piece[0][0]=JAUNE;
         piece[0][1]=JAUNE;
         piece[1][0]=JAUNE;
         break;
    case 8:
         piece[0][1]=JAUNE;
         piece[1][0]=JAUNE;
         piece[1][1]=JAUNE;
         break;
    case 9:
         piece[0][0]=ROUGE;
         piece[0][1]=ROUGE;
         piece[1][0]=ROUGE;
         piece[1][1]=ROUGE;
         break;
    case 10:
         piece[0][0]=ROUGE;
         piece[1][0]=ROUGE;
         piece[1][1]=ROUGE;
         piece[2][0]=ROUGE;
         break;
    case 11:
         piece[1][0]=ROUGE;
         piece[0][1]=ROUGE;
         piece[1][1]=ROUGE;
         piece[2][1]=ROUGE;
         break;
    case 12:
         piece[0][1]=ROUGE;
         piece[1][0]=ROUGE;
         piece[1][1]=ROUGE;
         piece[1][2]=ROUGE;
         break;
    case 13:
         piece[0][0]=ROUGE;
         piece[0][1]=ROUGE;
         piece[0][2]=ROUGE;
         piece[1][1]=ROUGE;
         break;
    case 14:
         piece[0][0]=ROUGE;
         piece[1][0]=ROUGE;
         piece[2][0]=ROUGE;
         piece[3][0]=ROUGE;
         break;
    case 15:
         piece[0][0]=ROUGE;
         piece[0][1]=ROUGE;
         piece[0][2]=ROUGE;
         piece[0][3]=ROUGE;
         break;
    case 16:
         piece[0][0]=VIOLET;
         piece[1][0]=VIOLET;
         piece[2][0]=VIOLET;
         piece[3][0]=VIOLET;
         piece[4][0]=VIOLET;
         break;
    case 17:
         piece[0][0]=VIOLET;
         piece[0][1]=VIOLET;
         piece[0][2]=VIOLET;
         piece[0][3]=VIOLET;
         piece[0][4]=VIOLET;
         break;
    case 18:
         piece[0][0]=VIOLET;
         piece[0][1]=VIOLET;
         piece[0][2]=VIOLET;
         piece[1][2]=VIOLET;
         piece[2][2]=VIOLET;
         break;
    case 19:
         piece[0][0]=VIOLET;
         piece[0][1]=VIOLET;
         piece[0][2]=VIOLET;
         piece[1][0]=VIOLET;
         piece[2][0]=VIOLET;
         break;
    case 20:
         piece[0][2]=VIOLET;
         piece[1][2]=VIOLET;
         piece[2][2]=VIOLET;
         piece[2][1]=VIOLET;
         piece[2][0]=VIOLET;
         break;
    case 21:
         piece[0][0]=VIOLET;
         piece[1][0]=VIOLET;
         piece[2][0]=VIOLET;
         piece[2][1]=VIOLET;
         piece[2][2]=VIOLET;
         break;
    case 22:
         piece[0][0]=VIOLET;
         piece[0][1]=VIOLET;
         piece[1][1]=VIOLET;
         piece[2][1]=VIOLET;
         piece[2][0]=VIOLET;
         break;
    case 23:
         piece[0][0]=VIOLET;
         piece[0][1]=VIOLET;
         piece[1][0]=VIOLET;
         piece[2][0]=VIOLET;
         piece[2][1]=VIOLET;
         break;
    case 24:
         piece[0][0]=VIOLET;
         piece[0][1]=VIOLET;
         piece[0][2]=VIOLET;
         piece[1][2]=VIOLET;
         piece[1][0]=VIOLET;
         break;
    case 25:
         piece[0][0]=VIOLET;
         piece[1][0]=VIOLET;
         piece[1][1]=VIOLET;
         piece[0][2]=VIOLET;
         piece[1][2]=VIOLET;
         break;
    case 26:
         piece[0][0]=ORANGE;
         piece[0][1]=ORANGE;
         piece[0][2]=ORANGE;
         piece[1][0]=ORANGE;
         piece[1][1]=ORANGE;
         piece[1][2]=ORANGE;
         piece[2][0]=ORANGE;
         piece[2][1]=ORANGE;
         piece[2][2]=ORANGE;
         break;
    }
}


//créer une nouvelle pièce et l'afficher
void creer_piece(SDL_Surface *ecran, int num_piece, int piece[][NB_PIECES], SDL_Rect pos, SDL_Rect position[][NB_PIECES])
{
    int i,j;

    construire_piece(piece, num_piece);

    for(i=0; i<NB_PIECES; i++)
    {
        for(j=0; j<NB_PIECES; j++)
        {
                position[i][j].x=pos.x + j*TAILLE_BLOC;
                position[i][j].y=pos.y + i*TAILLE_BLOC;
        }
    }

    bliter_piece(ecran, piece, position);
}

void bliter_piece(SDL_Surface *ecran, int piece[][NB_PIECES], SDL_Rect position[][NB_PIECES])
{
    int i,j;
    SDL_Surface *blocks[7] = {NULL};
    blocks[BLEU] = IMG_Load("block_bleu.png");
    blocks[ROUGE] = IMG_Load("block_rouge.png");
    blocks[ORANGE] = IMG_Load("block_ORANGE.png");
    blocks[JAUNE] = IMG_Load("block_jaune.png");
    blocks[VIOLET] = IMG_Load("block_violet.png");
    blocks[VERT] = IMG_Load("block_vert.png");

    for(i=0;i<NB_PIECES;i++)
    {
        for(j=0;j<NB_PIECES;j++)
        {
            switch(piece[i][j])
            {
            case ROUGE:
                SDL_BlitSurface(blocks[ROUGE], NULL, ecran, &position[i][j]);
            break;
            case VERT:
                SDL_BlitSurface(blocks[VERT], NULL, ecran, &position[i][j]);
            break;
            case BLEU:
                SDL_BlitSurface(blocks[BLEU], NULL, ecran, &position[i][j]);
            break;
            case JAUNE:
                SDL_BlitSurface(blocks[JAUNE], NULL, ecran, &position[i][j]);
            break;
            case ORANGE:
                SDL_BlitSurface(blocks[ORANGE], NULL, ecran, &position[i][j]);
            break;
            case VIOLET:
                SDL_BlitSurface(blocks[VIOLET], NULL, ecran, &position[i][j]);
            break;
            }
        }
    }
}

void bliter_grille(SDL_Surface *ecran, int piece[][NB_BLOCS], SDL_Rect position[][NB_BLOCS])
{
    int i,j;
    SDL_Surface *blocks[7] = {NULL};
    blocks[VIDE] = IMG_Load("block_vide.png");
    blocks[BLEU] = IMG_Load("block_bleu.png");
    blocks[ROUGE] = IMG_Load("block_rouge.png");
    blocks[ORANGE] = IMG_Load("block_ORANGE.png");
    blocks[JAUNE] = IMG_Load("block_jaune.png");
    blocks[VIOLET] = IMG_Load("block_violet.png");
    blocks[VERT] = IMG_Load("block_vert.png");

    for(i=0;i<NB_BLOCS;i++)
    {
        for(j=0;j<NB_BLOCS;j++)
        {
            switch(piece[i][j])
            {
            case VIDE:
                SDL_BlitSurface(blocks[VIDE], NULL, ecran, &position[i][j]);
            break;
            case ROUGE:
                SDL_BlitSurface(blocks[ROUGE], NULL, ecran, &position[i][j]);
            break;
            case VERT:
                SDL_BlitSurface(blocks[VERT], NULL, ecran, &position[i][j]);
            break;
            case BLEU:
                SDL_BlitSurface(blocks[BLEU], NULL, ecran, &position[i][j]);
            break;
            case JAUNE:
                SDL_BlitSurface(blocks[JAUNE], NULL, ecran, &position[i][j]);
            break;
            case ORANGE:
                SDL_BlitSurface(blocks[ORANGE], NULL, ecran, &position[i][j]);
            break;
            case VIOLET:
                SDL_BlitSurface(blocks[VIOLET], NULL, ecran, &position[i][j]);
            break;
            }
        }
    }
}


int clic_piece(int piece[][NB_PIECES], SDL_Rect position[][NB_PIECES], SDL_Event event)
{
    int i,j, clicGaucheEnCours = 0;

    for (i=0;i<NB_PIECES;i++)
    {
        for(j=0;j<NB_PIECES;j++)
        {
            if(piece[i][j] != 0)
            {
                if ((event.button.x <= (position[i][j].x + TAILLE_BLOC)) && (event.button.x >= position[i][j].x)
                        && (event.button.y <= (position[i][j].y + TAILLE_BLOC)) && (event.button.y >= position[i][j].y) )
                    {
                       clicGaucheEnCours = 1;
                    }
            }
        }
    }
    return clicGaucheEnCours;
}

void deplacer_piece(int piece[][NB_PIECES], SDL_Rect position[][NB_PIECES], int pasx, int pasy)
{
    int i,j,collis;

    for (i=0;i<NB_PIECES;i++)
    {
        for(j=0;j<NB_PIECES;j++)
        {
            position[i][j].x= position[i][j].x + pasx;
            position[i][j].y= position[i][j].y + pasy;
        }
    }

    collis = collision(piece, position);

    if(collis)
    {
        for (i=0;i<NB_PIECES;i++)
        {
            for(j=0;j<NB_PIECES;j++)
            {
                position[i][j].x= position[i][j].x - pasx;
                position[i][j].y= position[i][j].y - pasy;
            }
        }
    }
}

int verifycoordo(int grille[][NB_BLOCS], int x, int y, int piece[][NB_PIECES])
{
    int i,j,b=1;

    i=0;;
    while(i < NB_PIECES && b)
    {
        j=0;
        while(j < NB_PIECES && b)
        {
            if(piece[i][j] != VIDE)
            {
                if(grille[x + i][y + j] != VIDE)
                {
                    b=0;
                }
            }
            j++;
        }
        i++;
    }

    return b;
}

void placer_piece(int grille[][NB_BLOCS], int x, int y, int piece[][NB_PIECES])
{
    int i,j;

    for(i=0;i<NB_PIECES;i++)
    {
        for(j=0;j<NB_PIECES;j++)
        {
            if(piece[i][j] != VIDE)
            {
                (grille[x + i][y + j] = piece[i][j]);
            }
        }
    }
}




void placer_grille(SDL_Surface *ecran, int grille[][NB_BLOCS], int *num_piece, int *score, int piece[][NB_PIECES],
                    SDL_Rect pos, SDL_Rect pos_piece[][NB_PIECES], SDL_Rect pos_grille[][NB_BLOCS])
{
    int i =0,j =0, piece_in = 0, b, x, y;

    while(i<(NB_BLOCS - getmaxlong(piece) +1) && !piece_in)
    {
        j=0;
       while(j<(NB_BLOCS - getmaxlarg(piece)+1) && !piece_in)
       {
           if ( (pos_piece[0][0].x  >= pos_grille[i][j].x) && (pos_piece[0][0].x <= (pos_grille[i][j].x + TAILLE_BLOC))
                && (pos_piece[0][0].y  >= pos_grille[i][j].y) && (pos_piece[0][0].y <= (pos_grille[i][j].y) + TAILLE_BLOC) )

                    {
                         piece_in = 1;
                         x = i;
                         y = j;

                    }
                    j++;
       }
       i++;
    }

    if(piece_in)
    {
        b = verifycoordo(grille,x,y,piece);
        if(b==1)
        {
            placer_piece(grille,x,y,piece);
            *score = *score+countblocks(piece)*10;
            *num_piece =(SDL_GetTicks()%27);
            creer_piece(ecran, *num_piece, piece, pos, pos_piece);
        }
        else
        {
            for(i=0; i<NB_PIECES; i++)
            {
              for(j=0; j<NB_PIECES; j++)
              {
                pos_piece[i][j].x=pos.x + j*TAILLE_BLOC;
                pos_piece[i][j].y=pos.y + i*TAILLE_BLOC;
              }
            }
        }
    }
    else
    {
        for(i=0; i<NB_PIECES; i++)
        {
           for(j=0; j<NB_PIECES; j++)
           {
                pos_piece[i][j].x=pos.x + j*TAILLE_BLOC;
                pos_piece[i][j].y=pos.y + i*TAILLE_BLOC;
           }
        }
    }



}

int collision(int piece[][NB_PIECES], SDL_Rect position[][NB_PIECES])
{
    int haut,bas,gauche,droite;

    haut = position[0][0].y;
    gauche = position[0][0].x;
    droite = gauche + getmaxlarg(piece) * TAILLE_BLOC;
    bas = haut + getmaxlong(piece) * TAILLE_BLOC;

    if(gauche > 0 && haut > 0 && bas < 600 && droite < 600)
            return 0;
    else
            return 1;
}

void piece_inaccessible(SDL_Surface *ecran, SDL_Rect pos, int piece[][NB_PIECES])
{
    SDL_Surface *texte = NULL;
    TTF_Font *police = TTF_OpenFont("font.ttf", 16);// Chargement de la police
    SDL_Color couleurGrise = {195, 195, 195};
    SDL_Rect pos_texte;

    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texte = TTF_RenderText_Blended(police, "not accessible", couleurGrise);

    pos_texte.x = pos.x;
    pos_texte.y = pos.y + getmaxlong(piece) * TAILLE_BLOC + 1;

    SDL_BlitSurface(texte, NULL, ecran, &pos_texte); /* Blit du texte */
    SDL_Flip(ecran);
    SDL_Delay(500);
    TTF_CloseFont(police);
}

void vider_ligne(int grille[][NB_BLOCS], int lignes[NB_BLOCS])
{
    int i=0;
        while (lignes[i]!=-1)
        {
                int sup=lignes[i];
                for (int k=0;k<10;k++)
                    {
                       grille[sup][k]=VIDE;
                    }
                i++;

        }
}

void vider_colonne(int grille[][NB_BLOCS], int columns[NB_BLOCS])
{
     int i=0;
        while (columns[i]!=-1)
        {
                int sup=columns[i];
                for (int k=0;k<10;k++)
                    {
                       grille[k][sup]=VIDE;
                    }
                i++;

        }
}

void copier_grille(int grille[][NB_BLOCS], int copygrille[][NB_BLOCS])
{
    int i,j;

    //copier la grille
    for(i=0;i<NB_BLOCS;i++)
    {
        for(j=0;j<NB_BLOCS;j++)
        {
            copygrille[i][j] = grille[i][j];
        }
    }
}

int pieces_dispo(int copygrille[][NB_BLOCS])
{
    int i,nb,b;
    int copypiece[NB_PIECES][NB_PIECES] = {VIDE};

    nb = 0;
    for(i=0;i<27;i++)
    {
        construire_piece(copypiece, i);
        b = verifyplacement(copygrille,copypiece,10,getmaxlarg(copypiece),getmaxlong(copypiece));
        if(b == 1)
        {
            nb += 1;
        }
    }
    return nb;
}

place compare_pieces(place c1, place c2)
{
    if(c1.score > c2.score)
    {
       return (c1);
    }
    if(c1.score == c2.score)
    {
        if(c1.nb > c2.nb)
        {
            return(c1);
        }
        else
        {
            return(c2);
        }
    }
    else
    {
        return(c2);
    }
}




