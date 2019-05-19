/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <random>
#include "Board.hpp"
#include "Model.hpp"

namespace sanmoku
{
    class Player
    {
    public:
        Player();

        Player(const Player &orig);

        virtual ~Player();

        Color toPlayColor = Cross;

        bool play(Board &board);

        virtual Move genMove(Board &board, Color color) = 0;
    };

    class RandomPlayer : public Player
    {
    public:
        RandomPlayer();

        RandomPlayer(RandomPlayer &orig);

        virtual ~RandomPlayer();

        Move genMove(Board &board, Color color) override;

    protected:
        std::random_device rand;
    };

    class NNPlayer : public Player
    {
    public:
        NNPlayer();

        NNPlayer(NNPlayer &orig);

        virtual ~NNPlayer();

        Move genMove(Board &board, Color color) override;

        void train(Board &board);

        bool loadModel(std::string modelName);

        void saveModel(std::string modelName);

    protected:
        void makeDataset(MoveHistory<float> &history, Color color, float lastReward,
                         std::vector<torch::Tensor> &dataStack, std::vector<torch::Tensor> &labelStack);

        std::random_device randomDevice;
        Net model;
    };
}


#endif /* PLAYER_HPP */

