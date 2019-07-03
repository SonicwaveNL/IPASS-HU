// ==========================================================================
//
// File      : matrix-max7219.hpp
// Part of   : IPASS: Matrix window library with MAX7219 implementation
// Copyright : Justin.van.ziel@gmail.com 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef MATRIX_MAX7217_HPP
#define MATRIX_MAX7217_HPP

#include "hwlib.hpp"
#include "matrix-all.hpp"

/// MAX7219 class defines instructions for the MAX7219 shift register
//
/// This class defines the basic instructions for the MAX7219 shift register.
//
/// The 'OP' codes are accesable by inheritance
class max7219 : public matrix {

protected:
    const uint8_t OP_NO_OP          = 0x00;
    const uint8_t OP_DIGIT_0        = 0x01;
    const uint8_t OP_DIGIT_1        = 0x02;
    const uint8_t OP_DIGIT_2        = 0x03;
    const uint8_t OP_DIGIT_3        = 0x04;
    const uint8_t OP_DIGIT_4        = 0x05;
    const uint8_t OP_DIGIT_5        = 0x06;
    const uint8_t OP_DIGIT_6        = 0x07;
    const uint8_t OP_DIGIT_7        = 0x08;
    const uint8_t OP_DECODE_MODE    = 0x09;
    const uint8_t OP_INTENSITY      = 0x0A;
    const uint8_t OP_SCAN_LIMIT     = 0x0B;
    const uint8_t OP_SHUTDOWN_MODE  = 0x0C;
    const uint8_t OP_DISPLAYTEST    = 0x0F;

public:

    /// Constructor method
    //
    /// Constructor method for the MAX2719 animation class. A MAX7219 animation is constructed by the following given value:
    /// - window, with hwlib::spi_bus, latch/cs pin, 'X' range and 'Y' parameters.
    max7219( window & get_window ):
        matrix( get_window )
    {
        init();
        clear_matrix();
    }

    /// Initialize the MAX7219 matrix
    //
    /// Default settings are:
    /// - 0xX9: set decodemode to none
    /// - 0x0A: Set intensity to 3
    /// - 0x0B: Set Scan limit to use rows 0-7
    /// - 0xXC: set shutdown mode
    /// - 0xXF: set display test mode
    //
    /// The values can be changed using the functions within the MAX7219 class
    void init() override {

        // 0xX9: set decodemode to none
        decode_mode( 0x00 );

        // 0x0A: Set intensity to 3
        intensity( 0x0F );

        // 0x0B: Set Scan limit to use rows 0-7
        scan_limit( 0x07 );

        // 0xXC: set shutdown mode
        shutdown_mode( 0x01 );

        // 0xXF: set display test mode
        display_test( 0x00 );

    }

    /// Set the 'Decode mode' of the MAX7219 to given value
    //
    /// Use a uint8_t value to change the 'Decode mode' 
    void decode_mode( uint8_t amount ){  
        uint8_t cmd[2] = {OP_DECODE_MODE, amount};                        
        write( 2, cmd );

    }

    /// Set the 'Intensity' of the MAX7219 to given value
    //
    /// Use a uint8_t value to change the 'Intensity'
    void intensity( uint8_t amount ){  
        uint8_t cmd[2] = {OP_INTENSITY, amount};                        
        write( 2, cmd );

    }

    /// Set the 'Scan limit' of the MAX7219 to given value
    //
    /// Use a uint8_t value to change the 'Scan limit'
    void scan_limit( uint8_t amount ){
        uint8_t cmd[2] = {OP_SCAN_LIMIT, amount};                        
        write( 2, cmd );
    }

    /// Set the 'Shutdown mode' of the MAX7219 to given value
    //
    /// Use a uint8_t value to change the 'Scan limit'
    void shutdown_mode( uint8_t amount ){
        uint8_t cmd[2] = {OP_SHUTDOWN_MODE, amount};                        
        write( 2, cmd );
    }

    /// Set the 'Display test' of the MAX7219 to given value
    //
    /// Use a uint8_t value to change the 'Display test'
    void display_test( uint8_t amount ){
        uint8_t cmd[2] = {OP_DISPLAYTEST, amount};                        
        write( 2, cmd );
    }

};

#endif