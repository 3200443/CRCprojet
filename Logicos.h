#ifndef LOGICOS_H
#define LOGICOS_H



class Logicos
{
public:
    Logicos(int difficulte);
    int get_cmt();
    void set_cmt(int nb);
    int get_score_jeu();
    void set_score_jeu();
    int get_val_rand();
    void set_reponse(int nb);
    bool get_reussi();
    int compare();

private:
   int _cmt;
   int _difficulte;
   int _score_jeu;
   int _val_rand;
   int _reponse_user;
   bool _reussi;
};

#endif // LOGICOS_H
