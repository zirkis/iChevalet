#include <vue.h>

// Création de la fenêtre principale
    Vue::Vue()
    {
        // Initialisation du modele et du controleur
            modele = new Modele;
            controleur = new Controleur(modele);

        // Configuration de la zone centrale de la fenetre principale
            setCentralWidget(modele);
            centralWidget()->setCursor(Qt::CrossCursor);

        // Actions
            QAction *nouveau = new QAction("&Nouveau",this);
            QAction *ouvrir = new QAction("&Ouvrir",this);
            QAction *enregistrer = new QAction("&Enregistrer",this);
            QAction *imprimer = new QAction("&Imprimer",this);
            QAction *fermer = new QAction("&Fermer",this);
            QAction *pleinecran = new QAction("&Plein Ecran",this);
            QAction *minimiser = new QAction("&Minimiser",this);
            QAction *brosse = new QAction("&Brosse",this);
            QAction *ligne = new QAction("&Ligne",this);
            QAction *rectangle = new QAction("&Rectangle",this);
            QAction *cercle = new QAction("&Cercle",this);
            QAction *palette = new QAction("&Palette",this);
            QAction *epaisseur = new QAction("&Epaisseur",this);
            QAction *gomme = new QAction("&Gomme", this);
            QAction *rogner = new QAction("&Rogner", this);
            QAction *chaton = new QAction("&Chaton", this);
            QAction *aproposde = new QAction("&A propos de iChevalet...", this);
            QAction *modedemploi = new QAction("&Mode d'emploi", this);

        // Menu de la fenetre principale
            QMenu *fichier = menuBar()->addMenu("&Fichier");
                fichier->addAction(nouveau);
                fichier->addAction(ouvrir);
                fichier->addAction(enregistrer);
                fichier->addAction(imprimer);
                fichier->addAction(fermer);
            QMenu *edition = menuBar()->addMenu("&Edition");
                edition->addAction(palette);
                edition->addAction(epaisseur);
                edition->addAction(brosse);
                edition->addAction(ligne);
                edition->addAction(rectangle);
                edition->addAction(cercle);
                edition->addAction(chaton);
                edition->addAction(gomme);
                edition->addAction(rogner);
            QMenu *affichage = menuBar()->addMenu("&Affichage");
                affichage->addAction(pleinecran);
                affichage->addAction(minimiser);
            QMenu *aide = menuBar()->addMenu("&Aide");
                aide->addAction(modedemploi);
                aide->addAction(aproposde);

        // Barre d'outils
            QToolBar *outils = addToolBar("Outils");
                outils->addAction(nouveau);
                outils->addSeparator();
                outils->addAction(ouvrir);
                outils->addSeparator();
                outils->addAction(enregistrer);
                outils->addSeparator();
                outils->addAction(imprimer);
                outils->addSeparator();
                outils->addAction(palette);
                outils->addSeparator();
                outils->addAction(epaisseur);
                outils->addSeparator();
                outils->addAction(brosse);
                outils->addSeparator();
                outils->addAction(ligne);
                outils->addSeparator();
                outils->addAction(rectangle);
                outils->addSeparator();
                outils->addAction(cercle);
                outils->addSeparator();
                outils->addAction(chaton);
                outils->addSeparator();
                outils->addAction(gomme);
                outils->addSeparator();
                outils->addAction(rogner);

        // Connexions
            connect(fermer,SIGNAL(triggered(bool)),qApp,SLOT(quit()));
            connect(pleinecran,SIGNAL(triggered(bool)),this,SLOT(showFullScreen()));
            connect(minimiser,SIGNAL(triggered(bool)),this,SLOT(showNormal()));
            connect(ouvrir,SIGNAL(triggered(bool)),controleur,SLOT(ouvrir()));
            connect(enregistrer,SIGNAL(triggered(bool)),controleur,SLOT(enregistrer()));
            connect(nouveau,SIGNAL(triggered(bool)),controleur,SLOT(nouveau()));
            connect(imprimer,SIGNAL(triggered(bool)),controleur,SLOT(imprimer()));
            connect(palette,SIGNAL(triggered(bool)),controleur,SLOT(couleurStylo()));
            connect(epaisseur,SIGNAL(triggered(bool)),controleur,SLOT(epaisseurStylo()));
            connect(brosse,SIGNAL(triggered(bool)),controleur,SLOT(brosse()));
            connect(ligne,SIGNAL(triggered(bool)),controleur,SLOT(ligne()));
            connect(rectangle,SIGNAL(triggered(bool)),controleur,SLOT(rectangle()));
            connect(cercle,SIGNAL(triggered(bool)),controleur,SLOT(cercle()));
            connect(chaton,SIGNAL(triggered(bool)),controleur,SLOT(chaton()));
            connect(gomme,SIGNAL(triggered(bool)),controleur,SLOT(gomme()));
            connect(rogner,SIGNAL(triggered(bool)),controleur,SLOT(rogner()));
            connect(modedemploi,SIGNAL(triggered(bool)),controleur,SLOT(modedemploi()));
            connect(aproposde,SIGNAL(triggered(bool)),controleur,SLOT(apropos()));

        // Raccourcis
            nouveau->setShortcut(QKeySequence("Ctrl+N"));
            ouvrir->setShortcut(QKeySequence("Ctrl+O"));
            enregistrer->setShortcut(QKeySequence("Ctrl+S"));
            imprimer->setShortcut(QKeySequence("Ctrl+P"));
            fermer->setShortcut(QKeySequence("Escape"));
            pleinecran->setShortcut(QKeySequence("Ctrl+F"));
            minimiser->setShortcut(QKeySequence("Ctrl+M"));

        // Icones
            nouveau->setIcon(QIcon(":/icones/Image/nouveau.png"));
            ouvrir->setIcon(QIcon(":/icones/Image/ouvrir.png"));
            enregistrer->setIcon(QIcon(":/icones/Image/enregistrer.png"));
            imprimer->setIcon(QIcon(":/icones/Image/imprimer.png"));
            fermer->setIcon(QIcon(":/icones/Image/fermer.png"));
            pleinecran->setIcon(QIcon(":/icones/Image/pleinecran.png"));
            minimiser->setIcon(QIcon(":/icones/Image/minimiser.png"));
            brosse->setIcon(QIcon(":/icones/Image/brosse.png"));
            ligne->setIcon(QIcon(":/icones/Image/ligne.png"));
            rectangle->setIcon(QIcon(":/icones/Image/rectangle.png"));
            cercle->setIcon(QIcon(":/icones/Image/rond.png"));
            palette->setIcon(QIcon(":/icones/Image/couleur.png"));
            epaisseur->setIcon(QIcon(":/icones/Image/epaisseur.png"));
            gomme->setIcon(QIcon(":/icones/Image/gomme.png"));
            aproposde->setIcon(QIcon(":/icones/Image/apropos.png"));
            rogner->setIcon(QIcon(":/icones/Image/rogner.png"));
            chaton->setIcon(QIcon(":/icones/Image/chat.png"));
            modedemploi->setIcon(QIcon(":/icones/Image/aide.png"));
    }

//Gestion des évènements de la fenetre principale
    void Vue::closeEvent(QCloseEvent *event)
    {
        if (controleur->modification()){
            controleur->enregistrer();
            event->accept();
        }
        else
            event->accept();
    }
