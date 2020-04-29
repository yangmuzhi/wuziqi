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

    // init feature
    featureTensor0.clear();
    for (int k = 0; k < nFeature; k++)
    {

        std::vector<std::vector<int> > mapBoard;
        for (int i = 0; i < kBoardSizeNum; i++)
        {
            std::vector<int> lineBoard;
            for (int j = 0; j < kBoardSizeNum; j++)
                if(k==0)
                // map 0
                    lineBoard.push_back(1);
                else
                    lineBoard.push_back(0);
            mapBoard.push_back(lineBoard);
        }
        featureTensor0.push_back(mapBoard);
    }
    
    featureTensor1.clear();
    for (int k = 0; k < nFeature; k++)
    {

        std::vector<std::vector<int> > mapBoard;
        for (int i = 0; i < kBoardSizeNum; i++)
        {
            std::vector<int> lineBoard;
            for (int j = 0; j < kBoardSizeNum; j++)
                if(k==0)
                // map 0
                    lineBoard.push_back(1);
                else
                    lineBoard.push_back(0);
            mapBoard.push_back(lineBoard);
        }
        featureTensor1.push_back(mapBoard);
    }

    // 己方下为true,对方下位false
    playerFlag = true;

}

void GameModel::updateGameMap(int row, int col)
{
    if (playerFlag)
        gameMapVec[row][col] = 1;
    else
        gameMapVec[row][col] = -1;

   
}

void GameModel::actionByPerson(int row, int col)
{
    updateGameMap(row, col);
    updatefeature(row, col);
     // 换手
    playerFlag = !playerFlag;
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

std::vector<std::vector<int> > GameModel::getmap()
{
    return gameMapVec;
}


// update feature by step
void GameModel::updatefeature(int row, int col)
{


    // map 11
    featureTensor0[11][row][col] = 1; 
    featureTensor1[11][row][col] = 1; 

    if (playerFlag)
    {
        // player0 feature

        // map 5
        featureTensor0[5] = featureTensor0[4];   
        // map 4
        featureTensor0[4] = featureTensor0[3];   
        // map 3
        featureTensor0[3] = featureTensor0[2];   
        // map 2
        featureTensor0[2] = featureTensor0[1];   
        // map 1
        featureTensor0[1][row][col] = 1;   

        //
        // player1 feature
        
        // map 6
        featureTensor1[6] = featureTensor0[1];  
        // map 7
        featureTensor1[7] = featureTensor0[2]; 
        // map 8
        featureTensor1[8] = featureTensor0[3];   
        // map 9
        featureTensor1[9] = featureTensor0[4];   
        // map 10
        featureTensor1[10] = featureTensor0[5]; 
  
    }
    else
    {
        // player1 feature

        // map 5
        featureTensor1[5] = featureTensor1[4];   
        // map 4
        featureTensor1[4] = featureTensor1[3];   
        // map 3
        featureTensor1[3] = featureTensor1[2];   
        // map 2
        featureTensor1[2] = featureTensor1[1];   
        // map 1
        featureTensor1[1][row][col] = 1;   

        //
        // player0 feature
        
        // map 6
        featureTensor0[6] = featureTensor1[1];  
        // map 7
        featureTensor0[7] = featureTensor1[2]; 
        // map 8
        featureTensor0[8] = featureTensor1[3];   
        // map 9
        featureTensor0[9] = featureTensor1[4];   
        // map 10
        featureTensor0[10] = featureTensor1[5]; 
    }
    
}


std::vector<std::vector<std::vector<int> > > GameModel::get_feature(bool flag)
{
    //  flag = 1
    if (flag)
        return featureTensor0;
    else
    {
        return featureTensor1;
    }
    
}
