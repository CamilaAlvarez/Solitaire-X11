/* Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 * SPDX-License-Identifier:    MIT
 */
#ifndef _SOLITAIRE_WASTEPILE_HPP
#define _SOLITAIRE_WASTEPILE_HPP

#include "solitaire/card.hpp"
#include "solitaire/face_up_card_location.hpp"
#include <vector>

namespace solitaire
{
    /**
     * @brief Class representig the waste pile area of the tableau.
     * This area is next to the stock pile.
     *
     */
    class WastePile : public FaceUpCardLocation
    {
    public:
        /**
         * @brief Construct a new Waste Pile object
         *
         * @param cards
         */
        WastePile()
            : FaceUpCardLocation(std::vector<const Card *>(), FaceUpCardLocation::FaceUpCardLocationCode::WastePile) {}
        /**
         * @brief Indicates whether the player can place a card here or not.
         * In this case, they can't do it at all so teh function always returns false
         *
         * @return false
         */
        bool canPlayCardOnTop(const Card *) const override;
        /**
         * @brief Empties the wastepile and returns the cards in the opposite order
         *
         * @return std::vector<Card *>
         */
        std::vector<const Card *> emptyWastePile();
    };

}

#endif