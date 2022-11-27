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

int doublon_ordre_chateau(t_plateau* plateau, int id_element, int indice_ordre, int indice){
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

int doublon_ordre_centrale(t_plateau* plateau, int id_element, int indice_ordre, int indice){
    int compteur = 0;
    for(int i =0; i <indice_ordre; i++){
        if (id_element == plateau->batiments[indice]->ordre_centrale[i]->id_element){
            compteur = 1;
            break;
        }
    }
    if(compteur == 1)
        return 0;
    else
        return 1;
}

void tri_aleatoire(t_plateau* plateau,int indice){
    t_construction *temp;
    if(plateau->batiments[indice]->ordre_centrale[0] != NULL){
        for(int i = 0 ;i <20; i++){
            printf("ca paseee ");
            int nb_alea1 = rand()%(plateau->batiments[indice]->indice_ordre_centrale);
            int nb_alea2 = rand()%(plateau->batiments[indice]->indice_ordre_centrale);
            temp = plateau->batiments[indice]->ordre_centrale[nb_alea1];
            printf("ou ");
            plateau->batiments[indice]->ordre_centrale[nb_alea1] = plateau->batiments[indice]->ordre_centrale[nb_alea2];
            printf("ca ");
            plateau->batiments[indice]->ordre_centrale[nb_alea2] = temp;
            printf("casse ");
        }
    }
}

void bfs_eau(BITMAP * buffer, t_plateau * plateau, int indice){
    t_maillon * case_actuelle;
    int *cond;
    t_maillon *temp;
    t_maillon * maillon;
    t_file * file;
    for(int k = 0; k < plateau->indice_tab_batiment;k++) {
        plateau->batiments[k]->indice_ordre = 0;
        plateau->batiments[k]->indice_ordre_centrale = 0;
        //printf("TOUR BOUCLE\n");
        for (int i = 0; i < 35; i++) {
            for (int j = 0; j < 45; j++) {
                plateau->matrice[i][j].affiche = 0;
            }
        }
        if (plateau->batiments[k]->element == indice) {
            if (plateau->batiments[k] != NULL) {
                file = cases_adjacentes(buffer, plateau->batiments[k], plateau);
                int compteur = 1;
                case_actuelle = file->debut;
                cond = (int*) malloc(sizeof(int) * 9);
                int element_case, ligne_case, colonne_case;
                while (file->debut != NULL) {
                    //printf("debut while\n");
                    case_actuelle = file->debut;
                    /// depilage de la case actuelle pour la suite
                    if (file->debut->suivant == NULL) {
                        file->debut = NULL;
                        file->fin = NULL;
                    } else {
                        file->debut = file->debut->suivant;
                    }
                    //printf("avvatn affiche\n");
                    if (!plateau->matrice[case_actuelle->ligne][case_actuelle->colonne].affiche) {// si elle est pâs deja visitée
                        if (case_actuelle->compteur < compteur)
                            compteur = case_actuelle->compteur;
                        plateau->matrice[case_actuelle->ligne][case_actuelle->colonne].affiche = 1; // on la marque en visitée
                        cond_3_sur_4(cond, case_actuelle, plateau); // on regarde si c'est pas une fin de route
                        if (cond[0]) {
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
                                            //printf("mamamaa 2 \n");
                                            if (element_case > 4 && element_case < 10) { // si case = habitation
                                                plateau->matrice[ligne_case][colonne_case].affiche = 1;
                                                if(indice == CHATEAU_EAU){
                                                    if (compteur < plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->distance_chateau) {
                                                        /// mise a jour de la distance avec l echateau d'eau le plus proche
                                                        plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->distance_chateau = case_actuelle->compteur;
                                                        plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->derniere_case_chemin = case_actuelle;
                                                    } else if (doublon_ordre_chateau(plateau,plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->id_element,plateau->batiments[k]->indice_ordre, k)) {
                                                        plateau->batiments[k]->ordre_distribution[plateau->batiments[k]->indice_ordre] = plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element];
                                                        plateau->batiments[k]->indice_ordre++;
                                                        plateau->batiments[k]->ordre_distribution = realloc(plateau->batiments[k]->ordre_distribution,sizeof(t_construction) *(plateau->batiments[k]->indice_ordre + 1));
                                                        //plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->derniere_case_chemin = case_actuelle;
                                                    }
                                                }
                                                else if(indice == CENTRALE){
                                                    if (compteur < plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->distance_centrale) {
                                                        //printf("mamamaa 2.11 \n");
                                                        /// mise a jour de la distance avec l echateau d'eau le plus proche
                                                        plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->distance_centrale = case_actuelle->compteur;
                                                        plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->derniere_case_centrale = case_actuelle;
                                                    } else if (doublon_ordre_centrale(plateau,plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element]->id_element,plateau->batiments[k]->indice_ordre_centrale, k)) {
                                                        //printf("mamamaa 2.22 \n");
                                                        plateau->batiments[k]->ordre_centrale[plateau->batiments[k]->indice_ordre_centrale] = plateau->habitations[plateau->matrice[ligne_case][colonne_case].id_element];
                                                        plateau->batiments[k]->indice_ordre_centrale++;
                                                        plateau->batiments[k]->ordre_centrale = realloc(plateau->batiments[k]->ordre_centrale,sizeof(t_construction) *(plateau->batiments[k]->indice_ordre_centrale + 1));
                                                    }
                                                    printf("affiche\n");
                                                }
                                            } else if (element_case == 13) { // si case = route
                                                //printf("mamamaa 3 \n");
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
                    }
                }
            }
        }
        if(indice == CENTRALE){
            printf("barbare tu es\n");
            tri_aleatoire(plateau,k);
            printf("SUITE");
        }
    }
    printf("dijFIN\n");
}

void distribution_eau(t_plateau * plateau){
    for (int i = 0; i<plateau->indice_tab_habitations;i++){
        plateau->habitations[i]->quantite_eau = 0;
    }
    for(int k = 0; k < plateau->indice_tab_batiment;k++) {
        if(plateau->batiments[k]->element == 1){
            plateau->batiments[k]->quantite_ressource = 5022;
            for(int i = 0; i<plateau->batiments[k]->indice_ordre; i++){
                while(plateau->batiments[k]->quantite_ressource > 0 && plateau->batiments[k]->ordre_distribution[i]->quantite_eau < plateau->batiments[k]->ordre_distribution[i]->nb_residents){
                    plateau->batiments[k]->quantite_ressource -= 1;
                    plateau->batiments[k]->ordre_distribution[i]->quantite_eau++;
                }
                if(plateau->batiments[k]->ordre_distribution[i]->quantite_eau > 0)
                    plateau->batiments[k]->ordre_distribution[i]->eau = 1;
                else
                    plateau->batiments[k]->ordre_distribution[i]->eau = 0;
            }
        }
    }
}

void distribution_elec(t_plateau * plateau){
    for (int i = 0; i<plateau->indice_tab_habitations;i++){
        plateau->habitations[i]->quantite_elec = 0;
    }
    for(int k = 0; k < plateau->indice_tab_batiment;k++) {
        if(plateau->batiments[k]->element == 2){
            plateau->batiments[k]->quantite_ressource = 5022;
            for(int i = 0; i<plateau->batiments[k]->indice_ordre_centrale; i++){
                printf("nb resident = %d, quantite d'elec = %d, calcul = %d\n",plateau->batiments[k]->ordre_centrale[i]->nb_residents, plateau->batiments[k]->quantite_ressource,plateau->batiments[k]->quantite_ressource -plateau->batiments[k]->ordre_centrale[i]->nb_residents);
                if(plateau->batiments[k]->quantite_ressource -plateau->batiments[k]->ordre_centrale[i]->nb_residents >= 0){
                    while(plateau->batiments[k]->ordre_centrale[i]->quantite_eau < plateau->batiments[k]->ordre_centrale[i]->nb_residents){
                        printf("augmentation elec\n");
                        plateau->batiments[k]->quantite_ressource -= 1;
                        plateau->batiments[k]->ordre_centrale[i]->quantite_eau++;
                    }
                        if(plateau->batiments[k]->ordre_centrale[i]->quantite_elec > 0)
                        plateau->batiments[k]->ordre_centrale[i]->elec = 1;
                    else
                        plateau->batiments[k]->ordre_centrale[i]->elec = 0;
                    printf("vgalide = %d",plateau->batiments[k]->ordre_centrale[i]->elec);
                }
            }
        }
    }
}