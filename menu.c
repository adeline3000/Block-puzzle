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


/**************LE MENU PRINCIPAL*************/
void home(SDL_Surface *ecran)
{
    SDL_Surface* menu[5];
    menu[0]=IMG_Load("menu.png");
    menu[1]=IMG_Load("menu_quit.png");
    menu[2]=IMG_Load("menu_about.png");
    menu[3]=IMG_Load("menu_robot.png");
    menu[4]=IMG_Load("menu_play.png");

   SDL_Event event;

   SDL_Rect positionMenu;
   positionMenu.x = 0;
   positionMenu.y = 0;

   int continuer = 1,x = 0;

   SDL_BlitSurface( menu[0] ,NULL, ecran, &positionMenu );
   SDL_Flip(ecran);

    while (continuer) //mettre en pause le programme
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
           case SDL_QUIT:
                continuer = 0;
           break;

           case SDL_MOUSEMOTION:
            if((event.motion.x>481)&&(event.motion.x<560)&&(event.motion.y>240)&&(event.motion.y<319))
                    {
                    x=1;
                    }
            if((event.motion.x>340)&&(event.motion.x<419)&&(event.motion.y>240)&&(event.motion.y<319))
                    {
                    x=2;
                    }
            if((event.motion.x>191)&&(event.motion.x<270)&&(event.motion.y>240)&&(event.motion.y<319))
                    {
                    x=3;
                    }
            if((event.motion.x>48)&&(event.motion.x<127)&&(event.motion.y>240)&&(event.motion.y<319))
                    {
                    x=4;
                    }
            break;

            case SDL_MOUSEBUTTONDOWN:
               if (event.button.button == SDL_BUTTON_LEFT)
               {
                   switch(x)
                   {
                   case 1:
                    continuer = 0;
                    break;
                   case 2:
                    about(ecran);
                    break;
                   case 3:
                    robot(ecran);
                    break;
                   case 4:
                    init_jeu(ecran, 1);
                    break;
                   }
               }

        }
        //Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 19, 35, 50));
        SDL_BlitSurface(menu[x], NULL, ecran, &positionMenu);
        SDL_Flip(ecran);/* MISE A JOUR DE L'ECRAN */
    }

    for(x=0;x<5;x++)
    {
        SDL_FreeSurface(menu[x]);
    }
    SDL_Quit();
}


/***************LE MENU PAUSE**************/
void menu_pause(SDL_Surface *ecran, int grille[][NB_BLOCS], int *num_piece1, int *num_piece2, int *num_piece3, int *score)
{
    SDL_Surface * rectangle = NULL; //la nouvelle surfacee dans l'ecran
    SDL_Surface *texte = NULL;
    SDL_Surface *titre = NULL;
    SDL_Surface* menu[5];
    menu[0]=IMG_Load("big_play.png");
    menu[1]=IMG_Load("save.png");
    menu[2]=IMG_Load("replay.png");
    menu[3]=IMG_Load("ranking.png");
    menu[4]=IMG_Load("home.png");

    TTF_Font *police = TTF_OpenFont("font.ttf", 24);// Chargement de la police
    TTF_Font *police1 = TTF_OpenFont("font.ttf", 16);
    SDL_Color couleurBeige = {246, 211, 151};
    SDL_Color couleurBlanche = {255, 255, 255};

    SDL_Rect pos_texte;
    SDL_Rect pos_titre;
    SDL_Rect position;
    SDL_Rect pos[5];

    pos_titre.x = 236;
    pos_titre.y = 40;

    position.x = 0;
    position.y = 0;

    pos[0].x = 250;
    pos[0].y = 180;

    pos[1].x = 210;
    pos[1].y = 300;

    pos[2].x = 305;
    pos[2].y = 300;

    pos[3].x = 210;
    pos[3].y = 390;

    pos[4].x = 305;
    pos[4].y = 390;

    int continuer = 1, i, x=-1;
    SDL_Event event;

    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 600, 600, 32, 0, 0, 0, 0); //allocation de la surface
    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 19, 35, 50));//coloration de la surface
    titre = TTF_RenderText_Blended(police, "P A U S E", couleurBeige);

     /* Transparence Alpha moyenne (128) : */
    SDL_SetAlpha(rectangle, SDL_SRCALPHA, 200);
    /* On blitte l'image maintenant transparente sur le fond : */
    SDL_BlitSurface(rectangle, NULL, ecran, &position);

    SDL_BlitSurface(titre, NULL, ecran, &pos_titre);
    for(i=0;i<5;i++)
    {
        SDL_BlitSurface(menu[i], NULL, ecran, &pos[i]);
    }

    SDL_Flip(ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
            break;

            case SDL_MOUSEMOTION:
                    i=0;
                    x= -1;
                    while(i<5 && x==-1)
                    {
                        if((event.motion.x > pos[i].x)&&(event.motion.x < (pos[i].x + pos[i].w))
                          &&(event.motion.y > pos[i].y)&&(event.motion.y < (pos[i].y + pos[i].h)))
                          {
                              x=i;
                              pos_texte.x =pos[i].x;
                              pos_texte.y =pos[i].y + pos[i].h;
                          }
                          i++;
                    }
                    switch(x)
                   {
                   case 0:
                    texte = TTF_RenderText_Blended(police1, "continue", couleurBeige);
                    break;
                   case 1:
                    texte = TTF_RenderText_Blended(police1, "save", couleurBeige);
                    break;
                   case 2:
                    texte = TTF_RenderText_Blended(police1, "replay", couleurBeige);
                    break;
                   case 3:
                    texte = TTF_RenderText_Blended(police1, "ranking", couleurBeige);
                    break;
                   case 4:
                    texte = TTF_RenderText_Blended(police1, "home", couleurBeige);
                    break;
                   }
            break;

            case SDL_MOUSEBUTTONDOWN:
               if (event.button.button == SDL_BUTTON_LEFT)
               {
                   switch(x)
                   {
                   case 0:
                    init_jeu(ecran, 1);
                    break;
                   case 1:
                    save_jeu(grille, num_piece1, num_piece2, num_piece3, score);
                    break;
                   case 2:
                    init_jeu(ecran, 0);
                    break;
                   case 3:
                    //ranking
                    break;
                   case 4:
                    home(ecran);
                    break;
                   }
               }
               break;
        }
        if(x != -1)
        {
            SDL_BlitSurface(texte, NULL, ecran, &pos_texte); /* Blit du texte */
            SDL_Flip(ecran);
        }

    }

    for(i=0;i<5;i++)
    {
        SDL_FreeSurface(menu[i]);
    }
    SDL_FreeSurface(rectangle);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(titre);

    TTF_CloseFont(police);
    TTF_CloseFont(police1);
    SDL_Quit();
}


/*************************GAME OVER****************************/
void game_over(SDL_Surface *ecran)
{
    SDL_Surface * rectangle = NULL; //la nouvelle surfacee dans l'ecran
    SDL_Surface *texte = NULL;
    SDL_Surface *titre = NULL;
    SDL_Surface* menu[3];
    menu[0]=IMG_Load("big_replay.png");
    menu[1]=IMG_Load("ranking.png");
    menu[2]=IMG_Load("home.png");

    TTF_Font *police = TTF_OpenFont("font.ttf", 24);// Chargement de la police
    TTF_Font *police1 = TTF_OpenFont("font.ttf", 16);
    SDL_Color couleurBeige = {246, 211, 151};
    SDL_Color couleurrouge = {237, 28, 36};

    SDL_Rect pos_texte;
    SDL_Rect pos_titre;
    SDL_Rect position;
    SDL_Rect pos[5];

    pos_titre.x = 200;
    pos_titre.y = 40;

    position.x = 0;
    position.y = 0;

    pos[0].x = 250;
    pos[0].y = 180;

    pos[1].x = 210;
    pos[1].y = 300;

    pos[2].x = 305;
    pos[2].y = 300;


    int continuer = 1, i, x;
    SDL_Event event;

    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 600, 600, 32, 0, 0, 0, 0); //allocation de la surface
    SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 19, 35, 50));//coloration de la surface
    titre = TTF_RenderText_Blended(police, "G A M E  O V E R", couleurrouge);

     /* Transparence Alpha moyenne (128) : */
    SDL_SetAlpha(rectangle, SDL_SRCALPHA, 200);
    /* On blitte l'image maintenant transparente sur le fond : */
    SDL_BlitSurface(rectangle, NULL, ecran, &position);

    SDL_BlitSurface(titre, NULL, ecran, &pos_titre);
    for(i=0;i<3;i++)
    {
        SDL_BlitSurface(menu[i], NULL, ecran, &pos[i]);
    }

    SDL_Flip(ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
            break;

            case SDL_MOUSEMOTION:
                    i=0;
                    x= -1;
                    while(i<3 && x==-1)
                    {
                        if((event.motion.x > pos[i].x)&&(event.motion.x < (pos[i].x + pos[i].w))
                          &&(event.motion.y > pos[i].y)&&(event.motion.y < (pos[i].y + pos[i].h)))
                          {
                              x=i;
                              pos_texte.x =pos[i].x;
                              pos_texte.y =pos[i].y + pos[i].h;
                          }
                          i++;
                    }
                    switch(x)
                   {
                   case 0:
                    texte = TTF_RenderText_Blended(police1, "replay", couleurBeige);
                    break;
                   case 1:
                    texte = TTF_RenderText_Blended(police1, "ranking", couleurBeige);
                    break;
                   case 2:
                    texte = TTF_RenderText_Blended(police1, "home", couleurBeige);
                    break;

                   }
            break;

            case SDL_MOUSEBUTTONDOWN:
               if (event.button.button == SDL_BUTTON_LEFT)
               {
                   switch(x)
                   {
                   case 0:
                    robot(ecran);
                    break;
                   case 1:
                    //ranking
                    break;
                   case 2:
                    home(ecran);
                    break;
                   }
               }
            break;
        }
        if(x != -1)
        {
            SDL_BlitSurface(texte, NULL, ecran, &pos_texte); /* Blit du texte */
            SDL_Flip(ecran);
        }

    }

    for(i=0;i<3;i++)
    {
        SDL_FreeSurface(menu[i]);
    }
    SDL_FreeSurface(rectangle);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(titre);

    TTF_CloseFont(police);
    TTF_CloseFont(police1);
    SDL_Quit();

}
