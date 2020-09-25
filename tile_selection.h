#ifndef TILE_SELECTION_H
#define TILE_SELECTION_H

#include <QtGui>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QScrollBar>

class TileSelection : public QGraphicsView {

    Q_OBJECT

public:

    explicit TileSelection(QWidget* parent = 0);
    virtual ~TileSelection();

    void mousePressEvent(QMouseEvent*);

    QPixmap* getSelectedTile() const;
    QImage getSelectedTileImage() const;
    QPoint getMouseClickTileClip();

    void drawGridOverlay();

signals:

    void selectedTileImage(QImage img);
    void leftClickMouse();

private slots:

    void onMouseClickTile();
    void horzScrollOffset(int);
    void vertScrollOffset(int);

private:

    int calculateIndex(const int x, const int y) const;
    QPoint getClipCoordsFromIndex(const int index) const;

private:

    QImage* img; // this will be loaded tilesheet

    QGraphicsScene* scene;
    QPixmap* selectedTile;

    quint32 curTileX, curTileY;
    quint32 hScrollOffset, vScrollOffset;

};

#endif // TILE_SELECTION_H
