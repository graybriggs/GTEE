
#include "tile_selection.h"

#include <QString>

TileSelection::TileSelection(QWidget* parent)
    : QGraphicsView(parent),
      curTileX(0),
      curTileY(0)
{
    scene = new QGraphicsScene(this);
    this->setScene(scene);

    // load tilesheet
    img = new QImage(QString("smb_tilesheet.png"));
    qDebug() << "img val: " << img;

    selectedTile = new QPixmap;
    selectedTile->convertFromImage(*img);

    //////////


    //QPixmap* pm = new QPixmap();
    //pm->convertFromImage(*img);

    scene->addPixmap(*selectedTile);
    //addPixmap(*pm);
    drawGridOverlay();

    QObject::connect(this, SIGNAL(leftClickMouse()), this, SLOT(onMouseClickTile()));

    /// scrollbars
    QScrollBar* hsb = this->horizontalScrollBar();
    hScrollOffset = hsb->value();
    QObject::connect(hsb, SIGNAL(valueChanged(int)), this, SLOT(horzScrollOffset(int)));

    QScrollBar* vsb = this->verticalScrollBar();
    vScrollOffset = vsb->value();
    QObject::connect(vsb, SIGNAL(valueChanged(int)), this, SLOT(vertScrollOffset(int)));
}

TileSelection::~TileSelection() {
    delete img;
    delete selectedTile;
    delete scene;
}

void TileSelection::mousePressEvent(QMouseEvent* event) {

    if (event->button() == Qt::LeftButton) {

        // the absolute mouse click value is reduced or "clipped"
        // down so that tile value increments are stored
        curTileX = ((event->x() + hScrollOffset) / 32) * 32; // the horizontal scrollbar offset is added here!
        curTileY = ((event->y() + vScrollOffset) / 32) * 32; // the vertical scrollbar offset is addded here!

        // emit signal for mouse click
        emit leftClickMouse();
    }
}

int TileSelection::calculateIndex(const int x, const int y) const {
    int X = x / 32;
    int Y = y / 32;

    return Y * 32 + X;
}

QPoint TileSelection::getClipCoordsFromIndex(const int index) const {

    // a tilesheet is expected to be 16 tiles wide
    // that is 32 * 16 = 512 pixels
    int x = (index % 16) * 32;
    int y = (index / 32) * 32;

    return QPoint(x, y);
}

QPoint TileSelection::getMouseClickTileClip() {

    return QPoint(curTileX, curTileY);
}

// probably remove this
QPixmap* TileSelection::getSelectedTile() const {

    return selectedTile;
}

QImage TileSelection::getSelectedTileImage() const {

    QImage img = selectedTile->copy(curTileX, curTileY, 32, 32).toImage();
    return img;
}

void TileSelection::drawGridOverlay() {

    for (unsigned x = 0; x < 512; x += 32) {
        scene->addLine(0, x, 512, x);
    }

    for (unsigned y = 0; y < 512; y += 32) {
        scene->addLine(y, 0, y, 512);
    }
}


/////// SLOTS //////

void TileSelection::onMouseClickTile() {

    // emit the signal
    emit this->selectedTileImage(getSelectedTileImage());
}

void TileSelection::horzScrollOffset(int i) {
    hScrollOffset = i;
}

void TileSelection::vertScrollOffset(int i) {
    vScrollOffset = i;
}

