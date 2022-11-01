#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

void home(SDL_Surface *ecran);

void menu_pause(SDL_Surface *ecran, int grille[][NB_BLOCS], int *num_piece1, int *num_piece2, int *num_piece3, int *score);

void game_over(SDL_Surface *ecran);

#endif // MENU_H_INCLUDED
