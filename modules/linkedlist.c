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

void printEntity(const void* data)
{
	if (!data)
		return;

	Entity entity = *(Entity*) data;

	printf("\nName : %s\n", entity.name);
	printf("Health : %lf\n", entity.health);
	printf("Attack : %lf\n", entity.attack);
	printf("Defense : %lf\n", entity.defense);
	printf("Speed : %lf\n", entity.speed);
}

void printItem(const void* data)
{
	if (!data)
		return;

	Item item = *(Item*) data;

	printf("\nName : %s\n", item.name);
	printf("Description : %s\n", item.description);
	printf("Price : %f\n", item.price);
}

Entity* getEntity(Node* liste)
{
	if (!liste)
		return NULL;
	return (Entity*) liste->data;

}

Item* getItem(Node* liste)
{
	if (!liste){
		//printf("PAPAPAPAPA\n");
		return NULL;	
	}
		
	return (Item*) liste->data;

}

Plateau* getPlateau(Node* liste)
{
	if (!liste)
		return NULL;
	return (Plateau*) liste->data;

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
