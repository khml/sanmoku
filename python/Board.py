# -*- coding:utf-8 -*-

import numpy as np

import ccsanmoku as cc
from MoveHistory import MoveHistory

CROSS = 1
CYCLE = -1
DRAW = 0

EMPTY_SIGN = '.'
CROSS_SIGN = 'X'
CYCLE_SIGN = 'O'

BOARD_FORMAT = "{} | {} | {} \n{} | {} | {} \n{} | {} | {}"

BOARD_SIZE = 9


def turn_color(color: int):
    if color == CROSS:
        return CYCLE
    return CROSS


class Board:
    def __init__(self):
        self._board = cc.Board()
        self._moves = MoveHistory()

    @property
    def moves(self):
        return self._moves

    def put(self, pos: int, color: int):
        data = self.data(color)
        self._board.put(pos, color == CROSS)
        self._moves.add(color, pos, data)

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

    def string_board(self):
        board = []
        for color in self.as_list:
            if color == CROSS:
                board.append(CROSS_SIGN)
            elif color == CYCLE:
                board.append(CYCLE_SIGN)
            else:
                board.append(EMPTY_SIGN)
        return BOARD_FORMAT.format(*board)
