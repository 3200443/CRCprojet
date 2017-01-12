#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdlib>

#include "Federation.hh"
#include "Democratie.hh"


Federation::Federation()
:Pays(rand()%3+3)
,_id(rand()%5)
{}

void Federation::sondage()
{}


std::string Federation::display() const
{
	//printf("display_federation"); //TODO: de meme???
	return Pays::display() + "\n" + get_basic();
}

Federation::~Federation()
{

}
std::string Federation::get_basic()const
{
	return Democratie::get_basic() + "Federation:" + std::to_string(_id)+"\n";
}