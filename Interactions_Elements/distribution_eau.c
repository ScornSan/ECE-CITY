#include "../structures.h"
#include "../prototypes.h"

t_maillon * creation_maillon(int ligne, int colonne, int compteur){
    t_maillon * maillon = (t_maillon*)malloc(sizeof(t_maillon));
    maillon->ligne = ligne;
    maillon->colonne = colonne;
    maillon->compteur = compteur;
    maillon->suivant = NULL;
    maillon->precedent = NULL;
    return maillon;
}

t_pile * cases_adjacentes(BITMAP * buffer, t_batiment* batiment, t_plateau *plateau){
    int ligne = batiment->premier_bloc.ligne;
    int colonne = batiment->premier_bloc.colonne;
    t_pile * pile = (t_pile*)malloc(sizeof(t_pile));
    pile->debut = NULL;
    pile->fin = NULL;
    for (int i = ligne ; i < ligne +4;i++){
        if(plateau->matrice[i][colonne-1].element == 12){
            t_maillon *maillon = creation_maillon(i,colonne-1, 1);
            if(pile->debut == NULL) {
                pile->debut = maillon;
                pile->fin = maillon;
            }
            else{
                pile->fin->suivant = maillon;
                maillon->precedent = pile->fin;
                pile->fin = maillon;
            }
        }
        if(plateau->matrice[i][colonne+6].element == 12){
            t_maillon *maillon = creation_maillon(i,colonne+6, 1);
            if(pile->debut == NULL) {
                pile->debut = maillon;
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
        if(plateau->matrice[ligne-1][i].element == 12){
            t_maillon *maillon = creation_maillon(ligne-1,i, 1);
            if(pile->debut == NULL) {
                pile->debut = maillon;
                pile->fin = maillon;
            }
            else{
                pile->fin->suivant = maillon;
                maillon->precedent = pile->fin;
                pile->fin = maillon;
            }
        }
        if(plateau->matrice[ligne +4][i].element == 12){
            t_maillon *maillon = creation_maillon(ligne+4,i, 1);
            if(pile->debut == NULL){
                pile->debut = maillon;
                pile->fin = maillon;
            }
            else{
                pile->fin->suivant = maillon;
                maillon->precedent = pile->fin;
                pile->fin = maillon;
            }
        }
    }
    t_maillon *temp = pile->debut;
    while(temp != NULL){
        dessin_bloc_unique(buffer,temp->ligne, temp->colonne, plateau, 0,0,0);
        temp = temp->suivant;
    }
    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
    rest(2000);
    return pile;
}

int* cond_3_sur_4(int * cond,t_maillon * case_actuelle, t_plateau * plateau){
    int tab[9];
    cond = tab;
    int compteur = 0;
    for(int i = 0; i<5; i++){
        cond[i] = 0; /// a modifer plus tard car nouveaux chiffres d'affectation
    }
    if(case_actuelle->ligne == 0) {  // si case == extremité du haut
        cond[1] = 1;
        compteur++;
    }
    if(case_actuelle->ligne == 34) { // si case == extremité du bas
        cond[3] = 1;
        compteur++;
    }
    if(case_actuelle->colonne == 0) { // si case == extremité de gauche
        cond[4] = 1;
        compteur++;
    }
    if(case_actuelle->colonne == 44) {  // si case == extremité de droite
        cond[2] = 1;
        compteur++;
    }
    int element;
    for(int i = 0; i< 4; i++){
        if(cond[i+1] == 0){  // si case != extremité
            if(i == 0)
                element = plateau->matrice[case_actuelle->ligne -1][case_actuelle->colonne].element;
            else if (i == 1)
                element = plateau->matrice[case_actuelle->ligne ][case_actuelle->colonne +1].element;
            else if(i == 3)
                element = plateau->matrice[case_actuelle->ligne +1][case_actuelle->colonne].element;
            else
                element = plateau->matrice[case_actuelle->ligne ][case_actuelle->colonne-1].element;
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
    return cond;
}

void dijkstra(BITMAP * buffer, t_plateau * plateau){
    t_pile * pile = cases_adjacentes(buffer, plateau->batiments[plateau->indice_tab_batiment], plateau);
    int compteur = 1;
    t_maillon * case_actuelle = pile->fin;
    int *cond;
    int element_case, ligne_case, colonne_case;
    while(case_actuelle != NULL){
        /// depilage de la case actuelle pour la suite
        pile->fin->precedent->suivant = NULL;
        pile->fin = pile->fin->precedent;

        if (!plateau->matrice[case_actuelle->ligne][case_actuelle->colonne].affiche){// si elle est pâs deja visitée
            plateau->matrice[case_actuelle->ligne][case_actuelle->colonne].affiche = 1; // on la marque en visitée
            cond = cond_3_sur_4(cond, case_actuelle, plateau); // on regarde si c'est pas une fin de route
            if(cond[0]){
                for(int i = 0; i< 4; i++){    /// on regarde les 4 cases autour
                    if(!cond[i+1]){  // si case != extremité
                        if(i == 0) {    // element prend la valeur de la bonne case et les lignes et colonnes pareil
                            element_case = plateau->matrice[case_actuelle->ligne - 1][case_actuelle->colonne].element;
                            ligne_case = case_actuelle->ligne - 1;
                            colonne_case = case_actuelle->colonne;
                        }
                        else if (i == 1){
                            element_case = plateau->matrice[case_actuelle->ligne ][case_actuelle->colonne +1].element;
                            ligne_case = case_actuelle->ligne;
                            colonne_case = case_actuelle->colonne +1;
                        }
                        else if(i == 3){
                            element_case = plateau->matrice[case_actuelle->ligne +1][case_actuelle->colonne].element;
                            ligne_case = case_actuelle->ligne +1;
                            colonne_case = case_actuelle->colonne;
                        }
                        else{
                            element_case = plateau->matrice[case_actuelle->ligne ][case_actuelle->colonne-1].element;
                            ligne_case = case_actuelle->ligne;
                            colonne_case = case_actuelle->colonne-1;
                        }
                        if (!plateau->matrice[ligne_case][colonne_case].affiche){ // si la case verifié n'est pas e,core visitée
                            plateau->matrice[ligne_case][colonne_case].affiche = 1;
                            if(element_case != 0){ // si case != vide
                                if(element_case > 4) { // si case = habitation
                                    if(compteur < plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->distance_chateau){
                                        /// mise a jour de la distance avec l echateau d'eau le plus proche
                                        plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->distance_chateau = case_actuelle->compteur;
                                        plateau->batiments[plateau->indice_tab_batiment]->ordre_distribution[plateau->batiments[plateau->indice_tab_batiment]->indice_ordre] = plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element];
                                    }
                                    else
                                        plateau->batiments[plateau->indice_tab_batiment]->ordre_distribution[plateau->batiments[plateau->indice_tab_batiment]->indice_ordre] = plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element];
                                }
                                else if (element_case == 12){ // si case = route
                                    // carrefour

                                }
                                else
                                    compteur++; // case considérée comme vide
                            }
                        }

                    }
                }
                printf(" continue while\n");
            }
            else{
                printf(" arrete while \n");

            }
        }
        case_actuelle = pile->fin;
    }

}