#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include "Parti.hh"


//#define NB_LOBBY 2


Parti::Parti(){
    int k = rand()%MAX_P;
    switch (k)
    {
        case 0 :
            _nom = nom_p[0];
                break;

        case 1 : 
            _nom = nom_p[1];
            break;

         case 2 : 
            _nom = nom_p[2];
            break;

        case 3 : 
            _nom = nom_p[3];
                break;

        default :
             _nom = nom_p[4];
             break;
    }

}
bool Parti::operator<(const Parti & p)const{
	return this->_nom < p._nom;
}
std::string Parti::get_nom()const{
	return this->_nom;
}
// ======== Ajout perso ==========
std::string Parti::display() const
{
    std::ostringstream oss;
    oss << "Parti : " << this->_nom << std::endl;
    return oss.str();
}

const std::string Parti::nom_p[MAX_P] = {"curieux","guerre","logicos","matheux","N-A"}; // N-A = partie inutile pour vote blanc

