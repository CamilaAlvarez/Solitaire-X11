/* Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 * SPDX-License-Identifier:    MIT
 */
#ifndef _SOLITAIRE_COLUMN_HPP
#define _SOLITAIRE_COLUMN_HPP

#include "solitaire/card.hpp"
#include "solitaire/face_up_card_location.hpp"
#include <vector>
#include <optional>

#define HIDDEN_CARDS_COLUMN0 0
#define HIDDEN_CARDS_COLUMN1 1
#define HIDDEN_CARDS_COLUMN2 2
#define HIDDEN_CARDS_COLUMN3 3
#define HIDDEN_CARDS_COLUMN4 4
#define HIDDEN_CARDS_COLUMN5 5
#define HIDDEN_CARDS_COLUMN6 6

namespace solitaire
{
    /**
     * @brief Represents each of the columns located in the lower part of
     * the tableau. Each has a number of hidden cards ranging from 0 to 6.
     *
     */
    class Column : public FaceUpCardLocation
    {
    public:
        /**
         * @brief Construct a new Column object.
         *
         * @param card initial visible card
         * @param hiddenCards
         * @param locationCode defines the number of hidden cards
         * @throw std::invalid_argument when the visisble card is null
         * @throw std::invalid_argument when location code is an invalid column
         * @throw std::invalid_arguments if the number of hidden card does not match the column
         */
        Column(const Card *card, std::vector<const Card *> hiddenCards, FaceUpCardLocation::FaceUpCardLocationCode locationCode);
        /**
         * @brief Checks if the card can be added on top. For the column the rule is that the
         * card must be of the opposite rule and must be contiguous. If the space is empty it might be used
         * by any card.
         *
         * @param card
         * @return true
         * @return false
         */
        bool canPlayCardOnTop(const Card *card) const override;
        /**
         * @brief Removes the top card from the location
         *
         * @return const Card*
         * @throw std::underflow_error when the location is empty
         */
        const Card *removeTopCard() override;
        /**
         * @brief Get the current number of hidden cards of the column
         *
         * @return unsigned int
         */
        unsigned int getNumberHiddenCards() const;
        /**
         * @brief Add cards to the end of the visible cards
         *
         * @param cards
         */
        void addCardsToColumn(std::vector<const Card *> cards);
        /**
         * @brief Get the top n visible cards. N must be higher than 0.
         *
         * @param n number of cards to get
         * @return std::vector<const Card *>
         * @throw std::invalid_argument when n is 0
         * @throw std::domain_error when n is higher than the number of visible cards
         */
        std::vector<const Card *> getTopNCards(unsigned int n) const;
        /**
         * @brief Removes the top n card from the location
         *
         * @return const Card*
         * @throw std::invalid_argument when n is 0
         * @throw std::domain_error when n is higher than the number of visible cards
         */
        std::vector<const Card *> removeTopNCards(unsigned int n);

    private:
        /**
         * @brief current hidden cards of the column
         *
         */
        std::vector<const Card *> mHiddenCards;
        /**
         * @brief reveals a hidden card by taking one from the list
         * and adding it to the visible cards list
         *
         */
        void revealHiddenCard();
    };
}
#endif