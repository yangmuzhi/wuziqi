from libcpp.vector cimport vector
cdef extern from "GameModel.cpp":
    pass

# Declare the class with cdef
cdef extern from "GameModel.h":
    cdef cppclass GameModel:
        GameModel() except +
        bint playerFlag
        int gameStatus

        void startGame()
        void actionByPerson(int row, int col)
        void updateGameMap(int row, int col)
        bint isWin(int row, int col)
        bint isDeadGame()
        vector[vector[int]] getmap()
        vector[vector[vector[int]]] get_feature(bint playerFlag)
        vector[int] action0_vec_row
        vector[int] action0_vec_col
        vector[int] action1_vec_row
        vector[int] action1_vec_col
        