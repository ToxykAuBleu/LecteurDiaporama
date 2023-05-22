#ifndef LECTEURVUE_H
#define LECTEURVUE_H

#include <QMessageBox>
#include "lecteur.h"
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class LecteurVue; }
QT_END_NAMESPACE

class LecteurVue : public QMainWindow
{
    Q_OBJECT

public:
    LecteurVue(QWidget *parent = nullptr);
    ~LecteurVue();

private:
    Ui::LecteurVue *ui;
    const char* auteurs = "Virgile, Adrien, Mathieu";
    const char* date = "03/04/2023";
    const char* version = "V3";
    Lecteur _lecteur;
    QLabel *mode;
    QLabel *rang;
    enum EtatLecteur {nonCharge, manuel, automatique};
    EtatLecteur etat = nonCharge;
    QTimer timer;

public slots:
    void chargerDiaporama(); // Charge le diaporama
    void suivant(); // Affiche l'image suivante dans le diaporama
    void suivantClic();// Affiche l'image suivante dans le diaporama, considérant un clic de l'utilisateur sur "suivant"
    void precedentClic(); // Affiche l'image précedente dans le diaporama, considérant un clic de l'utilisateur sur "précédent"
    void demarrerDiapo(); // Passe le diaporama en mode automatique
    void arreterDiapo(); // Passe le diaporama en mode manuel
    void apropos(); //Ouvre boite de dialogue contenant les informations sur le diapo
    void afficherImageCourante(); // Affiche l'image courant du lecteur sur l'interface graphique
    void majStatusBar(); // Met à jour la status bar de l'application.
};

#endif // LECTEURVUE_H
