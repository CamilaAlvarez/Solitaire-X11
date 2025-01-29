#include "gtest/gtest.h"
#include "solitaire/stockpile.hpp"
#include "solitaire/card.hpp"

namespace
{
    class StockPileTest : public testing::Test
    {
    protected:
        solitaire::StockPile *mStockpile;
        std::vector<const solitaire::Card *> mCardsStockPile;
        StockPileTest()
        {
            solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
            solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
            solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
            solitaire::Card *card4 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
            solitaire::Card *card5 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5);
            solitaire::Card *card6 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6);
            solitaire::Card *card7 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::A);
            solitaire::Card *card8 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N2);
            solitaire::Card *card9 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N3);
            solitaire::Card *card10 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N4);
            solitaire::Card *card11 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N5);
            solitaire::Card *card12 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N6);
            solitaire::Card *card13 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::A);
            solitaire::Card *card14 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N2);
            solitaire::Card *card15 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N3);
            solitaire::Card *card16 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N4);
            solitaire::Card *card17 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N5);
            solitaire::Card *card18 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N6);
            solitaire::Card *card19 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::A);
            solitaire::Card *card20 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N2);
            solitaire::Card *card21 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N3);
            solitaire::Card *card22 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N4);
            solitaire::Card *card23 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N5);
            solitaire::Card *card24 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N6);
            mCardsStockPile = {card1, card2, card3, card4, card5, card6, card7, card8,
                               card9, card10, card11, card12, card13, card14, card15, card16,
                               card17, card18, card19, card20, card21, card22, card23, card24};
            mStockpile = new solitaire::StockPile(mCardsStockPile);
        }
        ~StockPileTest()
        {
            delete mStockpile;
            for (const solitaire::Card *c : mCardsStockPile)
            {
                delete c;
            }
        }
    };

    TEST_F(StockPileTest, InvalidNumberOfCardsStockpile)
    {
        const solitaire::Card card1(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::Q);
        const solitaire::Card card2(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J);
        const solitaire::Card card3(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N10);
        const solitaire::Card card4(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9);
        const solitaire::Card card5(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N8);
        const solitaire::Card card6(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N7);
        const solitaire::Card card7(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6);
        const solitaire::Card card8(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5);
        const solitaire::Card card9(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
        const solitaire::Card card10(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        const solitaire::Card card11(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        const solitaire::Card card12(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        const solitaire::Card card13(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::Q);
        const solitaire::Card card14(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::J);
        const solitaire::Card card15(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N10);
        const solitaire::Card card16(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N9);
        const solitaire::Card card17(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N8);
        const solitaire::Card card18(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N7);
        const solitaire::Card card19(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N6);
        const solitaire::Card card20(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N5);
        const solitaire::Card card21(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N4);
        const solitaire::Card card22(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N3);
        const solitaire::Card card23(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N2);
        std::vector<const solitaire::Card *> stockpileCards = {&card1, &card2, &card3, &card4, &card5, &card6,
                                                               &card7, &card8, &card9, &card10, &card11, &card12, &card13, &card14,
                                                               &card15, &card16, &card17, &card18, &card19, &card20, &card21, &card22,
                                                               &card23};
        EXPECT_THROW(solitaire::StockPile stockpile(stockpileCards), std::invalid_argument);
    }

    TEST_F(StockPileTest, RevealCard)
    {
        const solitaire::Card *revealedCard = mStockpile->revealCard();
        ASSERT_EQ(*revealedCard, *mCardsStockPile[23]);
    }

    TEST_F(StockPileTest, RevealTwoCards)
    {
        const solitaire::Card *revealedCard = mStockpile->revealCard();
        ASSERT_EQ(*revealedCard, *mCardsStockPile[23]);
        revealedCard = mStockpile->revealCard();
        ASSERT_EQ(*revealedCard, *mCardsStockPile[22]);
    }

    TEST_F(StockPileTest, RevealCardEmptyStockpile)
    {
        for (size_t i = 0; i < STOCKPILE_SIZE; i++)
        {
            mStockpile->revealCard();
        }

        EXPECT_THROW(mStockpile->revealCard(), std::underflow_error);
    }

    TEST_F(StockPileTest, isEmptyNonEmptyStockpile)
    {
        ASSERT_FALSE(mStockpile->isEmpty());
    }

    TEST_F(StockPileTest, isEmptyEmptyStockpile)
    {
        for (size_t i = 0; i < STOCKPILE_SIZE; i++)
        {
            mStockpile->revealCard();
        }
        ASSERT_TRUE(mStockpile->isEmpty());
    }

    TEST_F(StockPileTest, ReloadStockPile)
    {
        const solitaire::Card card1(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J);
        std::vector<const solitaire::Card *> cards = {&card1};
        for (size_t i = 0; i < STOCKPILE_SIZE; i++)
        {
            mStockpile->revealCard();
        }
        ASSERT_TRUE(mStockpile->isEmpty());
        mStockpile->reloadStockpile(cards);
        ASSERT_FALSE(mStockpile->isEmpty());
    }

    TEST_F(StockPileTest, ReloadStockPileNonEmpty)
    {
        const solitaire::Card card1(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J);
        std::vector<const solitaire::Card *> cards = {&card1};
        ASSERT_FALSE(mStockpile->isEmpty());
        EXPECT_THROW(mStockpile->reloadStockpile(cards), std::runtime_error);
    }

    TEST_F(StockPileTest, ReloadStockPileEmptyCards)
    {
        for (size_t i = 0; i < STOCKPILE_SIZE; i++)
        {
            mStockpile->revealCard();
        }
        ASSERT_TRUE(mStockpile->isEmpty());
        EXPECT_THROW(mStockpile->reloadStockpile(std::vector<const solitaire::Card *>()), std::invalid_argument);
    }
}
