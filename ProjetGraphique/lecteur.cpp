#include "lecteur.h"
#include <QSqlQuery>

Lecteur::Lecteur()
{
    _numDiaporamaCourant = 0;   // =  le lecteur est vide
    mydb = new Database();
}

void Lecteur::avancer()
{
    if (numDiaporamaCourant() > 0) {
        _posImageCourante = (_posImageCourante+1) % nbImages();
    }
}

void Lecteur::reculer()
{
    if (numDiaporamaCourant() > 0) {
        if (_posImageCourante == 0) {
            _posImageCourante = nbImages()-1;
        } else {
            _posImageCourante = (_posImageCourante-1) % nbImages();
        }
    }
}

void Lecteur::changerDiaporama(unsigned int pNumDiaporama)
{
    // s'il y a un diaporama courant, le vider, puis charger le nouveau Diaporama
    if (numDiaporamaCourant() > 0)
    {
        viderDiaporama();
    }
    _numDiaporamaCourant = pNumDiaporama;
    if (numDiaporamaCourant() > 0)
    {
        chargerDiaporama(); // charge le diaporama courant
    }

}

void Lecteur::chargerDiaporama()
{
    /* Chargement des images associées au diaporama courant
       Dans une version ultérieure, ces données proviendront d'une base de données,
       et correspondront au diaporama choisi */
    Image* imageACharger;

    if (mydb->openDatabase()) {
        QSqlQuery query("SELECT * FROM Diapos");

        for (int i = 0; query.next(); i++) {
            // qDebug() << query.value(0);
            imageACharger = new Image(query.value(0).toInt(), query.value(1).toString().toStdString(), query.value(2).toString().toStdString(), "://" + query.value(3).toString().toStdString());
            _diaporama.push_back(imageACharger);
        }
    }

    // trier le contenu du diaporama par ordre croissant selon le rang de l'image dans le diaporama
    int n = _diaporama.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (_diaporama[j]->getRang() > _diaporama[j + 1]->getRang()) {
                // swap v[j] and v[j+1]
                Image* temp = _diaporama[j];
                _diaporama[j] = _diaporama[j + 1];
                _diaporama[j + 1] = temp;
            }
        }
    }
	 
     _posImageCourante = 0;

     cout << "Diaporama num. " << numDiaporamaCourant() << " selectionne. " << endl;
     cout << nbImages() << " images chargees dans le diaporama" << endl;

}

void Lecteur::viderDiaporama()
{
    if (nbImages () > 0)
    {
        unsigned int taille = nbImages();
        for (unsigned int i = 0; i < taille ; i++)
        {
            _diaporama.pop_back(); /* Removes the last element in the vector,
                                      effectively reducing the container size by one.
                                      AND deletes the removed element */
        }
     _posImageCourante = 0;
    }
    cout << nbImages() << " images restantes dans le diaporama." << endl;

}

void Lecteur::afficher()
{
    /* affiche les information sur le lecteur :
     * 1) vide (si num. de diaporama = 0) OU BIEN  numéro de diaporama affiché
     * 2) Si un diaporama courant est chargé (num. de diaporama > 0), affiche l'image courante OU BIEN 'diaporama vide'
     *     si ce diaporama n'a aucun image */
    if (_numDiaporamaCourant == 0) { cout << "Lecteur vide !" << endl; }
    else {
        cout << "Diaporama num. " << numDiaporamaCourant() << " selectionne." << endl;
        if (nbImages() > 0) {
            Image* img = imageCourante();
            cout << "Image courante: ";
            img->afficher();
            cout << endl;
        } else {
            cout << "Diaporama vide !" << endl;
        }
    }
}

unsigned int Lecteur::nbImages()
{
    return _diaporama.size();
}

Image *Lecteur::imageCourante()
{
    if (nbImages() == 0 || numDiaporamaCourant() == 0) {
        return nullptr;
    } else {
        return _diaporama[_posImageCourante];
    }
}

unsigned int Lecteur::numDiaporamaCourant()
{
    return _numDiaporamaCourant;
}
