#include "Calcul.h"
#include <cstdlib>


Calcul::Calcul()
{
    _cmt_pts = 0;
    _cmt = 0;

    _val1_equa1 = rand()%15+5;  // 5 - 20
    _val2_equa1 = rand()%15+5;  // 5 - 20
    _resultat_equa1 = _val1_equa1 * _val2_equa1;

    _val1_equa2 = rand()%20+10; // 10 - 30
    _val2_equa2 = rand()%20+10; // 10 - 30
    _resultat_equa2 = _val1_equa2 * _val2_equa2;

    _val1_equa3 = rand()%10+10; // 10 - 20
    _val2_equa3 = rand()%30+10; // 10 - 40
    _resultat_equa3 = _val1_equa3 * _val2_equa3;

    _val1_equa4 = rand()%20;    // 0 - 20
    _val2_equa4 = rand()%50;    // 0 - 50
    _resultat_equa4 = _val1_equa4 * _val2_equa4;

    _val1_equa5 = rand()%10;   // 0 - 10
    _val2_equa5 = rand()%100;   // 0 - 100
    _resultat_equa5 = _val1_equa5 * _val2_equa5;

}

// ====== get_compteurs =========

int Calcul::get_cmt_pts(){
    return _cmt_pts;
}
void Calcul::increment_cmt_pts(){
    _cmt_pts++;
}


int Calcul::get_cmt(){
    return _cmt;
}
void Calcul::increment_cmt(){
    _cmt++;
}

// ====== get_valeurs =========

int Calcul::get_val1_equa1(){
    return _val1_equa1;
}
int Calcul::get_val2_equa1(){
    return _val2_equa1;
}


int Calcul::get_val1_equa2(){
    return _val1_equa2;
}
int Calcul::get_val2_equa2(){
    return _val2_equa2;
}


int Calcul::get_val1_equa3(){
    return _val1_equa3;
}
int Calcul::get_val2_equa3(){
    return _val2_equa3;
}


int Calcul::get_val1_equa4(){
    return _val1_equa4;
}
int Calcul::get_val2_equa4(){
    return _val2_equa4;
}


int Calcul::get_val1_equa5(){
    return _val1_equa5;
}
int Calcul::get_val2_equa5(){
    return _val2_equa5;
}

// ====== get_resultats =========

int Calcul::get_resultat_equa1(){
    return _resultat_equa1;
}
int Calcul::get_resultat_equa2(){
    return _resultat_equa2;
}
int Calcul::get_resultat_equa3(){
    return _resultat_equa3;
}
int Calcul::get_resultat_equa4(){
    return _resultat_equa4;
}
int Calcul::get_resultat_equa5(){
    return _resultat_equa5;
}




