#ifndef VUE
#define VUE

#include <QtWidgets>
#include <QCoreApplication>
#include <QDir>

#include <modele.h>
#include <controleur.h>

class Vue : public QMainWindow
{
    Q_OBJECT
public:
    Vue();
    Modele *modele;

protected:
    void closeEvent(QCloseEvent *event);

private:
    Controleur *controleur;
};

#endif // FENTREPRINCIPALE

