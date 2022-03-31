#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ITEM_NAME_STRING_SIZE 16
#define ITEM_STRS ITEM_NAME_STRING_SIZE

#define ENTITY_NAME_STRING_SIZE 16
#define ENTITY_STRS ENTITY_NAME_STRING_SIZE

typedef struct
{
	char name[ENTITY_STRS];
	double health;
	double attack;
	double defense;
	double speed;
} Entity;

typedef struct
{
	char name[ITEM_STRS];
	int val;
} Item;

typedef struct Node
{
	void* data;
	struct Node* next;
} Node;

void push(Node** head, const void* data, const size_t data_size)
{
	if (!head || !data)
		return;

	Node* new_node = (Node*) malloc(sizeof(Node));

	new_node->data = malloc(data_size);
	new_node->next = *head;

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
	printf("Val : %d\n", item.val);
}

int main (int argc, char** argv)
{
	Node* entity_list = NULL;
	Node* item_list = NULL;

	Entity entity1;
	strcpy(entity1.name, "Entity 1");
	entity1.health = 1.1;
	entity1.attack = 1.2;
	entity1.defense = 1.2;
	entity1.speed = 1.4;

	Entity entity2;
	strcpy(entity2.name, "Entity 2");
	entity2.health = 2.1;
	entity2.attack = 2.2;
	entity2.defense = 2.2;
	entity2.speed = 2.4;

	Entity entity3;
	strcpy(entity3.name, "Entity 3");
	entity3.health = 3.1;
	entity3.attack = 3.2;
	entity3.defense = 3.2;
	entity3.speed = 3.4;

	Item item1;
	strcpy(item1.name, "Item 1");
	item1.val = 10;

	Item item2;
	strcpy(item2.name, "Item 2");
	item2.val = 20;

	Item item3;
	strcpy(item3.name, "Item 3");
	item3.val = 30;

	push(&entity_list, &entity1, sizeof(entity1));
	push(&entity_list, &entity2, sizeof(entity2));
	push(&entity_list, &entity3, sizeof(entity3));

	push(&item_list, &item1, sizeof(item1));
	push(&item_list, &item2, sizeof(item2));
	push(&item_list, &item3, sizeof(item3));

	printList(entity_list, printEntity);
	printList(item_list, printItem);

	return 0;
}
