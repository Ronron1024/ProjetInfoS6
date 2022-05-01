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