// SPDX-License-Identifier:    MIT
/*
 * Foundation class implementation
 *
 * Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 */
#include "solitaire/foundation.hpp"
#include <stdexcept>

#define COMPLETE_FOUNDATION_SIZE 13

namespace solitaire
{
    Foundation::Foundation(FaceUpCardLocation::FaceUpCardLocationCode foundationCode)
        : FaceUpCardLocation(std::vector<const Card *>(), foundationCode)
    {
        switch (foundationCode)
        {
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation0:
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation1:
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation2:
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation3:
            break;
        default:
            throw std::invalid_argument("Foundation: Invalid foundation code");
        }
    }
    /**
     * @details The rules are:
     * 1. If the spot is empty we can only place an ace. It might be of any suit.
     * 2. If there is a card we can only place the contiguous one of the same suit
     *
     * @param card
     * @return true
     * @return false
     */
    bool Foundation::canPlayCardOnTop(const Card *card) const
    {
        if (mCards.empty())
        {
            return card->getRank() == Card::Rank::A;
        }
        // At this point we know we have at least one card
        const Card *topCard = this->getTopCard().value();
        return topCard->getSuit() == card->getSuit() && topCard->precedesAndContiguousTo(card);
    }
    /**
     * @details we'll verify the cards are in the correct order, and that there are 13 of them
     *
     * @return true
     * @return false
     */
    bool Foundation::isComplete() const
    {
        if (mCards.size() != COMPLETE_FOUNDATION_SIZE)
        {
            return false;
        }
        return mCards[0]->getRank() == Card::Rank::A && mCards[1]->getRank() == Card::Rank::N2 &&
               mCards[2]->getRank() == Card::Rank::N3 && mCards[3]->getRank() == Card::Rank::N4 && mCards[4]->getRank() == Card::Rank::N5 &&
               mCards[5]->getRank() == Card::Rank::N6 && mCards[6]->getRank() == Card::Rank::N7 && mCards[7]->getRank() == Card::Rank::N8 &&
               mCards[8]->getRank() == Card::Rank::N9 && mCards[9]->getRank() == Card::Rank::N10 && mCards[10]->getRank() == Card::Rank::J &&
               mCards[11]->getRank() == Card::Rank::Q && mCards[12]->getRank() == Card::Rank::K;
    }
}