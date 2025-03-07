#include <raylib.h>

#define height 800 
#define width 600
#define Block_Size 40
#define Rows 20 
#define Cols 15

int grid[Rows][Cols] = {0};

typedef struct {
  int shape[4][4]; 
  int posy,posx; 
}Tetris;

int frameCount = 0;
//7 for 7types shapes and 4 by 4 array
int tetrisShape[7][4][4] = {
  // 1
  {{0,0,0,0},
  {1,1,1,1},
  {0,0,0,0},
  {0,0,0,0}
}, // 2
{{2,2,0,0},
{2,2,0,0},
{0,0,0,0},
{0,0,0,0}
}, //3
{{0,3,0,0},
{3,3,3,0},
{0,0,0,0},
{0,0,0,0}
}, // 4
{{0,4,4,0},
{4,4,0,0},
{0,0,0,0},
{0,0,0,0}
}, //5
{{5,5,0,0},
{0,5,5,0},
{0,0,0,0},
{0,0,0,0}
},  //6
{{0,6,0,0},
{0,6,0,0},
{0,6,6,0},
{0,0,0,0}
}, //7
{{0,0,7,0},
{0,0,7,0},
{0,7,7,0},
{0,0,0,0}
},
};
// tetris currentshape is for the struct and current shape have posx posy and shape array
Tetris currentShape;

void spawn(int type){
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      currentShape.shape[i][j] = tetrisShape[type][i][j];
    }
  }
  currentShape.posx = 3;
  currentShape.posy = 0;
}
int Collision(int dx, int dy) {
  for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
          if (currentShape.shape[i][j] != 0) {
              int newX = currentShape.posx + j + dx;
              int newY = currentShape.posy + i + dy;

              if (newX < 0 || newX >= Cols || newY >= Rows) {
                  return 1;
              }
              if (newY >= 0 && grid[newY][newX] != 0) {
                  return 1; 
              }
          }
      }
  }
  return 0;
}

void ClearLines() {
  for (int i = Rows - 1; i >= 0; i--) {
      int full = 1;
      for (int j = 0; j < Cols; j++) {
          if (grid[i][j] == 0) {
              full = 0;
              break;
          }
      }
      if (full) {
          for (int k = i; k > 0; k--) {
              for (int j = 0; j < Cols; j++) {
                  grid[k][j] = grid[k - 1][j];
              }
          }
          for (int j = 0; j < Cols; j++) {
              grid[0][j] = 0;
          }
          i++;
      }
  }
}

void Respawn() {
  for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
          if (currentShape.shape[i][j] != 0) {
              grid[currentShape.posy + i][currentShape.posx + j] = currentShape.shape[i][j];
          }
      }
  }
  ClearLines();
  spawn(GetRandomValue(0, 6));
}

void move(int dx , int dy){
  if (!Collision( dx , dy)){
  currentShape.posx += dx;
  currentShape.posy += dy;
  }
  
}
void drawShape(){
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      if (currentShape.shape[i][j] != 0){
         DrawRectangle((currentShape.posx + j ) * Block_Size ,
          (currentShape.posy + i) * Block_Size ,
           Block_Size,Block_Size , RED); 
      }
    }
  }
}
void GridLines(){
  for (int i = 0; i < Rows; i++){
    for (int j = 0; j < Cols; j++){
      if (grid[i][j] != 0)
      {
         DrawRectangle(j * Block_Size,i * Block_Size, Block_Size,Block_Size , PINK);  
      }
      DrawRectangleLines(j * Block_Size,i * Block_Size, Block_Size, Block_Size , GRAY);
    } 
  }
}

int main(){
    InitWindow(width , height , "Tetris");
   SetTargetFPS(60);
   spawn(GetRandomValue(0 , 6));
   while (!WindowShouldClose()){
    frameCount++;
    if (frameCount >= 30) {
      if (Collision(0, 1)) {
          Respawn();
      } else {
          move(0, 1);
      }
      frameCount = 0;
  }
  
    
    if (IsKeyPressed(KEY_LEFT))
    {
       move(-1,0);
    }
    if (IsKeyPressed(KEY_RIGHT))
    {
     move(1,0);
    }
    if (IsKeyPressed(KEY_DOWN))
    {
      move(0,1);
    }
    
    BeginDrawing();
    ClearBackground(RAYWHITE);
    GridLines();
    drawShape();
    EndDrawing();
   }
   CloseWindow();
   return 0 ;
}
// tetris complete 
// leatcode complete
// next corse complete 
