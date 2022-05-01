#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/prototypes.h"

void push(Node** head, const void* data, const size_t data_size)
{
	if (!head || !data)
		return;

	Node* new_node = (Node*) malloc(sizeof(Node));

	new_node->data = malloc(data_size);
	new_node->next = *head;
	new_node->prev = NULL;
	if (*head)
		(*head)->prev = new_node;
	memcpy(new_node->data, data, data_size);

	*head = new_node;
}

void printList(Node* head, void (*fptr)(const void*))
{
	if (!head || !fptr)
		return;

	fptr(head->data);
	printList(head->next, fptr);
}

void debugList(Node* head)
{
	if (!head)
		return;
	
	printf("\n@ %p\n", head);
	printf("\tnext is @ %p\n", head->next);
	printf("\tprev is @ %p\n", head->prev);

	debugList(head->next);
}

void saveList(Node* head, FILE* save_file, void (*fptr)(const void*, FILE*))
{
	if (!head || !fptr)
		return;

	fptr(head->data, save_file);
	saveList(head->next, save_file, fptr);
}

int count(Node* list)
{
	int n = 0;
	if (!list)
		return 0;

	while (list)
	{
		n++;
		list = list->next;
	}

	return n;
}

Node* getRandomNode(Node* list)
{
	if (!list)
		return NULL;

	int random_index = randInt(0, count(list));
	for (int i = 0; i < random_index - 1; i++)
		list = list->next;

	return list;
}

// Ronron Patapon
// Can be optimized ?
void delete(Node** list, Node* node)
{
	if (!list || !node)
		return;

	// Delete only node
	if (!node->next && !node->prev)
	{
		*list = NULL;
		free(node);
		return;
	}

	// Delete first node
	if (!node->prev)
	{
		*list = node->next;
		node->next->prev = NULL;
		free(node);
		return;
	}

	// Delete last node
	if (!node->next)
	{
		node->prev->next = NULL;
		free(node);
		return;
	}

	// Delete intermediate node
	node->next->prev = node->prev;
	node->prev->next = node->next;
	free(node);
}

void sup(Node** head, Node* objet)
{
	if (!head || !objet)
		return;

	Node* current = *head;
	Node* prev = NULL;
	
	while (current != NULL){
	
		if( strcmp(getItem(objet)->name, getItem(current)->name) == 0){

			if(prev == NULL){
			
				*head = current->next;				
				current->prev = NULL;	
				return;
			}
			
			else{	
				
				if(current->next == NULL) {
					prev->next =NULL;
				}
				else{
					prev->next=current->next;
					current=current->next;
					current->prev = prev;	
					return;
				}		
			}			
		}
		
	prev = current;
	current=current->next;
		
	}
	
	return;
			
}

/*
void sup(Node** head, Node* objet){

	if (!head || !objet)
		return;

	Node* current = objet;
	Node* prev = NULL;

	//Element à sup en debut de liste
	if(current->prev == NULL){
			
		*head = current->next;				
		return;
	}
	
	//Element à sup en fin de liste		
	if( current->next == NULL) {
	
		prev = current->prev;
		prev->next = NULL;
		return;
	}
	
	//Element à sup en milieu de liste
	else{

		prev = current->prev;
		prev->next = current->next;
		current->prev = prev;
	}		
						
	return;			
}
*/
