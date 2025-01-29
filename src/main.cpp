// SPDX-License-Identifier:    MIT
/*
 * main implementation
 *
 * Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 */

#include "solitaire/game_screen.hpp"
#include "solitaire/deck.hpp"
#include "solitaire/game.hpp"
#include <vector>

static std::vector<const solitaire::Card *> cards;
static void fillCards();

int main(int argc, char *argv[])
{
    fillCards();
    solitaire::Deck *deck = new solitaire::Deck(cards);
    solitaire::Game game(deck);
    solitaire::GameScreen screen(&game);
    screen.startGameScreen();
    return 0;
}

void fillCards()
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

    cards = {card1, card2, card3, card4, card5, card6, card7, card8,
             card9, card10, card11, card12, card13, card14, card15, card16, card17, card18, card19, card20, card21,
             card22, card23, card24, card25, card26, card27, card28, card29, card30, card31, card32, card33, card34,
             card35, card36, card37, card38, card39, card40, card41, card42, card43, card44, card45, card46, card47,
             card48, card49, card50, card51, card52};
}