#include "game.h"

void ajouter_pioche(int *pioche, int *taille, int elt) {
    pioche[*taille] = elt;
    (*taille)++;
}

void creer_complexe(Salle complexe[][5], Mode m, int expert) {
    TypeSalle pioche[22];
    int taille = 0;
    int random;
    int i, j, k;
    complexe[2][2].type = S_DEPART;
    complexe[2][2].visible = 1;
    ajouter_pioche(pioche, &taille, S_VIDE);
    ajouter_pioche(pioche, &taille, S_VIDE);
    ajouter_pioche(pioche, &taille, S_VIDE);
    ajouter_pioche(pioche, &taille, S_VIDE);
    ajouter_pioche(pioche, &taille, S_VIDE);
    ajouter_pioche(pioche, &taille, S_NOIRE);
    ajouter_pioche(pioche, &taille, S_NOIRE);
    ajouter_pioche(pioche, &taille, S_FROIDE);
    ajouter_pioche(pioche, &taille, S_FROIDE);
    ajouter_pioche(pioche, &taille, S_PIEGE);
    ajouter_pioche(pioche, &taille, S_PIEGE);
    ajouter_pioche(pioche, &taille, S_INONDABLE);
    ajouter_pioche(pioche, &taille, S_INONDABLE);
    ajouter_pioche(pioche, &taille, S_ACIDE);
    ajouter_pioche(pioche, &taille, S_ACIDE);
    ajouter_pioche(pioche, &taille, S_VORTEX);
    ajouter_pioche(pioche, &taille, S_MORTELLE);
    ajouter_pioche(pioche, &taille, S_CONTROLE);
    if(expert) {
        ajouter_pioche(pioche, &taille, S_ILLUSION);
        if(m == M_SUSPISCION) {
            ajouter_pioche(pioche, &taille, S_VIDE);
            ajouter_pioche(pioche, &taille, S_VIDE);
            ajouter_pioche(pioche, &taille, S_MORTELLE);
            ajouter_pioche(pioche, &taille, S_MOBILE);
        }
        else {
            ajouter_pioche(pioche, &taille, S_JUMELLE);
            ajouter_pioche(pioche, &taille, S_JUMELLE);
            ajouter_pioche(pioche, &taille, S_PRISON);
            ajouter_pioche(pioche, &taille, S_PRISON);
        }
    }
    else {
        ajouter_pioche(pioche, &taille, S_VIDE);
        ajouter_pioche(pioche, &taille, S_VIDE);
        ajouter_pioche(pioche, &taille, S_VIDE);
        ajouter_pioche(pioche, &taille, S_VIDE);
        ajouter_pioche(pioche, &taille, S_VORTEX);
    }
    srand(time(NULL));
    for(i = 0; i < 5; i++) {
        for(j = abs(i - 2); j <= 4 - abs(i - 2); j++) {
            if(i != 2 || j != 2) {
                random = rand() % taille;
                complexe[i][j].type = pioche[random];
                complexe[i][j].visible = 0;
                taille--;
                for(k = random; k < taille; k++) {
                    pioche[k] = pioche[k+1];
                }
            }
        }
    }
    pioche[taille] = S_25;
    taille++;
    pioche[taille] = S_VISION;
    taille++;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            if(j < abs(i - 2) || j > 4 - abs(i - 2)) {
                random = rand() % taille;
                complexe[i][j].type = pioche[random];
                complexe[i][j].visible = 0;
                taille--;
                for(k = random; k < taille; k++) {
                    pioche[k] = pioche[k+1];
                }
            }
        }
    }
}

void role_joueurs(Joueur *joueurs, int nbjoueurs) {
    int i, k, random;
    int taille = 0;
    TypeJoueur pioche[6];
    srand(time(NULL));
    ajouter_pioche(pioche, &taille, J_GARDIEN);
    ajouter_pioche(pioche, &taille, J_PRISONNIER);
    ajouter_pioche(pioche, &taille, J_PRISONNIER);
    ajouter_pioche(pioche, &taille, J_PRISONNIER);
    ajouter_pioche(pioche, &taille, J_PRISONNIER);
    if(nbjoueurs >= 5)
        ajouter_pioche(pioche, &taille, J_GARDIEN);
    for(i = 0; i < nbjoueurs; i++) {
        random = rand() % taille;
        joueurs[i].type = pioche[random];
        taille--;
        for(k = random; k < taille; k++) {
            pioche[k] = pioche[k+1];
        }
    }
}

void init_joueurs(Joueur *joueurs, int nbjoueurs) {
    int i;
    for(i = 0; i < nbjoueurs; i++) {
        joueurs[i].mort = 0;
        joueurs[i].posx = 2;
        joueurs[i].posy = 2;
        joueurs[i].type = J_NORMAL;
    }
}

void action(Joueur *joueurs, int nbjoueurs, int debut, Mode mode, Salle complexe[][5]) {
    int i, j, n;
    Salle tmp;
    for(n = 0; n < 2; n++) {
        for(i = 0; i < nbjoueurs; i++) {
            if(joueurs[(i+debut)%nbjoueurs].type == J_GARDIEN) {
                //programmation
            }
            switch(joueurs[(i+debut)%nbjoueurs].action[n]) {
            case A_DEPLACER:
                switch(joueurs[(i+debut)%nbjoueurs].dir[n]) {
                case D_HAUT:
                    joueurs[(i+debut)%nbjoueurs].posy--;
                    break;
                case D_BAS:
                    joueurs[(i+debut)%nbjoueurs].posy++;
                    break;
                case D_GAUCHE:
                    joueurs[(i+debut)%nbjoueurs].posx--;
                    break;
                case D_DROITE:
                    joueurs[(i+debut)%nbjoueurs].posx++;
                    break;
                }
                break;
                effet_salle(joueurs, joueurs[(i+debut)%nbjoueurs], n, mode, complexe);
            case A_POUSSER:
                switch(joueurs[(i+debut)%nbjoueurs].dir[n]) {
                case D_HAUT:
                    joueurs[joueurs[(i+debut)%nbjoueurs].persopousse].posy = (joueurs[joueurs[(i+debut)%nbjoueurs].persopousse].posy - 1)%5;
                    break;
                case D_BAS:
                    joueurs[joueurs[(i+debut)%nbjoueurs].persopousse].posy = (joueurs[joueurs[(i+debut)%nbjoueurs].persopousse].posy + 1)%5;
                    break;
                case D_GAUCHE:
                    joueurs[joueurs[(i+debut)%nbjoueurs].persopousse].posx = (joueurs[joueurs[(i+debut)%nbjoueurs].persopousse].posx - 1)%5;
                    break;
                case D_DROITE:
                    joueurs[joueurs[(i+debut)%nbjoueurs].persopousse].posx = (joueurs[joueurs[(i+debut)%nbjoueurs].persopousse].posx + 1)%5;
                    break;
                }
                Joueur joueur_pousse = joueurs[joueurs[(i+debut)%nbjoueurs].persopousse];
                effet_salle(joueurs, joueur_pousse, n, mode, complexe);
                break;
            case A_REGARDER:
                switch(joueurs[(i+debut)%nbjoueurs].dir[n]) {
                case D_HAUT:
                    //Regarder haut
                    break;
                case D_BAS:
                    //Regarder bas
                    break;
                case D_GAUCHE:
                    //Regarder gauche
                    break;
                case D_DROITE:
                    //Regarder droite
                    break;
                }
                break;
            case A_CONTROLER:
                controler(joueurs, joueurs[(i+debut)%nbjoueurs].posx, joueurs[(i+debut)%nbjoueurs].posy, joueurs[(i+debut)%nbjoueurs].dir[n], nbjoueurs, complexe);
                break;
            }
        }
    }
}

void controler(Joueur *joueurs, int posx, int posy, Direction direction, int nbjoueurs, Salle complexe[5][5]){
    Salle tmp;
    int j;

    // impossible de controler 2 fois une ligne ou une colonne dans un même tour, dans 2 sens différents

    switch(direction) {
    case D_HAUT:
        if (posx!=2){
            tmp = complexe[posx][0];
            for(j = 0; j < 4; j++) {
                complexe[posx][j] = complexe[posx][j+1];
            }
            complexe[posx][4] = tmp;
            for(j = 0; j < nbjoueurs; j++) {
                if(joueurs[j].posx == posx)
                    joueurs[j].posy = (joueurs[j].posy - 1)%5;
            }
        }
        else{
            // Controle impossible
        }
        break;
    case D_BAS:
        if (posx!=2){
            tmp = complexe[posx][4];
            for(j = 4; j > 0; j--) {
                complexe[posx][j] = complexe[posx][j-1];
            }
            complexe[posx][0] = tmp;
            for(j = 0; j < nbjoueurs; j++) {
                if(joueurs[j].posx == posx)
                    joueurs[j].posy = (joueurs[j].posy + 1)%5;
            }
        }
        else{
            // Controle impossible
        }
        break;
    case D_GAUCHE:
        if (posy != 2){
            tmp = complexe[0][posy];
            for(j = 0; j < 4; j++) {
                complexe[j][posy] = complexe[j+1][posy];
            }
            complexe[4][posy] = tmp;
            for(j = 0; j < nbjoueurs; j++) {
                if(joueurs[j].posy == posy)
                    joueurs[j].posx = (joueurs[j].posx - 1)%5;
            }
        }
        else{
            // Controle impossible
        }
        break;
    case D_DROITE:
        if (posy != 2){
            tmp = complexe[4][posy];
            for(j = 4; j > 0; j--) {
                complexe[j][posy] = complexe[j-1][posy];
            }
            complexe[0][posy] = tmp;
            for(j = 0; j < nbjoueurs; j++) {
                if(joueurs[j].posy == posy)
                    joueurs[j].posx = (joueurs[j].posx + 1)%5;
            }
        }
        else{
            // Controle impossible
        }
        break;
    }
}






void jouer() {
    Salle complexe[5][5];
    Joueur joueurs[6];
    Mode mode;
    int nbjoueurs, expert, fini, debut;
    fini = 0;
    debut = 0;
    //Choix du mode
    //Choix des joueurs
    init_joueurs(joueurs, nbjoueurs);
    if(mode = M_SUSPISCION)
        role_joueurs(joueurs, nbjoueurs);
    creer_complexe(complexe, mode, expert);
    //Afficher complexe
    //Indice de départ
    while(!fini) {
        //Programmation
        //Action
        action(joueurs, nbjoueurs, debut, mode, complexe);
        //Décompte
        debut = (debut + 1) % nbjoueurs;
    }
}

void effet_salle(Joueur *joueurs, Joueur joueur_actuel, int nbjoueurs, Mode mode, Salle complexe[5][5]){
    Salle salle = complexe[joueur_actuel.posx][joueur_actuel.posy];
    Salle tmp;
    salle.visible = 1;

    int x=0, y=0, trouve, nb_joueur_salle;
    Direction direction;

    switch (salle.type){
    case S_DEPART:
        break;
    case S_25:
        // condition de victoire
        switch (mode){
        case M_SUSPISCION:
            if (joueur_actuel.type==J_PRISONNIER){

            }
            break;
        case M_COMPETITION:
            break;
        case M_EQUIPE:
            break;
        case M_COOPERATION:
            nb_joueur_salle = nombre_joueur_salle(joueurs, joueur_actuel.posx, joueur_actuel.posy, nbjoueurs);
            if (nbjoueurs==nb_joueur_salle){
                // s'il n'y a aucun mort ==> victoire totale
                // s'il y en a un ==> victoire partielle
                // sinon défaite
            }
            break;
        case M_SOLO:
            nb_joueur_salle = nombre_joueur_salle(joueurs, joueur_actuel.posx, joueur_actuel.posy, nbjoueurs);
            if (nbjoueurs==nb_joueur_salle){
                // S'il n'y a aucun mort ==> victoire
                // Sinon défaite
            }
            break;
        }
        break;
    case S_VORTEX:
        joueur_actuel.posx = 2;
        joueur_actuel.posy = 2;
        effet_salle(joueurs, joueur_actuel, nbjoueurs, mode, complexe);
        break;
    case S_VISION:
        // On demande au client quelle salle est ce qu'il veut regarder
        // On reçoit du client les coordonnées de la salle souhaitée
        x=0;
        y=0;
        // Il peut voir la salle
        break;
    case S_PIEGE:
        // si prochaine action != déplacer
        // joueur.mort = 1;
        break;
    case S_MOBILE:
        //On demande au client avec quelle salle est ce qu'il veut changer sa position
        //On reçoit du client les coordonnées de la salle souhaitée
        x = 0;
        y = 0;
        tmp = complexe[x][y];
        complexe[x][y] = complexe[joueur_actuel.posx][joueur_actuel.posy];
        complexe[joueur_actuel.posx][joueur_actuel.posy] = tmp;
        break;
    case S_CONTROLE:
        //On demande au client la direction dans laquelle il veut effectuer le contrôle
        //On reçoit du client la direction souhaitée
        direction = D_BAS;
        controler(joueurs, joueur_actuel.posx, joueur_actuel.posy, direction, nbjoueurs, complexe);
        break;
    case S_JUMELLE:
        trouve = rechercher_salle (S_JUMELLE, joueur_actuel.posx, joueur_actuel.posy, complexe, tmp, &x, &y);
        if (trouve){
            if (tmp.visible){
                joueur_actuel.posx = x;
                joueur_actuel.posy = y;
            }
        }
        break;
    default:
        break;
    }
}

int rechercher_salle (TypeSalle type, int posX_actuel, int posY_actuel, Salle complexe[5][5], Salle salle, int *posX, int *posY){
    int i=0, j=0;

    while (i<5 && j<5){
        if (complexe[i][j].type==type && complexe[i][j].visible==1 && i!=posX_actuel && j!=posY_actuel){
            salle = complexe[i][j];
            *posX = i;
            *posY = j;
            return 1;
        }
        i++;
        j++;
    }
    return 0;
}


int nombre_joueur_salle(Joueur *joueurs, int x, int y, int nb_max_joueur){
    int nb = 0, i;
    for (i=0; i<nb_max_joueur; i++){
        if (joueurs[i].posx==x && joueurs[i].posy==y){
            nb++;
        }
    }
    return nb;
}
