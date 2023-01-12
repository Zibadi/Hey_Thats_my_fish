int HelpF(Music firstMusic)   //Help function
{
    Rectangle back = {171, 96, 1026, 576};
    Rectangle exit = {1140, 100, 50, 50};
    
    char help[]="HELP";
    char helpDescription[]="Place your penguin on ice cubes on which there is 1 fish so in\neach round of game you can move your desired penguin along 6\norientaions as far as you like to catch more fish. The ice cube\nyou are on will break when you move.\nCatch more fish to win the game; The number of ice cubes you\nhave broken during the game will determine the final winner in the\neven of multiple winners.";
    char rules[]= "RULES:";
    char rulesDescription[]="1. You can not jump over the other players or gaps.\n2. Choose one direction and go along it as far as you want; Not\n   to redirect during the path.";
    
    int counter1=0; //show texts animationally 
    int counter2=0; //show texts animationally 
    int counter3=0; //show texts animationally 
    int counter4=0; //show texts animationally 
    
    while( !WindowShouldClose() )
    {
        UpdateMusicStream(firstMusic);
        counter1++;
        if(counter1 >= strlen(help) * 7) counter2++;
        if(counter2 >= strlen(rules) * 7) counter3++;
        if(counter3 >= strlen(rulesDescription) * 7) counter4++;
        
        if(CheckCollisionPointRec(GetMousePosition(), exit) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
            return 2;
        
        BeginDrawing();
        
        DrawRectangleRec(back, SKYBLUE);
        DrawRectangleRec(exit, RED);
        DrawText("x", 1148, 87, 70, DARKGRAY);
        
        DrawText(TextSubtext(help, 0, counter1/7), 575, 100, 75, DARKGRAY);
        if(counter1<strlen(help) * 7) 
        {       
            EndDrawing();
            continue;
        }
        
        DrawText(TextSubtext(helpDescription, 0, counter2/3), 180, 180, 30, DARKGREEN);
        if(counter2<strlen(helpDescription) * 3) 
        {       
            EndDrawing();
            continue;
        }
        DrawText(TextSubtext(rules, 0, counter3/7), 180 ,493 ,45 , DARKGRAY);
        if(counter3<strlen(rules) * 7) 
        {       
            EndDrawing();
            continue;
        }DrawText(TextSubtext(rulesDescription, 0, counter4/3),180 ,550 ,30 , DARKGREEN);
        if(counter4<strlen(rulesDescription) * 3) 
        {       
            EndDrawing();
            continue;
        }
        
        EndDrawing();
    }
   
   return 1;
}