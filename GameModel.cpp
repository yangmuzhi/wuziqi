#include <utility>
#include <stdlib.h>
#include <time.h>
#include "GameModel.h"

GameModel::GameModel()
{

}

void GameModel::startGame()
{

    // 初始棋盘
    gameMapVec.clear();
    for (int i = 0; i < kBoardSizeNum; i++)
    {
        std::vector<int> lineBoard;
        for (int j = 0; j < kBoardSizeNum; j++)
            lineBoard.push_back(0);
        gameMapVec.push_back(lineBoard);
    }

    // 初始化feature
    // feature.clear();
    // for (int m = 0;m<num_feature; m++)
    // {
    //     std::vector<std::vector<int>> feature_vec;
    //     for (int i = 0; i < kBoardSizeNum; i++)
    //     {
    //         std::vector<int> line_feature;
    //         for (int j = 0; j < kBoardSizeNum; j++)
    //             line_feature.push_back(0);
    //         feature_vec.push_back(line_feature);
    //     }
    //     feature.push_back(feature_vec);
    // }

    // 己方下为true,对方下位false
    playerFlag = true;

}

void GameModel::updateGameMap(int row, int col)
{
    if (playerFlag)
        gameMapVec[row][col] = 1;
    else
        gameMapVec[row][col] = -1;

    // 换手
    playerFlag = !playerFlag;
}

void GameModel::actionByPerson(int row, int col)
{
    updateGameMap(row, col);

    // update action history
    if(playerFlag)
    {    
        action0_vec_row.push_back(row);
        action0_vec_col.push_back(col);
    }
    else
    {
        action1_vec_row.push_back(row);
        action1_vec_col.push_back(col);
    }
    
}


bool GameModel::isWin(int row, int col)
{
    // 横竖斜四种大情况，每种情况都根据当前落子往后遍历5个棋子，有一种符合就算赢
    // 水平方向
    for (int i = 0; i < 5; i++)
    {
        // 往左5个，往右匹配4个子，20种情况
        if (col - i > 0 &&
            col - i + 4 < kBoardSizeNum &&
            gameMapVec[row][col - i] == gameMapVec[row][col - i + 1] &&
            gameMapVec[row][col - i] == gameMapVec[row][col - i + 2] &&
            gameMapVec[row][col - i] == gameMapVec[row][col - i + 3] &&
            gameMapVec[row][col - i] == gameMapVec[row][col - i + 4])
            return true;
    }

    // 竖直方向(上下延伸4个)
    for (int i = 0; i < 5; i++)
    {
        if (row - i > 0 &&
            row - i + 4 < kBoardSizeNum &&
            gameMapVec[row - i][col] == gameMapVec[row - i + 1][col] &&
            gameMapVec[row - i][col] == gameMapVec[row - i + 2][col] &&
            gameMapVec[row - i][col] == gameMapVec[row - i + 3][col] &&
            gameMapVec[row - i][col] == gameMapVec[row - i + 4][col])
            return true;
    }

    // 左斜方向
    for (int i = 0; i < 5; i++)
    {
        if (row + i < kBoardSizeNum &&
            row + i - 4 > 0 &&
            col - i > 0 &&
            col - i + 4 < kBoardSizeNum &&
            gameMapVec[row + i][col - i] == gameMapVec[row + i - 1][col - i + 1] &&
            gameMapVec[row + i][col - i] == gameMapVec[row + i - 2][col - i + 2] &&
            gameMapVec[row + i][col - i] == gameMapVec[row + i - 3][col - i + 3] &&
            gameMapVec[row + i][col - i] == gameMapVec[row + i - 4][col - i + 4])
            return true;
    }

    // 右斜方向
    for (int i = 0; i < 5; i++)
    {
        if (row - i > 0 &&
            row - i + 4 < kBoardSizeNum &&
            col - i > 0 &&
            col - i + 4 < kBoardSizeNum &&
            gameMapVec[row - i][col - i] == gameMapVec[row - i + 1][col - i + 1] &&
            gameMapVec[row - i][col - i] == gameMapVec[row - i + 2][col - i + 2] &&
            gameMapVec[row - i][col - i] == gameMapVec[row - i + 3][col - i + 3] &&
            gameMapVec[row - i][col - i] == gameMapVec[row - i + 4][col - i + 4])
            return true;
    }

    return false;
}

bool GameModel::isDeadGame()
{
    // 所有空格全部填满
    for (int i = 1; i < kBoardSizeNum; i++)
        for (int j = 1; j < kBoardSizeNum; j++)
        {
            if (!(gameMapVec[i][j] == 1 || gameMapVec[i][j] == -1))
                return false;
        }
    return true;
}

std::vector<std::vector<int>> GameModel::getmap()
{
    return gameMapVec;
}

std::vector<std::vector<std::vector<int>>> GameModel::get_feature(bool playerflag)
{
    // flag ： 0表示守， 1 表示攻; 
    std::vector<std::vector<std::vector<int>>> feature;
    int flag, is_attack, is_opp;
    // 0: 标明攻守 
    if (playerflag)
    {   
        flag = 1;
        is_attack = 1;
        is_opp = -1;
    }
    else
    {    
        flag = 0;
        is_attack = -1;
        is_opp = 1;
    }
    std::vector<std::vector<int>> feature_vec = empty_vec(flag);
    feature.push_back(feature_vec);

    // 1: 目前的所有的棋子
    // std::vector<std::vector<int>> feature_vec;
    feature_vec.clear();
    for (int i = 0; i < kBoardSizeNum; i++)
    {
        std::vector<int> line_feature;
        for (int j = 0; j < kBoardSizeNum; j++)
            if (gameMapVec[i][j] != 0)
                line_feature.push_back(1);
            else
                line_feature.push_back(0);
        feature_vec.push_back(line_feature);
    }
    feature.push_back(feature_vec);

    // 2: 自己的棋子
    // std::vector<std::vector<int>> feature_vec;
    feature_vec.clear();
    for (int i = 0; i < kBoardSizeNum; i++)
    {
        std::vector<int> line_feature;
        for (int j = 0; j < kBoardSizeNum; j++)
            if( gameMapVec[i][j] == is_attack)
                line_feature.push_back(1);
            else
                line_feature.push_back(0);
        feature_vec.push_back(line_feature);
    }
    feature.push_back(feature_vec);

    // 3: 对手的棋子
    // std::vector<std::vector<int>> feature_vec;
    feature_vec.clear();
    for (int i = 0; i < kBoardSizeNum; i++)
    {
        std::vector<int> line_feature;
        for (int j = 0; j < kBoardSizeNum; j++)
            if (gameMapVec[i][j] == is_opp)
                line_feature.push_back(1);
            else
                line_feature.push_back(0);
        feature_vec.push_back(line_feature);
    }
    feature.push_back(feature_vec);
    // 4: 没有下棋的位置
    // std::vector<std::vector<int>> feature_vec;
    feature_vec.clear();
    for (int i = 0; i < kBoardSizeNum; i++)
    {
        std::vector<int> line_feature;
        for (int j = 0; j < kBoardSizeNum; j++)
            if (gameMapVec[i][j] == 0)
                line_feature.push_back(1);
            else
                line_feature.push_back(0);
        feature_vec.push_back(line_feature);
    }
    feature.push_back(feature_vec);

    // 5 自己历史手牌的位置 stack 最近5步
    for (int step=0; step<5; step++)
    {
        feature_vec = make_action_history(1, step);
        feature.push_back(feature_vec);
    }

    // 6 对手历史手牌的位置 stack 最近5步
    for (int step=0; step<5; step++)
    {
        feature_vec = make_action_history(0, step);
        feature.push_back(feature_vec);
    }
    

    return  feature;
}


//  action history
// flag player flag, step: time step, from 0 to N
std::vector<std::vector<int>> GameModel::make_action_history(int flag, int step)
{
    std::vector<int> action_row={}, action_col={};
    std::vector<std::vector<int>> feature_vec;
    if (flag)
    {
        action_row = action0_vec_row;
        action_col = action0_vec_col;
    }
    else
    {
        action_row = action1_vec_row;
        action_col = action1_vec_col;
    }
    //  warning: comparison between signed and unsigned integer expressions 
    if(action_row.size() >= (step+1))
    {
        for (int i = 0; i < kBoardSizeNum; i++)
        {
            std::vector<int> line_feature;
            for (int j = 0; j < kBoardSizeNum; j++)
                if ((i == action_row[step]) && (j == action_col[step]))
                    line_feature.push_back(1);
                else
                    line_feature.push_back(0);
            feature_vec.push_back(line_feature);
        }
    }
    else
    {
        for (int i = 0; i < kBoardSizeNum; i++)
        {
            std::vector<int> line_feature;
            for (int j = 0; j < kBoardSizeNum; j++)
                line_feature.push_back(0);
            feature_vec.push_back(line_feature);
        }
    }
    return feature_vec;
}


std::vector<std::vector<int>> GameModel::empty_vec(int flag)
{
    std::vector<std::vector<int>> feature_vec;
        for (int i = 0; i < kBoardSizeNum; i++)
        {
            std::vector<int> line_feature;
            for (int j = 0; j < kBoardSizeNum; j++)
                line_feature.push_back(flag);
            feature_vec.push_back(line_feature);
        }
        return feature_vec;
}

