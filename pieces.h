#ifndef PIECES_H_INCLUDED
#define PIECES_H_INCLUDED

void construire_piece(int piece[][NB_PIECES], int num_piece);

void creer_piece(SDL_Surface *ecran, int num_piece,int piece[][NB_PIECES], SDL_Rect pos, SDL_Rect position[][NB_PIECES]);

void bliter_piece(SDL_Surface *ecran, int piece[][NB_PIECES], SDL_Rect position[][NB_PIECES]);

void bliter_grille(SDL_Surface *ecran, int piece[][NB_BLOCS], SDL_Rect position[][NB_BLOCS]);

int clic_piece(int piece[][NB_PIECES], SDL_Rect position[][NB_PIECES], SDL_Event event);

void deplacer_piece(int piece[][NB_PIECES], SDL_Rect position[][NB_PIECES], int pasx, int pasy);

int verifycoordo(int grille[][NB_BLOCS], int x, int y, int piece[][NB_PIECES]);

void placer_piece(int grille[][NB_BLOCS], int x, int y, int piece[][NB_PIECES]);

void placer_grille(SDL_Surface *ecran, int grille[][NB_BLOCS], int *num_piece, int *score, int piece[][NB_PIECES],
                    SDL_Rect pos, SDL_Rect pos_piece[][NB_PIECES], SDL_Rect pos_grille[][NB_BLOCS]);

int collision(int piece[][NB_PIECES], SDL_Rect position[][NB_PIECES]);

void piece_inaccessible(SDL_Surface *ecran, SDL_Rect pos, int piece[][NB_PIECES]);

void vider_ligne(int grille[][NB_BLOCS], int lignes[NB_BLOCS]);

void vider_colonne(int grille[][NB_BLOCS], int columns[NB_BLOCS]);

void copier_grille(int grille[][NB_BLOCS], int copygrille[][NB_BLOCS]);

int pieces_dispo(int copygrille[][NB_BLOCS]);

place compare_pieces(place c1, place c2);



#endif // PIECES_H_INCLUDED
