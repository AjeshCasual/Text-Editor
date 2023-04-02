/*
 ***************************************************************
 *                    Anadeia - Text Editor                     *
 *                      by Ajesh Sharma                         *
 *                                                              *
 *             [Github](https://github.com/Ajesh2)              *
 *                                                              *
 * A text editor made by Ajesh Sharma to learn and understand   *
 * the working of raylib and C.                                 *
 *                                                              *
 * The project is/was a way for me to visualize as to what I    *
 * need in a text editor and the hardship in making it and      *
 * even though it is not the most optimized or maybe not even   *
 * optimized, this project was a lot of fun to work on and am   *
 * happy with how it turned out and will keep on working on it. *
 ****************************************************************
 */
#include "math.h"
#include "include/raylib.h"

#define textBoxActive (Color){0,0,0,200}
#define textBoxInactive (Color){0,0,0,100}
#define textBoxActive (Color){0,0,0,200}
#define textBoxInactive (Color){0,0,0,100}
int activeBoxes = 0;
int selectedBoxes = -1;
int mainMode = 1;

struct editBox
{
    Rectangle filePosition;
    bool dragBox;
    Vector2 cursorPosition;
    char fileDir[100];

    //x for position in line, y is for line;
};


struct editBox arrayTextBox[200];


void boxUpdateDraw(){
    int i,j;
    int closeX = 50;
    int tabHeight = 30;
    int fontHeight = 10;
    for(i=0;i < 200;i++){
        if(i != selectedBoxes){
            DrawRectangleRec(arrayTextBox[i].filePosition,textBoxInactive);
            DrawRectangleRec((Rectangle){arrayTextBox[i].filePosition.x + arrayTextBox[i].filePosition.width - closeX,
                                            arrayTextBox[i].filePosition.y,
                                            closeX,tabHeight},RED);
            DrawRectangleLinesEx(arrayTextBox[i].filePosition,1,DARKGRAY);
            DrawRectangleLinesEx((Rectangle){arrayTextBox[i].filePosition.x + arrayTextBox[i].filePosition.width - closeX,
                                            arrayTextBox[i].filePosition.y,
                                            closeX,tabHeight},1,DARKGRAY);
            DrawRectangleLinesEx((Rectangle){arrayTextBox[i].filePosition.x,arrayTextBox[i].filePosition.y,arrayTextBox[i].filePosition.width,tabHeight},1,DARKGRAY);
        }
    }
    i = selectedBoxes;
    //main box
    DrawRectangleRec(arrayTextBox[i].filePosition,textBoxActive);

    //main box outline
    DrawRectangleLinesEx(arrayTextBox[i].filePosition,1,RAYWHITE);

    //close button
    DrawRectangleRec((Rectangle){arrayTextBox[i].filePosition.x + arrayTextBox[i].filePosition.width - closeX,
                                    arrayTextBox[i].filePosition.y,
                                    closeX,tabHeight},RED);
    
    
    //close button outline
    DrawRectangleLinesEx((Rectangle){arrayTextBox[i].filePosition.x + arrayTextBox[i].filePosition.width - closeX,
                                    arrayTextBox[i].filePosition.y,
                                    closeX,tabHeight},1,RAYWHITE);

    //bar
    DrawRectangleLinesEx((Rectangle){arrayTextBox[i].filePosition.x,arrayTextBox[i].filePosition.y,arrayTextBox[i].filePosition.width - closeX,tabHeight},1,RAYWHITE);
    /*DrawRectangleLinesEx((Rectangle){arrayTextBox[i].filePosition.x,
                                    arrayTextBox[i].filePosition.y + tabHeight - 1,
                                    30,arrayTextBox[i].filePosition.height - tabHeight + 1},
                                    1,RAYWHITE);*/

    
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        if(CheckCollisionPointRec((Vector2){GetMouseX(),GetMouseY()},(Rectangle){arrayTextBox[i].filePosition.x,arrayTextBox[i].filePosition.y,arrayTextBox[i].filePosition.width,tabHeight})){
            arrayTextBox[i].dragBox = true;
        }
    }
    else {
        arrayTextBox[i].dragBox = false;
    }
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(CheckCollisionPointRec((Vector2){GetMouseX(),GetMouseY()},(Rectangle){arrayTextBox[i].filePosition.x + arrayTextBox[i].filePosition.width - closeX,arrayTextBox[i].filePosition.y,closeX,tabHeight})){
            for(j = i;j<199;j++){
                arrayTextBox[j] = arrayTextBox[j + 1];
            }
            activeBoxes--;
            if(selectedBoxes >= activeBoxes){
                selectedBoxes = 0;
            }
        }
    } 
    
    if(arrayTextBox[i].dragBox){
        arrayTextBox[i].filePosition.x += GetMouseDelta().x;
        arrayTextBox[i].filePosition.y += GetMouseDelta().y;
    }

};

int main(void){
    int i;
    InitWindow(GetScreenWidth(),GetScreenHeight(), "Anadeia");
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_UNDECORATED);
    SetWindowState(FLAG_FULLSCREEN_MODE);
    SetWindowState(FLAG_WINDOW_ALWAYS_RUN);
    FilePathList test = LoadDirectoryFilesEx("background",".png",false);
    Texture2D backgrounds[test.count];
    for(i = 0;i < test.count;i++){
        Image backgroundMain = LoadImage(test.paths[i]);
        ImageResize(&backgroundMain,GetScreenWidth(),GetScreenHeight());
        Texture2D backgroundMain1 = LoadTextureFromImage(backgroundMain);
        UnloadImage(backgroundMain);
        backgrounds[i] = backgroundMain1;
    }
    
    
    for(i = 0;i < 6;i++){
        struct editBox test = {(Rectangle){GetRandomValue(0,600),GetRandomValue(0,600),GetRandomValue(200,500),GetRandomValue(200,500)},false,(Vector2){0,0},"test.txt"};
        activeBoxes += 1;
        selectedBoxes += 1;
        arrayTextBox[i] = test;
    }
    int frameChange = 0;
    float frameDelta= 0;

    
    
    

    while (!WindowShouldClose())
    {
        
        if(frameDelta < 30){
            frameDelta += GetFrameTime();
        }
        else{
            frameChange += 1;
            frameDelta = 0;
            if(frameChange>test.count - 1){
                frameChange = 0;
            }
        }
        if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_TAB)){
            selectedBoxes += 1;
            if(selectedBoxes >= activeBoxes){
                selectedBoxes = 0;
            }
        }
        if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_N)){
            if(activeBoxes < 199){
                activeBoxes += 1;
                selectedBoxes = activeBoxes - 1;
                struct editBox test = {(Rectangle){GetRandomValue(0,600),GetRandomValue(0,600),GetRandomValue(200,500),GetRandomValue(200,500)},false,(Vector2){0,0},"test"};
                if(selectedBoxes >= activeBoxes){
                    selectedBoxes = 0;
                }
                arrayTextBox[activeBoxes - 1] = test;
            }
        }
        if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_DELETE)){
            if(activeBoxes > 0){
                int j;
                for(j = selectedBoxes;j<199;j++){
                    arrayTextBox[j] = arrayTextBox[j + 1];
                }
                activeBoxes--;
                if(selectedBoxes >= activeBoxes){
                    selectedBoxes = 0;
                }
            }
            
        }
        BeginDrawing();
            ClearBackground(BLANK);
            
            DrawTexture(backgrounds[frameChange],0,0, WHITE);
            boxUpdateDraw();
            DrawRectangleRec((Rectangle){0,GetScreenHeight() - 20,GetScreenWidth(),20},BLACK);
            DrawFPS(0,0);
            DrawText(TextFormat("Anadeia | Tab: %d/%d | %d:%d:%d",selectedBoxes + 1,activeBoxes,(int){GetTime()}/3600,(int){GetTime()}/60,(int){GetTime()}%60),10,GetScreenHeight() - 17,16,WHITE);
        EndDrawing();
    }
    for(i = 0;i < test.count;i++){
        UnloadTexture(backgrounds[i]);
    }

    CloseWindow();
    return 0;
}