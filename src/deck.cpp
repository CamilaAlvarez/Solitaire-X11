// SPDX-License-Identifier:    MIT
/*
 * Deck class implementation
 *
 * Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 */
#include "solitaire/deck.hpp"
#include <algorithm>
#include <stdexcept>
#include <string>
#include <map>

namespace solitaire
{
    Deck::Deck(std::vector<const Card *> cards)
    {
        bool foundAllCards = true;
        std::map<std::string, bool> foundCards;
        for (size_t i = 0; i < NUMBER_SUIT; i++)
        {
            for (size_t j = 0; j < NUMBER_RANKS; j++)
            {
                foundCards[Card((Card::Suit)i, (Card::Rank)j).cardCode()] = false;
            }
        }
        for (const Card *c : cards)
        {
            if (foundCards.find(c->cardCode()) != foundCards.end())
            {
                foundCards[c->cardCode()] = true;
            }
        }
        for (auto const &card : foundCards)
        {
            foundAllCards = foundAllCards && card.second;
        }
        if (!foundAllCards)
        {
            throw std::invalid_argument("Deck: Missing cards! Invalid deck");
        }
        mCards = cards;
        std::random_device rd;
        mRandomGenerator = std::mt19937(rd());
        mCurrentIndex = 0;
    }

    std::vector<const Card *> Deck::extractNCards(unsigned int numberOfCards)
    {
        if ((numberOfCards + mCurrentIndex) > mCards.size())
        {
            throw std::invalid_argument("Deck: Invalid number of cards");
        }
        std::vector<const Card *> pickedCards = std::vector<const Card *>(mCards.begin() + mCurrentIndex, mCards.begin() + mCurrentIndex + numberOfCards);
        mCurrentIndex += numberOfCards;
        return pickedCards;
    }

    void Deck::shuffle()
    {
        std::shuffle(mCards.begin(), mCards.end(), mRandomGenerator);
    }

    void Deck::recoverAllCards()
    {
        mCurrentIndex = 0;
    }
}