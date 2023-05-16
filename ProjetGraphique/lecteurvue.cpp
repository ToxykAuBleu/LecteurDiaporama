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
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    // StatusBar
    majStatusBar(false);

    // Connexion des éléments de l'ui
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
    majStatusBar(true);
}

void LecteurVue::arreterDiapo() {
    qDebug() << "Arrêt du diaporama" << Qt::endl;
    ui->bLancerDiapo->setEnabled(true);
    ui->bArretDiapo->setEnabled(false);
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

void LecteurVue::majStatusBar(bool estCharge, unsigned int rangCourant) {
    if (!estCharge) {
        mode = new QLabel("Mode: Non chargé");
        rang = new QLabel("Rang");
    } else {
        mode = new QLabel("Mode: Manuel");
        rang = new QLabel("Rang: "  + QString::number(rangCourant) + "/x");
    }
    mode->setAlignment(Qt::AlignLeft);
    rang->setAlignment(Qt::AlignRight);

    ui->statusbar->removeWidget(mode);
    ui->statusbar->removeWidget(rang);
    ui->statusbar->addWidget(mode, 1);
    ui->statusbar->addWidget(rang, 0);
}
