#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "tile_selection.h"
#include "tile_map_render.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupMenubar();

    collisionButtonToggle = false;


    tileSelection = new TileSelection(ui->graphicsView);
    tileMap = new TileMapRender(1024, 768, ui->graphicsView_3);


    // Passing tiles
    // sending currently selected tile to the widget
    //QObject::connect(tileSelection, SIGNAL(selectedTileImage(QImage)), tileSelection, SLOT(receiveSelectedTile(QImage)));
    // and to the main tileMapRender object
    QObject::connect(
        tileSelection, SIGNAL(selectedTileImage(QImage)),
        tileMap, SLOT(updateSelectedTile(QImage))
    );
    QObject::connect(
        tileSelection, SIGNAL(newTilesheetLoad(QString)),
        tileMap, SLOT(loadNewTilesheet(QString))
    );
    QObject::connect(
        ui->fillAllButton, SIGNAL(clicked()),
        tileMap, SLOT(tileFill())
    );
    QObject::connect(
        ui->collisionPushButton, SIGNAL(clicked()),
        this, SLOT(updateCollisionButton())
    );
    QObject::connect(
        ui->loadTilesheetPushButton, SIGNAL(clicked()),
        tileSelection, SLOT(loadTilesheet())
    );


    messageOutput = new QString();
    messageOutput->append("GTEE v0.1 (testing)\n");

    ui->label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    ui->label->setText(*messageOutput);

    QObject::connect(
        tileSelection, SIGNAL(sendConsoleMessage(QString)),
        this, SLOT(receiveConsoleMessage(QString))
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent* event) {

    qDebug() << event->pos();
    if (event->button() == Qt::LeftButton) {

        // the absolute mouse click value is reduced or "clipped"
        // down so that tile value increments are stored
       // curTileX = ((event->x() + hScrollOffset) / 32) * 32; // the horizontal scrollbar offset is added here!
        //curTileY = ((event->y() + vScrollOffset) / 32) * 32; // the vertical scrollbar offset is addded here!

        // emit signal for mouse click
        //emit leftClickMouse();
    }
}


void MainWindow::setupMenubar() {

    //menuBar = new QMenuBar(this);
    menuBar = ui->menubar;

    ///// FILE DROPDOWN MENU
    fileMenu = new QMenu(tr("&File"));
    //fileMenu->addMenu(new QMenu("test"));
    newAction = new QAction(tr("New"), this);
    fileMenu->addAction(newAction);

    //QObject::connect(newAction, SIGNAL(triggered()), this, SLOT(newMap()));

    openAction = new QAction(tr("Open"), this);
    fileMenu->addAction(openAction);

    loadAction = new QAction(tr("Load"), this);
    fileMenu->addAction(loadAction);

    saveAction = new QAction(tr("Save"), this);
    fileMenu->addAction(saveAction);

    exitAction = new QAction(tr("Exit"), this);
    fileMenu->addAction(exitAction);

    menuBar->addMenu(fileMenu);

    ///// EDIT DROPDOWN MENU

    editMenu = new QMenu(tr("&Edit"));

    undoAction = new QAction(tr("Undo"), this);
    editMenu->addAction(undoAction);

    redoAction = new QAction(tr("Redo"), this);
    editMenu->addAction(redoAction);

    menuBar->addMenu(editMenu);

    ///// OPTIONS DROPDOWN MENU

    optionsMenu = new QMenu(tr("&Options"));
    displayGridAction = new QAction(tr("Grid Overlay"), this);
    displayGridAction->setCheckable(true);
    //QObject::connect(displayGridAction, SIGNAL(toggled(bool)), tileMapRender, SLOT(drawGridOverlay(bool)));

    ///
    fillWithSelectedTile = new QAction(tr("Fill Map With Tile"), this); // dangerous !
    addToPopularTile = new QAction(tr("Add to popular Tile"), this);
    optionsMenu->addAction(displayGridAction);
    optionsMenu->addAction(fillWithSelectedTile);
    optionsMenu->addAction(addToPopularTile);

    menuBar->addMenu(optionsMenu);


    ///// TILE EDITING MENU

    tileMenu = new QMenu(tr("&Tile"));
    makeAnimatedTile = new QAction(tr("Make Animated Tile"));
    tileMenu->addAction(makeAnimatedTile);

    menuBar->addMenu(tileMenu);

    ///// HELP DROPDOWN MENU

    helpMenu = new QMenu(tr("&Help"));
    aboutAction = new QAction(tr("About"), this);
    helpMenu->addAction(aboutAction);

    menuBar->addMenu(helpMenu);
}

void MainWindow::updateCollisionButton() {

    collisionButtonToggle = !collisionButtonToggle;

    if (collisionButtonToggle) {
        ui->collisionPushButton->setStyleSheet("QPushButton { background-color: grey; }\n"
                              "QPushButton:enabled { background-color: rgb(255,0,0); }\n");
    }
    else {
        ui->collisionPushButton->setStyleSheet("QPushButton { background-color: grey; }\n"
                              "QPushButton:enabled { background-color: light grey; }\n");
    }
}

void MainWindow::receiveConsoleMessage(QString msg) {
    messageOutput->append(msg + "\n");
    ui->label->setText(*messageOutput);
}
