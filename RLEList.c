#include "RLEList.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define RLE_LIST_NULL -1
#define NULL_CHAR '\0'
#define EXPORT_TO_STRING_ROW_SIZE 3
#define LINE_FINISH '\n'
//#define EXPORT_TO_STRING_LETTER_ID 0
//#define EXPORT_TO_STRING_REPETITIONS_ID 1
//#define EXPORT_TO_STRING_LINE_ID 2


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

static int listLengthNodes (RLEList list)
{
    assert(list);
    int counter = 0;
    RLENode temp = list->first;
    while (temp->next)
    {
        counter++;
        temp = temp->next;
    }
    return counter;
}

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


///https://piazza.com/class/l8vdfbb5pf86qf/post/116
// typedef char (*MapFunction)(char);
RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if (!list || !map_function){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLENode temp = list->first;
    while (temp->next)
    {
        temp->next->letter = map_function(temp->next->letter);
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
    // size of new string: 3 letters in row (including \n), times num of rows, +1 for null terminated string
    char* outString = malloc(listLengthNodes(list)*EXPORT_TO_STRING_ROW_SIZE*sizeof(char) + 1);
    if (!outString) {
        *result=RLE_LIST_OUT_OF_MEMORY;
        return NULL;
    }
    char* tempStringPtr = outString;
    RLENode temp = list->first;
    while (temp->next)
    {
        char currentRow[EXPORT_TO_STRING_ROW_SIZE+1] = {temp->next->letter,temp->next->repetitions,
                                                        LINE_FINISH, NULL_CHAR};
        strcpy(tempStringPtr,currentRow);
        temp=temp->next;
        tempStringPtr+=EXPORT_TO_STRING_ROW_SIZE;
    }
    return outString;
    //return
}

RLEListResult RLEListRemove(RLEList list, int index){

    RLEListResult result;
    RLENode prevNode = RLEListGetNodeFromIndex(list, index, &result);
    if (prevNode == NULL){
        return result;
    }

    RLENode node = prevNode->next;

    /// for debug - we should desired node by here:

    // Deal with case where repetitions > 1 (simple case)
    if(node->repetitions > 1){
        node->repetitions--;
        return RLE_LIST_SUCCESS;
    }
        // Deal with case where repetitions == 1
    else{
        // Deal with last node remove:
        if(node->next == NULL) {
            prevNode->next = NULL;
            list->last=prevNode;
        }
        // Deal with first node remove (after dummy):
//        else if()
//        {
//            prevNode->next = node->next;
//        }
            // Deal with the case where the previous node and next node have different letters:
        else if(list->first == prevNode || prevNode->letter != node->next->letter) { ///united above condition
            prevNode->next = node->next;
        }
            // Deal with case where the previous node and next node have SAME letter:
        else{
            prevNode->repetitions += node->next->repetitions;
            prevNode->next = node->next->next;
            if(list->last==node->next) {
                list->last = prevNode;
            }
            free(node->next);
        }
        free(node);
        return RLE_LIST_SUCCESS;
    }
    // return RLE_LIST_ERROR;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    RLENode prevNode = RLEListGetNodeFromIndex(list, index, result);
    if (prevNode == NULL){
        return 0;
    }
    else{
        return prevNode->next->letter;
    }
    
    // if (!list) {
    //     return RLE_LIST_NULL_ARGUMENT;
    // }
    // if(index < 0 || index + 1 > RLEListSize(list)) { // CHECK THIS +1 is correct??
    //     return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    // }

    // RLENode node = list->first->next;
    // int indicesRemaining = index;

    // while(indicesRemaining >= node->repetitions){
    //     indicesRemaining -= node->repetitions;
    //     node = node->next;
    // }

    // *result = RLE_LIST_SUCCESS;
    // return node->letter;
}

RLENode RLEListGetNodeFromIndex(RLEList list, int index, RLEListResult *result){
    if (!list) {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    if(index < 0 || index + 1 > RLEListSize(list)) { /// +1 should be correct
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return NULL;
    }
    // int current_idx = 0;
    RLENode prevNode = list->first;
    RLENode node = prevNode->next;
    int indicesRemaining = index;

    // First move to the correct node, and previous node
    while(indicesRemaining >= node->repetitions){
        indicesRemaining -= node->repetitions;
        prevNode = node;
        node = prevNode->next;
    }
    *result = RLE_LIST_SUCCESS;
    return prevNode;
}




