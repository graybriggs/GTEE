#include "tile_selection.h"

#include <QString>
#include <QGraphicsRectItem>


TileSelection::TileSelection(QWidget* parent)
    : QGraphicsView(parent),
      curTileX(0),
      curTileY(0)
{
    scene = new QGraphicsScene(this);
    this->setScene(scene);

    //////////

    //QPixmap* pm = new QPixmap();
    //pm->convertFromImage(*img);


    //addPixmap(*pm);
    drawGridOverlay();

    tileHighlight = new QGraphicsRectItem(curTileX, curTileY,32,32);

    QObject::connect(
        this, SIGNAL(leftClickMouse()),
        this, SLOT(onMouseClickTile())
    );
    QObject::connect(
        this, SIGNAL(leftClickMouse()),
        this, SLOT(drawSelectedTileOverlay())
    );

    /// scrollbars
    QScrollBar* hsb = this->horizontalScrollBar();
    hScrollOffset = hsb->value();
    QObject::connect(
        hsb, SIGNAL(valueChanged(int)),
        this, SLOT(horzScrollOffset(int))
    );

    QScrollBar* vsb = this->verticalScrollBar();
    vScrollOffset = vsb->value();
    QObject::connect(
        vsb, SIGNAL(valueChanged(int)),
        this, SLOT(vertScrollOffset(int))
    );
}

TileSelection::~TileSelection() {
    delete img;
    for (int i = 0; i < 25 * 25; i++) {
        delete selectedTiles[i];
    }
    delete tileHighlight;
    delete scene;
}


void TileSelection::mousePressEvent(QMouseEvent* event) {

    if (event->button() == Qt::LeftButton) {
        // the absolute mouse click value is reduced or "clipped"
        // down so that tile value increments are stored
        curTileX = ((event->pos().x() + hScrollOffset) / 32) * 32; // the horizontal scrollbar offset is added here!
        curTileY = ((event->pos().y() + vScrollOffset) / 32) * 32; // the vertical scrollbar offset is addded here!
        qDebug() << curTileX << QString(",") << curTileY;
        // emit signal for mouse click
        emit leftClickMouse();
    }
}

void mouseKeyComboEvent(QMouseEvent* mouseEvent, QKeyEvent* keyEvent) {

    if (mouseEvent->button() == Qt::LeftButton && keyEvent->key() == Qt::CTRL) {
        qDebug() << "L-Mouse and CTRL was pressed.\n";
    }
}

void TileSelection::loadTilesheet() {

    tilesheetName = "smb_tilesheet.png";
    QString* msg = new QString("Loading " + tilesheetName);

    qDebug() << *msg;

    emit sendConsoleMessage(*msg);

    img = new QImage(tilesheetName);

    for (int i = 0; i < 5 * 5; ++i) {
        selectedTiles[i] = new QPixmap;
        selectedTiles[i]->convertFromImage(*img);
    }
    scene->addPixmap(*selectedTiles[0]);

    drawGridOverlay();
    //scene->update();
}


int TileSelection::calculateNumIndices() {

    // currently max multiple tiles that can be pasted is 10x10 = 100 tiles
    int copy_max_tiles = 1;
    return copy_max_tiles;
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

    return selectedTiles[0];
}

QImage TileSelection::getSelectedTileImage() const {

    return selectedTiles[0]->copy(curTileX, curTileY, 32, 32).toImage();
}

void TileSelection::drawSelectedTileOverlay() {
    qDebug() << curTileX << " AND " << curTileY;

    tileHighlight->setPos(QPoint(curTileX, curTileY));
    tileHighlight->setBrush(Qt::red);
    tileHighlight->setOpacity(0.4);
    scene->addItem(tileHighlight);
    drawGridOverlay();
    scene->update();

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

