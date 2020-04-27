#ifndef GAMEMODEL_H
#define GAMEMODEL_H

// ---- 五子棋游戏模型类 ---- //
#include <vector>

// 游戏类型，双人还是AI（目前固定让AI下黑子）

//  游戏状态
const int PLAYING=0, WIN=1, DEAD=2;

// 棋盘尺寸
const int kBoardSizeNum = 15;
const int nFeature = 5;

class GameModel
{
public:
    GameModel();

public:
    std::vector<std::vector<int> > gameMapVec; // 存储当前游戏棋盘和棋子的情况,空白为0，白子1，黑子-1
    std::vector<std::vector<std::vector<int> > > featureTensor0; // flag=0 储存feature tensor, n * size**2
    std::vector<std::vector<std::vector<int> > > featureTensor1; // flag=1 储存feature tensor, n * size**2
    
    bool playerFlag; // 标示下棋方
    int gameStatus; // 游戏状态
    
    // std::vector<std::vector<std::vector<int>>> feature; // 储存特征 Nx15x15
    
    void startGame(); // 开始游戏
    void actionByPerson(int row, int col); // 人执行下棋
    void updateGameMap(int row, int col); // 每次落子后更新游戏棋盘
    void updatefeature(int row, int col); // // update feature by step
    bool isWin(int row, int col); // 判断游戏是否胜利
    bool isDeadGame(); // 判断是否和棋
    std::vector<std::vector<int> > getmap();
    std::vector<std::vector<std::vector<int> > > get_feature(bool flag); // n * size**2
};

#endif // GAMEMODEL_H
