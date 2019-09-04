#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <vector>

enum GameType
{
    PERSON,
    BOT
};

enum GameStatus
{
    IDLE,
    PLAYING,
    WIN,
    DEAD,
    QUIT
};

//棋盤尺寸
const int kBoardSizeNum = 15;

class GameModel
{
public:
    GameModel();

public:
    std::vector<std::vector<int>> gameMapVec; // 儲存當前棋盤的狀態 空白0，黑子1，白子-1
    std::vector<std::vector<int>> scoreMapVec; // 儲存評分狀態
    bool playerFlag; // 下棋方
    GameType gameType; // 遊戲模式
    GameStatus gameStatus; // 遊戲狀態

    void startGame(GameType type); // 開始遊戲
    void calculateScore(); // 計算評分
    void actionByPerson(int row, int col); // 人下棋
    void actionByAI(int &clickRow, int &clickCol); // AI下棋
    void updateGameMap(int row, int col); // 每次下棋更新棋盤
    bool isWin(int row, int col); // 判斷贏局
    bool isDeadGame(); // 判断和棋
};

#endif // GAMEMODEL_H
