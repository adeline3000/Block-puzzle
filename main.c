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

int main(int argc, char *argv[])
{
   /* int score;
    int meilleurscore;

   // enter user name at the strat of the game
    //playername="Saad";
    //load best score
      static const char filename[]="Score.dat";
    FILE *file=fopen(filename,"r");
    char line [8000];

    if (file !=NULL)
    {
        fgets(line,sizeof line,file) != NULL;
        {
        }
        fclose(file);

    }
    else
    {
        perror(filename);
    }

    char scoreint[20];
    int z=5;
    while(line[z]!='\0'){
        scoreint[z-5]=line[z]; z++;
    }
    scoreint[z-1]='\0';
    meilleurscore=atoi(scoreint);




   score=0;
*/

   SDL_Surface *ecran = NULL;//le pointeur qui va stocker la surface de l'écran


   SDL_Init(SDL_INIT_VIDEO);//charge la SDL en mémoire (charge le système vidéo)
   TTF_Init();//demarre SDL_ttf
   SDL_WM_SetIcon(IMG_Load("icone.png"), NULL); // L'icône doit être chargée avant SDL_SetVideoMode
   ecran = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);// ouverture d'une fenetre
   SDL_WM_SetCaption("BLOCK PUZZLE", NULL);//titre de la fenetre

    home(ecran);//on appelle le menu

    TTF_Quit();//arrete SDL_ttf
    SDL_Quit(); //libère SDL de la mémoire
    return EXIT_SUCCESS;// valeur à renvoyer en cas de réussite du programme
}
