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
    mode = new QLabel();
    rang = new QLabel();
    majStatusBar();
    mode->setAlignment(Qt::AlignLeft);
    rang->setAlignment(Qt::AlignRight);
    ui->statusbar->addWidget(mode, 1);
    ui->statusbar->addWidget(rang, 0);

    // Timer
    timer.setInterval(3000);

    // Connexion des éléments de l'ui
    connect(ui->actionCharger_diaporama, SIGNAL(triggered()), this, SLOT(chargerDiaporama()));
    connect(ui->bArretDiapo, SIGNAL(clicked()), this, SLOT(arreterDiapo()));
    connect(ui->bLancerDiapo, SIGNAL(clicked()), this, SLOT(demarrerDiapo()));
    connect(ui->bSuivant, SIGNAL(clicked()), this, SLOT(suivant()));
    connect(ui->bPrecedent, SIGNAL(clicked()), this, SLOT(precedent()));
    connect(ui->actionA_propos_de, SIGNAL(triggered()), this, SLOT(apropos()));
    connect(ui->actionQuitter, SIGNAL(triggered()), QCoreApplication::instance(), SLOT(quit()), Qt::QueuedConnection);
    connect(&timer, SIGNAL(timeout()), this, SLOT(suivant()));
}

LecteurVue::~LecteurVue() {
    delete ui;
}

void LecteurVue::chargerDiaporama() {
    _lecteur.changerDiaporama(1);
    afficherImageCourante();
    etat = manuel;
    majStatusBar();
}

void LecteurVue::demarrerDiapo() {
    qDebug() << "Démarrage du diaporama" << Qt::endl;
    ui->bArretDiapo->setEnabled(true);
    ui->bLancerDiapo->setEnabled(false);
    etat = automatique;
    timer.start();
    majStatusBar();
}

void LecteurVue::arreterDiapo() {
    qDebug() << "Arrêt du diaporama" << Qt::endl;
    ui->bLancerDiapo->setEnabled(true);
    ui->bArretDiapo->setEnabled(false);
    etat = manuel;
    timer.stop();
    majStatusBar();
}

void LecteurVue::suivant() {
    _lecteur.avancer();
    afficherImageCourante();
    majStatusBar();
}

void LecteurVue::precedent() {
    _lecteur.reculer();
    afficherImageCourante();
    majStatusBar();
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

void LecteurVue::majStatusBar() {
    if (etat == nonCharge) {
        mode->setText("Mode: Non chargé");
        rang->setText("");
    } else if (etat == manuel) {
        mode->setText("Mode: Manuel");
        rang->setText("Rang: " + QString::number(_lecteur.imageCourante()->getRang()) + "/" + QString::number(_lecteur.nbImages()));
    } else {
        mode->setText("Mode : Automatique");
        rang->setText("Rang: " + QString::number(_lecteur.imageCourante()->getRang()) + "/" + QString::number(_lecteur.nbImages()));
    }
}
