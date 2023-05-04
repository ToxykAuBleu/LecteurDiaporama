#ifndef LECTEURVUE_H
#define LECTEURVUE_H

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


private:
    Ui::LecteurVue *ui;
};
#endif // LECTEURVUE_H
