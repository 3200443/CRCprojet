#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "Parti.hh"
#include "Pays.hh"
#include "Federation.hh"
#include "NFederation.hh"
#include "Labyrinthe.hh"
#include "Logicos.h"
#include "Guerre.h"
#include "Calcul.h"

#include <QListWidget>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
private slots:

    void on_boption_clicked();

    void on_bretour_clicked();

    void on_bjouer_clicked();

    void on_bretour2_clicked();

    void on_btabnoteafficher_clicked();

    void on_btnotemodifier_clicked();

    void on_babandonner_clicked();

    void on_pushButton_clicked();


    void on_listWidget_itemSelectionChanged();

    void on_bVoyager_clicked();

    void on_bfin_clicked();

    void on_listWidget_itemClicked();

    void on_bsonder_clicked();

    void on_bfinminijeu_clicked();

    void on_bporte1_clicked();

    void on_bporte2_clicked();

    void on_bporte3_clicked();

    void on_blabarriere_clicked();

    void on_bquit3_clicked();

    void on_blababa_clicked();

    void on_bvaccontinuer_clicked();

    void on_bvalider_jeu2_valeur_clicked();

    void on_next_jeu3_clicked();

    void on_go_timer_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_next_jeu3_2_clicked();

    void on_go_jeu_calcul_clicked();

    void on_valider_calcul1_clicked();

    void on_valider_calcul2_clicked();

    void on_valider_calcul3_clicked();

    void on_valider_calcul4_clicked();

    void on_valider_calcul5_clicked();

    void on_next_jeu3_3_clicked();

    void Jeu_button();

    void chronometre();

    void Calcul_pop_jeu3();

    void Action_jeu_clic();

    void Fin_jeu_calcul();

private:
    Ui::MainWindow *ui;

    int _nbpays;
    int _tour; //note beacause count() is really unreliable
    std::string _nomj;
    std::vector<Pays*> _monde;
    int _popularite[5];
    int _difficulte;
    short _sondages;

    QString _notes;
    QTimer *_m_timer; // timer jeu_guerre

    Labyrinthe * _l;
    Logicos *_jeu_logicos;
    Guerre *_jeu_guerre;
    Calcul *_jeu_calcul;

    void mode1();

    void fin();

    bool resultat();

    void inipop();

    int gerer_lab(int i);

    void fin_minijeu(bool r);

    void event();

    void creer_lab();

    void set_pop();

    void init_int_jeu_Gue();

    void init_int_jeu_Cal();

    void init_int_jeu_Log();
};

#endif // MAINWINDOW_HH
