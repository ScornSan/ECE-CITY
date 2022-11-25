#include "../structures.h"
#include "../prototypes.h"

void sauvegarde( t_joueur* joueur, t_plateau* plateau){

    FILE *ifs_plateau = fopen("../ifs_plateau.txt", "w"); /// ouvertue du fichier en mode ecriture
    FILE *ifs_habitation = fopen("../ifs_habitation.txt", "w"); /// ouvertue du fichier en mode ecriture
    FILE *ifs_batiment = fopen("../ifs_batiment.txt", "w"); /// ouvertue du fichier en mode ecriture
    FILE *ifs_joueur = fopen("../ifs_joueur.txt", "w"); /// ouvertue du fichier en mode ecriture
    /// On écrase l'ancienne map et on sauvegarde la nouvelle (celle de notre partie déjà commencée

    /// STRUCTURE JOUEUR
    fprintf(ifs_joueur, "%d", joueur->mode);
    fprintf(ifs_joueur, "\n");
    fprintf(ifs_joueur, "%d", joueur->niveau);
    fprintf(ifs_joueur, "\n");
    fprintf(ifs_joueur, "%d", joueur->argent);
    fprintf(ifs_joueur, "\n");
    fprintf(ifs_joueur, "%d", joueur->habitants);
    fprintf(ifs_joueur, "\n");
    fprintf(ifs_joueur, "%d", joueur->totaleau);
    fprintf(ifs_joueur, "\n");
    fprintf(ifs_joueur, "%d", joueur->totalelec);

    /// STRUCTURE PLATEAU
    fprintf(ifs_plateau, "%d", plateau->indice_tab_habitations);
    fprintf(ifs_plateau, "\n");
    fprintf(ifs_plateau, "%d", plateau->indice_tab_batiment);
    fprintf(ifs_plateau, "\n");
    fprintf(ifs_plateau, "%d", plateau->lig_mouse);
    fprintf(ifs_plateau, "\n");
    fprintf(ifs_plateau, "%d", plateau->col_mouse);
    fprintf(ifs_plateau, "\n");

    for(int i = 0; i< 35; i++){                                   /// MATRICE MAP
        for(int j = 0; j < 45; j++){
            fprintf(ifs_plateau, "%d ", plateau->matrice_map[i][j]);
        }
        fprintf(ifs_plateau, "\n");
    }
    /////////
    for(int i = 0; i< 35; i++){                                   /// MATRICE
        for(int j = 0; j < 45; j++){
            fprintf(ifs_plateau, "%d ", plateau->matrice[i][j].element);
            fprintf(ifs_plateau, "%d ", plateau->matrice[i][j].id_element);
            fprintf(ifs_plateau, "%d ", plateau->matrice[i][j].x_bloc);
            fprintf(ifs_plateau, "%d ", plateau->matrice[i][j].y_bloc);
            fprintf(ifs_plateau, "%d ", plateau->matrice[i][j].affiche);
            fprintf(ifs_plateau, "%d ", plateau->matrice[i][j].ligne);
            fprintf(ifs_plateau, "%d ", plateau->matrice[i][j].colonne);
        }
        fprintf(ifs_plateau, "\n");
    }

    //fprintf(ifs_habitation, "STRUCTURE CONSTRUCTION");
    //fprintf(ifs_habitation, "\n");
    for(int i = 0; i < plateau->indice_tab_habitations; i++)            /// STRUCTURE T_CONSTRUCTION
    {
        fprintf(ifs_habitation, "%d", plateau->habitations[i]->niveau);
        fprintf(ifs_habitation, "\n");
        fprintf(ifs_habitation, "%d", plateau->habitations[i]->nb_residents);
        fprintf(ifs_habitation, "\n");
        fprintf(ifs_habitation, "%d", plateau->habitations[i]->incendie);
        fprintf(ifs_habitation, "\n");
        fprintf(ifs_habitation, "%d", plateau->habitations[i]->eau);
        fprintf(ifs_habitation, "\n");
        fprintf(ifs_habitation, "%d", plateau->habitations[i]->elec);
        fprintf(ifs_habitation, "\n");
        fprintf(ifs_habitation, "%d", plateau->habitations[i]->distance_centrale);
        fprintf(ifs_habitation, "\n");
        fprintf(ifs_habitation, "%d", plateau->habitations[i]->distance_chateau);
        fprintf(ifs_habitation, "\n");
        fprintf(ifs_habitation, "%d", plateau->habitations[i]->quantite_eau);
        fprintf(ifs_habitation, "\n");
        fprintf(ifs_habitation, "%d", plateau->habitations[i]->quantite_elec);
        fprintf(ifs_habitation, "\n");
        fprintf(ifs_habitation, "%d", plateau->habitations[i]->id_element);
        fprintf(ifs_habitation, "\n");
        fprintf(ifs_habitation, "%d", (plateau->habitations[i]->premier_bloc).id_element);
        fprintf(ifs_habitation, "\n");
        fprintf(ifs_habitation, "%d", (plateau->habitations[i]->premier_bloc).element);
        fprintf(ifs_habitation, "\n");
        fprintf(ifs_habitation, "%d", (plateau->habitations[i]->premier_bloc).affiche);
        fprintf(ifs_habitation, "\n");
        fprintf(ifs_habitation, "%d", (plateau->habitations[i]->premier_bloc).colonne);
        fprintf(ifs_habitation, "\n");
        fprintf(ifs_habitation, "%d", (plateau->habitations[i]->premier_bloc).ligne);
        fprintf(ifs_habitation, "\n");
        fprintf(ifs_habitation, "%d", (plateau->habitations[i]->premier_bloc).x_bloc);
        fprintf(ifs_habitation, "\n");
        fprintf(ifs_habitation, "%d", (plateau->habitations[i]->premier_bloc).y_bloc);
        fprintf(ifs_habitation, "\n");
    }


    //fprintf(ifs_batiment, "STRUCTURE BATIMENT");
    //fprintf(ifs_batiment, "\n");
    for(int i = 0; i < plateau->indice_tab_batiment; i++)            /// STRUCTURE T_BATIMENT
    {
        fprintf(ifs_batiment, "%d", plateau->batiments[i]->id_batiment);
        fprintf(ifs_batiment, "\n");
        fprintf(ifs_batiment, "%d", plateau->batiments[i]->indice_ordre);
        fprintf(ifs_batiment, "\n");
        fprintf(ifs_batiment, "%d", plateau->batiments[i]->quantite_ressource);
        fprintf(ifs_batiment, "\n");
        fprintf(ifs_batiment, "%d", plateau->batiments[i]->id_batiment);
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
    ifs_plateau = NULL;
    ifs_batiment=NULL;
    ifs_joueur = NULL;
    ifs_habitation = NULL;
    /// si on veut continuer la partie après sauvegarde ou juste quitter après sauvegarde
}


