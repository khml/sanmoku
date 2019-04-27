# -*- coding:utf-8 -*-

import numpy as np

import Board

POS = 'pos'
DATA = 'data'


class MoveHistory:
    def __init__(self):
        self._data_dict = {
            Board.CROSS: [],
            Board.CYCLE: []
        }

    def add(self, color: int, pos: int, board_data: np.array):
        self._data_dict[color].append({POS: pos, DATA: board_data})

    @property
    def data(self):
        return self._data_dict

    @property
    def cross(self):
        return self.data[Board.CROSS]

    @property
    def cycle(self):
        return self.data[Board.CYCLE]
