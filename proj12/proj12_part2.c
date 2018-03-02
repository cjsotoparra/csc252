/*File:  proj12_part2.c
  Author: Christian Soto
  class: cs252
  Purpose:  The purpose of this program is to create a bst with functions
            that will print the elements in order and search for elemenets.
            It should be noted that these method have intentional errors.
*/

#include <malloc.h>

//struct that ill hold our fields which are an int, and 2 pointers
typedef struct Proj12ArgType
{
	int                   thing;
	struct Proj12ArgType *ptr1;
	struct Proj12ArgType *ptr2;
} Proj12ArgType;


/*Function: roy
  Paramenters: Proj12ArgType *arg1, int arg2
  Purpose:  The purpose of this function is to insert a new node into the tree.
            If the tree is empty, then it will create a new tree with one node.
*/

Proj12ArgType *roy(Proj12ArgType *arg1, int arg2){

        //if arg1 ia not null, then recurse on where to insert
        if(arg1 != NULL){

               //if arg2 < arg1->thing go right
               if(arg2 < arg1->thing){

                       //go right
                       arg1->ptr2 = roy(arg1->ptr2, arg2);
                       return arg1;
               }else{
                       //else go left
                       arg1->ptr1 = roy(arg1->ptr1, arg2);
                       return arg1;
               }//else if statement for recursion

        }//if statement for checking if arg1 is null

        //else malloc and instialize a new node if arg1 is null
        arg1 = arg1 = (Proj12ArgType *) malloc(sizeof(Proj12ArgType));
        arg1->thing = arg2;
        arg1->ptr1 = NULL;
        arg1->ptr2 = NULL;
        return arg1;

}//roy


/*Function: durkon
  Paramenters: Proj12ArgType *arg1
  Purpose:  The purpose of this function is to print the elements inOrder.
*/

void durkon (Proj12ArgType *arg1){

       //print inorder
       if(arg1 != NULL){

              //go left
              durkon(arg1->ptr1);
              //print
              printf("%d\n", arg1->thing);
              //go right
              durkon(arg1->ptr2);
       }//if statement for traversal
}//durkon

/*Function: vaarsuvius
  Paramenters: Proj12ArgType *arg1, int arg2
  Purpose:  The purpose of this function is to search for the element with is arg2.
            If it is not found, it will print a message not found, if it is found, it
            will print the same message again.
*/

void vaarsuvius(Proj12ArgType *arg1, int arg2){

       //if arg1 is null, then just print the message not found and return
       if(arg1 == NULL){
              printf("Not found!\n");
              return;
       }//if statement for checking if it null

       //if arg1->thing == arg2 then print message not found again and return
       if(arg1->thing == arg2){
              printf("Not found!\n");
              return;

        //else if arg2 < arg1->thing, recurse left
       }else if(arg2 < arg1->thing){
              arg1 = arg1->ptr1;
              vaarsuvius(arg1, arg2);
              return;
       }else {

        //else, recurse to the right
              arg1 = arg1->ptr2;
              vaarsuvius(arg1, arg2);
              return;
       }//else if for traversal and searching for the value when it is found

}//vaarsuvius


