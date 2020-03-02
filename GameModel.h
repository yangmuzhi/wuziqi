#ifndef GAMEMODEL_H
#define GAMEMODEL_H

// ---- 五子棋游戏模型类 ---- //
#include <vector>

// // 游戏类型，双人还是AI（目前固定让AI下黑子）

// // 游戏状态
const int PLAYING=0, WIN=1, DEAD=2;

// 棋盘尺寸
const int kBoardSizeNum = 15;
const int num_feature = 4; // feature的数量

class GameModel
{
public:
    GameModel();

public:
    std::vector<std::vector<int>> gameMapVec; // 存储当前游戏棋盘和棋子的情况,空白为0，白子1，黑子-1
    bool playerFlag; // 标示下棋方
    int gameStatus; // 游戏状态
    
    // std::vector<std::vector<std::vector<int>>> feature; // 储存特征 Nx15x15
    
    void startGame(); // 开始游戏
    void actionByPerson(int row, int col); // 人执行下棋
    void updateGameMap(int row, int col); // 每次落子后更新游戏棋盘
    bool isWin(int row, int col); // 判断游戏是否胜利
    bool isDeadGame(); // 判断是否和棋
    std::vector<std::vector<int>> getmap();
    std::vector<std::vector<std::vector<int>>> get_feature(bool playerFlag); // get feature Nx15x15
    std::vector<int> action0_vec_row; // action history
    std::vector<int> action0_vec_col; // action history
    std::vector<int> action1_vec_row; // action history
    std::vector<int> action1_vec_col; // action history

    private:
        std::vector<std::vector<int>> empty_vec(int playerflag);//
        std::vector<std::vector<int>> make_action_history(int flag, int step);
};

#endif // GAMEMODEL_H
