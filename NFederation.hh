#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>


#include "Democratie.hh"
#include "Tyrannie.hh"

class NFederation: public Democratie, public Tyrannie
{
	public:
        NFederation();
        virtual ~NFederation();

		std::string display() const;
		void sondage();
		std::string get_basic()const;
	private:
		int init();
		char _type;
};
