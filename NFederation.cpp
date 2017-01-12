#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <cstdlib>

#include "NFederation.hh"
#include "Pays.hh"



int NFederation::init()
{
	switch(rand()%2)
	{
		case 0:
			_type = 'T';
			return 0;
		case 1:
			_type = 'D';
			return 4;
	}
	return 4;
}
NFederation::NFederation() : Pays(1+init()){
	
}
NFederation::~NFederation()
{
	
}

void NFederation::sondage()
{}


std::string NFederation::display() const
{
	//printf("display_Nfederation");	//TODO: wtf??
	return Pays::display() + "\n" + get_basic();
}
std::string NFederation::get_basic()const
{
	if(_type == 'T')
		return Tyrannie::get_basic();
	return Democratie::get_basic();
}