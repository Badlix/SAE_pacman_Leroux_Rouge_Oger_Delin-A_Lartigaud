vector<string> initMaze(Param &param) {
    if (param.skins["Maze"] == 1) return maze1;
    else return maze2;
}

PacmanMouth initPacmanmouth(Param &param) {
    if (param.skins["Pacman"] == 1) return {flowerPacmanClose, 0};
}

map<string, Character> initCharacters(Param &param) {
    map<string, Character> mapC;
    /* Set Pacman Skin*/
    Skin skin;
    Skin skinMouthClose;
    if (param.skins["Pacman"] == 1) {skin = flowerPacman; skinMouthClose = flowerPacmanClose;}
    /*else if (param.skins["Pacman"] == 2) {skin = candyPacman; skinMouthClose = flowerPacmanClose;}
    else if (param.skins["Pacman"] == 3) {skin = penguinPacman; skinMouthClose = penguinPacmanClose;}*/

    Character tmp = {
        "Pacman",  // type
        {1, 1}, // position
        "right", // direction
        true, // isDefaultState
        400, // vitesse
        {nsGui::Sprite({RGBAcolor{0,0,0,0}}, 1,  nsGraphics::Vec2D(0,0))}, // sprites
        skin
    };
    mapC["Pacman"] = tmp;

    /* Set Ghost1 Skin*/
    if (param.skins["Ghost"] == 1) skin = butterflyGhost;
//    else if (param.skins["Ghost"] == 2) skin = lolipopGhost;
//    else if (param.skins["Ghost"] == 3) skin = iceCreamGhost;

    tmp = {
        "Ghost",
        getPosCage(param),
        "up",
        true,
        500,
        {nsGui::Sprite({RGBAcolor{0,0,0,0}}, 1,  nsGraphics::Vec2D(0,0))},
        skin
    };
    mapC["Ghost1"] = tmp;
    vector<RGBAcolor> listPixel;
    vector<string> directions = {"up", "down", "right", "left"};
    for (unsigned i(2); i <= param.difficulty["GhostNumber"]; ++i) {
        mapC["Ghost"+to_string(i)] = tmp;
        mapC["Ghost"+to_string(i)].pos = {i,i};
        for (const string &direction : directions) {
            listPixel = mapC["Ghost1"].skins.defaultState.find(direction)->second.getPixelData();
            for (RGBAcolor &pixel : listPixel) {
                if (pixel == skinGhostColors[0]) {
                    pixel = skinGhostColors[i-1];
                }
            }
            mapC["Ghost"+to_string(i)].skins.defaultState.find(direction)->second = nsGui::Sprite(listPixel, 50, nsGraphics::Vec2D(0,0));
        }
    }
    return mapC;
}

size_t nbBubbleInMaze(vector<string> &maze){
    size_t bubbleLeft = 0;
    for (size_t i(0); i < maze.size(); ++i){
        for (size_t j=0; j<maze[i].size(); ++j){
            if (maze[i][j] == '.' || maze[i][j] == 'o'){
                ++bubbleLeft;
            }
        }
    }
    return bubbleLeft;
}

void initPersonality (vector<string> &characterList, map<string, string> personalities, unsigned &difficulty) {
    //Each personnality has a level of difficulty.
    //The chances of it to drop are in percentage.

    //Initialization of the personalities
    vector<string> easyPersonality {"dumb"};
    vector<string> normalPersonality {"confused"};
    vector<string> hardPersonality {"hardcore"};

    //Initialization of the droprate of each level of difficulty :
    unsigned easy = 100 - 30*difficulty;
    unsigned hard = 30 * difficulty - 20;
    unsigned normal = 100 - easy - hard ;

    //Application of a random personality to each characters
    unsigned random;
    string personality;
    for (size_t i = 0 ; i < characterList.size() ; ++i) {
        random = rand()%100;
        if (random <= easy) {
            personality = easyPersonality[(rand()%easyPersonality.size())-1];
            personalities.insert({characterList[i], personality});
        }
        else if (random <= easy+normal){
            personality = normalPersonality[(rand()%normalPersonality.size())-1];
            personalities.insert({characterList[i], personality});
        }
        else {
            personality = hardPersonality[(rand()%hardPersonality.size())-1];
            personalities.insert({characterList[i], personality});
        }
    }
}
