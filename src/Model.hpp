//
// Created by KHML on 2019-05-08.
//

#ifndef SANMOKU_MODEL_HPP
#define SANMOKU_MODEL_HPP

#include <torch/torch.h>

namespace sanmoku
{
    template <typename T>
    static torch::Tensor toTensor(std::vector<T> vector)
    {
        return torch::tensor(vector);
    }

    static std::vector<float> toVector(torch::Tensor x)
    {
        auto tensor = std::move(x);
        int64_t dimension = tensor.dim();

        int64_t size = 1;
        for (int64_t dim = 0; dim < dimension; dim++)
        {
            size *= tensor.size(dim);
        }

        std::vector<float> vec = std::vector<float>();
        float* first = tensor.template data<float_t>();
        vec.assign(first, &first[size]);
        return vec;
    }

    struct NetImpl : torch::nn::Module
    {
        torch::nn::Linear fc1;
        torch::nn::Linear fc2;

        NetImpl() : fc1(9, 18), fc2(18, 9)
        {
            register_module("fc1", fc1);
            register_module("fc2", fc2);
        }

        torch::Tensor forward(torch::Tensor x)
        {
            x = torch::relu(fc1->forward(x));
            x = fc2->forward(x);
            return torch::log_softmax(x, /*dim=*/1);
        }

        std::vector<float> infer(std::vector<float> vec)
        {
            eval();
            torch::NoGradGuard noGrad;
            auto tensor = toTensor(std::move(vec));
            tensor = tensor.view({-1, 9});
            auto predict = forward(std::move(tensor));
            return toVector(predict);
        }
    };

    TORCH_MODULE(Net);

}

#endif //SANMOKU_MODEL_HPP
