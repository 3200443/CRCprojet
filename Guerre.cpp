#include "Guerre.h"
#include <cstdlib>

Guerre::Guerre()
{
    _cmt = 0;
    _cmt_chrono = 0;
    _temps_final = 0;
    _score_jeu = 0;
}

int Guerre::gene_val_rand(){
    return _val_rand = rand()%9;
}

int Guerre::get_score_jeu(){
    return _score_jeu;
}

void Guerre::set_score_jeu(int nb){
    _score_jeu = nb;
}


int Guerre::get_cmt(){
    return _cmt;
}
void Guerre::increment_cmt(){
    _cmt++;
}


float Guerre::get_cmt_chrono(){
    return _cmt_chrono;
}
float Guerre::increment_cmt_chrono(){

    return _cmt_chrono += 0.5;
}


float Guerre::get_temps_final(){
    return _temps_final;
}
void Guerre::set_temps_final(float nb){
    _temps_final = nb;
}

