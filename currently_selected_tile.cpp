
#include "currently_selected_tile.h"


CurrentlySelectedTile::CurrentlySelectedTile(QWidget* parent)
    : QLabel(parent)
{

}

CurrentlySelectedTile::~CurrentlySelectedTile()
{

}

void CurrentlySelectedTile::receiveSelectedTile(QImage img) {

    QPixmap pm;
    pm.convertFromImage(img);

    setPixmap(pm);
    //ui->verticalLayout_2->addWidget(tileLabel);
}
