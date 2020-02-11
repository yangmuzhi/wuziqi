#ifndef GAMEMODEL_H
#define GAMEMODEL_H

// ---- 五子棋游戏模型类 ---- //
#include <vector>

// // 游戏类型，双人还是AI（目前固定让AI下黑子）

// // 游戏状态
const int PLAYING=0, WIN=1, DEAD=2;

// 棋盘尺寸
const int kBoardSizeNum = 15;

class GameModel
{
public:
    GameModel();

public:
    std::vector<std::vector<int>> gameMapVec; // 存储当前游戏棋盘和棋子的情况,空白为0，白子1，黑子-1
    bool playerFlag; // 标示下棋方
    int gameStatus; // 游戏状态

    void startGame(); // 开始游戏
    void actionByPerson(int row, int col); // 人执行下棋
    void updateGameMap(int row, int col); // 每次落子后更新游戏棋盘
    bool isWin(int row, int col); // 判断游戏是否胜利
    bool isDeadGame(); // 判断是否和棋
    std::vector<std::vector<int>> getmap();
};

#endif // GAMEMODEL_H
