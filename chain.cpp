#include "chain.h"
#include <cmath>
#include <iostream>


// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  clear();
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node * p, const Block &ndata) {
  Node* pp = new Node(ndata);
  if (p == NULL) { 
    if (head_ == NULL) {
    head_ = pp;
    } 
    else {
      pp ->next = head_;
      head_->prev = pp;
      head_ = pp;
    }
    length_++;
    return pp;
  }


  Node* cur = head_;
  while (cur != NULL) {
    if (cur == p) {
      if (cur->next != NULL) {
        cur->next->prev = pp;
        pp->next = cur->next;
        }
      pp->prev = cur;
      cur->next = pp;
      length_++;
      return pp;
    }
  cur = cur ->next;
  }
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::swap(Node *p, Node *q) {
  if (p == q) return;
  if (p == NULL || q == NULL) return;
  if (p == head_) {
    head_ = q;
  }
  else if (q == head_) {
    head_ = p;
  }

    Node* pPrev = p->prev;
    Node* pNext = p->next;
    Node* qPrev = q->prev;
    Node* qNext = q->next;

    //p adjacent to q
    if (p->next == q) {
      if (p->prev != NULL) {
      p->prev->next = q;
      }
      if (q->next != NULL) {
      q->next->prev = p;
      }

      q->prev = pPrev;
      p->next = qNext;

      q->next = p;
      p->prev = q;
      return;
    }
    else  if (q->next == p) {
      if (q->prev != NULL) {
      q->prev->next = p;
      }
      if (p->next != NULL) {
      p->next->prev = q;
      }
  
      p->prev = qPrev;
      q->next = pNext;

      p->next = q;
      q->prev = p;
      return;
    }

    if (qPrev != NULL) {
      qPrev->next = p;
    }
    if (qNext != NULL) {
      qNext->prev = p;
    }
    if (pPrev != NULL) {
      pPrev->next = q;
    }
    if (pNext != NULL) {
      pNext->prev = q;
    }
    
    p->next = qNext;
    q->next = pNext;

    q->prev = pPrev;
    p->prev = qPrev;
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
  Node *nn = head_->next;

  for(Node *curr = head_; curr != NULL; curr = nn) {
    Node* nn = curr->next;
    delete(curr);
    nn = nn->next;
  }

  head_ = NULL;
  length_ = 0;
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other) {
  clear();
  if (other.head_ == NULL) {
    return;
  }

  Node* placeHolder = other.head_;
  Node* curr = insertAfter(NULL, placeHolder->data);
  head_ = curr;
  placeHolder = placeHolder->next;

  while (placeHolder != NULL) {
    insertAfter(curr, placeHolder->data);
    curr = curr->next;
    placeHolder = placeHolder->next;
  }
}

/* Modifies the current chain:
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::unscramble() {
  Node* index = head_;

  while (index != NULL) {

    Node *maxBlock = NULL;
    double max = -1;

    for (Node* findMin = index; findMin != NULL; findMin = findMin->next) {
      Node* minBlock = NULL;
      double min = 1000000; 
      for (Node* findMax = index; findMax != NULL; findMax = findMax->next) {
       if (findMax->data.distanceTo(findMin->data) < min) {
            min = findMax->data.distanceTo(findMin->data);
            minBlock = findMin;
          }
      }
      if (min > max) {
        max = min;
        maxBlock = minBlock;
      }
    }
    Node* saved = index->next;
      swap(maxBlock, index);
    index = saved;
  }
}
