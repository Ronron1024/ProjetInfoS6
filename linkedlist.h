#ifndef INCLUDED_LINKEDLIST_H
#define INCLUDED_LINKEDLIST_H

#include "structure.h"

void push(Node** head, const void* data, const size_t data_size);

void printList(Node* head, void (*fptr)(const void*));
void debugList(Node* head);
void printEntity(const void* data);
void printItem(const void* data);

Entity* getEntity(Node* liste);
Item* getItem(Node* liste);

//OB
void sup(Node** head, Node* objet);



#endif
