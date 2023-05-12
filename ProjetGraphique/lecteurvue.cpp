#include "lecteurvue.h"
#include "lecteur.h"
#include "ui_lecteurvue.h"
#include <QDebug>

LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this);
    //ui->statusbar->showMessage("Mode: Non chargé");

    connect(ui->actionCharger_diaporama, SIGNAL(triggered()), this, SLOT(chargerDiaporama()));
    connect(ui->bArretDiapo, SIGNAL(clicked()), this, SLOT(arreterDiapo()));
    connect(ui->bLancerDiapo, SIGNAL(clicked()), this, SLOT(demarrerDiapo()));
    connect(ui->bSuivant, SIGNAL(clicked()), this, SLOT(suivant()));
    connect(ui->bPrecedent, SIGNAL(clicked()), this, SLOT(precedent()));
}

LecteurVue::~LecteurVue() {
    delete ui;
}

void LecteurVue::chargerDiaporama() {
    qDebug() << "Je charge la diaporama." << Qt::endl;
    ui->statusbar->showMessage("Mode: Manuel");
    _lecteur.changerDiaporama(1);
    QString lien = QString::fromStdString(_lecteur.imageCourante()->getChemin());
    ui->image->setPixmap(QPixmap(lien));
}

void LecteurVue::demarrerDiapo() {
    qDebug() << "Démarrage du diaporama" << Qt::endl;
    ui->bArretDiapo->setEnabled(true);
    ui->bLancerDiapo->setEnabled(false);
    ui->statusbar->showMessage("Mode: Automatique");
}

void LecteurVue::arreterDiapo() {
    qDebug() << "Arrêt du diaporama" << Qt::endl;
    ui->bLancerDiapo->setEnabled(true);
    ui->bArretDiapo->setEnabled(false);
    ui->statusbar->showMessage("Mode: Manuel");
}

void LecteurVue::suivant() {
    qDebug() << "Image suivante" << Qt::endl;
}

void LecteurVue::precedent() {
    qDebug() << "Image précedente" << Qt::endl;
}

/* Pour afficher tous les élements présent dans l'ui.
    ui->bLancerDiapo->show();
    ui->bPrecedent->show();
    ui->bSuivant->show();
    ui->bArretDiapo->show();
    ui->categorie->show();
    ui->titreDiapo->show();
    ui->titreImage->show();
    ui->image->show();
*/

/* Pour cacher tous les éléments présent dans l'ui.
    ui->bLancerDiapo->hide();
    ui->bPrecedent->hide();
    ui->bSuivant->hide();
    ui->bArretDiapo->hide();
    ui->categorie->hide();
    ui->titreDiapo->hide();
    ui->titreImage->hide();
    ui->image->hide();
*/
