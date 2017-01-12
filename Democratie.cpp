#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdlib>

#include "Democratie.hh"


Democratie::Democratie() :Pays(rand()%4+1){

}
void Democratie::sondage()
{}


std::string Democratie::display() const
{
	return "";
}
std::string Democratie::get_basic()const
{
	return "Poplation:" + std::to_string(_nbHab) +"\n" + "Democratie\n";
}
Democratie::~Democratie()
{
	
}