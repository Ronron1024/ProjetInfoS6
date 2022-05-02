#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
	Node* items = chargerTxtItem(ITEMS_PATH);
	Node* armors = chargerTxtItem(ARMORS_PATH);
	Node* weapons = chargerTxtItem(WEAPONS_PATH);

	push(shop, getItem(getRandomNode(items)), sizeof(Item));
	push(shop, getItem(getRandomNode(armors)), sizeof(Item));
	push(shop, getItem(getRandomNode(weapons)), sizeof(Item));
}

void upgradeShop(Node** shop, int level)
{
	// Empty shop
	freeList(*shop);
	*shop = NULL;

	Node* items = chargerTxtItem(ITEMS_PATH);
	Node* armors = chargerTxtItem(ARMORS_PATH);
	Node* weapons = chargerTxtItem(WEAPONS_PATH);

	push(shop, upItem(getItem(getRandomNode(items)), level), sizeof(Item));
	push(shop, upItem(getItem(getRandomNode(armors)), level), sizeof(Item));
	push(shop, upItem(getItem(getRandomNode(weapons)), level), sizeof(Item));
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

Item* upItem(Item* item, int level)
{
	item->health *= (COEFF_ITEM_UPGRADE + level/2);
	item->attack *= (COEFF_ITEM_UPGRADE + level/2);
	item->defense *= (COEFF_ITEM_UPGRADE + level/2);
	item->speed *= (COEFF_ITEM_UPGRADE + level/2);

	return item;
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

Entity getNullEntity()
{
	Entity null_entity = {
		0,
		"Nothing",
		getNullItem(),getNullItem(),
		0, 0, 0, 0	
	};

	return null_entity;
}

Item getRandomItem()
{
	// USE ALIASES !!
	int alea = randInt(0,2);
	switch(alea)
	{
		case 0:
			return *getItem(getRandomNode(chargerTxtItem(ITEMS_PATH)));
			break;
		case 1:
			return *getItem(getRandomNode(chargerTxtItem(ARMORS_PATH)));
			break;
		case 2:
			return *getItem(getRandomNode(chargerTxtItem(WEAPONS_PATH)));
			break;
	}

	return getNullItem();
}

Item getRandomTrap()
{
	Node* traps = chargerTxtItem(TRAPS_PATH);
	return *getItem(getRandomNode(traps));
}


Plateau* getPlateau(Node* liste)
{
	if (!liste)
		return NULL;
	return (Plateau*) liste->data;

}

int generateNextPlateau(Node** run)
{
	int nbMonster;
	int n;

	Plateau* current = (Plateau*) malloc(sizeof(Plateau));
	Entity monster = getNullEntity();
	Node* head =	(Node*) malloc(sizeof(Node));
		
	current->id = getPlateauId();
	current->monsters = NULL;
	
	//Randon fichier avec stats fonctions de l' id +/-1	
	head = chargerTxtEntity(MONSTERS_PATH);		
	nbMonster = compterObjet(head);

	for (int i = 0; i < current->id+1; i++){
	
		n = randInt(1, nbMonster);
		monster = selectEntity(head, n);
		monster = modified(monster, current->id);
		push(&current->monsters, &monster, sizeof(Entity));
	}
	
	// Treasure !!
	
	push(run, current, sizeof(Plateau));
	
	return 0; //OK
}

void savePlateau(const void* data, FILE* save_file)
{
	if (!save_file)
		return;

	Plateau* plateau = (Plateau*) data;

	int number_monster = count(plateau->monsters);

	fwrite(&number_monster, sizeof(int), 1, save_file);

	saveList(plateau->monsters, save_file, saveEntity);

	plateau->monsters = NULL;
	fwrite(&plateau, sizeof(Plateau), 1, save_file);
}

void saveEntity(const void* data, FILE* save_file)
{
	if (!save_file)
		return;

	Entity* entity = (Entity*) data;

	fwrite(entity, sizeof(Entity), 1, save_file);
}

void saveItem(const void* data, FILE* save_file)
{
	if (!save_file)
		return;

	Item* item = (Item*) data;

	fwrite(item, sizeof(Item), 1, save_file);
}

void saveGame(Node* run, GameState gamestate)
{
	int save_path_length = strlen(SAVE_FOLDER) + CHAR_SAVE_MAX + strlen(".bin");
	char* save_path = malloc(sizeof(char) * save_path_length);
	strcpy(save_path, SAVE_FOLDER);
	strcat(save_path, gamestate.save_file);
	strcat(save_path, ".bin");

	FILE* save_file = fopen(save_path, "w");

	if (!save_file)
	{
		printf("Error while saving game\n");
		free(save_path);
		return;
	}

	int number_plateau = count(run);
	int number_player = count(gamestate.team_player);
	int number_monster = count(gamestate.team_monster);
	int number_inventory = count(gamestate.inventory);
	int number_shop = count(gamestate.shop);

	fwrite(&number_plateau, sizeof(int), 1, save_file);
	// saveList(run, save_file, savePlateau);

	fwrite(&number_player, sizeof(int), 1, save_file);
	saveList(gamestate.team_player, save_file, saveEntity);

	fwrite(&number_monster, sizeof(int), 1, save_file);
	saveList(gamestate.team_monster, save_file, saveEntity);

	fwrite(&number_inventory, sizeof(int), 1, save_file);
	saveList(gamestate.inventory, save_file, saveItem);

	fwrite(&number_shop, sizeof(int), 1, save_file);
	saveList(gamestate.shop, save_file, saveItem);

	fwrite(gamestate.highscore, sizeof(Score), 1, save_file);

	fclose(save_file);
	free(save_path);
}

void loadGame(Node** run, GameState* gamestate)
{
	int save_path_length = strlen(SAVE_FOLDER) + CHAR_SAVE_MAX + strlen(".bin");
	char* save_path = malloc(sizeof(char) * save_path_length);
	strcpy(save_path, SAVE_FOLDER);
	strcat(save_path, gamestate->save_file);
	strcat(save_path, ".bin");

	FILE* save_file = fopen(save_path, "r");

	if (!save_file)
	{
		printf("Error while loading game\n");
		free(save_path);
		return;
	}

	int number_plateau = 0;
	fread(&number_plateau, sizeof(int), 1, save_file);
	for (int i = 0; i < number_plateau; i++)
		getPlateauId();

	int number_player = 0;
	Entity current_entity;
	fread(&number_player, sizeof(int), 1, save_file);
	for (int i = 0; i < number_player; i++)
	{
		fread(&current_entity, sizeof(Entity), 1, save_file);
		push(&gamestate->team_player, &current_entity, sizeof(Entity));
	}

	int number_monster = 0;
	fread(&number_monster, sizeof(int), 1, save_file);
	for (int i = 0; i < number_monster; i++)
	{
		fread(&current_entity, sizeof(Entity), 1, save_file);
		push(&gamestate->team_monster, &current_entity, sizeof(Entity));
	}

	int number_inventory = 0;
	Item current_item;
	fread(&number_inventory, sizeof(int), 1, save_file);
	for (int i = 0; i < number_inventory; i++)
	{
		fread(&current_item, sizeof(Item), 1, save_file);
		push(&gamestate->inventory, &current_item, sizeof(Item));
	}

	int number_shop = 0;
	fread(&number_shop, sizeof(int), 1, save_file);
	for (int i = 0; i < number_shop; i++)
	{
		fread(&current_item, sizeof(Item), 1, save_file);
		push(&gamestate->shop, &current_item, sizeof(Item));
	}

	Score* score = malloc(sizeof(Score));
	fread(score, sizeof(Score), 1, save_file);
	gamestate->highscore = score;

	fclose(save_file);
	free(save_path);
}