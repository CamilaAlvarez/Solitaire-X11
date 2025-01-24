#include "gtest/gtest.h"
#include "solitaire/solitaire.hpp"

#define STOCKPILE_START_SIZE 24

namespace
{
    class SolitaireTest : public testing::Test
    {
    public:
        SolitaireTest()
        {
            mWastepile = new solitaire::WastePile();
            mFoundations.push_back(new solitaire::Foundation(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0));
            mFoundations.push_back(new solitaire::Foundation(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation1));
            mFoundations.push_back(new solitaire::Foundation(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation2));
            mFoundations.push_back(new solitaire::Foundation(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation3));
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
            std::vector<const solitaire::Card *> cardsStockPile = {card1, card2, card3, card4, card5, card6, card7, card8,
                                                                   card9, card10, card11, card12, card13, card14, card15, card16,
                                                                   card17, card18, card19, card20, card21, card22, card23, card24};
            mStockpile = new solitaire::StockPile(cardsStockPile);
            solitaire::Card *card25 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N7);
            std::vector<const solitaire::Card *> hiddenColumn0;
            mColumns.push_back(new solitaire::Column(card25, hiddenColumn0, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0));

            solitaire::Card *card26 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N8);
            solitaire::Card *card27 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9);
            std::vector<const solitaire::Card *> hiddenColumn1 = {card27};
            mColumns.push_back(new solitaire::Column(card26, hiddenColumn1, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column1));

            solitaire::Card *card29 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J);
            solitaire::Card *card30 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::Q);
            solitaire::Card *card28 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N10);
            std::vector<const solitaire::Card *> hiddenColumn2 = {card30, card29};
            mColumns.push_back(new solitaire::Column(card28, hiddenColumn2, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2));

            solitaire::Card *card31 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::K);
            solitaire::Card *card32 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N7);
            solitaire::Card *card52 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::K);
            solitaire::Card *card51 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::Q);
            std::vector<const solitaire::Card *> hiddenColumn3 = {card32, card52, card31};
            mColumns.push_back(new solitaire::Column(card51, hiddenColumn3, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column3));

            solitaire::Card *card33 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N8);
            solitaire::Card *card34 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N9);
            solitaire::Card *card35 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N10);
            solitaire::Card *card37 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::Q);
            solitaire::Card *card36 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::J);
            std::vector<const solitaire::Card *> hiddenColumn4 = {card34, card35, card37, card33};
            mColumns.push_back(new solitaire::Column(card36, hiddenColumn4, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column4));

            solitaire::Card *card38 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::K);
            solitaire::Card *card39 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N7);
            solitaire::Card *card40 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N8);
            solitaire::Card *card41 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N9);
            solitaire::Card *card42 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N10);
            solitaire::Card *card43 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::J);
            std::vector<const solitaire::Card *> hiddenColumn5 = {card39, card40, card41, card42, card43};
            mColumns.push_back(new solitaire::Column(card38, hiddenColumn5, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column5));

            solitaire::Card *card44 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::Q);
            solitaire::Card *card46 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N7);
            solitaire::Card *card47 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N8);
            solitaire::Card *card48 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N9);
            solitaire::Card *card49 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N10);
            solitaire::Card *card50 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::J);
            solitaire::Card *card45 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::K);
            std::vector<const solitaire::Card *> hiddenColumn6 = {card46, card47, card48, card49, card50, card45};
            mColumns.push_back(new solitaire::Column(card44, hiddenColumn6, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column6));

            mCards = {card1, card2, card3, card4, card5, card6, card7, card8, card9, card10, card11, card12, card13, card14,
                      card15, card16, card17, card18, card19, card20, card21, card22, card23, card24, card25, card26, card27, card28,
                      card29, card30, card31, card32, card33, card34, card35, card36, card37, card38, card39, card40, card41, card42,
                      card43, card44, card45, card46, card47, card48, card49, card50, card51, card52};
            mGame = new solitaire::Solitaire(mWastepile, mStockpile, mFoundations, mColumns);
        }
        ~SolitaireTest()
        {
            delete mGame;
            delete mWastepile;
            delete mStockpile;
            for (solitaire::Foundation *f : mFoundations)
            {
                delete f;
            }
            for (solitaire::Column *c : mColumns)
            {
                delete c;
            }
            for (const solitaire::Card *c : mCards)
            {
                delete c;
            }
        }

    protected:
        solitaire::Solitaire *mGame;
        solitaire::WastePile *mWastepile;
        solitaire::StockPile *mStockpile;
        std::vector<solitaire::Foundation *> mFoundations;
        std::vector<solitaire::Column *> mColumns;
        std::vector<const solitaire::Card *> mCards;
    };

    TEST_F(SolitaireTest, GetTopCardValidLocation)
    {
        std::optional<const solitaire::Card *> card = mGame->getTopCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        EXPECT_NE(card, std::nullopt);
        EXPECT_EQ(*(card.value()), solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N7));
    }

    TEST_F(SolitaireTest, GetTopCardValidEmptyLocation)
    {
        std::optional<const solitaire::Card *> card = mGame->getTopCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0);
        EXPECT_EQ(card, std::nullopt);
        card = mGame->getTopCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::WastePile);
        EXPECT_EQ(card, std::nullopt);
    }

    TEST_F(SolitaireTest, GetTopCardInvalidLocation)
    {
        EXPECT_THROW(mGame->getTopCard((solitaire::FaceUpCardLocation::FaceUpCardLocationCode)25), std::invalid_argument);
    }

    TEST_F(SolitaireTest, MoveCardValidLocationValidMove)
    {
        ASSERT_TRUE(mGame->moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column4));
    }

    TEST_F(SolitaireTest, MoveCardValidLocationInvalidMove)
    {
        ASSERT_FALSE(mGame->moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column1));
    }

    TEST_F(SolitaireTest, MoveCardValidLocationInvalidMove2)
    {
        ASSERT_FALSE(mGame->moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column6, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column3));
    }

    TEST_F(SolitaireTest, MoveCardValidLocationInvalidLocation)
    {
        EXPECT_THROW(mGame->moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column6, (solitaire::FaceUpCardLocation::FaceUpCardLocationCode)25),
                     std::invalid_argument);
    }

    TEST_F(SolitaireTest, MoveCardValidLocationToWastePile)
    {
        EXPECT_THROW(mGame->moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column6, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::WastePile),
                     std::invalid_argument);
    }

    TEST_F(SolitaireTest, MoveNCardsValidLocationValidMove)
    {
        ASSERT_TRUE(mGame->moveNCards(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column4, 1));
    }

    TEST_F(SolitaireTest, MoveNCardsValidLocationValidMove2)
    {
        ASSERT_TRUE(mGame->moveNCards(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column4, 1));
        ASSERT_TRUE(mGame->moveNCards(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column4, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column6, 2));
    }

    TEST_F(SolitaireTest, MoveMCardsValidLocationInvalidMove)
    {
        ASSERT_FALSE(mGame->moveNCards(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column4, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2, 1));
        EXPECT_THROW(mGame->moveNCards(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0, 1), std::invalid_argument);
    }

    TEST_F(SolitaireTest, RevealFromStockPileNotEmpty)
    {
        std::optional<const solitaire::Card *> cardOpt = mGame->revealFromStockpile();
        ASSERT_NE(cardOpt, std::nullopt);
        const solitaire::Card *card = cardOpt.value();
        std::optional<const solitaire::Card *> wastePileCardOpt = mGame->getTopCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::WastePile);
        ASSERT_NE(wastePileCardOpt, std::nullopt);
        const solitaire::Card *wastePileCard = wastePileCardOpt.value();
        ASSERT_EQ(*card, *wastePileCard);
    }

    TEST_F(SolitaireTest, RevealFromStockPileEmpty)
    {
        for (size_t i = 0; i < STOCKPILE_START_SIZE; i++)
        {
            mGame->revealFromStockpile();
        }
        std::optional<const solitaire::Card *> cardOpt = mGame->revealFromStockpile();
        ASSERT_EQ(cardOpt, std::nullopt);
    }

    TEST_F(SolitaireTest, IsStockPileEmpty1)
    {
        ASSERT_FALSE(mGame->isStockPileEmpty());
    }

    TEST_F(SolitaireTest, IsStockPileEmpty2)
    {
        for (size_t i = 0; i < STOCKPILE_START_SIZE; i++)
        {
            mGame->revealFromStockpile();
        }
        ASSERT_TRUE(mGame->isStockPileEmpty());
    }

    TEST_F(SolitaireTest, RefreshStockPileEmpty)
    {
        for (size_t i = 0; i < STOCKPILE_START_SIZE; i++)
        {
            mGame->revealFromStockpile();
        }
        ASSERT_TRUE(mStockpile->isEmpty());
        mGame->refreshStockPile();
        ASSERT_FALSE(mStockpile->isEmpty());
    }

    TEST_F(SolitaireTest, RefreshStockPileNonEmpty)
    {
        ASSERT_FALSE(mStockpile->isEmpty());
        EXPECT_THROW(mGame->refreshStockPile(), std::runtime_error);
    }

    TEST_F(SolitaireTest, GetNumberOfPlayedCards)
    {
        ASSERT_EQ(mGame->getNumberOfPlayedCardsFrom(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0), 1);
    }

    TEST_F(SolitaireTest, GetNumberOfPlayedCardsInvalidLocation)
    {
        EXPECT_THROW(mGame->getNumberOfPlayedCardsFrom((solitaire::FaceUpCardLocation::FaceUpCardLocationCode)25), std::invalid_argument);
    }

    TEST_F(SolitaireTest, checkStatusWin)
    {
        const unsigned int NUMBER_CONTINUOUS_CARDS1 = 13;
        const unsigned int NUMBER_CONTINUOUS_CARDS2 = 11;
        const solitaire::Card card1(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J);
        const solitaire::Card card2(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N10);
        const solitaire::Card card3(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9);
        const solitaire::Card card4(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N8);
        const solitaire::Card card5(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N7);
        const solitaire::Card card6(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6);
        const solitaire::Card card7(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5);
        const solitaire::Card card8(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
        const solitaire::Card card9(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        const solitaire::Card card10(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        const solitaire::Card card11(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        const solitaire::Card card12(solitaire::Card::Suit::Spades, solitaire::Card::Rank::K);
        // Second part stockpile
        const solitaire::Card card13(solitaire::Card::Suit::Spades, solitaire::Card::Rank::Q);
        const solitaire::Card card14(solitaire::Card::Suit::Spades, solitaire::Card::Rank::J);
        const solitaire::Card card15(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N10);
        const solitaire::Card card16(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N9);
        const solitaire::Card card17(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N8);
        const solitaire::Card card18(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N7);
        const solitaire::Card card19(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N6);
        const solitaire::Card card20(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N5);
        const solitaire::Card card21(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N4);
        const solitaire::Card card22(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N3);
        const solitaire::Card card23(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N2);
        const solitaire::Card card24(solitaire::Card::Suit::Spades, solitaire::Card::Rank::A);
        std::vector<const solitaire::Card *> stockpileCards = {&card1, &card2, &card3, &card4, &card5, &card6,
                                                               &card7, &card8, &card9, &card10, &card11, &card12, &card13, &card14,
                                                               &card15, &card16, &card17, &card18, &card19, &card20, &card21, &card22,
                                                               &card23, &card24};
        solitaire::StockPile stockpile(stockpileCards);
        solitaire::WastePile wastepile;
        solitaire::Foundation foundation0(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0),
            foundation1(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation1),
            foundation2(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation2),
            foundation3(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation3);
        std::vector<solitaire::Foundation *> foundations = {&foundation0, &foundation1, &foundation2, &foundation3};

        // Top cards
        const solitaire::Card card25(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::Q);
        const solitaire::Card card26(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::K);
        const solitaire::Card card27(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N2);
        const solitaire::Card card28(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N5);
        const solitaire::Card card29(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N9);
        const solitaire::Card card30(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::A);
        const solitaire::Card card31(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N7);

        // Hidden cards
        const solitaire::Card card32(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::A);
        const solitaire::Card card33(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N3);
        const solitaire::Card card34(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N4);
        const solitaire::Card card35(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N6);
        const solitaire::Card card36(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N7);
        const solitaire::Card card37(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N8);
        const solitaire::Card card38(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N10);
        const solitaire::Card card39(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::J);
        const solitaire::Card card40(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::Q);
        const solitaire::Card card41(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::K);
        const solitaire::Card card42(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N2);
        const solitaire::Card card43(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N3);
        const solitaire::Card card44(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N4);
        const solitaire::Card card45(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N5);
        const solitaire::Card card46(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N6);
        const solitaire::Card card47(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N8);
        const solitaire::Card card48(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N9);
        const solitaire::Card card49(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N10);
        const solitaire::Card card50(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::J);
        const solitaire::Card card51(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::Q);
        const solitaire::Card card52(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::K);

        std::vector<const solitaire::Card *> cardsColumn0;
        std::vector<const solitaire::Card *> cardsColumn1 = {&card32};
        std::vector<const solitaire::Card *> cardsColumn2 = {&card34, &card33};
        std::vector<const solitaire::Card *> cardsColumn3 = {&card37, &card36, &card35};
        std::vector<const solitaire::Card *> cardsColumn4 = {&card41, &card40, &card39, &card38};
        std::vector<const solitaire::Card *> cardsColumn5 = {&card46, &card45, &card44, &card43, &card42};
        std::vector<const solitaire::Card *> cardsColumn6 = {&card52, &card51, &card50, &card49, &card48, &card47};

        solitaire::Column column0(&card25, cardsColumn0, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0),
            column1(&card26, cardsColumn1, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column1),
            column2(&card27, cardsColumn2, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2),
            column3(&card28, cardsColumn3, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column3),
            column4(&card29, cardsColumn4, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column4),
            column5(&card30, cardsColumn5, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column5),
            column6(&card31, cardsColumn6, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column6);
        std::vector<solitaire::Column *> columns = {&column0, &column1, &column2, &column3, &column4, &column5, &column6};
        solitaire::Solitaire game(&wastepile, &stockpile, foundations, columns);
        for (size_t i = 0; i < NUMBER_CONTINUOUS_CARDS1; i++)
        {
            game.revealFromStockpile();
            ASSERT_TRUE(game.moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::WastePile, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0));
        }
        for (size_t i = 0; i < NUMBER_CONTINUOUS_CARDS2; i++)
        {
            game.revealFromStockpile();
            ASSERT_TRUE(game.moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::WastePile, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation1));
        }
        ASSERT_TRUE(game.moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation1));
        ASSERT_TRUE(game.moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column1, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation1));
        ASSERT_TRUE(game.moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column1, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation2));
        for (size_t i = 0; i < HIDDEN_CARDS_COLUMN2 + 1; i++)
        {
            ASSERT_TRUE(game.moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation2));
        }
        for (size_t i = 0; i < HIDDEN_CARDS_COLUMN3 + 1; i++)
        {
            ASSERT_TRUE(game.moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column3, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation2));
        }
        for (size_t i = 0; i < HIDDEN_CARDS_COLUMN4 + 1; i++)
        {
            ASSERT_TRUE(game.moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column4, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation2));
        }
        for (size_t i = 0; i < HIDDEN_CARDS_COLUMN5 + 1; i++)
        {
            ASSERT_TRUE(game.moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column5, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation3));
        }
        for (size_t i = 0; i < HIDDEN_CARDS_COLUMN6 + 1; i++)
        {
            ASSERT_TRUE(game.moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column6, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation3));
        }

        ASSERT_EQ(game.checkGameStatus(), solitaire::Solitaire::GameStatus::Win);
    }

    TEST_F(SolitaireTest, checkStatusLose)
    {
        const unsigned int NUMBER_CONTINUOUS_CARDS = 6;
        // First part stockpile
        const solitaire::Card card1(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N6);
        const solitaire::Card card2(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N5);
        const solitaire::Card card3(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N4);
        const solitaire::Card card4(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N3);
        const solitaire::Card card5(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N2);
        const solitaire::Card card6(solitaire::Card::Suit::Spades, solitaire::Card::Rank::A);
        const solitaire::Card card7(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6);
        const solitaire::Card card8(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5);
        const solitaire::Card card9(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
        const solitaire::Card card10(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        const solitaire::Card card11(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        const solitaire::Card card12(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        // Second part stockpile
        const solitaire::Card card13(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N6);
        const solitaire::Card card14(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N5);
        const solitaire::Card card15(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N4);
        const solitaire::Card card16(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N3);
        const solitaire::Card card17(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N2);
        const solitaire::Card card18(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::A);
        const solitaire::Card card19(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N6);
        const solitaire::Card card20(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N5);
        const solitaire::Card card21(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N4);
        const solitaire::Card card22(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N3);
        const solitaire::Card card23(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N2);
        const solitaire::Card card24(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::A);
        std::vector<const solitaire::Card *> stockpileCards = {&card1, &card2, &card3, &card4, &card5, &card6,
                                                               &card7, &card8, &card9, &card10, &card11, &card12, &card13, &card14,
                                                               &card15, &card16, &card17, &card18, &card19, &card20, &card21, &card22,
                                                               &card23, &card24};
        solitaire::StockPile stockpile(stockpileCards);
        solitaire::WastePile wastepile;
        solitaire::Foundation foundation0(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0),
            foundation1(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation1),
            foundation2(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation2),
            foundation3(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation3);

        std::vector<solitaire::Foundation *> foundations = {&foundation0, &foundation1, &foundation2, &foundation3};

        // Top cards
        const solitaire::Card card25(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N8);
        const solitaire::Card card26(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N9);
        const solitaire::Card card27(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N10);
        const solitaire::Card card28(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::J);
        const solitaire::Card card29(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::Q);
        const solitaire::Card card30(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::K);
        const solitaire::Card card31(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N8);

        // Hidden cards
        const solitaire::Card card32(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N7);
        const solitaire::Card card33(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N7);
        const solitaire::Card card34(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N9);
        const solitaire::Card card35(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N10);
        const solitaire::Card card36(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::J);
        const solitaire::Card card37(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::Q);
        const solitaire::Card card38(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::K);
        const solitaire::Card card39(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N7);
        const solitaire::Card card40(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N8);
        const solitaire::Card card41(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9);
        const solitaire::Card card42(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N10);
        const solitaire::Card card43(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J);
        const solitaire::Card card44(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::Q);
        const solitaire::Card card45(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::K);
        const solitaire::Card card46(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N7);
        const solitaire::Card card47(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N8);
        const solitaire::Card card48(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N9);
        const solitaire::Card card49(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N10);
        const solitaire::Card card50(solitaire::Card::Suit::Spades, solitaire::Card::Rank::J);
        const solitaire::Card card51(solitaire::Card::Suit::Spades, solitaire::Card::Rank::Q);
        const solitaire::Card card52(solitaire::Card::Suit::Spades, solitaire::Card::Rank::K);

        std::vector<const solitaire::Card *> cardsColumn0;
        std::vector<const solitaire::Card *> cardsColumn1 = {&card32};
        std::vector<const solitaire::Card *> cardsColumn2 = {&card33, &card34};
        std::vector<const solitaire::Card *> cardsColumn3 = {&card35, &card36, &card37};
        std::vector<const solitaire::Card *> cardsColumn4 = {&card38, &card39, &card40, &card41};
        std::vector<const solitaire::Card *> cardsColumn5 = {&card42, &card43, &card44, &card45, &card46};
        std::vector<const solitaire::Card *> cardsColumn6 = {&card47, &card48, &card49, &card50, &card51, &card52};

        solitaire::Column column0(&card25, cardsColumn0, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0),
            column1(&card26, cardsColumn1, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column1),
            column2(&card27, cardsColumn2, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2),
            column3(&card28, cardsColumn3, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column3),
            column4(&card29, cardsColumn4, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column4),
            column5(&card30, cardsColumn5, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column5),
            column6(&card31, cardsColumn6, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column6);
        std::vector<solitaire::Column *> columns = {&column0, &column1, &column2, &column3, &column4, &column5, &column6};
        solitaire::Solitaire game(&wastepile, &stockpile, foundations, columns);
        for (size_t i = 0; i < NUMBER_CONTINUOUS_CARDS; i++)
        {
            game.revealFromStockpile();
            ASSERT_TRUE(game.moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::WastePile, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0));
        }
        for (size_t i = 0; i < NUMBER_CONTINUOUS_CARDS; i++)
        {
            game.revealFromStockpile();
            ASSERT_TRUE(game.moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::WastePile, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation1));
        }
        for (size_t i = 0; i < NUMBER_CONTINUOUS_CARDS; i++)
        {
            game.revealFromStockpile();
            ASSERT_TRUE(game.moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::WastePile, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation2));
        }
        for (size_t i = 0; i < NUMBER_CONTINUOUS_CARDS; i++)
        {
            game.revealFromStockpile();
            ASSERT_TRUE(game.moveCard(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::WastePile, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation3));
        }
        ASSERT_EQ(game.checkGameStatus(), solitaire::Solitaire::GameStatus::Lose);
    }

    TEST_F(SolitaireTest, checkStatusPlaying)
    {
        ASSERT_EQ(mGame->checkGameStatus(), solitaire::Solitaire::GameStatus::Playing);
    }

    TEST_F(SolitaireTest, GetTopNCards)
    {
        std::vector<const solitaire::Card *> cards = mGame->getTopNCards(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0, 1);
        ASSERT_EQ(*cards[0], *mCards[24]);
        ASSERT_EQ(cards.size(), 1);
    }

    TEST_F(SolitaireTest, GetTopNCardsInvalidLocation)
    {
        EXPECT_THROW(mGame->getTopNCards(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0, 2), std::invalid_argument);
        EXPECT_THROW(mGame->getTopNCards((solitaire::FaceUpCardLocation::FaceUpCardLocationCode)25, 1), std::invalid_argument);
    }
}