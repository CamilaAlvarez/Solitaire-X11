// SPDX-License-Identifier:    MIT
/*
 * StockPile class implementation
 *
 * Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 */
#include "solitaire/stockpile.hpp"
#include <stdexcept>

namespace solitaire
{
    /**
     * @details the back of the vector represents the top of the stockpile
     *
     * @return const Card*
     */
    const Card *StockPile::revealCard()
    {
        if (mCards.empty())
        {
            throw std::underflow_error("Stockpile: Stockpile is empty");
        }
        const Card *revealedCard = mCards.back();
        mCards.pop_back();
        return revealedCard;
    }
    bool StockPile::isEmpty() const
    {
        return mCards.empty();
    }
    void StockPile::reloadStockpile(std::vector<const Card *> cards)
    {
        if (!isEmpty())
        {
            throw std::runtime_error("Stockpile: Stockpile not empty when trying to reload");
        }
        if (cards.empty())
        {
            throw std::invalid_argument("Stockpile: No cards in the reload argument");
        }
        mCards = cards;
    }
}