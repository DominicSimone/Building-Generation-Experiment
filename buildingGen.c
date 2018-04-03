#include <stdio.h>
#include <stdlib.h>
#include "buildingGen.h"

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


//Check the surrounding 8 spaces, helper function
//Return the number of spaces occupied
int countNeighbors(Floor* floor, int row, int col){
  unsigned int numNeighbors = 0;

  if(col > 0){
    if(floor->map[row][col - 1] != 0){
      numNeighbors +=1;
    }
  }

  if(row > 0){
    if(floor->map[row - 1][col] != 0){
      numNeighbors += 1;
    }
  }

  if(row < floor->width - 1){
    if(floor->map[row + 1][col] != 0){
      numNeighbors += 1;
    }
  }

  if(col < floor->height - 1){
    if(floor->map[row][col + 1] != 0){
      numNeighbors += 1;
    }
  }

  return numNeighbors;
}

//Cut out rooms that are seperated from others
//  1 0 1    1 0 1
//  0 1 0 -> 0 0 0
//  0 0 0    0 0 0
void clipFloor(Floor* floor, int adjacentRooms){ 
  for(int row = 0; row < floor->width; row++){
    for(int col = 0; col < floor->height; col++){
      //If space has a room, check surrounding spots
      if(floor->map[row][col] == 1){
        if(countNeighbors(floor, row, col) <= adjacentRooms){
          floor->map[row][col] = 0;
        }
      }
    }
  }
}

//Fill in spaces that are surrounded by n rooms (specified by argument)
//  0 1 0    0 1 0
//  1 0 1 -> 1 1 1
//  1 1 0    1 1 0
void fillFloor(Floor* floor, int adjacentRooms){
  for(int row = 0; row < floor->width; row++){
    for(int col = 0; col < floor->height; col++){
      //If space is empty, check surrounding spots
      if(floor->map[row][col] == 0){
        if(countNeighbors(floor, row, col) >= adjacentRooms){
          floor->map[row][col] = 1;
        }
      }
    }
  }
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
  free(floor);
}

void clipTopFloors(Building* building){
  for(int i = building->height - 1; i >= 0; i--){
    int room = 0;
    for(int row = 0; row < building->floors[i]->width; row++){
      for(int col = 0; col < building->floors[i]->height; col++){
        if(building->floors[i]->map[row][col] != 0){
          room += 1;
          //To break the nested for loops
          row = 1000;
          col = 1000;
        }
      }
    }
    if(room == 0){
      freeFloor(building->floors[i]);
      building->height -= 1;
    }
  }
}

Building* generateBuilding(int width, int height, int levels){
  Floor** floors = malloc(sizeof(Floor*) * levels);
  floors[0] = generateBase(width, height);
  fillFloor(floors[0], 4);
  clipFloor(floors[0], 0);
  for(int i = 1; i < levels; i++){
    floors[i] = generateFloorFromFloor(floors[i-1]);
    fillFloor(floors[i], 4);
    clipFloor(floors[i], 0);
  } 

  Building* building = malloc(sizeof(Building));
  building->height = levels;
  building->floors = floors;

  clipTopFloors(building);

  return building;
}

void addStairs(Building* building){

}

//A more advanced version of the old print building, prints the whole building
//left to right, like so
//  0 0 1  0 0 0  0 0 0 
//  0 1 1  0 1 1  0 1 0
//  1 1 0  0 1 0  0 0 0
void printBuilding(Building* building){
  for(int x = 0; x < building->floors[0]->height; x++){
    for(int i = 0; i < building->height; i++){
      for(int j = 0; j < building->floors[0]->width; j++){
        printf("%d ", building->floors[i]->map[j][x]);
      }
      printf("  ");
    }
    printf("\n");
  }
  printf("\n");
}

void freeBuilding(Building* building){
  for(int i = 0; i < building->height; i++){
    freeFloor(building->floors[i]);
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

  Building* building2 = generateBuilding(width, height, levels);

  printBuilding(building2);

  freeBuilding(building2);

  return 0;
}
