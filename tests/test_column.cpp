#include "gtest/gtest.h"
#include "solitaire/card.hpp"
#include "solitaire/face_up_card_location.hpp"
#include "solitaire/column.hpp"
#include <stdexcept>

namespace
{
    TEST(ColumnTest, InvalidColumnCreation)
    {
        solitaire::Card card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        std::vector<const solitaire::Card *> cards;
        EXPECT_THROW(solitaire::Column(&card, cards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0),
                     std::invalid_argument);
        EXPECT_THROW(solitaire::Column(&card, cards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation1),
                     std::invalid_argument);
        EXPECT_THROW(solitaire::Column(&card, cards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation2),
                     std::invalid_argument);
        EXPECT_THROW(solitaire::Column(&card, cards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation3),
                     std::invalid_argument);
        EXPECT_THROW(solitaire::Column(&card, cards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::WastePile),
                     std::invalid_argument);
    }

    TEST(ColumnTest, Column0StartWith0HiddenCards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        std::vector<const solitaire::Card *> hiddenCards;
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        ASSERT_EQ(column.getNumberHiddenCards(), 0);
        delete card1;
    }

    TEST(ColumnTest, Column0FailsWithMoreThan0HiddenCards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        std::vector<const solitaire::Card *> hiddenCards = {card2};
        EXPECT_THROW(solitaire::Column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);, std::invalid_argument);
        delete card1;
        delete card2;
    }

    TEST(ColumnTest, Column0FailsWithLessThan1Card)
    {
        std::vector<const solitaire::Card *> hiddenCards;
        EXPECT_THROW(solitaire::Column(nullptr, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);, std::invalid_argument);
    }

    TEST(ColumnTest, Column1StartWith1HiddenCard)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        std::vector<const solitaire::Card *> hiddenCards = {card2};
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column1);
        ASSERT_EQ(column.getNumberHiddenCards(), 1);
        delete card1;
        delete card2;
    }

    TEST(ColumnTest, Column1FailsWithMoreThan1HiddenCards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        std::vector<const solitaire::Card *> hiddenCards = {card2, card3};
        EXPECT_THROW(solitaire::Column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column1);, std::invalid_argument);
        delete card1;
        delete card2;
        delete card3;
    }

    TEST(ColumnTest, Column1FailsWithLessThan1Card)
    {
        std::vector<const solitaire::Card *> hiddenCards;
        EXPECT_THROW(solitaire::Column(nullptr, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column1);, std::invalid_argument);
    }

    TEST(ColumnTest, Column2StartWith2HiddenCards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        std::vector<const solitaire::Card *> hiddenCards = {card2, card3};
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2);
        ASSERT_EQ(column.getNumberHiddenCards(), 2);
        delete card1;
        delete card2;
        delete card3;
    }

    TEST(ColumnTest, Column2FailsWithMoreThan2HiddenCards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        solitaire::Card *card4 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
        std::vector<const solitaire::Card *> hiddenCards = {card2, card3, card4};
        EXPECT_THROW(solitaire::Column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2);, std::invalid_argument);
        delete card1;
        delete card2;
        delete card3;
        delete card4;
    }

    TEST(ColumnTest, Column2FailsWithLessThan1Card)
    {
        std::vector<const solitaire::Card *> hiddenCards;
        EXPECT_THROW(solitaire::Column(nullptr, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2);, std::invalid_argument);
    }

    TEST(ColumnTest, Column3StartWith3HiddenCards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        solitaire::Card *card4 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
        std::vector<const solitaire::Card *> hiddenCards = {card2, card3, card4};
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column3);
        ASSERT_EQ(column.getNumberHiddenCards(), 3);
        delete card1;
        delete card2;
        delete card3;
        delete card4;
    }

    TEST(ColumnTest, Column3FailsWithMoreThan3HiddenCards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        solitaire::Card *card4 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
        solitaire::Card *card5 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5);
        std::vector<const solitaire::Card *> hiddenCards = {card2, card3, card4, card5};
        EXPECT_THROW(solitaire::Column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column3);, std::invalid_argument);
        delete card1;
        delete card2;
        delete card3;
        delete card4;
        delete card5;
    }

    TEST(ColumnTest, Column3FailsWithLessThan1Card)
    {
        std::vector<const solitaire::Card *> hiddenCards;
        EXPECT_THROW(solitaire::Column(nullptr, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column3);, std::invalid_argument);
    }

    TEST(ColumnTest, Column4StartWith4HiddenCards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        solitaire::Card *card4 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
        solitaire::Card *card5 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5);
        std::vector<const solitaire::Card *> hiddenCards = {card2, card3, card4, card5};
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column4);
        ASSERT_EQ(column.getNumberHiddenCards(), 4);
        delete card1;
        delete card2;
        delete card3;
        delete card4;
        delete card5;
    }

    TEST(ColumnTest, Column4FailsWithMoreThan4HiddenCards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        solitaire::Card *card4 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
        solitaire::Card *card5 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5);
        solitaire::Card *card6 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6);
        std::vector<const solitaire::Card *> hiddenCards = {card2, card3, card4, card5, card6};
        EXPECT_THROW(solitaire::Column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column4);, std::invalid_argument);
        delete card1;
        delete card2;
        delete card3;
        delete card4;
        delete card5;
        delete card6;
    }

    TEST(ColumnTest, Column4FailsWithLessThan1Card)
    {
        std::vector<const solitaire::Card *> hiddenCards;
        EXPECT_THROW(solitaire::Column(nullptr, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column4);, std::invalid_argument);
    }

    TEST(ColumnTest, Column5StartWith5HiddenCards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        solitaire::Card *card4 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
        solitaire::Card *card5 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5);
        solitaire::Card *card6 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6);
        std::vector<const solitaire::Card *> hiddenCards = {card2, card3, card4, card5, card6};
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column5);
        ASSERT_EQ(column.getNumberHiddenCards(), 5);
        delete card1;
        delete card2;
        delete card3;
        delete card4;
        delete card5;
        delete card6;
    }

    TEST(ColumnTest, Column5FailsWithMoreThan5HiddenCards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        solitaire::Card *card4 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
        solitaire::Card *card5 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5);
        solitaire::Card *card6 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6);
        solitaire::Card *card7 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N7);
        std::vector<const solitaire::Card *> hiddenCards = {card2, card3, card4, card5, card6, card7};
        EXPECT_THROW(solitaire::Column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column5);, std::invalid_argument);
        delete card1;
        delete card2;
        delete card3;
        delete card4;
        delete card5;
        delete card6;
        delete card7;
    }

    TEST(ColumnTest, Column5FailsWithLessThan1Card)
    {
        std::vector<const solitaire::Card *> hiddenCards;
        EXPECT_THROW(solitaire::Column(nullptr, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column5);, std::invalid_argument);
    }

    TEST(ColumnTest, Column6StartWith6HiddenCards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        solitaire::Card *card4 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
        solitaire::Card *card5 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5);
        solitaire::Card *card6 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6);
        solitaire::Card *card7 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N7);
        std::vector<const solitaire::Card *> hiddenCards = {card2, card3, card4, card5, card6, card7};
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column6);
        ASSERT_EQ(column.getNumberHiddenCards(), 6);
        delete card1;
        delete card2;
        delete card3;
        delete card4;
        delete card5;
        delete card6;
        delete card7;
    }

    TEST(ColumnTest, Column6FailsWithMoreThan6HiddenCards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        solitaire::Card *card4 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
        solitaire::Card *card5 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5);
        solitaire::Card *card6 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6);
        solitaire::Card *card7 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N7);
        solitaire::Card *card8 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N8);
        std::vector<const solitaire::Card *> hiddenCards = {card2, card3, card4, card5, card6, card7, card8};
        EXPECT_THROW(solitaire::Column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column6);, std::invalid_argument);
        delete card1;
        delete card2;
        delete card3;
        delete card4;
        delete card5;
        delete card6;
        delete card7;
        delete card8;
    }

    TEST(ColumnTest, Column6FailsWithLessThan1Card)
    {
        std::vector<const solitaire::Card *> hiddenCards;
        EXPECT_THROW(solitaire::Column(nullptr, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column6);, std::invalid_argument);
    }

    TEST(ColumnTest, GetTopCardNotEmptyColumnUpdateHiddenCards)
    {
        solitaire::Card *card = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::A);
        std::vector<const solitaire::Card *> hiddenCards = {card2};
        solitaire::Column column(card, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column1);
        column.removeTopCard();
        ASSERT_EQ(column.getNumberHiddenCards(), 0);
        delete card;
        delete card2;
    }

    TEST(ColumnTest, CanPlayCard1)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        std::vector<const solitaire::Card *> hiddenCards;
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        solitaire::Card *cardToAdd = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::A);
        ASSERT_TRUE(column.canPlayCardOnTop(cardToAdd));
        delete card1;
        delete cardToAdd;
    }

    TEST(ColumnTest, CanPlayCard2)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        std::vector<const solitaire::Card *> hiddenCards;
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        solitaire::Card *cardToAdd = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::A);
        ASSERT_TRUE(column.canPlayCardOnTop(cardToAdd));
        delete card1;
        delete cardToAdd;
    }

    TEST(ColumnTest, CannotPlayCardSameSuit)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        std::vector<const solitaire::Card *> hiddenCards;
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        solitaire::Card *cardToAdd = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        ASSERT_FALSE(column.canPlayCardOnTop(cardToAdd));
        delete card1;
        delete cardToAdd;
    }

    TEST(ColumnTest, CannotPlayCardSameColor)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        std::vector<const solitaire::Card *> hiddenCards;
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        solitaire::Card *cardToAdd = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N2);
        ASSERT_FALSE(column.canPlayCardOnTop(cardToAdd));
        delete card1;
        delete cardToAdd;
    }

    TEST(ColumnTest, CannotPlayCardNotConsecutive)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        std::vector<const solitaire::Card *> hiddenCards;
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        solitaire::Card *cardToAdd = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N3);
        ASSERT_FALSE(column.canPlayCardOnTop(cardToAdd));
        delete card1;
        delete cardToAdd;
    }

    TEST(ColumnTest, CannotPlayCardNotConsecutive2)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J);
        std::vector<const solitaire::Card *> hiddenCards;
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        solitaire::Card *cardToAdd = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::Q);
        ASSERT_FALSE(column.canPlayCardOnTop(cardToAdd));
        delete card1;
        delete cardToAdd;
    }

    TEST(ColumnTest, Add2CardsToColumn)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J);
        solitaire::Card *cardToAdd1 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::Q);
        solitaire::Card *cardToAdd2 = new solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::K);
        std::vector<const solitaire::Card *> hiddenCards;
        std::vector<const solitaire::Card *> cardsToAdd = {cardToAdd1, cardToAdd2};
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        column.addCardsToColumn(cardsToAdd);
        std::optional<const solitaire::Card *> topCardOpt = column.getTopCard();
        ASSERT_NE(topCardOpt, std::nullopt);
        const solitaire::Card *topCard = topCardOpt.value();
        ASSERT_EQ(*topCard, *cardToAdd2);
        column.removeTopCard();
        topCardOpt = column.getTopCard();
        ASSERT_NE(topCardOpt, std::nullopt);
        topCard = topCardOpt.value();
        ASSERT_EQ(*topCard, *cardToAdd1);
        delete card1;
        delete cardToAdd1;
        delete cardToAdd2;
    }

    TEST(ColumnTest, GetTop2Cards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        solitaire::Card *card4 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N2);
        std::vector<const solitaire::Card *> hiddenCards = {card2, card3};
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2);
        column.addCardToTop(card4);
        std::vector<const solitaire::Card *> top2Cards = column.getTopNCards(2);
        ASSERT_EQ(*top2Cards[0], *card1);
        ASSERT_EQ(*top2Cards[1], *card4);
        delete card1;
        delete card2;
        delete card3;
        delete card4;
    }

    TEST(ColumnTest, FailGetTop0Cards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        solitaire::Card *card4 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N2);
        std::vector<const solitaire::Card *> hiddenCards = {card2, card3};
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2);

        EXPECT_THROW(column.getTopNCards(0), std::invalid_argument);

        delete card1;
        delete card2;
        delete card3;
        delete card4;
    }

    TEST(ColumnTest, FailGetTop2Cards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        std::vector<const solitaire::Card *> hiddenCards = {card2, card3};
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2);

        EXPECT_THROW(column.getTopNCards(2), std::domain_error);

        delete card1;
        delete card2;
        delete card3;
    }

    TEST(ColumnTest, RemoveTop2Cards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card4 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N2);
        std::vector<const solitaire::Card *> hiddenCards;
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        column.addCardToTop(card4);
        std::vector<const solitaire::Card *> top2Cards = column.removeTopNCards(2);
        ASSERT_EQ(*top2Cards[0], *card1);
        ASSERT_EQ(*top2Cards[1], *card4);
        ASSERT_TRUE(column.isEmpty());
        delete card1;
        delete card4;
    }

    TEST(ColumnTest, RemoveTop2CardsColumn1With1Hidden)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card4 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N2);
        std::vector<const solitaire::Card *> hiddenCards = {card2};
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column1);
        column.addCardToTop(card4);
        std::vector<const solitaire::Card *> top2Cards = column.removeTopNCards(2);
        ASSERT_EQ(*top2Cards[0], *card1);
        ASSERT_EQ(*top2Cards[1], *card4);
        ASSERT_FALSE(column.isEmpty());
        delete card1;
        delete card4;
    }

    TEST(ColumnTest, FailRemoveTop0Cards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        solitaire::Card *card4 = new solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N2);
        std::vector<const solitaire::Card *> hiddenCards = {card2, card3};
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2);

        EXPECT_THROW(column.removeTopNCards(0), std::invalid_argument);

        delete card1;
        delete card2;
        delete card3;
        delete card4;
    }

    TEST(ColumnTest, FailRemoveTop2Cards)
    {
        solitaire::Card *card1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *card2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *card3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        std::vector<const solitaire::Card *> hiddenCards = {card2, card3};
        solitaire::Column column(card1, hiddenCards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2);

        EXPECT_THROW(column.removeTopNCards(2), std::domain_error);

        delete card1;
        delete card2;
        delete card3;
    }
}