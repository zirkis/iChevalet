#include <modele.h>

#ifndef QT_NO_PRINTER
#include <QPrinter>
#include <QPrintDialog>
#endif

// Initialisation de la zone de dessin
    Modele::Modele(QWidget *parent) : QWidget(parent)
    {
        setAttribute(Qt::WA_StaticContents);
        modifie = false;
        dessiner = false;
        monEpaisseurStylo = 1;
        maCouleurStylo = Qt::red;
        outilSelec = 1;
    }

// Gestion de la zone de dessin
    bool Modele::ouvrirImage(const QString &nomFichier)
    {
        QImage imageChargée;
        if (!imageChargée.load(nomFichier))
            return false;

        image = imageChargée.scaled(image.size(),Qt::KeepAspectRatio, Qt::FastTransformation);

        modifie = false;
        update();
        return true;
    }

    bool Modele::enregistrerImage(const QString &nomFichier)
    {
        if (image.save(nomFichier, 0)){
            modifie = false;
            return true;
        } else
            return false;
    }

    void Modele::redimensionnerImage(QImage *image, const QSize &nouvelleTaille)
    {
        if (image->size() == nouvelleTaille)
            return;
        QImage nouvelleImage(nouvelleTaille, QImage::Format_RGB32);
        nouvelleImage.fill(qRgb(255, 255, 255));
        QPainter painter(&nouvelleImage);
        painter.drawImage(QPoint(0,0), *image);
        *image = nouvelleImage;
    }

    void Modele::nouveau()
    {
        redimensionnerImage(&image, size() - QSize(50,50));
        image.fill(qRgb(255,255,255));
        modifie = false;
        update();
    }

    void Modele::print()
    {
    #if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
        QPrinter printer(QPrinter::HighResolution);

        QPrintDialog printDialog(&printer, this);
        if (printDialog.exec() == QDialog::Accepted) {
            QPainter painter(&printer);
            QRect rect = painter.viewport();
            QSize size = image.size();
            size.scale(rect.size(), Qt::KeepAspectRatio);
            painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
            painter.setWindow(image.rect());
            painter.drawImage(0, 0, image);
        }
    #endif // QT_NO_PRINTER
    }


// Sélecteurs
    void Modele::setCouleurStylo(const QColor &nouvelleCouleur)
    {
        maCouleurStylo = nouvelleCouleur;
    }

    void Modele::setEpaisseurStylo(int nouvelleEpaisseur)
    {
        monEpaisseurStylo = nouvelleEpaisseur;
    }

    void Modele::setOutil(int nouvelOutil)
    {
        outilSelec = nouvelOutil;
    }

// Outils de dessin
    void Modele::brosse(const QPoint &destination)
    {
        QPainter painter(&image);
        painter.setPen(QPen(maCouleurStylo, monEpaisseurStylo, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(origine, destination);
        modifie = true;

        int rad = (monEpaisseurStylo / 2) + 2;
        update(QRect(origine, destination).normalized().adjusted(-rad, -rad, +rad, +rad));

        origine = destination;
    }

    void Modele::ligne(const QPoint &destination)
    {
        QPainter painter(&image);
        painter.setPen(QPen(maCouleurStylo, monEpaisseurStylo, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(origine, destination);
        modifie = true;
        update();
    }

    void Modele::rectangle(const QPoint &destination)
    {
        QPainter painter(&image);
        painter.setPen(QPen(maCouleurStylo, monEpaisseurStylo, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(origine.x(),origine.y(), (destination.x() - origine.x()), (destination.y() - origine.y()));
        modifie = true;
        update();
    }

    void Modele::cercle(const QPoint &destination)
    {
        QPainter painter(&image);
        painter.setPen(QPen(maCouleurStylo, monEpaisseurStylo, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

        if (origine.x() < destination.x()) //Tracé un cercle vers la droite et
        {
            if (origine.y() < destination.y()) //vers le bas
                painter.drawEllipse(origine.x(), origine.y(), destination.x() - origine.x(), destination.x() - origine.x());
            else if (destination.y() < origine.y()) //vers le haut
                painter.drawEllipse(origine.x(), origine.y(), destination.x() - origine.x(), -(destination.x() - origine.x()));
        }
        if (destination.x() < origine.x()) //Tracé un cercle vers la gauche
        {
            if(origine.y() < destination.y()) //vers le bas
                painter.drawEllipse(origine.x(), origine.y(), -(origine.x() - destination.x()), (origine.x() - destination.x()));
            else if(destination.y() < origine.y()) //vers le haut
                painter.drawEllipse(origine.x(), origine.y(), -(origine.x() - destination.x()), -(origine.x() - destination.x()));
        }

        modifie = true;
        update();
    }

    void Modele::gomme(const QPoint &destination)
    {
        QPainter painter(&image);
        painter.setPen(QPen(Qt::white, 15, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        painter.drawLine(origine, destination);
        modifie = true;

        int rad = (15 / 2) + 2;
        update(QRect(origine, destination).normalized().adjusted(-rad, -rad, +rad, +rad));

        origine = destination;
    }

    void Modele::rogner(const QPoint &destination)
    {
        if (origine.x() <= image.width() && destination.x() <= image.width() &&
            origine.y() <= image.height() && destination.y() <= image.height() &&
            origine.x() < destination.x() && origine.y() < destination.y())
            {
                image = image.copy(origine.x(),origine.y(),(destination.x()-origine.x()),(destination.y()-origine.y()));
                modifie = true;
                update();
            }
    }

    void Modele::chaton(const QPoint &destination)
    {
        if (origine.x() < destination.x() && origine.y() < destination.y())
            {
                QRect zoneChat(origine.x(),origine.y(),(destination.x()-origine.x()),(destination.y()-origine.y()));
                QImage chat(":/icones/Image/chatImage.png");
                QPainter painter(&image);
                painter.drawImage(zoneChat,chat);
                modifie = true;
                update();
            }
    }

// Gestion des évènements de la zone de dessin
    void Modele::mousePressEvent(QMouseEvent *event)
    {
        if(event->button() == Qt::LeftButton){
            origine = event->pos();
            dessiner = true;
        }
    }

    void Modele::mouseMoveEvent(QMouseEvent *event)
    {
        if((event->buttons() & Qt::LeftButton) && dessiner)
        {
            if(outil() == 1)
                brosse(event->pos());
            if(outil() == 5)
                gomme(event->pos());
            }
    }

    void Modele::mouseReleaseEvent(QMouseEvent *event)
    {
        if((event->button() == Qt::LeftButton) && dessiner){
            if (outil() == 1)
            {
                brosse(event->pos());
                dessiner = false;
            }
            if (outil() == 2)
            {
                ligne(event->pos());
                dessiner = false;
            }
            if (outil() == 3)
            {
                rectangle(event->pos());
                dessiner = false;
            }
            if (outil() == 4)
            {
                cercle(event->pos());
                dessiner = false;
            }
            if (outil() == 5)
            {
                gomme(event->pos());
                dessiner = false;
            }
            if (outil() == 6)
            {
                rogner(event->pos());
                dessiner = false;
            }
            if (outil() == 7)
            {
                chaton(event->pos());
                dessiner = false;
            }
        }
    }

    void Modele::paintEvent(QPaintEvent *event)
    {
            QPainter painter(this);
            QRect dirtyRect = event->rect();
            painter.drawImage(dirtyRect, image, dirtyRect);
    }

    void Modele::resizeEvent(QResizeEvent *event)
    {
        if (width() > image.width() || height() > image.height())
        {
            int newWidth = qMax(width(), image.width());
            int newHeight = qMax(height(), image.height());
            redimensionnerImage(&image, QSize(newWidth-50, newHeight-50));
            update();
        }
        if (width() < image.width() || height() < image.height())
        {
            int newWidth = qMin(width(), image.width());
            int newHeight = qMin(height(), image.height());
            redimensionnerImage(&image, QSize(newWidth-50, newHeight-50));
            update();
        }
        QWidget::resizeEvent(event);
    }
