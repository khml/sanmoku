# -*- coding utf-8 -*-

import pickle

from tqdm import tqdm
import torch
import torchvision

from MakeDataset import DataStack


class DatafileLoader:
    def __init__(self, filename):
        self._data = self.__load_data_from_pkl(filename)

    @staticmethod
    def __load_data_from_pkl(filename):
        with open(filename, 'rb') as f:
            data = pickle.load(f)
            return data

    def __split_data(self, ratio):
        data_size = len(self._data.policies)
        split = int(data_size * ratio)

        policies = self._data.policies
        boards = self._data.boards

        train = (boards[:split], policies[:split])
        valid = (boards[:split], policies[:split])
        return train, valid

    def __make_data_loader(self, data, label, batch_size, shuffle=True):
        data = torch.Tensor.float(torch.as_tensor(data))
        label = torch.Tensor.long(torch.as_tensor(label))
        dataset = torch.utils.data.TensorDataset(data, label)
        data_loader = torch.utils.data.DataLoader(dataset, batch_size=batch_size, shuffle=shuffle)
        return data_loader

    def make_data_loader(self, ratio=0.8, batch_size=8):
        train, valid = self.__split_data(ratio)
        train_loader = self.__make_data_loader(train[0], train[1], batch_size, shuffle=True)
        valid_loader = self.__make_data_loader(valid[0], valid[1], batch_size, shuffle=False)
        return train_loader, valid_loader


class Model(torch.nn.Module):
    def __init__(self, in_size, mid_size, out_size):
        super(Model, self).__init__()
        self.fc1 = torch.nn.Linear(in_size, mid_size)
        self.fc2 = torch.nn.Linear(mid_size, out_size)

    def forward(self, x):
        x = torch.nn.functional.relu(self.fc1(x))
        x = self.fc2(x)
        return x


class Trainer:
    def __init__(self, data_filename, model, batch_size=8, device='cpu'):
        self._batch_size = batch_size
        self._device = torch.device(device)

        self._model = model
        self._criterion = torch.nn.CrossEntropyLoss()
        self._optimizer = torch.optim.SGD(self.model.parameters(), lr=1e-2, momentum=0.9)

        datafile_loader = DatafileLoader(data_filename)
        self._train_dataloader, self._valid_dataloader = datafile_loader.make_data_loader(batch_size=self._batch_size)

        self._train_data_size = len(self._train_dataloader) * self._batch_size
        self._valid_data_size = len(self._valid_dataloader) * self._batch_size

    @property
    def model(self):
        return self._model

    def inference(self, inputs):
        logit = self.model(inputs)
        predict = torch.nn.functional.softmax(logit, dim=0)
        return predict

    def _calc_loss(self, inputs, label):
        predict = self.inference(inputs)
        return self._criterion(predict, label)

    def train(self):
        self.model.train()
        loss_summary = 0
        for (data, label) in tqdm(self._train_dataloader):
            self._optimizer.zero_grad()
            loss = self._calc_loss(data, label)
            loss_summary += loss.item()
            loss.backward()
            self._optimizer.step()
        return loss_summary / self._train_data_size

    def valid(self):
        self.model.eval()
        loss_summary = 0
        with torch.no_grad():
            for (data, label) in tqdm(self._valid_dataloader):
                loss = self._calc_loss(data, label)
                loss_summary += loss.item()
        return loss_summary / self._valid_data_size

    def save_model_as_torch_script(self, save_name):
        example_data, _ = next(iter(self._train_dataloader))
        traced_script_module = torch.jit.trace(self.model, example_data)
        traced_script_module.save(save_name)


def main():
    filename = 'data.pkl'
    save_name = 'model.pt'
    Epoch = 1

    model = Model(9, 9, 9)
    trainer = Trainer(filename, model)

    print("start Training.")
    for epoch in range(Epoch):
        print("Epoch {} Training.".format(epoch + 1))
        train_loss = trainer.train()
        print("train loss = {}".format(train_loss))
        valid_loss = trainer.valid()
        print("valid loss = {}".format(valid_loss))

    print("save Model")
    trainer.save_model_as_torch_script(save_name)


if __name__ == '__main__':
    main()
