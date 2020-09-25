#ifndef MAP_SCENE_H
#define MAP_SCENE_H

#include <QGraphicsScene>

#include <vector>
#include <memory>

struct MapScene {
    MapScene(qreal x, qreal y, qreal w, qreal h);

    QGraphicsScene* scene;
    std::vector<std::shared_ptr<QGraphicsPixmapItem>> layer;

};

#endif // MAP_SCENE_H
