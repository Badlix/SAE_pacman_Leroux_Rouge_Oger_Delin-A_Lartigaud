#define FPS_LIMIT 60

#include <iostream>
#include <thread>

#include "mingl/mingl.h"
#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"

#include "functions.h"
#include "constants.h"

using namespace std;
using namespace nsGraphics;
using namespace nsShape;
using namespace functions;
using namespace constants;

int main() {
    showMaze(maze1);
}


//int main()
//{
//    // Initialise le système
//    MinGL window("Pacman", Vec2D(1500, 800), Vec2D(128, 128), nsGraphics::KBlack);
//    window.initGlut();
//    window.initGraphic();

//    // Variable qui tient le temps de frame
//    chrono::microseconds frameTime = chrono::microseconds::zero();

//    // On fait tourner la boucle tant que la fenêtre est ouverte
//    while (window.isOpen())
//    {
//        // Récupère l'heure actuelle
//        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

//        // On efface la fenêtre
//        window.clearScreen();

//        // On dessine les formes géométriques
//        dessiner(window);

//        // On finit la frame en cours
//        window.finishFrame();

//        // On vide la queue d'évènements
//        window.getEventManager().clearEvents();

//        // On attend un peu pour limiter le framerate et soulager le CPU
//        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

//        // On récupère le temps de frame
//        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
//    }
//    return 0;
//}
