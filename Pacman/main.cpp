#define FPS_LIMIT 60

#include <iostream>
#include <thread>
#include <chrono>

#include "mingl/mingl.h"
#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"
#include "mingl/transition/transition_engine.h"

#include "functions.h"
#include "constants.h"

using namespace std;
using namespace nsGraphics;
using namespace nsShape;
using namespace nsTransition;

// main pour les tests console

//int main() {
//    vector<string> maze = maze1;
//    showMaze(maze);
//    map<string, Character> characterMaps;
//    initCharacters(characterMaps);
//    showMap(characterMaps);
//}


// main mingl

int main()
{
    // Initalisation des elements console
    map<string, Character> characterMaps;
    initCharacters(characterMaps);

    // Initialisation du système de gestion graphique
    MinGL window("Pacman", Vec2D(1500, 900), Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();
    TransitionEngine transitionEngine;

    // Initialisation des formes
    vector<Rectangle> vR = {};
    Vec2D posBegin = {175,125};
    Circle pacman(posBegin + Vec2D{(int)(characterMaps["Pacman"].posX)*50, (int)(characterMaps["Pacman"].posY)*50}, 25, KYellow);
    for (int i (150); i < 1350; i+=50) {
        for (int j (100); j < 750; j+=50) {
            vR.push_back(Rectangle(Vec2D(i,j), Vec2D(i+50, j+50), KBlue));
            vR[vR.size()-1].setBorderColor(KCyan);
        }
    }

    bool isTransitionFinished (true);
    chrono::microseconds frameTime = chrono::microseconds::zero();

    while (window.isOpen())
    {
        if (isTransitionFinished) {
            isTransitionFinished = false;
            TransitionContract a(pacman, pacman.TRANSITION_POSITION, chrono::milliseconds(500), {(float)(175+characterMaps["Pacman"].posX*50), (float)(125+characterMaps["Pacman"].posY*50)});
            a.setDestinationCallback([&] {
                keyboardInput(window, characterMaps);
                isTransitionFinished = true;
                cout << "ok - " << characterMaps["Pacman"].posX << endl;
            });
            transitionEngine.startContract(a);
        }
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        window.clearScreen();
        transitionEngine.update(frameTime);
        for (size_t k (0); k < vR.size(); ++k) {
            window << vR[k];
        }
        //window << Rectangle(Vec2D(150, 100), Vec2D(1350, 750), KRed); // area in which the maze will be draw
        window << pacman;

        window.finishFrame();
        window.getEventManager().clearEvents();
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }
    return 0;
}
