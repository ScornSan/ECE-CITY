#include "../structures.h"
#include "../prototypes.h"

t_maillon * creation_maillon(int ligne, int colonne, int compteur){
    t_maillon * maillon = (t_maillon*)malloc(sizeof(t_maillon));
    maillon->ligne = ligne;
    maillon->colonne = colonne;
    maillon->compteur = compteur;
    maillon->predecesseur = NULL;
    maillon->suivant = NULL;
    return maillon;
}

t_file * cases_adjacentes(BITMAP * buffer, t_batiment* batiment, t_plateau *plateau){
    int ligne = batiment->premier_bloc.ligne;
    int colonne = batiment->premier_bloc.colonne;
    t_file * file = (t_file*)malloc(sizeof(t_file));
    file->debut = NULL;
    file->fin = NULL;
    for (int i = ligne ; i < ligne +4;i++){
        if(plateau->matrice[i][colonne-1].element == 13){
            t_maillon *maillon = creation_maillon(i,colonne-1, 1);
            if(file->debut == NULL) {
                file->debut = maillon;
                file->fin = maillon;
            }
            else{
                file->fin->suivant = maillon;
                file->fin = maillon;
            }
        }
        if(plateau->matrice[i][colonne+6].element == 13){
            t_maillon *maillon = creation_maillon(i,colonne+6, 1);
            if(file->debut == NULL) {
                file->debut = maillon;
                file->fin = maillon;
            }
            else{
                file->fin->suivant = maillon;
                file->fin = maillon;
            }
        }
    }
    for (int i = colonne; i < colonne +6;i++){
        if(plateau->matrice[ligne-1][i].element == 13){
            t_maillon *maillon = creation_maillon(ligne-1,i, 1);
            if(file->debut == NULL) {
                file->debut = maillon;
                file->fin = maillon;
            }
            else{
                file->fin->suivant = maillon;
                file->fin = maillon;
            }
        }
        if(plateau->matrice[ligne +4][i].element == 13){
            t_maillon *maillon = creation_maillon(ligne+4,i, 1);
            if(file->debut == NULL){
                file->debut = maillon;
                file->fin = maillon;
            }
            else{
                file->fin->suivant = maillon;
                file->fin = maillon;
            }
        }
    }
    printf("sortie file\n");
    return file;
}

void cond_3_sur_4(int * cond,t_maillon * case_actuelle, t_plateau * plateau){
    int compteur = 0;
    for(int i = 0; i<5; i++){
        cond[i] = 0; /// a modifer plus tard car nouveaux chiffres d'affectation
    }
    //printf("case actuelle colonne = %d, colonne = %d\n",case_actuelle->ligne, case_actuelle->colonne);
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

int doublon_file(t_file* file, int ligne_case, int col_case){
    t_maillon *temp = file->debut;
    int compteur=0;
    while(temp != NULL){
        if(ligne_case == temp->ligne && col_case == temp->colonne){
            compteur = 1;
            break;
        }
        temp = temp->suivant;
    }
    if(compteur == 1)
        return 0;
    else
        return 1;
}

int doublon_ordre(t_plateau* plateau, int id_element, int indice_ordre, int indice){
    int compteur = 0;
    for(int i =0; i <indice_ordre; i++){
        if (id_element == plateau->batiments[indice]->ordre_distribution[i]->id_element){
            compteur = 1;
            break;
        }
    }
    if(compteur == 1)
        return 0;
    else
        return 1;
}

void tri_tab_ordre(t_plateau* plateau){
    for(int i = 0; i <plateau->indice_tab_batiment; i++){
        t_construction * temp;
        for (int k=0 ; k < plateau->batiments[i]->indice_ordre-1; k++)
        {
            for (int j=0 ; j < plateau->batiments[i]->indice_ordre-k-1; j++)
            {
                if (plateau->batiments[i]->ordre_distribution[j]->distance_chateau > plateau->batiments[i]->ordre_distribution[j+1]->distance_chateau)
                {
                    temp = plateau->batiments[i]->ordre_distribution[j];
                    plateau->batiments[i]->ordre_distribution[j] = plateau->batiments[i]->ordre_distribution[j+1];
                    plateau->batiments[i]->ordre_distribution[j+1] = temp;
                }
            }
        }
        free(temp);
        temp = NULL;
    }
}


void dijkstra(BITMAP * buffer, t_plateau * plateau, int affichage){
    t_maillon * case_actuelle;
    int *cond;
    t_maillon *temp;
    t_maillon * maillon;
    t_file * file;
    for(int k = 0; k < plateau->indice_tab_batiment;k++) {
        printf("TOUR BOUCLE\n");
        for (int i = 0; i < 35; i++) {
            for (int j = 0; j < 45; j++) {
                plateau->matrice[i][j].affiche = 0;
            }
        }
        if (plateau->batiments[k]->element == 1) {
            if (plateau->batiments[k] != NULL) {
                file = cases_adjacentes(buffer, plateau->batiments[k], plateau);
                int compteur = 1;
                case_actuelle = file->debut;
                cond = (int*) malloc(sizeof(int) * 9);
                int element_case, ligne_case, colonne_case;
                while (file->debut != NULL) {
                    printf("debut while\n");
                    case_actuelle = file->debut;
                    /// depilage de la case actuelle pour la suite
                    if (file->debut->suivant == NULL) {
                        file->debut = NULL;
                        file->fin = NULL;
                    } else {
                        file->debut = file->debut->suivant;
                    }
                    printf("avvatn affiche\n");
                    if (!plateau->matrice[case_actuelle->ligne][case_actuelle->colonne].affiche) {// si elle est pâs deja visitée
                        if (case_actuelle->compteur < compteur)
                            compteur = case_actuelle->compteur;
                        plateau->matrice[case_actuelle->ligne][case_actuelle->colonne].affiche = 1; // on la marque en visitée
                        cond_3_sur_4(cond, case_actuelle, plateau); // on regarde si c'est pas une fin de route
                        if (cond[0]) {
                            printf("mamamaa");
                            for (int i = 0; i < 4; i++) {    /// on regarde les 4 cases autour
                                if (!cond[i + 1]) {  // si case != extremité
                                    if (i ==0) {    // element prend la valeur de la bonne case et les lignes et colonnes pareil
                                        element_case = plateau->matrice[case_actuelle->ligne -1][case_actuelle->colonne].element;
                                        ligne_case = case_actuelle->ligne - 1;
                                        colonne_case = case_actuelle->colonne;
                                    } else if (i == 1) {
                                        element_case = plateau->matrice[case_actuelle->ligne][case_actuelle->colonne +
                                                                                              1].element;
                                        ligne_case = case_actuelle->ligne;
                                        colonne_case = case_actuelle->colonne + 1;
                                    } else if (i == 3) {
                                        element_case = plateau->matrice[case_actuelle->ligne][case_actuelle->colonne -
                                                                                              1].element;
                                        ligne_case = case_actuelle->ligne;
                                        colonne_case = case_actuelle->colonne - 1;
                                    } else {
                                        element_case = plateau->matrice[case_actuelle->ligne +
                                                                        1][case_actuelle->colonne].element;
                                        ligne_case = case_actuelle->ligne + 1;
                                        colonne_case = case_actuelle->colonne;
                                    }
                                    if (!plateau->matrice[ligne_case][colonne_case].affiche) { // si la case verifié n'est pas encore visitée
                                        if (element_case != 0) { // si case != vide
                                            printf("mamamaa 2 \n");
                                            if (element_case > 4 && element_case < 10) { // si case = habitation
                                                plateau->matrice[ligne_case][colonne_case].affiche = 1;
                                                if (compteur < plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->distance_chateau) {
                                                    printf("mamamaa 2.11 \n");
                                                    /// mise a jour de la distance avec l echateau d'eau le plus proche
                                                    plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->distance_chateau = case_actuelle->compteur;
                                                    plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->derniere_case_chemin = case_actuelle;
                                                } else if (doublon_ordre(plateau,plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->id_element,plateau->batiments[k]->indice_ordre, k)) {
                                                    printf("mamamaa 2.22 \n");
                                                    plateau->batiments[k]->ordre_distribution[plateau->batiments[k]->indice_ordre] = plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element];
                                                    plateau->batiments[k]->indice_ordre++;
                                                    plateau->batiments[k]->ordre_distribution = realloc(plateau->batiments[k]->ordre_distribution,sizeof(t_construction) *(plateau->batiments[k]->indice_ordre + 1));
                                                    //plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->derniere_case_chemin = case_actuelle;
                                                }
                                            } else if (element_case == 13) { // si case = route
                                                printf("mamamaa 3 \n");
                                                compteur++;
                                                if (doublon_file(file, ligne_case, colonne_case)) {
                                                    maillon = creation_maillon(ligne_case, colonne_case, compteur);
                                                    if (file->debut == NULL) {
                                                        file->debut = maillon;
                                                        file->fin = maillon;
                                                    } else {
                                                        file->fin->suivant = maillon;
                                                        file->fin = maillon;
                                                    }
                                                    maillon->predecesseur = case_actuelle;
                                                }
                                            } else
                                                plateau->matrice[ligne_case][colonne_case].affiche = 1;
                                        }
                                    }
                                }
                            }
                        }
                        case_actuelle = file->debut;
                    }
                }
                printf("pas de while");
            }
        }
        tri_tab_ordre(plateau);
    }
    printf("affichage\n");
    if(affichage){
        for(int i = 0; i <plateau->indice_tab_habitations; i++){
            if(plateau->habitations[i]->derniere_case_chemin != NULL){
                temp = plateau->habitations[i]->derniere_case_chemin;
                while(temp != NULL){
                    dessin_bloc_unique(buffer, temp->ligne, temp->colonne,plateau, 255,255,255);
                    temp = temp->predecesseur;
                }
            }
        }
        blit(buffer, screen,0,0,0,0, SCREEN_W, SCREEN_H);
        rest(500);
    }
}