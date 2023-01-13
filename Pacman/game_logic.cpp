void moveCharacter(Character &character, string direction) {
    if (direction == "up") --character.pos.y;
    else if (direction == "right") ++character.pos.x;
    else if (direction == "down") ++character.pos.y;
    else if (direction == "left") --character.pos.x;
    character.direction = direction;
}

void moveCharacterTeleporter (vector<string> &maze, Character &character, Param& param) {
    if(isTeleporter(maze,character)){
        if(character.pos == (getPosTeleporter(param))[0]){ // check if the player is on the first teleporter to know on wich teleporter the player have to move.
            character.pos = (getPosTeleporter(param))[1]; // change the positionof the player to set it on the linked teleporter.
        }else if(character.pos == (getPosTeleporter(param))[1]){
                character.pos = (getPosTeleporter(param))[0];
        }
    }
}

void eatBubble (const Character &character, vector<string> &maze, size_t &bubbleLeft){
    if(character.direction == "up") maze[character.pos.y+1][character.pos.x] = ' ';
    else if(character.direction == "down") maze[character.pos.y-1][character.pos.x] = ' ';
    else if(character.direction == "left") maze[character.pos.y][character.pos.x+1] = ' ';
    else if(character.direction == "right") maze[character.pos.y][character.pos.x-1] = ' ';
    bubbleLeft -= 1;
}

void eatBigBubble (Character &character, vector<string> &maze, size_t &bubbleLeft){
    if(character.direction == "up") maze[character.pos.y+1][character.pos.x] = ' ';
    else if(character.direction == "down") maze[character.pos.y-1][character.pos.x] = ' ';
    else if(character.direction == "left") maze[character.pos.y][character.pos.x+1] = ' ';
    else if(character.direction == "right") maze[character.pos.y][character.pos.x-1] = ' ';
    bubbleLeft -= 1;
}

void bigBubbleDuration(map<string, Character> &mapCharact) {
    this_thread::sleep_for(chrono::seconds(5));
    changeEveryoneState(mapCharact, true);
}

void changeState(Character &charact) {
    charact.isDefaultState = !charact.isDefaultState;
    if (charact.isDefaultState) {
        if (charact.type == "Pacman") charact.vitesse = 500;
    } else {
        if (charact.type == "Pacman") charact.vitesse = 300;
    }
}

void changeEveryoneState(map<string, Character> &mapCharact, bool newValue) {
    for (auto& charact : mapCharact) {
        if (charact.second.isDefaultState != newValue) changeState(charact.second);
    }
}

// void eatGhost

//void checkEating(map<string, Character> mapC, bool &gameRunning) {
//    for (auto it = mapC.begin(); it != mapC.end(); it++) {
//        if (it->second.type == "Ghost") {
//            if (isSamePos(mapC["Pacman"], it->second)) {
//                if (it->second.isDefaultState == true) gameOver(gameRunning);
//                else ()
//            }
//        }
//    }
//}
