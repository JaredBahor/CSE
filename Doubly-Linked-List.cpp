//
// Created by jared on 6/15/2021.
//

#include <iostream>

#include "List.h"

using std::cout;
using std::endl;


namespace ds {
    Node::Node(int v){
        val = v;
        //next = nullptr;
        //prev = nullptr;
    }

    Node::Node() {
        val = 0;
        Node* next = nullptr;
        Node* prev = nullptr;
    }

    DoublyLinkedList::DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    DoublyLinkedList::DoublyLinkedList(int arr[], int size)  {
        // Your code
        if (size == 0){//empty list
            head = nullptr;
            tail = nullptr;
            length = 0;
            return;
        }
        //first node creation
        head = new Node(arr[0]);// first node in arr is the head and tail
        head->next = nullptr;
        head->prev = nullptr;
        tail = head;
        length = size;

        for (int elem = 1; elem < size; elem++){
            int value = arr[elem];
            Node* node = new Node(value);
            node->next = nullptr;
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
    }



    //insert to empty list
    //invalid insert idx, does nothing
    void DoublyLinkedList::Insert(int idx, int v) {
        // Your code
        Node* actual = head;
        Node* node = new Node();
        if (idx >= 0 && idx <= length) {
            if (length == 0){//inserting into empty list
                node->prev = nullptr;
                node->next = nullptr;
                node->val = v;
                head = node;
                tail = node;
                length += 1;
                return;
            }
            if (length == idx) {//inserting at the end of list (next == NULL) should be set to tail
                node->prev = tail;
                node->next = nullptr;
                node->val = v;
                tail->next = node;
                tail = node;
                length += 1;
                return;
            } else if (idx == 0) {//inserting at beginning of list (prev == NULL) should be set to head
                node->next = head;
                node->prev = nullptr;
                node->val = v;
                head->prev = node;
                head = node;
                length += 1;
                return;
            } else {//inserting in the middle somewhere
                int i = 0;
                while (i != idx){
                    actual = actual->next;
                    i += 1;
                }
                node->next = actual;
                node->prev = actual->prev;
                actual->prev->next = node;
                node->val = v;
                actual->prev = node;
                length += 1;
                return;
                i++;

            }
        }
        //length += 1;
    }

    void DoublyLinkedList::Remove(int idx) {
        // Your code
        Node* node = head;
        Node* tails = tail;
        if (idx >= 0 && idx <= length - 1){
            for (int i = 0; i < length; i++){
                if (idx == 0){//remove head  /  check length
                    if (length > 1){
                        Node* newnode = node->next;
                        newnode->prev = nullptr;
                        head = newnode;
                        length -= 1;
                        return;
                    }else {
                        head = nullptr;
                        tail = nullptr;
                        length -= 1;
                        return;
                    }
                }else if (idx == length - 1){// remove tail  /  check length
                    Node* newnode = tails->prev;
                    //newnode->val = tails->prev->val;
                    newnode->next = nullptr;
                    tail = newnode;
                    length -= 1;
                    return;
                }else if (i == idx){//middle removal
                    Node* nextnode = node->next;
                    Node* prevnode = node->prev;
                    prevnode->next = nextnode;
                    nextnode->prev = prevnode;
                    length -= 1;
                    return;
                }
                node = node->next;
            }
        }
        //length -= 1;
        //return;
    }



    int DoublyLinkedList::Get(int idx) {
        // Your code
        Node* node = head;
        if (idx >= 0 && idx <= length){
            for (int i = 0; i < length; i++){
                if (i == idx){// we found the idx
                    return node->val;
                }
                node = node->next;
            }
            return -1;
        }else{
            return -1;
        }
    }

    int DoublyLinkedList::Search(int v) {
        // Your code
        Node* node = head;
        for (int i = 0; i < length; i++){
            if (node->val == v){//found a match
                return i;
            }
            node = node->next;
        }
        return -1;
    }

    void DoublyLinkedList::ReverseList() {
        // Your code
        Node* reversed = new Node();
        Node* node = tail;
        int count = 0;
        while (node->prev != nullptr){// start at tail and work backwards to the head
            if (count == 0){// node is head on first run
                reversed->val = node->val;
                reversed->next = nullptr;
                reversed->prev = nullptr;
                tail = reversed;
                head = reversed;
            }else{
                Node* node1 = new Node();
                node1->val = node->val;
                node1->next = nullptr;
                node1->prev = tail;
                tail->next = node1;
                tail = node1;
            }
            node = node->prev;
            count++;
        }
        Node* node1 = new Node();
        node1->val = node->val;
        node1->next = nullptr;
        node1->prev = tail;
        tail->next = node1;
        tail = node1;
        length = count + 1;
    }


    /*
     *
     * Node* reversed = new Node();
        Node* node = tail;
        int count = 0;
        while (node->prev != nullptr){// start at tail and work backwards to the head
            if (count == 0){// node is head on first run
                reversed->val = node->val;
                reversed->next = nullptr;
                reversed->prev = nullptr;
                tail = reversed;
                head = reversed;
            }else{
                Node* node1 = new Node();
                node1->val = node->val;
                node1->next = nullptr;
                node1->prev = tail;
                tail->next = node1;
                tail = node1;
            }
            node = node->prev;
            count++;
        }
        Node* node1 = new Node();
        node1->val = node->val;
        node1->next = nullptr;
        node1->prev = tail;
        tail->next = node1;
        tail = node1;
        length = count + 1;
     */

    void DoublyLinkedList::PrintList() {
        // Your code
        if (head != nullptr){// always print the head first
            std::cout << head->val;
        }
        Node* node = head->next;
        for (int i = 1; i < length; i++){
            std::cout << " ";
            std::cout << node->val;
            node = node->next;
        }
    }

    void DoublyLinkedList::MergeList(DoublyLinkedList *list)  {
        // Your code
        Node* node = list->head;
        while (node != nullptr){
            tail->next = node;// the new node is after the tail node
            node->prev = tail;// the new nodes prev is the old tail
            tail = node;// set new tail
            node = node->next;//update the current node to the next node
            //length += 1;//update length for newly added node
        }
        length += list->length;
    }
}
