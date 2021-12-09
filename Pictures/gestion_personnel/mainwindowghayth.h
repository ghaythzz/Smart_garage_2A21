#ifndef MAINWINDOWGHAYTH_H
#define MAINWINDOWGHAYTH_H
#include "arduino.h"
#include <QMainWindow>
#include "voiture.h"
namespace Ui {
class MainWindowghayth;
}

class MainWindowghayth : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowghayth(QWidget *parent = nullptr);
    ~MainWindowghayth();

private slots:


    void on_pb_ajouter_clicked();

    void on_pb_sup_clicked();

    void on_pb_modifer_clicked();

    void on_combo_currentIndexChanged(const QString &arg1);

    void on_gadour_currentTextChanged(const QString &arg1);

    void on_pb_archv_clicked();

    void on_restaurer_clicked();

    void on_tabzarch_activated(const QModelIndex &index);

    void on_tabvoit_activated(const QModelIndex &index);

    void on_sup_arch_clicked();

    void on_sup1_arch_clicked();

    void on_trimarque_clicked();

    void update_label();
    // ce slot est lancé à chaque réception d'un message de Arduino

    void on_defaut_clicked();

    void on_pb_affecter_clicked();

    void on_pb_archv_2_clicked();



private:
    QByteArray data; // variable contenant les données reçues //arduino
        Arduino A; // objet temporaire
        Voiture v ;
        Voiture Voit;
};

#endif // MAINWINDOWGHAYTH_H
