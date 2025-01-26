/* Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 * SPDX-License-Identifier:    MIT
 */
#ifndef _SOLITAIRE_GAME_SCREEN_HPP
#define _SOLITAIRE_GAME_SCREEN_HPP

#include "solitaire/card.hpp"
#include "solitaire/game.hpp"
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
        GameScreen(Game *game) : mGame(game) {}
        void drawTableau();
        void startGameScreen();

    private:
        /**
         * @brief Init all necessary screen parameters
         *
         */
        void init();
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
         * @brief Reacts to a click on the waste pile
         *
         */
        void onClickWastePile();
        /**
         * @brief React to a click on a foundation
         *
         * @param foundationNumber
         */
        void onClickFoundation(unsigned int foundationNumber);
        /**
         * @brief Reacts to a click on a column
         *
         * @param columnNumber
         */
        void onClickColumn(unsigned int columnNumber);
        /**
         * @brief Reacts to a click on restart button
         *
         * @param columnNumber
         */
        void onClickRestart();
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
         * @brief Game being displayed on the screen
         *
         */
        Game *mGame;
    };
}
#endif