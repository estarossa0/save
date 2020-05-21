#include "header.hpp"

using namespace std;
std::vector<s_livre>	livres;
std::vector<s_client>	clients;
std::vector<s_commande>	commandes;
std::fstream	f_livre;
std::fstream	f_client;
std::fstream	f_commande;
int main()
{

	string line;
	f_livre.open("liste_livres.poc", std::ofstream::trunc);
	f_client.open("liste_clients.poc", std::ofstream::trunc);
	f_commande.open("liste_commandes.poc", std::ofstream::trunc);
	while (1)
	{
		cout << "1.Gestion des livres.\n2.Gestion des clients.\n3.Gestion des commandes.\n4.Quitter.\n";
		getline(cin, line);
		if (line == "1")
			gestion_livre();
		else if (line == "2")
			gestion_client();
		else if (line == "3")
			gestion_commande();
		else if (line == "4")
			exit(0);
		else
		{
			cout << "error input\n";
		}
	}
}
