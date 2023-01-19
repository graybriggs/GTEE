#ifndef CURRENT_TILE_H
#define CURRENT_TILE_H



#include <QLabel>
#include <QPixmap>

class QWidget;

class CurrentTile : public QLabel {

    Q_OBJECT

public:
    CurrentTile(QWidget* parent = 0);
    virtual ~CurrentTile();


public slots:

    void receiveSelectedTile(QImage img);


};


#endif // CURRENT_TILE_H
