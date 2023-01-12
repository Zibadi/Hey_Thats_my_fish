/*
.
.
Hey that's my fish #GAME 
this game is written using raylib.h library and has some header files attached to it as: /start.h/, /help.h/ and /other_functions.h/  
first page in which are players information and buttons of functions is written in /main.c/ 
if start button on first page is pressed, startF(start function) will be called which is written in /start.h/ 
if help button on first page or game page pressed, helpF(help function) will be called which is written in /help.h/
other functions those are used between all codes are written in /other_functions.h/
play and enjoy :)
.
.
*/

#include "raylib.h"
#include "string.h"
#include "libraries/other_functions.h"
#include "libraries/start.h"
#include "libraries/help.h"

int main()
{
    //the screen have been considered to be 1366*768 to be showable on any computer
    const int screenWidth  = 1366;
    const int screenHeight = 768;
    
    InitWindow(screenWidth, screenHeight, "Hey, That's my fish!");
    
    InitAudioDevice();
    
    Texture2D background        = loadImage  ("images/background.png",     1366, 768);
    Texture2D greenPenguin      = loadImage  ("images/green_penguin.png",  64, 64);
    Texture2D redPenguin        = loadImage  ("images/red_penguin.png",    64, 64);
    Texture2D goldPenguin       = loadImage  ("images/gold_penguin.png",   64, 64);
    Texture2D purplePenguin     = loadImage  ("images/purple_penguin.png", 64, 64);
    
    Music firstMusic = LoadMusicStream("sounds/first_sound.mp3");
    firstMusic.looping = true;
    SetMusicVolume(firstMusic, 1.2f);
    Music itemMusic = LoadMusicStream("sounds/item2_sound.mp3");
    itemMusic.looping = false;
    SetMusicVolume(itemMusic, 0.15f);
    
    char welcome[]= "Hey, That's my fish!";
    
    Rectangle numPlayer1 = { 150, 430, 130, 80 };   // show if 2 players(box)
    Rectangle numPlayer2 = { 150, 530, 130, 80 };   // show if 3 players(box)
    Rectangle numPlayer3 = { 150, 630, 130, 80 };   // show if 4 players(box)   
    bool mouseOnText1 = false;  //related to numPlayer 1 box
    bool mouseOnText2 = false;  //related to numPlayer 2 box
    bool mouseOnText3 = false;  //related to numPlayer 3 box
    
    char name1[11];
    char name2[11];
    char name3[11];
    char name4[11];
    name1[0]=name2[0]=name3[0]=name4[0]=0;
    int Nname1=0, Nname2=0, Nname3=0, Nname4=0;  // num of char of playername
    Rectangle name1Rec = {310, 430, 380, 50};   // name box player1
    Rectangle name2Rec = {310, 507, 380, 50};   // name box player2
    Rectangle name3Rec = {310, 584, 380, 50};   // name box player3
    Rectangle name4Rec = {310, 661, 380, 50};   // name box player4
    bool mouseOnTextName1 = false;  //related to numPlayer1 box
    bool mouseOnTextName2 = false;  //related to numPlayer2 box
    bool mouseOnTextName3 = false;  //related to numPlayer3 box
    bool mouseOnTextName4 = false;  //related to numPlayer4 box
    
    Rectangle start = { 1185, 425, 110, 64 };    // start is a rectangle associatd with start box (but Start is booilan which check if goto function start or not)
    Rectangle load = { 1185, 499, 110, 64};      // load is a rectangle associatd with load box  (same)
    Rectangle help = { 1185, 573, 110, 64};      // help is a rectangle associatd with help box   (same)
    Rectangle exit = { 1185, 647, 110, 64};      // exit is a rectangle associatd with exit box   (same)
    bool mouseOnStart = false, mousePressStart=false;
    bool mouseOnLoad = false, mousePressLoad=false;
    bool mouseOnHelp = false, mousePressHelp=false;
    bool mouseOnExit = false, mousePressExit=false;
    
    bool Start=false;   // Start function (in start.h)
    bool Load=false;    // Load function (in other_functions.h)
    bool Help=false;    // Help function (in help.h)
    bool Exit=false;  
    
    bool swItem1=false; //check for play the sound of item(mouse on start box)
    bool swItem2=false; //check for play the sound of item(mouse on load box)
    bool swItem3=false; //check for play the sound of item(mouse on help box)
    bool swItem4=false; //check for play the sound of item(mouse on exit box)
    
    int codeReturn;  // returned code of Start function and help function(1 for closing the game, 2 for keep playing)
    int swStart[4]={0}; // for allowing to start the game(if all names entered) (0=allow, 1=not allow)
    
    unsigned char numPl=0;  // number of players  
    
    int counter=0;  // write title of game animationly
    
    PlayMusicStream(firstMusic);
    SetTargetFPS(60);
    
    while(!WindowShouldClose()) 
    {
        UpdateMusicStream(firstMusic);
        UpdateMusicStream(itemMusic);
        
        counter++;  // write title of game animationally
        
        // start of game
        if(Start) 
        {
            if(Nname1==0) swStart[0]=1;
            else swStart[0]=0;
            if(Nname2==0) swStart[1]=1;
            else swStart[1]=0;
            if(Nname3==0 && (numPl==3 || numPl==4)) swStart[2]=1;
            else swStart[2]=0;
            if(Nname4==0 && numPl==4) swStart[3]=1;
            else swStart[3]=0;
            if(Nname1!=0 && Nname2!=0 && !(Nname3==0 && (numPl==3 || numPl==4)) && !(Nname4==0 && numPl==4)) 
            {
                StopMusicStream(firstMusic);
                Start=false;
                codeReturn=StartF(numPl, name1, name2, name3, name4, 0, itemMusic);        // in start.h
                PlayMusicStream(firstMusic);
                Nname1=Nname2=Nname3=Nname4=0;
            }
            if(codeReturn==1) 
            {
                CloseWindow();
                
                UnloadTexture(background);
                UnloadTexture(greenPenguin);
                UnloadTexture(redPenguin);
                UnloadTexture(goldPenguin);
                UnloadTexture(purplePenguin);
                
                return 0;
            }
        }
        if(Load){
            StopMusicStream(firstMusic);
            Start=false;
            codeReturn=StartF(numPl, name1, name2, name3, name4, 1, itemMusic);        // in start.h
            PlayMusicStream(firstMusic);
            Nname1=Nname2=Nname3=Nname4=0;
            if(codeReturn==1)
            {
                CloseWindow();
                
                UnloadTexture(background);
                UnloadTexture(greenPenguin);
                UnloadTexture(redPenguin);
                UnloadTexture(goldPenguin);
                UnloadTexture(purplePenguin);
                
                return 0;
            }
        }
        if(Help) 
        {
            Help=false;
            codeReturn=HelpF(firstMusic);        // in help.h
            if(codeReturn==1)
            {
                CloseWindow();
                
                UnloadTexture(background);
                UnloadTexture(greenPenguin);
                UnloadTexture(redPenguin);
                UnloadTexture(goldPenguin);
                UnloadTexture(purplePenguin);
                
                return 0;
            }
        }
        if(Exit) 
        {
            CloseWindow();
            
            UnloadTexture(background);
            UnloadTexture(greenPenguin);
            UnloadTexture(redPenguin);
            UnloadTexture(goldPenguin);
            UnloadTexture(purplePenguin);
            
            return 0;
        }
        if(!Nname1==0) swStart[0]=0;
        if(!Nname2==0) swStart[1]=0;
        if(!(Nname3==0 && (numPl==3 || numPl==4))) swStart[2]=0;
        if(!(Nname4==0 && numPl==4)) swStart[3]=0;
        
        // functions
        if(CheckCollisionPointRec(GetMousePosition(), help) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) Help=true;
        else if(!CheckCollisionPointRec(GetMousePosition(), help) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) Help=false;
        if(CheckCollisionPointRec(GetMousePosition(), start) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) Start=true;
        else if(!CheckCollisionPointRec(GetMousePosition(), start) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) Start=false;
        if(CheckCollisionPointRec(GetMousePosition(), load) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) Load=true;
        else if(!CheckCollisionPointRec(GetMousePosition(), load) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) Load=false;
        if(CheckCollisionPointRec(GetMousePosition(), exit) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) Exit=true;
        else if(!CheckCollisionPointRec(GetMousePosition(), exit) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) Exit=false;
        
        // select mumber of players
        if (CheckCollisionPointRec(GetMousePosition(), numPlayer1) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnText1 = true;
        if(!CheckCollisionPointRec(GetMousePosition(), numPlayer1) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnText1 = false;
        if (CheckCollisionPointRec(GetMousePosition(), numPlayer2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnText2 = true;
        if(!CheckCollisionPointRec(GetMousePosition(), numPlayer2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnText2 = false;     
        if (CheckCollisionPointRec(GetMousePosition(), numPlayer3) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnText3 = true;
        if(!CheckCollisionPointRec(GetMousePosition(), numPlayer3) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnText3 = false;
        
        if(mouseOnText1) numPl=2;
        else if(mouseOnText2) numPl=3;
        else if(mouseOnText3) numPl=4;
        
        if(numPl<=2) 
        {
            name3[0]=name4[0]=0;
            Nname3=Nname4=0;
        }
        if(numPl==3) 
        {
            name4[0]=0;
            Nname4=0;
        }
        
        // specifying which player name is going to get
        if (CheckCollisionPointRec(GetMousePosition(), name1Rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnTextName1 = true;
        if(!CheckCollisionPointRec(GetMousePosition(), name1Rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnTextName1 = false;
        if (CheckCollisionPointRec(GetMousePosition(), name2Rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnTextName2 = true;
        if(!CheckCollisionPointRec(GetMousePosition(), name2Rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnTextName2 = false;     
        if (CheckCollisionPointRec(GetMousePosition(), name3Rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnTextName3 = true;
        if(!CheckCollisionPointRec(GetMousePosition(), name3Rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnTextName3 = false;
        if (CheckCollisionPointRec(GetMousePosition(), name4Rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnTextName4 = true;
        if(!CheckCollisionPointRec(GetMousePosition(), name4Rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnTextName4 = false;
        
        //SetMouseCursor type
        if( (numPl!=0 && (CheckCollisionPointRec(GetMousePosition(), name1Rec) || CheckCollisionPointRec(GetMousePosition(), name2Rec))) || (CheckCollisionPointRec(GetMousePosition(), name3Rec) && (numPl==3 || numPl==4)) ||  ((CheckCollisionPointRec(GetMousePosition(), name4Rec) && numPl==4))) SetMouseCursor(MOUSE_CURSOR_IBEAM);
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        
        //check functions status
        checkFunction(start, &mouseOnStart, &mousePressStart);
        checkFunction(load, &mouseOnLoad, &mousePressLoad);
        checkFunction(help, &mouseOnHelp, &mousePressHelp);
        checkFunction(exit, &mouseOnExit, &mousePressExit);
        
        if(mouseOnTextName1)                             getName(name1, &Nname1);
        if(mouseOnTextName2)                             getName(name2, &Nname2);
        if(mouseOnTextName3 && (numPl==3 || numPl==4))   getName(name3, &Nname3);
        if(mouseOnTextName4 && numPl==4)                 getName(name4, &Nname4);
        
        //mouse on functions boxes sound
        soundBoxes(mouseOnStart, &swItem1, itemMusic);   //in other_functions.h
        soundBoxes(mouseOnLoad, &swItem2, itemMusic);
        soundBoxes(mouseOnHelp, &swItem3, itemMusic);
        soundBoxes(mouseOnExit, &swItem4, itemMusic);

        BeginDrawing(); 
        ClearBackground(RAYWHITE);
        
        DrawTexture(background, 0, 0, WHITE);
        if(numPl>=1)                DrawTexture(greenPenguin, 740, 426, WHITE);
        if(numPl>=1 || numPl==2)    DrawTexture(redPenguin,   740, 503, WHITE);
        if(numPl==3 || numPl==4)    DrawTexture(goldPenguin,  740, 580, WHITE);
        if(numPl==4)                DrawTexture(purplePenguin,740, 657, WHITE);
        
        DrawText(TextSubtext(welcome, 0, counter/5), 400, 80, 55, MAROON);
        if(counter<100) // 5*20
        {
            EndDrawing();
            continue;
        }
        
        DrawText(TextFormat("Select Number Of Players: "), 150, 350, 40, DARKGREEN);
        
        // functions boxes
        if(mouseOnStart)    DrawFunctionsBox(start, "START", LIME, 1196, 447, 6, '2');   // in other_functions.h
        else                DrawFunctionsBox(start, "START", LIME, 1196, 447, 6, '1');   // in other_functions.h
        if(mouseOnLoad)     DrawFunctionsBox(load, "LOAD", GOLD, 1211, 520, 6, '2');     // in other_functions.h
        else                DrawFunctionsBox(load, "LOAD", GOLD, 1211, 520, 6, '1');     // in other_functions.h
        if(mouseOnHelp)     DrawFunctionsBox(help, "HELP", GOLD, 1211, 595, 6, '2');     // in other_functions.h
        else                DrawFunctionsBox(help, "HELP", GOLD, 1211, 595, 6, '1');     // in other_functions.h
        if(mouseOnExit)     DrawFunctionsBox(exit, "EXIT", RED, 1211, 668, 6, '2');      // in other_functions.h
        else                DrawFunctionsBox(exit, "EXIT", RED, 1211, 668, 6, '1');      // in other_functions.h
       
        //rectangles of 2,3,4 boxes
        DrawRectangleRounded(numPlayer1, 20,10,LIGHTGRAY);
        DrawRectangleRounded(numPlayer2, 20,10,LIGHTGRAY);
        DrawRectangleRounded(numPlayer3, 20,10,LIGHTGRAY);
        if(numPl==2)  DrawRectangleRounded(numPlayer1, 20,10,DARKGREEN);
        else if(numPl==3)  DrawRectangleRounded(numPlayer2, 20,10,DARKGREEN);
        else if(numPl==4)  DrawRectangleRounded(numPlayer3, 20,10,DARKGREEN);
        DrawText(TextFormat("2"), 205, 450, 40, BLACK);
        DrawText(TextFormat("3"), 205, 550, 40, BLACK);
        DrawText(TextFormat("4"), 205, 650, 40, BLACK);
        
        //rectangles of name boxes
        if(numPl==2 || numPl==3 || numPl==4)
        {
            DrawRectangleRec(name1Rec, LIGHTGRAY);
            DrawText(TextFormat("%d/10",Nname1), 645, 460, 15, DARKGRAY);
            if(!name1[0]) DrawText(TextFormat("Player 1:"), 325, 442, 30, GRAY);
            if(swStart[0] && !name1[0]) DrawText(TextFormat("Player 1:"), 325, 442, 30, MAROON);
            if (mouseOnTextName1) DrawRectangleLinesEx(name1Rec, 3, RED);
            else   DrawRectangleLinesEx(name1Rec, 3, DARKGRAY);
            if(swStart[0])   DrawRectangleLinesEx(name1Rec, 3, RED);
            DrawText(name1, name1Rec.x + 5, name1Rec.y + 8, 30, DARKGREEN);
            
            DrawRectangleRec(name2Rec, LIGHTGRAY);
            DrawText(TextFormat("%d/10",Nname2), 645, 537, 15, DARKGRAY);
            if(!name2[0]) DrawText(TextFormat("Player 2:"), 325, 519, 30, GRAY);
            if(swStart[1] && !name2[0]) DrawText(TextFormat("Player 2:"), 325, 519, 30, MAROON);
            if (mouseOnTextName2)   DrawRectangleLinesEx(name2Rec, 3, RED);
            else  DrawRectangleLinesEx(name2Rec, 3, DARKGRAY);
            if(swStart[1])    DrawRectangleLinesEx(name2Rec, 3, RED);
            DrawText(name2, (int)name2Rec.x + 5, (int)name2Rec.y + 8, 30, DARKGREEN);
        }
        if(numPl==3 || numPl==4)
        {    
            DrawRectangleRec(name3Rec, LIGHTGRAY);
            DrawText(TextFormat("%d/10",Nname3), 645, 614, 15, DARKGRAY);
            if(!name3[0]) DrawText(TextFormat("Player 3:"), 325, 595, 30, GRAY);
            if(swStart[2] && !name3[0]) DrawText(TextFormat("Player 3:"), 325, 595, 30, MAROON);
            if (mouseOnTextName3)   DrawRectangleLinesEx(name3Rec, 3, RED);
            else  DrawRectangleLinesEx(name3Rec, 3, DARKGRAY);
            if(swStart[2])     DrawRectangleLinesEx(name3Rec, 3, RED);
            DrawText(name3, (int)name3Rec.x + 5, (int)name3Rec.y + 8, 30, DARKGREEN);
        }
        if(numPl==4)
        {
            DrawRectangleRec(name4Rec, LIGHTGRAY);
            DrawText(TextFormat("%d/10",Nname4), 645, 691, 15, DARKGRAY);
            if(!name4[0]) DrawText(TextFormat("Player 4:"), 325, 673, 30, GRAY);
            if(swStart[3] && !name4[0]) DrawText(TextFormat("Player 4:"), 325, 673, 30, MAROON);
            if (mouseOnTextName4)  DrawRectangleLinesEx(name4Rec, 3, RED);
            else DrawRectangleLinesEx(name4Rec, 3, DARKGRAY);
            if(swStart[3]) DrawRectangleLinesEx(name4Rec, 3, RED);
            DrawText(name4, (int)name4Rec.x + 5, (int)name4Rec.y + 8, 30, DARKGREEN);
        }
        
        EndDrawing();
    }

    CloseWindow();
    
    UnloadTexture(background);
    UnloadTexture(greenPenguin);
    UnloadTexture(redPenguin);
    UnloadTexture(goldPenguin);
    UnloadTexture(purplePenguin);
    
    UnloadMusicStream(firstMusic);
    UnloadMusicStream(itemMusic);
    
    CloseAudioDevice();
    return 0;
}
