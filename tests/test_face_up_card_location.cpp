#include "gtest/gtest.h"
#include "solitaire/face_up_card_location.hpp"
#include <stdexcept>

namespace
{
    class FaceUpCardLocationImpl : public solitaire::FaceUpCardLocation
    {
    public:
        FaceUpCardLocationImpl(std::vector<const solitaire::Card *> cards, solitaire::FaceUpCardLocation::FaceUpCardLocationCode locationCode)
            : FaceUpCardLocation(cards, locationCode)
        {
        }
        bool canPlayCardOnTop(const solitaire::Card *card) const
        {
            return true;
        }
    };

    TEST(TestFaceUpCardLocation, CreateLocationInvalidLocationCode)
    {
        EXPECT_THROW(FaceUpCardLocationImpl(std::vector<const solitaire::Card *>(), (solitaire::FaceUpCardLocation::FaceUpCardLocationCode)25), std::invalid_argument);
    }

    TEST(TestFaceUpCardLocation, GetTopCard)
    {
        solitaire::Card *card = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::K);
        std::vector<const solitaire::Card *> cards = {card};
        FaceUpCardLocationImpl location(cards,
                                        solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        std::optional<const solitaire::Card *> topCardOpt = location.getTopCard();
        ASSERT_NE(topCardOpt, std::nullopt);
        const solitaire::Card *topCard = topCardOpt.value();
        ASSERT_EQ(*topCard, *card);
        delete card;
    }

    TEST(TestFaceUpCardLocation, GetTopCardEmptyLocation)
    {
        FaceUpCardLocationImpl location(std::vector<const solitaire::Card *>(),
                                        solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        ASSERT_EQ(location.getTopCard(), std::nullopt);
    }

    TEST(TestFaceUpCardLocation, AddCardToTop)
    {
        FaceUpCardLocationImpl location(std::vector<const solitaire::Card *>(),
                                        solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        ASSERT_EQ(location.getTopCard(), std::nullopt);
        solitaire::Card *newCard = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::K);
        location.addCardToTop(newCard);
        ASSERT_NE(location.getTopCard(), std::nullopt);
        const solitaire::Card *topCard = location.getTopCard().value();
        ASSERT_EQ(*topCard, *newCard);
        delete newCard;
    }

    TEST(TestFaceUpCardLocation, GetNumberOfCardsEmpty)
    {
        FaceUpCardLocationImpl location(std::vector<const solitaire::Card *>(),
                                        solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        ASSERT_EQ(location.getTopCard(), std::nullopt);
    }

    TEST(TestFaceUpCardLocation, GetNumberOfCardsNotEmpty)
    {
        FaceUpCardLocationImpl location(std::vector<const solitaire::Card *>(),
                                        solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        solitaire::Card newCard(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::K);
        location.addCardToTop(&newCard);
        ASSERT_EQ(location.getNumberOfCards(), 1);
    }

    TEST(TestFaceUpCardLocation, RemoveTopCard)
    {
        solitaire::Card *card = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::K);
        std::vector<const solitaire::Card *> cards = {card};
        FaceUpCardLocationImpl location(cards,
                                        solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        ASSERT_NE(location.getTopCard(), std::nullopt);
        const solitaire::Card *topCard = location.getTopCard().value();
        ASSERT_EQ(*topCard, *card);
        const solitaire::Card *removedCard = location.removeTopCard();
        ASSERT_EQ(*removedCard, *card);
        ASSERT_EQ(location.getTopCard(), std::nullopt);
        delete card;
    }

    TEST(TestFaceUpCardLocation, RemoveTopCardEmptyLocation)
    {
        FaceUpCardLocationImpl location(std::vector<const solitaire::Card *>(),
                                        solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        EXPECT_THROW(location.removeTopCard(), std::underflow_error);
    }

    TEST(TestFaceUpCardLocation, LocationIsEmpty)
    {
        FaceUpCardLocationImpl location(std::vector<const solitaire::Card *>(),
                                        solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        ASSERT_TRUE(location.isEmpty());
    }

    TEST(TestFaceUpCardLocation, LocationIsNotEmpty)
    {
        solitaire::Card *card = new solitaire::Card(solitaire::Card::Suit::Diamonds, solitaire::Card::Rank::K);
        std::vector<const solitaire::Card *> cards = {card};
        FaceUpCardLocationImpl location(cards,
                                        solitaire::FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        ASSERT_FALSE(location.isEmpty());
        delete card;
    }
}