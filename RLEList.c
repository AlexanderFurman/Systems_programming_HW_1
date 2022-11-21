#include "RLEList.h"
#include <stdlib.h>
#include <assert.h>

#define RLE_LIST_NULL -1
#define NULL_CHAR 0

typedef struct RLENode_t {
    char letter;
    int repetitions;
    RLENode_t* next;
} *RLENode;

struct RLEList_t{
    //TODO: implement
    RLENode first;
    RLENode last;
    //int size
    //numLetters
};

/***
 * typedef enum {
    RLE_LIST_SUCCESS,
    RLE_LIST_OUT_OF_MEMORY,
    RLE_LIST_NULL_ARGUMENT,
    RLE_LIST_INDEX_OUT_OF_BOUNDS,
    RLE_LIST_ERROR
} RLEListResult;
 */


/*** Function Implement ***/
//implement the functions here

RLEList RLEListCreate()
{
    RLEList linkedList = malloc(sizeof(*linkedList)); ///added * in malloc
    if (!linkedList) {
        return NULL;
    }
    linkedList->first = malloc(sizeof(*first));
    if (!linkedList->first) {
        free(linkedList);
        return NULL;
    }
    linkedList->first->next = NULL;
    linkedList->first->repetitions = 0;
    linkedList->first->letter= NULL_CHAR ;
    linkedList->last = linkedList->first;
}

void RLEListDestroy(RLEList list)
{
    if (!list){
        return;
    }
    RLENode toDelete = NULL;
    while (list->first->next)
    {
        assert(RLEListSize(list)>=0);
        toDelete=list->first->next;
        list->first->next = toDelete->next;
        free(toDelete);
    }
    free(list->first);
    free(list);
}

RLEListResult RLEListAppend(RLEList list, char value)
{
    if(list == NULL) {
        return RLE_LIST_NULL_ARGUMENT;
    }

    if(RLEListSize(list)==0 || list->last->letter != value )
    {
        list->last->next = malloc(sizeof(*RLENode));
        if (!list->last->next){
            return RLE_LIST_OUT_OF_MEMORY;
        }

        list->last = list->last->next;
        list->last->letter = value;
        list->last->repetitions = 1;
    }
    else { //(list->last->letter == value)
        list->last->repetitions++;
    }
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    if (!list) {
        return RLE_LIST_NULL;
    }
    int counter = 0;
    RLENode temp = list->first;
    while (temp->next)
    {
        counter += temp->next->repetitions;
        temp = temp->next;
    }
    //counter+=list->last->repetitions;
    return counter;
}

RLEListResult RLEListRemove(RLEList list, int index){
    if (!list) {
        return RLE_LIST_NULL;
    }
    if(RLEListSize(list)!=0) {
        int current_idx = -1;
        // Find the node for removal:
        RLENode node;
        RLENode prev_node = list->first;
//        if(index == 0){
//            if(node->repetitions > 0){
//                node->repetitions--
//            }
//            else{
//
//            }
//        }
        while (current_idx != index) {
            current_idx++
            node = prev_node->next
            helper_count = 0
            while(helper_count<node->repetitions){

            }



        }
    }

}


///https://piazza.com/class/l8vdfbb5pf86qf/post/116
// typedef char (*MapFunction)(char);
RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (!list || !map_function){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLENode temp = list->first;
    while (temp)
    {
        temp->letter = map_function(temp->letter);
        temp=temp->next;
    }
    return RLE_LIST_SUCCESS;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (!result) {
        return NULL;
    }
    if (!list) {
        *result=RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }

    //return

}





