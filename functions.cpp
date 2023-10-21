#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

using std::cout, std::endl, std::string;

void initializeImage(Pixel image[][MAX_HEIGHT]) {
  // iterate through columns
  for (unsigned int col = 0; col < MAX_WIDTH; col++) {
    // iterate through rows
    for (unsigned int row = 0; row < MAX_HEIGHT; row++) {
      // initialize pixel
      image[col][row] = {0, 0, 0};
    }
  }
}

void loadImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int& height) {
  ifstream inputFS;
  inputFS.open(filename);

  if(!inputFS.is_open()){
    throw std::runtime_error("Failed to open " + filename);
  }
  string check = "";
  inputFS >> check;
  if (check != "p3" && check != "P3"){
    throw std::runtime_error("Invalid type " + check);
  }

  int tempWidth;
  int tempHeight;

  inputFS >> tempWidth;
  inputFS >> tempHeight;
  if(tempWidth > static_cast<int>(MAX_WIDTH) || tempWidth <= 0 || tempHeight > static_cast<int>(MAX_HEIGHT) || tempHeight <= 0){
    throw std::runtime_error("Invalid dimensions");
  }
  width = static_cast<unsigned int>(tempWidth);
  height = static_cast<unsigned int>(tempHeight);


  unsigned int column = width;
  unsigned int row = height;

  for (unsigned int r = 0; r < row; r++){
      for (unsigned int c = 0; c < column; c++){
        image[c][r].r = -1;
        image[c][r].g = -1;
        image[c][r].b = -1;
      }}

  int maxVal;
  inputFS >> maxVal;
  if (maxVal != 255){
    throw std::runtime_error("Invalid color value");
  }

  int numPixels = width * height;
  double pixelCount = 0;
    for (unsigned int r = 0; r < row; r++){
      for (unsigned int c = 0; c < column; c++){
        inputFS >> image[c][r].r;
        if(inputFS.eof() && inputFS.fail()){
          throw std::runtime_error("Invalid color value");
        }
        inputFS >> image[c][r].g;
        if(inputFS.eof() && inputFS.fail()){
          throw std::runtime_error("Invalid color value");
        }
        inputFS >> image[c][r].b;
        if(inputFS.eof() && inputFS.fail()){
          throw std::runtime_error("Invalid color value");
        }
        if(image[c][r].r > 255 || image[c][r].r < 0 ||
        image[c][r].g > 255 || image[c][r].g < 0 ||
        image[c][r].b > 255 || image[c][r].b < 0){
        throw std::runtime_error("Invalid color value");
        }
          pixelCount++;
        }
      }
    
    int temp;
    inputFS >> temp;
    if(!inputFS.fail()){
      throw std::runtime_error("Too many values");
    }

  if(pixelCount < numPixels){
    throw std::runtime_error("Invalid color value");
  }
  else if(pixelCount > numPixels){
    throw std::runtime_error("Too many values");
  }
}

void outputImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height) {
  ofstream outFile;
  outFile.open(filename);
  if (!outFile.is_open()){
    throw std::runtime_error("Failed to open " + filename);
  }

  string Preamble = "P3";
  outFile << Preamble << endl << width << " " << height << endl << "255" << endl;

  unsigned int row = width;
  unsigned int column = height;

  for (unsigned int c = 0; c < column; c++){
      for (unsigned int r = 0; r < row; r++){
        outFile << image[r][c].r << endl;
        outFile << image[r][c].g << endl;
        outFile << image[r][c].b << endl;
      }
    }
}

unsigned int energy(Pixel image[][MAX_HEIGHT], unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
Pixel Ex;
Pixel Ey;
int ExF;
int EyF;
int tWidth = width;
int tHeight = height;

int a = x-1;
if(a < 0){
  a = tWidth-1;
}
int b = x+1;
if(b > tWidth-1){
  b = 0;
}

Ex.r = image[b][y].r - image[a][y].r;
if(Ex.r < 0){
  Ex.r *= -1;
}
Ex.g = image[b][y].g - image[a][y].g;
if(Ex.g < 0){
  Ex.g *= -1;
}
Ex.b = image[b][y].b - image[a][y].b;
if(Ex.b < 0){
  Ex.b *= -1;
}

int c = y-1;
if(c < 0){
  c = tHeight-1;
}
int d = y+1;
if(d > tHeight-1){
  d = 0;
}
Ey.r = image[x][d].r - image[x][c].r;
if(Ey.r < 0){
  Ey.r *= -1;
}
Ey.g = image[x][d].g - image[x][c].g;
if(Ey.g < 0){
  Ey.g *= -1;
}
Ey.b = image[x][d].b - image[x][c].b;
if(Ey.b < 0){
  Ey.b *= -1;
}

int Final = 0;
ExF = pow(Ex.r,2)+pow(Ex.g,2)+pow(Ex.b,2);
EyF = pow(Ey.r,2)+pow(Ey.g,2)+pow(Ey.b,2);
Final = ExF + EyF;
return Final;



  return 0;
}


unsigned int loadVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_col, unsigned int width, unsigned int height, unsigned int seam[]) {
int runningTotal = energy(image, start_col, 0, width, height);
for (unsigned int i = 0; i < height; i++){
  seam[i] = 0;
}
seam[0] = start_col;
for(unsigned int row = 1; row < height; row++){
  unsigned int min = 2147483647;
  int leftE;
  int midE;
  int rightE;
  if(start_col == 0){
    rightE = min;
    midE = energy(image, start_col, row, width, height);
    leftE = energy(image, start_col+1, row, width, height);
  }else if(start_col == width-1){
    leftE = min;
    midE = energy(image, start_col, row, width, height);
    rightE = energy(image, start_col-1, row, width, height);
  }else{
    leftE = energy(image, start_col+1, row, width, height);
    midE = energy(image, start_col, row, width, height);
    rightE = energy(image, start_col-1, row, width, height);
  }

  if(midE <= rightE && midE <= leftE){
    runningTotal+= midE;
    seam[row]=start_col;
  }else if(leftE <= rightE){
    runningTotal+=leftE;
    start_col++;
    seam[row]=start_col;
  }else{
    runningTotal+=rightE;
    start_col--;
    seam[row]=start_col;
  }
}
return runningTotal;
}

unsigned int loadHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_row, unsigned int width, unsigned int height, unsigned int seam[]) {
int runningTotal = energy(image, 0, start_row, width, height);
for (unsigned int i = 0; i < width; i++){
  seam[i] = 0;
}
seam[0] = start_row;
for(unsigned int col = 1; col < width; col++){
  unsigned int min = 2147483647;
  int leftE = 0;
  int midE = 0;
  int rightE = 0;
  if(start_row == 0){
    leftE = min;
    midE = energy(image, col, start_row, width, height);
    rightE = energy(image, col, start_row+1, width, height);
  }else if(start_row == height-1){
    rightE = min;
    midE = energy(image, col, start_row, width, height);
    leftE = energy(image, col, start_row-1, width, height);
  }else{
    rightE = energy(image, col, start_row+1, width, height);
    midE = energy(image, col, start_row, width, height);
    leftE = energy(image, col, start_row-1, width, height);
  }
  if(midE <= rightE && midE <= leftE){
    runningTotal+= midE;
    seam[col]=start_row;
  }else if(leftE <= rightE){
    runningTotal+=leftE;
    start_row--;
    seam[col]=start_row;
  }else{
    runningTotal+=rightE;
    start_row++;
    seam[col]=start_row;
  }
}
return runningTotal;
}

void findMinVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
int min = 0;
min = loadVerticalSeam(image, 0, width,  height, seam);
int minIndex = 0;
minIndex = 0;
for(unsigned int i = 1; i < width; i++){
  int temp = loadVerticalSeam(image, i, width,  height, seam);
  if (temp < min){
    min = temp;
    minIndex = i;
  }
}
loadVerticalSeam(image, minIndex, width,  height, seam);
}

void findMinHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
int min = 0;
min = loadHorizontalSeam(image, 0, width,  height, seam);
int minIndex = 0;
minIndex = 0;
for(unsigned int i = 1; i < height; i++){
  int temp = loadHorizontalSeam(image, i, width,  height, seam);
  if (temp < min){
    min = temp;
    minIndex = i;
  }
}
loadHorizontalSeam(image, minIndex, width,  height, seam);
}

void removeVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int height, unsigned int verticalSeam[]) {
for (unsigned int r = 0; r < height;r++){
  for(unsigned int col = verticalSeam[r]; col < width-1; col++){
    image[col][r].r = image[col+1][r].r;
    image[col][r].g = image[col+1][r].g;
    image[col][r].b = image[col+1][r].b;
  }
}
width = width-1;
}

void removeHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int& height, unsigned int horizontalSeam[]) {
for (unsigned int col = 0; col < width;col++){
  for(unsigned int r = horizontalSeam[col]; r < height-1; r++){
    image[col][r].r = image[col][r+1].r;
    image[col][r].g = image[col][r+1].g;
    image[col][r].b = image[col][r+1].b;
  }
}
height = height-1;
}

