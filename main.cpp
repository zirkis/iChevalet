#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QtWidgets>

#include <vue.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Vue fenetre;
    fenetre.resize(730,700);
    fenetre.setCursor(Qt::PointingHandCursor);
    fenetre.setWindowTitle("iChevalet");
    fenetre.setWindowIcon(QIcon(":/icones/Image/icone.png"));
    fenetre.show();

    return app.exec();

}

