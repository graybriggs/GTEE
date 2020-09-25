#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include <vector>
#include <utility>
#include <memory>

class TileMap : public QGraphicsView {
public:

    TileMap(QWidget* parent = 0);

protected:
    void moveMapVertical();
    void moveMapHorizontal();
    void drawGridOverlay();

protected:
    QGraphicsScene* scene;
    std::vector<std::unique_ptr<QGraphicsPixmapItem>> layer;

    qint32 sceneWidth;
    qint32 sceneHeight;
};

#endif // TILE_MAP_H
