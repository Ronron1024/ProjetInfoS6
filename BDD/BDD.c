#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/isen/Bureau/ProjetInfoS6/includes/structures.h"

#define LINE_SIZE   1000
#define TAILLE_STRING 200
#define NOM_FICHIER_ITEM "item.txt"
#define NOM_FICHIER_ARME "arme.txt"
#define NOM_FICHIER_OBJET "objet.txt"

Item*recupererLigne(char*ligne);
Item*chargerTxt(char*nomFichier);
Item*insertionAlpha(Item*liste,Item*nouvelElement);
Item*saisirElementItem(void);
Item*saisirElementArme(void);
Item*saisirElementObjet(void);
void printMenu(void);
void printSousMenu(void);
void printAjoutListe(void);
void saveTxt(Item*liste,char*nomFichier);
void afficheListe(Item *liste);
void afficheElement(Item *elem);
void afficheListeRec(Item *liste);


int main(int argc, char **argv) //on place tout la classe item, ou on fait des classes differentes : item, objet,armes, etc car si on classe tout sous item, une arme n'aura par exemple pas de capacité de soins donc 0
//si une capacité à 0 (exemple du soins avec une armes, alors on peut l'enelver lors de l'affichage de l'element dans la liste
{
	Item *liste_item = NULL;
	Item *liste_arme = NULL;
	Item *liste_objet = NULL;

	printf("chargement\n");


	liste_item=chargerTxt(NOM_FICHIER_ITEM);
	liste_arme=chargerTxt(NOM_FICHIER_ARME);
	liste_objet=chargerTxt(NOM_FICHIER_OBJET);
	
	
	int exit = 0;
	char choix;
	char choix1;
	char choix2;
	
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
				saveTxt(liste_item,NOM_FICHIER_ITEM);
				saveTxt(liste_arme,NOM_FICHIER_ARME);
				saveTxt(liste_objet,NOM_FICHIER_OBJET);
				break;
				
			case '1':
				do
				{
					printSousMenu();
					scanf(" %c", &choix1);

					switch (choix1)
					{

					case 'a' :
					case 'A' :
						afficheListe(liste_arme);
						break;
						
					case 'i' :
					case 'I' :
						afficheListe(liste_item);
						break;
						
					case 'o' :
					case 'O' :
						afficheListe(liste_objet);
						break;
						
					case 'e' :
					case 'E' :
						afficheListe(liste_arme);
						afficheListe(liste_item);
						afficheListe(liste_objet);
						break;

					case 'r':
					case 'R':
                        break;

                    default:
                        printf("ERR: Choix\n");
                        break;

					}
				}
            while( choix1 != 'r' && choix1 != 'R');
			
			break;
				
			case '2':
				do
				{
					printAjoutListe();
					scanf(" %c", &choix2);
					
					switch(choix2)
					{
					
					case 'a' :
					case 'A' :
						liste_arme = insertionAlpha(liste_arme,saisirElementArme());
						break;
						
					case 'i' :
					case 'I' :
						liste_item = insertionAlpha(liste_item,saisirElementItem());						
						break;
						
					case 'o' :
					case 'O' :
						liste_objet = insertionAlpha(liste_objet,saisirElementObjet());
						break;

					case 'r':
					case 'R':
                        break;

                    default:
                        printf("ERR: Choix\n");
                        break;
				
					}
				}
				while( choix2 != 'r' && choix2 != 'R');
				
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
	printf("\nMenu \n");
	printf("0 - Exit \n");
	printf("1 - Afficher les Liste \n"); // possible de faire un sous menu pour choisir la liste a afficher
	printf("2 - Ajouter un element dans une liste \n"); // pareil faire un sous menu pour ajouter une entree dans la liste que l'on veut armes,objet,item,etc
	printf("3 - compterParGenre (encore en dev) \n"); // dans les listes il faudrait pouvoir compter le nombre de chaque type. Exemple compter le nombre d'armes de corps a corps daans la liste armes, le notre de potions dans la liste item etc

}

void printSousMenu(void)
{
	printf("Listes \n");
	printf("A - Listes Armes \n");
	printf("I - Listes Item \n");
	printf("O - Liste Objets \n");
	printf("E - Toutes les Listes \n");
	printf("R - Retour \n");
	
}

void printAjoutListe(void)
{
	printf("Ajouter elements dans une liste : \n");
	printf("A - Ajouter une arme \n");
	printf("I - Ajouter un item \n");
	printf("O - Ajouter un objet \n");
	printf("R - Retour \n");
	
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
	printf("|nom  :                            %20s|\n",elem->name);
	printf("|description :             %20s|\n",elem->description);
	printf("|type :                            %20s|\n",elem->type);
	printf("|prix :                            %20.2f|\n",elem->price);
	printf("|PV :                              %20lf|\n",elem->health);
	printf("|Attaque :                         %20lf|\n",elem->attack);
	printf("|Defense :                         %20lf|\n",elem->defense);
	printf("|Vitesse :                         %20lf|\n",elem->speed);

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

Item*saisirElementItem(void)
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

Item*saisirElementArme(void)
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

Item*saisirElementObjet(void)
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


