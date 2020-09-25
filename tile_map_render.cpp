
#include "tile_map.h"
#include "tile_map_render.h"

TileMapRender::TileMapRender(int w, int h, QWidget* parent)
    : QGraphicsView(parent),
      sceneWidth(w),
      sceneHeight(h),
      leftMouseButton(false),
      valLast(0),
      mouseXOffset(0),
      mouseYOffset(0)
{
    setupScene();
    initTileLayers();

    QObject::connect(this, SIGNAL(leftMouseClick()), this, SLOT(addTile()));


    ///////////
    hsb = horizontalScrollBar();
    hBarOffset = hsb->value();
    QObject::connect(hsb, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarOffset(int)));

    vsb = verticalScrollBar();
    vBarOffset = vsb->value();
    QObject::connect(vsb, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarOffset(int)));
}

TileMapRender::~TileMapRender() {

    //delete finalRenderScene; // temp
    //delete pm;

}

void TileMapRender::setupScene() {

   // sceneOne = new QGraphicsScene(this);
    sceneOne = std::make_unique<QGraphicsScene>(this);
    sceneOne->setSceneRect(0, 0, sceneWidth, sceneHeight);

    //sceneTwo = new QGraphicsScene(this);
    sceneTwo = std::make_unique<QGraphicsScene>(this);
    sceneTwo->setSceneRect(0, 0, sceneWidth, sceneHeight);

    //sceneThree = new QGraphicsScene(this);
    sceneThree = std::make_unique<QGraphicsScene>(this);
    sceneThree->setSceneRect(0, 0, sceneWidth, sceneHeight);

    //sceneFour = new QGraphicsScene(this);
    sceneFour = std::make_unique<QGraphicsScene>(this);
    sceneFour->setSceneRect(0, 0, sceneWidth, sceneHeight);

    //sceneCollision = new QGraphicsScene(this);
    sceneCollision = std::make_unique<QGraphicsScene>(this);
    sceneCollision->setSceneRect(0, 0, sceneWidth, sceneHeight);

    //finalRenderScene = new QGraphicsScene(this);
    finalRenderScene = std::make_unique<QGraphicsScene>(this);
    finalRenderScene->setSceneRect(0, 0, sceneWidth, sceneHeight);

    this->setScene(sceneFour.get());
    selectLayerFour(); // currentLayer member variable initialization is handled here (instead of in the initialisation list)!
    //pm = new QPixmap;
    pm = std::make_unique<QPixmap>();
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
        index = calculateIndex(event->x() + hBarOffset, event->y() + vBarOffset);
        addTile();
        //emit leftMouseClick();
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
        index = calculateIndex(event->x() + hBarOffset, event->y() + vBarOffset);
        addTile();
    }
}

void TileMapRender::keyPressEvent(QKeyEvent* event) {

    switch (event->key()) {
    case Qt::Key_1:
        selectLayerOne();
        updateLayerValue(3);
        break;
    case Qt::Key_2:
        selectLayerTwo();
        updateLayerValue(2);
        break;
    case Qt::Key_3:
        selectLayerThree();
        updateLayerValue(1);
        break;
    case Qt::Key_4:
        selectLayerFour();
        updateLayerValue(0);
        break;
    case Qt::Key_5:
        selectLayerCollision();
        updateLayerValue(4);
        break;
    case Qt::Key_Right:
        hsb->setValue(hsb->value() + 12);
        break;
    case Qt::Key_Left:
        hsb->setValue(hsb->value() - 12);
        break;
    case Qt::Key_Down:
        vsb->setValue(vsb->value() + 12);
        break;
    case Qt::Key_Up:
        vsb->setValue(vsb->value() - 12);
        break;
    default:
        break;
    }
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

            auto pmItem2 = std::make_unique<QGraphicsPixmapItem>();
            pmItem2->setOffset(x, y);
            sceneTwo->addItem(pmItem2.get());
            tileLayerTwo.push_back(std::move(pmItem2));

            auto pmItem3 = std::make_unique<QGraphicsPixmapItem>();
            pmItem3->setOffset(x, y);
            sceneThree->addItem(pmItem3.get());
            tileLayerThree.push_back(std::move(pmItem3));

            auto pmItem4 = std::make_unique<QGraphicsPixmapItem>();
            pmItem4->setOffset(x, y);
            sceneFour->addItem(pmItem4.get());
            tileLayerFour.push_back(std::move(pmItem4));

            auto pmItem5 = std::make_unique<QGraphicsPixmapItem>();
            pmItem5->setOffset(x, y);
            sceneCollision->addItem(pmItem5.get());
            tileLayerCollision.push_back(std::move(pmItem5));

            x += 32;
        }
        x = 0;
        y += 32;
    }
}


////////// SLOTS ///


// Updates the tile that is pointed to by tiles index
void TileMapRender::addTile() {
/*
    std::shared_ptr<QGraphicsPixmapItem> selectedTile = tileLayerTwo[index];
    selectedTile->setPixmap(pm->copy(0,0,32,32));
*/
    switch (currentLayer) {
    case 1:
        qDebug() << "Writing to layer: 1";
        tileLayerOne[index]->setPixmap(pm->copy(0,0,32,32));
        break;
    case 2:
        qDebug() << "Writing to layer: 2";
        tileLayerTwo[index]->setPixmap(pm->copy(0,0,32,32));
        break;
    case 3:
        qDebug() << "Writing to layer: 3";
        tileLayerThree[index]->setPixmap(pm->copy(0,0,32,32));
        break;
    case 4:
        qDebug() << "Writing to layer: 4";
        tileLayerFour[index]->setPixmap(pm->copy(0,0,32,32));
        break;
    case 5: // collision
        qDebug() << "Writing to layer: collision";
        tileLayerCollision[index]->setPixmap(pm->copy(0,0,32,32));
        break;

    }
}

void TileMapRender::updateSelectedTile(QImage img) {
    pm->convertFromImage(img);
}

void TileMapRender::selectLayerOne() {
    currentLayer = 1;
    this->setScene(sceneOne.get());
    sceneOne->update();

}

void TileMapRender::selectLayerTwo() {
    currentLayer = 2;
    this->setScene(sceneTwo.get());
    sceneTwo->update();
}

void TileMapRender::selectLayerThree() {
    currentLayer = 3;
    this->setScene(sceneThree.get());
}

void TileMapRender::selectLayerFour() {
    currentLayer = 4;
    this->setScene(sceneFour.get());
    sceneFour->update();
    qDebug() << "4";
}

void TileMapRender::selectLayerCollision() {
    currentLayer = 5;
    this->setScene(sceneCollision.get());
}

void TileMapRender::selectLayer(const int index) {

    switch(index) {
        case 0:
            selectLayerFour();
            break;
        case 1:
            selectLayerThree();
            break;
        case 2:
            selectLayerTwo();
            break;
        case 3:
            selectLayerOne();
            break;
        case 4:
            selectLayerCollision();
            break;
        default:
            break;
    }
}

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
            sceneTwo->addLine(0, x, sceneWidth, x);
            sceneThree->addLine(0, x, sceneWidth, x);
            sceneFour->addLine(0, x, sceneWidth, x);
            sceneFour->update();

            sceneCollision->addLine(0, x, sceneWidth, x);
        }

        for (int y = 0; y < sceneWidth; y += 32) {
            sceneOne->addLine(y, 0, y, sceneHeight);
            sceneTwo->addLine(y, 0, y, sceneHeight);
            sceneThree->addLine(y, 0, y, sceneHeight);
            sceneFour->addLine(y, 0, y, sceneHeight);
            sceneCollision->addLine(y, 0, y, sceneHeight);
        }
    }
}
