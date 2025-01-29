// SPDX-License-Identifier:    MIT
/*
 * WastePile class implementation
 *
 * Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 */

#include "solitaire/wastepile.hpp"

namespace solitaire
{
    /**
     * @details The waste pile can never be used by the player as a place to place
     * a card
     *
     * @return true
     * @return false
     */
    bool WastePile::canPlayCardOnTop(const Card *card) const
    {
        return false;
    }
    std::vector<const Card *> WastePile::emptyWastePile()
    {
        std::vector<const Card *> reversedCards(mCards.rbegin(), mCards.rend());
        mCards.clear();
        return reversedCards;
    }

}