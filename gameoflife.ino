// Written by Caleb LaFeve 
//Conway's game of life



//Rules
//    Any live cell with fewer than two live neighbors dies, as if by underpopulation.
//    Any live cell with two or three live neighbors lives on to the next generation.
//    Any live cell with more than three live neighbors dies, as if by overpopulation.
//    Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

#include <RGBmatrixPanel.h>

#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
//#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

//Animation Speed
#define animationSpeed 75

//How many loops before it resets
#define resetTime 300

//Replace width, height, and both 2D arrays to the dimensions of your LED matrix
//I was working with a 32x32
#define WIDTH 32
#define HEIGHT 32


RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
//May need to change the lines above if you're using a different board or LED matrix than the 32x32 

int r, g, b;
int counter = 0;
int cells[HEIGHT][WIDTH];
int newCells[HEIGHT][WIDTH];



void setup() {
  //Color 
  r = 1;
  g = 0;
  b = 0;

  //Create dead/alive cells
  //0 == Dead
  //1 == Alive

  for(unsigned int row = 0; row < WIDTH; row++) for(unsigned int col = 0; col < HEIGHT; cells[row][col++] = random(0,2));
  
  matrix.begin();

}

void loop() {
  
  counter++;
  if(counter == resetTime){
    reset();
    counter = 0;
  }
  
  update();
  delay(animationSpeed);
  writeNextGeneration();
  

}
//Resets 2D araay back to randomness
void reset(){
  for(unsigned int row = 0; row < WIDTH; row++) for(unsigned int col = 0; col < HEIGHT; cells[row][col++] = random(0,2));
}
//This method checks every cell(pixel) and check to see how many neighbors it has
//The amount of neighbors determines its future state
void writeNextGeneration(){
  for(int row = 0; row < WIDTH; row++){
    for(int col = 0; col < HEIGHT; col++){
      newCells[row][col] = cells[row][col];
    }
  }
  
  for(unsigned int row = 0; row < WIDTH; row++){
    for(unsigned int col = 0; col < HEIGHT; col++){
      int surroundingCells = 0;
     
      boolean isAlive=false;

      cells[row][col]?isAlive = true:isAlive = false;
      
      for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
          int colNum = (row + i) % WIDTH;
          int rowNum = (col + j) % HEIGHT;
          surroundingCells += cells[colNum][rowNum];
        }
      }
      surroundingCells -= cells[row][col];
      //Check neighboring cells and store its future state in a new 2D array
      if(surroundingCells < 2 && isAlive) newCells[row][col] = 0;
   
      if(surroundingCells > 3 && isAlive) newCells[row][col] = 0;
 
      if(surroundingCells == 3 && !isAlive) newCells[row][col] = 1;
      
    }
  }
  //copy new 2d Array to old
  for(int row = 0; row < WIDTH; row++){
    for(int col = 0; col < HEIGHT; col++){
      cells[row][col] = newCells[row][col];
    }
  }
  
}
//Update pixels
void update(){
  for(unsigned int row = 0; row < WIDTH; row++){
    for(unsigned int col = 0; col < HEIGHT; col++){
      if(cells[row][col] == 1){

        //Random colors/party mode ;)
        //matrix.drawPixel(row, col, matrix.Color333(random(7), random(7),random(7)));
        //If you uncomment the above line, make sure to comment the line below
        matrix.drawPixel(row, col, matrix.Color333(r, g,b));
      }
      else
        matrix.drawPixel(row, col, matrix.Color333(0,0,0));
    }
  }
}

