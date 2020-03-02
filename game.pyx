# distutils: language = c++

from GameModel cimport GameModel
from libcpp.vector cimport vector

cdef class kernel:
    cdef GameModel gm
    
    # def bint playerFlag
    # def int gameStatus

    def __cinit__(self):
        self.gm = GameModel()
    
    def reset(self):
        self.gm.startGame()
        cdef vector[vector[int]] gameMapVec = self.gm.getmap()
        return gameMapVec
    
    def step(self, int row, int col):
        self._action(row, col)
        cdef vector[vector[int]] gameMapVec = self.gm.getmap()
        cdef bint is_win = self.is_win(row, col)
        cdef bint is_dead = self.is_dead()
        return gameMapVec, is_win, is_dead
    
    def _get_map(self):
        cdef vector[vector[int]] gameMapVec = self.gm.getmap()
        return gameMapVec
    
    def _action(self, int row, int col):
        self.gm.actionByPerson(row, col)

    def is_win(self, int row, int col):
        cdef bint is_win = self.gm.isWin(row, col)
        return is_win
        
    def is_dead(self):
        cdef bint is_dead = self.gm.isDeadGame()
        return is_dead

    def get_feature(self, bint flag):
        cdef  vector[vector[vector[int]]] feature = self.gm.get_feature(flag)
        return feature