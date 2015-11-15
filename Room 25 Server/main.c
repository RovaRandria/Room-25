#include "game.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

int main(int argc, char** argv) {
    SDL_Surface *ecran, *image;
    SDL_Event event;
    SDL_Rect p;
    Uint32 couleur;
    int i, j;
    int fini = 0;
    Salle complexe[5][5];
    Joueur joueurs[6];
    init_joueurs(joueurs, 5);
    role_joueurs(joueurs, 5);
    for(i = 0; i < 5; i++) {
        fprintf(stderr, "%d\n", joueurs[i].type);
    }
    creer_complexe(complexe, M_SUSPISCION, 1);
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(500, 500, 32, SDL_HWSURFACE);
    while(!fini) {
        SDL_WaitEvent(&event);
        switch(event.type) {
        case SDL_QUIT:
            fini = 1;
        case SDL_MOUSEBUTTONDOWN:
            joueurs[0].action[0] = A_POUSSER;
            joueurs[0].dir[0] = D_BAS;
            joueurs[0].persopousse = 1;
            joueurs[0].action[1] = A_REGARDER;
            joueurs[0].dir[1] = D_DROITE;
            joueurs[1].action[0] = A_CONTROLER;
            joueurs[1].dir[0] = D_GAUCHE;
            joueurs[1].action[1] = A_REGARDER;
            joueurs[1].dir[1] = D_DROITE;
            action(joueurs, 2, 0, complexe);
        }
        for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            switch(complexe[i][j].type) {
            case S_25:
                couleur = SDL_MapRGB(ecran->format, 255, 255, 255);
                image = IMG_Load("Images/Room 25.png");
                break;
            case S_ACIDE:
                couleur = SDL_MapRGB(ecran->format, 0, 255, 0);
                image = IMG_Load("Images/Bain d'acide.png");
                break;
            case S_CONTROLE:
                couleur = SDL_MapRGB(ecran->format, 100, 50, 0);
                image = IMG_Load("Images/Salle de controle.png");
                break;
            case S_DEPART:
                couleur = SDL_MapRGB(ecran->format, 155, 155, 155);
                image = IMG_Load("Images/Salle de depart.png");
                break;
            case S_FROIDE:
                couleur = SDL_MapRGB(ecran->format, 0, 255, 255);
                image = IMG_Load("Images/Chambre froide.png");
                break;
            case S_ILLUSION:
                couleur = SDL_MapRGB(ecran->format, 55, 55, 55);
                image = IMG_Load("Images/Salle des illusions.png");
                break;
            case S_INONDABLE:
                couleur = SDL_MapRGB(ecran->format, 0, 0, 255);
                image = IMG_Load("Images/Salle inondable.png");
                break;
            case S_JUMELLE:
                couleur = SDL_MapRGB(ecran->format, 255, 0, 255);
                image = IMG_Load("Images/Salle tunnel.png");
                break;
            case S_MOBILE:
                couleur = SDL_MapRGB(ecran->format, 255, 255, 0);
                image = IMG_Load("Images/Salle mobile.png");
                break;
            case S_MORTELLE:
                couleur = SDL_MapRGB(ecran->format, 255, 0, 0);
                image = IMG_Load("Images/Salle mortelle.png");
                break;
            case S_NOIRE:
                couleur = SDL_MapRGB(ecran->format, 50, 0, 50);
                image = IMG_Load("Images/Chambre noire.png");
                break;
            case S_PIEGE:
                couleur = SDL_MapRGB(ecran->format, 255, 155, 0);
                image = IMG_Load("Images/Salle piegee.png");
                break;
            case S_PRISON:
                couleur = SDL_MapRGB(ecran->format, 100, 100, 0);
                image = IMG_Load("Images/Salle prison.png");
                break;
            case S_VIDE:
                couleur = SDL_MapRGB(ecran->format, 0, 0, 0);
                image = IMG_Load("Images/Salle vide.png");
                break;
            case S_VISION:
                couleur = SDL_MapRGB(ecran->format, 255, 100, 255);
                image = IMG_Load("Images/Salle de vision.png");
                break;
            case S_VORTEX:
                couleur = SDL_MapRGB(ecran->format, 0, 100, 100);
                image = IMG_Load("Images/Salle vortex.png");
                break;
            }
            p.x = i * 100;
            p.y = j * 100;
            SDL_BlitSurface(image, NULL, ecran, &p);
            /*p.w = 100;
            p.h = 100;
            SDL_FillRect(ecran, &p, couleur);*/
        }
    }
    SDL_Flip(ecran);
    }
    SDL_FreeSurface(image);
    SDL_Quit();
    return EXIT_SUCCESS;
}
