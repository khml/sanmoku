/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <fstream>

#include "Player.hpp"

#define GAMMA 0.8

using std::vector;
using std::get;
using std::cerr;
using std::endl;

using torch::tensor;
using torch::Tensor;
using torch::softmax;
using torch::binary_cross_entropy;

namespace sanmoku
{
    Player::Player()
    {}

    Player::Player(const Player &orig) : toPlayColor(orig.toPlayColor)
    {}

    Player::~Player()
    {}

    bool Player::play(Board &board)
    {
        if (board.isFinished())
            return false;

        while (true)
        {
            Move move = genMove(board, toPlayColor);
            if (board.isLegal(move))
            {
                board.put(move);
                break;
            }
        }
        toPlayColor = turnColor(toPlayColor);
        return true;
    }

    RandomPlayer::RandomPlayer()
    {}

    RandomPlayer::RandomPlayer(sanmoku::RandomPlayer &orig)
    {}

    RandomPlayer::~RandomPlayer()
    {}

    Move RandomPlayer::genMove(sanmoku::Board &board, Color color)
    {
        return {color, (int) rand() % BOARD_SIZE};
    }

    NNPlayer::NNPlayer()
    {}

    NNPlayer::NNPlayer(sanmoku::NNPlayer &orig) : model(orig.model)
    {}

    NNPlayer::~NNPlayer()
    {}

    Move NNPlayer::genMove(sanmoku::Board &board, Color color)
    {
        auto policy = model->infer(board.getBoard());
        vector<int> posIndices = {0, 1, 2, 3, 4, 5, 6, 7, 8};

        while (true)
        {
            std::discrete_distribution<std::size_t> dist(policy.begin(), policy.end());
            std::mt19937 engine(randomDevice());
            std::size_t index = dist(engine);
            Move move(color, posIndices[(int) index]);
            if (board.isLegal(move))
                return move;
            policy.erase(policy.begin() + index);
            posIndices.erase(posIndices.begin() + index);
        }

    }

    void NNPlayer::train(sanmoku::Board &board)
    {
        if (board.result == Empty)
        {
            cerr << "result is DRAW, do not learning" << endl;
            return;
        }

        model->train();
        torch::optim::SGD optimizer(model->parameters(), torch::optim::SGDOptions(0.01).momentum(0.5));

        vector<Tensor> dataStack;
        vector<Tensor> labelStack;
        makeDataset(board.history, board.result, 1.0, dataStack, labelStack);
        makeDataset(board.history, turnColor(board.result), 0.0, dataStack, labelStack);
        auto data = torch::stack(dataStack);
        auto labels = torch::stack(labelStack);

        // learning
        optimizer.zero_grad();
        auto out = model->forward(data);
        auto loss = binary_cross_entropy(out, labels);
        cerr << "Loss = " << *(loss.template data<float>()) << endl;
        loss.backward();
        optimizer.step();
    }

    void NNPlayer::makeDataset(sanmoku::MoveHistory<float> &history, sanmoku::Color color, float lastReward,
                               std::vector<torch::Tensor> &dataStack, std::vector<torch::Tensor> &labelStack)
    {
        auto targetData = history.data(color);
        for (int i = 0; i < targetData.size(); i++)
        {
            auto data = get<0>(targetData[i]);
            dataStack.push_back(torch::tensor(data));

            auto label = torch::tensor(model->infer(data));
            auto move = get<1>(targetData[i]);

            if (i == targetData.size() - 1) // last
            {
                label[move.pos] += lastReward;
                labelStack.push_back(label);
                continue;
            }

            auto next = get<0>(targetData[i + 1]);
            auto futureValue = torch::tensor(model->infer(next));
            label[move.pos] += GAMMA * futureValue.max();
            label = softmax(label, 0);
            labelStack.push_back(label);
        }
    }

    bool NNPlayer::loadModel(std::string modelName)
    {
        std::ifstream ifs(modelName);
        if (!ifs.is_open())
            return false;

        torch::load(model, modelName);
        return true;
    }

    void NNPlayer::saveModel(std::string modelName)
    {
        torch::save(model, modelName);
    }

}
