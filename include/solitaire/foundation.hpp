/* Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 * SPDX-License-Identifier:    MIT
 */
#ifndef _SOLITAIRE_FOUNDATION_HPP
#define _SOLITAIRE_FOUNDATION_HPP

#include "solitaire/card.hpp"
#include "solitaire/face_up_card_location.hpp"
#include <vector>
#include <stdexcept>

namespace solitaire
{
    /**
     * @brief Represents the foundation spots in the tableau.
     * These are the empty places at the top of the mat, next to the waste pile
     *
     */
    class Foundation : public FaceUpCardLocation
    {
    public:
        /**
         * @brief Construct a new Foundation object. It starts with an empty list of cards.
         *
         * @param foundationCode
         * @throw std::invalid_argument when the foundationCode doesn't match a foundation
         */
        Foundation(FaceUpCardLocation::FaceUpCardLocationCode foundationCode);
        /**
         * @brief Checks if the card can be added on top. For the foundation the rule is that all
         * cards must of the same suit and be placed on ascending order (the cards must be contiguous).
         * Also, if the foundation is empty only an ace may be placed.
         *
         * @param card
         * @return true
         * @return false
         */
        bool canPlayCardOnTop(const Card *card) const override;
        /**
         * @brief Checks if the foundation has the complete suit on it.
         *
         * @return true
         * @return false
         */
        bool isComplete() const;
    };
}

#endif