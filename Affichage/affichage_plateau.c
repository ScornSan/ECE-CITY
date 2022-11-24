#include "../structures.h"
#include "../prototypes.h"

void dessin_bloc_unique(BITMAP *buffer, int k, int l, t_plateau *plateau, int red, int green, int blue) {
    if (k >= 0 && k <= 34 && l <= 44 && l >= 0) {
        int x1 = 26 + 11 * k + l * 13;
        int y1 = 478 + 7 * k - l * 8;
        /// triangle en bas a droitee
        int x4 = 38 + 11 * k + l * 13  ;     // x de base + largeur du bas +1  donc 26 + 11 + 1 = 38
        int y4 = 477 + 7 * k - l * 8   ;      // y de base - 1 donc 477
        /// triangle en haut a gauche
        int x2 = 26 + 13 * l + k * 11  ;
        int y2 = 478 - 8 * l + k * 7   ;
        /// triangle en haut Ã  droite
        int x3 = 40 + 13 * l + k * 11  ;   // x de base + largeur du haut +1  donc 26 + 14 = 40
        int y3 = 477 - 8 * l + k * 7   ;

        for (int i = 0; i < 6; i++) {
            line(buffer, x1 + 2 * i - plateau->screenx + 100, y1 + i - plateau->screeny + 100, x1 + 12 - plateau->screenx + 100, y1 + i - plateau->screeny + 100, makecol(red, green, blue));
        }
        putpixel(buffer, x1 + 11 - plateau->screenx + 100, y1 + 6 - plateau->screeny + 100, makecol(red, green, blue));
        for (int i = 0; i < 7; i++) {
            line(buffer, x2 + 2 * i - plateau->screenx + 100, y2 - i - plateau->screeny + 100, x2 + 14 - plateau->screenx + 100, y2 - i - plateau->screeny + 100, makecol(red, green, blue));
        }
        putpixel(buffer, x2 + 13 - plateau->screenx + 100, y1 + 7 - plateau->screeny + 100, makecol(red, green, blue));
        for (int i = 0; i < 6; i++) {
            line(buffer, x3 - 1 - plateau->screenx + 100 , y3 - i - plateau->screeny + 100, x3 + 12 - 2 * i - plateau->screenx + 100, y3 - i - plateau->screeny + 100, makecol(red, green, blue));
        }
        putpixel(buffer, x3 - plateau->screenx + 100, y3 - 6 - plateau->screeny + 100, makecol(red, green, blue));
        for (int i = 0; i < 7; i++) {
            line(buffer, x4 - 1 - plateau->screenx + 100, y4 + i - plateau->screeny + 100, x4 + 14 - 2 * i - plateau->screenx + 100, y4 + i - plateau->screeny + 100, makecol(red, green, blue));
        }
        putpixel(buffer, x4 - plateau->screenx + 100, y4 + 7 - plateau->screeny + 100, makecol(red, green, blue));
    }
}