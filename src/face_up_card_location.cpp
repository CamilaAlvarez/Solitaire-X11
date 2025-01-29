// SPDX-License-Identifier:    MIT
/*
 * FaceUpCardLocation class implementation
 *
 * Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 */
#include "solitaire/face_up_card_location.hpp"
#include <stdexcept>

namespace solitaire
{
    FaceUpCardLocation::FaceUpCardLocation(std::vector<const Card *> cards, FaceUpCardLocationCode locationCode)
    {
        switch (locationCode)
        {
        case FaceUpCardLocationCode::WastePile:
        case FaceUpCardLocationCode::Column0:
        case FaceUpCardLocationCode::Column1:
        case FaceUpCardLocationCode::Column2:
        case FaceUpCardLocationCode::Column3:
        case FaceUpCardLocationCode::Column4:
        case FaceUpCardLocationCode::Column5:
        case FaceUpCardLocationCode::Column6:
        case FaceUpCardLocationCode::Foundation0:
        case FaceUpCardLocationCode::Foundation1:
        case FaceUpCardLocationCode::Foundation2:
        case FaceUpCardLocationCode::Foundation3:
            mLocationCode = locationCode;
            break;
        default:
            throw std::invalid_argument("FaceUpCardLocation: Invalid location code");
        }
        mCards = cards;
    }

    /**
     * @details The last element of mCards represents the top of the location
     *
     * @return std::optional<Card *>
     */
    std::optional<const Card *> FaceUpCardLocation::getTopCard() const
    {
        if (mCards.empty())
        {
            return std::nullopt;
        }
        return mCards.back();
    }

    /**
     * @details Put the card on top means adding it to the back of the vector
     *
     * @param card
     */
    void FaceUpCardLocation::addCardToTop(const Card *card)
    {
        mCards.push_back(card);
    }

    const Card *FaceUpCardLocation::removeTopCard()
    {
        if (mCards.empty())
        {
            throw std::underflow_error("FaceUpCardLocation: Location is already empty");
        }
        const Card *topCard = mCards.back();
        mCards.pop_back();
        return topCard;
    }
    unsigned int FaceUpCardLocation::getNumberOfCards() const
    {
        return mCards.size();
    }
    bool FaceUpCardLocation::isEmpty() const
    {
        return mCards.empty();
    }
}