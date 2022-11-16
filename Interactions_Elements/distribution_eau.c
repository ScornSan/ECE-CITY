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

t_file * cases_adjacentes(BITMAP * buffer, t_batiment* batiment, t_plateau *plateau){
    int ligne = batiment->premier_bloc.ligne;
    int colonne = batiment->premier_bloc.colonne;
    t_file *file = (t_file*)malloc(sizeof(t_file));
    file->debut = NULL;
    file->fin = NULL;
    for (int i = ligne ; i < ligne +4;i++){
        if(plateau->matrice[i][colonne-1].element == 12){
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
        if(plateau->matrice[i][colonne+6].element == 12){
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
        if(plateau->matrice[ligne-1][i].element == 12){
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
        if(plateau->matrice[ligne +4][i].element == 12){
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
    t_maillon *temp = file->debut;
    while(temp != NULL){
        dessin_bloc_unique(buffer,temp->ligne, temp->colonne, plateau, 0,0,0);
        temp = temp->suivant;
    }
    blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
    rest(2000);
    return file;
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
    t_file * file = cases_adjacentes(buffer, plateau->batiments[1], plateau);
    int compteur = 1;
    t_maillon * case_actuelle = file->debut;
    int *cond;
    while(case_actuelle != NULL){
        cond = cond_3_sur_4(cond, case_actuelle, plateau);
        if(cond[0]){
            printf(" continue while\n");
        }
        else
            printf(" arrete while \n");
        case_actuelle = case_actuelle->suivant;
    }

}