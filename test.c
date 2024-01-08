#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



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

CellNode* makeCN(int r, int c);

int main()
{
  CellNode *top=NULL;
    Cell c;
    c.row=10;
    c.column=6;
    CellNode cNode={c, NULL};

    top = &cNode;

    printf("%d, ", top->cell.column);

    top->cell.column=2;
    printf("%d, ", top->cell.column);

    Cell d={20, 90};
    CellNode cNode2={d, top};
    top=&cNode2;
    printf("top c: %d, ", top->cell.column);
    //printf("%p   %p\n", );
    CellNode e={{300,400}, NULL};
    printf("e Col: %d\n",e.cell.column);
    printf("top->next row: %d, ", top->next->cell.row);
    //printf("%p, %p\n", &cNode, top);
    //if(NULL==top->next->next){
    //printf("%p", top->next->next);
   
    //}
    
    CellNode *garb=makeCN(1000, 2000);
    printf("new r: %d\n",garb->cell.row);
    char input[20];
    fgets(input, (20), stdin);
    char *token=strtok(input," ");
    printf("%s, %d\n", token, atoi(token));
    token=strtok(NULL, " ");
    printf("%s, %d\n", token, atoi(token));
    


    char poop[45];
    assert(NULL!=poop);
    /*
    char input[60];
    while(fgets(input, (60)-1, stdin)!= NULL)
    {
        char *token=strtok(input, " ");
        while(token!=NULL)
        {
            printf("%d/n")
            printf("%s\n",token);

            token=strtok(NULL, " ");
        }
    printf("\n");
    }
    

   char a='m';
   char b=1;
   char *c="m";
   int d=a;
   int e=c[0];
   printf("a:%c:, b:%c:, c:%d:, d:%d:, e:%d:\n", a, b, c[0], d, e);
   printf("%d\n", a==c[0]);
   if(a==c[0]){printf("kejrv\n");}
    */

}
CellNode *makeCN(int r, int c)
    {
      CellNode *new= malloc(sizeof(CellNode));
      new->cell.row=r;
      new->cell.column=c;
      new->next=NULL;
      return new;
    }