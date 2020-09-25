#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("GTE Editor (v0.1)");

    setupTileMapRender();

    setupTileSelection();
    setupCurrentlySelectedTile();

    setupSignalsSlots();

    setupMenubar();
}

MainWindow::~MainWindow() {

    delete ui;
}

//////////

void MainWindow::setupSignalsSlots() {
    // selection checkboxes - to detemine which layers are rendered

    /*
    QObject::connect(ui->checkBox_Layer1, SIGNAL(clicked()), tileMapRender, SLOT(selectLayerOne()));
    QObject::connect(ui->checkBox_Layer2, SIGNAL(clicked()), tileMapRender, SLOT(selectLayerTwo()));
    QObject::connect(ui->checkBox_Layer3, SIGNAL(clicked()), tileMapRender, SLOT(selectLayerThree()));
    QObject::connect(ui->checkBox_Layer4, SIGNAL(clicked()), tileMapRender, SLOT(selectLayerFour()));
    QObject::connect(ui->checkBox_Collision, SIGNAL(clicked()), tileMapRender, SLOT(selectLayerCollision()));

    //combobox selection indicates the layer to render to
    layerComboBox = ui->comboBox;
    QObject::connect(layerComboBox, SIGNAL(currentIndexChanged(int)), tileMapRender, SLOT(selectLayer(int)));
    */

    // signals received from tile map render to update combobox (from the numerical keypress [layers])
   // QObject::connect(tileMapRender, SIGNAL(updateLayerValue(int)), layerComboBox, SLOT(setCurrentIndex(int)));


    // Passing tiles
    // sending currently selected tile to the widget
    //QObject::connect(tileSelection, SIGNAL(selectedTileImage(QImage)), curSelectedTile, SLOT(receiveSelectedTile(QImage)));
    // and to the main tileMapRender object
    //QObject::connect(tileSelection, SIGNAL(selectedTileImage(QImage)), tileMapRender, SLOT(updateSelectedTile(QImage)));

}

// the scrollbars for TileMapRender are handled internally
// by that object.
void MainWindow::setupTileMapRender() {
    tileMapRender = std::make_unique<TileMapRender>(1600, 1200);

    /*
    QScrollArea* mapScrollArea = ui->scrollArea;
    mapScrollArea->setWidget(tileMapRender);
    mapScrollArea->show(); // as per documentation
    */
}

void MainWindow::setupTileSelection() {

    tileSelection = std::make_unique<TileSelection>();
    //QScrollArea* tileScrollArea = ui->scrollAreaTileSelection;

    //tileScrollArea->setWidget(tileSelection);

}

void MainWindow::setupCurrentlySelectedTile() {

    curSelectedTile = std::make_unique<CurrentlySelectedTile>();
    //ui->verticalLayout_2->addWidget(curSelectedTile, Qt::AlignCenter);
}

void MainWindow::setupMenubar() {

    //menuBar = new QMenuBar(this);
    menuBar = ui->menubar;

    ///// FILE DROPDOWN MENU
    fileMenu = new QMenu(tr("&File"));
    //fileMenu->addMenu(new QMenu("test"));
    newAction = new QAction(tr("New"), this);
    fileMenu->addAction(newAction);

    QObject::connect(newAction, SIGNAL(triggered()), this, SLOT(newMap()));

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


void MainWindow::newMap() {
    qDebug() << "yup";
    d = new QDialog;
    d->show();
}


