#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "personnel.h"
#include "connection.h"
#include <QIntValidator>
#include <QDebug>
#include <QTableView>
#include <QSqlQuery>
#include <QString>
#include <QDate>
#include <QDateEdit>
#include <QRect>
#include<QtCharts>
#include<QChartView>
#include "gestionclient.h"
#include "voiture.h"
#include "client.h"
#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
// Used to create stacked bar charts
#include <QtCharts/QHorizontalStackedBarSeries>
#include "client.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlQueryModel>
#include <QDialog>
#include<QSqlQuery>
#include <QSystemTrayIcon>
#include "smtp.h"
#include "ui_mainwindow.h"
#include "excel.h"
#include <QIntValidator>
// Used to create a line chart
#include <QtCharts/QLineSeries>

// Used to change names on axis
#include <QtCharts/QCategoryAxis>

// Used to make Pie Charts
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include "facture.h"
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <QSqlQueryModel>
#include <QPlainTextEdit>
#include <QDateTime>
//Include Stats
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
       switch(ret){
       case(0):qDebug()<< "arduino is available and connected to : "<<A.getarduino_port_name();
           break;
       case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
          break;
       case(-1):qDebug() << "arduino is not available";
       }
        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
        //le slot update_label suite à la reception du signal readyRead (reception des données).



       ui->gadour->addItem("MITSUBISHI");
       ui->gadour->addItem("OPEL");
       ui->gadour->addItem("AUDI");
       ui->gadour->addItem("MERCEDES BENZ");
       ui->gadour->addItem("PEUGEOT");
       ui->gadour->addItem("FIAT");
       ui->gadour->addItem("BMW");

       ui->panne->addItem("MOTEUR");
       ui->panne->addItem("PARE-BRISE");
       ui->panne->addItem("PNEUS");
       ui->panne->addItem("LAVAGE");
       ui->panne->addItem("CIRCUIT ELECTRIQUE");
       ui->panne->addItem("DIESEL");

       ui->combo->setModel(Voit.getcins());
       ui->tabvoit->setModel(v.afficher());
       ui->tabzarch->setModel(v.archive());

       ui->le_cin->setValidator(new QIntValidator(0, 99999999, this));
       ui->l_CIN->setValidator(new QIntValidator(0, 99999999, this));
       ui->le_cin_supp->setValidator(new QIntValidator(0, 99999999, this));
       ui->le_tel->setValidator(new QIntValidator(0, 99999999, this));
       ui->l_tel->setValidator(new QIntValidator(0, 99999999, this));
       ui->le_nbr_conge->setValidator(new QIntValidator(0, 99, this));
       ui->l_nbr_conge->setValidator(new QIntValidator(0, 99, this));
       ui->tab_personnel->QTableView:: setModel(P.afficher_emp());
       setWindowIcon(QIcon(":/logo.png"));

       ui->tab_client->setModel(c.afficher());
           ui->comboBox->setModel(c.afficher());
           ui->tableView_email->setModel(c.afficher());
           ui->le_CINsupp->setValidator(new QIntValidator(0,99999999,this));
            ui->le_cin->setValidator(new QIntValidator(0,99999999,this));
            ui->le_tel->setValidator(new QIntValidator(0,99999999,this));



                ui->facture_affiche->setModel(F.afficher());



}



MainWindow::~MainWindow()
{
    delete ui;
}


/*void MainWindow::on_ahmed_clicked()
{
    son->play();
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_ahmed_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_khalfi_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

}*/
/*void MainWindow::update_label()  //A modifier
{
    data=A.read_from_arduino();
    ui->label_23->setText(data);
    QSqlQuery query;
            query.prepare("SELECT PARKING FROM PERSONNEL WHERE ID='"+data+"'  ");

            if(query.exec())
            {if(query.next())//staff existe
         {ui->label_25->setText(query.value(0).toString()) ;
                QString q=ui->label_25->text();

                if(q=="OUI")
                {
                    A.write_to_arduino("1");

                    ui->label_26->setText("MERCI D'ATTENDRE LORS DE L'OUVERTURE ...") ;
                }
                else { A.write_to_arduino("0");
                 ui->label_26->setText("VOUS N'AVEZ PAS LE DROIT D'ACCES MONSIEUR !") ;}
                }
                else{
                                   ui->label_23->clear();
                         ui->label_25->clear();

                         QMessageBox::critical(nullptr, QObject::tr("PARKING"),
                                     QObject::tr("STAFF N'EXISTE PAS.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);

                 }



                 }



}
*/
void MainWindow::on_pb_ajouter_2_clicked()
{bool test=false;
    int a=v.row_count();
    if(a<15)
    {QSqlQuery query;
    QString matricule=ui->matric->text();
    QString marque=ui->gadour->currentText();
    QString cin_prop=ui->combo->currentText();
    int nb_visites=ui->nbv->text().toInt();
QString modele=ui->iyadh->currentText();
QString panne=ui->panne->currentText();
QString affectation="NON AFFECTEE";
 Voiture V(matricule,marque,nb_visites,cin_prop,modele,panne,affectation);
    test= V.ajouter();

    if(test)
    {ui->tabvoit->setModel(V.afficher());
        ui->tabzarch->setModel(v.archive());
        ui->matric->clear();
        ui->nbv->clear();

        QMessageBox::information(nullptr, QObject::tr("AJOUT"),
                    QObject::tr("AJOUT AVEC SUCCES.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
    { ui->matric->clear();
        ui->nbv->clear();

        QMessageBox::critical(nullptr, QObject::tr("AJOUT"),
                    QObject::tr("ERREUR.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}}
    else
    {QMessageBox::critical(nullptr, QObject::tr("NOTIFICATION"),   //METIER NOTIFICATION
                           QObject::tr("GARAGE SATURE : MAX 5.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel); }




}

void MainWindow::on_pb_sup_22_clicked()
{Voiture v1;
bool test=false;

QSqlQuery query;


     v1.setmatricule(ui->matric_2->text());
     test= v1.supprimer(v1.getmatricule());


    if(test)
    {ui->tabvoit->setModel(v1.afficher());
        ui->tabzarch->setModel(v1.archive());
        ui->b->clear();
        ui->c->clear();
        ui->d->clear();
        ui->e->clear();
        ui->f->clear();
        ui->matric_2->clear();
        QMessageBox::information(nullptr, QObject::tr("sup"),
                    QObject::tr("suppression effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("sup"),
                    QObject::tr("erreur suppression.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}

}

void MainWindow::on_pb_modifer_clicked()
{
    bool test=false;
     QSqlQuery query;
        QString matricule=ui->matric->text();
        QString marque=ui->gadour->currentText();
        QString cin_prop=ui->combo->currentText();
        int nb_visites=ui->nbv->text().toInt();
       QString modele=ui->iyadh->currentText();
        QString panne=ui->panne->currentText();
        QString affectation="NON AFFECTEE";
         Voiture V(matricule,marque,nb_visites,cin_prop,modele,panne,affectation);

         V.setmatricule(ui->matric->text());
          test=V.modifier(V.getmatricule());

        if(test)
        {ui->tabvoit->setModel(V.afficher());

            ui->matric->clear();
           ui->nbv->clear();
            ui->panne->clear();

            QMessageBox::information(nullptr, QObject::tr("MODIFICATION"),
                        QObject::tr("Modification effectuée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

    }
        else
        {ui->matric->clear();

            ui->nbv->clear();

            ui->panne->clear();
            QMessageBox::critical(nullptr, QObject::tr("MODIFICATION"),
                        QObject::tr("Erreur lors de la modification.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}


}



void MainWindow::on_combo_currentIndexChanged(const QString &arg1)
{
     Voit.getcin2((&arg1)->toInt());
}

void MainWindow::on_gadour_currentTextChanged(const QString &arg1)
{if(arg1=="OPEL")
    {ui->iyadh->clear();
        ui->iyadh->addItem("ASTRA");
        ui->iyadh->addItem("CORSA");
        ui->iyadh->addItem("AGILA");
        ui->iyadh->addItem("SENATOR");
        ui->iyadh->addItem("ARENA");

    }
    else if (arg1 == "MITSUBISHI") {
            ui->iyadh->clear();
            ui->iyadh->addItem("CANTER");
            ui->iyadh->addItem("ASX");
            ui->iyadh->addItem("CARISMA");
            ui->iyadh->addItem("LANCER");
            ui->iyadh->addItem("PAJERO");
        }
    else if (arg1 == "MERCEDES BENZ") {
            ui->iyadh->clear();
            ui->iyadh->addItem("AMG");
            ui->iyadh->addItem("GLA");
            ui->iyadh->addItem("GLC");
            ui->iyadh->addItem("G");
            ui->iyadh->addItem("S");
        }
    else if (arg1 == "BMW") {
            ui->iyadh->clear();
            ui->iyadh->addItem("X5");
            ui->iyadh->addItem("SERIE1");
            ui->iyadh->addItem("M5");
            ui->iyadh->addItem("M4");
            ui->iyadh->addItem("Z6");
        }
    else if (arg1 == "FIAT") {
            ui->iyadh->clear();
            ui->iyadh->addItem("PALIO");
            ui->iyadh->addItem("PUNTO");
            ui->iyadh->addItem("UNO");
            ui->iyadh->addItem("GRANDI");
            ui->iyadh->addItem("F500");
        }
    else if (arg1 == "AUDI") {
            ui->iyadh->clear();
            ui->iyadh->addItem("A4");
            ui->iyadh->addItem("RS3");
            ui->iyadh->addItem("E-TRON");
            ui->iyadh->addItem("TT");
            ui->iyadh->addItem("Q3");
        }
    else if (arg1 == "PEUGEOT") {
            ui->iyadh->clear();
            ui->iyadh->addItem("206");
            ui->iyadh->addItem("307");
            ui->iyadh->addItem("407");
            ui->iyadh->addItem("2008");
            ui->iyadh->addItem("508");
        }

}

void MainWindow::on_pb_archv_clicked()
{bool test,test2;
    QString matricule=ui->matric_2->text();
    QString marque=ui->c->text();
    QString cin_prop=ui->d->text();
    int nb_visites=ui->b->text().toInt();
    QString modele=ui->f->text();
    QString panne=ui->e->text();
    QString affectation="NON AFFECTEE";
     Voiture V(matricule,marque,nb_visites,cin_prop,modele,panne,affectation);
      test=V.ajouter_archive();
      test2=V.supprimer(matricule);


      if(test&&test2)
      {ui->tabvoit->setModel(V.afficher());
          ui->tabzarch->setModel(v.archive());
          ui->b->clear();
          ui->c->clear();
          ui->d->clear();
          ui->e->clear();
          ui->f->clear();
          ui->matric_2->clear();
          QMessageBox::information(nullptr, QObject::tr("Historique"),
                      QObject::tr("Archivage effectué.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);


  }
      else
      {
          QMessageBox::critical(nullptr, QObject::tr("Historique"),
                      QObject::tr("erreur Archivage.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);}

}

void MainWindow::on_restaurer_clicked() //restauration de zarch vers gvoit
{
    bool test,test2;
        QString matricule=ui->mat->text();
        QString marque=ui->mar->text();
        QString cin_prop=ui->cin->text();
        int nb_visites=ui->vis->text().toInt();
        QString modele=ui->mod->text();
        QString panne=ui->pan->text();
        QString affectation="NON AFFECTEE";
         Voiture V(matricule,marque,nb_visites,cin_prop,modele,panne,affectation);
          test=V.ajouter();
          test2=V.supprimer_archive(matricule);


          if(test&&test2)
          {ui->tabvoit->setModel(V.afficher());
              ui->tabzarch->setModel(v.archive());
              ui->mat->clear();
              ui->mar->clear();
              ui->mod->clear();
              ui->pan->clear();
              ui->vis->clear();
              ui->cin->clear();
              QMessageBox::information(nullptr, QObject::tr("Historique"),
                          QObject::tr("Archivage effectué.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);


      }
          else
          {
              QMessageBox::critical(nullptr, QObject::tr("Historique"),
                          QObject::tr("erreur Archivage.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);}
}

void MainWindow::on_tabzarch_activated(const QModelIndex &index)
{ QString val=ui->tabzarch->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("SELECT * FROM ZARCHIVE WHERE MATRICULE='"+val+"'  ");

    if(query.exec())
    {while(query.next())
        {ui->mat->setText(query.value(0).toString());

ui->vis->setText(query.value(1).toString());
ui->mod->setText(query.value(2).toString());
ui->cin->setText(query.value(3).toString());
ui->pan->setText(query.value(4).toString());
ui->mar->setText(query.value(5).toString());
        }



    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("sup"),
                    QObject::tr("ERREUR .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}

}

void MainWindow::on_tabvoit_activated(const QModelIndex &index)
{
    QString val=ui->tabvoit->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("SELECT * FROM GVOITURE WHERE MATRICULE='"+val+"'  ");

        if(query.exec())
        {while(query.next())
            {
    ui->matric_2->setText(query.value(0).toString());
    ui->b->setText(query.value(1).toString());
    ui->c->setText(query.value(2).toString());
    ui->d->setText(query.value(3).toString());
    ui->e->setText(query.value(4).toString());
    ui->f->setText(query.value(5).toString());
            }



        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("ARCHIVE"),
                        QObject::tr("ERREUR .\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}

}



void MainWindow::on_sup_arch_clicked() //vider(all columns)
{Voiture v1;
    bool test=false;

      QSqlQuery query;

      test=v1.vider_archive();

        if(test)
        {ui->tabvoit->setModel(v1.afficher());
            ui->tabzarch->setModel(v1.archive());
            ui->mat->clear();
            ui->mar->clear();
            ui->mod->clear();
            ui->pan->clear();
            ui->vis->clear();
            ui->cin->clear();
            QMessageBox::information(nullptr, QObject::tr("ARCHIVE"),
                        QObject::tr("ARCHIVE VIDE.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
    }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("sup"),
                        QObject::tr("ERREUR.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}

}

void MainWindow::on_sup1_arch_clicked() //kaaba bark
{
    Voiture v1;
    bool test=false;

    QSqlQuery query;

         v1.setmatricule(ui->mat->text());
         test= v1.supprimer_archive(v1.getmatricule());

        if(test)
        {ui->tabvoit->setModel(v1.afficher());
            ui->tabzarch->setModel(v1.archive());
            ui->mat->clear();
            ui->mar->clear();
            ui->mod->clear();
            ui->pan->clear();
            ui->vis->clear();
            ui->cin->clear();
            QMessageBox::information(nullptr, QObject::tr("sup"),
                        QObject::tr("suppression effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
   }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("sup"),
                        QObject::tr("erreur suppression.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}

}



void MainWindow::on_trimarque_clicked()
{
    ui->tabvoit->setModel(v.AfficherTrimarque());

}



void MainWindow::on_defaut_clicked()
{
    ui->tabvoit->setModel(v.afficher());
}

void MainWindow::on_pb_affecter_clicked()
{bool test,test2;
    QString ch=ui->e->text();
    if(ch=="MOTEUR")
    {QString val="motoriste";
        QSqlQuery query;
        query.prepare("SELECT CINEMP,NOMEMP,PRENOMEMP,ETAT FROM PERSONNEL WHERE SPECIALITE='"+val+"'  ");

        if(query.exec())
        {if(query.next())//staff existe
     {ui->cinemp->setText(query.value(0).toString()) ;
    ui->nomemp->setText(query.value(1).toString());
    ui->prenomemp->setText(query.value(2).toString());
    QString q=ui->nomemp->text();
    QString etat=query.value(3).toString();
    QString p=ui->matric_2->text();
    if(etat=="DISPONIBLE")
    {
    test=v.update_personnel(q);
    test2=v.update_affectation(p);

    if(test&&test2)
    {ui->tabvoit->setModel(v.afficher());
        QMessageBox::information(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("AFFECTATION EFFECTUEE.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
    else
    {QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("ERREUR.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("PAS DE STAFF DISPONIBLE POUR LE MOMENT.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

}

            else //staff n'existe pas
            {
                QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                            QObject::tr("PAS DE STAFF DISPONIBLE POUR LE MOMENT.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}



}


    }


    else if(ch=="PARE_BRISE")
    {QString val="POSEUR PARE-BRISE";
        QSqlQuery query;
        query.prepare("SELECT CINEMP,NOMEMP,PRENOMEMP,ETAT FROM PERSONNEL WHERE SPECIALITE='"+val+"'  ");

        if(query.exec())
        {if(query.next())//staff existe
     {ui->cinemp->setText(query.value(0).toString()) ;
    ui->nomemp->setText(query.value(1).toString());
    ui->prenomemp->setText(query.value(2).toString());
    QString q=ui->nomemp->text();
    QString etat=query.value(3).toString();
    QString p=ui->matric_2->text();
    if(etat=="DISPONIBLE")
    {
    test=v.update_personnel(q);
    test2=v.update_affectation(p);

    if(test&&test2)
    {ui->tabvoit->setModel(v.afficher());
        QMessageBox::information(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("AFFECTATION EFFECTUEE.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
    else
    {QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("ERREUR.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("PAS DE STAFF DISPONIBLE POUR LE MOMENT.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

}

            else //staff n'existe pas
            {
                QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                            QObject::tr("PAS DE STAFF DISPONIBLE POUR LE MOMENT.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}



}


    }
    else if(ch=="PNEUS")
    {QString val="MONTEUR PNEUMATIQUE";
        QSqlQuery query;
        query.prepare("SELECT CINEMP,NOMEMP,PRENOMEMP,ETAT FROM PERSONNEL WHERE SPECIALITE='"+val+"'  ");

        if(query.exec())
        {if(query.next())//staff existe
     {ui->cinemp->setText(query.value(0).toString()) ;
    ui->nomemp->setText(query.value(1).toString());
    ui->prenomemp->setText(query.value(2).toString());
    QString q=ui->nomemp->text();
    QString etat=query.value(3).toString();
    QString p=ui->matric_2->text();
    if(etat=="DISPONIBLE")
    {
    test=v.update_personnel(q);
    test2=v.update_affectation(p);

    if(test&&test2)
    {ui->tabvoit->setModel(v.afficher());
        QMessageBox::information(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("AFFECTATION EFFECTUEE.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
    else
    {QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("ERREUR.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("PAS DE STAFF DISPONIBLE POUR LE MOMENT.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

}

            else //staff n'existe pas
            {
                QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                            QObject::tr("PAS DE STAFF DISPONIBLE POUR LE MOMENT.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}



}


    }
            else if(ch=="LAVAGE")
    {QString val="LAVEUR";
        QSqlQuery query;
        query.prepare("SELECT CINEMP,NOMEMP,PRENOMEMP,ETAT FROM PERSONNEL WHERE SPECIALITE='"+val+"'  ");

        if(query.exec())
        {if(query.next())//staff existe
     {ui->cinemp->setText(query.value(0).toString()) ;
    ui->nomemp->setText(query.value(1).toString());
    ui->prenomemp->setText(query.value(2).toString());
    QString q=ui->nomemp->text();
    QString etat=query.value(3).toString();
    QString p=ui->matric_2->text();
    if(etat=="DISPONIBLE")
    {
    test=v.update_personnel(q);
    test2=v.update_affectation(p);

    if(test&&test2)
    {ui->tabvoit->setModel(v.afficher());
        QMessageBox::information(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("AFFECTATION EFFECTUEE.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
    else
    {QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("ERREUR.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("PAS DE STAFF DISPONIBLE POUR LE MOMENT.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

}

            else //staff n'existe pas
            {
                QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                            QObject::tr("PAS DE STAFF DISPONIBLE POUR LE MOMENT.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}



}


    }
    else if(ch=="CIRCUIT ELECTRIQUE")
    {QString val="ELECTRICIEN";
        QSqlQuery query;
        query.prepare("SELECT CINEMP,NOMEMP,PRENOMEMP,ETAT FROM PERSONNEL WHERE SPECIALITE='"+val+"'  ");

        if(query.exec())
        {if(query.next())//staff existe
     {ui->cinemp->setText(query.value(0).toString()) ;
    ui->nomemp->setText(query.value(1).toString());
    ui->prenomemp->setText(query.value(2).toString());
    QString q=ui->nomemp->text();
    QString etat=query.value(3).toString();
    QString p=ui->matric_2->text();
    if(etat=="DISPONIBLE")
    {
    test=v.update_personnel(q);
    test2=v.update_affectation(p);

    if(test&&test2)
    {ui->tabvoit->setModel(v.afficher());
        QMessageBox::information(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("AFFECTATION EFFECTUEE.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
    else
    {QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("ERREUR.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("PAS DE STAFF DISPONIBLE POUR LE MOMENT.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

}

            else //staff n'existe pas
            {
                QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                            QObject::tr("PAS DE STAFF DISPONIBLE POUR LE MOMENT.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}



}


    }
    else if(ch=="DIESEL")
    {QString val="DIESILISTE";
        QSqlQuery query;
        query.prepare("SELECT CINEMP,NOMEMP,PRENOMEMP,ETAT FROM PERSONNEL WHERE SPECIALITE='"+val+"'  ");

        if(query.exec())
        {if(query.next())//staff existe
     {ui->cinemp->setText(query.value(0).toString()) ;
    ui->nomemp->setText(query.value(1).toString());
    ui->prenomemp->setText(query.value(2).toString());
    QString q=ui->nomemp->text();
    QString etat=query.value(3).toString();
    QString p=ui->matric_2->text();
    if(etat=="DISPONIBLE")
    {
    test=v.update_personnel(q);
    test2=v.update_affectation(p);

    if(test&&test2)
    {ui->tabvoit->setModel(v.afficher());
        QMessageBox::information(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("AFFECTATION EFFECTUEE.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
    else
    {QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("ERREUR.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);}
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                    QObject::tr("PAS DE STAFF DISPONIBLE POUR LE MOMENT.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

}

            else //staff n'existe pas
            {
                QMessageBox::critical(nullptr, QObject::tr("AFFECTATION"),
                            QObject::tr("PAS DE STAFF DISPONIBLE POUR LE MOMENT.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}



}


    }


}

void MainWindow::on_pb_archv_2_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString val1="AUDI";
    QString val2="BMW";
    QString val3="OPEL";
                                model->setQuery("select * from GVOITURE where MARQUE='"+val1+"' ");
                                float nbr1=model->rowCount();
                                model->setQuery("select * from GVOITURE where MARQUE='"+val2+"' ");
                                float nbr2=model->rowCount();
                                model->setQuery("select * from GVOITURE where MARQUE='"+val3+"' ");
                                //count
                                float nbr3=model->rowCount();
                                float total=nbr1+nbr2+nbr3;
                                QString a=QString("AUDI "+QString::number((nbr1*100)/total,'f',2)+"%" );
                                QString b=QString("BMW "+QString::number((nbr2*100)/total,'f',2)+"%" );
                                QString c=QString("OPEL "+QString::number((nbr3*100)/total,'f',2)+"%" );
                                QPieSeries *series = new QPieSeries();
                                series->append(a,nbr1);
                                series->append(b,nbr2);
                                series->append(c,nbr3);
                        if (nbr1!=0)
                        {QPieSlice *slice = series->slices().at(0);
                         slice->setLabelVisible();
                         slice->setPen(QPen());}
                        if ( nbr2!=0)
                        {
                                 // Add label, explode and define brush for 2nd slice
                                 QPieSlice *slice1 = series->slices().at(1);
                                 //slice1->setExploded();
                                 slice1->setLabelVisible();
                        }
                        if(nbr3!=0)
                        {
                                 // Add labels to rest of slices
                                 QPieSlice *slice2 = series->slices().at(2);
                                 //slice1->setExploded();
                                 slice2->setLabelVisible();
                        }
                                // Create the chart widget
                                QChart *chart = new QChart();
                                // Add data to chart with title and hide legend
                                chart->addSeries(series);
                                chart->setTitle("POURCENTAGE PAR NOMBRE DES VISITES "+ QString::number(total));
                                chart->legend()->hide();
                                // display the chart
                                QChartView *chartView = new QChartView(chart);
                                chartView->setRenderHint(QPainter::Antialiasing);
                                chartView->resize(1000,500);
                                chartView->show();

}
//ahmed sta
void MainWindow::on_pb_ajouter12_clicked()
{

     int cin=ui->le_cin_2->text().toInt();

        QString nom=ui->le_nom_2->text();
        QString prenom=ui->le_prenom_2->text();
          int tel=ui->le_tel_2->text().toInt();
        QString mail=ui->le_mail_2->text();
         QString adresse=ui->le_adresse_2->text();

    Client c (cin,nom,prenom,tel,mail,adresse);
    bool test=c.ajouter();
    if(test)

      { ui->tableView_email->setModel(c.afficher());
        ui->tab_client->setModel(c.afficher());

        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
   }

void MainWindow::on_pb_supprimer_2_clicked()
{
    c.setcin(ui->le_CINsupp->text().toInt());
    bool test=c.supprimer(c.getcin());
    if (test)
    {ui->tableView_email->setModel(c.afficher());
        ui->tab_client->setModel(c.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                              QObject::tr("suppression effectue.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

          }

          else
          QMessageBox::critical(nullptr, QObject::tr("not ok"),
                          QObject::tr("suppression non effectuée.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_pushButton_3_clicked()

{
  ui->tab_client->setModel(c.afficher());

    int cin=ui->le_cin_2->text().toInt();
        QString nom=ui->le_nom_2->text();
        QString prenom=ui->le_prenom_2->text();
        int tel=ui->le_tel_2->text().toInt();
        QString mail=ui->le_mail_2->text();
         QString adresse=ui->le_adresse_2->text();

        bool    test=c.update(cin,nom,prenom,tel,mail,adresse);
        if (test)
              { ui->tab_client->setModel(c.afficher());

                  QMessageBox::information(nullptr,QObject::tr("OK"),
                                       QObject::tr("modification établie"),
                                       QMessageBox::Ok);}
              else{
              QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                      QObject::tr("modification non établie"),
                                      QMessageBox::Cancel);
            }

}




void MainWindow::on_comboBox_activated(const QString &arg1)
{
    int cin = ui->comboBox->currentText().toInt();
         QString id_string= QString::number(cin);
                QSqlQuery query;
                query.prepare("select * from GESTIONCLIENT where CIN ='"+id_string+"'");

                if(query.exec()){

                    while(query.next())
                    {

                   ui->le_cin_2->setText(query.value(0).toString());
                   ui->le_nom_2->setText(query.value(1).toString());
                    ui->le_prenom_2->setText(query.value(2).toString());
                    ui->le_tel_2->setText(query.value(3).toString());
                    ui->le_mail_2->setText(query.value(4).toString());
                    ui->le_adresse_2->setText(query.value(5).toString());


    }}
                else
                    QMessageBox::critical(nullptr, QObject::tr(" echoué"),
                                QObject::tr("Erreur !.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

    }


void MainWindow::on_tri_parcin_clicked()
{
    {QMessageBox msgBox ;
                QSqlQueryModel * model= new QSqlQueryModel();


                   model->setQuery("select * from GESTIONCLIENT order by cin");

                   model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
                   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
                  model->setHeaderData(2, Qt::Horizontal, QObject::tr(" prenom"));
                  model->setHeaderData(3, Qt::Horizontal, QObject::tr("tel"));
                   model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));
                    model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse"));

                            ui->tab_client->setModel(model);
                            ui->tab_client->show();
                            msgBox.setText("Tri avec succés.");
                            msgBox.exec();

            }
}

void MainWindow::on_tri_parnom_clicked()
{
    {
        QMessageBox msgBox ;
               QSqlQueryModel * model= new QSqlQueryModel();


                  model->setQuery("select * from GESTIONCLIENT order by nom ");

                  model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
                  model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
                 model->setHeaderData(2, Qt::Horizontal, QObject::tr(" prenom"));
                 model->setHeaderData(3, Qt::Horizontal, QObject::tr("tel"));
                  model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));
                   model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse"));


                           ui->tab_client->setModel(model);
                           ui->tab_client->show();
                           msgBox.setText("Tri avec succés.");
                           msgBox.exec();
     }
}


void MainWindow::on_tri_parprenom_clicked()
{
    QMessageBox msgBox ;
            QSqlQueryModel * model= new QSqlQueryModel();



               model->setQuery("select * from GESTIONCLIENT order by prenom");

               model->setHeaderData(0, Qt::Horizontal ,QObject::tr("cin"));
               model->setHeaderData(1, Qt::Horizontal ,QObject::tr("nom"));
              model->setHeaderData(2, Qt::Horizontal  ,QObject::tr(" prenom"));
              model->setHeaderData(3, Qt::Horizontal  ,QObject::tr("tel"));
               model->setHeaderData(4, Qt::Horizontal ,QObject::tr("mail"));
                model->setHeaderData(5, Qt::Horizontal,QObject::tr("adresse"));
                        ui->tab_client->setModel(model);
                        ui->tab_client->show();
                        msgBox.setText("Tri avec succés.");
                        msgBox.exec();
}



void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en fichier Excel"), qApp->applicationDirPath (),
                                                                tr("Fichiers d'extension Excel (*.xls)"));
                if (fileName.isEmpty())
                    return;

                EXCEL obj(fileName, "test_bd", ui->tab_client);

                // you can change the column order and
                // choose which colum to export
                obj.addField(0, "cin", "char(20)");
                obj.addField(1, "nom", "char(20)");
                obj.addField(2, "prenom", "char(20)");
                obj.addField(3, "tel", "char(20)");
                obj.addField(4, "mail", "char(20)");
                 obj.addField(5, "adresse", "char(20)");


                int retVal = obj.export2Excel();

                if( retVal > 0)
                {
                    QMessageBox::information(this, tr("FAIS!"),
                                             QString(tr("%1 enregistrements exportés!")).arg(retVal)
                                             );
                }
}

void MainWindow::on_pushButton_send_email_clicked()
{QString from = ui->lineEdit_from_email->text();
    QString to = ui->lineEdit_to_email->text();
    QString subject = ui->lineEdit_subject_email->text();
    QString password = ui->lineEdit_psswrd_email->text();
    QString email_text = ui->textEdit_email->toPlainText();

    Smtp* smtp = new Smtp(from, password);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(from, to, subject, email_text, files);
    else
        smtp->sendMail(from, to, subject, email_text);

}

void MainWindow::on_pushButton_browse_email_clicked()
{
files.clear();

QFileDialog dialog(this);
dialog.setDirectory(QDir::homePath());
dialog.setFileMode(QFileDialog::ExistingFiles);

if (dialog.exec())
    files = dialog.selectedFiles();

QString fileListString;
foreach(QString file, files)
    fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

ui->lineEdit_atchmnt_email->setText( fileListString );
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "email" ), tr( "Message sent.\n\n" ) );
    ui->lineEdit_to_email->clear();
    ui->lineEdit_subject_email->clear();
    ui->lineEdit_atchmnt_email->clear();
    ui->textEdit_email->clear();
    ui->lineEdit_psswrd_email->clear();
}

void MainWindow::on_cin_recherche_2_textChanged(const QString &arg1)
{
    Client c;

            QString rech = ui->cin_recherche_2->text();
                c.recherche(ui->tab_client,rech);
                if (ui->cin_recherche_2->text().isEmpty())
                {
                    ui->tab_client->setModel(c.afficher());
                }
}

void MainWindow::on_pushButton_stat_clicked()
{
    QChart* chart_bar = c.chart_pie();
        QChartView* chart_view_bar = new QChartView(chart_bar, ui->label_stat );
        chart_view_bar->setRenderHint(QPainter::Antialiasing);
        chart_view_bar->setMinimumSize(400,400);
        chart_view_bar->show();
}


//-----------------ajout----------
void MainWindow::on_pb_ajouter_clicked()
{
    int cin_emp=ui->le_cin-> text().toInt();
    QString nom_emp=ui->le_nom->text();
    QString prenom_emp=ui->le_prenom->text();
    QString id_emp=ui->le_mail->text();
    QString parking_emp=ui->le_adresse->text();
    int tel_emp=ui->le_tel->text().toInt();
    int nbr_conge_emp=ui->le_nbr_conge->text().toInt();
    QString etat_emp=ui->cb_ajouter->currentText();
    QString Specialite_emp=ui->cb_genre->currentText();
    QDate date_emp=ui->dateEdit->date();
    personnel P( cin_emp , nom_emp , prenom_emp , id_emp, parking_emp , nbr_conge_emp , tel_emp , etat_emp, Specialite_emp,date_emp);
    bool test=P.ajouter_emp();
    ui->tab_personnel->QTableView:: setModel(P.afficher_emp());
    QMessageBox msgBox;

      if(test)
       {
           msgBox.setText("AJOUT AVEC SUCCES.");
           msgBox.exec();
      }
        else
      {
          msgBox.setText("ECHEC DE L'AJOUT");
          msgBox.exec();
      }


}

//----------------supprimer------------

void MainWindow::on_pb_supprimer_12_clicked()
{
    personnel P1;
    P1.setcin_emp(ui->le_cin_supp->text().toInt());
    bool test=P1.supprimer_emp(P1.getcin_emp());
    ui->tab_personnel->QTableView:: setModel(P.afficher_emp());
    QMessageBox msgBox;

      if(test)
       {
           msgBox.setText("supprimer avec succes.");
           msgBox.exec();
      }
        else
      {
          msgBox.setText("echec de suppression");
          msgBox.exec();
      }

}
//---------------------modifier----------
void MainWindow::on_pushButton_9_clicked()
{
    ui->tab_personnel->QTableView::setModel(P.afficher_emp());
    bool test=P.modifier_emp(ui->l_CIN->text().toInt(),ui->l_nom->text(),ui->l_prenom->text(),ui->l_mail->text(),ui->l_adresse->text(),ui->l_tel->text().toInt(),ui->l_nbr_conge->text().toInt(),ui->cb_modifier->currentText(),ui->cb_genre_modifier->currentText(),ui->dateEdit->date());
    if (test)
              {
                      ui->tab_personnel->QTableView::setModel(P.afficher_emp());

                  QMessageBox::information(nullptr,QObject::tr("OK"),
                                       QObject::tr("modification établie"),
                                       QMessageBox::Ok);}
              else{
              QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                      QObject::tr("modification non établie"),
                                      QMessageBox::Cancel);}
}

//-----------------tri
void MainWindow::on_trinom_toggled(bool checked)
{
    if (checked == true){
            ui->tab_personnel->QTableView::setModel(P.trierparnom_emp());
        } else {
             ui->tab_personnel->QTableView::setModel(P.afficher_emp());
        }
    }



void MainWindow::on_tricin_toggled(bool checked)
{
    if (checked == true){
            ui->tab_personnel->QTableView::setModel(P.trier_emp());
        } else {
             ui->tab_personnel->QTableView::setModel(P.afficher_emp());
        }
}
//----------------------recherche
void MainWindow::on_recherche_pb_clicked()
{
    QString nom_emp = ui->lineEdit_chercher->text();
    ui->tab_personnel->QTableView::setModel(P.recherche_emp(nom_emp));
}
//------------------pdf
void MainWindow::on_pb_pdf_clicked()
{
    bool test=false;
       test=P.genererPDFproduit_emp();
       if(test)

           {
           ui->tab_personnel->QTableView::setModel(P.afficher_emp());
           QMessageBox::information(nullptr, QObject::tr("créé"),

                               QObject::tr(" PDF créé.\n"

                                           "Click Cancel to exit."), QMessageBox::Cancel);}
       else

           {

               QMessageBox::critical(nullptr, QObject::tr("non créé"),

                           QObject::tr("PDF non créé !.\n"

                                       "Click Cancel to exit."), QMessageBox::Cancel);



   }
}
//-------------------statistique
void MainWindow::on_pb_statistique_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                                model->setQuery("select * from PERSSONEL where NBR_CONGEEMP < 7 ");
                                float nbr1=model->rowCount();
                                model->setQuery("select * from PERSSONEL where NBR_CONGEEMP  between 2 and 5 ");
                                float nbr2=model->rowCount();
                                model->setQuery("select * from PERSSONEL where NBR_CONGEEMP >3 ");
                                float nbr3=model->rowCount();
                                float total=nbr1+nbr2+nbr3;
                                QString a=QString(" nombre de conge_emp inférieur  à 7 "+QString::number((nbr1*100)/total,'f',2)+"%" );
                                QString b=QString("nombre de congee_emp entre 2 et 5 "+QString::number((nbr2*100)/total,'f',2)+"%" );
                                QString c=QString(" nombre de congee_emp plus que 3 "+QString::number((nbr3*100)/total,'f',2)+"%" );
                                QPieSeries *series = new QPieSeries();
                                series->append(a,nbr1);
                                series->append(b,nbr2);
                                series->append(c,nbr3);
                        if (nbr1!=0)
                        {QPieSlice *slice = series->slices().at(0);
                         slice->setLabelVisible();
                         slice->setPen(QPen());}
                        if ( nbr2!=0)
                        {
                                 // Add label, explode and define brush for 2nd slice
                                 QPieSlice *slice1 = series->slices().at(1);
                                 //slice1->setExploded();
                                 slice1->setLabelVisible();
                        }
                        if(nbr3!=0)
                        {
                                 // Add labels to rest of slices
                                 QPieSlice *slice2 = series->slices().at(2);
                                 //slice1->setExploded();
                                 slice2->setLabelVisible();
                        }
                                // Create the chart widget
                                QChart *chart = new QChart();
                                // Add data to chart with title and hide legend
                                chart->addSeries(series);
                                chart->setTitle("Pourcentage Par nombre  :nombre de congee_emp "+ QString::number(total));
                                chart->legend()->hide();
                                // Used to display the chart
                                QChartView *chartView = new QChartView(chart);
                                chartView->setRenderHint(QPainter::Antialiasing);
                                chartView->resize(1000,500);
                                chartView->show();
}


void MainWindow::on_ahmed_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}



void MainWindow::on_khalfi_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

void MainWindow::on_ghayth_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);

}

void MainWindow::on_zriba_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);

}


void MainWindow::on_ajouter_button_clicked()
{
int reference=ui->le_reference->text().toInt();
QString client=ui->comboBox_23->currentText();
 float montant=ui->le_montant->text().toFloat();

 QString caissier=ui->le_caissier->text();

 QString date=ui->date_time->text();
 QString achats=ui->lineEdit_6->text();
  Facture F(reference,client,montant,caissier,date,achats);
bool test=F.ajouter();
if(test)
{

    QMessageBox::information(nullptr,QObject::tr("OK"),
    QObject::tr("Ajout effectué\n"
    "click Cancel to exit"),QMessageBox::Cancel);
     ui->facture_affiche->setModel(F.afficher());//Refresh
}
else
    QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
    QObject::tr("Ajout not effectué.\n"
    "Click Cancel to exit"), QMessageBox::Cancel);
}

void MainWindow::on_pb_supprimer_clicked()

{
  Facture F;
  F.setreference(ui->le_reference->text().toInt());
  bool test=F.supprimer(F.getrefernce());

  if(test)
  {

      QMessageBox::information(nullptr,QObject::tr("OK"),
      QObject::tr("Suppression avec succes.\n"
      "click Cancel to exit"),QMessageBox::Cancel);
      ui->facture_affiche->setModel(F.afficher());
  }
  else
      QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
      QObject::tr("Echec de suppression.\n"
      "Click Cancel to exit"), QMessageBox::Cancel);
}

void MainWindow::on_pb_modifier_clicked()
{

    int reference=ui->le_reference->text().toInt();//
     float montant=ui->le_montant->text().toFloat();
     QString client=ui->comboBox_23->currentText();
     QString caissier=ui->le_caissier->text();
     QString achats=ui->lineEdit_6->text();
     QString date;



    Facture F;
           bool test;
           test=F.modifier(reference,client,montant,caissier,date,achats);
           if(test)
           {
              ui->facture_affiche->setModel(F.afficher());

              QMessageBox::information(nullptr,QObject::tr("OK"),
                QObject::tr(" stade modifé") ,QMessageBox::Ok);

             }else

                 QMessageBox::critical(nullptr,QObject::tr("Not Ok"),
                   QObject::tr("Erreur !.\n""Click Ok to exit."), QMessageBox::Ok);
    }
void MainWindow::stats(QString table,QString critere,int valeur1,int valeur2,QString unite)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString valeur1QString=QString::number(valeur1);
    QString valeur2QString=QString::number(valeur2);

                model->setQuery("select * from "+table+" where "+critere+"<"+valeur1QString);

                float countFirst=model->rowCount();
                model->setQuery("select * from "+table+" where " +critere+" between " +valeur1QString+ " and "+valeur2QString);
                float countSecond=model->rowCount();
                model->setQuery("select * from "+table+" where " +critere+">"+valeur2QString);
                float countThird=model->rowCount();
                float total=countFirst+countSecond+countThird;
                QString a=QString("moins de "+valeur1QString+" "+unite+" "+QString::number((countFirst*100)/total,'f',2)+"%" );

                QString b=QString("entre "+valeur1QString+ " et " +valeur2QString+" "+unite+" "+QString::number((countSecond*100)/total,'f',2)+"%" );
                QString c=QString("Plus que "+valeur2QString +" "+unite+" "+QString::number((countThird*100)/total,'f',2)+"%" );
                QPieSeries *series = new QPieSeries();
                series->append(a,countFirst);
                series->append(b,countSecond);
                series->append(c,countThird);
        if (countFirst!=0)
        {QPieSlice *slice = series->slices().at(0);
         slice->setLabelVisible();
         slice->setPen(QPen());}
        if ( countSecond!=0)
        {
                 // Add label, explode and define brush for 2nd slice
                 QPieSlice *slice1 = series->slices().at(1);
                 //slice1->setExploded();
                 slice1->setLabelVisible();
        }
       if(countThird!=0)
        {
                 // Add labels to rest of slices
                 QPieSlice *slice2 = series->slices().at(2);
                 //slice1->setExploded();
                 slice2->setLabelVisible();
        }
                // Create the chart widget
                QChart *chart = new QChart();
                // Add data to chart with title and hide legend
                chart->addSeries(series);
                if(critere=="Montant")
                    critere="montant";
                chart->setTitle("Pourcentage Par " +critere+":Nombre Des " +table+" :" +QString::number(total));
                chart->legend()->hide();
                // Used to display the chart
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                chartView->resize(1000,500);
                chartView->show();
}


void MainWindow::on_statsmontant_clicked()
{
    stats("FACTURE","MONTANT",10,1000,"DT");
}



void MainWindow::on_pushButton_8_clicked() //imprimer
{

}






void MainWindow::on_lineEdit_9_textChanged(const QString &arg1) //recherche
{
    Facture c;
            if(ui->lineEdit_9->text() == "")
                {
                    ui->facture_affiche_2->setModel(c.afficher());
                }
                else
                {
                     ui->facture_affiche_2->setModel(c.rechercher(ui->lineEdit_9->text()));
                }
}



void MainWindow::on_comboBox_23_currentIndexChanged(const QString &arg1)
{
    //Facture.getcin20((&arg1)->toInt());

}