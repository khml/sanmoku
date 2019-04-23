# -*- coding:utf-8 -*-

import numpy as np

import ccsanmoku as cc


class Board:
    def __init__(self):
        self._board = cc.Board()

    def put(self, pos: int, is_cross: bool):
        self._board.put(pos, is_cross)

    @property
    def as_list(self) -> np.array:
        return self._board.asList()

    def is_legal(self, pos: int) -> bool:
        return self._board.isLegal(pos)

    def is_finished(self) -> bool:
        return self._board.isFinished()
