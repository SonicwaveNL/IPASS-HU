// ==========================================================================
//
// File      : matrix-max7219-animation.hpp
// Part of   : IPASS: Matrix window library with MAX7219 implementation
// Copyright : Justin.van.ziel@gmail.com 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef MATRIX_MAX7219_ANIMATION_HPP
#define MATRIX_MAX7219_ANIMATION_HPP

#include "hwlib.hpp"
#include "matrix-all.hpp"


/// A simple matrix animation
//
/// This class creates a basic matrix wave animation
class max7219_animation : public max7219 {

public:

    /// Constructor method
    //
    /// Constructor method for the MAX2719 animation class. A MAX7219 animation is constructed by the following given value:
    /// - window, with hwlib::spi_bus, latch/cs pin, 'X' range and 'Y' parameters.
    max7219_animation( window & get_window ):
        max7219( get_window )
    {}

    /// Create a wave effect
    //
    /// A int is given to set the speed of the fade in ms
    void wave( int speed_ms ){
        uint8_t cmd[2] = {0x00, 0b11111111};

            for(int i = 0; i < 8; i++){
                cmd[0] = (uint8_t)(i + 1);          
                write( 2, cmd );
                hwlib::wait_ms(speed_ms);   
            }

            for(int i = 0; i < 8; i++){
                cmd[0] = (uint8_t)(i + 1);
                cmd[1] = 0x00;           
                write( 2, cmd );
                hwlib::wait_ms(speed_ms); 
            }

            clear_matrix();

    }

};

#endif