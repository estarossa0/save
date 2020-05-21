#include "header.hpp"

using namespace std;

void	afficher_client()
{
	for (s_client client : clients)
	{
		cout << "IDC: "  + client.IDC << endl;
		cout << "Nom: " + client.nom << endl;
		cout << "Adresse: " + client.adresse << endl;
		cout << "Tel: " << client.tel << endl;
		cout << "Anciente: " << client.anciente << endl;
	}
}

void	ajouter_client()
{
	string		  line;
	s_client		client;

	cout << "IDC: ";
	getline(cin, line);
	client.IDC = line;
	cout << "Nom: " ;
	getline(cin, line);
	client.nom = line;
	cout << "Adresse: ";
	getline(cin, line);
	client.adresse = line;
	cout << "Tel: ";
	getline(cin, line);
	client.tel = line;
	cout << "Anciente: ";
	getline(cin, line);
	client.anciente = line;
	clients.push_back(client);
	f_client << "IDC: "  + client.IDC << endl;
	f_client << "Nom: " + client.nom << endl;
	f_client << "Adresse: " + client.adresse << endl;
	f_client << "Tel: " << client.tel << endl;
	f_client << "Anciente: " << client.anciente << endl;

}

void	supprimer_client()
{
	int		index;
	std::string line;
	std::cout << "IDC du client: ";
	std::getline(std::cin, line);

	index = 0;
	for (s_client client : clients)
	{
		if (client.IDC == line)
		{
			clients.erase(clients.begin() + index);
			return ;
		}
		index++;
	}
	std::cout << "Client non trouvé\n";
}

void	rechercher_client()
{
	std::string line;
	std::cout << "IDC du client: ";
	std::getline(std::cin, line);

	for (s_client client : clients)
	{
		if (client.IDC == line)
		{
			cout << "IDC: "  + client.IDC << endl;
			cout << "Nom: " + client.nom << endl;
			cout << "Adresse: " + client.adresse << endl;
			cout << "Tel: " << client.tel << endl;
			cout << "Anciente: " << client.anciente << endl;
		}
	}
	std::cout << "not found\n";
}

void	update_f_client()
{
	f_client.close();
	f_client.open("liste_clients.poc" , std::ofstream::trunc);
	for (s_client client : clients)
	{
		f_client << "IDC: "  + client.IDC << endl;
		f_client << "Nom: " + client.nom << endl;
		f_client << "Adresse: " + client.adresse << endl;
		f_client << "Tel: " << client.tel << endl;
		f_client << "Anciente: " << client.anciente << endl;
	}
}

void	modifier_client()
{
	std::string line;
	std::cout << "IDC du client:";
	std::getline(std::cin, line);
	for (s_client client : clients)
	{
    int choice;
		if (client.IDC == line)
		{
      do {
        std::cout << "Quelle caractéristique souhaitez vous changer: ";
        std::cout << "1. IDC" << endl;
        std::cout << "2. Nom" << endl;
        std::cout << "3. Adresse" << endl;
        std::cout << "4. Tel" << endl;
        std::cout << "5. Anciente" << endl;
        choice = std::stoi(line);
        if (choice >= 1 && choice <= 6) {
          std::cout << "Nouvelle valeur: ";
          std::getline(std::cin, line);
        }
        switch (choice) {
          case 1:
          {
            client.IDC = line;
			update_f_client();
            return ;
          }
          case 2:
          {
            client.nom = line;
			update_f_client();
            return ;
          }
          case 3:
          {
            client.adresse = line;
			update_f_client();
            return ;
          }
          case 4:
          {
            client.tel = line;
			update_f_client();
            return ;
          }
          case 5:
          {
            client.anciente = line;
			update_f_client();
            return ;
          }
          default: std::cout << "Choix invalide" << endl;
        }
      } while (choice >= 1 && choice <= 5);
		}
	}
	std::cout << "not found\n";
}

void	gestion_client()
{
	string line;
	while (1)
	{
		cout << "1.Afficher la liste des clients.\n2.Ajouter un clients.\n3.Supprimer un clients.\n4.Modifier un clients.\n5.Rechercher un clients.\n6.Revenir au menu précédent.\n";
		getline(cin, line);
		if (line == "1")
			afficher_client();
		else if (line == "2")
			ajouter_client();
		else if (line == "3")
			supprimer_client();
		else if (line == "4")
			modifier_client();
		else if (line == "5")
			rechercher_client();
		else if (line == "6")
			return;
		else
		{
			cout << "error input\n";
		}
	}
}
