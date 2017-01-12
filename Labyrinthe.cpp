#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <cassert>

#include "Labyrinthe.hh"




void Labyrinthe::creer_lab(int row, Noeud* p)
{
    if(row > 0)
    {
        int lim = rand()%4;
        for(int i = 0 ; i < lim; i++)
            p->suivants.push_back(new Noeud);
        int j=0;
        for(auto & iter : p->suivants)
        {
            iter->precedent = p;
            iter->isArrivee = false;
            creer_lab(row-1,iter);
            j++;
        }
    }
}

void Labyrinthe::creer_lab_fin(Noeud* p)
{
    Noeud* temp;
    int i = 0;
    int lim;
    if(p->suivants.size() > 0)
    {
        lim  = rand()%p->suivants.size();
        for(auto & iter: p->suivants)
        {
            if(i == lim)
            {
                temp = iter;
                break;
            }
            i++;
        }
        creer_lab_fin(temp);
    }else
    {
        p->isArrivee = true;
    }
}

Labyrinthe::Labyrinthe(int difficultee)
{
	_tete = new Noeud;
    _tete -> precedent = NULL;
    _tete ->isArrivee = false;
	_location = _tete;

    switch(difficultee)
    {
        case 0:
            creer_lab(2,_tete);
            break;
        case 1:
            creer_lab(4, _tete);
            break;
        case 2:
            creer_lab(9,_tete);
            break;
        default:
            creer_lab(3,_tete);
            std::cout << "ERROR 1" << std::endl;
    }
    creer_lab_fin(_tete);
}

void Labyrinthe::detruire_lab(Noeud* p)
{
    if(p->suivants.size() > 0)
    {
        for(auto & iter: p->suivants)
        {
            detruire_lab(iter);
        }

    }else
    {
        delete p;
    }
}

Labyrinthe::~Labyrinthe()
{
    detruire_lab(_tete);//cela detruit aussi la tete ne pas la detruire 2x en ajoutant delete _tete ensuite
}

char Labyrinthe::get_suivant(int s)
{
   if(s ==-1)
   {
       if(_location->precedent == NULL)
       {
           if(_location->isArrivee == true)
               return 14;
           return _location->suivants.size() +10;
       }
   }else
   {
       int i = 0;
       for(auto & iter: _location->suivants)
       {
           if(i==s)
           {
                _location = iter;
               break;
           }
           i++;
       }

    }
   if(_location->isArrivee == true)
       return 4;
   return _location->suivants.size();
}

char Labyrinthe::get_precedent()
{
    _location = _location->precedent;
   if(_location->precedent == NULL)
       return _location->suivants.size() +10;
   return _location->suivants.size();
}
