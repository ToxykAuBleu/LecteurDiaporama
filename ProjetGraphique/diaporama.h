#ifndef DIAPORAMA_H
#define DIAPORAMA_H

#include <QString>

class Diaporama {
    public:
        Diaporama();
        QString getTitre();
        int getVitesse();

    private:
        QString _titre;
        int _vitesseDefilement;
};

#endif // DIAPORAMA_H
