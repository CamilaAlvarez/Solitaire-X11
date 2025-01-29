/* Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 * SPDX-License-Identifier:    MIT
 */
#ifndef _SOLITAIRE_FACE_UP_CARD_LOCATION_HPP
#define _SOLITAIRE_FACE_UP_CARD_LOCATION_HPP

#include "solitaire/card.hpp"
#include "solitaire/card_stack.hpp"
#include <vector>
#include <optional>

namespace solitaire
{
    /**
     * @brief Represents a location where the player can find a face up card.
     *
     */
    class FaceUpCardLocation : public CardStack
    {
    public:
        /**
         * @brief All the possible face up locations that can be found in a solitaire.
         * We give each of them a code.
         *
         */
        enum class FaceUpCardLocationCode
        {
            WastePile,
            Column0,
            Column1,
            Column2,
            Column3,
            Column4,
            Column5,
            Column6,
            Foundation0,
            Foundation1,
            Foundation2,
            Foundation3,
        };
        /**
         * @brief Construct a new Face Up Card Location object
         *
         * @param cards Cards to be added to the specific location. Must be non-empty
         * @param locationCode Code of the location
         * @throw std::invalid_argument when locationCode is invalid
         */
        FaceUpCardLocation(std::vector<const Card *> cards, FaceUpCardLocationCode locationCode);
        /**
         * @brief Destroy the Face Up Card Location object
         *
         */
        virtual ~FaceUpCardLocation() {}
        /**
         * @brief Get the Top Card from the location
         *
         * @return std::optional<Card *>
         */
        std::optional<const Card *> getTopCard() const;
        /**
         * @brief Adds a new card to the top of the location. The param is the new top
         *
         * @param card Card to be placed at the top
         */
        void addCardToTop(const Card *card);
        /**
         * @brief Get the number Of cards in the face up location
         *
         * @return unsigned int
         */
        unsigned int getNumberOfCards() const;
        /**
         * @brief Checks if the param can be added on top of the current top card
         *
         * @param card Card to verify
         * @return true
         * @return false
         */
        virtual bool canPlayCardOnTop(const Card *card) const = 0;
        /**
         * @brief Removes the top card from the location
         *
         * @return const Card*
         * @throw std::invalid_argument when the location is empty
         */
        virtual const Card *removeTopCard();
        /**
         * @brief Checks if the location is empty
         *
         * @return true
         * @return false
         */
        bool isEmpty() const;

    protected:
        /**
         * @brief Cards that form the location.
         *
         */
        std::vector<const Card *> mCards;
        /**
         * @brief Location code of this specific instance
         *
         */
        FaceUpCardLocationCode mLocationCode;
    };
}

#endif