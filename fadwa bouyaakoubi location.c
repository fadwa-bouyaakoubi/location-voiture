#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct	date
{
	int	year;
	int	mois;
	int	jour;
	int	hh;
}				date;

typedef struct	Voiture
{
	int		nbplaces;
	int		prixJour;
	int		idVoiture;
	char	marque[15];
	char	couleur[7];
	char	nomVoiture[15];
	char	EnLocation[4];
}				voiture;

typedef	struct	contratLocation
{
	float	numContrat;
	int		idVoiture;
	int		idClient;
	int		cout;
	date	debut;
	date	fin;
}				contrat;

typedef	struct	client
{
	char	nom[20];
	char	prenom[20];
	char	adresse[15];
	int		cin;
	int		idClient;
	int		telephone;
}				client;

int		print_menu_principal()
{
	int	choice;

	choice = 0;
	do
	{
		printf("\t\t -------------------------------\t\t\t\n");
		printf("\t\t|\tMenu Principal\t\t|\n");
		printf("\t\t -------------------------------\t\t\t\n\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t|\tLocation..............................1\t\t|\n");
		printf("\t|\tGestion voitures......................2\t\t|\n");
		printf("\t|\tGestion clients.......................3\t\t|\n");
		printf("\t|\tQuitter...............................4\t\t|\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t\t votre choix : ");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 4);

	return (choice);
}














void	ft_rental_management(void)
{
	int choice;

	while (1)
	{
		choice = print_rental_menu();
		if (choice == 1)		ft_visualizer_les_contrat();
		else if (choice == 2)	louer_une_voiture();
		else if (choice == 3)	retourner_une_voiture();
		else if (choice == 4)	modifier_une_contrat();
		else if (choice == 5)	sup_une_contrat();
		else if (choice == 6)	break ;
	}
}

int		print_rental_menu()
{
	int	choice;

	choice = 0;
	do
	{
//		system("clear");
		printf("\t\t -------------------------------\t\t\t\n");
		printf("\t\t|\tLocation d'une voiture\t\t|\n");
		printf("\t\t -------------------------------\t\t\t\n\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t|\tVisualiser contrat..............................1\t\t|\n");
		printf("\t|\tlouer voiture...................................2\t\t|\n");
		printf("\t|\tRetourner voiture...............................3\t\t|\n");
		printf("\t|\tModifier contrat................................4\t\t|\n");
		printf("\t|\tsupprimer contrat...............................5\t\t|\n");
		printf("\t|\tretour..........................................6\t\t|\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t\t votre choix  :  ");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 6);
	return (choice);
}

//	float	numContrat;
//	int		idVoiture;
//	int		idClient;
//	int		cout;
//	date	debut;
//	date	fin;

/*
** **************************************************************************
*/

void	ft_visualizer_les_contrat()
{
	contrat	cntr;
	FILE	*file = fopen("ContratsLocations", "r");

	if (file == NULL)
	{
		file = fopen("ContratsLocations", "w");
		fclose(file);
		file = fopen("ContratsLocations", "r");
		//printf("ERROR, couldn't open contract file\n");
		//return ;
	}
	while (read_one_contrat(file, &cntr) != EOF)
		print_one_contrat(cntr);
	fclose(file);
}




/*
** **************************************************************************
*/

void	louer_une_voiture()
{
	contrat	cntr;

	get_contrat_input(&cntr);
	//verify_this_contrat(cntr);
	add_this_contrat(cntr, "ContratsLocations");
	modifier_car_enLocation(cntr.idVoiture, "Yes");
}

void	get_contrat_input(contrat *cntr)
{
	printf("please write the information of this contrat : \n");
	printf("contrat number : "); 	scanf("%f", &(cntr->numContrat));
	printf("voiture id     : ");	scanf("%d",  &(cntr->idVoiture));
	printf("client id      : ");	scanf("%d",  &(cntr->idClient));
	printf("cout           : ");	scanf("%d",  &(cntr->cout));
	printf("le temp dans cette format : heure jour mois année \n");
	printf("debut          : ");	scanf("%d %d %d %d",   \
		&cntr->debut.hh, &cntr->debut.jour, &cntr->debut.mois, &cntr->debut.year);
	printf("fin            : ");	scanf("%d %d %d %d",   \
		&cntr->fin.hh, &cntr->fin.jour, &cntr->fin.mois, &cntr->fin.year);
}

/*
** **************************************************************************
*/

void	retourner_une_voiture()
{
	int 	id;
	contrat	cntr;
	FILE	*file =  fopen("ContratsLocations", "r");

	printf("Donner l'id du contrat : ");
	scanf("%d", &id);

	while (read_one_contrat(file, &cntr) != EOF)
	{
		if (cntr.numContrat == id)
		{
			fclose(file);
			modifier_car_enLocation(cntr.idVoiture, "Non");
			del_one_contrat(cntr);
			return ;
		}
	}
	fclose(file);
}

/*
** **************************************************************************
*/

void	modifier_une_contrat()
{
	FILE	*file = fopen("ContratsLocations", "r");
	float	contrat_id;
	int		choix;
	int		tmp;
	contrat	cntr;

	if (file == NULL)
	{
		printf("A BIIIG FAT PROBLEM\n");
		//exit(0);
	}
	get_contrat_modification(&contrat_id, &choix);
	printf("you have choosed\tid : %f. choix : %d\n", contrat_id, choix);

	while (1)
	{
		tmp = read_one_contrat(file, &cntr);
		if (tmp != EOF && contrat_id == cntr.numContrat)
		{
			fclose(file);
			if (choix >= 1 && choix <= 5)
			{
				del_one_contrat(cntr);
				printf("saisir la modification : ");
				if (choix == 1)			scanf("%d", &(cntr.idVoiture));
				else if (choix == 2)	scanf("%d", &(cntr.idClient));
				else if (choix == 3)	scanf("%d", &(cntr.cout));
				else if (choix == 4)
				{
					printf("\ndebut in this format hh dd/mm/yy : ");
					scanf("%d %d %d %d",   \
						&(cntr.debut.hh), &(cntr.debut.jour), \
						&(cntr.debut.mois), &(cntr.debut.year));
				}
				else if (choix == 5)
				{
					printf("\nfin in this format hh dd/mm/yy :  ");
					scanf("%d %d %d %d",   \
						&(cntr.fin.hh), &(cntr.fin.jour), \
						&(cntr.fin.mois), &(cntr.fin.year));
				}
				printf("going to add this contrat : \n");
				print_one_contrat(cntr);
				add_this_contrat(cntr, "ContratsLocations");
				return ;
			}
			else
				printf("choix invalid\n");
			return ;
		}
		if (tmp == EOF)
			break ;
	}
	fclose(file);
}

void	get_contrat_modification(float *contrat_id, int *choix)
{
	printf("Donner l'id de le contrat tu veut modifer : ");
	scanf("%f", contrat_id);
	printf("\tque voulez-vous modifier?\n");
	printf("\tidVoiture...............1\n");
	printf("\tidClient................2\n");
	printf("\tcout....................3\n");
	printf("\tdebut...................4\n");
	printf("\tfin.....................5\n");
	printf("\t\tvotre choix :  ");	scanf("%d", choix);
}

//	float	numContrat;
//	int		idVoiture;
//	int		idClient;
//	int		cout;
//	date	debut;
//	date	fin;

/*
** **************************************************************************
*/

void	sup_une_contrat()
{
	int		id;
	int		ret;
	voiture car;
	contrat	contrat;
	FILE	*cars = fopen("Voitures", "r");
	FILE	*file = fopen("ContratsLocations", "r");

	printf("donnez l'id du contrat que vous souhaitez supprimer : ");
	scanf("%d", &id);
	while (1)
	{
		ret = read_one_contrat(file, &contrat);	
		if (ret == EOF)
		{
			printf("this id doesn't exist.\n");
			return ;
		}
		if (contrat.idVoiture == id)
			break;
	}
	while (1)
	{
		read_one_car_info(cars, &car);
		if (car.idVoiture == contrat.idVoiture)
		{
			if (strcmp(car.EnLocation, "Non") == 0)
			{
				fclose(cars);
				fclose(file);
				del_one_contrat(contrat);
				return ;
			}
			else
			{
				printf("la voiture est louée.\n");
				break ;
			}
		}
	}
	fclose(cars);
	fclose(file);
}


/*
** **************************************************************************
**					main functions
*/

void	add_this_contrat(contrat cntr, char *filename)
{
	FILE	*file = fopen (filename, "a+");

	fprintf(file, "<<\n");
	fprintf(file, "%f\n", cntr.numContrat);
	fprintf(file, "%d\n", cntr.idVoiture);
	fprintf(file, "%d\n", cntr.idClient);
	fprintf(file, "%d\n", cntr.cout);
	fprintf(file, "%d %d %d %d\n", \
			cntr.debut.hh, cntr.debut.jour, cntr.debut.mois, cntr.debut.year);
	fprintf(file, "%d %d %d %d\n", \
			cntr.fin.hh, cntr.fin.jour, cntr.fin.mois, cntr.fin.year);
	fprintf(file, "/>>\n");
	fclose(file);
}

int		read_one_contrat(FILE *file, contrat *cntr)
{
	int		ret;
	char	line[10];
	//static int i;

	//printf("read i == %d;\n", i++);
	ret = fscanf(file, "%s\n",    line);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%f\n",  &(cntr->numContrat));
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%d\n",  &(cntr->idVoiture));
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%d\n",  &(cntr->idClient));
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%d\n",  &(cntr->cout));
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%d %d %d %d\n",   \
				&cntr->debut.hh, &cntr->debut.jour, &cntr->debut.mois, &cntr->debut.year);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%d %d %d %d\n",   \
				&cntr->fin.hh, &cntr->fin.jour, &cntr->fin.mois, &cntr->fin.year);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%s\n", line);
	return (ret);
}

void	print_one_contrat(contrat contrat)
{
	printf("_________________________________\n");
	printf("\tContrat num : %f.\n", contrat.numContrat);
	printf("\tidVoiture   : %d\n", contrat.idClient);
	printf("\tcout        : %d\n", contrat.cout);
	printf("\tdebut       : %.2d:00, %.2d/%.2d/%.4d\n", \
			contrat.debut.hh, contrat.debut.jour, contrat.debut.mois, contrat.debut.year);
	printf("\tfin         : %d:00 %.2d/%.2d/%.4d\n", \
			contrat.fin.hh, contrat.fin.jour, contrat.fin.mois, contrat.fin.year);
	printf("_________________________________\n");
}

void	del_one_contrat(contrat cntr)
{
	FILE	*ptr1, *ptr2;
	contrat	temp_cntr;
	int tmp;

	ptr1 = fopen("ContratsLocations", "r");
	ptr2 = fopen("cntr_replica.txt", "w");
	fclose(ptr2);

	while (1)
	{
		tmp = read_one_contrat(ptr1, &temp_cntr);
		if (tmp == EOF)
			break ;
		if (tmp != EOF && temp_cntr.numContrat != cntr.numContrat)
			add_this_contrat(temp_cntr, "cntr_replica.txt");
	}
	fclose(ptr1);
	remove("ContratsLocations");
	rename("cntr_replica.txt", "ContratsLocations");
}










int		print_clients_menu()
{
	int	choice;

	choice = 0;
	do
	{
//		system("clear");
		printf("\t\t -------------------------------\t\t\t\n");
		printf("\t\t|\tGestion des Clients\t\t|\n");
		printf("\t\t -------------------------------\t\t\t\n\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t|\tList des clients................................1\t\t|\n");
		printf("\t|\tAjouter client...................................2\t\t|\n");
		printf("\t|\tModifier client.................................3\t\t|\n");
		printf("\t|\tSupprimer client................................4\t\t|\n");
		printf("\t|\tretour..........................................5\t\t|\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t\t votre choix  :  ");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 6);
	return (choice);
}


void	ft_clients_management(void)
{
	int choice;

	while (1)
	{
		choice = print_clients_menu();
		if (choice == 1)		list_all_clients();
		else if (choice == 2)	add_client();
		else if (choice == 3)	modify_client();
		else if (choice == 4)	del_client();
		else if (choice == 5)	break ;
	}
}


void	list_all_clients()
{
	client	cl;
	FILE	*fileptr = fopen("Clients", "r");

	if (fileptr == NULL)
		return ;
	while (read_one_client(&cl, fileptr) != EOF)
		print_one_client(cl);
	fclose(fileptr);
}

/*
**	**************************************************************************
*/

void	add_client()
{
	client	cl;

	get_client_info(&cl);
	add_this_client(cl, "Clients");
}

void	get_client_info(client *cl)
{
	printf("please write the information of the new client : \n");
	printf("idClient   : ");	scanf("%d", &cl->idClient);
	printf("nom        : ");	scanf("%s", cl->nom);
	printf("prenom     : ");	scanf("%s", cl->prenom);
	printf("cin        : ");	scanf("%d", &cl->cin);
	printf("adresse    : ");	scanf("%s", cl->adresse);
	printf("Telephone  : ");	scanf("%d", &cl->telephone);
}
/*
**	**************************************************************************
*/

void	modify_client()
{
	int		id;
	int		choix;
	int		ret;
	FILE	*file = fopen("Clients", "r");
	client	cl;

	printf("Donner l'id du client : ");	scanf("%d", &id);

	printf("saisir la modification : ");
	printf("\tque voulez-vous modifier?\n");
	printf("\nnom................1\n");
	printf("\tprenom.............2\n");
	printf("\tcin................3\n");
	printf("\tadresse............4\n");
	printf("\ttelephone..........5\n");
	printf("\t\tvotre choix :  ");	scanf("%d", &choix);

	while (1)
	{
		ret = read_one_client(&cl, file);
		if (ret == EOF)
		{
			fclose(file);
			return;
		}
		if (cl.idClient == id)
		{
			fclose(file);
			if (choix >= 1 && choix <= 5)
			{
				del_this_client(cl.idClient);
				
				printf("saisir la modification : ");
				if (choix == 1)			scanf("%s", cl.nom);
				else if (choix == 2)	scanf("%s", cl.prenom);
				else if (choix == 3)	scanf("%d", &cl.cin);
				else if (choix == 4)	scanf("%s", cl.adresse);
				else if (choix == 5)	scanf("%d", &cl.telephone);

				add_this_client(cl, "Clients");
			}
			else
				printf("choix invalid.\n");
			return ;
		}
	}
	fclose(file);
}

/*
**	**************************************************************************
*/

void	del_client()
{
	int		id;

	printf("Donner l'id du contrat que vous souhaitez supprimer : ");
	scanf("%d", &id);
	del_this_client(id);
}

/*
**	**************************************************************************
**	**************************************************************************
*/

void	add_this_client(client cl, char *filename)
{
	FILE	*file = fopen(filename, "a+");

	fprintf(file, "<<\n");	
	fprintf(file, "%d\n", cl.idClient);	
	fprintf(file, "%s\n", cl.nom);	
	fprintf(file, "%s\n", cl.prenom);	
	fprintf(file, "%d\n", cl.cin);	
	fprintf(file, "%s\n", cl.adresse);	
	fprintf(file, "%d\n", cl.telephone);	
	fprintf(file, "/>>\n");	
	fclose(file);
}

int	read_one_client(client *cl, FILE *file)
{
	int ret;
	char line[10];

	ret = fscanf(file, "%s\n", line);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%d\n", &cl->idClient);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%s\n", cl->nom);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%s\n", cl->prenom);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%d\n", &cl->cin);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%s\n", cl->adresse);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%d\n", &cl->telephone);
	if (ret == EOF)	return (ret);
	ret = fscanf(file, "%s\n", line);
	return (ret);
}

void	del_this_client(int	id)
{
	FILE	*ptr1, *ptr2;
	client	temp_client;
	int tmp;

	ptr1 = fopen("Clients", "r");
	ptr2 = fopen("clients_replica.txt", "w");
	fclose(ptr2);

	while (1)
	{
		tmp = read_one_client(&temp_client, ptr1);
		if (tmp == EOF)
			break;
		if (temp_client.idClient != id)
			add_this_client(temp_client, "clients_replica.txt");
	}
	fclose(ptr1);
	remove("Clients");
	rename("clients_replica.txt", "Clients");
}

void	print_one_client(client cl)
{
	printf("____________________________________\n");
	printf("\tidClient  : %d\n", cl.idClient);
	printf("\tnom       : %s\n", cl.nom);
	printf("\tprenom    : %s\n", cl.prenom);
	printf("\tcin       : %d\n", cl.cin);
	printf("\tadresse   : %s\n", cl.adresse);
	printf("\ttelephone : %12.12d\n", cl.telephone);
	printf("____________________________________\n");

}










int		print_cars_menu()
{
	int	choice;

	choice = 0;
	do
	{
		//system("clear");
		printf("\t\t -------------------------------\t\t\t\n");
		printf("\t\t|\tGestion des voiture\t\t|\n");
		printf("\t\t -------------------------------\t\t\t\n\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t|\tList des voitures.................................1\t\t|\n");
		printf("\t|\tAjouter voiture...................................2\t\t|\n");
		printf("\t|\tModifier voiture..................................3\t\t|\n");
		printf("\t|\tsupprimer voiture.................................4\t\t|\n");
		printf("\t|\tretour............................................5\t\t|\n");
		printf("\t -------------------------------------------------------\t\t\t\n");
		printf("\t\t votre choix  :  ");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 6);
	return (choice);
}

/*
** ****************************************************************************
*/

void	ft_cars_management()
{
	int choice;

	do
	{
		choice = print_cars_menu();
		if (choice == 1)
			ft_list_cars();
		else if (choice == 2)
			ft_add_car();
		else if(choice == 3)
			ft_modify_car_info();
		else if(choice == 4)
			ft_delete_car();
	} while (choice != 5);
}

/*
** ****************************************************************************
*/

void	ft_list_cars()
{
	voiture car;
	char line[5];
	int ret;
	FILE *file = fopen("Voitures", "r");

	if (file == NULL)
	{
		printf("ERROR couldn't open cars file\n");
		return ;
	}
	while ((ret = read_one_car_info(file, &car)) != EOF)
	{
		printf("<\n");
		printf("\tnbplaces: %d\n",   car.nbplaces);
		printf("\tprixJour: %d\n",   car.prixJour);
		printf("\tidVoiture: %d\n",  car.idVoiture);
		printf("\tmarque: %s\n",     car.marque);
		printf("\tcouleur: %s\n",    car.couleur);
		printf("\tnomVoiture: %s\n", car.nomVoiture);
		printf("\tEnLocation: %s\n", car.EnLocation);
		printf("/>\n");
	}
	fclose(file);
}

int		read_one_car_info(FILE *file, voiture *car)
{
	char line[100];
	int ret;

	fscanf(file, "%s", line);
	fscanf(file, "%d\n",  &(car->nbplaces));
	fscanf(file, "%d\n",  &(car->prixJour));
	fscanf(file, "%d\n", &(car->idVoiture));
	fscanf(file, "%s\n",    car->marque);
	fscanf(file, "%s\n",   car->couleur);
	fscanf(file, "%s\n", car->nomVoiture);
	fscanf(file, "%s\n", car->EnLocation);
	ret = fscanf(file, "%s", line);
	return (ret);
}

/*
** ****************************************************************************
*/

void	ft_add_car(void)
{
	voiture car;

	get_car_input(&car);
	ft_add_this_car(car, "Voitures");
}

void	get_car_input(voiture *car)
{
	printf("please write the information of this car:\n");
	printf("nbplaces:   "); scanf("%d",   &(car->nbplaces));
	printf("\nprixJour:   "); scanf("%d", &(car->prixJour));
	printf("\nidVoiture:  "); scanf("%d", &(car->idVoiture));
	printf("\nmarque:     "); scanf("%s", car->marque);
	printf("\ncouleur:    "); scanf("%s", car->couleur);
	printf("\nnomVoiture: "); scanf("%s", car->nomVoiture);
	printf("\nEnLocation: "); scanf("%s", car->EnLocation);
}

void	ft_add_this_car(voiture car, char *filename)
{

	FILE *ptr = fopen(filename, "a+");
	fprintf(ptr, "<\n");
	fprintf(ptr, "%d\n",   car.nbplaces);
	fprintf(ptr, "%d\n",   car.prixJour);
	fprintf(ptr, "%d\n",  car.idVoiture);
	fprintf(ptr, "%s\n",     car.marque);
	fprintf(ptr, "%s\n",    car.couleur);
	fprintf(ptr, "%s\n", car.nomVoiture);
	fprintf(ptr, "%s\n", car.EnLocation);
	fprintf(ptr, "/>\n");
	fclose(ptr);
}

/*
** ****************************************************************************
*/

void	ft_modify_car_info()
{
	int num;
	int	nbr;
	int	id;
	int	ret;
	char str[20];
	int	choice;
	voiture car;
	FILE *file = fopen("Voitures", "r");

	print_modify_menu(&id, &choice, &nbr, str);
	while ((ret = read_one_car_info(file, &car)) != EOF)
	{
		if (car.idVoiture == id)
		{
			fclose(file);
			delete_this_car(car);
			if(choice == 1)	car.nbplaces = nbr;
			else if (choice == 2)	car.prixJour = nbr;
			else if (choice == 3)	car.idVoiture = nbr;
			else if (choice == 4)	strcpy(car.marque, str);
			else if (choice == 5) 	strcpy(car.couleur, str);
			else if (choice == 6) 	strcpy(car.nomVoiture, str);
			else if (choice == 7) 	strcpy(car.EnLocation, str);
			file = fopen("Voitures", "a+");
			ft_add_this_car(car, "Voitures");
			break;
		}
	}
	fclose(file);
}

int		print_modify_menu(int *id, int *choice, int *nbr, char *str)
{
	printf("écrivez l'identifiant de la voiture que vous souhaitez modifier.\n--> ");
	scanf("%d", id);
	printf("choisissez le nombre qui correspond à l'attribut que vous souhaitez modifier:\n");
	while (1)
	{
		printf("nbplaces:.........1\n");
		printf("prixJour:.........2\n");
		printf("idVoiture:........3\n");
		printf("marque:...........4\n");
		printf("couleur:..........5\n");
		printf("nomVoiture:.......6\n");
		printf("EnLocation:.......7\n");
		scanf("%d", choice);
		if (*choice > 0 && *choice < 4)
		{
			printf("saisir la modification: ");
			scanf("%d", nbr);
			return (0);
		}
		else if (*choice > 3 && *choice < 8)
		{
			printf("saisir la modification: ");
			scanf("%s", str);
			return (1);
		}
	}
}

/*
** ****************************************************************************
*/

void	ft_delete_car()
{
	int	id;
	int ret;
	voiture car;
	FILE	*file = fopen("Voitures", "r");

	printf("Donner l'id de la voiture tu veut supprimer : ");
	scanf("%d", &id);
	while ((ret = read_one_car_info(file, &car)) != EOF)
	{
		if (car.idVoiture == id)
		{
			fclose(file);
			delete_this_car(car);
			return ;
		}
	}
	fclose(file);
	return ;
}

void	delete_this_car(voiture car)
{
	FILE *fileptr1, *fileptr2;
	voiture temp_car;
	int	end;

	fileptr1 = fopen("Voitures", "r");
	fileptr2 = fopen("replica.txt", "w");
	fclose(fileptr2);

	while (1)
	{
		end = read_one_car_info(fileptr1, &temp_car);
		if (end != EOF && temp_car.idVoiture != car.idVoiture)
			ft_add_this_car(temp_car, "replica.txt");
		if (end == EOF)
			break;
	}
	fclose(fileptr1);
	remove("Voitures");
	rename("replica.txt", "Voitures");
	return ;
}


/*
** ****************************************************************************
*/

void	modifier_car_enLocation(int	id, char *str)
{
	FILE	*file = fopen("Voitures", "r");
	voiture  car;


	while (read_one_car_info(file, &car) != EOF)
	{
		if (car.idVoiture == id)
		{
			fclose(file);
			delete_this_car(car);
			strcpy(car.EnLocation, str);
			ft_add_this_car(car, "Voitures");
			return ;
		}
	}
	fclose(file);
}











int		main(void)
{
	int choice;

	do
	{
		choice = print_menu_principal();
		if (choice == 1)
			ft_rental_management();
	   	else if (choice == 2)
	   		ft_cars_management();
	   	else if (choice == 3)
	   		ft_clients_management();
	} while (choice > 0 && choice < 4);
	return (0);
}

