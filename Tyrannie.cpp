#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdlib>

#include "Tyrannie.hh"


Tyrannie::Tyrannie()
:Pays(1)
{

}
std::string Tyrannie::display() const
{
	return "";
}
std::string Tyrannie::get_basic()const
{
    return "Poplation:" + std::to_string(_nbHab) + "\n" +"Tyrannie\n"; //TODO: POLYMORPHISME
}
Tyrannie::~Tyrannie()
{
	
}
