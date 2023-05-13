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

private:
    Ui::LecteurVue *ui;
    const std::string version = "v2";
    const std::string auteurs = "Virgile, Mathieu, Adrien";
    const std::string date = "12/05/2023";
    Lecteur _lecteur;
};
#endif // LECTEURVUE_H
