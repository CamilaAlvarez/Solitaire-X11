/* Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 * SPDX-License-Identifier:    MIT
 */
#ifndef _SOLITAIRE_GAME_SCREEN_HPP
#define _SOLITAIRE_GAME_SCREEN_HPP

#include "solitaire/card.hpp"
#include "solitaire/solitaire.hpp"
#include "solitaire/deck.hpp"
#include <X11/Xlib.h>

namespace solitaire
{
    /**
     * @brief Game screen using X11
     *
     */
    class GameScreen
    {
    public:
        /**
         * @brief Construct a new Game Screen object
         *
         * @param game Game to be displayed
         */
        GameScreen(Deck *deck) : mDeck(deck) {}
        /**
         * @brief Starts the game, and displays it on the game screen
         *
         */
        void startGameScreen();
        /**
         * @brief Destroy the Game Screen object
         *
         */
        ~GameScreen();

    private:
        /**
         * @brief Represents the first click on a face up location
         *
         */
        struct FirstClickLocation
        {
            bool clicked, isMultiCard;
            FaceUpCardLocation::FaceUpCardLocationCode location;
            unsigned int numberOfCards;
        };
        /**
         * @brief Stores the first click
         *
         */
        FirstClickLocation mFromLocationClick;
        /**
         * @brief Defines the playable area of the screen where the player clicks on
         *
         */
        enum class ClickPosition
        {
            StockPile,
            WastePile,
            Foundation0,
            Foundation1,
            Foundation2,
            Foundation3,
            Column0,
            Column1,
            Column2,
            Column3,
            Column4,
            Column5,
            Column6,
            RestartButton,
            NoLocation
        };
        /**
         * @brief Parses and handles the user click action
         *
         * @param x
         * @param y
         */
        void handlePlayerClick(unsigned int x, unsigned int y);
        /**
         * @brief Parses and returns the logical location where the user clicked
         *
         * @param x
         * @param y
         * @return ClickPosition
         */
        GameScreen::ClickPosition parsePlayerClick(unsigned int x, unsigned int y);
        /**
         * @brief Checks if click x,y is inside the box with top left
         * (topLeftX, topLeftY) and width and height
         *
         * @param clickX
         * @param clickY
         * @param topLeftX
         * @param topLeftY
         * @param width
         * @param height
         * @return true
         * @return false
         */
        bool isClickInBox(unsigned int clickX, unsigned int clickY, unsigned int topLeftX,
                          unsigned int topLeftY, unsigned int width, unsigned int height);
        /**
         * @brief Init all necessary screen parameters
         *
         */
        void init();
        /**
         * @brief Starts the solitaire setting the columns, foundations, stock pile and waste pile
         *
         */
        void setSolitaire();
        /**
         * @brief Builds the 7 columns
         *
         */
        void buildColumns();
        /**
         * @brief Builds the 4 foundations
         *
         */
        void buildFoundations();

        /**
         * @brief Draws a message when the Game has ended
         *
         */
        void drawGameEnd();
        /**
         * @brief Draws the complete tableau
         *
         */
        void drawTableau();
        /**
         * @brief Draws a card in the window
         *
         * @param card
         * @param topLeftX
         * @param topLeftY
         */
        void drawCard(const Card *card, unsigned int topLeftX, unsigned int topLeftY);
        /**
         * @brief Draws a empty card spot
         *
         * @param topLeftX
         * @param topLeftY
         */
        void drawEmptyCardSpot(unsigned int topLeftX, unsigned int topLeftY);
        /**
         * @brief Draw the stockpile in the screen
         *
         */
        void drawStockPile();
        /**
         * @brief Draw a face up card location with a set x, y origin
         *
         */
        void drawSimpleCardLocation(FaceUpCardLocation::FaceUpCardLocationCode location, unsigned int topLeftX, unsigned int topLeftY);
        /**
         * @brief Draw a single column
         *
         * @throw std::invalid_argument if the location is not a column
         */
        void drawColumn(FaceUpCardLocation::FaceUpCardLocationCode location, unsigned int hiddenCards, unsigned int topLeftX, unsigned int topLeftY);
        /**
         * @brief Draw all 4 foundations int the screen
         *
         */
        void drawFoundations();
        /**
         * @brief Draw the 7 columns in the screen
         *
         */
        void drawColumns();
        /**
         * @brief Draws the restart button in the screen
         *
         */
        void drawRestartButton();
        /**
         * @brief Reacts to a click on the stock pile
         *
         */
        void onClickStockPile();
        /**
         * @brief Reacts to a click on a column
         *
         * @param y y coordinate of the click
         * @param code of the column
         * * @throw std::invalid_argument if the location is not a column
         */
        void onClickColumn(unsigned int y, FaceUpCardLocation::FaceUpCardLocationCode code);
        /**
         * @brief Handles a click on a face up card location
         *
         * @param code
         * @throw std::invalid_argument if the location is invalid or a column
         */
        void onClickFaceUpCardLocation(FaceUpCardLocation::FaceUpCardLocationCode code);
        /**
         * @brief Draws the label indicating the current card in play
         *
         */
        void drawCurrentCardInPlay();
        /**
         * @brief Reacts to a click on restart button
         *
         * @param columnNumber
         */
        void onClickRestart();
        /**
         * @brief Clears the game releasing the memory
         *
         */
        void clearGame();
        /**
         * @brief X11 display
         *
         */
        Display *mDisplay;
        /**
         * @brief represents screen number. We'll use the default screen
         *
         */
        int mScreenNumber;
        /**
         * @brief Window object
         *
         */
        Window mWindow;
        /**
         * @brief Graphics context
         *
         */
        GC mContext;
        /**
         * @brief Colors black, white and red
         *
         */
        unsigned long mBlack, mWhite, mRed;
        /**
         * @brief Deck to be used to build the game
         *
         */
        Deck *mDeck;
        /**
         * @brief Foundations of the game
         *
         */
        std::vector<Foundation *> mFoundations;
        /**
         * @brief Columns of the game
         *
         */
        std::vector<Column *> mColumns;
        /**
         * @brief Waste pile of the game
         *
         */
        WastePile *mWastePile;
        /**
         * @brief Stock pile of the game
         *
         */
        StockPile *mStockPile;
        /**
         * @brief the solitaire game
         *
         */
        Solitaire *mGame;
        /**
         * @brief Stores the current game status, wo we don't have to compute it all the time
         *
         */
        Solitaire::GameStatus mGameStatus;
    };
}
#endif