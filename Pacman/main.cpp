#define FPS_LIMIT 60

#include <iostream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"

using namespace std;
using namespace nsGraphics;
using namespace nsShape;

void dessiner(MinGL &window)
{
    window << Rectangle(Vec2D(70, 100), Vec2D(1170, 150), KBlue);
    window << Rectangle(Vec2D(70,100), Vec2D(120, 700), KBlue);
    window << Rectangle(Vec2D(1400, 20), Vec2D(1420,50), KYellow);
    window << Rectangle(Vec2D(1405, 25), Vec2D(1415,45), KBlack);
    window << Rectangle(Vec2D(1425, 20), Vec2D(1445,50), KYellow);
    window << Rectangle(Vec2D(1430, 25), Vec2D(1440,45), KBlack);
}

int main()
{
    // Initialise le système
    MinGL window("01 - Shapes", nsGraphics::Vec2D(1500, 800), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On dessine les formes géométriques
        dessiner(window);

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }

    return 0;
}
