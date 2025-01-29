#include "gtest/gtest.h"
#include "solitaire/wastepile.hpp"

namespace
{
    TEST(WastePileTest, CannotAddCard)
    {
        solitaire::Card *card = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::A);
        solitaire::WastePile wastepile;
        ASSERT_FALSE(wastepile.canPlayCardOnTop(card));
        delete card;
        card = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        ASSERT_FALSE(wastepile.canPlayCardOnTop(card));
        delete card;
        card = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::A);
        ASSERT_FALSE(wastepile.canPlayCardOnTop(card));
        delete card;
        card = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::A);
        ASSERT_FALSE(wastepile.canPlayCardOnTop(card));
        delete card;
    }

    TEST(WastePileTest, EmptyWastePileNonEmpty)
    {
        solitaire::Card *card = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::A);
        solitaire::WastePile wastepile;
        wastepile.addCardToTop(card);
        wastepile.addCardToTop(card2);
        ASSERT_FALSE(wastepile.isEmpty());
        std::vector<const solitaire::Card *> pile = wastepile.emptyWastePile();
        ASSERT_TRUE(wastepile.isEmpty());
        ASSERT_EQ(*pile[0], *card2);
        ASSERT_EQ(*pile[1], *card);
        delete card;
        delete card2;
    }

    TEST(WastePileTest, EmptyWastePileEmpty)
    {
        solitaire::WastePile wastepile;
        ASSERT_TRUE(wastepile.isEmpty());
        std::vector<const solitaire::Card *> pile = wastepile.emptyWastePile();
        ASSERT_TRUE(wastepile.isEmpty());
        ASSERT_TRUE(pile.empty());
    }
}