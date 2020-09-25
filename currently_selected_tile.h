#ifndef CURRENTLY_SELECTED_TILE_H
#define CURRENTLY_SELECTED_TILE_H


#include <QLabel>
#include <QPixmap>

class QWidget;

class CurrentlySelectedTile : public QLabel {

    Q_OBJECT

public:
    CurrentlySelectedTile(QWidget* parent = 0);
    virtual ~CurrentlySelectedTile();


public slots:

    void receiveSelectedTile(QImage img);


};

#endif // CURRENTLY_SELECTED_TILE_H
