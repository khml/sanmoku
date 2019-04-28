# -*- coding:utf-8 -*-

import numpy as np

import Board


class Move:
    def __init__(self, pos: int, data: np.ndarray):
        self._pos = pos
        self._data = data

    @property
    def pos(self):
        return self._pos

    @property
    def data(self):
        return self._data


class MoveHistory:
    def __init__(self):
        self._data_dict = {
            Board.CROSS: [],
            Board.CYCLE: []
        }

    def add(self, color: int, pos: int, board_data: np.ndarray):
        self._data_dict[color].append(Move(pos, board_data))

    @property
    def data(self):
        return self._data_dict

    @property
    def cross(self):
        return self.data[Board.CROSS]

    @property
    def cycle(self):
        return self.data[Board.CYCLE]
