# -*- coding:utf-8 -*-

import pickle

from tqdm import tqdm

from DataUtil import OneLineData


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
