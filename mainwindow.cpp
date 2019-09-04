#include <QPainter>
#include <QTimer>
#include <QSound>
#include <QMouseEvent>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <math.h>
#include <QKeyEvent>
#include "mainwindow.h"
#include <windows.h>

bool AI;
int j = 0;
int i = 0;
#define CHESS_ONE_SOUND ":/sound/chessone.wav"
#define WIN_SOUND ":/sound/win.wav"
#define LOSE_SOUND ":/sound/lose.wav"
const int kBoardMargin = 30; // 棋盤邊緣空隙
const int kRadius = 15; // 棋子半徑
const int kMarkSize = 6; // 落子標記邊長
const int kBlockSize = 40; // 格子大小
const int kPosDelta = 20; // 滑鼠點擊模糊距離上限
const int kAIDelay = 70; // AI下棋的思考時間
bool ai;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setFixedSize(kBoardMargin * 2 + kBlockSize * kBoardSizeNum, kBoardMargin * 2 + kBlockSize * kBoardSizeNum);
//    setStyleSheet("background-color:yellow;");

    setMouseTracking(true);
    //  centralWidget()->setMouseTracking(true);

    QMenu *gameMenu = menuBar()->addMenu(tr("Setting"));
    QAction *actionPVP = new QAction("Person VS Person", this);
    connect(actionPVP, SIGNAL(triggered()), this, SLOT(initPVPGame()));
    gameMenu->addAction(actionPVP);

    QAction *actionPVE = new QAction("Person VS Computer", this);
    connect(actionPVE, SIGNAL(triggered()), this, SLOT(initPVEGame()));
    gameMenu->addAction(actionPVE);\

    QAction *actionPVT = new QAction("Special", this);
    connect(actionPVT, SIGNAL(triggered()), this, SLOT(initPVTGame()));
    gameMenu->addAction(actionPVT);
/*
    QAction *actionStart = new QAction("Prepare Game", this);
    connect(actionStart, SIGNAL(triggered()), this, SLOT(initStartGame()));
    gameMenu->addAction(actionStart);
*/
    QAction *actionQuit = new QAction("I want to quit this fucking game", this);
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(initQuitGame()));
    gameMenu->addAction(actionQuit);



    /*QMenu *gameMenu1 = menuBar()->addMenu(tr("chess"));
    QAction *actionPVa = new QAction("black", this);
    connect(actionPVa, SIGNAL(triggered()), this, SLOT(initPVPGame()));
    brush.setColor(Qt::black);
    gameMenu1->addAction(actionPVa);

    QAction *actionPVb = new QAction("white", this);
    connect(actionPVb, SIGNAL(triggered()), this, SLOT(initPVPGame()));
    brush.setColor(Qt::white);
    gameMenu1->addAction(actionPVb);

*/
    //this->setFixedSize(700,700);
    bgm = new easyMusic("sound/bj.mp3",80,0);
    fgm = new easyMusic("sound/fg.mp3",100,0);
    //bg =new easyMusic("sound/chessone.mp3",80,0);

    initGame(); //開始遊戲
}

MainWindow::
MainWindow::~MainWindow()
{
    if (game)
    {
        delete game;
        game = nullptr;
    }
}

void MainWindow::initGame()
{
    game = new GameModel;
    initStartGame();
}

void MainWindow::initPVPGame()
{
    game_type = PERSON;
    ai = true;
    game->gameStatus = PLAYING;
   bgm->stop();
   fgm->stop();
    game->startGame(game_type);
    update();
}

void MainWindow::initPVEGame()
{
    game_type = BOT;
    ai = true;
    game->gameStatus = PLAYING;
    bgm->stop();
    fgm->stop();
    game->startGame(game_type);
    update();
}

void MainWindow::initPVTGame()
{
    game_type = BOT;
    ai = false;
    bgm->stop();
    fgm->stop();
    game->gameStatus = PLAYING;
    game->startGame(game_type);
    update();
}

void MainWindow::initStartGame()
{
    if(AI) game_type = BOT;
    else game_type = PERSON;
    bgm->play();
     fgm->stop();
    game->gameStatus = IDLE;
    game->startGame(game_type);
    update();
}

void MainWindow::initQuitGame()
{
    bgm->stop();
    fgm->play();
    game->gameStatus = QUIT;
    game->startGame(game_type);
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if(game->gameStatus==IDLE){
    QString redypic[100];
/*
    redypic[0] = ":/Image/042.jpg";
    redypic[1] = ":/Image/085.jpg";
    redypic[2] = ":/Image/106.jpg";
    redypic[3] = ":/Image/152.jpg";
    redypic[4] = ":/Image/209.jpg";
    redypic[5] = ":/Image/254.jpg";
    redypic[6] = ":/Image/297.jpg";
    redypic[7] = ":/Image/339.jpg";
    redypic[8] = ":/Image/382.jpg";
    redypic[9] = ":/Image/422.jpg";
*/
    redypic[0] = ":/Image/1 (1).jpg";
    redypic[1] = ":/Image/1 (2).jpg";
    redypic[2] = ":/Image/1 (3).jpg";
    redypic[3] = ":/Image/1 (4).jpg";
    redypic[4] = ":/Image/1 (5).jpg";
    redypic[5] = ":/Image/1 (6).jpg";
    redypic[6] = ":/Image/1 (7).jpg";
    redypic[7] = ":/Image/1 (8).jpg";
    redypic[8] = ":/Image/1 (9).jpg";
    redypic[9] = ":/Image/1 (10).jpg";
    redypic[10] = ":/Image/1 (11).jpg";
    redypic[11] = ":/Image/1 (12).jpg";
    redypic[12] = ":/Image/1 (13).jpg";
    redypic[13] = ":/Image/1 (14).jpg";
    redypic[14] = ":/Image/1 (15).jpg";
    redypic[15] = ":/Image/1 (16).jpg";
    redypic[16] = ":/Image/1 (17).jpg";
    redypic[17] = ":/Image/1 (18).jpg";
    redypic[18] = ":/Image/1 (19).jpg";
    redypic[19] = ":/Image/1 (20).jpg";
    redypic[20] = ":/Image/1 (21).jpg";
    redypic[21] = ":/Image/1 (22).jpg";
    redypic[22] = ":/Image/1 (23).jpg";
    redypic[23] = ":/Image/1 (24).jpg";
    redypic[24] = ":/Image/1 (25).jpg";
    redypic[25] = ":/Image/1 (26).jpg";
    redypic[26] = ":/Image/1 (27).jpg";
    redypic[27] = ":/Image/1 (28).jpg";
    redypic[28] = ":/Image/1 (29).jpg";
    redypic[29] = ":/Image/1 (30).jpg";
    redypic[30] = ":/Image/1 (31).jpg";
    redypic[31] = ":/Image/1 (32).jpg";
    redypic[32] = ":/Image/1 (33).jpg";
    redypic[33] = ":/Image/1 (34).jpg";
    redypic[34] = ":/Image/1 (35).jpg";
    redypic[35] = ":/Image/1 (36).jpg";
    redypic[36] = ":/Image/1 (37).jpg";
    redypic[37] = ":/Image/1 (38).jpg";
    redypic[38] = ":/Image/1 (39).jpg";
    redypic[39] = ":/Image/1 (40).jpg";
    redypic[40] = ":/Image/1 (41).jpg";
    redypic[41] = ":/Image/1 (42).jpg";
    redypic[42] = ":/Image/1 (43).jpg";
    redypic[43] = ":/Image/1 (44).jpg";
    redypic[44] = ":/Image/1 (45).jpg";
    redypic[45] = ":/Image/1 (46).jpg";
    redypic[46] = ":/Image/1 (47).jpg";
    redypic[47] = ":/Image/1 (48).jpg";
    redypic[48] = ":/Image/1 (49).jpg";
    redypic[49] = ":/Image/1 (50).jpg";
    redypic[50] = ":/Image/1 (51).jpg";
    redypic[51] = ":/Image/1 (52).jpg";
    redypic[52] = ":/Image/1 (53).jpg";
    redypic[53] = ":/Image/1 (54).jpg";
    redypic[54] = ":/Image/1 (55).jpg";
    redypic[55] = ":/Image/1 (56).jpg";
    redypic[56] = ":/Image/1 (57).jpg";
    redypic[57] = ":/Image/1 (58).jpg";
    redypic[58] = ":/Image/1 (59).jpg";
    redypic[59] = ":/Image/1 (60).jpg";
    redypic[60] = ":/Image/1 (61).jpg";
    redypic[61] = ":/Image/1 (62).jpg";
    redypic[62] = ":/Image/1 (63).jpg";
    redypic[63] = ":/Image/1 (64).jpg";
    redypic[64] = ":/Image/1 (65).jpg";
    redypic[65] = ":/Image/1 (66).jpg";
    redypic[66] = ":/Image/1 (67).jpg";
    redypic[67] = ":/Image/1 (68).jpg";
    redypic[68] = ":/Image/1 (69).jpg";
    redypic[69] = ":/Image/1 (70).jpg";
    redypic[70] = ":/Image/1 (71).jpg";
    redypic[71] = ":/Image/1 (72).jpg";
    redypic[72] = ":/Image/1 (73).jpg";
    redypic[73] = ":/Image/1 (74).jpg";
    redypic[74] = ":/Image/1 (75).jpg";
    redypic[75] = ":/Image/1 (76).jpg";
    redypic[76] = ":/Image/1 (77).jpg";
    redypic[77] = ":/Image/1 (78).jpg";
    redypic[78] = ":/Image/1 (79).jpg";
    redypic[79] = ":/Image/1 (80).jpg";
    redypic[80] = ":/Image/1 (81).jpg";
    redypic[81] = ":/Image/1 (82).jpg";
    redypic[82] = ":/Image/1 (83).jpg";
    redypic[83] = ":/Image/1 (84).jpg";
    redypic[84] = ":/Image/1 (86).jpg";
    redypic[85] = ":/Image/1 (87).jpg";
    redypic[86] = ":/Image/1 (88).jpg";
    redypic[87] = ":/Image/1 (89).jpg";
    redypic[88] = ":/Image/1 (90).jpg";
    redypic[89] = ":/Image/1 (91).jpg";
    redypic[90] = ":/Image/1 (92).jpg";
    redypic[91] = ":/Image/1 (93).jpg";
    redypic[92] = ":/Image/1 (94).jpg";
    redypic[93] = ":/Image/1 (95).jpg";
    redypic[95] = ":/Image/1 (96).jpg";
    redypic[96] = ":/Image/1 (97).jpg";
    redypic[97] = ":/Image/1 (98).jpg";
    redypic[98] = ":/Image/1 (99).jpg";
    redypic[99] = ":/Image/1 (85).jpg";

    QPixmap redybgimage;

    redybgimage.load(redypic[j%100]);
    if(j==99){
       // j=0;
        redybgimage.load(":/Image/1 (85).jpg");

    }
    else j++;
    painter.drawPixmap(0,0,670,720,redybgimage);
    Sleep(140);
    update();
}
    if(game->gameStatus==QUIT){
        QString redypic1[56];

        redypic1[0] = ":/Image/2 (1).jpg";
        redypic1[1] = ":/Image/2 (2).jpg";
        redypic1[2] = ":/Image/2 (3).jpg";
        redypic1[3] = ":/Image/2 (4).jpg";
        redypic1[4] = ":/Image/2 (5).jpg";
        redypic1[5] = ":/Image/2 (6).jpg";
        redypic1[6] = ":/Image/2 (7).jpg";
        redypic1[7] = ":/Image/2 (8).jpg";
        redypic1[8] = ":/Image/2 (9).jpg";
        redypic1[9] = ":/Image/2 (10).jpg";
        redypic1[10] = ":/Image/2 (11).jpg";
        redypic1[11] = ":/Image/2 (12).jpg";
        redypic1[12] = ":/Image/2 (13).jpg";
        redypic1[13] = ":/Image/2 (14).jpg";
        redypic1[14] = ":/Image/2 (15).jpg";
        redypic1[15] = ":/Image/2 (16).jpg";
        redypic1[16] = ":/Image/2 (17).jpg";
        redypic1[17] = ":/Image/2 (18).jpg";
        redypic1[18] = ":/Image/2 (19).jpg";
       redypic1[19] = ":/Image/2 (20).jpg";
        redypic1[20] = ":/Image/2 (21).jpg";
        redypic1[21] = ":/Image/2 (22).jpg";
        redypic1[22] = ":/Image/2 (23).jpg";
        redypic1[23] = ":/Image/2 (24).jpg";
        redypic1[24] = ":/Image/2 (25).jpg";
        redypic1[25] = ":/Image/2 (26).jpg";
        redypic1[26] = ":/Image/2 (27).jpg";
        redypic1[27] = ":/Image/2 (28).jpg";
        redypic1[28] = ":/Image/2 (29).jpg";
        redypic1[29] = ":/Image/2 (30).jpg";
        redypic1[30] = ":/Image/2 (31).jpg";
        redypic1[31] = ":/Image/2 (32).jpg";
        redypic1[32] = ":/Image/2 (33).jpg";
        redypic1[33] = ":/Image/2 (34).jpg";
        redypic1[34] = ":/Image/2 (35).jpg";
        redypic1[35] = ":/Image/2 (36).jpg";
        redypic1[36] = ":/Image/2 (37).jpg";
        redypic1[37] = ":/Image/2 (38).jpg";
        redypic1[38] = ":/Image/2 (39).jpg";
        redypic1[39] = ":/Image/2 (40).jpg";
        redypic1[40] = ":/Image/2 (41).jpg";
        redypic1[41] = ":/Image/2 (42).jpg";
        redypic1[42] = ":/Image/2 (43).jpg";
        redypic1[43] = ":/Image/2 (44).jpg";
        redypic1[44] = ":/Image/2 (45).jpg";
        redypic1[45] = ":/Image/2 (46).jpg";
        redypic1[46] = ":/Image/2 (47).jpg";
        redypic1[47] = ":/Image/2 (48).jpg";
        redypic1[48] = ":/Image/2 (49).jpg";
        redypic1[49] = ":/Image/2 (50).jpg";
        redypic1[50] = ":/Image/2 (51).jpg";
        redypic1[51] = ":/Image/2 (52).jpg";
        redypic1[52] = ":/Image/2 (53).jpg";
        redypic1[53] = ":/Image/2 (54).jpg";
        redypic1[54] = ":/Image/2 (55).jpg";
        redypic1[55] = ":/Image/2 (56).jpg";



        QPixmap redybgimage1;

        redybgimage1.load(redypic1[i%56]);
        if(i==55){
           // j=0;
            redybgimage1.load(":/Image/1 (85).jpg");

        }
        else i++;
        painter.drawPixmap(0,0,670,720,redybgimage1);
        Sleep(200);
        update();
    }


    if(game->gameStatus==PLAYING){

    QPixmap bgImg;
    bgImg.load(":/sound/bg.jpg");
    painter.drawPixmap(0,0,700,700,bgImg);

    painter.setRenderHint(QPainter::Antialiasing, true);
    //QPen pen;
    //pen.setWidth(2);
    //painter.setPen(pen);
    for (int i = 0; i < kBoardSizeNum + 1; i++)
    {
        painter.drawLine(kBoardMargin + kBlockSize * i, kBoardMargin, kBoardMargin + kBlockSize * i, size().height() - kBoardMargin);
        painter.drawLine(kBoardMargin, kBoardMargin + kBlockSize * i, size().width() - kBoardMargin, kBoardMargin + kBlockSize * i);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if (clickPosRow > 0 && clickPosRow < kBoardSizeNum &&
        clickPosCol > 0 && clickPosCol < kBoardSizeNum &&
        game->gameMapVec[clickPosRow][clickPosCol] == 0)
    {
        if (game->playerFlag)
            brush.setColor(Qt::black);
        else
            brush.setColor(Qt::white);
        painter.setBrush(brush);
        painter.drawRect(kBoardMargin + kBlockSize * clickPosCol - kMarkSize / 2, kBoardMargin + kBlockSize * clickPosRow - kMarkSize / 2, kMarkSize, kMarkSize);
    }

    for (int i = 0; i < kBoardSizeNum; i++)
        for (int j = 0; j < kBoardSizeNum; j++)
        {
            if (game->gameMapVec[i][j] == 1)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius, kRadius * 2, kRadius * 2);
            }
            else if (game->gameMapVec[i][j] == -1)
            {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(kBoardMargin + kBlockSize * j - kRadius, kBoardMargin + kBlockSize * i - kRadius, kRadius * 2, kRadius * 2);
            }
        }

    if (clickPosRow > 0 && clickPosRow < kBoardSizeNum &&
        clickPosCol > 0 && clickPosCol < kBoardSizeNum &&
        (game->gameMapVec[clickPosRow][clickPosCol] == 1 ||
            game->gameMapVec[clickPosRow][clickPosCol] == -1))
    {
        if (game->isWin(clickPosRow, clickPosCol) && game->gameStatus == PLAYING)
        {
            qDebug() << "win";
            game->gameStatus = WIN;
            QSound::play(WIN_SOUND);
           // QSound::stop(WIN_SOUND);

            QString str;
            if (game->gameMapVec[clickPosRow][clickPosCol] == 1)
                str = "white player";
            else if (game->gameMapVec[clickPosRow][clickPosCol] == -1)
                str = "black player";
            QMessageBox::StandardButton btnValue = QMessageBox::information(this, "Winner", str + " win!");

            if (btnValue == QMessageBox::Ok)
            {

                //QSound::stop();
                game->startGame(game_type);
                game->gameStatus = PLAYING;
            }
        }
    }


    if (game->isDeadGame())
    {
        QSound::play(LOSE_SOUND);
        QMessageBox::StandardButton btnValue = QMessageBox::information(this, "oops", "dead game!");
        if (btnValue == QMessageBox::Ok)
        {
            game->startGame(game_type);
            game->gameStatus = PLAYING;
        }

    }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    int x = event->x();
    int y = event->y();

    // 棋盤邊緣不能有棋子
    if (x >= kBoardMargin + kBlockSize / 2 &&
            x < size().width() - kBoardMargin &&
            y >= kBoardMargin + kBlockSize / 2 &&
            y < size().height()- kBoardMargin)
    {

        int col = x / kBlockSize;
        int row = y / kBlockSize;

        int leftTopPosX = kBoardMargin + kBlockSize * col;
        int leftTopPosY = kBoardMargin + kBlockSize * row;

        clickPosRow = -1;
        clickPosCol = -1;
        int len = 0;

        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < kPosDelta)
        {
            clickPosRow = row;
            clickPosCol = col + 1;
        }
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - kBlockSize) * (y - leftTopPosY - kBlockSize));
        if (len < kPosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col;
        }
        len = sqrt((x - leftTopPosX - kBlockSize) * (x - leftTopPosX - kBlockSize) + (y - leftTopPosY - kBlockSize) * (y - leftTopPosY - kBlockSize));
        if (len < kPosDelta)
        {
            clickPosRow = row + 1;
            clickPosCol = col + 1;
        }
    }

    update();

}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
 if(event->button()==Qt::LeftButton)
 {
    // bgm->play();
 }
}
 void MainWindow::keyPressEvent(QKeyEvent *event)
{
 if(event->key()==Qt::Key_Space || event->key()==Qt::Key_Up)
 {
     //bgm->play();
     if(ai==false){
         QTimer::singleShot(kAIDelay, this, SLOT(chessOneByAI()));
         if (!(game_type == BOT && !game->playerFlag))
         {
             QTimer::singleShot(kAIDelay, this, SLOT(chessOneByAI()));

              if (game->gameType == BOT && !game->playerFlag)
             {

                 QTimer::singleShot(kAIDelay, this, SLOT(chessOneByAI()));

             }
         }
     }
 }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(ai==true){

        if (!(game_type == BOT && !game->playerFlag))
        {
            chessOneByPerson();

            if (game->gameType == BOT && !game->playerFlag)
            {

                QTimer::singleShot(kAIDelay, this, SLOT(chessOneByAI()));
            }
        }
    }
   /* else{
        QTimer::singleShot(kAIDelay, this, SLOT(chessOneByAI()));
        if (!(game_type == BOT && !game->playerFlag))
        {
            QTimer::singleShot(kAIDelay, this, SLOT(chessOneByAI()));

             if (game->gameType == BOT && !game->playerFlag)
            {

                QTimer::singleShot(kAIDelay, this, SLOT(chessOneByAI()));

            }
        }

    }*/
}

void MainWindow::chessOneByPerson()
{

    if (clickPosRow != -1 && clickPosCol != -1 && game->gameMapVec[clickPosRow][clickPosCol] == 0)
    {
        game->actionByPerson(clickPosRow, clickPosCol);
        QSound::play(CHESS_ONE_SOUND);

        update();
    }
}

void MainWindow::chessOneByAI()
{
    game->actionByAI(clickPosRow, clickPosCol);
    QSound::play(CHESS_ONE_SOUND);
    update();
}

