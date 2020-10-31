#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/* #include "llqueue.h" */
/* #include "bst.h" */

struct bst {
    struct bst *left;
    struct bst *right;
    struct bst *parent;
    int depth;
    int counter;
    int data;
};

void rightRotate(struct bst *grandparent, struct bst *parent);

void leftRotate(struct bst *grandparent, struct bst *parent);

/* 
    The function you are to write. Takes a parent pointer (null for the root),
    and returns the tree with the child in the right position. Returns the
    item in a new tree with null left/right pointers.
*/
struct bst *bstInsert(struct bst *parent, int data){
    /* Write this function. */
    struct bst **insertLocation = &parent;
    struct bst *currentParent = NULL;
    
    int ldepth;
    int rdepth;
    
    while(*insertLocation){
        if(data < (*insertLocation)->data){
            currentParent = *insertLocation;
            insertLocation = &((*insertLocation)->left);
        } else {
            currentParent = *insertLocation;
            insertLocation = &((*insertLocation)->right);
        }
    }
    
    *insertLocation = (struct bst *) malloc(sizeof(struct bst));
    assert(*insertLocation);
    
    (*insertLocation)->left = NULL;
    (*insertLocation)->right = NULL;
    (*insertLocation)->parent = currentParent;
    (*insertLocation)->data = data;
    (*insertLocation)->depth = 0;
    (*insertLocation)->counter = 0;
    
    while(currentParent){
        if(! currentParent->left){
            ldepth = -1;
        } else {
            ldepth = currentParent->left->depth;
            if(ldepth >= currentParent->depth){
                currentParent->depth = ldepth + 1;
            }
        }
        if(! currentParent->right){
            rdepth = -1;
        } else {
            rdepth = currentParent->right->depth;
            if(rdepth >= currentParent->depth){
                currentParent->depth = rdepth + 1;
            }
        }
        
        currentParent->counter = ldepth - rdepth;
        
        if(currentParent->counter < -1){
            /* Right leaning */
            if(currentParent->right->counter > 0){
                rightRotate(currentParent->right, 
                            currentParent->right->left);
            }
            leftRotate(currentParent, currentParent->right);
        } else if(currentParent->counter > 1) {
            /* Left Leaning */
            if(currentParent->left->counter < 0){
                leftRotate(currentParent->left, 
                           currentParent->left->right);
            }
            rightRotate(currentParent, currentParent->left);
        }
        
        currentParent = currentParent->parent;
    }
    
    return parent;
}

void leftRotate(struct bst *grandparent, struct bst *parent){
    struct bst *child = parent->left;
    parent->parent = grandparent->parent;
    if(grandparent->parent){
        if(grandparent->parent->left == grandparent){
            grandparent->parent->left = parent;
        } else {
            grandparent->parent->right = parent;
        }
    }
    parent->left = grandparent;
    grandparent->parent = parent;
    grandparent->right = child;
    if(child){
        child->parent = grandparent;
    }
    grandparent->depth -= 2;
}

void rightRotate(struct bst *grandparent, struct bst *parent){
    struct bst *child = parent->right;
    parent->parent = grandparent->parent;
    if(grandparent->parent){
        if(grandparent->parent->left == grandparent){
            grandparent->parent->left = parent;
        } else {
            grandparent->parent->right = parent;
        }
    }
    parent->right = grandparent;
    grandparent->parent = parent;
    grandparent->left = child;
    if(child){
        child->parent = grandparent;
    }
    grandparent->depth -= 2;
}

void freeTree(struct bst *parent){
    if(! parent){
        return;
    }
    /* Fill in function according to function description. */
    freeTree(parent->left);
    freeTree(parent->right);
    free(parent);
}

/* Calculate the number of spaces which need to appear before and after the 
    data point at a given depth to allow a single character to occur in all 
    children below it. */
int spacesAtDepth(int depth);

/* Calculate the depth to the deepest child of a given node. */
int countDepth(struct bst *parent);

/* Draws the tree. You will need to change this if your bst uses different names. */
/* You needn't understand how this works, but you're welcome to try. */
void drawTree(struct bst *parent){
    int i;
    if(!parent){
        /* Done, no tree to print. */
        return;
    }
    
    struct llqueue *currentQueue = newQueue();
    struct llqueue *nextQueue = newQueue();
    /* Used for swapping. */
    struct llqueue *tempQueue;
    /* Current node being processed */
    struct bst *current;
    
    /* The depth of the parent, used to work out where to place the value. */
    int depth = countDepth(parent);

    /* The number of spaces needed at the current level before and after each
        data value. */
    int spaces = spacesAtDepth(depth);

    
    /* Add the parent node to the queue. */
    queue(&currentQueue, parent);
    
    while(!empty(currentQueue) && depth >= 0){
        current = (struct bst *) dequeue(currentQueue);
        for(i = 0; i < spaces; i++){
            printf("  ");
        }
        if(current){
            printf("%2d",current->data);
        } else {
            printf("  ");
        }
        for(i = 0; i < spaces; i++){
            printf("  ");
        }
        /* Account for parent's space */
        printf("  ");

        /* Queue any children for next row */
        if(current && current->left){
            queue(&nextQueue, current->left);
        } else {
            /* Mark empty space so spacing stays consistent. */
            queue(&nextQueue, NULL);
        }

        if(current && current->right){
            queue(&nextQueue, current->right);
        } else {
            /* Mark empty space so spacing stays consistent. */
            queue(&nextQueue, NULL);
        }
        
        if(empty(currentQueue)){
            /* Start new row. */
            printf("\n");
            /* Update depth information. */
            depth--;
            spaces = spacesAtDepth(depth);
            
            /* Swap the new row to the current row. */
            tempQueue = currentQueue;
            currentQueue = nextQueue;
            nextQueue = tempQueue;
        }
    }
    /* If we reach depth 0, the queue may still have contents
        we must empty first. */
    while(!empty(currentQueue)){
        current = (struct bst *) dequeue(currentQueue);
    }
    if(tempQueue){
        free(nextQueue);
    }
    if(currentQueue){
        free(currentQueue);
    }
}

int countDepth(struct bst *parent){
    int leftDepth;
    int rightDepth;
    if(!parent){
        /* Here we assume a leaf node is at depth -1, other choices are possible. */
        return -1;
    }
    leftDepth = countDepth(parent->left);
    rightDepth = countDepth(parent->right);
    if(leftDepth > rightDepth){
        return leftDepth + 1;
    } else {
        return rightDepth + 1;
    }
}

int spacesAtDepth(int depth){
    int cDepth = depth;
    int result = 1;
    while(cDepth > 0){
        result = 2*result + 1;
        cDepth--;
    }
    return result;
}
