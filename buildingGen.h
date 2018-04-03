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
void clipFloor(Floor*, int);
void fillFloor(Floor*, int);
void printFloor(Floor*);
void freeFloor(Floor*);
int countNeighbors(Floor*, int, int);

Building* generateBuilding(int, int, int);
void addStairs(Building*);
void printBuilding(Building*);
void freeBuilding(Building*);
void clipTopFloors(Building*);
void addStairs(Building*);
