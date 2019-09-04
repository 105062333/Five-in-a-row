#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GameModel.h"
#include"easymusic.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent*event);
    void mousePressEvent(QMouseEvent *event);


private:
    GameModel *game;
    GameType game_type; // 儲存遊戲類型
    int clickPosRow, clickPosCol; // 儲存要點擊的位置
    void initGame();
    void checkGame(int y, int x);
    easyMusic *bgm;
    easyMusic *fgm;

private slots:
    void chessOneByPerson();
    void chessOneByAI();
    void initPVPGame();
    void initPVEGame();
    void initPVTGame();
    void initStartGame();
    void initQuitGame();
};

#endif // MAINWINDOW_H
