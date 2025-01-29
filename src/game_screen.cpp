// SPDX-License-Identifier:    MIT
/*
 * GameScreen class implementation
 *
 * Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 */

#include "solitaire/game_screen.hpp"
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <cstring>
#include <optional>

#define SCREEN_TITLE "Camila's X11 Solitaire"
#define ICON_NAME "SOLITAIRE"
#define SCREEN_WIDTH 1060
#define SCREEN_HEIGHT 850
#define CARD_HEIGHT 180
#define CARD_WIDTH 130
// Estimated char dimensions
#define CHAR_WIDTH 5
#define CHAR_HEIGHT 3
#define NUMBER_LOCATION_TOP 20
#define NUMBER_LOCATION_RIGHT 10
#define SEPARATION 20
#define STOCKPILE_X 10
#define STOCKPILE_Y 100
#define WASTEPILE_X (STOCKPILE_X + CARD_WIDTH + SEPARATION)
#define WASTEPILE_Y STOCKPILE_Y
#define FOUNDATION_X (WASTEPILE_X + 2 * CARD_WIDTH + 2 * SEPARATION)
#define FOUNDATION_Y STOCKPILE_Y
#define COLUMNS_X STOCKPILE_X
#define COLUMNS_Y (STOCKPILE_Y + 2 * SEPARATION + CARD_HEIGHT)
#define RESTART_BUTTON_WIDTH 200
#define RESTART_BUTTON_HEIGHT 50
#define RESTART_X (SCREEN_WIDTH - RESTART_BUTTON_WIDTH - 2 * NUMBER_LOCATION_RIGHT)
#define RESTART_Y 20
#define HIDDEN_CARD_HEIGHT 25
#define CLICK_TEXT_X STOCKPILE_X
#define CLICK_TEXT_Y RESTART_Y
#define GAME_END_WIDTH (SCREEN_WIDTH / 2)
#define GAME_END_HEIGHT (SCREEN_HEIGHT / 3)
#define GAME_END_X ((SCREEN_WIDTH - GAME_END_WIDTH) / 2)
#define GAME_END_Y ((SCREEN_HEIGHT - GAME_END_HEIGHT) / 2)

namespace solitaire
{
    // Init
    void GameScreen::init()
    {
        mRed = 255 << 16;
        mDisplay = XOpenDisplay((char *)0);
        mScreenNumber = DefaultScreen(mDisplay);
        mBlack = BlackPixel(mDisplay, mScreenNumber);
        mWhite = WhitePixel(mDisplay, mScreenNumber);
        // Create the window
        mWindow = XCreateSimpleWindow(mDisplay, DefaultRootWindow(mDisplay), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 5, mBlack, mWhite);
        XSetStandardProperties(mDisplay, mWindow, SCREEN_TITLE, ICON_NAME, None, NULL, 0, NULL);
        XSelectInput(mDisplay, mWindow, ExposureMask | ButtonPressMask);
        // Map the window to the display
        XMapWindow(mDisplay, mWindow);
        // Create the context, which will allow to customize colors and other preoperties
        mContext = XCreateGC(mDisplay, mWindow, 0, 0);
        XSetBackground(mDisplay, mContext, mWhite);
        XSetForeground(mDisplay, mContext, mBlack);
        // Clear window
        XClearWindow(mDisplay, mWindow);
        // Move window to the top
        XMapRaised(mDisplay, mWindow);
        mFromLocationClick.clicked = false;
        mFoundations.resize(NUMBER_FOUNDATIONS);
        mColumns.resize(NUMBER_COLUMNS);
        setSolitaire();
    }
    void GameScreen::setSolitaire()
    {
        mDeck->shuffle();
        mWastePile = new WastePile();
        buildColumns();
        buildFoundations();
        std::vector<const Card *> stockPileCards = mDeck->extractNCards(STOCKPILE_SIZE);
        mStockPile = new StockPile(stockPileCards);
        mGame = new Solitaire(mWastePile, mStockPile, mFoundations, mColumns);
        mGameStatus = Solitaire::GameStatus::Playing;
    }
    void GameScreen::buildColumns()
    {
        std::vector<const Card *> topCard, hiddenCards;
        // Column 0
        topCard = mDeck->extractNCards(1);
        mColumns[0] = new Column(topCard[0], hiddenCards, FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        // Column 1
        topCard = mDeck->extractNCards(1);
        hiddenCards = mDeck->extractNCards(HIDDEN_CARDS_COLUMN1);
        mColumns[1] = new Column(topCard[0], hiddenCards, FaceUpCardLocation::FaceUpCardLocationCode::Column1);
        // Column 2
        topCard = mDeck->extractNCards(1);
        hiddenCards = mDeck->extractNCards(HIDDEN_CARDS_COLUMN2);
        mColumns[2] = new Column(topCard[0], hiddenCards, FaceUpCardLocation::FaceUpCardLocationCode::Column2);
        // Column 3
        topCard = mDeck->extractNCards(1);
        hiddenCards = mDeck->extractNCards(HIDDEN_CARDS_COLUMN3);
        mColumns[3] = new Column(topCard[0], hiddenCards, FaceUpCardLocation::FaceUpCardLocationCode::Column3);
        // Column 4
        topCard = mDeck->extractNCards(1);
        hiddenCards = mDeck->extractNCards(HIDDEN_CARDS_COLUMN4);
        mColumns[4] = new Column(topCard[0], hiddenCards, FaceUpCardLocation::FaceUpCardLocationCode::Column4);
        // Column 5
        topCard = mDeck->extractNCards(1);
        hiddenCards = mDeck->extractNCards(HIDDEN_CARDS_COLUMN5);
        mColumns[5] = new Column(topCard[0], hiddenCards, FaceUpCardLocation::FaceUpCardLocationCode::Column5);
        // Column 6
        topCard = mDeck->extractNCards(1);
        hiddenCards = mDeck->extractNCards(HIDDEN_CARDS_COLUMN6);
        mColumns[6] = new Column(topCard[0], hiddenCards, FaceUpCardLocation::FaceUpCardLocationCode::Column6);
    }
    void GameScreen::buildFoundations()
    {
        mFoundations[0] = new Foundation(FaceUpCardLocation::FaceUpCardLocationCode::Foundation0);
        mFoundations[1] = new Foundation(FaceUpCardLocation::FaceUpCardLocationCode::Foundation1);
        mFoundations[2] = new Foundation(FaceUpCardLocation::FaceUpCardLocationCode::Foundation2);
        mFoundations[3] = new Foundation(FaceUpCardLocation::FaceUpCardLocationCode::Foundation3);
    }
    // Play game
    void GameScreen::startGameScreen()
    {
        XEvent ev;
        init();
        while (XNextEvent(mDisplay, &ev) == 0)
        {
            if (ev.type == ButtonPress)
            {
                int x = ev.xbutton.x, y = ev.xbutton.y;
                handlePlayerClick(x, y);
            }
            XClearWindow(mDisplay, mWindow);
            drawCurrentCardInPlay();
            drawTableau();
            drawRestartButton();
            drawGameEnd();
        }
        XUnmapWindow(mDisplay, mWindow);
        XDestroyWindow(mDisplay, mWindow);
    }
    void GameScreen::drawTableau()
    {
        drawStockPile();
        drawSimpleCardLocation(FaceUpCardLocation::FaceUpCardLocationCode::WastePile, WASTEPILE_X, WASTEPILE_Y);
        drawFoundations();
        drawColumns();
    }
    // Draw screen
    void GameScreen::drawCard(const Card *card, unsigned int topLeftX, unsigned int topLeftY)
    {
        char const *cardNumberText, *cardSuitText;
        XTextItem textItem;
        textItem.delta = 2;
        textItem.font = None;
        // Draw the filled rectangle rectangle
        XSetForeground(mDisplay, mContext, mWhite);
        XFillRectangle(mDisplay, mWindow, mContext, topLeftX, topLeftY, CARD_WIDTH, CARD_HEIGHT);
        // Only Hearts and Diamonds use red font
        switch (card->getSuit())
        {
        case Card::Suit::Hearts:
            XSetForeground(mDisplay, mContext, mRed);
            cardSuitText = "Hearts";
            break;
        case Card::Suit::Diamonds:
            XSetForeground(mDisplay, mContext, mRed);
            cardSuitText = "Diamonds";
            break;
        case Card::Suit::Clubs:
            XSetForeground(mDisplay, mContext, mBlack);
            cardSuitText = "Clubs";
            break;
        case Card::Suit::Spades:
            XSetForeground(mDisplay, mContext, mBlack);
            cardSuitText = "Spades";
            break;
        }
        switch (card->getRank())
        {
        case Card::Rank::A:
            cardNumberText = "A";
            break;
        case Card::Rank::N2:
            cardNumberText = "2";
            break;
        case Card::Rank::N3:
            cardNumberText = "3";
            break;
        case Card::Rank::N4:
            cardNumberText = "4";
            break;
        case Card::Rank::N5:
            cardNumberText = "5";
            break;
        case Card::Rank::N6:
            cardNumberText = "6";
            break;
        case Card::Rank::N7:
            cardNumberText = "7";
            break;
        case Card::Rank::N8:
            cardNumberText = "8";
            break;
        case Card::Rank::N9:
            cardNumberText = "9";
            break;
        case Card::Rank::N10:
            cardNumberText = "10";
            break;
        case Card::Rank::J:
            cardNumberText = "J";
            break;
        case Card::Rank::Q:
            cardNumberText = "Q";
            break;
        case Card::Rank::K:
            cardNumberText = "K";
            break;
        }

        // Draw the numbers of the card
        textItem.chars = (char *)cardNumberText;
        textItem.nchars = strlen(cardNumberText);
        XDrawText(mDisplay, mWindow, mContext, topLeftX + NUMBER_LOCATION_RIGHT, topLeftY + NUMBER_LOCATION_TOP, &textItem, 1);
        int bottomNumberX = topLeftX + CARD_WIDTH - 2 * NUMBER_LOCATION_RIGHT - strlen(cardNumberText) * CHAR_WIDTH;
        int bottomNumberY = topLeftY + CARD_HEIGHT - NUMBER_LOCATION_TOP + CHAR_WIDTH;
        XDrawText(mDisplay, mWindow, mContext, bottomNumberX, bottomNumberY, &textItem, 1);
        // Draw the suit
        textItem.chars = (char *)cardSuitText;
        textItem.nchars = strlen(cardSuitText);
        int suitX = topLeftX + (CARD_WIDTH - strlen(cardSuitText) * CHAR_WIDTH) / 2;
        int suitY = topLeftY + CARD_HEIGHT / 2 - CHAR_WIDTH;
        XDrawText(mDisplay, mWindow, mContext, suitX, suitY, &textItem, 1);
        // Draw the border of the card
        XDrawRectangle(mDisplay, mWindow, mContext, topLeftX, topLeftY, CARD_WIDTH, CARD_HEIGHT);
        // Reset the foreground color (it might still be red)
        XSetForeground(mDisplay, mContext, mBlack);
    }
    void GameScreen::drawStockPile()
    {
        if (mGame->isStockPileEmpty())
        {
            drawEmptyCardSpot(STOCKPILE_X, STOCKPILE_Y);
        }
        else
        {
            XFillRectangle(mDisplay, mWindow, mContext, STOCKPILE_X, STOCKPILE_Y, CARD_WIDTH, CARD_HEIGHT);
        }
    }
    void GameScreen::drawSimpleCardLocation(FaceUpCardLocation::FaceUpCardLocationCode location, unsigned int topLeftX, unsigned int topLeftY)
    {
        std::optional<const Card *> topCard = mGame->getTopCard(location);
        if (topCard.has_value())
        {
            drawCard(topCard.value(), topLeftX, topLeftY);
        }
        else
        {
            drawEmptyCardSpot(topLeftX, topLeftY);
        }
    }
    void GameScreen::drawFoundations()
    {
        drawSimpleCardLocation(FaceUpCardLocation::FaceUpCardLocationCode::Foundation0, FOUNDATION_X, FOUNDATION_Y);
        drawSimpleCardLocation(FaceUpCardLocation::FaceUpCardLocationCode::Foundation1, FOUNDATION_X + CARD_WIDTH + SEPARATION, FOUNDATION_Y);
        drawSimpleCardLocation(FaceUpCardLocation::FaceUpCardLocationCode::Foundation2, FOUNDATION_X + 2 * (CARD_WIDTH + SEPARATION), FOUNDATION_Y);
        drawSimpleCardLocation(FaceUpCardLocation::FaceUpCardLocationCode::Foundation3, FOUNDATION_X + 3 * (CARD_WIDTH + SEPARATION), FOUNDATION_Y);
    }
    void GameScreen::drawColumn(FaceUpCardLocation::FaceUpCardLocationCode location, unsigned int hiddenCards, unsigned int topLeftX, unsigned int topLeftY)
    {
        // We need to know if the location is not a column! We just crash the game
        switch (location)
        {
        case FaceUpCardLocation::FaceUpCardLocationCode::Column0:
        case FaceUpCardLocation::FaceUpCardLocationCode::Column1:
        case FaceUpCardLocation::FaceUpCardLocationCode::Column2:
        case FaceUpCardLocation::FaceUpCardLocationCode::Column3:
        case FaceUpCardLocation::FaceUpCardLocationCode::Column4:
        case FaceUpCardLocation::FaceUpCardLocationCode::Column5:
        case FaceUpCardLocation::FaceUpCardLocationCode::Column6:
            break;
        default:
            throw std::invalid_argument("Game Screen: in drawColumn location must be a column!");
        }
        // Now we draw the cards
        unsigned int playedCardsNumber = mGame->getNumberOfPlayedCardsFrom(location);
        for (size_t i = 0; i < hiddenCards; i++)
        {
            XFillRectangle(mDisplay, mWindow, mContext, topLeftX, topLeftY, CARD_WIDTH, HIDDEN_CARD_HEIGHT);
            XSetForeground(mDisplay, mContext, mWhite);
            XDrawRectangle(mDisplay, mWindow, mContext, topLeftX, topLeftY, CARD_WIDTH, HIDDEN_CARD_HEIGHT);
            XSetForeground(mDisplay, mContext, mBlack);
            topLeftY += HIDDEN_CARD_HEIGHT;
        }
        if (playedCardsNumber == 0)
        {
            drawEmptyCardSpot(topLeftX, topLeftY);
        }
        else
        {
            for (const Card *card : mGame->getTopNCards(location, playedCardsNumber))
            {
                drawCard(card, topLeftX, topLeftY);
                topLeftY += HIDDEN_CARD_HEIGHT;
            }
        }
    }
    void GameScreen::drawColumns()
    {
        drawColumn(FaceUpCardLocation::FaceUpCardLocationCode::Column0,
                   mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column0), COLUMNS_X, COLUMNS_Y);
        drawColumn(FaceUpCardLocation::FaceUpCardLocationCode::Column1,
                   mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column1), COLUMNS_X + (CARD_WIDTH + SEPARATION), COLUMNS_Y);
        drawColumn(FaceUpCardLocation::FaceUpCardLocationCode::Column2,
                   mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column2), COLUMNS_X + 2 * (CARD_WIDTH + SEPARATION), COLUMNS_Y);
        drawColumn(FaceUpCardLocation::FaceUpCardLocationCode::Column3,
                   mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column3), COLUMNS_X + 3 * (CARD_WIDTH + SEPARATION), COLUMNS_Y);
        drawColumn(FaceUpCardLocation::FaceUpCardLocationCode::Column4,
                   mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column4), COLUMNS_X + 4 * (CARD_WIDTH + SEPARATION), COLUMNS_Y);
        drawColumn(FaceUpCardLocation::FaceUpCardLocationCode::Column5,
                   mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column5), COLUMNS_X + 5 * (CARD_WIDTH + SEPARATION), COLUMNS_Y);
        drawColumn(FaceUpCardLocation::FaceUpCardLocationCode::Column6,
                   mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column6), COLUMNS_X + 6 * (CARD_WIDTH + SEPARATION), COLUMNS_Y);
    }
    void GameScreen::drawEmptyCardSpot(unsigned int topLeftX, unsigned int topLeftY)
    {
        XSetForeground(mDisplay, mContext, mWhite);
        XFillRectangle(mDisplay, mWindow, mContext, topLeftX, topLeftY, CARD_WIDTH, CARD_HEIGHT);
        XSetForeground(mDisplay, mContext, mBlack);
        XDrawRectangle(mDisplay, mWindow, mContext, topLeftX, topLeftY, CARD_WIDTH, CARD_HEIGHT);
    }
    void GameScreen::drawRestartButton()
    {
        char const *buttonText = "Restart game";
        XTextItem textItem;
        textItem.delta = 2;
        textItem.font = None;
        textItem.chars = (char *)buttonText;
        textItem.nchars = strlen(buttonText);

        int textX = RESTART_X + (RESTART_BUTTON_WIDTH - strlen(buttonText) * CHAR_WIDTH) / 2;
        int textY = RESTART_Y + (RESTART_BUTTON_HEIGHT - CHAR_WIDTH) / 2;
        XDrawText(mDisplay, mWindow, mContext, textX, textY, &textItem, 1);
        // Draw the rectangle
        XDrawRectangle(mDisplay, mWindow, mContext, RESTART_X, RESTART_Y, RESTART_BUTTON_WIDTH, RESTART_BUTTON_HEIGHT);
    }
    void GameScreen::drawCurrentCardInPlay()
    {
        const Card *clickedCard;
        XTextItem textItem;
        textItem.delta = 2;
        textItem.font = None;
        if (!mFromLocationClick.clicked)
        {
            return;
        }
        if (mFromLocationClick.isMultiCard)
        {
            std::vector<const Card *> cards = mGame->getTopNCards(mFromLocationClick.location, mFromLocationClick.numberOfCards);
            clickedCard = cards.front();
        }
        else
        {
            std::optional<const Card *> card = mGame->getTopCard(mFromLocationClick.location);
            if (!card.has_value())
            {
                return;
            }
            clickedCard = card.value();
        }

        char finalLabel[255];
        char const *baseLabelText = "You're currently trying to move ";
        strcpy(finalLabel, baseLabelText);
        strcat(finalLabel, clickedCard->cardCode().c_str());
        textItem.chars = (char *)finalLabel;
        textItem.nchars = strlen(finalLabel);
        XDrawText(mDisplay, mWindow, mContext, CLICK_TEXT_X, CLICK_TEXT_Y, &textItem, 1);
    }
    void GameScreen::drawGameEnd()
    {
        char const *message;
        switch (mGameStatus)
        {
        case Solitaire::GameStatus::Playing:
            return;
        case Solitaire::GameStatus::Win:
            message = "You win!";
            break;
        case Solitaire::GameStatus::Lose:
            message = "You lose";
            break;
        }
        XTextItem textItem;
        textItem.delta = 2;
        textItem.font = None;
        textItem.chars = (char *)message;
        textItem.nchars = strlen(message);
        XSetForeground(mDisplay, mContext, mWhite);
        XFillRectangle(mDisplay, mWindow, mContext, GAME_END_X, GAME_END_Y, GAME_END_WIDTH, GAME_END_HEIGHT);
        XSetForeground(mDisplay, mContext, mBlack);
        XDrawRectangle(mDisplay, mWindow, mContext, GAME_END_X, GAME_END_Y, GAME_END_WIDTH, GAME_END_HEIGHT);
        XDrawText(mDisplay, mWindow, mContext, GAME_END_X + GAME_END_WIDTH / 2 - (strlen(message) * CHAR_WIDTH), GAME_END_Y + GAME_END_Y / 2 - CHAR_HEIGHT, &textItem, 1);
    }
    // Handle clicks
    void GameScreen::handlePlayerClick(unsigned int x, unsigned int y)
    {
        ClickPosition position = parsePlayerClick(x, y);
        if ((mGameStatus == Solitaire::GameStatus::Win || mGameStatus == Solitaire::GameStatus::Lose) && position != ClickPosition::RestartButton)
        {
            return;
        }

        switch (position)
        {
        case ClickPosition::StockPile:
            onClickStockPile();
            break;
        case ClickPosition::WastePile:
            onClickFaceUpCardLocation(FaceUpCardLocation::FaceUpCardLocationCode::WastePile);
            break;
        case ClickPosition::Foundation0:
            onClickFaceUpCardLocation(FaceUpCardLocation::FaceUpCardLocationCode::Foundation0);
            break;
        case ClickPosition::Foundation1:
            onClickFaceUpCardLocation(FaceUpCardLocation::FaceUpCardLocationCode::Foundation1);
            break;
        case ClickPosition::Foundation2:
            onClickFaceUpCardLocation(FaceUpCardLocation::FaceUpCardLocationCode::Foundation2);
            break;
        case ClickPosition::Foundation3:
            onClickFaceUpCardLocation(FaceUpCardLocation::FaceUpCardLocationCode::Foundation3);
            break;
        case ClickPosition::Column0:
            onClickColumn(y, FaceUpCardLocation::FaceUpCardLocationCode::Column0);
            break;
        case ClickPosition::Column1:
            onClickColumn(y, FaceUpCardLocation::FaceUpCardLocationCode::Column1);
            break;
        case ClickPosition::Column2:
            onClickColumn(y, FaceUpCardLocation::FaceUpCardLocationCode::Column2);
            break;
        case ClickPosition::Column3:
            onClickColumn(y, FaceUpCardLocation::FaceUpCardLocationCode::Column3);
            break;
        case ClickPosition::Column4:
            onClickColumn(y, FaceUpCardLocation::FaceUpCardLocationCode::Column4);
            break;
        case ClickPosition::Column5:
            onClickColumn(y, FaceUpCardLocation::FaceUpCardLocationCode::Column5);
            break;
        case ClickPosition::Column6:
            onClickColumn(y, FaceUpCardLocation::FaceUpCardLocationCode::Column6);
            break;
        case ClickPosition::RestartButton:
            onClickRestart();
            break;
        case ClickPosition::NoLocation:
            break;
        }
    }
    bool GameScreen::isClickInBox(unsigned int clickX, unsigned int clickY, unsigned int topLeftX,
                                  unsigned int topLeftY, unsigned int width, unsigned int height)
    {
        return clickX >= topLeftX && clickX <= (topLeftX + width) && clickY >= topLeftY && clickY <= (topLeftY + height);
    }
    void GameScreen::onClickStockPile()
    {
        mFromLocationClick.clicked = false;
        if (mGame->isStockPileEmpty())
        {
            mGame->refreshStockPile();
        }
        else
        {
            mGame->revealFromStockpile();
        }
    }
    void GameScreen::onClickFaceUpCardLocation(FaceUpCardLocation::FaceUpCardLocationCode code)
    {
        // We need to know if the location is not a column! We just crash the game
        switch (code)
        {
        case FaceUpCardLocation::FaceUpCardLocationCode::WastePile:
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation0:
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation1:
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation2:
        case FaceUpCardLocation::FaceUpCardLocationCode::Foundation3:
            break;
        default:
            throw std::invalid_argument("Game Screen: in onClickFaceUpCardLocation location must be  valid and not a column!");
        }
        if (mFromLocationClick.clicked && (mFromLocationClick.isMultiCard || code == FaceUpCardLocation::FaceUpCardLocationCode::WastePile || mFromLocationClick.location == code))
        {
            mFromLocationClick.clicked = false;
        }
        else if (mFromLocationClick.clicked)
        {
            if (mGame->moveCard(mFromLocationClick.location, code))
            {
                // Update game status after moving card succesfully
                mGameStatus = mGame->checkGameStatus();
            }
            mFromLocationClick.clicked = false;
        }
        else if (!mFromLocationClick.clicked)
        {
            mFromLocationClick.clicked = true;
            mFromLocationClick.isMultiCard = false;
            mFromLocationClick.location = code;
        }
    }
    void GameScreen::onClickColumn(unsigned int y, FaceUpCardLocation::FaceUpCardLocationCode code)
    {
        // We need to know if the location is not a column! We just crash the game
        switch (code)
        {
        case FaceUpCardLocation::FaceUpCardLocationCode::Column0:
        case FaceUpCardLocation::FaceUpCardLocationCode::Column1:
        case FaceUpCardLocation::FaceUpCardLocationCode::Column2:
        case FaceUpCardLocation::FaceUpCardLocationCode::Column3:
        case FaceUpCardLocation::FaceUpCardLocationCode::Column4:
        case FaceUpCardLocation::FaceUpCardLocationCode::Column5:
        case FaceUpCardLocation::FaceUpCardLocationCode::Column6:
            break;
        default:
            throw std::invalid_argument("Game Screen: in onClickColumn location must be a column!");
        }
        if (mFromLocationClick.clicked && mFromLocationClick.location == code)
        {
            mFromLocationClick.clicked = false;
            return;
        }
        int clickedCard = 1;
        int numberHiddenCards = mGame->getNumberOfHiddenCards(code);
        int numberPlayedCards = mGame->getNumberOfPlayedCardsFrom(code);
        int initialTop = (numberHiddenCards + numberPlayedCards - 1) * HIDDEN_CARD_HEIGHT + COLUMNS_Y;
        // we clicked on top of the top card
        if (y < initialTop)
        {
            while (y < initialTop)
            {
                clickedCard++;
                initialTop -= HIDDEN_CARD_HEIGHT;
            }
        }

        if (mFromLocationClick.clicked && clickedCard == 1 && mFromLocationClick.isMultiCard)
        {
            if (mGame->moveNCards(mFromLocationClick.location, code, mFromLocationClick.numberOfCards))
            {
                // Update game status after moving card succesfully
                mGameStatus = mGame->checkGameStatus();
            }
            mFromLocationClick.clicked = false;
        }
        else if (mFromLocationClick.clicked && clickedCard == 1 && !mFromLocationClick.isMultiCard)
        {
            if (mGame->moveCard(mFromLocationClick.location, code))
            {
                // Update game status after moving card succesfully
                mGameStatus = mGame->checkGameStatus();
            }
            mFromLocationClick.clicked = false;
        }
        else if (!mFromLocationClick.clicked && clickedCard == 1)
        {
            mFromLocationClick.clicked = true;
            mFromLocationClick.location = code;
            mFromLocationClick.isMultiCard = false;
        }
        else if (!mFromLocationClick.clicked && clickedCard > 1)
        {
            mFromLocationClick.clicked = true;
            mFromLocationClick.location = code;
            mFromLocationClick.isMultiCard = true;
            mFromLocationClick.numberOfCards = clickedCard;
        }
    }
    void GameScreen::onClickRestart()
    {
        mFromLocationClick.clicked = false;
        mDeck->recoverAllCards();
        clearGame();
        setSolitaire();
    }
    GameScreen::ClickPosition GameScreen::parsePlayerClick(unsigned int x, unsigned int y)
    {
        if (isClickInBox(x, y, STOCKPILE_X, STOCKPILE_Y, CARD_WIDTH, CARD_HEIGHT))
        {
            return ClickPosition::StockPile;
        }
        else if (isClickInBox(x, y, WASTEPILE_X, WASTEPILE_Y, CARD_WIDTH, CARD_HEIGHT))
        {
            return ClickPosition::WastePile;
        }
        else if (isClickInBox(x, y, FOUNDATION_X, FOUNDATION_Y, CARD_WIDTH, CARD_HEIGHT))
        {
            return ClickPosition::Foundation0;
        }
        else if (isClickInBox(x, y, FOUNDATION_X + CARD_WIDTH + SEPARATION, FOUNDATION_Y, CARD_WIDTH, CARD_HEIGHT))
        {
            return ClickPosition::Foundation1;
        }
        else if (isClickInBox(x, y, FOUNDATION_X + 2 * (CARD_WIDTH + SEPARATION), FOUNDATION_Y, CARD_WIDTH, CARD_HEIGHT))
        {
            return ClickPosition::Foundation2;
        }
        else if (isClickInBox(x, y, FOUNDATION_X + 3 * (CARD_WIDTH + SEPARATION), FOUNDATION_Y, CARD_WIDTH, CARD_HEIGHT))
        {
            return ClickPosition::Foundation3;
        }
        int numberPlayerCards = mGame->getNumberOfPlayedCardsFrom(FaceUpCardLocation::FaceUpCardLocationCode::Column0);
        if (isClickInBox(x, y, COLUMNS_X, COLUMNS_Y, CARD_WIDTH, (CARD_HEIGHT + numberPlayerCards * HIDDEN_CARD_HEIGHT)))
        {
            return ClickPosition::Column0;
        }
        // For the rest of the columns I need to move both x and y, because of the hidden cards
        int numberHiddenCards = mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column1);
        numberPlayerCards = mGame->getNumberOfPlayedCardsFrom(FaceUpCardLocation::FaceUpCardLocationCode::Column1);
        if (isClickInBox(x, y, COLUMNS_X + CARD_WIDTH + SEPARATION, COLUMNS_Y + numberHiddenCards * HIDDEN_CARD_HEIGHT, CARD_WIDTH, (CARD_HEIGHT + numberPlayerCards * HIDDEN_CARD_HEIGHT)))
        {
            return ClickPosition::Column1;
        }
        numberHiddenCards = mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column2);
        numberPlayerCards = mGame->getNumberOfPlayedCardsFrom(FaceUpCardLocation::FaceUpCardLocationCode::Column2);
        if (isClickInBox(x, y, COLUMNS_X + 2 * (CARD_WIDTH + SEPARATION), COLUMNS_Y + numberHiddenCards * HIDDEN_CARD_HEIGHT, CARD_WIDTH, (CARD_HEIGHT + numberPlayerCards * HIDDEN_CARD_HEIGHT)))
        {
            return ClickPosition::Column2;
        }
        numberHiddenCards = mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column3);
        numberPlayerCards = mGame->getNumberOfPlayedCardsFrom(FaceUpCardLocation::FaceUpCardLocationCode::Column3);
        if (isClickInBox(x, y, COLUMNS_X + 3 * (CARD_WIDTH + SEPARATION), COLUMNS_Y + numberHiddenCards * HIDDEN_CARD_HEIGHT, CARD_WIDTH, (CARD_HEIGHT + numberPlayerCards * HIDDEN_CARD_HEIGHT)))
        {
            return ClickPosition::Column3;
        }
        numberHiddenCards = mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column4);
        numberPlayerCards = mGame->getNumberOfPlayedCardsFrom(FaceUpCardLocation::FaceUpCardLocationCode::Column4);
        if (isClickInBox(x, y, COLUMNS_X + 4 * (CARD_WIDTH + SEPARATION), COLUMNS_Y + numberHiddenCards * HIDDEN_CARD_HEIGHT, CARD_WIDTH, (CARD_HEIGHT + numberPlayerCards * HIDDEN_CARD_HEIGHT)))
        {
            return ClickPosition::Column4;
        }
        numberHiddenCards = mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column5);
        numberPlayerCards = mGame->getNumberOfPlayedCardsFrom(FaceUpCardLocation::FaceUpCardLocationCode::Column5);
        if (isClickInBox(x, y, COLUMNS_X + 5 * (CARD_WIDTH + SEPARATION), COLUMNS_Y + numberHiddenCards * HIDDEN_CARD_HEIGHT, CARD_WIDTH, (CARD_HEIGHT + numberPlayerCards * HIDDEN_CARD_HEIGHT)))
        {
            return ClickPosition::Column5;
        }
        numberHiddenCards = mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column6);
        numberPlayerCards = mGame->getNumberOfPlayedCardsFrom(FaceUpCardLocation::FaceUpCardLocationCode::Column6);
        if (isClickInBox(x, y, COLUMNS_X + 6 * (CARD_WIDTH + SEPARATION), COLUMNS_Y + numberHiddenCards * HIDDEN_CARD_HEIGHT, CARD_WIDTH, (CARD_HEIGHT + numberPlayerCards * HIDDEN_CARD_HEIGHT)))
        {
            return ClickPosition::Column6;
        }
        if (isClickInBox(x, y, RESTART_X, RESTART_Y, RESTART_BUTTON_WIDTH, RESTART_BUTTON_HEIGHT))
        {
            return ClickPosition::RestartButton;
        }
        return ClickPosition::NoLocation;
    }
    // Clear game
    void GameScreen::clearGame()
    {
        delete mGame;
        delete mWastePile;
        delete mStockPile;
        for (Foundation *f : mFoundations)
        {
            delete f;
        }
        for (Column *c : mColumns)
        {
            delete c;
        }
    }
    GameScreen::~GameScreen()
    {
        clearGame();
    }
}