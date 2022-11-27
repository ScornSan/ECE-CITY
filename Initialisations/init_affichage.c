#include "../structures.h"
#include "../prototypes.h"

t_affichage* init_affichage(t_plateau *plateau){
    t_affichage *hud = (t_affichage*) malloc(sizeof(t_affichage));
    hud->mode = load_bitmap("../BITMAPS/mode.bmp",0);
    hud->nom = load_bitmap("../BITMAPS/nom.bmp",0);
    hud->pauseselec = load_bitmap("../BITMAPS/HUD/pauseselec.bmp",0);
    hud->credits = load_bitmap("../BITMAPS/credits.bmp",0);
    hud->bouton_menu = load_bitmap("../BITMAPS/HUD/bouton_menu.bmp",0);
    hud->bouton_menu2 = load_bitmap("../BITMAPS/HUD/bouton_menu2.bmp",0);
    hud->son_on = load_bitmap("../BITMAPS/HUD/son_on.bmp",0);
    hud->son_off = load_bitmap("../BITMAPS/HUD/son_off.bmp",0);
    hud->accueil = load_bitmap("../BITMAPS/accueil.bmp",0);
    hud->argent = load_bitmap("../BITMAPS/HUD/Cash.bmp", 0);
    hud->bg = load_bitmap("../BITMAPS/HUD/Bg.bmp", 0);
    hud->bg_on = load_bitmap("../BITMAPS/HUD/BgOn.bmp", 0);
    hud->eau = load_bitmap("../BITMAPS/HUD/Water.bmp", 0);
    hud->eau_outline = load_bitmap("../BITMAPS/HUD/WaterOutline.bmp", 0);
    hud->elec = load_bitmap("../BITMAPS/HUD/Energy.bmp", 0);
    hud->elec_outline = load_bitmap("../BITMAPS/HUD/EnergyOutline.bmp", 0);
    hud->construct = load_bitmap("../BITMAPS/HUD/Construct.bmp", 0);
    hud->construct_outline = load_bitmap("../BITMAPS/HUD/ConstructOutline.bmp", 0);
    hud->habitants = load_bitmap("../BITMAPS/HUD/Habitants.bmp", 0);
    hud->habitants_outline = load_bitmap("../BITMAPS/HUD/HabitantsOutline.bmp", 0);
    hud->banque = load_bitmap("../BITMAPS/HUD/banque.bmp", 0);
    hud->Sbanque = load_bitmap("../BITMAPS/HUD/Sbanque.bmp", 0);
    hud->cursor = load_bitmap("../BITMAPS/HUD/Cursor.bmp", 0);
    hud->chantier = load_bitmap("../BITMAPS/HUD/chantier.bmp", 0);
    hud->Nonchantier = load_bitmap("../BITMAPS/HUD/Nchantier.bmp", 0);
    hud->Schantier = load_bitmap("../BITMAPS/HUD/Schantier.bmp", 0);
    hud->cabane = load_bitmap("../BITMAPS/BUILDS/cabane.bmp", 0);
    hud->maison = load_bitmap("../BITMAPS/BUILDS/maison.bmp", 0);
    hud->building = load_bitmap("../BITMAPS/BUILDS/building.bmp", 0);
    hud->gratteciel = load_bitmap("../BITMAPS/BUILDS/gratteciel.bmp", 0);
    hud->chateau = load_bitmap("../BITMAPS/HUD/chateau.bmp", 0);
    hud->centrale = load_bitmap("../BITMAPS/HUD/centrale.bmp", 0);
    hud->caserne = load_bitmap("../BITMAPS/HUD/caserne.bmp", 0);
    hud->banque = load_bitmap("../BITMAPS/HUD/banque.bmp", 0);
    hud->Nonchateau = load_bitmap("../BITMAPS/HUD/Nchateau.bmp", 0);
    hud->Noncentrale = load_bitmap("../BITMAPS/HUD/Ncentrale.bmp", 0);
    hud->Noncaserne = load_bitmap("../BITMAPS/HUD/Ncaserne.bmp", 0);
    hud->Nonbanque = load_bitmap("../BITMAPS/HUD/Nbanque.bmp", 0);
    hud->Scaserne = load_bitmap("../BITMAPS/HUD/caserne_selec.bmp", 0);
    hud->Scentrale = load_bitmap("../BITMAPS/HUD/centrale_selec.bmp", 0);
    hud->Schateau = load_bitmap("../BITMAPS/HUD/chateau_selec.bmp", 0);
    hud->Sbanque = load_bitmap("../BITMAPS/HUD/Sbanque.bmp", 0);
    hud->route = load_bitmap("../BITMAPS/HUD/routes.bmp", 0);
    hud->Nonroute = load_bitmap("../BITMAPS/HUD/Nroutes.bmp", 0);
    hud->Sroute = load_bitmap("../BITMAPS/HUD/Sroutes.bmp", 0);
    hud->case_eau = load_bitmap("../BITMAPS/HUD/case_eau.bmp", 0);
    hud->case_elec = load_bitmap("../BITMAPS/HUD/case_elec.bmp", 0);
    hud->moinsun = load_bitmap("../BITMAPS/HUD/-1.bmp", 0);
    hud->moinsdeux = load_bitmap("../BITMAPS/HUD/-2.bmp", 0);


    hud->construction[0][0] = load_bitmap("../BITMAPS/HUD/Nchateau.bmp", 0);       /// NON chateau
    hud->construction[0][1] = load_bitmap("../BITMAPS/BUILDS/chateau.bmp", 0);       /// chateau
    hud->construction[0][2] = load_bitmap("../BITMAPS/HUD/chateau_selec.bmp", 0);      /// select_chateau

    hud->construction[1][0] = load_bitmap("../BITMAPS/HUD/Ncentrale.bmp", 0);     /// NON centrale
    hud->construction[1][1] = load_bitmap("../BITMAPS/BUILDS/centrale.bmp", 0);      /// centrale
    hud->construction[1][2] = load_bitmap("../BITMAPS/HUD/centrale_selec.bmp", 0);      /// select_centrale

    hud->construction[2][0] = load_bitmap("../BITMAPS/HUD/Ncaserne.bmp", 0);       /// NON caserne
    hud->construction[2][1] = load_bitmap("../BITMAPS/BUILDS/caserne.bmp", 0);      /// caserne
    hud->construction[2][2] = load_bitmap("../BITMAPS/HUD/caserne_selec.bmp", 0);     /// select_caserne

    hud->construction[3][0] = load_bitmap("../BITMAPS/HUD/Nbanque.bmp", 0);     /// NON ecole
    hud->construction[3][1] = load_bitmap("../BITMAPS/BUILDS/banque.bmp", 0);     /// ecole
    hud->construction[3][2] = load_bitmap("../BITMAPS/HUD/Sbanque.bmp", 0);     /// select_ecole

    hud->construction[4][0] = load_bitmap("../BITMAPS/HUD/Nchantier.bmp", 0);     /// Nterrain vague/chantier
    hud->construction[4][1] = load_bitmap("../BITMAPS/HUD/chantier.bmp", 0);     /// terrain vague/chantier
    hud->construction[4][2] = load_bitmap("../BITMAPS/HUD/Schantier.bmp", 0);     /// select_terrain vague/chantier

    hud->construction[5][1] = load_bitmap("../BITMAPS/BUILDS/cabane.bmp", 0);     /// cabane
    hud->construction[6][1] = load_bitmap("../BITMAPS/BUILDS/maison.bmp", 0);     /// maison
    hud->construction[7][1] = load_bitmap("../BITMAPS/BUILDS/building.bmp", 0);     /// immeuble
    hud->construction[8][1] = load_bitmap("../BITMAPS/BUILDS/gratteciel.bmp", 0);     /// gratte_ciel
    // son
    hud->son_menu = load_sample("../MUSIC/son_menu.wav");
    hud->son_jeu = load_sample("../MUSIC/son_jeu.wav");

    hud->buffer2 = create_bitmap(SCREEN_W, SCREEN_H);

    return hud;
}

