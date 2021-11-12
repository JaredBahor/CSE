#include <stdlib.h>

#include "list.h"

/* Counts and returns the number of nodes in the given list. */
int list_length(struct ListNode *list) {
    int length = 1;
    if (list == NULL && length == 1){// length be zero ??
        return 0;
    }
    while(list -> next != NULL){
        list = list -> next;
        length++;
    }
    return length;
}

/* Searches the given list for the first node containing the given
 * value.  If such a list element is found, it is removed from the list
 * and freed.
 *
 * Returns the resulting list after any adjustments are made. */
struct ListNode *list_remove(struct ListNode *list, long value) {
    if (list != NULL && list -> value == value){// if listis empty
        struct ListNode* templist = list -> next;
        free(list);
        return templist;
    }
    else if (list == NULL){
        return NULL;
    }
    else{
        struct ListNode* templist = list;
        while(templist -> next != NULL && templist -> next -> value != value){
            templist = templist -> next;
        }
        if(templist -> next == NULL){
            return list;
        }else{
            struct ListNode* ptrdelete = templist -> next;
            templist -> next = templist -> next -> next;
            free(ptrdelete);
        }
    }
    return list;
}
