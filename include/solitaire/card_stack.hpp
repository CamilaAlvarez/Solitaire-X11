/* Copyright (C) 2025 Camila Alvarez <cam.alvarez.i@gmail.com>
 * SPDX-License-Identifier:    MIT
 */
#ifndef _SOLITAIRE_CARD_STACK_HPP
#define _SOLITAIRE_CARD_STACK_HPP

namespace solitaire
{
    /**
     * @brief Interface representing a stack of cards
     *
     */
    class CardStack
    {
    public:
        /**
         * @brief Construct a new Card Stack object
         *
         */
        CardStack() {}
        /**
         * @brief Destroy the Card Stack object
         *
         */
        virtual ~CardStack() {}
        /**
         * @brief Checks if the stack is empty
         *
         * @return true
         * @return false
         */
        virtual bool isEmpty() const = 0;
    };
}

#endif