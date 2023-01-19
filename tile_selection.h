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
    void mouseKeyComboEvent(QMouseEvent*, QKeyEvent*);

    QPixmap* getSelectedTile() const;
    QImage getSelectedTileImage() const;
    QPoint getMouseClickTileClip();

    void drawGridOverlay();

signals:

    void selectedTileImage(QImage img);
    void leftClickMouse();
    void newTilesheetLoad(QString);
    void sendConsoleMessage(QString);

public slots:
    void loadTilesheet();

private slots:

    void onMouseClickTile();
    void horzScrollOffset(int);
    void vertScrollOffset(int);
    void drawSelectedTileOverlay();



private:

    int calculateNumIndices();
    int calculateIndex(const int x, const int y) const;
    QPoint getClipCoordsFromIndex(const int index) const;

private:

    QString tilesheetName;
    QImage* img; // this will be loaded tilesheet

    QGraphicsScene* scene;
    QPixmap* selectedTiles[25];
    QGraphicsRectItem* tileHighlight;
    quint32 curTileX, curTileY;
    quint32 hScrollOffset, vScrollOffset;

};

#endif // TILE_SELECTION_H
