/* Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 * SPDX-License-Identifier:    MIT
 */
#ifndef _SOLITAIRE_STOCKPILE_HPP
#define _SOLITAIRE_STOCKPILE_HPP

#include "solitaire/card_stack.hpp"
#include "solitaire/card.hpp"
#include <vector>
#include <stdexcept>

#define STOCKPILE_SIZE 24

namespace solitaire
{
    /**
     * @brief Class representig the stock pile area of the tableau.
     * This area has a set of face-down cards
     *
     */
    class StockPile : public CardStack
    {
    public:
        /**
         * @brief Construct a new Stock Pile object.
         *
         * @param cards it must include STOCKPILE_SIZE cards
         * @throw std::invalid_argument when card doesn't include STOCKPILE_SIZE cards
         */
        StockPile(std::vector<const Card *> cards) : mCards(cards)
        {
            if (cards.size() != STOCKPILE_SIZE)
            {
                throw std::invalid_argument("Stockpile: Invalid number of cards");
            }
        }
        /**
         * @brief Removes a card from the top of the stockpile,
         * revealing its value
         *
         * @return const Card*
         * @throw std::underflow_error when the stockpile is empty
         */
        const Card *revealCard();
        /**
         * @brief Checks if the stockpile is empty
         *
         * @return true
         * @return false
         */
        bool isEmpty() const;
        /**
         * @brief Loads card into the stockpile, can only be done if the stock pile is empty
         *
         * @param cards
         * @throw std::invalid_argument if the cards argument is empty
         * @throw std::runtime_error when the stock pile is not empty
         */
        void reloadStockpile(std::vector<const Card *> cards);

    private:
        std::vector<const Card *> mCards;
    };
}

#endif