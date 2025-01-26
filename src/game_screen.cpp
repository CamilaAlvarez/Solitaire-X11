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
#include <iostream>

#define SCREEN_TITLE "Camila's X11 Solitaire"
#define ICON_NAME "SOLITAIRE"
#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 850
#define CARD_HEIGHT 250
#define CARD_WIDTH 180
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
#define RESTART_X 1190
#define RESTART_Y 20
#define RESTART_BUTTON_WIDTH 200
#define RESTART_BUTTON_HEIGHT 50
#define HIDDEN_CARD_HEIGHT 30

namespace solitaire
{
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
        XSelectInput(mDisplay, mWindow, ExposureMask | ButtonPressMask | KeyPressMask);
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
    }
    void GameScreen::drawTableau()
    {
        drawStockPile();
        drawSimpleCardLocation(FaceUpCardLocation::FaceUpCardLocationCode::WastePile, WASTEPILE_X, WASTEPILE_Y);
        drawFoundations();
        drawColumns();
    }
    void GameScreen::startGameScreen()
    {
        XEvent ev;
        init();
        mGame->startSolitaire();
        while (XNextEvent(mDisplay, &ev) == 0)
        {
            if (ev.type == ButtonPress)
            {
                int x = ev.xbutton.x, y = ev.xbutton.y;
                handlePlayerClick(x, y);
            }
            drawTableau();
            drawRestartButton();
        }
        XUnmapWindow(mDisplay, mWindow);
        XDestroyWindow(mDisplay, mWindow);
    }
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
        std::optional<const Card *> topCard = mGame->viewTopCard(location);
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

        for (size_t i = 0; i < hiddenCards; i++)
        {
            XFillRectangle(mDisplay, mWindow, mContext, topLeftX, topLeftY, CARD_WIDTH, HIDDEN_CARD_HEIGHT);
            XSetForeground(mDisplay, mContext, mWhite);
            XDrawRectangle(mDisplay, mWindow, mContext, topLeftX, topLeftY, CARD_WIDTH, HIDDEN_CARD_HEIGHT);
            XSetForeground(mDisplay, mContext, mBlack);
            topLeftY += HIDDEN_CARD_HEIGHT;
        }

        drawSimpleCardLocation(location, topLeftX, topLeftY);
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
    void GameScreen::handlePlayerClick(unsigned int x, unsigned int y)
    {
        ClickPosition position = parsePlayerClick(x, y);
        switch (position)
        {
        case ClickPosition::StockPile:
            onClickStockPile();
            break;
        case ClickPosition::WastePile:
            onClickWastePile();
            break;
        case ClickPosition::Foundation0:
            onClickFoundation(FaceUpCardLocation::FaceUpCardLocationCode::Foundation0);
            break;
        case ClickPosition::Foundation1:
            onClickFoundation(FaceUpCardLocation::FaceUpCardLocationCode::Foundation1);
            break;
        case ClickPosition::Foundation2:
            onClickFoundation(FaceUpCardLocation::FaceUpCardLocationCode::Foundation2);
            break;
        case ClickPosition::Foundation3:
            onClickFoundation(FaceUpCardLocation::FaceUpCardLocationCode::Foundation3);
            break;
        case ClickPosition::Column0:
            onClickColumn(FaceUpCardLocation::FaceUpCardLocationCode::Column0);
            break;
        case ClickPosition::Column1:
            onClickColumn(FaceUpCardLocation::FaceUpCardLocationCode::Column1);
            break;
        case ClickPosition::Column2:
            onClickColumn(FaceUpCardLocation::FaceUpCardLocationCode::Column2);
            break;
        case ClickPosition::Column3:
            onClickColumn(FaceUpCardLocation::FaceUpCardLocationCode::Column3);
            break;
        case ClickPosition::Column4:
            onClickColumn(FaceUpCardLocation::FaceUpCardLocationCode::Column4);
            break;
        case ClickPosition::Column5:
            onClickColumn(FaceUpCardLocation::FaceUpCardLocationCode::Column5);
            break;
        case ClickPosition::Column6:
            onClickColumn(FaceUpCardLocation::FaceUpCardLocationCode::Column6);
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
        if (mGame->isStockPileEmpty())
        {
            // refresh stockpile
        }
        else
        {
            mGame->revealTopStockPile();
        }
    }
    void GameScreen::onClickWastePile() {}
    void GameScreen::onClickFoundation(FaceUpCardLocation::FaceUpCardLocationCode code) {}
    void GameScreen::onClickColumn(FaceUpCardLocation::FaceUpCardLocationCode code) {}
    void GameScreen::onClickRestart()
    {
        mGame->restartSolitaire();
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
        else if (isClickInBox(x, y, COLUMNS_X, COLUMNS_Y, CARD_WIDTH, CARD_HEIGHT))
        {
            return ClickPosition::Column0;
        }
        // For the rest of the columns I need to move both x and y, because of the hidden cards
        int numberHiddenCards = mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column1);
        if (isClickInBox(x, y, COLUMNS_X + CARD_WIDTH + SEPARATION, COLUMNS_Y + numberHiddenCards * HIDDEN_CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT))
        {
            return ClickPosition::Column1;
        }
        numberHiddenCards = mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column2);
        if (isClickInBox(x, y, COLUMNS_X + 2 * (CARD_WIDTH + SEPARATION), COLUMNS_Y + numberHiddenCards * HIDDEN_CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT))
        {
            return ClickPosition::Column2;
        }
        numberHiddenCards = mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column3);
        if (isClickInBox(x, y, COLUMNS_X + 3 * (CARD_WIDTH + SEPARATION), COLUMNS_Y + numberHiddenCards * HIDDEN_CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT))
        {
            return ClickPosition::Column3;
        }
        numberHiddenCards = mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column4);
        if (isClickInBox(x, y, COLUMNS_X + 4 * (CARD_WIDTH + SEPARATION), COLUMNS_Y + numberHiddenCards * HIDDEN_CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT))
        {
            return ClickPosition::Column4;
        }
        numberHiddenCards = mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column5);
        if (isClickInBox(x, y, COLUMNS_X + 5 * (CARD_WIDTH + SEPARATION), COLUMNS_Y + numberHiddenCards * HIDDEN_CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT))
        {
            return ClickPosition::Column5;
        }
        numberHiddenCards = mGame->getNumberOfHiddenCards(FaceUpCardLocation::FaceUpCardLocationCode::Column6);
        if (isClickInBox(x, y, COLUMNS_X + 6 * (CARD_WIDTH + SEPARATION), COLUMNS_Y + numberHiddenCards * HIDDEN_CARD_HEIGHT, CARD_WIDTH, CARD_HEIGHT))
        {
            return ClickPosition::Column6;
        }
        if (isClickInBox(x, y, RESTART_X, RESTART_Y, RESTART_BUTTON_WIDTH, RESTART_BUTTON_HEIGHT))
        {
            return ClickPosition::RestartButton;
        }
        return ClickPosition::NoLocation;
    }
}