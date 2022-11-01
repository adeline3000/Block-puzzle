#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "pieces.h"
#include "jeu.h"
#include "fichier.h"
#include "score.h"
#include "menu.h"


int meilleurscore;


/************************LE JEU****************************/
void init_jeu(SDL_Surface *ecran, int save)
{
    int score =0;
    SDL_Surface *trophy = IMG_Load("trophy.png");
    SDL_Surface *pause = IMG_Load("pause.png");

    SDL_Surface *textscore = NULL;
    SDL_Surface *textbest = NULL;

    SDL_Surface *blocks[8] = {NULL};
    blocks[BLEU] = IMG_Load("block_bleu.png");
    blocks[ROUGE] = IMG_Load("block_rouge.png");
    blocks[ORANGE] = IMG_Load("block_ORANGE.png");
    blocks[JAUNE] = IMG_Load("block_jaune.png");
    blocks[VIOLET] = IMG_Load("block_violet.png");
    blocks[VERT] = IMG_Load("block_vert.png");

    TTF_Font *police = TTF_OpenFont("font.ttf", 16);// Chargement de la police
    SDL_Color couleurBlanche = {255, 255, 255};

    int grille[NB_BLOCS][NB_BLOCS]={VIDE},
        piece1[NB_PIECES][NB_PIECES]={VIDE},
        piece2[NB_PIECES][NB_PIECES]={VIDE},
        piece3[NB_PIECES][NB_PIECES]={VIDE},
        lignes[10],columns[10];

    SDL_Rect pos_grille[NB_BLOCS][NB_BLOCS], pos_piece1[NB_PIECES][NB_PIECES], pos_piece2[NB_PIECES][NB_PIECES],
             pos_piece3[NB_PIECES][NB_PIECES],prem_pos, deux_pos, trois_pos, anc_pos, pos_pause, pos_trophy,
             pos_score, pos_best;

    SDL_Event event;
    int continuer = 1;
    int i,j, pasx, pasy;
    int num_piece1, num_piece2, num_piece3;
    int clic_piece1=0, clic_piece2=0, clic_piece3 =0;
    char scores[100];


    prem_pos.x =22;
    prem_pos.y =TAILLE_GRILLE + 70; // la pièce est au_dessous de la grille

    deux_pos.x = TAILLE_PIECE + prem_pos.x + 22; // il y a un vide de 22 pixels entre chaque 2 pièces
    deux_pos.y = prem_pos.y;

    trois_pos.x = TAILLE_PIECE + deux_pos.x + 22;
    trois_pos.y = prem_pos.y;

    pos_pause.x =5; // la position de l'icone pause et tout en haut à gauche
    pos_pause.y =5;

    pos_trophy.x =280; // la position de l'icone trophy est au milieu au-dessus de la grille
    pos_trophy.y =5;

    pos_best.x = pos_trophy.x + 40;
    pos_best.y = 20;

    pos_score.x = pos_trophy.x - 50;
    pos_score.y = 20;


     for(i=0; i<10; i++)
    {
        for(j=0; j<10; j++)
        {
                pos_grille[i][j].x=X + j*TAILLE_BLOC; // la grille est au milieu
                pos_grille[i][j].y=Y + i*TAILLE_BLOC;  // la grille est décalée de 50 pixels vers le bas
        }
    }

    if (save == 1)
    {
       charger_jeu(grille, &num_piece1, &num_piece2, &num_piece3, &score);
    }
    else
    {
        num_piece1 =(SDL_GetTicks()%27);
        num_piece2 =((SDL_GetTicks() + 4000) %27);
        num_piece3 =((SDL_GetTicks() * 5000) %27);
    }

    creer_piece(ecran, num_piece1, piece1, prem_pos, pos_piece1);
    creer_piece(ecran, num_piece2, piece2, deux_pos, pos_piece2);
    creer_piece(ecran, num_piece3, piece3, trois_pos, pos_piece3);

    int p1 = verifyplacement(grille,piece1,10,getmaxlarg(piece1),getmaxlong(piece1));
    int p2 = verifyplacement(grille,piece2,10,getmaxlarg(piece2),getmaxlong(piece2));
    int p3 = verifyplacement(grille,piece3,10,getmaxlarg(piece3),getmaxlong(piece3));

    while (continuer)
    {
         p1 = verifyplacement(grille,piece1,10,getmaxlarg(piece1),getmaxlong(piece1));
         p2 = verifyplacement(grille,piece2,10,getmaxlarg(piece2),getmaxlong(piece2));
         p3 = verifyplacement(grille,piece3,10,getmaxlarg(piece3),getmaxlong(piece3));

         if (p1==0&&p2==0&&p3==0) // game over
            {
                game_over(ecran);
                if (score>meilleurscore)
                   {
                      //ecriture dans le fichier

                   }

            }

        SDL_WaitEvent(&event);
        switch(event.type)
        {
           case SDL_QUIT:
                continuer = 0;
           break;

           case SDL_MOUSEBUTTONDOWN:
               if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if((event.button.x > pos_pause.x)&&(event.button.x < (pos_pause.x + pos_pause.w))
                       &&(event.button.y > pos_pause.y)&&(event.button.y < (pos_pause.y + pos_pause.h)))
                    {
                        menu_pause(ecran, grille, &num_piece1, &num_piece2, &num_piece3, &score);
                    }
                    clic_piece1 = clic_piece(piece1, pos_piece1,event);//verifier si on a cliqué sur cette pièce
                    if(clic_piece1 && !p1)//si on a cliqué et la pièce est inaccessible
                    {
                        piece_inaccessible(ecran, prem_pos, piece1);//afficher un message d'inaccessibilité
                    }
                    clic_piece2 = clic_piece(piece2, pos_piece2,event);//verifier si on a cliqué sur cette pièce
                    if(clic_piece2 && !p2)//si on a cliqué et la pièce est inaccessible
                    {
                        piece_inaccessible(ecran, deux_pos, piece2);//afficher un message d'inaccessibilité
                    }
                    clic_piece3 = clic_piece(piece3, pos_piece3,event);//verifier si on a cliqué sur cette pièce
                    if(clic_piece3 && !p3)//si on a cliqué et la pièce est inaccessible
                    {
                        piece_inaccessible(ecran, trois_pos, piece3);//afficher un message d'inaccessibilité
                    }

                    anc_pos.x = event.button.x;
                    anc_pos.y = event.button.y;
                }
           break;

           case SDL_MOUSEMOTION:
               if (clic_piece1 && p1)//si on a cliqué sur cette pièce et elle est accessible
                {
                  /*calculer le pas de la souris*/
                  pasx = event.motion.x - anc_pos.x;
                  pasy = event.motion.y - anc_pos.y;
                  deplacer_piece(piece1, pos_piece1, pasx, pasy);
                }

                if (clic_piece2 && p2)//si on a cliqué sur cette pièce et elle est accessible
                {
                  /*calculer le pas de la souris*/
                  pasx = event.motion.x - anc_pos.x;
                  pasy = event.motion.y - anc_pos.y;
                  deplacer_piece(piece2, pos_piece2, pasx, pasy);
                }

                if (clic_piece3 && p3)//si on a cliqué sur cette pièce et elle est accessible
                {
                  /*calculer le pas de la souris*/
                  pasx = event.motion.x - anc_pos.x;
                  pasy = event.motion.y - anc_pos.y;
                  deplacer_piece(piece3, pos_piece3, pasx, pasy);
                }

                anc_pos.x = event.motion.x;
                anc_pos.y = event.motion.y;
          break;

          case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    clic_piece1 = 0;
                    clic_piece2 = 0;
                    clic_piece3 = 0;

                    placer_grille(ecran, grille, &num_piece1, &score, piece1, prem_pos, pos_piece1, pos_grille);
                    placer_grille(ecran, grille, &num_piece2, &score, piece2, deux_pos, pos_piece2, pos_grille);
                    placer_grille(ecran, grille, &num_piece3, &score, piece3, trois_pos, pos_piece3, pos_grille);

                    for (i=0;i<10;i++)
                        {
                          lignes[i]=-1;
                        }

                    for (i=0;i<10;i++)
                        {
                            columns[i]=-1;
                        }

                    linestodelete(grille,lignes);
                    columnstodelete(grille,columns);

                    calcul_bonus(&score, lignes, columns);//calcule le nouveau score
                    sprintf(scores,"%d",score);//convertir le score (int) en string
                    /* Écriture du texte dans la SDL_Surface textscore en mode Blended (optimal) */
                    textscore = TTF_RenderText_Blended(police, scores, couleurBlanche);

                    vider_ligne(grille, lignes);
                    vider_colonne(grille, columns);

                }
            break;
        }
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 19, 35, 50));
        //afficher la nouvelle grille
        bliter_grille(ecran, grille, pos_grille);
        //afficher les nouvelles pièces ou le nouvel emplacement de la pièce
        bliter_piece(ecran, piece1, pos_piece1);
        bliter_piece(ecran, piece2, pos_piece2);
        bliter_piece(ecran, piece3, pos_piece3);
        SDL_BlitSurface(trophy, NULL, ecran, &pos_trophy);
        SDL_BlitSurface(pause, NULL, ecran, &pos_pause);
        SDL_BlitSurface(textscore, NULL, ecran, &pos_score); /* Blit du score */

        SDL_Flip(ecran);
    }

    SDL_FreeSurface(trophy);
    SDL_FreeSurface(pause);
    SDL_FreeSurface(textscore);
    SDL_FreeSurface(textbest);
    for(i=0;i<7;i++)
    {
        SDL_FreeSurface(blocks[i]);
    }
    TTF_CloseFont(police);
    SDL_Quit();
}

/************PETITE DESCRIPTION DU JEU************/
void about(SDL_Surface *ecran)
{
    SDL_Surface *fenetre = IMG_Load("about.png");
    SDL_Rect position;
    SDL_Event event;
    int continuer = 1;
    position.x = 0;
    position.y = 0;

    while (continuer)
    {
       SDL_WaitEvent(&event);
       switch(event.type)
       {
        case SDL_QUIT:
           continuer = 0;
         break;

         case SDL_MOUSEBUTTONDOWN:
               if (event.button.button == SDL_BUTTON_LEFT)
               {
                   if((event.button.x>22)&&(event.button.x<49)&&(event.button.y>21)&&(event.button.y<53))
                    {
                        home(ecran);
                    }
               }
       }
       //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
       SDL_BlitSurface(fenetre, NULL, ecran, &position); /* Blit du texte */
       SDL_Flip(ecran);
  }

}



/************************ROBOT******************************/
void robot(SDL_Surface *ecran)
{

    SDL_Surface *blocks[8] = {NULL};
    blocks[BLEU] = IMG_Load("block_bleu.png");
    blocks[ROUGE] = IMG_Load("block_rouge.png");
    blocks[ORANGE] = IMG_Load("block_ORANGE.png");
    blocks[JAUNE] = IMG_Load("block_jaune.png");
    blocks[VIOLET] = IMG_Load("block_violet.png");
    blocks[VERT] = IMG_Load("block_vert.png");
    SDL_Surface *pause = IMG_Load("pause.png");

    SDL_Surface *textscore = NULL;
    TTF_Font *police = TTF_OpenFont("font.ttf", 16);// Chargement de la police
    SDL_Color couleurBlanche = {255, 255, 255};

     int grille[NB_BLOCS][NB_BLOCS]={VIDE},
        piece1[NB_PIECES][NB_PIECES]={VIDE},
        piece2[NB_PIECES][NB_PIECES]={VIDE},
        piece3[NB_PIECES][NB_PIECES]={VIDE},
        lignes[10],columns[10];

    SDL_Rect pos_grille[NB_BLOCS][NB_BLOCS], pos_piece1[NB_PIECES][NB_PIECES], pos_piece2[NB_PIECES][NB_PIECES],
             pos_piece3[NB_PIECES][NB_PIECES],prem_pos, deux_pos, trois_pos,
             pos_pause, pos_score;

    SDL_Event event;
    int tempsPrecedent = 0, tempsActuel = 0;
    int continuer = 1;
    int i,j,p1,p2,p3;
    int num_piece1, num_piece2, num_piece3;
    int score =0;
    char scores[100];
    place c, c1, c2, c3;

    prem_pos.x =22;
    prem_pos.y =TAILLE_GRILLE + 70; // la pièce est au_dessous de la grille

    deux_pos.x = TAILLE_PIECE + prem_pos.x + 22; // il y a un vide de 22 pixels entre chaque 2 pièces
    deux_pos.y = prem_pos.y;

    trois_pos.x = TAILLE_PIECE + deux_pos.x + 22;
    trois_pos.y = prem_pos.y;

    pos_pause.x =5; // la position de l'icone pause et tout en haut à gauche
    pos_pause.y =5;

    pos_score.x = 280;
    pos_score.y = 20;



    for(i=0; i<10; i++)
    {
        for(j=0; j<10; j++)
        {
                pos_grille[i][j].x=X + j*TAILLE_BLOC; // la grille est au milieu
                pos_grille[i][j].y=Y + i*TAILLE_BLOC;  // la grille est décalée de 50 pixels vers le bas
        }
    }

    num_piece1 =(SDL_GetTicks()%27);
    num_piece2 =((SDL_GetTicks() + 4000) %27);
    num_piece3 =((SDL_GetTicks() * 5000) %27);

    creer_piece(ecran, num_piece1, piece1, prem_pos, pos_piece1);
    creer_piece(ecran, num_piece2, piece2, deux_pos, pos_piece2);
    creer_piece(ecran, num_piece3, piece3, trois_pos, pos_piece3);

    // L'AFFICHAGE
     SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 19, 35, 50));
    //afficher la grille
    bliter_grille(ecran, grille, pos_grille);
    //afficher les pièces
    bliter_piece(ecran, piece1, pos_piece1);
    bliter_piece(ecran, piece2, pos_piece2);
    bliter_piece(ecran, piece3, pos_piece3);
    SDL_BlitSurface(pause, NULL, ecran, &pos_pause);
    SDL_BlitSurface(textscore, NULL, ecran, &pos_score); /* Blit du score */

    SDL_Flip(ecran);// mise à jour de l'écran



    while (continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
           case SDL_QUIT:
                continuer = 0;
           break;
        }

    tempsActuel = SDL_GetTicks();
    if (tempsActuel - tempsPrecedent > 100) /* Si 30 ms se sont écoulées depuis le dernier tour de boucle */
    {
         tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
         p1 = verifyplacement(grille,piece1,10,getmaxlarg(piece1),getmaxlong(piece1));
         p2 = verifyplacement(grille,piece2,10,getmaxlarg(piece2),getmaxlong(piece2));
         p3 = verifyplacement(grille,piece3,10,getmaxlarg(piece3),getmaxlong(piece3));

         if (p1==0&&p2==0&&p3==0)
         {
             game_over(ecran);
         }

        // trouver la meilleure piece avec la meilleure position et le meilleur score

         if(p1)// si on peut mettre cette piece
         {
             c1 = verifyscore(grille, piece1, score);//retourne la meilleure position
         }
         else //sinon on ne peut pas deplacer cette piece (c1 vide)
         {
             c1.vide = 1;
         }
         if(p2)
         {
             c2 = verifyscore(grille, piece2, score);
         }
         else
         {
             c2.vide = 1;
         }
         if(p3)
         {
             c3 = verifyscore(grille, piece3, score);
         }
         else
         {
             c3.vide = 1;
         }

         if(c1.vide) // c1 vide
         {
             if(c2.vide) // c1 vide et c2 vide
             {
                c = c3;
             }
             else // c1 vide et c2 non vide
             {
                 if(c3.vide) //c1 vide et c3 vide
                 {
                     c = c2;
                 }
                 else // c2 non vide et c3 non vide
                 {
                     c = compare_pieces(c2, c3);// retourne la meilleure place des deux
                 }
             }
         }
         else //c1 non vide
         {
             if(c2.vide) // c1 non vide et c2 vide
             {
                 if(c3.vide) // c3 vide et c2 vide
                 {
                     c = c1;
                 }
                 else // c1 non vide, c3 non vide et c2 vide
                 {
                     c = compare_pieces(c1, c3);
                 }
             }
             else // c1 non vide et c2 non vide
             {
                 if(c3.vide) //c1 non vide, c2 non vide et c3 vide
                 {
                     c = compare_pieces(c1, c2);
                 }
                 else //c1 non vide, c2 non vide et c3 non vide
                 {
                     c = compare_pieces(c1, c2);
                     c = compare_pieces(c, c3);
                 }

             }
         }

         if ((c.col == c1.col) && (c.lig == c1.lig) && (c.nb == c1.nb) && (c.score == c1.score))
         {
            placer_piece(grille, c.lig, c.col,piece1);
            score = c.score;
            num_piece1 =(SDL_GetTicks()%27);
            creer_piece(ecran, num_piece1, piece1, prem_pos, pos_piece1);
         }
         else
         {
             if ((c.col == c2.col) && (c.lig == c2.lig) && (c.nb == c2.nb) && (c.score == c2.score))
             {
                placer_piece(grille, c.lig, c.col,piece2);
                score = c.score;
                num_piece2 =(SDL_GetTicks()%27);
                creer_piece(ecran, num_piece2, piece2, deux_pos, pos_piece2);
             }
             else
             {
                placer_piece(grille, c.lig, c.col,piece3);
                score = c.score;
                num_piece3 =(SDL_GetTicks()%27);
                creer_piece(ecran, num_piece3, piece3, trois_pos, pos_piece3);
             }
         }
          for (i=0;i<10;i++)
            {
                lignes[i]=-1;
            }

          for (i=0;i<10;i++)
            {
                columns[i]=-1;
            }

          linestodelete(grille,lignes);
          columnstodelete(grille,columns);

          sprintf(scores,"%d",score);//convertir le score (int) en string
          /* Écriture du texte dans la SDL_Surface textscore en mode Blended (optimal) */
          textscore = TTF_RenderText_Blended(police, scores, couleurBlanche);

          vider_ligne(grille, lignes);
          vider_colonne(grille, columns);
    }
    else /* Si ça fait moins de 30 ms depuis le dernier tour de boucle, on endort le programme le temps qu'il faut */
    {
         SDL_Delay(100 - (tempsActuel - tempsPrecedent));
    }


         SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 19, 35, 50));
        //afficher la nouvelle grille
        bliter_grille(ecran, grille, pos_grille);
        //afficher les nouvelles pièces ou le nouvel emplacement de la pièce
        bliter_piece(ecran, piece1, pos_piece1);
        bliter_piece(ecran, piece2, pos_piece2);
        bliter_piece(ecran, piece3, pos_piece3);
        SDL_BlitSurface(pause, NULL, ecran, &pos_pause);
        SDL_BlitSurface(textscore, NULL, ecran, &pos_score); /* Blit du score */

        SDL_Flip(ecran);// mise à jour de l'écran


    }

    SDL_FreeSurface(pause);
    SDL_FreeSurface(textscore);
    for(i=0;i<7;i++)
    {
        SDL_FreeSurface(blocks[i]);
    }
    TTF_CloseFont(police);
    SDL_Quit();
}





