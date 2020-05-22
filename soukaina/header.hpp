#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

void	gestion_livre();
void	gestion_client();
void 	gestion_commande();
class	s_livre
{
	public:
		std::string	ISBN;
		std::string	titre;
		std::string auteur;
		std::string editeur;
		std::string annee;
		std::string prix;
};

class	s_client
{
	public:
		std::string	IDC;
		std::string	nom;
		std::string adresse;
		std::string	tel;
		std::string anciente;
};

class s_commande
{
	public:
		std::string IDCM;
		std::string IDCCM;
		std::string date;
		std::string total;
};

extern std::vector<s_livre>	livres;
extern std::vector<s_client>	clients;
extern std::vector<s_commande>	commandes;
extern std::fstream	f_livre;
extern std::fstream	f_client;
extern std::fstream	f_commande;


