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

// main pour les tests console

int main() {
    vector<string> maze = maze1;
    showMaze(maze);
    map<string, Character> characterMaps;
    initCharacters(characterMaps);
    showMap(characterMaps);
}


// main mingl

//int main()
//{
//    MinGL window("Pacman", Vec2D(1500, 800), Vec2D(128, 128), nsGraphics::KBlack);
//    window.initGlut();
//    window.initGraphic();
//    nsTransition::TransitionEngine transitionEngine;

//    // On peut définir une fonction a appeler quand une transition se termine
////    nsTransition::TransitionContract rectTransitionContract(rect, rect.TRANSITION_FILL_COLOR_ALPHA, chrono::seconds(5), {64});
////    rectTransitionContract.setDestinationCallback([&] {
////        // On définit ici ce qu'il se passe quand la transition est terminée
////        std::cout << "Transition sur rectangle terminé!" << std::endl;
////        rect.setFillColor(nsGraphics::RGBAcolor(255, 0, 0, 64));
////        rect.setBorderColor(nsGraphics::KGreen);
////    });

////    transitionEngine.startContract(rectTransitionContract);
//    Vec2D pos = {75,75};
//    Circle pacman(pos, 25, KYellow);
//    // Enfin, il existe aussi plusieurs mode de transitions (ici, nous voyons une transition infinie)
//    transitionEngine.startContract(nsTransition::TransitionContract(pacman, pacman.TRANSITION_POSITION, chrono::milliseconds(250), {pos.getX()+ 50, pos.getY()}));

//    chrono::microseconds frameTime = chrono::microseconds::zero();

//    while (window.isOpen())
//    {
//        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

//        window.clearScreen();
//        transitionEngine.update(frameTime);
//        window << Rectangle(Vec2D(150, 100), Vec2D(1350, 750), KRed); // area in which the maze will be draw
//        window << Rectangle(Vec2D(150,100), Vec2D(200,150), KGray); // exemple of case
//        window << Rectangle(Vec2D(200,100), Vec2D(250,150), KBlue);
//        window << Rectangle(Vec2D(250,100), Vec2D(300,150), KGreen);
//        window << pacman;

//        window.finishFrame();
//        window.getEventManager().clearEvents();
//        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));
//        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
//    }
//    return 0;
//}
