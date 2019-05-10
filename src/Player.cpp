/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <fstream>

#include "Player.hpp"

using std::vector;
using std::get;
using std::cerr;
using std::endl;

using torch::tensor;
using torch::Tensor;
using torch::data::Example;
using torch::nll_loss;

namespace sanmoku
{
    Player::Player () { }

    Player::Player (const Player& orig) : toPlayColor(orig.toPlayColor), model(orig.model) { }

    Player::~Player () { }

    Move Player::getRandomPos ()
    {
        return {toPlayColor, (int) rand () % BOARD_SIZE};
    }

    Move Player::genMove(sanmoku::Board &board)
    {
        auto policy = model->infer(board.getBoard());
        vector<int> posIndices = {0, 1, 2, 3, 4, 5, 6, 7, 8};

        while (true)
        {
            std::discrete_distribution<std::size_t> dist(policy.begin(), policy.end());
            std::mt19937 engine(rand());
            std::size_t index = dist(engine);
            Move move(toPlayColor, posIndices[(int) index]);
            if (board.isLegal(move))
                return move;
            policy.erase(policy.begin() + index);
            posIndices.erase(posIndices.begin() + index);
        }

    }

    bool Player::play (Board& board)
    {
        if (board.isFinished ())
            return false;

        while (true)
        {
            Move move = genMove (board);
            if (board.isLegal (move))
            {
                board.put (move);
                break;
            }
        }
        toPlayColor = (toPlayColor == Cross ? Cycle : Cross);
        return true;
    }

    void Player::train(sanmoku::Board &board)
    {
        if (board.result == Empty)
        {
            cerr << "result is DRAW, do not learning" << endl;
            return;
        }

        model->train();
        torch::optim::SGD optimizer(model->parameters(), torch::optim::SGDOptions(0.01).momentum(0.5));

        optimizer.zero_grad();
        for(auto item : board.history.data())
        {
            auto move = get<1>(item);
            if (move.color == board.result)
                continue;

            auto data = tensor(get<0>(item)).view({-1, 9});
            auto label = tensor(move.pos, torch::kLong);
            auto out = model->forward(data);

            auto loss = nll_loss(out, label);
            cerr << "Loss = " << *(loss.template data<float>()) << endl;
            loss.backward();
        }
        optimizer.step();
    }

    bool Player::loadModel(std::string modelName)
    {
        std::ifstream ifs(modelName);
        if (! ifs.is_open())
            return false;

        torch::load(model, modelName);
        return true;
    }

    void Player::saveModel(std::string modelName)
    {
        torch::save(model, modelName);
    }
}
