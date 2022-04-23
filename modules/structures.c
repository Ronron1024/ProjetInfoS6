#include <stdio.h>
#include "../includes/structures.h"
#include "../includes/prototypes.h"

void printEntity(const void* data)
{
	if (!data)
		return;

	Entity entity = *(Entity*) data;

	printf("\nName : %s\n", entity.name);
	printf("Weapon :\n");
	printItem(&entity.weapon);
	printf("Armor :\n");
	printItem(&entity.armor);
	printf("Health : %.2lf\n", entity.health);
	printf("Attack : %.2lf\n", entity.attack);
	printf("Defense : %.2lf\n", entity.defense);
	printf("Speed : %.2lf\n", entity.speed);
}

Entity* getEntity(Node* liste)
{
	if (!liste)
		return NULL;
	return (Entity*) liste->data;

}

Entity getEntityComputedStats(Entity entity)
{
	entity.attack += entity.weapon.attack;
	entity.defense += entity.armor.defense;
	return entity;
}

bool isDead(Entity entity)
{
	return entity.health <= 0;
}

void printItem(const void* data)
{
	if (!data)
		return;

	Item item = *(Item*) data;

	printf("\tName : %s\n", item.name);
	printf("\tDescription : %s\n", item.description);
	printf("\tPrice : %.2f\n", item.price);
	printf("\tHealth : %.2lf\n", item.health);
	printf("\tAttack : %.2lf\n", item.attack);
	printf("\tDefense : %.2lf\n", item.defense);
	printf("\tSpeed : %.2lf\n", item.speed);
}

Item* getItem(Node* liste)
{
	if (!liste)
		return NULL;
	return (Item*) liste->data;

}