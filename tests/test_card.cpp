
#include "gtest/gtest.h"
#include "solitaire/card.hpp"
#include <stdexcept>

namespace
{
    TEST(CardTest, BuildInvalidSuitCard)
    {
        EXPECT_THROW(solitaire::Card((solitaire::Card::Suit)7, solitaire::Card::Rank::N9), std::invalid_argument);
    }

    TEST(CardTest, BuildInvalidRankCard)
    {
        EXPECT_THROW(solitaire::Card(solitaire::Card::Suit::Clubs, (solitaire::Card::Rank)20), std::invalid_argument);
    }

    TEST(CardTest, GetSuit)
    {
        solitaire::Card cardClubs(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9);
        solitaire::Card cardHearts(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N9);
        solitaire::Card cardDiamonds(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N9);
        solitaire::Card cardSpades(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N9);
        ASSERT_EQ(cardClubs.getSuit(), solitaire::Card::Suit::Clubs);
        ASSERT_EQ(cardHearts.getSuit(), solitaire::Card::Suit::Hearts);
        ASSERT_EQ(cardDiamonds.getSuit(), solitaire::Card::Suit::Diamonds);
        ASSERT_EQ(cardSpades.getSuit(), solitaire::Card::Suit::Spades);
    }

    TEST(CardTest, GetRank)
    {
        solitaire::Card cardA(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        solitaire::Card card2(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        solitaire::Card card3(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3);
        solitaire::Card card4(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
        solitaire::Card card5(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5);
        solitaire::Card card6(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6);
        solitaire::Card card7(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N7);
        solitaire::Card card8(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N8);
        solitaire::Card card9(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9);
        solitaire::Card card10(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N10);
        solitaire::Card cardJ(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J);
        solitaire::Card cardQ(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::Q);
        solitaire::Card cardK(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::K);
        ASSERT_EQ(cardA.getRank(), solitaire::Card::Rank::A);
        ASSERT_EQ(card2.getRank(), solitaire::Card::Rank::N2);
        ASSERT_EQ(card3.getRank(), solitaire::Card::Rank::N3);
        ASSERT_EQ(card4.getRank(), solitaire::Card::Rank::N4);
        ASSERT_EQ(card5.getRank(), solitaire::Card::Rank::N5);
        ASSERT_EQ(card6.getRank(), solitaire::Card::Rank::N6);
        ASSERT_EQ(card7.getRank(), solitaire::Card::Rank::N7);
        ASSERT_EQ(card8.getRank(), solitaire::Card::Rank::N8);
        ASSERT_EQ(card9.getRank(), solitaire::Card::Rank::N9);
        ASSERT_EQ(card10.getRank(), solitaire::Card::Rank::N10);
        ASSERT_EQ(cardJ.getRank(), solitaire::Card::Rank::J);
        ASSERT_EQ(cardQ.getRank(), solitaire::Card::Rank::Q);
        ASSERT_EQ(cardK.getRank(), solitaire::Card::Rank::K);
    }

    TEST(CardTest, IsLowerThanSameSuit)
    {
        solitaire::Card card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5);
        ASSERT_TRUE(card < solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6));
        ASSERT_TRUE(card < solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N10));
        ASSERT_TRUE(card < solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J));
        ASSERT_FALSE(card < solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A));
        ASSERT_FALSE(card < solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3));
    }

    TEST(CardTest, IsLowerThanDifferentSuit)
    {
        solitaire::Card card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6);
        ASSERT_TRUE(card < solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N7));
        ASSERT_TRUE(card < solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N9));
        ASSERT_TRUE(card < solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::K));
        ASSERT_FALSE(card < solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N2));
        ASSERT_FALSE(card < solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N4));
    }

    TEST(CardTest, IsEqualSameSuit)
    {
        solitaire::Card card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N8);
        ASSERT_TRUE(card == solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N8));
        ASSERT_FALSE(card == solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::Q));
    }

    TEST(CardTest, IsEqualDifferentSuit)
    {
        solitaire::Card card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5);
        ASSERT_TRUE(card == solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N5));
        ASSERT_TRUE(card == solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N5));
        ASSERT_TRUE(card == solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N5));
        ASSERT_FALSE(card == solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::Q));
        ASSERT_FALSE(card == solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::Q));
        ASSERT_FALSE(card == solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::Q));
    }

    TEST(CardTest, IsHigherThanSameSuit)
    {
        solitaire::Card card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4);
        ASSERT_TRUE(card > solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A));
        ASSERT_TRUE(card > solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3));
        ASSERT_FALSE(card > solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6));
        ASSERT_FALSE(card > solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N10));
        ASSERT_FALSE(card > solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J));
    }

    TEST(CardTest, IsHigherThanDifferentSuit)
    {
        solitaire::Card card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N8);
        ASSERT_TRUE(card > solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N2));
        ASSERT_TRUE(card > solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N4));
        ASSERT_FALSE(card > solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::Q));
        ASSERT_FALSE(card > solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N9));
        ASSERT_FALSE(card > solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::K));
    }

    TEST(CardTest, IsDifferentSameSuit)
    {
        solitaire::Card card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N4));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N5));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N7));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N8));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N10));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::Q));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::K));
        ASSERT_FALSE(card != solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A));
    }

    TEST(CardTest, IsDifferentDifferentSuit)
    {
        solitaire::Card card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A);

        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N2));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N3));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N4));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N5));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N6));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N7));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N8));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N9));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N10));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::J));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::Q));
        ASSERT_TRUE(card != solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::K));
        ASSERT_FALSE(card != solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::A));
    }

    TEST(CardTest, IsLowerOrEqualThanSameSuit)
    {
        solitaire::Card card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6);
        ASSERT_TRUE(card <= solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N6));
        ASSERT_TRUE(card <= solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N10));
        ASSERT_TRUE(card <= solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J));
        ASSERT_FALSE(card <= solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::A));
        ASSERT_FALSE(card <= solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3));
    }

    TEST(CardTest, IsLowerThanOrEqualDifferentSuit)
    {
        solitaire::Card card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N2);
        ASSERT_TRUE(card <= solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N7));
        ASSERT_TRUE(card <= solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N9));
        ASSERT_TRUE(card <= solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N2));
        ASSERT_FALSE(card <= solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::A));
    }

    TEST(CardTest, IsHigherOrEqualThanSameSuit)
    {
        solitaire::Card card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N7);
        ASSERT_TRUE(card >= solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N7));
        ASSERT_TRUE(card >= solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N3));
        ASSERT_FALSE(card >= solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N8));
        ASSERT_FALSE(card >= solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N10));
        ASSERT_FALSE(card >= solitaire::Card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J));
    }

    TEST(CardTest, IsHigherOrEqualThanDifferentSuit)
    {
        solitaire::Card card(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9);
        ASSERT_TRUE(card >= solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N2));
        ASSERT_TRUE(card >= solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N9));
        ASSERT_FALSE(card >= solitaire::Card(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::Q));
        ASSERT_FALSE(card >= solitaire::Card(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N10));
        ASSERT_FALSE(card >= solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::K));
    }

    TEST(CardTest, IsSameSuit)
    {
        solitaire::Card cardClubs(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9);
        solitaire::Card cardHearts(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N9);
        solitaire::Card cardDiamonds(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N9);
        solitaire::Card cardSpades(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N9);

        solitaire::Card cardClubs2(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N8);
        solitaire::Card cardHearts2(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N8);
        solitaire::Card cardDiamonds2(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N8);
        solitaire::Card cardSpades2(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N8);
        // Test for clubs
        ASSERT_TRUE(cardClubs.isSameSuit(&cardClubs2));
        ASSERT_FALSE(cardClubs.isSameSuit(&cardHearts));
        ASSERT_FALSE(cardClubs.isSameSuit(&cardDiamonds));
        ASSERT_FALSE(cardClubs.isSameSuit(&cardSpades));
        // Test for spades
        ASSERT_TRUE(cardSpades.isSameSuit(&cardSpades2));
        ASSERT_FALSE(cardSpades.isSameSuit(&cardHearts));
        ASSERT_FALSE(cardSpades.isSameSuit(&cardDiamonds));
        ASSERT_FALSE(cardSpades.isSameSuit(&cardClubs));
        // Test for diamonds
        ASSERT_TRUE(cardDiamonds.isSameSuit(&cardDiamonds2));
        ASSERT_FALSE(cardDiamonds.isSameSuit(&cardHearts));
        ASSERT_FALSE(cardDiamonds.isSameSuit(&cardSpades));
        ASSERT_FALSE(cardDiamonds.isSameSuit(&cardClubs));
        // Test for hearts
        ASSERT_TRUE(cardHearts.isSameSuit(&cardHearts2));
        ASSERT_FALSE(cardHearts.isSameSuit(&cardDiamonds));
        ASSERT_FALSE(cardHearts.isSameSuit(&cardSpades));
        ASSERT_FALSE(cardHearts.isSameSuit(&cardClubs));
    }

    TEST(CardTest, IsOppositeSuit)
    {
        solitaire::Card cardClubs(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9);
        solitaire::Card cardHearts(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N9);
        solitaire::Card cardDiamonds(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N9);
        solitaire::Card cardSpades(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N9);

        solitaire::Card cardClubs2(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N8);
        solitaire::Card cardHearts2(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N8);
        solitaire::Card cardDiamonds2(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::N8);
        solitaire::Card cardSpades2(solitaire::Card::Suit::Spades, solitaire::Card::Rank::N8);
        // Test for clubs
        ASSERT_FALSE(cardClubs.isOppositeColor(&cardClubs2));
        ASSERT_TRUE(cardClubs.isOppositeColor(&cardHearts));
        ASSERT_TRUE(cardClubs.isOppositeColor(&cardDiamonds));
        ASSERT_FALSE(cardClubs.isOppositeColor(&cardSpades));
        // Test for spades
        ASSERT_FALSE(cardSpades.isOppositeColor(&cardSpades2));
        ASSERT_TRUE(cardSpades.isOppositeColor(&cardHearts));
        ASSERT_TRUE(cardSpades.isOppositeColor(&cardDiamonds));
        ASSERT_FALSE(cardSpades.isOppositeColor(&cardClubs));
        // Test for diamonds
        ASSERT_FALSE(cardDiamonds.isOppositeColor(&cardDiamonds2));
        ASSERT_FALSE(cardDiamonds.isOppositeColor(&cardHearts));
        ASSERT_TRUE(cardDiamonds.isOppositeColor(&cardSpades));
        ASSERT_TRUE(cardDiamonds.isOppositeColor(&cardClubs));
        // Test for hearts
        ASSERT_FALSE(cardHearts.isOppositeColor(&cardHearts2));
        ASSERT_FALSE(cardHearts.isOppositeColor(&cardDiamonds));
        ASSERT_TRUE(cardHearts.isOppositeColor(&cardSpades));
        ASSERT_TRUE(cardHearts.isOppositeColor(&cardClubs));
    }

    TEST(CardTest, PrecedesAndIsContiguousToSameSuit)
    {
        solitaire::Card card9(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9);
        solitaire::Card card10(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N10);
        ASSERT_TRUE(card9.precedesAndContiguousTo(&card10));
    }

    TEST(CardTest, PrecedesAndIsContiguousToDifferentSuit)
    {
        solitaire::Card card9(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9);
        solitaire::Card card10(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::N10);
        ASSERT_TRUE(card9.precedesAndContiguousTo(&card10));
    }

    TEST(CardTest, DoesNotPrecedeAndIsNotContiguousTo)
    {
        solitaire::Card card9(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9);
        solitaire::Card cardJ(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::J);
        ASSERT_FALSE(card9.precedesAndContiguousTo(&cardJ));
    }

    TEST(CardTest, DoesNotPrecedeAndIsContiguousTo)
    {
        solitaire::Card card9(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9);
        solitaire::Card card7(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N7);
        ASSERT_FALSE(card9.precedesAndContiguousTo(&card7));
    }

    TEST(CardTest, GetCardCode)
    {
        solitaire::Card cardClubs(solitaire::Card::Suit::Clubs, solitaire::Card::Rank::N9);
        solitaire::Card cardHearts(solitaire::Card::Suit::Hearts, solitaire::Card::Rank::A);
        solitaire::Card cardDiamonds(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::J);
        solitaire::Card cardSpades(solitaire::Card::Suit::Spades, solitaire::Card::Rank::K);

        ASSERT_EQ(cardClubs.cardCode(), "clubs_9");
        ASSERT_EQ(cardHearts.cardCode(), "hearts_A");
        ASSERT_EQ(cardDiamonds.cardCode(), "diamonds_J");
        ASSERT_EQ(cardSpades.cardCode(), "spades_K");
    }
}