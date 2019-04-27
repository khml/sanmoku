# -*- coding:utf-8 -*-


import numpy as np

from Board import Board


def choice_move(policy: np.ndarray, board: Board, random: int = 0):
    p = policy.copy()
    p += p.max() - p.min()
    p /= sum(p)

    for _ in range(random):
        try:
            pos = np.random.choice(len(p), p=p)
        except Exception as err:
            print(p)
            print(err)
            exit()
        if board.is_legal(pos):
            return pos
        p = p.tolist()
        p.pop(pos)
        p = np.array(p) / sum(p)

    for pos in np.argsort(policy):
        if board.is_legal(pos):
            return pos

    return False
