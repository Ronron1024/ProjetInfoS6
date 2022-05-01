#include <stdio.h>
#include <string.h>
#include "../includes/structures.h"
#include "../includes/prototypes.h"

void initGameState(GameState* gamestate)
{
	gamestate->team_player = NULL;
	gamestate->team_monster = NULL;
	gamestate->inventory = NULL;
	gamestate->shop = NULL;
	gamestate->highscore = NULL;
	gamestate->treasure = getNullItem();
	strcpy(gamestate->save_file, "");
}

void initShop(Node** shop)
{
	Item item1={"DOUDOUNE", "Vetement de demi saison, procure une defense plutot faible",EQUIPMENT,4.7,1,1,1,1};
	Item item2={"POTION TABASCO", "Un remontant qui ne laisse pas indifferent",ITEM,29.9,1,1,1,1};
	Item item3={"TABAC", "Un peu fumeux pour une arme",ITEM,20.5,1,1,1,1};
	Item item4={"FOURCHETTE", "Pour manger et piquer les monstres acessoirement",EQUIPMENT,212.9,1,1,1,1};

	push(shop, &item1, sizeof(Item));
	push(shop, &item2, sizeof(Item));
	push(shop, &item3, sizeof(Item));
	push(shop, &item4, sizeof(Item));
}

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

Item getNullItem()
{
	Item null_item = {
		"Nothing",
		"Nothing",
		NULL_ITEM,
		0, 0, 0, 0, 0, 0	//Ajout equipped de type int
	};

	return null_item;
}

Plateau* getPlateau(Node* liste)
{
	if (!liste)
		return NULL;
	return (Plateau*) liste->data;

}

int generateNextPlateau(Node** run)
{
	static int id = 0;

	Plateau current;
	
	current.id = id; id++;

	current.monsters = NULL;
	Entity monster = {
		0,			//id
		"Monster",
		getNullItem(), getNullItem(),
		10, 0, 2, 10
	};
	for (int i = 0; i < id; i++)
		push(&current.monsters, &monster, sizeof(Entity));

	// Treasure !!

	push(run, &current, sizeof(Plateau));
	
	return 0; //OK
}
