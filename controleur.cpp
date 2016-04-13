#include <controleur.h>
#include <vue.h>

// Initialisation du controleur
Controleur::Controleur(Modele *modele)
{
    modeleUtilise = modele;
    nouvelOutil = 1;
}

// Gestion de la zone de dessin
    void Controleur::ouvrir()
    {
        QString nomFichier = QFileDialog::getOpenFileName(this,"Ouvrir Fichier",QDir::currentPath());
        if (!nomFichier.isEmpty())
            modeleUtilise->ouvrirImage(nomFichier);
    }

    void Controleur::enregistrer()
    {
        QString cheminInitial = QDir::currentPath() + "/Oeuvre.png";
        QString nomFichier = QFileDialog::getSaveFileName(this,"Enregistrer Sous",cheminInitial);
        if (!nomFichier.isEmpty())
            modeleUtilise->enregistrerImage(nomFichier);
    }

    void Controleur::nouveau()
    {
        modeleUtilise->nouveau();
    }

    void Controleur::imprimer()
    {
        modeleUtilise->print();
    }

    bool Controleur::modification()
    {
        if (modeleUtilise->modifie)
        {
           QMessageBox::StandardButton modif = QMessageBox::warning(this,"iChevalet","Vous avez modifié votre oeuvre.\nVoulez-vous sauvegarder ?", QMessageBox::Yes | QMessageBox::No);
           if (modif == QMessageBox::Yes)
               return true;
           else if (modif == QMessageBox::No)
               return false;
        }
        return false;
    }

// Gestion des outils

    void Controleur::couleurStylo()
    {
        QColor nouvelleCouleur = QColorDialog::getColor(modeleUtilise->couleurStylo());
        if (nouvelleCouleur.isValid())
            modeleUtilise->setCouleurStylo(nouvelleCouleur);
    }

    void Controleur::epaisseurStylo()
    {
        bool ok;
        int nouvelleEpaisseur = QInputDialog::getInt(this, "iChevalet", "Selectionner Epaisseur:",modeleUtilise->epaisseurStylo(),1,50,1,&ok);
        if (ok)
            modeleUtilise->setEpaisseurStylo(nouvelleEpaisseur);
    }

    void Controleur::brosse()
    {
        nouvelOutil = 1;
        modeleUtilise->setOutil(nouvelOutil);
    }

    void Controleur::ligne()
    {
        nouvelOutil = 2;
        modeleUtilise->setOutil(nouvelOutil);
    }

    void Controleur::rectangle()
    {
        nouvelOutil = 3;
        modeleUtilise->setOutil(nouvelOutil);
    }

    void Controleur::cercle()
    {
        nouvelOutil = 4;
        modeleUtilise->setOutil(nouvelOutil);
    }

    void Controleur::gomme()
    {
        nouvelOutil = 5;
        modeleUtilise->setOutil(nouvelOutil);
    }

    void Controleur::rogner()
    {
        nouvelOutil = 6;
        modeleUtilise->setOutil(nouvelOutil);
    }

    void Controleur::chaton()
    {
        nouvelOutil = 7;
        modeleUtilise->setOutil(nouvelOutil);
    }

// Documentation
    void Controleur::apropos()
    {
        QMessageBox::information(this,"A propos de iChevalet",
                                 "iChevalet 1.00\n\nCopyright 2015 All rights reserved\n\nCe logiciel a été créé par Benjamin HAOUI "
                                 "& Maite CAZENAVE dans le cadre d'un projet commandité par l'ESME Sudria afin de développer une application de "
                                 "dessin en \nC++ à l'aide du framework graphique Qt5.\n\nNous espérons que l'expérience proposée répondra "
                                 "à toutes vos exigences artistiques.");
    }

    void Controleur::modedemploi()
    {
        QMessageBox::information(this,"iChevalet",
                                      "Palette: Cliquer sur la palette pour sélectionner la couleur du pinceau\n\n"
                                      "Epaisseur: Cliquer sur l'outil épaisseur pour régler l'épaisseur du pinceau\n\n"
                                      "Brosse: Maintener le clic gauche de la souris enfoncé et déplacer la souris afin que le pinceau suive le tracé le souris\n\n"
                                      "Ligne: Maintener le clic gauche de la souris enfoncé et tracé la droite, puis relâcher pour dessiner\n\n"
                                      "Rectangle: Maintener le clic gauche de la souris enfoncé et tracé une diagonale, puis relâcher pour dessiner\n\n"
                                      "Cercle: Maintener le clic gauche de la souris enfoncé et tracé un diamètre, puis relâcher pour dessiner\n\n"
                                      "Chaton: Maintener le clic gauche de la souris enfoncé et tracé une diagonale dans la direction SUD/EST, puis relâcher pour dessiner\n\n"
                                      "Rogner: Maintener le clic gauche de la souris enfoncé et tracé une diagonale dans la direction SUD/EST, puis relâcher pour rogner\n\n"
                                      "Pour redimensionner la zone de dessin, il suffit de redimensionner la fenêtre d'affichage !");
    }
