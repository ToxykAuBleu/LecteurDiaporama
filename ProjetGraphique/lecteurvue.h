#ifndef LECTEURVUE_H
#define LECTEURVUE_H

#include <QMessageBox>
#include "lecteur.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LecteurVue; }
QT_END_NAMESPACE

class LecteurVue : public QMainWindow
{
    Q_OBJECT

public:
    LecteurVue(QWidget *parent = nullptr);
    ~LecteurVue();

public slots:
    void chargerDiaporama(); // Charge le diaporama
    void suivant(); // Affiche l'image suivante dans le diaporama
    void precedent(); // Affiche l'image précedente dans le diaporama
    void demarrerDiapo(); // Passe le diaporama en mode automatique
    void arreterDiapo(); // Passe le diaporama en mode manuel
    void apropos(); //Ouvre boite de dialogue contenant les informations sur le diapo
    void afficherImageCourante(); // Affiche l'image courant du lecteur sur l'interface graphique
    void majStatusBar(bool, unsigned int = 0); // Met à jour la status bar de l'application.

private:
    Ui::LecteurVue *ui;
    const char* auteurs = "Virgile, Adrien, Mathieu";
    const char* date = "13/05/2023";
    const char* version = "V2";
    Lecteur _lecteur;
    QLabel *mode;
    QLabel *rang;
};
#endif // LECTEURVUE_H
