#include "../structures.h"
#include "../prototypes.h"

t_maillon * creation_maillon(int ligne, int colonne, int compteur){
    t_maillon * maillon = (t_maillon*)malloc(sizeof(t_maillon));
    maillon->ligne = ligne;
    maillon->colonne = colonne;
    maillon->compteur = compteur;
    maillon->suivant = NULL;
    return maillon;
}

t_pile * cases_adjacentes(BITMAP * buffer, t_batiment* batiment, t_plateau *plateau){
    int ligne = batiment->premier_bloc.ligne;
    int colonne = batiment->premier_bloc.colonne;
    t_pile * pile = (t_pile*)malloc(sizeof(t_pile));
    pile->debut = NULL;
    pile->fin = NULL;
    for (int i = ligne ; i < ligne +4;i++){
        if(plateau->matrice[i][colonne-1].element == 13){
            t_maillon *maillon = creation_maillon(i,colonne-1, 1);
            if(pile->debut == NULL) {
                pile->debut = maillon;
                maillon->precedent = NULL;
                pile->fin = maillon;
            }
            else{
                pile->fin->suivant = maillon;
                maillon->precedent = pile->fin;
                pile->fin = maillon;
            }
        }
        if(plateau->matrice[i][colonne+6].element == 13){
            t_maillon *maillon = creation_maillon(i,colonne+6, 1);
            if(pile->debut == NULL) {
                pile->debut = maillon;
                maillon->precedent = NULL;
                pile->fin = maillon;
            }
            else{
                pile->fin->suivant = maillon;
                maillon->precedent = pile->fin;
                pile->fin = maillon;
            }
        }
    }
    for (int i = colonne; i < colonne +6;i++){
        if(plateau->matrice[ligne-1][i].element == 13){
            t_maillon *maillon = creation_maillon(ligne-1,i, 1);
            if(pile->debut == NULL) {
                pile->debut = maillon;
                maillon->precedent = NULL;
                pile->fin = maillon;
            }
            else{
                pile->fin->suivant = maillon;
                maillon->precedent = pile->fin;
                pile->fin = maillon;
            }
        }
        if(plateau->matrice[ligne +4][i].element == 13){
            t_maillon *maillon = creation_maillon(ligne+4,i, 1);
            if(pile->debut == NULL){
                pile->debut = maillon;
                maillon->precedent = NULL;
                pile->fin = maillon;
            }
            else{
                pile->fin->suivant = maillon;
                maillon->precedent = pile->fin;
                pile->fin = maillon;
            }
        }
    }
    return pile;

}

void cond_3_sur_4(int * cond,t_maillon * case_actuelle, t_plateau * plateau){
    int compteur = 0;
    for(int i = 0; i<5; i++){
        cond[i] = 0; /// a modifer plus tard car nouveaux chiffres d'affectation
    }
    //printf("case actuelle colonne = %d, colonne = %d\n",case_actuelle->ligne, case_actuelle->colonne);
    if(case_actuelle->ligne == 0) {  // si case == extremité du haut
        printf("extremite du haut\n");
        cond[1] = 1;
        compteur++;
    }
    if(case_actuelle->ligne == 34) { // si case == extremité du bas
        printf("extremite du bas\n");
        cond[3] = 1;
        compteur++;
    }
    if(case_actuelle->colonne == 0) { // si case == extremité de gauche
        printf("extremite de gauche\n");
        cond[4] = 1;
        compteur++;
    }
    if(case_actuelle->colonne == 44) {  // si case == extremité de droite
        printf("extremite de droite\n");
        cond[2] = 1;
        compteur++;
    }
    int element;
    for(int i = 0; i< 4; i++){
        if(cond[i+1] == 0){  // si case != extremité
            if(i == 0) {
                element = plateau->matrice[case_actuelle->ligne - 1][case_actuelle->colonne].element;
                //printf("case verifiee ligne = %d, colonne = %d\n",case_actuelle->ligne - 1,case_actuelle->colonne );
            }
            else if (i == 1) {
                element = plateau->matrice[case_actuelle->ligne][case_actuelle->colonne + 1].element;
                //printf("case verifiee ligne = %d, colonne = %d\n",case_actuelle->ligne,case_actuelle->colonne +1);
            }
            else if(i == 3) {
                element = plateau->matrice[case_actuelle->ligne][case_actuelle->colonne - 1].element;
                //printf("case verifiee ligne = %d, colonne = %d\n",case_actuelle->ligne ,case_actuelle->colonne -1);
            }
            else {
                element = plateau->matrice[case_actuelle->ligne + 1][case_actuelle->colonne].element;
                //printf("case verifiee ligne = %d, colonne = %d\n",case_actuelle->ligne + 1,case_actuelle->colonne );
            }
            if(element != 0){ // si case != vide
                if(element == 12) // si case = route
                    cond[i+5] = 12;
                else if (element > 4){ // si case = habitation
                    cond[i+5] = element;
                }
                else
                    compteur++; // case considérée comme vide
            }
            else
                compteur++;
        }
    }
    if(compteur != 4){
        cond[0] = 1;
    }
}

void dijkstra(BITMAP * buffer, t_plateau * plateau){
    if(plateau->batiments[plateau->indice_tab_batiment-1] != NULL){
        printf("\n");
        for(int i = 0; i<35; i++){
            for(int j = 0; j<45; j++){
                printf("%d ", plateau->matrice[i][j].element);
            }
            printf("\n");
        }
        t_pile * pile = cases_adjacentes(buffer, plateau->batiments[plateau->indice_tab_batiment-1], plateau);
        int compteur = 1;
        t_maillon * case_actuelle = pile->fin;
        int *cond = (int*)malloc(sizeof(int) * 9);
        int element_case, ligne_case, colonne_case;
        printf("debut while\n");
        while(pile->fin != NULL){
            printf("\n");
            t_maillon *temp = pile->debut;
            while(temp != NULL){
                printf("ligne = %d, colonne = %d -> ", temp->ligne, temp->colonne);
                temp = temp->suivant;
            }
            case_actuelle = pile->fin;
            printf("\n");
            printf("----------TOUR DE BOUCLE-------------\n");
            printf("compteur = %d\n", compteur);
            temp = pile->debut;
            while(temp != NULL){
                dessin_bloc_unique(buffer,temp->ligne, temp->colonne, plateau, 0,0,0);
                temp = temp->suivant;
            }
            blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
            /// depilage de la case actuelle pour la suite
            printf("pile fin ligne = %d et colonne = %d\n",pile->fin->ligne, pile->fin->colonne);
            if(pile->fin->precedent == NULL) {
                printf("rentre");
                pile->debut = NULL;
                pile->fin = NULL;
            }
            else{
                pile->fin = pile->fin->precedent;
                pile->fin->suivant = NULL;
            }
            if (!plateau->matrice[case_actuelle->ligne][case_actuelle->colonne].affiche){// si elle est pâs deja visitée
                plateau->matrice[case_actuelle->ligne][case_actuelle->colonne].affiche = 1; // on la marque en visitée
                compteur++;
                compteur = case_actuelle->compteur;
                cond_3_sur_4(cond, case_actuelle, plateau); // on regarde si c'est pas une fin de route
                printf("tableau cond i0 = %d, i1 = %d, i2 = %d, i3 = %d, i4 = %d\n", cond[0], cond[1], cond[2], cond[3], cond[4]);
                if(cond[0]){
                    printf("pas de fin de case\n");
                    for(int i = 0; i< 4; i++){    /// on regarde les 4 cases autour
                        if(!cond[i+1]){  // si case != extremité
                            printf("tour for\n");

                            if(i == 0) {    // element prend la valeur de la bonne case et les lignes et colonnes pareil
                                element_case = plateau->matrice[case_actuelle->ligne - 1][case_actuelle->colonne].element;
                                printf("element_case = %d\n",element_case);
                                ligne_case = case_actuelle->ligne - 1;
                                colonne_case = case_actuelle->colonne;
                                dessin_bloc_unique(buffer, ligne_case, colonne_case, plateau, 30*(i+1),0,0);
                            }
                            else if (i == 1){
                                element_case = plateau->matrice[case_actuelle->ligne][case_actuelle->colonne +1].element;
                                printf("element_case = %d\n",element_case);
                                ligne_case = case_actuelle->ligne;
                                colonne_case = case_actuelle->colonne +1;
                                dessin_bloc_unique(buffer, ligne_case, colonne_case, plateau, 30*(i+1),0,0);
                            }
                            else if(i == 3){
                                element_case = plateau->matrice[case_actuelle->ligne ][case_actuelle->colonne-1].element;
                                printf("element_case = %d\n",element_case);
                                ligne_case = case_actuelle->ligne;
                                colonne_case = case_actuelle->colonne-1;
                                dessin_bloc_unique(buffer, ligne_case, colonne_case, plateau, 30*(i+1),0,0);
                            }
                            else{
                                element_case = plateau->matrice[case_actuelle->ligne +1][case_actuelle->colonne].element;
                                printf("element_case = %d\n",element_case);
                                ligne_case = case_actuelle->ligne +1;
                                colonne_case = case_actuelle->colonne;
                                dessin_bloc_unique(buffer, ligne_case, colonne_case, plateau, 30*(i+1),0,0);
                            }
                            if (!plateau->matrice[ligne_case][colonne_case].affiche){ // si la case verifié n'est pas encore visitée
                                printf("case pas encore affiche\n");
                                if(element_case != 0){ // si case != vide
                                    if(element_case > 4 && element_case < 10) { // si case = habitation
                                        printf("la case est une MAISON\n");
                                        plateau->matrice[ligne_case][colonne_case].affiche = 1;
                                        if(compteur < plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->distance_chateau){
                                            /// mise a jour de la distance avec l echateau d'eau le plus proche
                                            printf("mise a jour de la distance\n");
                                            plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->distance_chateau = case_actuelle->compteur;
                                        }
                                        plateau->batiments[plateau->indice_tab_batiment -1]->ordre_distribution[plateau->batiments[plateau->indice_tab_batiment -1]->indice_ordre] = plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element];
                                    }
                                    else if (element_case == 13){ // si case = route
                                        printf("la case est une ROUTE\n");
                                        t_maillon * maillon = creation_maillon(ligne_case, colonne_case, compteur);
                                        if(pile->debut == NULL) {
                                            pile->debut = maillon;
                                            maillon->precedent = NULL;
                                            pile->fin = maillon;
                                        }
                                        else{
                                            pile->fin->suivant = maillon;
                                            maillon->precedent = pile->fin;
                                            pile->fin = maillon;
                                        }
                                    }
                                    else {
                                        printf("autre = %d   \n", element_case);
                                        plateau->matrice[ligne_case][colonne_case].affiche = 1;
                                    }
                                }
                                else
                                    printf("case vide\n");
                            }
                            else
                                printf("case deja affiche\n");
                        }
                        else
                            printf("c'est une extremite\n");
                        blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
                        rest(100);
                    }
                }
                else{
                    printf(" fin de route \n");
                }
            }
            else
                printf("saut de case\n");
            printf("\n");
            temp = pile->debut;
            while(temp != NULL){
                printf("ligne = %d, colonne = %d -> ", temp->ligne, temp->colonne);
                temp = temp->suivant;
            }
            case_actuelle = pile->fin;
        }
    }
}