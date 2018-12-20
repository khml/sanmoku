# -*- coding:utf-8 -*-

import numpy as np


class Data:
    def __init__(self):
        pass

    @property
    def result(self):
        raise NotImplementedError

    @property
    def policy(self):
        raise NotImplementedError

    @property
    def board(self):
        raise NotImplementedError


class OneLineData(Data):
    __PARSE_DATA_CHAR = ':'
    __PARSE_BOARD_DATA_CHAR = ','
    __RESULT = 'result'
    __POLICY = 'policy'
    __BOARD = 'board'

    def __init__(self, sample):
        super().__init__()
        self.__data = self.__parse_data(sample)

    @property
    def data(self):
        """
        :return: dict
        """
        return self.__data

    @property
    def result(self):
        """
        :return: int
        """
        return self.__get_value(self.__RESULT, int)

    @property
    def policy(self):
        """
        :return: int
        """
        return self.__get_value(self.__POLICY, int)

    @property
    def board(self):
        """
        :return: np.ndarray
        """
        return self.__get_value(self.__BOARD, self.__get_ndarray_from_str)

    def __parse_data(self, sample):
        """
        :param sample: str
        :return:
        """
        parsed_data = {}
        data = sample.split(self.__PARSE_DATA_CHAR)
        data_size = len(data)
        for i in range(data_size // 2):
            key = data[2 * i]
            value = data[2 * i + 1]
            parsed_data[key] = value

        return parsed_data

    def __get_value(self, key, preprocessing, value_if_not_exist=None):
        if key in self.data.keys():
            value = self.data[key]
            return preprocessing(value)
        return value_if_not_exist

    def __get_ndarray_from_str(self, board_as_str):
        """
        :param board_as_str: str
        :return:
        """
        board_as_list = [int(elelement) for elelement in board_as_str.split(self.__PARSE_BOARD_DATA_CHAR)]
        return np.array(board_as_list)
