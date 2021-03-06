#ifndef TILE_MAP_RENDER_H
#define TILE_MAP_RENDER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QImage>

#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QDebug>
#include <QAbstractSlider>
#include <QScrollBar>

#include <vector>
#include <memory>
#include <utility>

class QWidget;

class TileMapRender : public QGraphicsView {

    Q_OBJECT

public:

    TileMapRender(int w, int h, QWidget* parent = 0);
    ~TileMapRender();

    void setupScene();

    quint32 calculateIndex(const int, const int) const;
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);

signals:
    void leftMouseClick();
    void updateLayerValue(const int); // used from a key press to update the combobox for the corresponding layer number

public slots:

    void addTile();
    void updateSelectedTile(QImage);

    void selectLayerOne();
    void selectLayerTwo();
    void selectLayerThree();
    void selectLayerFour();
    void selectLayerCollision();
    void selectLayer(const int index);

    void moveMapHorizontal(const int); // slot for a scrollbar signal
    void moveMapVertical(const int);

    void horzScrollBarOffset(int);
    void vertScrollBarOffset(int);

    void drawGridOverlay(bool);

private:

    void initTileLayers();

private:

    const int sceneWidth;
    const int sceneHeight;

    std::unique_ptr<QGraphicsScene> sceneOne;
    std::unique_ptr<QGraphicsScene> sceneTwo;
    std::unique_ptr<QGraphicsScene> sceneThree;
    std::unique_ptr<QGraphicsScene> sceneFour;
    std::unique_ptr<QGraphicsScene> sceneCollision;
    std::unique_ptr<QGraphicsScene> finalRenderScene;

    std::vector<std::unique_ptr<QGraphicsPixmapItem>> tileLayerCollision;
    std::vector<std::unique_ptr<QGraphicsPixmapItem>> tileLayerFour;
    std::vector<std::unique_ptr<QGraphicsPixmapItem>> tileLayerThree;
    std::vector<std::unique_ptr<QGraphicsPixmapItem>> tileLayerTwo;
    std::vector<std::unique_ptr<QGraphicsPixmapItem>> tileLayerOne;

    // points to the tile that is currently selected to 'paint'
    // it is updated by the updateSelectedTile slot
    //QPixmap* pm;
    std::unique_ptr<QPixmap> pm;

    // the corresponding index of the currently selected map area
    quint32 index;

    // holds the currently selected layer that will be drawn to
    quint8 currentLayer;
    bool leftMouseButton;

    // used for scrolling
    int valLast;
    // keep track of mouse offsets when the map has been scrolled
    int mouseXOffset;
    int mouseYOffset;

    int hBarOffset, vBarOffset;

    // raw pointers because returned by the UI.
    QScrollBar* vsb;
    QScrollBar* hsb;

};


#endif // TILE_MAP_RENDER_H
