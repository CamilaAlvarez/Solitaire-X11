/* Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 * SPDX-License-Identifier:    MIT
 */
#ifndef _SOLITAIRE_SOLITAIRE_HPP
#define _SOLITAIRE_SOLITAIRE_HPP

#include "solitaire/card.hpp"
#include "solitaire/wastepile.hpp"
#include "solitaire/stockpile.hpp"
#include "solitaire/foundation.hpp"
#include "solitaire/column.hpp"
#include <vector>
#include <string>
#include <map>
#include <optional>

#define NUMBER_FOUNDATIONS 4
#define NUMBER_COLUMNS 7

namespace solitaire
{
    /**
     * @brief Represents all Solitaire mechanics
     *
     */
    class Solitaire
    {
    public:
        /**
         * @brief Represents the state of the game
         *
         */
        enum class GameStatus
        {
            Win,
            Lose,
            Playing
        };
        /**
         * @brief Construct a new Solitaire object
         *
         * @param watepile
         * @param stockpile
         * @param foundations
         * @param columns
         */
        Solitaire(WastePile *wastepile, StockPile *stockpile, std::vector<Foundation *> foundations, std::vector<Column *> columns);
        /**
         * @brief Computes and returns current game status
         *
         * @return GameStatus
         */
        GameStatus checkGameStatus() const;
        /**
         * @brief Move card from one location to the other
         *
         * @param from
         * @param to
         * @return true if the card could be moved
         * @return false otherwise
         * @throw std::invalid_argument when passed an invalid location
         * @throw std::invalid_argument when to location is the waste pile
         */
        bool moveCard(FaceUpCardLocation::FaceUpCardLocationCode from, FaceUpCardLocation::FaceUpCardLocationCode to);
        /**
         * @brief Move N cards from one column to the other
         *
         * @param from
         * @param to
         * @param n
         * @return true if the card could be moved
         * @return false otherwise
         * @throw std::invalid_argument when passed an invalid location, or it is not a column
         * @throw std::invalid_argument when to location is the waste pile
         * @throw std::invalid_argument when from location is not column and n > 1
         */
        bool moveNCards(FaceUpCardLocation::FaceUpCardLocationCode from, FaceUpCardLocation::FaceUpCardLocationCode to, int n);
        /**
         * @brief Get the top card from a location
         *
         * @param from
         * @return const Card*
         * @return std::nullopt whente the location is empty
         * @throw std::invalid_argument when passed an invalid location
         */
        std::optional<const Card *> getTopCard(FaceUpCardLocation::FaceUpCardLocationCode from) const;
        /**
         * @brief Reveals the first card from the stockpile, moving it to the top of the wastepile
         *
         * @return const Card* if the stockpile has elements
         * @return std::nullopt if the stockpile is empty
         */
        std::optional<const Card *> revealFromStockpile();
        /**
         * @brief Moves all cards from the waste pile to the stock pile.
         *
         * @throw std::runtime_error when attempting to perform when the stock pile still has cards
         * @throw std::runtime_error when attempting the waste pile doesn't have cards
         */
        void refreshStockPile();
        /**
         * @brief Checks if the stockpile is empty
         *
         * @return true
         * @return false
         */
        bool isStockPileEmpty() const;
        /**
         * @brief Get the number of played cards on a location
         *
         * @param from
         * @return unsigned int
         * @throw std::invalid_argument when passed an invalid location
         */
        unsigned int getNumberOfPlayedCardsFrom(FaceUpCardLocation::FaceUpCardLocationCode from) const;
        /**
         * @brief Returns the top card n cards from a column
         *
         * @param from
         * @param n
         * @return const Card*
         * @throw std::runtime_error when there is no active game
         * @throw std::invalid_argument when the location is not valid, or n > 1 and from not a column
         */
        std::vector<const Card *> getTopNCards(FaceUpCardLocation::FaceUpCardLocationCode from, unsigned int n) const;
        /**
         * @brief Get the number of hidden cards from a specific location
         *
         * @param from
         * @return unsigned int
         * @throw std::runtime_error when there is no active game
         * @throw std::invalid_argument when the location is not valid
         */
        unsigned int getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode from) const;

    private:
        struct CardStatus
        {
            bool revealed;
            bool onTop;
            std::optional<std::vector<std::string>> playOnColumns;
            std::optional<std::string> playOnFoundation;
            bool onFoundation;
            bool onColumn;
        };
        /**
         * @brief wastepile of the tableau
         *
         */
        WastePile *mWastepile;
        /**
         * @brief Stockpile of the tableau
         *
         */
        StockPile *mStockpile;
        /**
         * @brief Set of foundations. There must be four of them
         *
         */
        std::vector<Foundation *> mFoundations;
        /**
         * @brief Set of columns. There must be 7 of them
         *
         */
        std::vector<Column *> mColumns;
        /**
         * @brief Stores the status for each card and every card
         *
         */
        std::map<const std::string, CardStatus> mCardStatuses;
    };
}

#endif