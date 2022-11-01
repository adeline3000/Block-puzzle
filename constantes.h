#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#define X 130
#define Y 50
#define TAILLE_BLOC 34 // Taille d'un block (carré) en pixels
#define NB_BLOCS 10    //Le nombre de blocks dans la grille
#define TAILLE_GRILLE TAILLE_BLOC * NB_BLOCS
#define NB_PIECES 5 //Le nombre maximale de blocks qu'une pièce peut avoir
#define TAILLE_PIECE TAILLE_BLOC * NB_PIECES

enum {VIDE, ROUGE, VERT, BLEU, JAUNE, ORANGE, VIOLET};//ces constantes correspondent aux couleurs des blocs

typedef struct place place;

struct place
    {
        int vide;
        int score;
        int nb;
        int lig;
        int col;
    };


#endif // CONSTANTES_H_INCLUDED
