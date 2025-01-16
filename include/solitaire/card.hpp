/* Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 * SPDX-License-Identifier:    MIT
 */
#ifndef _SOLITAIRE_CARD_HPP
#define _SOLITAIRE_CARD_HPP

#include <stdexcept>
#include <string>

#define NUMBER_SUIT 4
#define NUMBER_RANKS 13

namespace solitaire
{
    /**
     * @brief Class representing a card from a standard 52-card deck
     *
     */
    class Card
    {
    public:
        /**
         * @brief Represents the suit of the cards
         *
         */
        enum class Suit
        {
            Diamonds,
            Hearts,
            Clubs,
            Spades
        };
        /**
         * @brief Represents the rank of a card
         *
         */
        enum class Rank
        {
            A,   /**< Ace */
            N2,  /**< 2 */
            N3,  /**< 3 */
            N4,  /**< 4 */
            N5,  /**< 5 */
            N6,  /**< 6 */
            N7,  /**< 7 */
            N8,  /**< 8 */
            N9,  /**< 9 */
            N10, /**< 10 */
            J,   /**< Jack */
            Q,   /**< Queen */
            K    /**< King */
        };
        /**
         * @brief Construct a new Card object. It verifies that both the suit and rank are valid values
         *
         * @param s suit of the card
         * @param r rank of the card
         * @throw std::invalid_argument when s is an invalid suit or r is an invalid rank
         */
        Card(Suit s, Rank r)
        {
            switch (s)
            {
            case Suit::Clubs:
            case Suit::Spades:
            case Suit::Hearts:
            case Suit::Diamonds:
                mSuit = s;
                break;
            default:
                throw std::invalid_argument("Card: Invalid suit");
            }

            switch (r)
            {
            case Rank::A:
            case Rank::N2:
            case Rank::N3:
            case Rank::N4:
            case Rank::N5:
            case Rank::N6:
            case Rank::N7:
            case Rank::N8:
            case Rank::N9:
            case Rank::N10:
            case Rank::J:
            case Rank::Q:
            case Rank::K:
                mRank = r;
                break;
            default:
                throw std::invalid_argument("Card: Invalid rank");
            }
        }
        /**
         * @brief Checks if the rank is lower than the param's rank
         *
         * @param card Card to compare to
         * @return true
         * @return false
         */
        bool operator<(const Card &card) const
        {
            return this->mRank < card.mRank;
        }
        /**
         * @brief Checks if the rank is equal to the param's rank
         *
         * @param card Card to compare to
         * @return true
         * @return false
         */
        bool operator==(const Card &card) const
        {
            return this->mRank == card.mRank;
        }
        /**
         * @brief Checks if the rank is higher than the param's rank
         *
         * @param card Card to compare to
         * @return true
         * @return false
         */
        bool operator>(const Card &card) const
        {
            return !this->operator<(card) && !this->operator==(card);
        }
        /**
         * @brief Checks if the rank is different to the param's rank
         *
         * @param card Card to compare to
         * @return true
         * @return false
         */
        bool operator!=(const Card &card) const
        {
            return !this->operator==(card);
        }
        /**
         * @brief Checks if the rank is lower than or equal to the param's rank
         *
         * @param card Card to compare to
         * @return true
         * @return false
         */
        bool operator<=(const Card &card) const
        {
            return this->operator<(card) || this->operator==(card);
        }
        /**
         * @brief Checks if the rank is higher than or equal the param's rank
         *
         * @param card Card to compare to
         * @return true
         * @return false
         */
        bool operator>=(const Card &card) const
        {
            return this->operator>(card) || this->operator==(card);
        }
        /**
         * @brief Checks if the suit if the same as the param's suit
         *
         * @param card Card to compare to
         * @return true
         * @return false
         */
        bool isSameSuit(const Card &card) const
        {
            return this->mSuit == card.mSuit;
        }
        /**
         * @brief Checks if the suit is the oppossite color from the param's suit.
         * The opposite colors are as follow:
         *  - Clubs are black so the opposite are the diamonds and hearts which are red
         *  - Spades are black so the opposite are the diamonds and hearts which are red
         *  - Hearts are red so the opposite are the clubs and spades which are black
         *  - Diamonds are red so the opposite are the clubs and spades which are black
         *
         * @param card Card to compare to
         * @return true
         * @return false
         * @throw std::domain_error when the current suit is invalid
         */
        bool isOppositeColor(const Card &card) const
        {
            switch (this->mSuit)
            {
            case Suit::Clubs:
            case Suit::Spades:
                return card.mSuit == Suit::Diamonds || card.mSuit == Suit::Hearts;
            case Suit::Diamonds:
            case Suit::Hearts:
                return card.mSuit == Suit::Clubs || card.mSuit == Suit::Spades;
            default:
                throw std::domain_error("Card: Invalid suit value");
            }
        }
        /**
         * @brief Get the suit of the card
         *
         * @return Suit
         */
        Suit getSuit() const
        {
            return this->mSuit;
        }
        /**
         * @brief Get the rank of the card
         *
         * @return Rank
         */
        Rank getRank() const
        {
            return this->mRank;
        }
        /**
         * @brief Returns a unique code for the card
         *
         * @ return const std::string code of the card
         * @throw std::runtime_error when the suit or rank are invalid∫
         */
        const std::string cardCode() const
        {
            std::string suitStr;
            switch (this->mSuit)
            {
            case Suit::Clubs:
                suitStr = "clubs_";
                break;
            case Suit::Spades:
                suitStr = "spades_";
                break;
            case Suit::Diamonds:
                suitStr = "diamonds_";
                break;
            case Suit::Hearts:
                suitStr = "hearts_";
                break;
            default:
                throw std::domain_error("Card: Invalid suit value");
            }
            switch (this->mRank)
            {
            case Rank::A:
                return suitStr + "A";
            case Rank::N2:
                return suitStr + "2";
            case Rank::N3:
                return suitStr + "3";
            case Rank::N4:
                return suitStr + "4";
            case Rank::N5:
                return suitStr + "5";
            case Rank::N6:
                return suitStr + "6";
            case Rank::N7:
                return suitStr + "7";
            case Rank::N8:
                return suitStr + "8";
            case Rank::N9:
                return suitStr + "9";
            case Rank::N10:
                return suitStr + "10";
            case Rank::J:
                return suitStr + "J";
            case Rank::Q:
                return suitStr + "Q";
            case Rank::K:
                return suitStr + "K";
            default:
                throw std::domain_error("Card: Invalid rank value");
            }
        }

    private:
        /**
         * @brief The suit of the card
         */
        Suit mSuit;
        /**
         * @brief The rank of the card
         */
        Rank mRank;
    };
}

#endif