void drawPlayground(void){
    for(int i = 1; i <= 8; i++){
        if(i % 2 == 0)
            for(int j = 1; j <= 8; j++)
                DrawPoly((Vector2){74*j + 336, 65*i + 8}, 6, 40, 0, SKYBLUE);
        
        else
            for(int j = 1; j <= 7; j++)
                DrawPoly((Vector2){74*j + 373, 65*i + 8}, 6, 40, 0, SKYBLUE);
    }
}