#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <cassert>
#include <QTimer>


#define NB_PAYS_MAX 20


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setRange(5,NB_PAYS_MAX);
    ui->spinBox->setValue(2);
    ui->cnomj->setText("Joueur");
    ui->stackedWidget->setCurrentIndex(0);
    ui->cResultat->setReadOnly(true);
    ui->cfinminijeu->setReadOnly(true);
    ui->cfinminijeu->setAlignment(Qt::AlignHCenter);
    ui->cResultat->setAlignment(Qt::AlignHCenter);
    ui->Enonce_3->setReadOnly(true);
    ui->VACANCES->setReadOnly(true);
    ui->VACANCES->setStyleSheet("text-align: center");
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::green);
    ui->VACANCES->setPalette(*palette);
    ui->VACANCES->setAlignment(Qt::AlignHCenter);
    ui->VACANCES->setText("Est ce reellement le moment de prendre des vacances??");

    // Jeu guerre
    _m_timer = new QTimer(this); // On ne le delete pls on le guarde en permanance pourne pas avoir d erreur avec le connect
    connect(_m_timer, SIGNAL(timeout()), this, SLOT(Jeu_button()));
    connect(_m_timer, SIGNAL(timeout()), this, SLOT(chronometre()));

    ui->nb_clic->setText("0");


    init_gui();
    delete palette;


}
void MainWindow::init_gui()
{
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    ui->pushButton_9->setEnabled(false);
    ui->pushButton_10->setEnabled(false);
    ui->pushButton_11->setEnabled(false);
    ui->pushButton_12->setEnabled(false);
    ui->pushButton_13->setEnabled(false);

    const std::string nom_p[5] = {"curieux","guerre","logicos","matheux","N-A"};
    ui->label_p1->setText(QString::fromStdString(nom_p[0]));
    ui->label_p2->setText(QString::fromStdString(nom_p[1]));
    ui->label_p3->setText(QString::fromStdString(nom_p[2]));
    ui->label_p4->setText(QString::fromStdString(nom_p[3]));
}

MainWindow::~MainWindow()
{
    delete _m_timer;
    delete ui;
}

void MainWindow::on_boption_clicked() // Pour aller dans les options
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_bretour_clicked() //Sortir des options
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::creer_lab()  // Creer un labyrinthe coherant
{
    do
    {
        _l= new Labyrinthe(_difficulte);
        if(gerer_lab(-1) == 4)
        {
            delete _l;
        }
        else
            break;
    }while(1);
}

void MainWindow::inipop() //  initialisation de la popularité
{
    if(ui->rfacile->isChecked())
    {
        _difficulte = 0;
        for(int i = 0; i < 5; i++)
        {
            _popularite[i] = 40;
        }
    }else if(ui->rnormal->isChecked())
    {
        _difficulte = 1;
        for(int i = 0; i < 5; i++)
        {
            _popularite[i] = 30;
        }
    }else
    {
        _difficulte = 2;
        for(int i = 0; i < 5; i++)
            _popularite[i] = 20;
    }
}

void MainWindow::on_bjouer_clicked() //initialisation du monde et de la popularité
{
    std::set<Pays> temp;
    Pays* p;
    _nbpays = ui->spinBox->text().toInt();
    assert(_nbpays>1);
    assert(_nbpays <21);
    do
    {
        switch(rand()%2)
        {
            case(0):
                p = new Federation;
                break;
            case(1):
                p = new NFederation;
                break;
            default:
                QMessageBox::information(0,"ERREUR","Erreur création dans le _monde");
        }
        if( !temp.insert(*p).second )
        {
            delete p;
        }else
        {
            _monde.push_back(p);
        }
    }while(_monde.size()<(unsigned)_nbpays);

    inipop();

    _nomj = ui->cnomj->text().toStdString();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_bretour2_clicked()
{
    _monde.clear();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::mode1(){ //initialisation des minijeux et de l'interface
    _sondages = 2;
    _tour = 0;
    _nomj = ui->cnomj->text().toStdString();

    ui->tabWidget->setCurrentIndex(0);
    ui->lsondage->setText(QString::number(_sondages));
    ui->progressBar->reset();


    for(auto& iter : _monde)
    {
        ui->listWidget->addItem(QString::fromStdString((*iter).get_nom()));
    }


    //popularité
    set_pop();

    ui->ljeunbj->setText(QString::fromStdString(_nomj));
    int temp = 0;
    for(auto& iter : _monde)
    {
        temp += iter->get_nbhab();
    }
    _jeu_logicos = new Logicos(_difficulte);  // facile = 0, normale = 1; difficile = 2;
    _jeu_guerre = new Guerre();
    _jeu_calcul = new Calcul();
    creer_lab();

    ui->ljpopmond->setText(QString::number(temp));
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_btabnoteafficher_clicked()
{
    ui->ctnote->setText(_notes);
}
void MainWindow::set_pop() //affiche la popularité actuelle
{
    // Vérifications
    for(int i = 1; i < MAX_P; i++) {
        if(_popularite[i] > 100 ) _popularite[i] = 100;
        if(_popularite[i] < 0 ) _popularite[i] = 0;
    }
    ui->progressBar_p1->setValue(_popularite[0]);
    ui->progressBar_p2->setValue(_popularite[1]);
    ui->progressBar_p3->setValue(_popularite[2]);
    ui->progressBar_p4->setValue(_popularite[3]);
}

void MainWindow::on_btnotemodifier_clicked()
{
    _notes = ui->ctnote->toPlainText();
}

void MainWindow::on_babandonner_clicked()
{
    _notes = "";
    ui->listWidget->clear(); //TODO: clear() devrait suffir mais valgrind ne semble pas être satisfait, à revoir
    for(auto iter : _monde)
        delete iter;
    _monde.clear();
    delete _l;
    delete _jeu_logicos;
    delete _jeu_guerre;
    delete _jeu_calcul;

    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_clicked() //Lorsque l on clique su le bouton joeur on doit initialiser la suite
{
    ui->bVoyager->setEnabled(false);
    ui->bsonder->setEnabled(false);
    mode1();
}

void MainWindow::on_listWidget_itemSelectionChanged() //gestion de la liste
{
    if(_nbpays > _tour)
    {
        for(auto& iter : _monde)
        {

            if(!(*iter).get_nom().compare(ui->listWidget->currentItem()->text().toStdString()))
            {
                ui->tjeu_2->setText(QString::fromStdString((*iter).get_basic()));
                return;
            }
        }
    }
}

void MainWindow::on_bVoyager_clicked() // progression du jeu principal et determination du minijeu
{
    ui->bVoyager->setEnabled(false);
    ui->bsonder->setEnabled(false);
    ui->progressBar->setValue((_tour+1)*100.0/_nbpays);
    if(_nbpays > _tour)
    {
        for(auto& iter : _monde)
        {

            if(!(*iter).get_nom().compare(ui->listWidget->currentItem()->text().toStdString()))
            {
                if(_nbpays-_tour > 1)
                    delete ui->listWidget->takeItem(ui->listWidget->currentRow());
                else
                    ui->listWidget->reset();
                break;
            }
        }
        _tour ++ ;
        event();
    }
}

void MainWindow::fin() // Determine si le jeu est teminé ou non
{
    if(_nbpays - _tour > 0)
    {
        ui->stackedWidget->setCurrentIndex(3);
        ui->stackedWidget_2->setCurrentIndex(0);
    }
    else
    {
        QPalette *palette = new QPalette();
        if(resultat())
        {
            ui->cResultat->setText("VICTOIRE");
            ui->cResultat->setFont(QFont( "lucida", 20, QFont::Bold, true ));
            palette->setColor(QPalette::Text,Qt::green);
            palette->setColor(QPalette::Base,Qt::blue);
        }else
        {
            ui->cResultat->setText("PERDU");
            ui->cResultat->setFont(QFont( "lucida", 20, QFont::Bold, true ));
            palette->setColor(QPalette::Text,Qt::red);
            palette->setColor(QPalette::Base,Qt::black);
        }
        ui->cResultat->setPalette(*palette);
        ui->stackedWidget_2->setCurrentIndex(1);
        ui->stackedWidget->setCurrentIndex(3);
        delete palette;
    }
}

void MainWindow::on_bfin_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

bool MainWindow::resultat()//determine si le joueur gagne ou non ...
{
// Elections piege a con => 1 chance sur 10 d etre elu.

    if(rand()%10 == 1)
        return 1;
    return 0;
}

void MainWindow::on_listWidget_itemClicked() // Force le clic su l item permet d eviter des soucis lors de suppression notamment
{
    if(_sondages > 0 && ! ui->bVoyager->isEnabled())
        ui->bsonder->setEnabled(true);
    ui->bVoyager->setEnabled(true);
}

void MainWindow::on_bsonder_clicked() // Affiche des informations complementaires
{
    ui->bsonder->setDisabled(true);
    if(_sondages > 0)
    {
        for(auto& iter : _monde)
        {

            if(!(*iter).get_nom().compare(ui->listWidget->currentItem()->text().toStdString()))
            {
                ui->tjeu_2->setText(QString::fromStdString((*iter).display()));
                break;
            }
        }
        _sondages --;
        ui->lsondage->setText(QString::number(_sondages));
    }
}

int MainWindow::deplacement_lab(int i)
{
    switch(i) // deplacement
    {
        case -1:
            return _l->get_suivant(-1);
        case 0:
            return _l->get_suivant(0);
        case 1:
            return _l->get_suivant(1);
        case 2:
            return _l->get_suivant(2);
        case 3:
            return _l->get_precedent();
        default :
            return 14;
    }
}

int MainWindow::gerer_lab(int i) // gestion de l affichage du labyrinthe
{
    char temp = (char)deplacement_lab(i);

    if(temp >= 10) //verification de si on ne se trouve pas a la tete
    {
        ui->blabarriere->setEnabled(false);
        if(temp == 14)
            return 4;
        temp -=10;
    }else // Mise a jour de l affichage des portes
    {
        ui->blabarriere->setEnabled(true);
    }
    switch(temp)
    {
        case 0:
            ui->bporte1->setEnabled(false);
            ui->bporte2->setEnabled(false);
            ui->bporte3->setEnabled(false);
            return temp;
        case 1:
            ui->bporte1->setEnabled(true);
            ui->bporte2->setEnabled(false);
            ui->bporte3->setEnabled(false);
            return temp;
        case 2:
            ui->bporte1->setEnabled(true);
            ui->bporte2->setEnabled(true);
            ui->bporte3->setEnabled(false);
            return temp;
        case 3:
            ui->bporte1->setEnabled(true);
            ui->bporte2->setEnabled(true);
            ui->bporte3->setEnabled(true);
            return temp;
        case 4:
            _popularite[0] += 5;
            delete _l;
            creer_lab();
            fin_minijeu(true);
            return temp;
    }
    return temp;
}

void MainWindow::fin_minijeu(bool r) // Affichage du resultat  d un minijeu
{
    if(r)
        ui->cfinminijeu->setText("REUSSITE");
    else
        ui->cfinminijeu->setText("ECHEC");
    set_pop();
    ui->stackedWidget->setCurrentIndex(5);
}

//Bouton des portes
void MainWindow::on_bfinminijeu_clicked()
{
    fin();
}

void MainWindow::on_bporte1_clicked()
{
    gerer_lab(0);
}

void MainWindow::on_bporte2_clicked()
{
    gerer_lab(1);
}

void MainWindow::on_bporte3_clicked()
{
    gerer_lab(2);
}

void MainWindow::on_blabarriere_clicked()
{
    gerer_lab(3);
}
//determination du prochain minijeu
void MainWindow::event()
{
    int r = rand()%5;
    switch(r)
    {
        case 0:
            ui->stackedWidget->setCurrentIndex(4);
            break;
        case 1:
            ui->stackedWidget->setCurrentIndex(9);
            break;
        case 2:
            ui->stackedWidget->setCurrentIndex(6);
            break;
        case 3:
            ui->stackedWidget->setCurrentIndex(7);
            break;
        case 4:
            ui->stackedWidget->setCurrentIndex(8);
            break;
    }
}

void MainWindow::on_bquit3_clicked()
{
    for(auto iter : _monde)
        delete iter;
}

void MainWindow::on_blababa_clicked()
{
    delete _l;
    creer_lab();
    fin_minijeu(false);
}

void MainWindow::on_bvaccontinuer_clicked()
{
    fin();
}
// ========== Jeu Logicos ============
void MainWindow::on_bvalider_jeu2_valeur_clicked()
{
    if(_jeu_logicos->get_cmt() > 0){

        _jeu_logicos->set_reponse(ui->spin_reponse->value());

        switch (_jeu_logicos->compare()){
            case 0 : ui->conseil->setText("Nombre trouvé !");
                    break;
            case 1 : ui->conseil->setText("Il faut un nombre plus grand !");
                    break;
            case 2 : ui->conseil->setText("Il faut un nombre plus petit !");
                    break;
        }
     }
        QString coup = QString("%1").arg(_jeu_logicos->get_cmt());
        ui->coups_restants->setText(coup);

    if(_jeu_logicos->get_cmt() == 0){
        ui->bvalider_jeu2_valeur->setEnabled(false);

         QString reponse = QString("%1").arg(_jeu_logicos->get_val_rand());
         ui->reponse->setText(reponse);


         if(_jeu_logicos->get_reussi() == true){
             _jeu_logicos->set_score_jeu();
             QString score = QString ("Vous avez gagnez, +%1 points dans la popularite du parti Logicos ").arg(_jeu_logicos->get_score_jeu());
             ui->resul_pop_2->setText(score);
         }else{
              ui->resul_pop_2->setText(" Vous avez perdu, pas de points dans la popularite du parti Logicos ");
         }
    }
}

void MainWindow::on_next_jeu3_clicked()
{
    int temp= _jeu_logicos->get_score_jeu();
    _popularite[2] += temp;
    delete _jeu_logicos;
    _jeu_logicos =  new Logicos(_difficulte);
    init_int_jeu_Log();
    fin_minijeu(temp > 0 ? true : false);
}
// ========== Jeu Guerre ============
void MainWindow::Jeu_button(){


    QString nb_clic = QString("%1").arg(_jeu_guerre->get_cmt());
    ui->nb_clic->setText(nb_clic);

    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    ui->pushButton_9->setEnabled(false);
    ui->pushButton_10->setEnabled(false);
    ui->pushButton_11->setEnabled(false);
    ui->pushButton_12->setEnabled(false);
    ui->pushButton_13->setEnabled(false);

    switch(_jeu_guerre->gene_val_rand()) {

    case 0 : ui->pushButton_5->setEnabled(true);
        break;
    case 1 : ui->pushButton_6->setEnabled(true);
        break;
    case 2 : ui->pushButton_7->setEnabled(true);
        break;
    case 3 : ui->pushButton_8->setEnabled(true);
        break;
    case 4 : ui->pushButton_9->setEnabled(true);
        break;
    case 5 : ui->pushButton_10->setEnabled(true);
        break;
    case 6 : ui->pushButton_11->setEnabled(true);
        break;
    case 7 : ui->pushButton_12->setEnabled(true);
        break;
    case 8 : ui->pushButton_13->setEnabled(true);
        break;
     default : ui->Resultat_3->setText("defaut");
        break;
    }
}

void MainWindow::chronometre(){
    ui->lcdNumber->display(_jeu_guerre->increment_cmt_chrono());
}

void MainWindow::on_go_timer_clicked()
{
    ui->go_timer->setEnabled(false);
    _m_timer->start(500);
}

void MainWindow::Calcul_pop_jeu3(){

    _jeu_guerre->set_temps_final(ui->lcdNumber->value());

    if(_jeu_guerre->get_temps_final() <= 15 ){

        ui->Resultat_3->setText("Temps inferieur a 15 s : popularite parti agressif + 10 points");
        _jeu_guerre->set_score_jeu(10);

    }else if(15 < _jeu_guerre->get_temps_final() && _jeu_guerre->get_temps_final() < 30){
        ui->Resultat_3->setText("Temps compris entre 15 et 30 s :popularite parti agressif + 5 points");
        _jeu_guerre->set_score_jeu(5);

    }else{
        ui->Resultat_3->setText("Temps supérieur a 30 s : pas de points gagnes pour le parti agressif");
    }

}

void MainWindow::Action_jeu_clic(){
    _jeu_guerre->increment_cmt();

    if(_jeu_guerre->get_cmt() >= 10){
        _m_timer->stop();
        Calcul_pop_jeu3();
    }
}

void MainWindow::on_pushButton_13_clicked()
{
    Action_jeu_clic();
     ui->pushButton_13->setEnabled(false);
}

void MainWindow::on_pushButton_8_clicked()
{
    Action_jeu_clic();
     ui->pushButton_8->setEnabled(false);
}

void MainWindow::on_pushButton_5_clicked()
{
    Action_jeu_clic();
     ui->pushButton_5->setEnabled(false);
}

void MainWindow::on_pushButton_11_clicked()
{
    Action_jeu_clic();
     ui->pushButton_11->setEnabled(false);
}

void MainWindow::on_pushButton_7_clicked()
{
    Action_jeu_clic();
     ui->pushButton_7->setEnabled(false);
}

void MainWindow::on_pushButton_6_clicked()
{
    Action_jeu_clic();
     ui->pushButton_6->setEnabled(false);
}

void MainWindow::on_pushButton_12_clicked()
{
    Action_jeu_clic();
     ui->pushButton_12->setEnabled(false);
}

void MainWindow::on_pushButton_9_clicked()
{
    Action_jeu_clic();
     ui->pushButton_9->setEnabled(false);
}

void MainWindow::on_pushButton_10_clicked()
{
    Action_jeu_clic();
     ui->pushButton_10->setEnabled(false);
}

void MainWindow::on_next_jeu3_2_clicked()
{
    _m_timer->stop();
    int temp  = _jeu_guerre->get_score_jeu();
    _popularite[1] += temp;
    delete _jeu_guerre;
    _jeu_guerre = new Guerre();
    init_int_jeu_Gue();
    fin_minijeu((temp > 0 ? true : false));
}

// ========== Jeu Calcul ============

void MainWindow::on_go_jeu_calcul_clicked()
{
    ui->go_jeu_calcul->setEnabled(false);

    ui->valider_calcul1->setEnabled(true);
    ui->valider_calcul2->setEnabled(true);
    ui->valider_calcul3->setEnabled(true);
    ui->valider_calcul4->setEnabled(true);
    ui->valider_calcul5->setEnabled(true);

    ui->res_calcul1->setMaximum(1000);
    ui->res_calcul2->setMaximum(1000);
    ui->res_calcul3->setMaximum(1000);
    ui->res_calcul4->setMaximum(1000);
    ui->res_calcul5->setMaximum(1000);


    QString calc1 = QString (" %1 x %2 ").arg(_jeu_calcul->get_val1_equa1()).arg(_jeu_calcul->get_val2_equa1());
    ui->calcul1->setText(calc1);

    QString calc2 = QString (" %1 x %2 ").arg(_jeu_calcul->get_val1_equa2()).arg(_jeu_calcul->get_val2_equa2());
    ui->calcul2->setText(calc2);

    QString calc3 = QString (" %1 x %2 ").arg(_jeu_calcul->get_val1_equa3()).arg(_jeu_calcul->get_val2_equa3());
    ui->calcul3->setText(calc3);

    QString calc4 = QString (" %1 x %2 ").arg(_jeu_calcul->get_val1_equa4()).arg(_jeu_calcul->get_val2_equa4());
    ui->calcul4->setText(calc4);

    QString calc5 = QString (" %1 x %2 = ").arg(_jeu_calcul->get_val1_equa5()).arg(_jeu_calcul->get_val2_equa5());
    ui->calcul5->setText(calc5);
}

void MainWindow::Fin_jeu_calcul()
{
    QString resu_jeu_calc = QString ("Vous avez gagnez %1 points pour le parti Matheu").arg(_jeu_calcul->get_cmt_pts());
    ui->Resultat_4->setText(resu_jeu_calc);
}

void MainWindow::on_valider_calcul1_clicked()
{
    ui->valider_calcul1->setEnabled(false);
    _jeu_calcul->increment_cmt();

    if(ui->res_calcul1->value() == _jeu_calcul->get_resultat_equa1()){
       _jeu_calcul->increment_cmt_pts();
        ui->valider_calcul1->setText("Bon resultat");
    }else{
        ui->valider_calcul1->setText("Mauvais resultat");
    }

    if(_jeu_calcul->get_cmt() == 5) Fin_jeu_calcul();
}

void MainWindow::on_valider_calcul2_clicked()
{
    ui->valider_calcul2->setEnabled(false);
    _jeu_calcul->increment_cmt();

    if(ui->res_calcul2->value() == _jeu_calcul->get_resultat_equa2()){
        _jeu_calcul->increment_cmt_pts();
        ui->valider_calcul2->setText("Bon resultat");
    }else{
        ui->valider_calcul2->setText("Mauvais resultat");
    }

    if(_jeu_calcul->get_cmt() == 5) Fin_jeu_calcul();
}

void MainWindow::on_valider_calcul3_clicked()
{
    ui->valider_calcul3->setEnabled(false);
    _jeu_calcul->increment_cmt();

    if(ui->res_calcul3->value() == _jeu_calcul->get_resultat_equa3()){
        _jeu_calcul->increment_cmt_pts();
        ui->valider_calcul3->setText("Bon resultat");
    }else{
        ui->valider_calcul3->setText("Mauvais resultat");
    }

    if(_jeu_calcul->get_cmt() == 5) Fin_jeu_calcul();
}

void MainWindow::on_valider_calcul4_clicked()
{
    ui->valider_calcul4->setEnabled(false);
    _jeu_calcul->increment_cmt();

    if(ui->res_calcul4->value() == _jeu_calcul->get_resultat_equa4()){
        _jeu_calcul->increment_cmt_pts();
        ui->valider_calcul4->setText("Bon resultat");
    }else{
        ui->valider_calcul4->setText("Mauvais resultat");
    }

    if(_jeu_calcul->get_cmt() == 5) Fin_jeu_calcul();
}

void MainWindow::on_valider_calcul5_clicked()
{
    ui->valider_calcul5->setEnabled(false);
    _jeu_calcul->increment_cmt();

    if(ui->res_calcul5->value() == _jeu_calcul->get_resultat_equa5()){
        _jeu_calcul->increment_cmt_pts();
        ui->valider_calcul5->setText("Bon resultat");
    }else{
        ui->valider_calcul5->setText("Mauvais resultat");
    }

    if(_jeu_calcul->get_cmt() == 5) Fin_jeu_calcul();
}

void MainWindow::on_next_jeu3_3_clicked()
{
    int temp = _jeu_calcul->get_cmt_pts();
    _popularite[3] += temp;
    delete _jeu_calcul;
    _jeu_calcul = new Calcul();
    init_int_jeu_Cal();
    fin_minijeu(temp > 0 ? true : false);
}

void MainWindow::init_int_jeu_Gue()
{
    ui->go_timer->setEnabled(true);
    ui->nb_clic->setText("");
    ui->Resultat_3->setText("");

    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    ui->pushButton_9->setEnabled(false);
    ui->pushButton_10->setEnabled(false);
    ui->pushButton_11->setEnabled(false);
    ui->pushButton_12->setEnabled(false);
    ui->pushButton_13->setEnabled(false);
  //  ui->lcdNumber->display("0");
}

void MainWindow::init_int_jeu_Cal()
{
     ui->go_jeu_calcul->setEnabled(true);
     ui->calcul1->setText("");
     ui->calcul2->setText("");
     ui->calcul3->setText("");
     ui->calcul4->setText("");
     ui->calcul5->setText("");

     ui->res_calcul1->setValue(0);
     ui->res_calcul2->setValue(0);
     ui->res_calcul3->setValue(0);
     ui->res_calcul4->setValue(0);
     ui->res_calcul5->setValue(0);

     ui->valider_calcul1->setText("Valider");
     ui->valider_calcul2->setText("Valider");
     ui->valider_calcul3->setText("Valider");
     ui->valider_calcul4->setText("Valider");
     ui->valider_calcul5->setText("Valider");

     ui->valider_calcul1->setEnabled(false);
     ui->valider_calcul2->setEnabled(false);
     ui->valider_calcul3->setEnabled(false);
     ui->valider_calcul4->setEnabled(false);
     ui->valider_calcul5->setEnabled(false);

     ui->Resultat_4->setText("");
}
void MainWindow::init_int_jeu_Log()
{
    ui->bvalider_jeu2_valeur->setEnabled(true);
    ui->spin_reponse->setValue(0);
    ui->reponse->setText("");
    ui->coups_restants->setText("");
    ui->resul_pop_2->setText("");
    ui->conseil->setText("");
}

