# -*- coding:utf-8 -*-

import numpy as np

import ccsanmoku as cc

CROSS = 1
CYCLE = -1
DRAW = 0

BOARD_SIZE = 9


def turn_color(color: int):
    if color == CROSS:
        return CYCLE
    return CROSS


class Board:
    def __init__(self):
        self._board = cc.Board()

    def put(self, pos: int, color: int):
        self._board.put(pos, color == CROSS)

    @property
    def as_list(self) -> np.array:
        return self._board.asList()

    def is_legal(self, pos: int) -> bool:
        return self._board.isLegal(pos)

    @property
    def is_finished(self) -> bool:
        return self._board.isFinished()

    @property
    def result(self) -> int:
        return self._board.result()

    def data(self, color: int):
        color_array = np.zeros
        if color == CROSS:
            color_array = np.ones

        one_hot_data = [color_array(BOARD_SIZE), (self.as_list == CROSS) * 1, (self.as_list == CYCLE) * 1]
        return np.concatenate(one_hot_data)
