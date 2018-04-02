typedef struct struct_Floor{
  int width;
  int height;
  int** map;
} Floor;

typedef struct struct_Building{
  Floor** floors;
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
