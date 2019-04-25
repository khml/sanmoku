# -*- coding:utf-8 -*-

import numpy as np
import torch


class Model(torch.nn.Module):
    def __init__(self, in_size, mid_size, out_size):
        super(Model, self).__init__()
        self.fc1 = torch.nn.Linear(in_size, mid_size)
        self.fc2 = torch.nn.Linear(mid_size, out_size)

    def forward(self, x):
        x = torch.nn.functional.relu(self.fc1(x))
        x = self.fc2(x)
        return x

    def save(self, path: str):
        torch.save(self.state_dict(), path)

    def load(self, path):
        self.load_state_dict(torch.load(path))

    def infer(self, data: np.array) -> np.array:
        with torch.no_grad():
            data = torch.Tensor(data)
            return self(data).numpy()
