#include "gtest/gtest.h"
#include "solitaire/deck.hpp"
#include <stdexcept>

namespace
{
    static const int DECK_SIZE = 52;
    class DeckTest : public testing::Test
    {
    public:
    protected:
        DeckTest()
        {
            solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::Q);

            solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::K);
            solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::A);

            solitaire::Card *card4 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N2);
            solitaire::Card *card5 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N4);
            solitaire::Card *card6 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N3);

            solitaire::Card *card7 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N5);
            solitaire::Card *card8 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N8);
            solitaire::Card *card9 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N7);
            solitaire::Card *card10 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N6);

            solitaire::Card *card11 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N9);
            solitaire::Card *card12 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::K);
            solitaire::Card *card13 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::Q);
            solitaire::Card *card14 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::J);
            solitaire::Card *card15 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N10);

            solitaire::Card *card16 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::A);
            solitaire::Card *card17 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N6);
            solitaire::Card *card18 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N5);
            solitaire::Card *card19 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N4);
            solitaire::Card *card20 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N3);
            solitaire::Card *card21 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N2);

            solitaire::Card *card22 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N7);
            solitaire::Card *card23 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::K);
            solitaire::Card *card24 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::Q);
            solitaire::Card *card25 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::J);
            solitaire::Card *card26 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N10);
            solitaire::Card *card27 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N9);
            solitaire::Card *card28 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N8);

            solitaire::Card *card29 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J);
            solitaire::Card *card30 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N10);
            solitaire::Card *card31 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9);
            solitaire::Card *card32 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N8);
            solitaire::Card *card33 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N7);
            solitaire::Card *card34 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6);
            solitaire::Card *card35 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5);
            solitaire::Card *card36 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
            solitaire::Card *card37 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
            solitaire::Card *card38 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
            solitaire::Card *card39 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
            solitaire::Card *card40 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::K);
            solitaire::Card *card41 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::Q);
            solitaire::Card *card42 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::J);
            solitaire::Card *card43 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N10);
            solitaire::Card *card44 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N9);
            solitaire::Card *card45 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N8);
            solitaire::Card *card46 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N7);
            solitaire::Card *card47 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N6);
            solitaire::Card *card48 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N5);
            solitaire::Card *card49 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N4);
            solitaire::Card *card50 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N3);
            solitaire::Card *card51 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N2);
            solitaire::Card *card52 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::A);

            mCards = {card1, card2, card3, card4, card5, card6, card7, card8,
                      card9, card10, card11, card12, card13, card14, card15, card16, card17, card18, card19, card20, card21,
                      card22, card23, card24, card25, card26, card27, card28, card29, card30, card31, card32, card33, card34,
                      card35, card36, card37, card38, card39, card40, card41, card42, card43, card44, card45, card46, card47,
                      card48, card49, card50, card51, card52};

            mDeck = new solitaire::Deck(mCards);
        }

        ~DeckTest()
        {
            for (size_t i = 0; i < DECK_SIZE; i++)
            {
                delete mCards[i];
            }
            delete mDeck;
        }

        solitaire::Deck *mDeck;
        std::vector<const solitaire::Card *> mCards;
    };

    TEST_F(DeckTest, InvalidDeck)
    {
        delete mCards[51];
        mCards[51] = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::Q);
        EXPECT_THROW(solitaire::Deck deck(mCards), std::invalid_argument);
    }

    TEST_F(DeckTest, Get0Cards)
    {
        std::vector<const solitaire::Card *> subDeck = mDeck->extractNCards(0);
        ASSERT_EQ(subDeck, std::vector<const solitaire::Card *>());
        ASSERT_EQ(subDeck.size(), 0);
    }

    TEST_F(DeckTest, Get1Card)
    {
        std::vector<const solitaire::Card *> subDeck = mDeck->extractNCards(1);
        ASSERT_EQ(subDeck[0], mCards[0]);
        ASSERT_EQ(subDeck.size(), 1);
    }

    TEST_F(DeckTest, GetWholeDeck)
    {
        std::vector<const solitaire::Card *> subDeck = mDeck->extractNCards(DECK_SIZE);
        for (size_t i = 0; i < DECK_SIZE; i++)
        {
            ASSERT_EQ(subDeck[i], mCards[i]);
        }
        ASSERT_EQ(subDeck.size(), DECK_SIZE);
    }

    TEST_F(DeckTest, GetMoreCardsThanExistInDeckTwoExtractions)
    {
        std::vector<const solitaire::Card *> subDeck = mDeck->extractNCards(DECK_SIZE - 1);
        for (size_t i = 0; i < DECK_SIZE - 1; i++)
        {
            ASSERT_EQ(subDeck[i], mCards[i]);
        }
        ASSERT_EQ(subDeck.size(), DECK_SIZE - 1);
        ASSERT_THROW(mDeck->extractNCards(2), std::invalid_argument);
    }

    TEST_F(DeckTest, GetMoreCardsThanDeckSize)
    {
        ASSERT_THROW(mDeck->extractNCards(DECK_SIZE + 1), std::invalid_argument);
    }

    TEST_F(DeckTest, RecoverAllCards)
    {
        mDeck->extractNCards(DECK_SIZE);
        EXPECT_THROW(mDeck->extractNCards(1), std::invalid_argument);
        mDeck->recoverAllCards();
        EXPECT_NO_THROW(mDeck->extractNCards(1));
    }

    TEST_F(DeckTest, ShuffleDeck)
    {
        const solitaire::Card *card1 = mCards[0];
        const solitaire::Card *card2 = mCards[1];
        const solitaire::Card *card3 = mCards[2];
        const solitaire::Card *card4 = mCards[3];
        const solitaire::Card *card5 = mCards[4];
        const solitaire::Card *card6 = mCards[5];
        const solitaire::Card *card7 = mCards[6];
        const solitaire::Card *card8 = mCards[7];
        const solitaire::Card *card9 = mCards[8];
        const solitaire::Card *card10 = mCards[9];
        mDeck->shuffle();
        int nPositionChanged = 0;
        std::vector<const solitaire::Card *> shuffledDeck = mDeck->extractNCards(DECK_SIZE);
        // At least one position must have changed
        nPositionChanged += (shuffledDeck[0] == card1) ? 0 : 1;
        nPositionChanged += (shuffledDeck[1] == card2) ? 0 : 1;
        nPositionChanged += (shuffledDeck[2] == card3) ? 0 : 1;
        nPositionChanged += (shuffledDeck[3] == card4) ? 0 : 1;
        nPositionChanged += (shuffledDeck[4] == card5) ? 0 : 1;
        nPositionChanged += (shuffledDeck[5] == card6) ? 0 : 1;
        nPositionChanged += (shuffledDeck[6] == card7) ? 0 : 1;
        nPositionChanged += (shuffledDeck[7] == card8) ? 0 : 1;
        nPositionChanged += (shuffledDeck[8] == card9) ? 0 : 1;
        nPositionChanged += (shuffledDeck[9] == card10) ? 0 : 1;
        ASSERT_GT(nPositionChanged, 0);
    }
}