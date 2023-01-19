#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class TileSelection;
class TileMapRender;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mousePressEvent(QMouseEvent* event);
    void setupMenubar();

private slots:
    void updateCollisionButton();
    void receiveConsoleMessage(QString);

private:
    Ui::MainWindow *ui;

    TileSelection* tileSelection;
    TileMapRender* tileMap;

    QString* messageOutput;

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

    bool collisionButtonToggle;
};
#endif // MAINWINDOW_H
