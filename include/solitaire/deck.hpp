/* Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 * SPDX-License-Identifier:    MIT
 */
#ifndef _SOLITAIRE_DECK_HPP
#define _SOLITAIRE_DECK_HPP

#include "solitaire/card.hpp"
#include <vector>
#include <random>

namespace solitaire
{
    /**
     * @brief A class that represents a generic card deck
     *
     */
    class Deck
    {
    public:
        /**
         * @brief Construct a new Deck object
         *
         * @param cards Cards to be added to the deck.
         * @throw std::invalid_argument if cards has over/under 52 cards, or cards are repeated
         */
        Deck(std::vector<const Card *> cards);
        /**
         * @brief Shuffle the deck. Shuffling several times should return different results
         *
         */
        void shuffle();
        /**
         * @brief Get a vector with N cards and remove them from the deck
         *
         * @param numberOfCards Number of cards to extract
         * @return std::vector<const Card *>
         * @throw std::invalid_argument when numberOfCards exceeds the current size of the deck
         */
        std::vector<const Card *> extractNCards(unsigned int numberOfCards);

    private:
        /**
         * @brief Cards from the deck
         *
         */
        std::vector<const Card *> mCards;
        /**
         * @brief Random generator used to shuffle the deck
         *
         */
        std::mt19937 mRandomGenerator;
    };
}

#endif