#include "gtest/gtest.h"
#include "solitaire/foundation.hpp"
#include "solitaire/face_up_card_location.hpp"
#include "solitaire/card.hpp"
#include <stdexcept>

namespace
{
    TEST(FoundationTest, CreateInvalidFoundation)
    {
        EXPECT_THROW(solitaire::Foundation{solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0},
                     std::invalid_argument);
        EXPECT_THROW(solitaire::Foundation{solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column1},
                     std::invalid_argument);
        EXPECT_THROW(solitaire::Foundation{solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column2},
                     std::invalid_argument);
        EXPECT_THROW(solitaire::Foundation{solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column3},
                     std::invalid_argument);
        EXPECT_THROW(solitaire::Foundation{solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column4},
                     std::invalid_argument);
        EXPECT_THROW(solitaire::Foundation{solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column5},
                     std::invalid_argument);
        EXPECT_THROW(solitaire::Foundation{solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column6},
                     std::invalid_argument);
        EXPECT_THROW(solitaire::Foundation{solitaire::FaceUpCardLocation::FaceUpCardLocationCode::WastePile},
                     std::invalid_argument);
    }

    TEST(FoundationTest, CanAddAceCardEmpty)
    {
        solitaire::Card *card = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Foundation foundation(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0);
        ASSERT_TRUE(foundation.canPlayCardOnTop(card));
        delete card;
    }

    TEST(FoundationTest, CanAddCardSameSuitHigher)
    {
        solitaire::Card *card = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *cardToAdd = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Foundation foundation(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0);
        ASSERT_TRUE(foundation.canPlayCardOnTop(card));
        foundation.addCardToTop(card);
        ASSERT_TRUE(foundation.canPlayCardOnTop(cardToAdd));
        delete card;
        delete cardToAdd;
    }

    TEST(FoundationTest, CannnotAddNonAceCardEmpty)
    {
        solitaire::Card *card = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::K);
        solitaire::Foundation foundation(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0);
        ASSERT_FALSE(foundation.canPlayCardOnTop(card));
        delete card;
    }

    TEST(FoundationTest, CannnotAddCardDifferentSuitContiguous)
    {
        solitaire::Card *card = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *cardToAdd = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N2);
        solitaire::Foundation foundation(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0);
        ASSERT_TRUE(foundation.canPlayCardOnTop(card));
        foundation.addCardToTop(card);
        ASSERT_FALSE(foundation.canPlayCardOnTop(cardToAdd));
        delete card;
        delete cardToAdd;
    }

    TEST(FoundationTest, CannnotAddCardLowerValue)
    {
        solitaire::Card *card = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *cardToAdd = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Foundation foundation(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0);
        ASSERT_TRUE(foundation.canPlayCardOnTop(card));
        foundation.addCardToTop(card);
        ASSERT_TRUE(foundation.canPlayCardOnTop(cardToAdd));
        foundation.addCardToTop(cardToAdd);
        ASSERT_FALSE(foundation.canPlayCardOnTop(card));
        delete card;
        delete cardToAdd;
    }

    TEST(FoundationTest, CannotAddCardSameSuitHigherThanOne)
    {
        solitaire::Card *card = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *cardToAdd = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N3);
        solitaire::Foundation foundation(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0);
        ASSERT_TRUE(foundation.canPlayCardOnTop(card));
        foundation.addCardToTop(card);
        ASSERT_FALSE(foundation.canPlayCardOnTop(cardToAdd));
        delete card;
        delete cardToAdd;
    }

    TEST(FoundationTest, IsComplete)
    {
        solitaire::Card *card = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card *cardToAdd1 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card *cardToAdd2 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        solitaire::Card *cardToAdd3 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
        solitaire::Card *cardToAdd4 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5);
        solitaire::Card *cardToAdd5 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6);
        solitaire::Card *cardToAdd6 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N7);
        solitaire::Card *cardToAdd7 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N8);
        solitaire::Card *cardToAdd8 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9);
        solitaire::Card *cardToAdd9 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N10);
        solitaire::Card *cardToAdd10 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J);
        solitaire::Card *cardToAdd11 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::Q);
        solitaire::Card *cardToAdd12 = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::K);
        solitaire::Foundation foundation(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0);
        ASSERT_TRUE(foundation.canPlayCardOnTop(card));
        foundation.addCardToTop(card);
        ASSERT_TRUE(foundation.canPlayCardOnTop(cardToAdd1));
        foundation.addCardToTop(cardToAdd1);
        ASSERT_TRUE(foundation.canPlayCardOnTop(cardToAdd2));
        foundation.addCardToTop(cardToAdd2);
        ASSERT_TRUE(foundation.canPlayCardOnTop(cardToAdd3));
        foundation.addCardToTop(cardToAdd3);
        ASSERT_TRUE(foundation.canPlayCardOnTop(cardToAdd4));
        foundation.addCardToTop(cardToAdd4);
        ASSERT_TRUE(foundation.canPlayCardOnTop(cardToAdd5));
        foundation.addCardToTop(cardToAdd5);
        ASSERT_TRUE(foundation.canPlayCardOnTop(cardToAdd6));
        foundation.addCardToTop(cardToAdd6);
        ASSERT_TRUE(foundation.canPlayCardOnTop(cardToAdd7));
        foundation.addCardToTop(cardToAdd7);
        ASSERT_TRUE(foundation.canPlayCardOnTop(cardToAdd8));
        foundation.addCardToTop(cardToAdd8);
        ASSERT_TRUE(foundation.canPlayCardOnTop(cardToAdd9));
        foundation.addCardToTop(cardToAdd9);
        ASSERT_TRUE(foundation.canPlayCardOnTop(cardToAdd10));
        foundation.addCardToTop(cardToAdd10);
        ASSERT_TRUE(foundation.canPlayCardOnTop(cardToAdd11));
        foundation.addCardToTop(cardToAdd11);
        ASSERT_TRUE(foundation.canPlayCardOnTop(cardToAdd12));
        foundation.addCardToTop(cardToAdd12);
        ASSERT_TRUE(foundation.isComplete());
        delete card;
        delete cardToAdd1;
        delete cardToAdd2;
        delete cardToAdd3;
        delete cardToAdd4;
        delete cardToAdd5;
        delete cardToAdd6;
        delete cardToAdd7;
        delete cardToAdd8;
        delete cardToAdd9;
        delete cardToAdd10;
        delete cardToAdd11;
        delete cardToAdd12;
    }

    TEST(FoundationTest, IsNotComplete)
    {
        solitaire::Card *card = new solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Foundation foundation(solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Foundation0);
        foundation.addCardToTop(card);
        ASSERT_FALSE(foundation.isComplete());
        delete card;
    }
}