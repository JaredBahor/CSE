//
// Created by jared on 7/7/2021.
//

#include "avl.h"
#include <iostream>
#include <queue>

using namespace std;

void AVL::rotateLeft(Node *& node) {
    Node *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    node = tmp;
    return;
}

void AVL::rotateRight(Node *& node) {
    Node *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    node = tmp;
    return;
}

void AVL::rotateLeftRight(Node *& node) {
    rotateLeft(node->left);
    rotateRight(node);
    return;
}

void AVL::rotateRightLeft(Node *& node) {
    rotateRight(node->right);
    rotateLeft(node);
    return;
}

int getHeight(Node *root) {
    if (root == nullptr) {
        return -1;
    } else {
        int hLeft = getHeight(root->left);
        int hRight = getHeight(root->right);
        return std::max(hLeft, hRight) + 1;
    }
}
//newly made functions




Node* insert2(Node* node, const int &v){

    int bal;
    if (node == nullptr){// if tree is empty
        Node* node1 = new Node(v);
        return node1;
    }
    if (v > node->val){
        node->right = insert2(node->right, v);
    }else if (v < node->val){
        node->left = insert2(node->left, v);
    }else{
        return node;
    }

    node->height = getHeight(node);

    bal = getHeight(node->left) - getHeight(node->right);// add if statement to check if node is null

    //rotate cases
    if (1 < bal && v < node->left->val){//rotate right
        AVL::rotateRight(node);
    }
    if (bal < -1 && v > node->right->val){//rotate left
        AVL::rotateLeft(node);
    }
    if (bal > 1 && v > node->left->val){//rotate left -> right
        AVL::rotateLeftRight(node);
    }
    if (bal < -1 && node->right->val > v){//rotate right -> left
        AVL::rotateRightLeft(node);
    }
    return node;
}



void AVL::insert(const int &v) {
    // your code
    // <50 lines of code should be OK

    root = insert2(root, v);
    //correctly insert a num but will not balance

}





int computeHeight(Node *root){
    if (root == nullptr){
        return -1;
    }else{
        int hLeft = computeHeight(root->left);
        int hRight = computeHeight(root->right);
        return std::max(hLeft, hRight) + 1;
    }
}


void printBT(const string& prefix, const Node* node, bool isLeft)
{
    if( node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "├──" : "└──" );

        int balance = computeHeight(node->left) - computeHeight(node->right);
        // print the value of the node
        cout << " " << node->val << "," << node->height << "," << balance << endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void printBT(const Node* node)
{
    printBT("", node, false);
}

