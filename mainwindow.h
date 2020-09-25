#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollBar>
#include <QComboBox>
#include <QMenuBar>
#include <QActionEvent>
#include <QAction>
#include <QDialog>

#include "tile_map_render.h"
#include "tile_selection.h"
#include "currently_selected_tile.h"

#include <iostream>
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

public slots:

    void test(int i) { qDebug() << "mm " << i; }
     void newMap();

private:

    void setupTileMapRender();
    void setupTileSelection();
    void setupCurrentlySelectedTile();
    void setupSignalsSlots();
    void setupMenubar();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<TileMapRender> tileMapRender;
    std::unique_ptr<TileSelection> tileSelection;
    std::unique_ptr<CurrentlySelectedTile> curSelectedTile;

    QComboBox* layerComboBox;

    // menu pointer variables
    QMenuBar* menuBar;
    QMenu* fileMenu;
    QAction* newAction;
    QAction* openAction;
    QAction* loadAction;
    QAction* saveAction;
    QAction* exitAction;

    QMenu* editMenu;
    QAction* undoAction;
    QAction* redoAction;

    QMenu* optionsMenu;
    QAction* displayGridAction;
    QAction* fillWithSelectedTile;
    QAction* addToPopularTile;

    QMenu* tileMenu;
    QAction* makeAnimatedTile;

    QMenu* helpMenu;
    QAction* aboutAction;

    QDialog* d;
};

#endif // MAINWINDOW_H
