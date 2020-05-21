#include "header.hpp"

using namespace std;

void	afficher_commande()
{
	for (s_commande commande : commandes)
	{
		cout << "IDC: "  + commande.IDCM << endl;
		cout << "IDCCM: " + commande.IDCCM << endl;
		cout << "Date: " + commande.date << endl;
		cout << "Prix: " << commande.prix << endl;
	}
}

void	ajouter_commande()
{
	string		  line;
	s_commande		commande;

	cout << "IDCM: ";
	getline(cin, line);
	commande.IDCM = line;
	cout << "IDCCM: " ;
	getline(cin, line);
	commande.IDCCM = line;
	cout << "Date: ";
	getline(cin, line);
	commande.date = line;
	cout << "Prix: ";
	getline(cin, line);
	commande.prix = std::stoi(line);
	commandes.push_back(commande);
	f_commande << "IDC: "  + commande.IDCM << endl;
	f_commande << "IDCCM: " + commande.IDCCM << endl;
	f_commande << "Date: " + commande.date << endl;
	f_commande << "Prix: " << commande.prix << endl << endl;
}

void	supprimer_commande()
{
	int		index;
	std::string line;
	std::cout << "IDCM du commande: ";
	std::getline(std::cin, line);

	index = 0;
	for (s_commande commande : commandes)
	{
		if (commande.IDCM == line)
		{
			commandes.erase(commandes.begin() + index);
			return ;
		}
		index++;
	}
	std::cout << "commande non trouvé\n";
}

void	rechercher_commande()
{
	std::string line;
	std::cout << "IDC du commande: ";
	std::getline(std::cin, line);

	for (s_commande commande : commandes)
	{
		if (commande.IDCM == line)
		{
			cout << "IDCM: "  + commande.IDCM << endl;
			cout << "IDCCM: " + commande.IDCCM << endl;
			cout << "Adresse: " + commande.date << endl;
			cout << "Prix total: " << commande.prix << endl;
		}
	}
	std::cout << "not found\n";
}

void	update_f_commande()
{
	f_client.close();
	f_client.open("liste_clients.poc" , std::ofstream::trunc);
	for (s_commande commande : commandes)
	{
		f_commande << "IDC: "  + commande.IDCM << endl;
		f_commande << "IDCCM: " + commande.IDCCM << endl;
		f_commande << "Date: " + commande.date << endl;
		f_commande << "Prix: " << commande.prix << endl << endl;
	}
}

void	modifier_commande()
{
	std::string line;
	std::cout << "IDCM du commande:";
	std::getline(std::cin, line);
	for (s_commande commande : commandes)
	{
    int choice;
		if (commande.IDCM == line)
		{
      do {
        std::cout << "Quelle caractéristique souhaitez vous changer: ";
        std::cout << "1. IDCM" << endl;
        std::cout << "2. IDCCM" << endl;
        std::cout << "3. Date" << endl;
        std::cout << "4. Prix total" << endl;
        choice = std::stoi(line);
        if (choice >= 1 && choice <= 4) {
          std::cout << "Nouvelle valeur: ";
          std::getline(std::cin, line);
        }
        switch (choice) {
          case 1:
          {
            commande.IDCM = line;
			update_f_commande();
            return ;
          }
          case 2:
          {
            commande.IDCCM = line;
			update_f_commande();
            return ;
          }
          case 3:
          {
            commande.date = line;
			update_f_commande();
            return ;
          }
          case 4:
          {
            commande.prix = stoi(line);
			update_f_commande();
            return ;
          }
          default: std::cout << "Choix invalide" << endl;
        }
      } while (choice >= 1 && choice <= 4);
		}
	}
	std::cout << "not found\n";
}

void 	gestion_commande()
{
	std::string line;
	while (1)
	{
		std::cout << "1.Afficher la liste des commandes.\n2.Ajouter un commandes.\n3.Supprimer un commandes.\n4.Modifier un commandes.\n5.Rechercher un commandes.\n6.Revenir au menu précédent.\n";
		std::getline(std::cin, line);
		if (line == "1")
			afficher_commande();
		else if (line == "2")
			ajouter_commande();
		else if (line == "3")
			supprimer_commande();
		else if (line == "4")
			modifier_commande();
		else if (line == "5")
			rechercher_commande();
		else if (line == "6")
			return ;
		else
		{
			std::cout << "error input\n";
		}
	}
}
