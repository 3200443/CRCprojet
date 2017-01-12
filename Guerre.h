#ifndef GUERRE_H
#define GUERRE_H


class Guerre
{
public:
    Guerre();

    int gene_val_rand();

    int get_score_jeu();
    void set_score_jeu(int nb);

    int get_cmt();
    void increment_cmt();

    float get_cmt_chrono();
    float increment_cmt_chrono();

    float get_temps_final();
    void set_temps_final(float nb);

private:
    int _val_rand;
    int _cmt;
    float _cmt_chrono;
    float _temps_final;
    int _score_jeu;
};

#endif // GUERRE_H
