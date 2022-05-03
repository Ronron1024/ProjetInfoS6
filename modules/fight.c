#include <string.h>
#include "../includes/structures.h"
#include "../includes/prototypes.h"

void addStats(Entity* entity, Item item)
{
	entity->health += item.health;
	entity->attack += item.attack;
	entity->defense += item.defense;
	entity->speed += item.speed;
}

void subStats(Entity* entity, Item item)
{
	entity->health -= item.health;
	entity->attack -= item.attack;
	entity->defense -= item.defense;
	entity->speed -= item.speed;
}


bool canGetAlly()
{
	return ((double)randInt(1,100))/100.0 < ALLY_PROBA;
}

double attack(Entity* attacker, Entity* defender)
{
	double damage_points = getEntityComputedStats(*attacker).attack - getEntityComputedStats(*defender).defense;
	damage_points = damage_points < 0 ? 0 : damage_points; // Prevent negative damage
	defender->health -= damage_points;
	return damage_points;
}

bool fight(Node** team1, Node** team2, char* log)
{
	// Initial conditions
	static Team attacker_team = TEAM1;
	static Team defender_team = TEAM2;
	static Node* attacker = NULL;

	// Other variables
	Node* defender = NULL;
	double damage_points = 0.0;

	// End fight (condition : no member left in one team)
	if (!*team1 || !*team2)
	{
		// Reset initial conditions
		attacker_team = TEAM1;
		defender_team = TEAM2;
		attacker = NULL;

		// Assuming team1 is the player team, log fight outcome
		if (!*team1)
			strcpy(log, "No member left in your team, end of the game...");
		else
			strcpy(log, "It's a victory !");

		return FALSE;
	}

	// Define attacker
	if (!attacker)
		attacker = *team1; // Init first attacker
	else
	{
		if (attacker->next) // While team has next member
			attacker = attacker->next;
		else // Switch team
		{
			attacker_team = attacker_team == TEAM1 ? TEAM2 : TEAM1;
			defender_team = defender_team == TEAM1 ? TEAM2 : TEAM1;
			attacker = attacker_team == TEAM1 ? *team1 : *team2;
		}
	}

	// Define defender
	defender = attacker_team == TEAM1 ? getRandomNode(*team2) : getRandomNode(*team1);

	// Inflige damage & manage death
	damage_points = attack(getEntity(attacker), getEntity(defender));
	sprintf(log, "%s hits %s with %.2lf DP !", getEntity(attacker)->name, getEntity(defender)->name, damage_points);
	if (isDead(*getEntity(defender)))
	{
		delete(defender_team == TEAM1 ? team1 : team2, defender);
		strcat(log, " (Dead)");
	}

	return TRUE;
}
