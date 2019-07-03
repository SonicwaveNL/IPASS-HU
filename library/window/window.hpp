// ==========================================================================
//
// File      : window.hpp
// Part of   : IPASS: Matrix window library with MAX7219 implementation
// Copyright : Justin.van.ziel@gmail.com 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "hwlib.hpp"

using namespace std;

/// Window class defines a window
//
/// This class construct a abstract interface foundation.
/// The window is mainly used to do basic 'spi bus' operations
class window {

protected:
    hwlib::spi_bus & bus;   
    hwlib::pin_out & cs;

    const int window_x = 0;
    const int window_y = 0;

public:

    /// Constructor method
    //
    /// Constructor method for the window class. A window is constructed by the following given values:
    /// - hwlib::spi_bus, a spi bus with 'Clock' and 'DATAIN' parameters
    /// - hwlib::pin_out, the latch/cs pin
    /// - int, the 'X' size of the window
    /// - int, the 'Y' size of the window
    window( hwlib::spi_bus & bus, hwlib::pin_out & cs, int get_x, int get_y ):
        bus( bus ),
        cs( cs ),
        window_x( get_x ),
        window_y( get_y )
    {}

    /// Get the 'X' range of the window
    //
    /// Return the range of X in int
    int get_x(){ return window_x; }

    /// Get the 'Y' range of the window
    //
    /// Return the range of Y in int
    int get_y(){ return window_y; }

    /// Clear the window
    //
    /// This function clears the window by writing '0x00' hex values to the bus.
    /// The amount of times the hex values are writen to the bus are determined by
    /// the total range of the window ( X * Y )
    virtual void clear() {

        uint8_t cmd[2] = {0x00, 0x00};

        for(int i = 0; i < (window_x * window_y); i++){
            cmd[0] = (uint8_t)(i + 1);              
            write( 2, cmd );
        }

    }

    /// Reverse given byte
    //
    /// This is mainly used the write the window font in reverse.
    //
    /// Returns a revesed uint8_t value
    uint8_t reverse_byte( uint8_t input ){
        input = (input & 0xF0) >> 4 | (input & 0x0F) << 4;
        input = (input & 0xCC) >> 2 | (input & 0x33) << 2;
        input = (input & 0xAA) >> 1 | (input & 0x55) << 1;
        return input;

    }

    /// Write command to spi bus
    //
    /// Write given command and size of command to the spi bus.
    //
    /// This is a virtual function
    virtual void write( int size, uint8_t command[] ){
        bus.transaction( cs ).write_and_read( size, command, nullptr );
    }

};

#endif