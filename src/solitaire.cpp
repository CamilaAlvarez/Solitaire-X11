// SPDX-License-Identifier:    MIT
/*
 * Solitaire class implementation
 *
 * Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 */
#include "solitaire/solitaire.hpp"

namespace solitaire
{
    Solitaire::Solitaire(WastePile *wastepile, StockPile *stockpile, std::vector<Foundation *> foundations, std::vector<Column *> columns)
        : mWastepile(wastepile), mStockpile(stockpile), mFoundations(foundations), mColumns(columns)
    {
        for (size_t i = 0; i < NUMBER_SUIT; i++)
        {
            for (size_t j = 0; j < NUMBER_RANKS; j++)
            {
                CardStatus status;
                status.onTop = false;
                status.revealed = false;
                status.onColumn = false;
                status.onFoundation = false;
                Card::Suit oppositeSuit1, oppositeSuit2;
                Card::Rank previousCardRank;
                std::optional<Card::Rank>
                    rankColumn, rankFoundation;
                Card::Suit suit = (Card::Suit)i;
                Card::Rank rank = (Card::Rank)j;
                switch (suit)
                {
                case Card::Suit::Clubs:
                case Card::Suit::Spades:
                    oppositeSuit1 = Card::Suit::Hearts;
                    oppositeSuit2 = Card::Suit::Diamonds;
                    break;
                case Card::Suit::Hearts:
                case Card::Suit::Diamonds:
                    oppositeSuit1 = Card::Suit::Clubs;
                    oppositeSuit2 = Card::Suit::Spades;
                    break;
                }
                switch (rank)
                {
                case Card::Rank::A:
                    rankColumn = Card::Rank::N2;
                    rankFoundation = std::nullopt;
                    break;
                case Card::Rank::N2:
                case Card::Rank::N3:
                case Card::Rank::N4:
                case Card::Rank::N5:
                case Card::Rank::N6:
                case Card::Rank::N7:
                case Card::Rank::N8:
                case Card::Rank::N9:
                case Card::Rank::N10:
                case Card::Rank::J:
                case Card::Rank::Q:
                    rankColumn = (Card::Rank)(j + 1);
                    rankFoundation = (Card::Rank)(j - 1);
                    break;
                case Card::Rank::K:
                    rankColumn = std::nullopt;
                    rankFoundation = Card::Rank::Q;
                    break;
                }
                Card card(suit, rank);
                if (rankColumn == std::nullopt)
                {
                    status.playOnColumns = std::nullopt;
                }
                else
                {
                    previousCardRank = rankColumn.value();
                    status.playOnColumns = {
                        Card(oppositeSuit1, previousCardRank).cardCode(),
                        Card(oppositeSuit2, previousCardRank).cardCode(),
                    };
                }
                if (rankFoundation == std::nullopt)
                {
                    status.playOnFoundation = std::nullopt;
                }
                else
                {
                    previousCardRank = rankFoundation.value();
                    status.playOnFoundation = Card(suit, previousCardRank).cardCode();
                }
                mCardStatuses[card.cardCode()] = status;
            }
        }
        std::vector<const Card *> cards;
        while (!mStockpile->isEmpty())
        {
            const Card *c = mStockpile->revealCard();
            mCardStatuses[c->cardCode()].revealed = true;
            mCardStatuses[c->cardCode()].onTop = true;
            mCardStatuses[c->cardCode()].onColumn = true;
            cards.push_back(c);
        }
        mStockpile->reloadStockpile(std::vector<const Card *>(cards.rbegin(), cards.rend()));
        for (const Column *c : mColumns)
        {
            std::optional<const Card *> topCard = c->getTopCard();
            if (topCard.has_value())
            {
                const Card *card = topCard.value();
                mCardStatuses[card->cardCode()].revealed = true;
                mCardStatuses[card->cardCode()].onTop = true;
                mCardStatuses[card->cardCode()].onColumn = true;
            }
        }
    }

    bool Solitaire::moveCard(FaceUpCardLocation::FaceUpCardLocationCode from, FaceUpCardLocation::FaceUpCardLocationCode to)
    {
        FaceUpCardLocation *fromLocation, *toLocation;
        bool toLocationIsColumn = false, toLocationInFoundation = false;
        switch (from)
        {
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation0:
            fromLocation = mFoundations[0];
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation1:
            fromLocation = mFoundations[1];
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation2:
            fromLocation = mFoundations[2];
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation3:
            fromLocation = mFoundations[3];
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column0:
            fromLocation = mColumns[0];
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column1:
            fromLocation = mColumns[1];
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column2:
            fromLocation = mColumns[2];
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column3:
            fromLocation = mColumns[3];
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column4:
            fromLocation = mColumns[4];
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column5:
            fromLocation = mColumns[5];
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column6:
            fromLocation = mColumns[6];
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::WastePile:
            fromLocation = mWastepile;
            break;
        default:
            throw std::invalid_argument("Solitaire: invalid location from moveCard");
        }
        switch (to)
        {
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation0:
            toLocation = mFoundations[0];
            toLocationInFoundation = true;
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation1:
            toLocation = mFoundations[1];
            toLocationInFoundation = true;
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation2:
            toLocation = mFoundations[2];
            toLocationInFoundation = true;
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation3:
            toLocation = mFoundations[3];
            toLocationInFoundation = true;
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column0:
            toLocation = mColumns[0];
            toLocationIsColumn = true;
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column1:
            toLocation = mColumns[1];
            toLocationIsColumn = true;
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column2:
            toLocation = mColumns[2];
            toLocationIsColumn = true;
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column3:
            toLocation = mColumns[3];
            toLocationIsColumn = true;
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column4:
            toLocation = mColumns[4];
            toLocationIsColumn = true;
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column5:
            toLocation = mColumns[5];
            toLocationIsColumn = true;
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::Column6:
            toLocation = mColumns[6];
            toLocationIsColumn = true;
            break;
        case FaceUpCardLocation::FaceUpCardLocationCode::WastePile:
            throw std::invalid_argument("Solitaire:: cannot move card to wastepile");
            break;
        default:
            throw std::invalid_argument("Solitaire: invalid location to moveCard");
        }
        // Get the card from the from location
        std::optional<const Card *> topCardFrom = fromLocation->getTopCard();
        // If the from location is empty we return false
        if (topCardFrom == std::nullopt)
        {
            return false;
        }
        const Card *card = topCardFrom.value();
        // Check if the card can be added in the to location
        bool canAddCard = toLocation->canPlayCardOnTop(card);
        if (!canAddCard)
        {
            return false;
        }
        // If it can be added we remove it from the from location
        fromLocation->removeTopCard();
        topCardFrom = fromLocation->getTopCard();
        if (topCardFrom.has_value())
        {
            mCardStatuses[topCardFrom.value()->cardCode()].onTop = true;
            // in the case a hidden card became the top card
            mCardStatuses[topCardFrom.value()->cardCode()].revealed = true;
        }
        std::optional<const Card *> topCardTo = toLocation->getTopCard();
        if (topCardTo.has_value())
        {
            mCardStatuses[topCardTo.value()->cardCode()].onTop = false;
        }
        // now we add it to the to location
        toLocation->addCardToTop(card);
        mCardStatuses[card->cardCode()].onTop = true;
        mCardStatuses[card->cardCode()].onColumn = toLocationIsColumn;
        mCardStatuses[card->cardCode()].onFoundation = toLocationInFoundation;
        return true;
    }

    std::optional<const Card *> Solitaire::getTopCard(FaceUpCardLocation::FaceUpCardLocationCode from) const
    {
        switch (from)
        {
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation0:
            return mFoundations[0]->getTopCard();
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation1:
            return mFoundations[1]->getTopCard();
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation2:
            return mFoundations[2]->getTopCard();
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation3:
            return mFoundations[3]->getTopCard();
        case FaceUpCardLocation::FaceUpCardLocationCode::Column0:
            return mColumns[0]->getTopCard();
        case FaceUpCardLocation::FaceUpCardLocationCode::Column1:
            return mColumns[1]->getTopCard();
        case FaceUpCardLocation::FaceUpCardLocationCode::Column2:
            return mColumns[2]->getTopCard();
        case FaceUpCardLocation::FaceUpCardLocationCode::Column3:
            return mColumns[3]->getTopCard();
        case FaceUpCardLocation::FaceUpCardLocationCode::Column4:
            return mColumns[4]->getTopCard();
        case FaceUpCardLocation::FaceUpCardLocationCode::Column5:
            return mColumns[5]->getTopCard();
        case FaceUpCardLocation::FaceUpCardLocationCode::Column6:
            return mColumns[6]->getTopCard();
        case FaceUpCardLocation::FaceUpCardLocationCode::WastePile:
            return mWastepile->getTopCard();
        default:
            throw std::invalid_argument("Solitaire: invalid location for getTopCard");
        }
    }

    std::optional<const Card *> Solitaire::revealFromStockpile()
    {
        if (mStockpile->isEmpty())
        {
            return std::nullopt;
        }
        const Card *stockpileCard = mStockpile->revealCard();
        mCardStatuses[stockpileCard->cardCode()].revealed = true;
        mWastepile->addCardToTop(stockpileCard);
        return stockpileCard;
    }

    void Solitaire::refreshStockPile()
    {
        if (!mStockpile->isEmpty())
        {
            throw std::runtime_error("Solitaire: Stock pile cannot be refresh, it is not empty");
        }
        if (mWastepile->isEmpty())
        {
            throw std::runtime_error("Solitaire: Waste pile is empty, cannot reload stock pile");
        }
        std::vector<const Card *> newStockpile = mWastepile->emptyWastePile();
        mStockpile->reloadStockpile(newStockpile);
    }

    Solitaire::GameStatus Solitaire::checkGameStatus() const
    {
        bool hasWon = true, canMoveAnyCards = false;
        // If there are no hidden cards left, then we should be able to complete all foundations
        for (Column *c : mColumns)
        {
            hasWon = hasWon && (c->getNumberHiddenCards() == 0);
        }
        if (hasWon)
        {
            return Solitaire::GameStatus::Win;
        }
        for (Foundation *f : mFoundations)
        {
            hasWon = hasWon && f->isComplete();
        }

        if (hasWon)
        {
            return Solitaire::GameStatus::Win;
        }
        // If at least one card can be movedm then we haven't lost
        // TODO: Check for cyclic movements (column0 -> column1 -> column0 -> column1 -> ...)
        for (auto const &card : mCardStatuses)
        {
            bool cardHasSpot = false;
            // Card is visible
            if (card.second.revealed)
            {
                std::optional<std::string> foundationCards = card.second.playOnFoundation;
                std::optional<std::vector<std::string>> columnCards = card.second.playOnColumns;
                if (!foundationCards.has_value())
                {
                    for (const Foundation *f : mFoundations)
                    {
                        if (f->isEmpty())
                        {
                            cardHasSpot = true;
                            break;
                        }
                    }
                }
                else
                {
                    cardHasSpot = (mCardStatuses.at(foundationCards.value()).onTop && mCardStatuses.at(foundationCards.value()).onFoundation);
                }
                // If we already found a spot
                if (cardHasSpot)
                {
                    canMoveAnyCards = true;
                    break;
                }
                if (!columnCards.has_value())
                {
                    for (const Column *c : mColumns)
                    {
                        if (c->isEmpty())
                        {
                            cardHasSpot = true;
                            break;
                        }
                    }
                }
                else
                {
                    std::vector<std::string> options = columnCards.value();
                    cardHasSpot = (mCardStatuses.at(options[0]).onTop && mCardStatuses.at(options[0]).onColumn) || (mCardStatuses.at(options[1]).onTop && mCardStatuses.at(options[1]).onColumn);
                }
                // If we already found a spot
                if (cardHasSpot)
                {
                    canMoveAnyCards = true;
                    break;
                }
            }
        }
        if (!canMoveAnyCards)
        {
            return Solitaire::GameStatus::Lose;
        }

        return Solitaire::GameStatus::Playing;
    }

    bool Solitaire::isStockPileEmpty() const
    {
        return mStockpile->isEmpty();
    }

    unsigned int Solitaire::getNumberOfPlayedCardsFrom(FaceUpCardLocation::FaceUpCardLocationCode from) const
    {
        switch (from)
        {
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation0:
            return mFoundations[0]->getNumberOfCards();
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation1:
            return mFoundations[1]->getNumberOfCards();
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation2:
            return mFoundations[2]->getNumberOfCards();
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation3:
            return mFoundations[3]->getNumberOfCards();
        case FaceUpCardLocation::FaceUpCardLocationCode::Column0:
            return mColumns[0]->getNumberOfCards();
        case FaceUpCardLocation::FaceUpCardLocationCode::Column1:
            return mColumns[1]->getNumberOfCards();
        case FaceUpCardLocation::FaceUpCardLocationCode::Column2:
            return mColumns[2]->getNumberOfCards();
        case FaceUpCardLocation::FaceUpCardLocationCode::Column3:
            return mColumns[3]->getNumberOfCards();
        case FaceUpCardLocation::FaceUpCardLocationCode::Column4:
            return mColumns[4]->getNumberOfCards();
        case FaceUpCardLocation::FaceUpCardLocationCode::Column5:
            return mColumns[5]->getNumberOfCards();
        case FaceUpCardLocation::FaceUpCardLocationCode::Column6:
            return mColumns[6]->getNumberOfCards();
        case FaceUpCardLocation::FaceUpCardLocationCode::WastePile:
            return mWastepile->getNumberOfCards();
        default:
            throw std::invalid_argument("Solitaire: invalid location for getNumberOfPlayedCardsFrom");
        }
    }
}