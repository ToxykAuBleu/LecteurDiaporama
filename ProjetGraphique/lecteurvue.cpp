#include "lecteurvue.h"
#include "lecteur.h"
#include "ui_lecteurvue.h"
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>

LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this);

    // Pour bloquer le redimensionnement de la fenetre.
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    // StatusBar
    mode = new QLabel();
    rang = new QLabel();
    majStatusBar(); // On actualise le contenu de la status bar au démarrage de l'application
    // On aligne les labels correctement dans la status bar.
    mode->setAlignment(Qt::AlignLeft);
    rang->setAlignment(Qt::AlignRight);
    // Enfin on les ajoute à la status bar.
    ui->statusbar->addWidget(mode, 1);
    ui->statusbar->addWidget(rang, 0);

    // Timer
    timer.setInterval(2000);

    // Connexion des éléments de l'ui
    // Connexion des boutons
    connect(ui->bArretDiapo, SIGNAL(clicked()), this, SLOT(arreterDiapo()));
    connect(ui->bLancerDiapo, SIGNAL(clicked()), this, SLOT(demarrerDiapo()));
    connect(ui->bSuivant, SIGNAL(clicked()), this, SLOT(suivantClic()));
    connect(ui->bPrecedent, SIGNAL(clicked()), this, SLOT(precedentClic()));

    // Connexion des éléments de la bar d'outils
    connect(ui->actionCharger_diaporama, SIGNAL(triggered()), this, SLOT(chargerDiaporama()));
    connect(ui->actionEnlever_diaporama, SIGNAL(triggered()), this, SLOT(enleverDiaporama()));
    connect(ui->actionVitesse, SIGNAL(triggered()), this, SLOT(changerVitesse()));
    connect(ui->actionA_propos_de, SIGNAL(triggered()), this, SLOT(apropos()));
    connect(ui->actionQuitter, SIGNAL(triggered()), QCoreApplication::instance(), SLOT(quit()), Qt::QueuedConnection);

    // Connexion du timer pour l'affichage de l'image suivante lors du mode automatique
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
    arreterTimer();
    majBoutonsLabels(true);
}

void LecteurVue::enleverDiaporama() {
    _lecteur.changerDiaporama(0);
    etat = nonCharge;
    majStatusBar();
    arreterTimer();
    majBoutonsLabels(false);
}

void LecteurVue::demarrerDiapo() {
    ui->bArretDiapo->setEnabled(true);

    // Pour revenir au début du diaporama
    while (_lecteur.imageCourante()->getRang() != 1) {
        suivant();
    }

    etat = automatique;
    majStatusBar();
    timer.start(); // On démare le timer
}

void LecteurVue::arreterDiapo() {
    etat = manuel;
    majStatusBar();
    arreterTimer();
}

void LecteurVue::changerVitesse() {
    bool ok;
    int vitesse = QInputDialog::getInt(this, QString("Changer de vitesse"), "Vitesse en ms: ", timer.interval(), 0, 60000, 1, &ok);
    // On change l'intervalle du timer seulement s'il a cliqué sur le bouton ok.
    if (ok) {
        timer.setInterval(vitesse);
    }
}

void LecteurVue::suivant() {
    _lecteur.avancer();
    afficherImageCourante();
    majStatusBar();
}

void LecteurVue::suivantClic() {
    _lecteur.avancer();
    afficherImageCourante();
    if (etat == automatique) {
        etat = manuel;
    }
    majStatusBar();
    arreterTimer();
}

void LecteurVue::precedentClic() {
    _lecteur.reculer();
    afficherImageCourante();
    if (etat == automatique) {
        etat = manuel;
    }
    majStatusBar();
    arreterTimer();
}

void LecteurVue::afficherImageCourante() {
    Image* img = _lecteur.imageCourante();
    // On récupère les informations nécessaires en lien avec l'affichage de l'image courante
    QString lien = QString::fromStdString(img->getChemin());
    QString titre = QString::fromStdString(img->getTitre());
    QString categorie = QString::fromStdString(img->getCategorie());
    // On affiche l'image (avec le lien récupéré précédemment) + titre et catégorie
    ui->image->setPixmap(QPixmap(lien));
    ui->titreImage->setText(titre);
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

void LecteurVue::arreterTimer() {
    if (timer.isActive()) {
        ui->bArretDiapo->setEnabled(false);
        timer.stop();
    }
}

void LecteurVue::majBoutonsLabels(bool actif) {
    ui->actionEnlever_diaporama->setEnabled(actif);
    ui->actionVitesse->setEnabled(actif);
    ui->bLancerDiapo->setEnabled(actif);
    ui->bSuivant->setEnabled(actif);
    ui->bPrecedent->setEnabled(actif);

    if (!actif) {
        ui->image->clear();
        ui->titreImage->setText("Titre de l'image");
        ui->titreDiapo->setText("Titre diaporama");
        ui->categorie->setText("Catégorie");
    }
}
