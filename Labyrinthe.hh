#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <cassert>


class Labyrinthe
{
	public:
        Labyrinthe(int);
		~Labyrinthe();
        char get_suivant(int);
		char get_precedent();
	private:
	typedef struct noeud
	{
        struct noeud* precedent;
        std::vector<struct noeud*> suivants;
		bool isArrivee;
	}Noeud;
	Noeud* _location;
    Noeud* _tete;
    void creer_lab(int row, Noeud *p);
    void detruire_lab(Noeud *p);
    void creer_lab_fin(Noeud *p);
};
