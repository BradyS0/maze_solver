#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------

#define MAX_DIMENSION 20

// constant definitions for the different cell states
const char WALL    = '1';
const char SPACE   = '0';
const char VISITED = '.';
const char MOUSE   = 'm';
const char EXIT    = 'e';

typedef enum BOOL { false, true } Boolean;

struct CELL
{
  int row;
  int column;
};
typedef struct CELL Cell;

typedef struct CELL_NODE CellNode;
struct CELL_NODE
{
  Cell     cell;
  CellNode *next;
};

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------

CellNode *top = NULL;

// a 2D array used to store the maze
char maze[MAX_DIMENSION][MAX_DIMENSION];

int mazeRows;
int mazeCols;

// holds the location of the mouse and escape hatch
Cell mouse;
Cell escape;

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------

// basic cell manipulation

// returns true if the cells are at the same position in our maze
Boolean equalCells(const Cell cell1, const Cell cell2);
// returns a new cell object
Cell makeCell(const int newRow, const int newCol);
// returns true if the cell is within our maze
Boolean validCell(const Cell theCell);
//used to find mouse and escape
Cell findCell(char goal);
//makes a node
CellNode* makeNode(Cell c, CellNode *cNode);

void removeNode();
// routines for managing our backtracking

// returns true if there are no more cells to try
Boolean noMoreCells();
// returns the next cell to try for a path out of the maze
Cell nextCell();
// introduces a new cell to try
void addCell(const Cell cell);
//adds a node to Linkded list
void addNode(int r, int c);



//maze functions
void makeArray(char input[], char output[]);//takes the input and makes it into an array
void printMaze();
void loadMaze();
int findEscape();

int found(CellNode current);
// returns true if there's a solution to the maze
Boolean solveMaze();

// our invariant checker
void checkState();

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------

int main( int argc, char *argv[] )
{
    loadMaze();
    printMaze();

    mouse= findCell('m');
    printf("mouse: row:%d:, col:%d:\n",mouse.row, mouse.column);
    escape = findCell('e');
    printf("escape: row:%d:, col:%d:\n",escape.row, escape.column);
    
    if(findEscape())
    {
        printf("Found escape!\n");
    }else
    {
        printf("No escape was found\n");
    }
    
   /*
    if ( solveMaze() )
      printf( "The mouse is free!!!!\n" );
    else
      printf( "The mouse is trapped!!!!\n" );
    
    printf( "\nEnd of processing\n" );
    */

  return EXIT_SUCCESS;
}


//////////////////////////////////////////////
// Cell routines
//////////////////////////////////////////////
Cell makeCell(const int newRow, const int newCol)
{
    Cell newCell;
    newCell.row=newRow;
    newCell.column=newCol;

    return newCell;
}

CellNode* makeNode(Cell c, CellNode *cNode)
{
    
    CellNode *new=malloc(sizeof(CellNode));
    new->cell=c;
    new->next=cNode;
    return new;
}

void checkState(){
    assert(NULL!=top);
    assert(NULL!=maze);
}
//////////////////////////////////////////////
// List routines
//////////////////////////////////////////////


//////////////////////////////////////////////
// Maze routines
//////////////////////////////////////////////
void loadMaze()
{
    char lineArray[MAX_DIMENSION];
    char input[MAX_DIMENSION*3];
    if(fgets(input, (MAX_DIMENSION*3)-1, stdin)!= NULL)//for getting size
    {
        char *token=strtok(input," ");
        mazeRows=atoi(token);
        token=strtok(NULL, " ");
        mazeCols=atoi(token);

        //mazeRows=lineArray[0]-48;//ascii translation
        //mazeCols=lineArray[1]-48;
       
    }
    int i=0;
    while (fgets(input, (MAX_DIMENSION*3)-1, stdin)!= NULL)//for maze
    {
        makeArray(input, lineArray);
        for(int j=0; j<mazeCols;j++)
        {
            maze[i][j]=lineArray[j];
        }
        i++;
    }
}

void makeArray(char input[], char output[])
{
    char *token=strtok(input, " ");
    int counter=0;
    
        while(token!=NULL)
        {
            
            output[counter]=token[0];
            token=strtok(NULL, " ");
            counter++;
        }
        
}

void printMaze()
{
    //checkState();
    assert(NULL!=maze);
    for(int i=0;i<mazeRows;i++)
    {
        for(int j=0;j<mazeCols;j++)
        {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

Cell findCell(char goal)//to find mouse and escape
{
    Cell found;
    for(int i=0;i<mazeRows;i++)
    {
        for(int j=0;j<mazeCols;j++)
        {
            int c=maze[i][j];
            if(c==goal)
            {
                found=makeCell(i,j);
            }
        }
    }
    return found;
}

int findEscape()
{
    int noEscape=1;
    CellNode *start=makeNode(mouse, NULL);
    top=start;
    while(noEscape&&!found(*top))
    {
        //checkState();
        int cRow=top->cell.row;
        int cCol=top->cell.column;

        removeNode();
        printMaze();

        
        if(maze[cRow-1][cCol]==SPACE||maze[cRow-1][cCol]==EXIT)
        {

            addNode(cRow-1, cCol);
        }
        if(maze[cRow][cCol-1]==SPACE||maze[cRow][cCol-1]==EXIT)
        {
            addNode(cRow, cCol-1);
        }
        if(maze[cRow+1][cCol]==SPACE||maze[cRow+1][cCol]==EXIT)
        {
            addNode(cRow+1, cCol);
        }
        if(maze[cRow][cCol+1]==SPACE||maze[cRow][cCol+1]==EXIT)
        {
            addNode(cRow, cCol+1);
        }
        
        if(NULL==top)//mo more open paths
        {
            noEscape=0;
        }
    }
   return noEscape;
}

int found(CellNode current)
{  
    int found=0;
    if(current.cell.row==escape.row&&current.cell.column==escape.column)
    {
        found=1;
    }
    return found;
}

void addNode(int r, int c)
{

    if(top!=NULL)
    {
        CellNode *new = makeNode(makeCell(r, c), top);


        top=new;
    }else
    {
        CellNode *new = makeNode(makeCell(r, c), NULL);
        top=new;
    }
}

void removeNode()
{   checkState();
    
    maze[top->cell.row][top->cell.column]=VISITED;
    
    //free memory

    if(top==NULL){
        printf("Trying to remove node that does not exist");
    }else//works if theres 1 or more nodes
    {
         CellNode *ptr=top->next;
       
         free(top);
         top=ptr;
    }
    
}


