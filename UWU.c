
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct liste
{
  int nombre;
  struct liste *suivant;
} liste;

void alocation_dernier (liste **ptr)
{
	if (*ptr == NULL)
	{
		*ptr = (liste *)malloc(sizeof(liste));
		(*ptr)->suivant = NULL;
	}
	else
	{
		while((*ptr)->suivant != NULL)
			(*ptr) = (*ptr)->suivant;
		(*ptr)->suivant = (liste *)malloc(sizeof(liste));
		(*ptr) = (*ptr)->suivant;
		(*ptr)->suivant = NULL;
	}
}

void	allocation_position(liste **tete, int pos)
{
	liste *ptr;
	liste *derriere;

	if (pos <= 1)
	{
		derriere = (liste *)malloc(sizeof(liste));
		derriere->suivant = *tete;
		*tete = derriere;
	}
	else
	{
		ptr = *tete;
		for (int i = 1; i < pos; i++)
		{
			if (ptr == NULL)
				break;
			derriere = ptr;
			ptr = ptr->suivant;
		}
		derriere->suivant = (liste *)malloc(sizeof(liste));
		derriere = derriere->suivant;
		derriere->suivant = ptr;
	}
}

void	afficher_liste(liste *tete)
{
	while (tete != NULL)
	{
		printf("%d ", tete->nombre);
		tete = tete->suivant;
	}
	printf("\n");
}

void	trier(liste *tete)
{
	int		ech;
	int		temp;
	liste	*ptr;
	liste	*derriere;

	derriere = NULL;
	do
	{
		ech = 0;
		ptr = tete;
		while (ptr->suivant != derriere)
		{
			if (ptr->nombre > ptr->suivant->nombre)
			{
				temp = ptr->nombre;
				ptr->nombre = ptr->suivant->nombre;
				ptr->suivant->nombre = temp;
				ech = 1;
			}
			ptr = ptr->suivant;
		}
		derriere = ptr;
	} while (ech);

}

void	separee(liste *tete)
{
	liste	*ptr;
	liste	*pair = NULL;
	liste	*pair_tete;
	liste	*impair = NULL;
	liste	*impair_tete;
	int		i = 0, j = 0;
	ptr = tete;
	while(ptr != NULL)
	{
		if ((ptr->nombre % 2) == 0)
		{
			alocation_dernier(&pair);
			if (i == 0)
				pair_tete = pair;
			pair->nombre = ptr->nombre;
			i++;
		}
		else if ((ptr->nombre % 2) == 1)
		{
			alocation_dernier(&impair);
			if (j == 0)
				impair_tete = impair;
			impair->nombre = ptr->nombre;
			j++;
		}
		ptr = ptr->suivant;
	}
	printf("les listes pair: ");
	afficher_liste(pair_tete);
	printf("les listes impair: ");
	afficher_liste(impair_tete);
}
int main ()
{
	liste		*ptr = NULL;
	liste		*sv = NULL;
	liste		*tete = NULL;
	int			t;
	int			i;

	printf("entre nombre des elements: ");
	scanf("%d", &t);
	if (t == 0)
		return (-1);
	for (i = 0; i < t; i++)
	{
		alocation_dernier(&ptr);
		if (i == 0)
			tete = ptr;
		printf("entrer l'entrier: ");
		scanf("%d", &(ptr->nombre));
	}
	afficher_liste(tete);
	printf("entrer position: ");
	scanf("%d", &t);
	allocation_position(&tete, t);
	ptr = tete;
	for (i = 1; i < t; i++)
	{
		if (ptr->suivant == NULL)
			break;
		ptr = ptr->suivant;
	}
	printf("entrer l'entier: ");
	scanf("%d", &(ptr->nombre));
	afficher_liste(tete);
	printf("apres trier: ");
	trier(tete);
	afficher_liste(tete);
	separee(tete);
  return 0;
}
