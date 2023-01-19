#include "current_tile.h"


CurrentTile::CurrentTile(QWidget* parent)
    : QLabel(parent)
{

}

CurrentTile::~CurrentTile()
{

}

void CurrentTile::receiveSelectedTile(QImage img) {

    QPixmap pm;
    pm.convertFromImage(img);

    setPixmap(pm);
    //ui->verticalLayout_2->addWidget(tileLabel);
}
