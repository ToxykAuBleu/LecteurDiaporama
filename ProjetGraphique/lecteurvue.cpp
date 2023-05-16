#include "lecteurvue.h"
#include "lecteur.h"
#include "ui_lecteurvue.h"
#include <QDebug>
#include <QMessageBox>
LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    //ui->statusbar->showMessage("Mode: Non chargé");

    connect(ui->actionCharger_diaporama, SIGNAL(triggered()), this, SLOT(chargerDiaporama()));
    connect(ui->bArretDiapo, SIGNAL(clicked()), this, SLOT(arreterDiapo()));
    connect(ui->bLancerDiapo, SIGNAL(clicked()), this, SLOT(demarrerDiapo()));
    connect(ui->bSuivant, SIGNAL(clicked()), this, SLOT(suivant()));
    connect(ui->bPrecedent, SIGNAL(clicked()), this, SLOT(precedent()));
    connect(ui->actionA_propos_de, SIGNAL(triggered()), this, SLOT(apropos()));
    connect(ui->actionQuitter, SIGNAL(triggered()), QCoreApplication::instance(), SLOT(quit()), Qt::QueuedConnection);
}

LecteurVue::~LecteurVue() {
    delete ui;
}

void LecteurVue::chargerDiaporama() {
    ui->statusbar->showMessage("Mode: Manuel");
    _lecteur.changerDiaporama(1);
    afficherImageCourante();
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
    _lecteur.avancer();
    afficherImageCourante();
}

void LecteurVue::precedent() {
    _lecteur.reculer();
    afficherImageCourante();
}

void LecteurVue::afficherImageCourante() {
    Image* img = _lecteur.imageCourante();
    QString lien = QString::fromStdString(img->getChemin());
    ui->image->setPixmap(QPixmap(lien));
    QString titre = QString::fromStdString(img->getTitre());
    ui->titreImage->setText(titre);
    QString categorie = QString::fromStdString(img->getCategorie());
    ui->categorie->setText(categorie);
}

void LecteurVue::apropos() {
    QString message = "Les auteurs sont : "+ QString::fromUtf8(auteurs) +"\n";
    message += "La date de création du projet est le : "+ QString::fromUtf8(date) +"\n";
    message += "La version du diaporama est la : "+ QString::fromUtf8(version);
    QMessageBox::information(this, "Information", message);
}

