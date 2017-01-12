#ifndef CALCUL_H
#define CALCUL_H


class Calcul
{
public:
    Calcul();

    int get_cmt_pts();
    void increment_cmt_pts();

    int get_cmt();
    void increment_cmt();

    int get_val1_equa1();
    int get_val2_equa1();

    int get_val1_equa2();
    int get_val2_equa2();

    int get_val1_equa3();
    int get_val2_equa3();

    int get_val1_equa4();
    int get_val2_equa4();

    int get_val1_equa5();
    int get_val2_equa5();

    int get_resultat_equa1();
    int get_resultat_equa2();
    int get_resultat_equa3();
    int get_resultat_equa4();
    int get_resultat_equa5();

private:
    int _cmt_pts;
    int _cmt;

    int _val1_equa1;
    int _val2_equa1;

    int _val1_equa2;
    int _val2_equa2;

    int _val1_equa3;
    int _val2_equa3;

    int _val1_equa4;
    int _val2_equa4;

    int _val1_equa5;
    int _val2_equa5;

    int  _resultat_equa1;
    int  _resultat_equa2;
    int  _resultat_equa3;
    int  _resultat_equa4;
    int  _resultat_equa5;
};

#endif // CALCUL_H
