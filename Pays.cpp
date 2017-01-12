#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <cassert>
#include <sstream>
#include <QMessageBox>
#include "Pays.hh"
#include "Parti.hh"


///////////////////////////////////////////////////////////////////////////////
std::string Pays::creer_nom()
{
	int i = 0;
    int nbLignes = 0;
    std::string ligne;
    std::string contenu = "!";
    std::ifstream fichier("nom_pays.txt", std::ios::in);
    if(fichier)
    {
        while(std::getline(fichier, ligne)){
            nbLignes++;
        }
        //retour debut fichier
        fichier.clear();
        fichier.seekg(0,std::ios::beg);
        // Affiche nom aléatoire
        int n = rand()%(nbLignes) +1;
        while(i < n){
            std::getline(fichier, contenu);
            i++;
        }
        fichier.close();
    }else
    {
        //printf("ERROR le fichier de nom n'existe pas!!!\n");
        QMessageBox::information(0,"ERREUR","le fichier de nom n'existe pas!!!");
        exit(-1);
    }
    return contenu;
}
///////////////////////////////////////////////////////////////////////////////
std::map<Parti, int> Pays::creer_partis(int n)
{
    assert(n>0);
	std::map<Parti,int> partis;
	while(partis.size() < (unsigned)n)
	{
		partis.insert(std::make_pair(Parti(), rand()%10000+10000));//TODO: TESTER SIZE POUR SAVOIR SI UN NEW EST NECESSAIRE
	}
	return partis;
}
///////////////////////////////////////////////////////////////////////////////
Pays::Pays(int n)
:_nom(creer_nom())
,_partis(creer_partis(n))
{
	_nbHab=0;
	for(const  auto& iter : _partis)
  	{
    	_nbHab+= iter.second;
  	}
    //std::cout<<"pays cree"<<std::endl;
}
///////////////////////////////////////////////////////////////////////////////
bool Pays::operator<(const Pays & p) const
{
	return this->_nom < p._nom;
}
///////////////////////////////////////////////////////////////////////////////
void Pays::sondage()
{

}
///////////////////////////////////////////////////////////////////////////////
std::string Pays::display() const
{
    std::ostringstream oss;
    oss <<  std::endl;
    oss << "Pays : " << this->_nom << std::endl;
    oss << "Nombre d'habitants : " << this->_nbHab << std::endl;
    for(const auto& it : _partis)
    {
         oss <<it.first.display();
         oss << "Nombre d'adherants : " << it.second << std::endl; //TODO: un peu craqué d avoir cette information, par contre ca en serait une bonne pour sondage
    }
    oss << std::endl;
    return oss.str();
}
std::string Pays::get_nom()const
{
    return this->_nom;
}
std::string Pays::get_basic()const
{
    return "";
}
int Pays::get_nbhab()
{
    return this->_nbHab;
}

std::map<Parti, int> Pays::get_partis() const
{
    return this->_partis;
}

Pays::~Pays()
{
    
}
