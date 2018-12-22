# -*- coding:utf-8 -*-

import pickle

import numpy as np
from tqdm import tqdm


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


class DataStack:
    def __init__(self):
        self.__boards = []
        self.__policies = []

    def push(self, one_line_data, check_none=True):
        """
        :param one_line_data: DataReader
        :param check_none:Bool
        :return:
        """
        if check_none and (one_line_data.board is None or one_line_data.policy is None):
            return

        self.__boards.append(one_line_data.board)
        self.__policies.append(one_line_data.policy)

    def save_as_pkl(self, save_name):
        """
        :param save_name: str
        :return:
        """
        dataset = (self.__boards, self.__policies)
        with open(save_name, 'wb') as f:
            pickle.dump(dataset, f)


class DatasetMaker:
    def __init__(self):
        self.__data = None

    def load_data_from_file(self, filename):
        """
        :param filename: str
        :return:
        """
        with open(filename, 'r') as f:
            self.__data = f.readlines()

    def make_dataset(self, save_name, data_reader=OneLineData):
        """
        :param save_name: str
        :param data_reader: DataUtil.Data
        :return:
        """
        if self.__data is None:
            print("load data before making dataset.")
            return None

        data_stack = DataStack()
        for line in tqdm(self.__data):
            line_data = data_reader(line)
            data_stack.push(line_data)

        data_stack.save_as_pkl(save_name)


def main():
    filename = 'result.txt'
    dataset_maker = DatasetMaker()
    dataset_maker.load_data_from_file(filename)
    dataset_maker.make_dataset(save_name='data.pkl')


if __name__ == '__main__':
    main()
