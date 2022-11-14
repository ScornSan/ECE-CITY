#include "structures.h"
#include "prototypes.h"

int main(int argc, char *argv[])
{
    allegro_init();
    // pour disposer de la souris
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT,1024,768 ,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(buffer);
    // init. variable de sortie boucle interactive

    t_affichage* hud = init_affichage();
    t_joueur* joueur = init_joueur();
    t_plateau* plateau = init_plateau();
    plateau->batiment = init_batiments();
    menu(hud, joueur, buffer, plateau);

    return 0;
}
END_OF_MAIN();
