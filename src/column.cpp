// SPDX-License-Identifier:    MIT
/*
 * Column class implementation
 *
 * Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 */
#include "solitaire/column.hpp"
#include <stdexcept>

namespace solitaire
{
    Column::Column(const Card *card, std::vector<const Card *> hiddenCards, FaceUpCardLocation::FaceUpCardLocationCode locationCode)
        : FaceUpCardLocation(std::vector<const Card *>(), locationCode)
    {
        if (card == nullptr)
        {
            throw std::invalid_argument("Column: Invalid number of visible cards");
        }
        mCards.push_back(card);
        switch (locationCode)
        {
        case FaceUpCardLocation::FaceUpCardLocationCode::Column0:
            if (hiddenCards.size() != HIDDEN_CARDS_COLUMN0)
            {
                throw std::invalid_argument("Column: Invalid number of hidden cards for column 0");
            }
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column1:
            if (hiddenCards.size() != HIDDEN_CARDS_COLUMN1)
            {
                throw std::invalid_argument("Column: Invalid number of hidden cards for column 1");
            }
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column2:
            if (hiddenCards.size() != HIDDEN_CARDS_COLUMN2)
            {
                throw std::invalid_argument("Column: Invalid number of hidden cards for column 2");
            }
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column3:
            if (hiddenCards.size() != HIDDEN_CARDS_COLUMN3)
            {
                throw std::invalid_argument("Column: Invalid number of hidden cards for column 3");
            }
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column4:
            if (hiddenCards.size() != HIDDEN_CARDS_COLUMN4)
            {
                throw std::invalid_argument("Column: Invalid number of hidden cards for column 4");
            }
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column5:
            if (hiddenCards.size() != HIDDEN_CARDS_COLUMN5)
            {
                throw std::invalid_argument("Column: Invalid number of hidden cards for column 5");
            }
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column6:
            if (hiddenCards.size() != HIDDEN_CARDS_COLUMN6)
            {
                throw std::invalid_argument("Column: Invalid number of hidden cards for column 6");
            }
            break;
        default:
            throw std::invalid_argument("Column: Invalid location code");
        }
        mHiddenCards = hiddenCards;
    }

    unsigned int Column::getNumberHiddenCards() const
    {
        return mHiddenCards.size();
    }

    void Column::revealHiddenCard()
    {
        const Card *topHiddenCard = mHiddenCards.back();
        mHiddenCards.pop_back();
        mCards.push_back(topHiddenCard);
    }

    const Card *Column::removeTopCard()
    {
        const Card *topCard = FaceUpCardLocation::removeTopCard();
        if (mCards.empty() && !mHiddenCards.empty())
        {
            revealHiddenCard();
        }
        return topCard;
    }

    bool Column::canPlayCardOnTop(const Card *card) const
    {
        std::optional<const Card *> topCardOpt = getTopCard();
        if (topCardOpt == std::nullopt)
        {
            return true;
        }
        const Card *topCard = topCardOpt.value();
        if (topCard->isOppositeColor(card) && card->precedesAndContiguousTo(topCard))
        {
            return true;
        }
        return false;
    }

    void Column::addCardsToColumn(std::vector<const Card *> cards)
    {
        for (const Card *c : cards)
        {
            addCardToTop(c);
        }
    }

    std::vector<const Card *> Column::getTopNCards(unsigned int n) const
    {
        if (n == 0)
        {
            throw std::invalid_argument("Column: Invalid number of requested cards: 0");
        }
        else if (n > mCards.size())
        {
            throw std::domain_error("Column: Requesting too many cards");
        }
        std::vector<const Card *> topNCards = std::vector<const Card *>(mCards.end() - n, mCards.end());
        return topNCards;
    }

    std::vector<const Card *> Column::removeTopNCards(unsigned int n)
    {
        if (n == 0)
        {
            throw std::invalid_argument("Column: Invalid number of requested cards to be removed: 0");
        }
        else if (n > mCards.size())
        {
            throw std::domain_error("Column: Removing too many cards");
        }
        std::vector<const Card *> removedCards(n);
        for (size_t i = 0; i < n; i++)
        {
            removedCards[n - 1 - i] = removeTopCard();
        }
        return removedCards;
    }
}