#ifndef CONTROLEUR
#define CONTROLEUR

#include <QtWidgets>
#include <modele.h>

class Controleur : public QWidget
{
    Q_OBJECT
public:
    Controleur(Modele *modele);
public slots:
    void ouvrir();
    void enregistrer();
    void nouveau();
    void imprimer();

    void couleurStylo();
    void epaisseurStylo();
    void brosse();
    void ligne();
    void rectangle();
    void cercle();
    void gomme();
    void rogner();
    void chaton();

    void apropos();
    void modedemploi();

    bool modification();

private:
    int nouvelOutil;
    Modele *modeleUtilise;
};

#endif // CONTROLEUR

