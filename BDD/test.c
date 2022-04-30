#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/media/sf_partage/ProjetInfoS6/includes/structures.h"

#define LINE_SIZE   1000
#define TAILLE_STRING 200
#define NOM_FICHIER_ITEM "item.txt"

Item*recupererLigne(char*ligne);
Item*chargerTxt(char*nomFichier);
Item*insertionAlpha(Item*liste,Item*nouvelElement);
Item*saisirElement(void);
void printMenu(void);
void saveTxt(Item*liste,char*nomFichier);
void afficheListe(Item *liste);
void afficheElement(Item *elem);
void afficheListeRec(Item *liste);

int main(int argc, char **argv)
{
	Item *liste = NULL;

	printf("charger\n");

	liste=chargerTxt(NOM_FICHIER_ITEM);
	
	int exit = 0;
	char choix;
	
	while( exit == 0 )
	{
		printMenu();
		scanf(" %c",&choix);//getchar(); pas besoin car il y a un espace devant le %c MAGIC
		switch(choix)
		{
			case '0':
			case 'o':
			case 'O':
				exit = 1;
				saveTxt(liste,NOM_FICHIER_ITEM);
				break;
				
			case '1':
				afficheListe(liste);
				break;
				
			case '2':
				liste=insertionAlpha(liste,saisirElement());
				break;
				
			default :
				printf("Commande inconnue\n");
				break;
		
		}
	}
	return 0;
}

void printMenu(void)
{
	printf("\nMenu\n");
	printf("0 - exit \n1 - affichier tout \n2 - ajouter element\n");
	printf("3 - compterParGenre\n");
	printf("4 - valeurGlobale\n");
	printf("5 - prixMoyenParGenre\n");
}


/* charge la liste qui a été save en TXT */
Item*chargerTxt(char*nomFichier)
{
	printf("chargement du fichier %s\n",nomFichier);

	Item*liste = NULL;
	Item*new = NULL;
	FILE*f;
	
	f = fopen(nomFichier,"r");
	if (f == NULL )
	{
		printf("erreur lecture de fichier %s chargement annulee\n",nomFichier);
		return NULL;
	}

	char lineBuffer[LINE_SIZE];
	
	while(fgets(lineBuffer,LINE_SIZE,f) != NULL)
	{
		new=recupererLigne(lineBuffer);
		liste=insertionAlpha(liste,new);
	}
	
	
	fclose(f);
	return liste;
}

/* converti la ligne ecrit en TXT en une structure que le program peut comprendre */
Item*recupererLigne(char*ligne)
{
	Item*new=malloc(sizeof(Item));
	if( new == NULL )
	{
		printf("Erreur allocation memoire dans recupererLigne()\n");
		return NULL;
	}
	ligne[strlen(ligne)-1]='\0';
	
	char separator[2]=";";
	
	char * token =strtok(ligne,separator);
	strcpy(new->name,token);

	token = strtok(NULL,separator);
	strcpy(new->description,token);

	token = strtok(NULL,separator);
	strcpy(new->type,token);
	
	token = strtok(NULL,separator);
	new->price = atof(token); //converti l'element de l'ascci vers un float 
	
	token = strtok(NULL,separator);
	new->health = atof(token);
	
	token = strtok(NULL,separator);
	new->attack = atof(token);
	
	token = strtok(NULL,separator);
	new->defense = atof(token);
	
	token = strtok(NULL,separator);
	new->speed = atof(token);
	
	new->suiv=NULL;
	
	return new;
	
}

void saveTxt(Item*liste,char*nomFichier)
{
	FILE*f = NULL;
	f = fopen(nomFichier,"w");
	if (f == NULL )
	{
		printf("erreur creation de fichier %s sauvgarder annulee",nomFichier);
		return;
	}
	Item *courant=liste;
	while( courant != NULL ) /* tant qu'il reste des elements */
	{
		
			fprintf(f,"%s;%s;%s;%f;%lf;%lf;%lf;%lf\n", courant->name, courant->description, courant->type, courant->price, courant->health, courant->attack, courant->defense, courant->speed);	
			courant = courant->suiv;
		
	}
	fclose(f);	
}

void afficheElement(Item *elem)
{
	if( elem == NULL )
	{
		printf("afficheElement impossible sur Element vide\n");
		return;
	}
	printf("|---------------------------|\n");
	printf("|nom  : %20s|\n",elem->name);
	printf("|description : %20s|\n",elem->description);
	printf("|type: %20s|\n",elem->type);
	printf("|prix : %20.2f|\n",elem->price);
	printf("|PV  : %lf\n",elem->health);
	printf("|Attaque  : %lf\n",elem->attack);
	printf("|Defense  : %lf\n",elem->defense);
	printf("|Vitesse  : %lf\n",elem->speed);

}

void afficheListe(Item *liste)
{
	Item *courant=liste;
	if( liste == NULL )
	{
		printf("afficheListe impossible sur liste vide\n");
		return ;
	}
	while( courant != NULL ) // tant qu'il reste des elements 
	{
		afficheElement(courant);
		courant = courant->suiv;
		
	}
}

void afficheListeRec(Item *liste)
{

	// 1) cas de sortie de la recurivité
	if (liste == NULL )
		return;
	// 2.1) traitement = afficher element avant rec? 
	printf("a");
	afficheElement(liste);
	
	// 3) recurcivité = rappeler la fonction afficheListeRec avec un autre parametre??
	printf("-------------------------------------------\n");
	afficheListeRec(liste->suiv);
	// 2.2) traitement = afficher elementapres rec?
	printf("p");
	afficheElement(liste);
}

Item*insertionAlpha(Item*liste,Item*nouvelElement)
{
	
	if (liste == NULL)
	{	/* cas d'une lsite vide */
		nouvelElement->suiv = NULL;
		liste = nouvelElement;
		return liste;
	}
	
	if(nouvelElement == NULL)
	{
		printf("Rien a insert\n");
		return liste;
	}
	
	Item*courant = liste;
	Item*precedent = NULL;
	while( courant != NULL )
	{
/* parcour de la liste pour trouver le bon endroit ou insert */
		if( strcmp(courant->name,nouvelElement->name)>0)
		{ /* on a trouver le bon endroit */
			if(courant==liste)
			{ /* ajout debut */
				nouvelElement->suiv = liste;
				liste = nouvelElement;
				return liste;
			}
			else
			{
				precedent->suiv=nouvelElement;
				nouvelElement->suiv=courant;
				return liste;
			}
		}
		else
		{ /* on continue d'avancer */
			precedent=courant;
			courant=courant->suiv;
		}
	}
/* ici on est sortie de la boucle => fin de la liste courant == NULL */
	precedent->suiv=nouvelElement;
	nouvelElement->suiv=NULL;

	return liste;
}

Item*saisirElement(void)
{
	Item*new=malloc(sizeof(Item));
	if( new == NULL )
	{
		printf("Erreur allocation memoire dans saisirElement()\n");
		return NULL;
	}
	printf("Saisir objet \n");
	printf("NAME : ");
	scanf("%s",new->name);
	printf("description de l'objet : ");
	//scanf("%s",new->description);
	getchar();	
	fgets(new->description,TAILLE_STRING,stdin);
	new->description[strlen(new->description)-1]='\0';
	
	printf("Type : ");
	scanf("%s",new->type);
	printf("Prix : ");
	scanf("%f",&new->price);
	printf("PV : ");
	scanf("%lf",&new->health);
	printf("Attaque : ");
	scanf("%lf",&new->attack);
	printf("Defense : ");
	scanf("%lf",&new->defense);
	printf("Vitesse : ");
	scanf("%lf",&new->speed);
	printf("affichage de l'element saisi\n");
	afficheElement(new);
	return new;
}
