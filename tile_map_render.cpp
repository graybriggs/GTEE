
#include "tile_map_render.h"

#include <QMouseEvent>
#include <memory>

TileMapRender::TileMapRender(int w, int h, QWidget* parent)
    : QGraphicsView(parent),
      sceneWidth(w),
      sceneHeight(h),
      leftMouseButton(false),
      valLast(0),
      mouseXOffset(0),
      mouseYOffset(0),
      currentLayer(1)
{
    setupScene();
    initTileLayers();

    QObject::connect(this, SIGNAL(leftMouseClick()), this, SLOT(addTile()));
    //QObject::connect(this, SIGNAL(onMouseClickTile()), this, SLOT(addTile()));
    /*
    ///////////
    hsb = horizontalScrollBar();
    hBarOffset = hsb->value();
    QObject::connect(hsb, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarOffset(int)));

    vsb = verticalScrollBar();
    vBarOffset = vsb->value();
    QObject::connect(vsb, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarOffset(int)));
    */
}

TileMapRender::~TileMapRender() {

    //delete finalRenderScene; // temp
    //delete pm;
}

void TileMapRender::setupScene() {

   // sceneOne = new QGraphicsScene(this);
    //sceneOne = std::make_unique<QGraphicsScene>(this);
    //sceneOne->setSceneRect(0, 0, sceneWidth, sceneHeight);

    sceneOne = std::make_unique<QGraphicsScene>(this);
    sceneOne->setSceneRect(0,0, sceneWidth, sceneHeight);

    //graphicsView = new QGraphicsView(this);


    this->setScene(sceneOne.get());
    //selectLayerOne(); // currentLayer member variable initialization is handled here (instead of in the initialisation list)!
    //pm = new QPixmap;


    for (int i = 0; i < 5 * 5; ++i) {
        //selected_tiles.push_back(std::make_unique<QPixmap>());
        //selected_tiles.emplace_back(new QPixmap);
        selected_tiles[i] = new QPixmap;
    }

    //selected_tiles = new QPixmap();
}

quint32 TileMapRender::calculateIndex(const int x, const int y) const {
    int X = (x + mouseXOffset) / 32;
    int Y = (y + mouseYOffset) / 32;

    qDebug() << "X: " << X << " | Y:" << Y;
    //return Y * 16 + X;
    return Y * sceneWidth / 32 + X;
}

////////////////////
////// EVENTS //////

void TileMapRender::mousePressEvent(QMouseEvent* event) {

    // get the position of the mouse event click and add the
    // horizontal and vertical scroll bar offsets so the correct
    // tile map array index can be calculated.

    if (event->button() == Qt::LeftButton) {
        leftMouseButton = true;
        index = calculateIndex(event->pos().x() + hBarOffset, event->pos().y() + vBarOffset);
        addTile();
        emit leftMouseClick();
    }

}

void TileMapRender::mouseReleaseEvent(QMouseEvent* event) {


    if (event->button() == Qt::LeftButton) {
        leftMouseButton = false;
    }

}

void TileMapRender::mouseMoveEvent(QMouseEvent* event) {

    // ditto mousePressEvent comment

    // using a bool flag is hacky but...
    if (leftMouseButton) {
        index = calculateIndex(event->pos().x() + hBarOffset, event->pos().y() + vBarOffset);
        addTile();
    }
}

void TileMapRender::keyPressEvent(QKeyEvent* event) {
}

////////////////////////////
////// Private functions ///
////////////////////////////

void TileMapRender::initTileLayers() {

    int x = 0;
    int y = 0;

    for (int i = 0; i < sceneHeight; i += 32) {
        for (int j = 0; j < sceneWidth; j += 32) {
            // five different layers
            auto pmItem1 = std::make_unique<QGraphicsPixmapItem>();
            pmItem1->setOffset(x, y);
            //test
            sceneOne->addItem(pmItem1.get());
            tileLayerOne.push_back(std::move(pmItem1));

            auto col = std::make_unique<QGraphicsRectItem>();
            col->setPos(QPoint(x, y));
            col->setBrush(Qt::red);
            col->setOpacity(0.4);
            collisionLayer.push_back(std::move(col));

            x += 32;
        }
        x = 0;
        y += 32;
    }
}


int TileMapRender::numTileIndices() {

    // currently max selectable tiles at once is 10x10 = 100#
    int max_tiles_select = 1;

    return max_tiles_select;
}


////////// SLOTS ///


// Updates the tile that is pointed to by tiles index
void TileMapRender::addTile() {
/*
    std::shared_ptr<QGraphicsPixmapItem> selectedTile = tileLayerTwo[index];
    selectedTile->setPixmap(pm->copy(0,0,32,32));
*/
    switch (currentLayer) {
    case 0:
        qDebug() << "Writing to collision layer";
        /*
        tileHighlight->setPos(QPoint(curTileX, curTileY));
        tileHighlight->setBrush(Qt::red);
        tileHighlight->setOpacity(0.4);
        scene->addItem(tileHighlight);
        */
    case 1:
        qDebug() << "Writing to layer: 1";
        tileLayerOne[index]->setPixmap(selected_tiles[0]->copy(0,0,32,32));
        //tileLayerOne[index]->setPixmap(selected_tiles->copy(0,0,32,32));
        break;
    }
}

void TileMapRender::updateSelectedTile(QImage img) {
    selected_tiles[0]->convertFromImage(img);
    //selected_tiles->convertFromImage(img);
}

void TileMapRender::tileFill() {
    std::size_t sz = sceneHeight / 32 * sceneWidth / 32;
    for (std::size_t i = 0; i < sz; ++i) {
        tileLayerOne[i]->setPixmap(selected_tiles[0]->copy(0,0,32,32));
    }
}

void TileMapRender::selectLayerOne() {
    currentLayer = 1;
    this->setScene(sceneOne.get());
    sceneOne->update();
}


/*
void TileMapRender::moveMapHorizontal(const int val) {

    qDebug() << "val: " << val << " valLast: " << valLast;

    int change = 0;

    if (val > valLast) {
        valLast = val;
        //change = -1;
        change = -(int)sceneWidth / 100;
        mouseXOffset += 1;
    }
    else if (val < valLast){
        valLast = val;
        //change = 1;
        change = (int)sceneWidth / 100;
        mouseXOffset -= 1;
    }


    std::size_t sz = tileLayerFour.size();

    for (std::size_t i = 0; i < sz; ++i) {
        QPointF p = tileLayerFour[i]->offset();
        tileLayerFour[i]->setOffset(p.x() + change, p.y());
    }

}

void TileMapRender::moveMapVertical(const int val) {

    qDebug() << "Scrolling vertically";

    int change = 0;

    if (val > valLast) {
        valLast = val;
        change = -1;
        mouseYOffset += 1;
    }
    else if (val < valLast){
        valLast = val;
        change = 1;
        mouseYOffset -= 1;
    }

    std::size_t sz = tileLayerFour.size();

    for (std::size_t i = 0; i < sz; ++i) {
        QPointF p = tileLayerFour[i]->offset();
        tileLayerFour[i]->setOffset(p.x(), p.y() + change);
    }
}
*/

void TileMapRender::horzScrollBarOffset(int i) {
    hBarOffset = i;
}

void TileMapRender::vertScrollBarOffset(int i) {
    vBarOffset = i;
}

void TileMapRender::drawGridOverlay(bool toggle) {

    // currently does not work as intended. A grid is able to be drawn
    // however not removed. There needs to be an additional "buffer"
    // type layer to handle the drawing of multiple layers into one
    // and this includes the grid lines.
    if (toggle) {
        for (int x = 0; x < sceneHeight; x += 32) {
            sceneOne->addLine(0, x, sceneWidth, x);
            sceneOne->update();
        }

        for (int y = 0; y < sceneWidth; y += 32) {
            sceneOne->addLine(y, 0, y, sceneHeight);
        }
    }
}

void TileMapRender::loadNewTilesheet(QString filename) {
    qDebug() << "loaded " << filename << " in tileMap.";
}
