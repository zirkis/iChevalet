#ifndef MODELE
#define MODELE

#include <QtWidgets>

class Modele : public QWidget
{
    Q_OBJECT

public:
    Modele(QWidget *parent = 0);

    bool ouvrirImage(const QString &nomFichier);
    bool enregistrerImage(const QString &nomFichier);
    void nouveau();
    void print();

    void setCouleurStylo(const QColor &nouvelleCouleur);
    void setEpaisseurStylo(int nouvelleEpaisseur);
    void setOutil(int nouvelOutil);

    QColor couleurStylo() const {return maCouleurStylo;}
    int epaisseurStylo() const {return monEpaisseurStylo;}
    int outil() const {return outilSelec;}

    bool modifie;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void brosse(const QPoint &destination);
    void ligne(const QPoint &destination);
    void rectangle(const QPoint &destination);
    void cercle(const QPoint &destination);
    void gomme(const QPoint &destination);
    void rogner(const QPoint &destination);
    void chaton(const QPoint &destination);

    void redimensionnerImage(QImage *image, const QSize &nouvelleTaille);

    int monEpaisseurStylo;
    QColor maCouleurStylo;
    int outilSelec;
    QImage image;
    QPoint origine;
    bool dessiner;
};

#endif // ZONEDEDESSIN

