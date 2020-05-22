#include "header.hpp"

using namespace std;

void	afficher_livre()
{
	for (s_livre livre : livres)
	{
		cout << "ISBN: "  + livre.ISBN << endl;
		cout << "titre: " + livre.titre << endl;
		cout << "Auteur: " + livre.auteur << endl;
		cout << "Editeur: " + livre.editeur << endl;
		cout << "annee: " << livre.annee << endl;
		cout << "prix: " << livre.prix << endl;
		cout << "--------------" << endl;
	}
}

void	ajouter_livre()
{
	string		line;
	s_livre		livre;

	cout << "ISBN: "  ;
	std::getline(std::cin, line);
	livre.ISBN = line;
	cout << "titre: " ;
	std::getline(std::cin, line);
	livre.titre = line;
	cout << "Auteur: ";
	std::getline(std::cin, line);
	livre.auteur = line;
	cout << "Editeur: ";
	std::getline(std::cin, line);
	livre.editeur = line;
	cout << "Annee: " ;
	std::getline(std::cin, line);
	livre.annee = line;
	cout << "prix: " ;
	std::getline(std::cin, line);
	livre.prix = line;
	livres.push_back(livre);
	f_livre << "ISBN: "  + livre.ISBN << endl;
	f_livre << "titre: " + livre.titre << endl;
	f_livre << "Auteur: " + livre.auteur << endl;
	f_livre << "Editeur: " + livre.editeur << endl;
	f_livre << "annee: " << livre.annee << endl;
	f_livre << "prix: " << livre.prix << endl;
	f_livre << "--------------" << endl;
}

void	update_f_livre()
{
	f_livre.close();
	f_livre.open("liste_livres.poc" , fstream::out | std::ofstream::trunc);
	for (s_livre livre : livres)
	{
		f_livre << "ISBN: "  + livre.ISBN << endl;
		f_livre << "titre: " + livre.titre << endl;
		f_livre << "Auteur: " + livre.auteur << endl;
		f_livre << "Auteur: " + livre.editeur << endl;
		f_livre << "annee: " << livre.annee << endl;
		f_livre << "prix: " << livre.prix << endl;
		f_livre << "--------------" << endl;
	}
}

void	modifier_livre()
{
	std::string line;
	std::cout << "ISBN de live :";
	std::getline(std::cin, line);
	for (auto & livre : livres)
	{
		int choice;
		if (livre.ISBN == line)
		{
			do {
				std::cout << "1. ISBN" << endl;
				std::cout << "2. titre" << endl;
				std::cout << "3. Auteur" << endl;
				std::cout << "4. Editeur" << endl;
				std::cout << "5. annee" << endl;
				std::cout << "6. prix" << endl;
				std::cout << "Quelle caractéristique souhaitez vous changer: ";
				std::getline(std::cin, line);
				choice = std::stoi(line);
				if (choice >= 1 && choice <= 5) {
					std::cout << "Nouvelle valeur: ";
					std::getline(std::cin, line);
				}
				switch (choice) {
					case 1:
					{
						livre.ISBN = line;
						update_f_livre();
						return ;
					}
					case 2:
					{
						livre.titre = line;
						update_f_livre();
						return ;
					}
					case 3:
					{
						livre.auteur = line;
						update_f_livre();
						return ;
					}
					case 4:
					{
						livre.editeur = line;
						update_f_livre();
						return ;
					}
					case 5:
					{
						livre.annee = line;
						update_f_livre();
						return ;
					}
					case 6:
					{
						livre.prix = line;
						update_f_livre();
						return ;
					}
					default: std::cout << "Choix invalide" << endl;
				}
			} while (choice >= 1 && choice <= 5);
		}
	}
	std::cout << "Non trouvé\n";
}

void	supprimer_livre()
{
	std::string line;
	std::cout << "ISBN de live :";
	std::getline(std::cin, line);
	int		index;

	index = 0;
	for (s_livre livre : livres)
	{

		if (livre.ISBN == line)
		{
			livres.erase(livres.begin() + index);
			update_f_livre();
			return;
		}
		index++;
	}
	std::cout << "Non trouvé\n";
}

void	rechercher_livre()
{
	std::string line;
	std::cout << "ISBN de live :";
	std::getline(std::cin, line);

	for (s_livre livre : livres)
	{
		if (livre.ISBN == line)
		{
			cout << "ISBN: "  + livre.ISBN << endl;
			cout << "titre: " + livre.titre << endl;
			cout << "Auteur: " + livre.auteur << endl;
			cout << "Editeur: " + livre.editeur << endl;
			cout << "annee: " << livre.annee << endl;
			cout << "prix: " << livre.prix << endl;
			return ;
		}
	}
	std::cout << "Non trouvé\n";
}

void	gestion_livre()
{
	string line;
	while (1)
	{
		cout << "1.Afficher la liste des livres.\n2.Ajouter un livre.\n3.Supprimer un livre.\n4.Modifier un livre.\n5.Rechercher un livre.\n6.Revenir au menu précédent.\n";
		getline(cin, line);
		if (line == "1")
			afficher_livre();
		else if (line == "2")
			ajouter_livre();
		else if (line == "3")
			supprimer_livre();
		else if (line == "4")
			modifier_livre();
		else if (line == "5")
			rechercher_livre();
		else if (line == "6")
			return ;
		else
		{
			cout << "error input\n";
		}
	}
}
