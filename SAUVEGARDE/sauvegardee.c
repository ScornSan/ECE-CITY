#include "../structures.h"
#include "../prototypes.h"

void sauvegarde( t_joueur* joueur, t_plateau* plateau){

    FILE *ifs_plateau = fopen("../ifs_plateau.txt", "w"); /// ouvertue du fichier en mode ecriture
    FILE *ifs_habitation = fopen("../ifs_habitation.txt", "w"); /// ouvertue du fichier en mode ecriture
    FILE *ifs_batiment = fopen("../ifs_batiment.txt", "w"); /// ouvertue du fichier en mode ecriture
    FILE *ifs_joueur = fopen("../ifs_joueur.txt", "w"); /// ouvertue du fichier en mode ecriture
    /// On écrase l'ancienne map et on sauvegarde la nouvelle (celle de notre partie déjà commencée

    /// STRUCTURE JOUEUR
    fprintf(ifs_joueur, "%d\n", joueur->mode);
    fprintf(ifs_joueur, "%d\n", joueur->niveau);
    fprintf(ifs_joueur, "%d\n", joueur->argent);
    fprintf(ifs_joueur, "%d\n", joueur->habitants);
    fprintf(ifs_joueur, "%d\n", joueur->totaleau);
    fprintf(ifs_joueur, "%d\n", joueur->totalelec);


    /// STRUCTURE PLATEAU
    fprintf(ifs_plateau, "%d\n", plateau->indice_tab_habitations);
    fprintf(ifs_plateau, "%d\n", plateau->indice_tab_batiment);
    fprintf(ifs_plateau, "%d\n", plateau->lig_mouse);
    fprintf(ifs_plateau, "%d\n", plateau->col_mouse);
    fprintf(ifs_plateau, "%d\n", plateau->screenx);
    fprintf(ifs_plateau, "%d\n", plateau->screeny);
    fprintf(ifs_plateau, "%d\n", plateau->lig);
    fprintf(ifs_plateau, "%d\n", plateau->col);
    // Load terrain
    // Load buffer pixel
    // Load calque pixel
    // BITMAPS routes

    /// MATRICE

    for(int i = 0; i< 35; i++){
        for(int j = 0; j < 45; j++){

            fprintf(ifs_plateau, "%d\n", plateau->matrice[i][j].element);
            fprintf(ifs_plateau, "%d\n", plateau->matrice[i][j].id_element);
            fprintf(ifs_plateau, "%d\n", plateau->matrice[i][j].x_bloc);
            fprintf(ifs_plateau, "%d\n", plateau->matrice[i][j].y_bloc);
            fprintf(ifs_plateau, "%d\n", plateau->matrice[i][j].affiche);
            fprintf(ifs_plateau, "%d\n", plateau->matrice[i][j].ligne);
            fprintf(ifs_plateau, "%d\n", plateau->matrice[i][j].colonne);
            for (int k = 0; k < 3; k++)
                fprintf(ifs_plateau, "%d\n", plateau->matrice[i][j].RGB[k]);

            fprintf(ifs_plateau, "%d\n", plateau->matrice[i][j].id_bitmap);
        }
    }

    //fprintf(ifs_habitation, "STRUCTURE CONSTRUCTION");
    //fprintf(ifs_habitation, "\n");
    for(int i = 0; i < plateau->indice_tab_habitations; i++)            /// STRUCTURE T_CONSTRUCTION
    {
        fprintf(ifs_habitation, "%d\n", plateau->habitations[i]->niveau);
        fprintf(ifs_habitation, "%d\n", plateau->habitations[i]->nb_residents);
        fprintf(ifs_habitation, "%d\n", plateau->habitations[i]->incendie);
        fprintf(ifs_habitation, "%d\n", plateau->habitations[i]->eau);
        fprintf(ifs_habitation, "%d\n", plateau->habitations[i]->elec);
        fprintf(ifs_habitation, "%d\n", plateau->habitations[i]->distance_centrale);
        fprintf(ifs_habitation, "%d\n", plateau->habitations[i]->distance_chateau);
        fprintf(ifs_habitation, "%d\n", plateau->habitations[i]->quantite_eau);
        fprintf(ifs_habitation, "%d\n", plateau->habitations[i]->quantite_elec);
        fprintf(ifs_habitation, "%d\n", plateau->habitations[i]->id_element);
        //fprintf(ifs_habitation, "%d\n", plateau->habitations[i]->timer);
        fprintf(ifs_habitation, "%d\n", (plateau->habitations[i]->premier_bloc).id_element);
        fprintf(ifs_habitation, "%d\n", (plateau->habitations[i]->premier_bloc).element);
        fprintf(ifs_habitation, "%d\n", (plateau->habitations[i]->premier_bloc).affiche);
        fprintf(ifs_habitation, "%d\n", (plateau->habitations[i]->premier_bloc).colonne);
        fprintf(ifs_habitation, "%d\n", (plateau->habitations[i]->premier_bloc).ligne);
        fprintf(ifs_habitation, "%d\n", (plateau->habitations[i]->premier_bloc).x_bloc);
        fprintf(ifs_habitation, "%d\n", (plateau->habitations[i]->premier_bloc).y_bloc);
        // BITMAP style[6]
        // t_bloc surface[3][3]
        // t_maillon* derniere case chemin
    }


    for(int i = 0; i < plateau->indice_tab_batiment; i++)            /// STRUCTURE T_BATIMENT
    {
        fprintf(ifs_batiment, "%d", plateau->batiments[i]->id_batiment);
        fprintf(ifs_batiment, "\n");
        fprintf(ifs_batiment, "%d", plateau->batiments[i]->indice_ordre);
        fprintf(ifs_batiment, "\n");
        fprintf(ifs_batiment, "%d", plateau->batiments[i]->quantite_ressource);
        fprintf(ifs_batiment, "\n");
        fprintf(ifs_batiment, "%d", plateau->batiments[i]->element);
        fprintf(ifs_batiment, "\n");
        fprintf(ifs_batiment, "%d", (plateau->batiments[i]->premier_bloc).id_element);
        fprintf(ifs_batiment, "\n");
        fprintf(ifs_batiment, "%d", (plateau->batiments[i]->premier_bloc).element);
        fprintf(ifs_batiment, "\n");
        fprintf(ifs_batiment, "%d", (plateau->batiments[i]->premier_bloc).affiche);
        fprintf(ifs_batiment, "\n");
        fprintf(ifs_batiment, "%d", (plateau->batiments[i]->premier_bloc).colonne);
        fprintf(ifs_batiment, "\n");
        fprintf(ifs_batiment, "%d", (plateau->batiments[i]->premier_bloc).ligne);
        fprintf(ifs_batiment, "\n");
        fprintf(ifs_batiment, "%d", (plateau->batiments[i]->premier_bloc).x_bloc);
        fprintf(ifs_batiment, "\n");
        fprintf(ifs_batiment, "%d", (plateau->batiments[i]->premier_bloc).y_bloc);
        fprintf(ifs_batiment, "\n");
    }

    fclose(ifs_plateau);
    fclose(ifs_batiment);
    fclose(ifs_habitation);
    fclose(ifs_joueur);
    /// si on veut continuer la partie après sauvegarde ou juste quitter après sauvegarde
}


