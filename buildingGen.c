#include <stdio.h>
#include <stdlib.h>

typedef struct struct_Floor{
  int width;
  int height;
  int** map;
} Floor;

typedef struct struct_Building{
  Floor* floors;
  int height;
} Building;

Floor* generateBase(int, int);
Floor* makeFloor(int, int, int**);
Floor* generateFloorFromFloor(Floor*);
void printFloor(Floor*);
void freeFloor(Floor*);

Building* generateBuilding(int, int, int);
void printBuilding(Building*);
void freeBuilding(Building*);

Floor* generateBase(int width, int height){
  //2D array that will hold room orientation
  int** map = malloc(sizeof(int*) * width);

  //Allocating spaces in map
  for(int row = 0; row < width; row++){
    map[row] = malloc(sizeof(int) * height);
    for(int col = 0; col < height; col++){
      if(rand() % 2 == 0){
        map[row][col] = 1;
      }
      else{
        map[row][col] = 0;
      }
    }
  }
  
  Floor* floor = makeFloor(width, height, map);
  return floor;
}

Floor* generateFloorFromFloor(Floor* prev){
  
  int** map = malloc(sizeof(int*) * prev->width);

  for(int row = 0; row < prev->width; row++){
    map[row] = malloc(sizeof(int) * prev->height);
    for(int col = 0; col < prev->height; col++){
      map[row][col] = 0;
      if(prev->map[row][col] == 1){
        if(rand() % 2 == 0){
          map[row][col] = 1;
        }
      }
    }
  }
  

  Floor* floor = makeFloor(prev->width, prev->height, map);
  return floor;
}

Floor* makeFloor(int Width, int Height, int** Map){
  Floor* floor = malloc(sizeof(Floor));
  floor->width = Width;
  floor->height = Height;
  floor->map = Map;

  return floor;
}

void printFloor(Floor* floor){
  for(int row = 0; row < floor->width; row++){
    //printf("row %d: ", row);
    for(int col = 0; col < floor->height; col++){
      printf("%d ", floor->map[row][col]);
    }
    printf("\n");
  }
}
 
void freeFloor(Floor* floor){
  for(int row = 0; row < floor->width; row++){
    free(floor->map[row]);
  }
  free(floor->map);
  //free(floor);
}

Building* generateBuilding(int width, int height, int levels){
  Floor* floors = malloc(sizeof(Floor) * levels);
  floors[0] = *generateBase(width, height);
  for(int i = 1; i < levels; i++){
    floors[i] = *generateFloorFromFloor(&floors[i-1]);
  } 

  Building* building = malloc(sizeof(Building));
  building->height = levels;
  building->floors = floors;

  return building;
}

void printBuilding(Building* building){
  for(int i = 0; i < building->height; i++){
    printFloor(&building->floors[i]);
    printf("\n");
  }
}

void freeBuilding(Building* building){
  for(int i = 0; i < building->height; i++){
    freeFloor(&building->floors[i]);
  }
  free(building->floors);
  free(building);
}

int main(){

  int width = 5;
  int height = 5;
  int levels = 4;

  //Initialize random number gen
  srand(time(NULL));

  Building* building = generateBuilding(width, height, levels);

  printBuilding(building);

  freeBuilding(building);

  return 0;
}
