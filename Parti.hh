#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <set>

#define MAX_P 5
//#define THEME_PARTI 3

class Parti
{
	public:
		Parti();
		std::string get_nom()const;
		std::vector<std::string> get_lobby() const;
		bool operator<(const Parti &)const;
		std::string display() const;
		
	private:
		std::string _nom;
        //std::vector<std::string> _lobby;
		//static short _id;

		static const std::string nom_p[MAX_P];
//		static const std::string p_agressif[THEME_PARTI][2];
//		static const std::string p_peace[THEME_PARTI][2];
//		static const std::string p_zinzin[THEME_PARTI][2];
//		static const std::string p_cuisine[THEME_PARTI][2];
//		static const std::string p_maths[THEME_PARTI][2];
};
