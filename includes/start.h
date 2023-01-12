#include <stdio.h>
HelpF();    // in help.h

int StartF(unsigned char numPl, char playerName1[11], char playerName2[11], char playerName3[11], char playerName4[11], char mode, Music itemMusic)    // start function
{
    const unsigned short int width  = 1366;
    const unsigned short int height = 768;
    
    Rectangle restart                        = {width / 2 + 325, 660, 145, 50};
    Rectangle help                           = {width / 2 + 350, 595, 90, 50};
    Rectangle save                           = {width / 2 - 435, 595, 90, 50};
    Rectangle music                          = {width / 2 - 460, 660, 145, 50};
    
    char name1[11];
    char name2[11];
    char name3[11];
    char name4[11];
    strcpy(name1, playerName1);
    strcpy(name2, playerName2);
    strcpy(name3, playerName3);
    strcpy(name4, playerName4);
    
    unsigned char tiles[8][8]                = {0};
    unsigned char scores[4]                  = {0};
    unsigned char whoseTurn                  =  0;
    unsigned char playersPenguinCount        =  numPl * -1 + 6;
    unsigned char playersBrokenTilesCount[4] = {0};
    unsigned char numOfPenguinsOnBoard[4]    = {0};
    unsigned char tempPenguinPos[2]          = {0};
    unsigned char frames                     =  0;
    unsigned char losersCount                =  0;
    unsigned char lostPlayers[4]             = {0};
    unsigned char isStartingPointState       =  1;
    unsigned char saveAlertDelay             =  0;
    
    bool mouseOnRestart = false;    //is position of mouse in restart box?
    bool mouseOnSave = false;
    bool mouseOnHelp = false;
    bool mouseOnMusic = false;
    
    bool swItem1 = false;     //check for play the sound of item(mouse on restart box)
    bool swItem2 = false;     //check for play the sound of item(mouse on save box)
    bool swItem3 = false;     //check for play the sound of item(mouse on help box)
    bool swItem4 = false;     //check for play the sound of item(mouse on music box)
    
    bool playMusic=true;    // should music(gameMusic) play?
    bool playMusic2=true;    // should music(winnerMusic) play?
    
    createRandomTiles(tiles);   // in other_functions.h
    
    if(mode == 1){
        FILE *saveFile = fopen("save/savegame.dat", "rb");
        
        fread(&numPl,                  sizeof(char), 1,                               saveFile);
        fread(name1,                   sizeof(char), sizeof(name1),                   saveFile);
        fread(name2,                   sizeof(char), sizeof(name2),                   saveFile);
        fread(name3,                   sizeof(char), sizeof(name3),                   saveFile);
        fread(name4,                   sizeof(char), sizeof(name4),                   saveFile);
        fread(tiles,                   sizeof(char), sizeof(tiles),                   saveFile);
        fread(scores,                  sizeof(char), sizeof(scores),                  saveFile);
        fread(&whoseTurn,              sizeof(char), 1,                               saveFile);
        fread(playersBrokenTilesCount, sizeof(char), sizeof(playersBrokenTilesCount), saveFile);
        fread(numOfPenguinsOnBoard,    sizeof(char), sizeof(numOfPenguinsOnBoard),    saveFile);
        fread(tempPenguinPos,          sizeof(char), sizeof(tempPenguinPos),          saveFile);
        fread(&frames,                 sizeof(char), 1,                               saveFile);
        fread(lostPlayers,             sizeof(char), sizeof(lostPlayers),             saveFile);
        fread(&isStartingPointState,   sizeof(char), 1,                               saveFile);
        
        playersPenguinCount = numPl * -1 + 6;
        
        fclose(saveFile);
    }
    
    Texture2D background        = loadImage  ("images/background.png",     1366, 768);
    
    Texture2D singleFish        = loadImage  ("images/single_fish.png",    89, 103);            //if tiles[x][y]==1
    Texture2D doubleFish        = loadImage  ("images/double_fish.png",    89, 103);            //if tiles[x][y]==2
    Texture2D tripleFish        = loadImage  ("images/triple_fish.png",    89, 103);            //if tiles[x][y]==3
    
    Texture2D greenPenguinTile  = loadImage  ("images/green_penguin_tile.png",  89, 103);       //if tiles[x][y]==4
    Texture2D redPenguinTile    = loadImage  ("images/red_penguin_tile.png",    89, 103);       //if tiles[x][y]==5
    Texture2D goldPenguinTile   = loadImage  ("images/gold_penguin_tile.png",   89, 103);       //if tiles[x][y]==6
    Texture2D purplePenguinTile = loadImage  ("images/purple_penguin_tile.png", 89, 103);       //if tiles[x][y]==7
    
    Texture2D blueSingleFish    = loadImage  ("images/blue_single_fish.png",    89, 103);       //if tiles[x][y]==8
    Texture2D blueDoubleFish    = loadImage  ("images/blue_double_fish.png",    89, 103);       //if tiles[x][y]==9
    Texture2D blueTripleFish    = loadImage  ("images/blue_triple_fish.png",    89, 103);       //if tiles[x][y]==10
    
    Texture2D greenPenguin      = loadImage  ("images/green_penguin.png",  64, 64); 
    Texture2D redPenguin        = loadImage  ("images/red_penguin.png",    64, 64);
    Texture2D goldPenguin       = loadImage  ("images/gold_penguin.png",   64, 64);
    Texture2D purplePenguin     = loadImage  ("images/purple_penguin.png", 64, 64);
    
    Texture2D play              = loadImage  ("images/snowflake.png", 64, 64);

    
    Music gameMusic = LoadMusicStream("sounds/game_sound.mp3");
    gameMusic.looping = true;
    SetMusicVolume(gameMusic, 0.5f);
    Music tileMusic = LoadMusicStream("sounds/fish_sound.mp3");
    tileMusic.looping = false;
    SetMusicVolume(tileMusic, 0.3f);
    Music winnerMusic = LoadMusicStream("sounds/winner_sound.mp3");
    winnerMusic.looping = false;
    Music saveMusic = LoadMusicStream("sounds/save_sound.mp3");
    saveMusic.looping = false;
    SetMusicVolume(saveMusic, 0.3f);
    
    
    PlayMusicStream(gameMusic);
    
    while (!WindowShouldClose())
    {
        UpdateMusicStream(gameMusic);
        UpdateMusicStream(itemMusic);
        UpdateMusicStream(tileMusic);
        UpdateMusicStream(winnerMusic);
        UpdateMusicStream(saveMusic);
        
        if(CheckCollisionPointRec(GetMousePosition(), restart)) mouseOnRestart =true;
        else mouseOnRestart=false;
        if(CheckCollisionPointRec(GetMousePosition(), save)) mouseOnSave =true;
        else mouseOnSave=false;
        if(CheckCollisionPointRec(GetMousePosition(), help)) mouseOnHelp =true;
        else mouseOnHelp=false;
        if(CheckCollisionPointRec(GetMousePosition(), music)) mouseOnMusic =true;
        else mouseOnMusic=false;
        
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() >= 390 && GetMouseX() <= 975 && GetMouseY() >= 38 && GetMouseY() <= 557){
                char i = (GetMouseY() - 39) / 65;
                char j = -1;
                
                if(i % 2 == 0 && GetMouseX() >= 429)
                    j = (GetMouseX() - 422) / 74;
                if(i % 2 == 1)
                    j = (GetMouseX() - 383) / 74;
                
                if(i >= 0 && i <= 7 && j >= 0 && j <= 7){
                    if(isStartingPointState){   //put penguins
                        if(numOfPenguinsOnBoard[whoseTurn] < playersPenguinCount && tiles[i][j] == 1){
                            tiles[i][j] = whoseTurn + 4;
                            numOfPenguinsOnBoard[whoseTurn]++;
                            scores[whoseTurn]++;
                            whoseTurn++;
                            whoseTurn %= numPl;
                        }
                        
                        if(numOfPenguinsOnBoard[numPl - 1] == playersPenguinCount)
                            isStartingPointState = 0;
                    }
                    else{   //move penguins
                        if(tiles[i][j] == whoseTurn + 4){
                            
                            tempPenguinPos[0] = i;
                            tempPenguinPos[1] = j;
                            
                            //showing tiles can/can't move on(choosable tiles = shown in blue)
                            for(char y = 0; y < 8; y++) 
                                for(char x = 0; x < 8; x++)
                                    if(tiles[y][x] >= 8)
                                        tiles[y][x] -= 7;
                            
                            for(char y = i, x = j-1; x >= 0; x--){ 
                                if(tiles[y][x] >= 1 && tiles[y][x] <= 3)
                                    tiles[y][x] += 7;
                                else break;
                            }
                            for(char y = i, x = j+1; x <= 7; x++){
                                if(tiles[y][x] >= 1 && tiles[y][x] <= 3)
                                    tiles[y][x] += 7;
                                else break;
                            }                             
                            for(char y = i-1, x = j; y >= 0 && x >= 0; y--){
                                if(y%2==0) x--;
                                if(x < 0) break;
                                if(tiles[y][x] >= 1 && tiles[y][x] <= 3)
                                    tiles[y][x] += 7;
                                else break;
                            }
                            for(char y = i-1, x = j; y >= 0 && x <= 7; y--){
                                if(y%2==1) x++;
                                if(x > 7) break;
                                if(tiles[y][x] >= 1 && tiles[y][x] <= 3)
                                    tiles[y][x] += 7;
                                else break;
                            }
                            for(char y = i+1, x = j; y <= 7 && x <= 7; y++){
                                if(y%2==1) x++;
                                if(x > 7) break;
                                if(tiles[y][x] >= 1 && tiles[y][x] <= 3)
                                    tiles[y][x] += 7;
                                else break;
                            }
                            for(char y = i+1, x = j; y <= 7 && x >= 0; y++){
                                if(y%2==0) x--;
                                if(x < 0) break;
                                if(tiles[y][x] >= 1 && tiles[y][x] <= 3)
                                    tiles[y][x] += 7;
                                else break;
                            }
                        }
                        else if(tiles[i][j] >= 8){
                            tiles[tempPenguinPos[0]][tempPenguinPos[1]] = 0;
                            playersBrokenTilesCount[whoseTurn]++;
                            scores[whoseTurn] += tiles[i][j] % 7;
                            tiles[i][j] = whoseTurn + 4;
                            PlayMusicStream(tileMusic);
                            for(char y = 0; y < 8; y++)
                                for(char x = 0; x < 8; x++)
                                    if(tiles[y][x] >= 8)
                                        tiles[y][x] -= 7;
                            if(whoseTurn < numPl - 1)
                                whoseTurn++;
                            else
                                whoseTurn = 0;
                        }
                    }
                    
                    frames = 0;
                }
            }
           
        if(CheckCollisionPointRec(GetMousePosition(), restart) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            StopMusicStream(gameMusic);
            playerName1[0] = 0;
            playerName2[0] = 0;
            playerName3[0] = 0;
            playerName4[0] = 0;
      
            return 2;   // will be saved as "codeStart" in main.c
        }
        
        if(CheckCollisionPointRec(GetMousePosition(), help) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) HelpF(gameMusic);    // in other_functions.h
        
        if(CheckCollisionPointRec(GetMousePosition(), music) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if(playMusic) 
            {
                PauseMusicStream(gameMusic);
                playMusic=false;
            }
            else 
            {
                ResumeMusicStream(gameMusic);
                playMusic=true;
            }
        }
            
        if(CheckCollisionPointRec(GetMousePosition(), save) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            
            saveAlertDelay = 1;
            
            FILE *saveFile = fopen("save/savegame.dat", "wb");
            
            fwrite(&numPl,                  sizeof(char), 1,                               saveFile);
            fwrite(name1,                   sizeof(char), sizeof(name1),                   saveFile);
            fwrite(name2,                   sizeof(char), sizeof(name2),                   saveFile);
            fwrite(name3,                   sizeof(char), sizeof(name3),                   saveFile);
            fwrite(name4,                   sizeof(char), sizeof(name4),                   saveFile);
            fwrite(tiles,                   sizeof(char), sizeof(tiles),                   saveFile);
            fwrite(scores,                  sizeof(char), sizeof(scores),                  saveFile);
            fwrite(&whoseTurn,              sizeof(char), 1,                               saveFile);
            fwrite(playersBrokenTilesCount, sizeof(char), sizeof(playersBrokenTilesCount), saveFile);
            fwrite(numOfPenguinsOnBoard,    sizeof(char), sizeof(numOfPenguinsOnBoard),    saveFile);
            fwrite(tempPenguinPos,          sizeof(char), sizeof(tempPenguinPos),          saveFile);
            fwrite(&frames,                 sizeof(char), 1,                               saveFile);
            fwrite(lostPlayers,             sizeof(char), sizeof(lostPlayers),             saveFile);
            fwrite(&isStartingPointState,   sizeof(char), 1,                               saveFile);
            
            fclose(saveFile);
        }
        
        soundBoxes(mouseOnRestart, &swItem1, itemMusic);   //in other_functions.h
        soundBoxes(mouseOnSave,    &swItem2, itemMusic);
        soundBoxes(mouseOnHelp,    &swItem3, itemMusic);
        soundBoxes(mouseOnMusic,   &swItem4, itemMusic);
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            DrawTexture(background, 0, 0, RAYWHITE);

            if(saveAlertDelay > 0 && saveAlertDelay < 240){
                    DrawText("your game has been saved successfully!", 440, 630, 25, RAYWHITE);
                    saveAlertDelay++;
                    if(saveAlertDelay < 120)
                        PlayMusicStream(saveMusic);
            }
    
            for(int i = 0; i < numPl; i++)
                if(lostPlayers[i])
                    losersCount++;
            
            //end of game result    
            if(numPl - losersCount == 0){
                unsigned char winner;
                unsigned char score = 0;

                for(int i = 0; i < numPl; i++)
                    if(scores[i] > score){
                        winner = i;
                        score = scores[i];
                    }
                
                for(int i = 0; i < numPl; i++)
                    if(i != winner && scores[i] == score)
                        if(playersBrokenTilesCount[winner] < playersBrokenTilesCount[i])
                            winner = i;
                        
                if(playMusic2)       
                    PlayMusicStream(winnerMusic);
                playMusic2 = false;
                
                switch(winner){
                    case 0: DrawText(TextFormat("Congratulation %s!\n\nYou Won The Game!", name1), 550, 600, 25, DARKGREEN); break;
                    case 1: DrawText(TextFormat("Congratulation %s!\n\nYou Won The Game!", name2), 550, 600, 25, DARKGREEN); break;
                    case 2: DrawText(TextFormat("Congratulation %s!\n\nYou Are The Winner!", name3), 550, 600, 25, RAYWHITE); break;
                    case 3: DrawText(TextFormat("Congratulation %s!\n\nYou Are The Winner!", name4), 550, 600, 25, RAYWHITE); break;
                }
            }
            
            losersCount = 0;    
            
            //specyfing that player can/can't resume the game and break the tiles
            switch(whoseTurn){
                case 0: if(canMove(tiles, whoseTurn) || isStartingPointState) 
                            DrawTexture(play , 985, 170, RAYWHITE);
                        else {
                            lostPlayers[whoseTurn] = 1;
                            numOfPenguinsOnBoard[whoseTurn] = 0;
                            whoseTurn++;
                            for(int i = 0; i < 8; i++)
                                for(int j = 0; j < 8; j++)
                                    if(tiles[i][j] == 4)
                                        tiles[i][j] = 0;
                                        
                        }
                        break;
                case 1: if(canMove(tiles, whoseTurn) || isStartingPointState)
                            DrawTexture(play , 985, 230, RAYWHITE);
                        else {
                            lostPlayers[whoseTurn] = 1;
                            numOfPenguinsOnBoard[whoseTurn] = 0;
                            whoseTurn++;
                            for(int i = 0; i < 8; i++)
                                for(int j = 0; j < 8; j++)
                                    if(tiles[i][j] == 5)
                                        tiles[i][j] = 0;
                        }
                        break;
                case 2: if(canMove(tiles, whoseTurn) || isStartingPointState)
                            DrawTexture(play , 985, 290, RAYWHITE);
                        else {
                            lostPlayers[whoseTurn] = 1;
                            numOfPenguinsOnBoard[whoseTurn] = 0;
                            whoseTurn++;
                            for(int i = 0; i < 8; i++)
                                for(int j = 0; j < 8; j++)
                                    if(tiles[i][j] == 6)
                                        tiles[i][j] = 0;
                        }
                        break;
                case 3: if(canMove(tiles, whoseTurn) || isStartingPointState)
                            DrawTexture(play , 985, 350, RAYWHITE);
                        else {
                            lostPlayers[whoseTurn] = 1;
                            numOfPenguinsOnBoard[whoseTurn] = 0;
                            whoseTurn = 0;
                            for(int i = 0; i < 8; i++)
                                for(int j = 0; j < 8; j++)
                                    if(tiles[i][j] == 7)
                                        tiles[i][j] = 0;
                        }
                        break;
            }
            
            //names and score board and number of penguins out of tiles
            DrawText(TextFormat("%s",   name1), 195, 200, 20, RAYWHITE);
            DrawText(TextFormat("%hhu", scores[0]), 347, 200, 20, RAYWHITE);
            for(char i = playersPenguinCount; i > numOfPenguinsOnBoard[0]; i--)
                DrawTexture(greenPenguin , 1000 + i*35, 170, RAYWHITE);
            if(!isStartingPointState)
                DrawTexture(greenPenguin , 1070, 170, RAYWHITE);
            
            DrawText(TextFormat("%s",   name2), 195, 260, 20, RAYWHITE);
            DrawText(TextFormat("%hhu", scores[1]), 347, 260, 20, RAYWHITE);
            for(char i = playersPenguinCount; i > numOfPenguinsOnBoard[1]; i--)
                DrawTexture(redPenguin   , 1000 + i*35, 230, RAYWHITE);
            if(!isStartingPointState)
                DrawTexture(redPenguin , 1070, 230, RAYWHITE);
            
            if(numPl >= 3){
                DrawText(TextFormat("%s",   name3), 195, 320, 20, RAYWHITE);
                DrawText(TextFormat("%hhu", scores[2]), 347, 320, 20, RAYWHITE);
                for(char i = playersPenguinCount; i > numOfPenguinsOnBoard[2]; i--)
                    DrawTexture(goldPenguin  , 1000 + i*35, 290, RAYWHITE);
                if(!isStartingPointState)
                    DrawTexture(goldPenguin , 1070, 290, RAYWHITE);
            }
            if(numPl == 4){
                DrawText(TextFormat("%s",   name4), 195, 380, 20, RAYWHITE);
                DrawText(TextFormat("%hhu", scores[3]), 347, 380, 20, RAYWHITE);
                for(char i = playersPenguinCount; i > numOfPenguinsOnBoard[3]; i--)
                    DrawTexture(purplePenguin, 1000 + i*35, 350, RAYWHITE);
                if(!isStartingPointState)
                    DrawTexture(purplePenguin , 1070, 350, RAYWHITE);
            }
            
            //draw functions boxes
            if(mouseOnRestart) DrawFunctionsBox(restart, "RESTART", RAYWHITE, 1020, 675, 4, '2');
            else DrawFunctionsBox(restart, "RESTART", RAYWHITE, 1020, 675, 4, '1');
            if(mouseOnHelp) DrawFunctionsBox(help, "HELP", RAYWHITE, 1048, 608, 4, '2');
            else DrawFunctionsBox(help, "HELP", RAYWHITE, 1048, 608, 4, '1');
            if(mouseOnMusic) DrawFunctionsBox(music, "MUSIC", RAYWHITE, 257, 675, 4, '2');
            else DrawFunctionsBox(music, "MUSIC", RAYWHITE, 257, 675, 4, '1');
            if(mouseOnSave) DrawFunctionsBox(save, "SAVE", RAYWHITE, 260, 610, 4, '2');
            else DrawFunctionsBox(save, "SAVE", RAYWHITE, 260, 610, 4, '1');
          
            //music box color based on play/not play music
            if(playMusic) DrawFunctionsBox(music, "MUSIC", DARKGREEN, 257, 675, 4, '1'); 
          
            for(int i = 0; i < 8; i++){
                if(i % 2 == 0)
                    for(int j = 0; j < 7; j++)
                        switch(tiles[i][j]){
                            case 1:
                                if(isStartingPointState && frames == 5){
                                    DrawTexture(blueSingleFish,    74*j + 418, 65*i + 19, RAYWHITE);
                                    break;
                                }
                                else{
                                    DrawTexture(singleFish,        74*j + 418, 65*i + 19, RAYWHITE);
                                    break;
                                }
                            case 2: DrawTexture(doubleFish,        74*j + 418, 65*i + 19, RAYWHITE); break;
                            case 3: DrawTexture(tripleFish,        74*j + 418, 65*i + 19, RAYWHITE); break;
                            case 4: DrawTexture(greenPenguinTile,  74*j + 418, 65*i + 19, RAYWHITE); break;
                            case 5: DrawTexture(redPenguinTile,    74*j + 418, 65*i + 19, RAYWHITE); break;
                            case 6: DrawTexture(goldPenguinTile,   74*j + 418, 65*i + 19, RAYWHITE); break;
                            case 7: DrawTexture(purplePenguinTile, 74*j + 418, 65*i + 19, RAYWHITE); break;
                            case 8: DrawTexture(blueSingleFish,    74*j + 418, 65*i + 19, RAYWHITE); break;
                            case 9: DrawTexture(blueDoubleFish,    74*j + 418, 65*i + 19, RAYWHITE); break;
                            case 10: DrawTexture(blueTripleFish,   74*j + 418, 65*i + 19, RAYWHITE); break;
                        }
                else
                    for(int j = 0; j < 8; j++)
                        switch(tiles[i][j]){
                            case 1:
                                if(isStartingPointState && frames == 5){
                                    DrawTexture(blueSingleFish,    74*j + 379, 65*i + 19, RAYWHITE);
                                    break;
                                }
                                else{
                                    DrawTexture(singleFish,        74*j + 379, 65*i + 19, RAYWHITE);
                                    break;
                                }
                            case 2: DrawTexture(doubleFish,        74*j + 379, 65*i + 19, RAYWHITE); break;
                            case 3: DrawTexture(tripleFish,        74*j + 379, 65*i + 19, RAYWHITE); break;
                            case 4: DrawTexture(greenPenguinTile,  74*j + 379, 65*i + 19, RAYWHITE); break;
                            case 5: DrawTexture(redPenguinTile,    74*j + 379, 65*i + 19, RAYWHITE); break;
                            case 6: DrawTexture(goldPenguinTile,   74*j + 379, 65*i + 19, RAYWHITE); break; 	
                            case 7: DrawTexture(purplePenguinTile, 74*j + 379, 65*i + 19, RAYWHITE); break;
                            case 8: DrawTexture(blueSingleFish,    74*j + 379, 65*i + 19, RAYWHITE); break;
                            case 9: DrawTexture(blueDoubleFish,    74*j + 379, 65*i + 19, RAYWHITE); break;
                            case 10: DrawTexture(blueTripleFish,   74*j + 379, 65*i + 19, RAYWHITE); break;
                        }
            }
            if(isStartingPointState && frames < 5)
                frames++;
            
            
        EndDrawing();
       
    }
   
    UnloadTexture(background);
    UnloadTexture(singleFish);
    UnloadTexture(doubleFish);
    UnloadTexture(tripleFish);
    UnloadTexture(blueSingleFish);
    UnloadTexture(blueDoubleFish);
    UnloadTexture(blueTripleFish);
    UnloadTexture(greenPenguin);
    UnloadTexture(redPenguin);
    UnloadTexture(goldPenguin);
    UnloadTexture(purplePenguin);
    UnloadTexture(greenPenguinTile);
    UnloadTexture(redPenguinTile);
    UnloadTexture(goldPenguinTile);
    UnloadTexture(purplePenguinTile);
    UnloadTexture(play);
    
    UnloadMusicStream(gameMusic);
    UnloadMusicStream(itemMusic);
    UnloadMusicStream(tileMusic);
    UnloadMusicStream(winnerMusic);
    UnloadMusicStream(saveMusic);

    return 1;   // will be saved as "codeStart" in main.c

}