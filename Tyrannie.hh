#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>


#include "Pays.hh"

class Tyrannie: virtual public Pays
{
	public:
		Tyrannie();
		virtual ~Tyrannie();
		virtual std::string display() const;
		virtual std::string get_basic()const;
	private:
};