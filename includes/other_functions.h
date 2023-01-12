void createRandomTiles(char tiles[8][8])
{
    char singleFishCount = 0;
    char doubleFishCount = 0;
    char tripleFishCount = 0;
    
    while(singleFishCount < 30||doubleFishCount < 20||tripleFishCount < 10){
        char i = GetRandomValue(0,7);
        char j;
        
        if(i % 2 == 0) j = GetRandomValue(0,6);
        else           j = GetRandomValue(0,7);
        
        if(tiles[i][j]==0){
            if     (tripleFishCount < 10) {tiles[i][j] = 3; tripleFishCount++;}
            else if(doubleFishCount < 20) {tiles[i][j] = 2; doubleFishCount++;}
            else                          {tiles[i][j] = 1; singleFishCount++;}
        }
    }
}
Texture2D loadImage(char imgPath[], unsigned short int width, unsigned short int height)
{
    Image img  = LoadImage(imgPath);
    ImageResize(&img, width, height);
    Texture2D result = LoadTextureFromImage(img);
    UnloadImage(img);
    return result;
}

bool canMove(char tiles[8][8], char whoseTurn){
    
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if(tiles[i][j] == whoseTurn + 4){
                for(char y = i, x = j-1; x >= 0; x--){
                    if(tiles[y][x] >= 1 && tiles[y][x] <= 3 || tiles[y][x] >= 8)
                        return true;
                    else break;
                }
                for(char y = i, x = j+1; x <= 7; x++){
                    if(tiles[y][x] >= 1 && tiles[y][x] <= 3 || tiles[y][x] >= 8)
                        return true;
                    else break;
                }
                for(char y = i-1, x = j; y >= 0 && x >= 0; y--){
                    if(y%2==0) x--;
                    if(x < 0) break;
                    if(tiles[y][x] >= 1 && tiles[y][x] <= 3 || tiles[y][x] >= 8)
                        return true;
                    else break;
                }
                for(char y = i-1, x = j; y >= 0 && x <= 7; y--){
                    if(y%2==1) x++;
                    if(x > 7) break;
                    if(tiles[y][x] >= 1 && tiles[y][x] <= 3 || tiles[y][x] >= 8)
                        return true;
                    else break;
                }
                for(char y = i+1, x = j; y <= 7 && x <= 7; y++){
                    if(y%2==1) x++;
                    if(x > 7) break;
                    if(tiles[y][x] >= 1 && tiles[y][x] <= 3 || tiles[y][x] >= 8)
                        return true;
                    else break;
                }
                for(char y = i+1, x = j; y <= 7 && x >= 0; y++){
                    if(y%2==0) x--;
                    if(x < 0) break;
                    if(tiles[y][x] >= 1 && tiles[y][x] <= 3 || tiles[y][x] >= 8)
                        return true;
                    else break;
                }
            }
        
    return false;
}

void DrawFunctionsBox(Rectangle R, char name[], Color C, int x, int y, int thikness, int code)
{
    if (code == '1')
    {
        DrawRectangleLinesEx(R, thikness, C);
        DrawText(name, x, y, 25, C);
        return;
    }
    DrawRectangleLinesEx(R, thikness, Fade(C, 0.6));
    DrawText(name, x, y, 25, Fade(C, 0.6));

    return;
}

int getName(char name[], int *Nname)
{
    if(*Nname<=9)
    {
        int key=GetCharPressed();
        while(key>0)
        {
            if ((key >= 32) && (key <= 125))
            {
                name[*Nname] = (char)key;
                name[(*Nname)+1] = '\0'; // Add null terminator at the end of the string.
                (*Nname)++;
                if( (*Nname) >=10) break;
            }
            
            key = GetCharPressed();
        }
    }
            
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        (*Nname)--;
        if ( (*Nname) < 0) *Nname = 0;
        name[*Nname] = '\0';
    }
    
    return ;
}
void checkFunction(Rectangle box, bool *mouseOnBox, bool *mousePressBox)
{
    if(CheckCollisionPointRec(GetMousePosition(), box)) *mouseOnBox= true;
    else *mouseOnBox= false;
    if(CheckCollisionPointRec(GetMousePosition(), box) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) *mousePressBox= true;
    else if (!CheckCollisionPointRec(GetMousePosition(), box) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) *mouseOnBox= false;
}
void soundBoxes(bool mouseOnBox, bool *swItem, Music itemMusic)
{
    if(mouseOnBox && *swItem==false)
    {
        PlayMusicStream(itemMusic);
        *swItem=true;
    }
    if(!mouseOnBox) *swItem=false;
}