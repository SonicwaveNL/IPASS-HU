// ==========================================================================
//
// File      : matrix-max7219-shift.hpp
// Part of   : IPASS: Matrix window library with MAX7219 implementation
// Copyright : Justin.van.ziel@gmail.com 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef MATRIX_MAX7219_SHIFT_HPP
#define MATRIX_MAX7219_SHIFT_HPP

#include "hwlib.hpp"
#include "matrix-all.hpp"

/// MAX7219 shift class creates a shift animation
//
/// This class defines a left shift animation with overrided render buffer.
//
/// This class overrides the render_buffer funtion of the matrix class
class max7219_shift : public max7219 {

public:

    /// Constructor method
    //
    /// Constructor method for the MAX2719 animation class. A MAX7219 animation is constructed by the following given value:
    /// - window, with hwlib::spi_bus, latch/cs pin, 'X' range and 'Y' parameters.
    max7219_shift( window & get_window ):
        max7219( get_window )
    {}

    /// Render the left shift function with the write buffer
    //
    /// Uses the shift count to create a shifting effect with a indexed value and indexed value + 1 within the write buffer
    void render_buffer() override {

        for(int i = 0; i < 8; i++){

            set_font();

            uint8_t cmd[8];

            for(int j = 0; j < MATRIX_TOTAL; j++ ){

                    uint8_t first = (write_buffer[j] << shift_count );
                    uint8_t second = (write_buffer[j + 1] >> (8 - shift_count ));
                    uint8_t new_first = ( first | second );

                    cmd[j * 2]       = (uint8_t)(i + 1);
                    cmd[(j * 2) + 1] = new_first;


                }

            write( 8, cmd );
        
        }

    }

    /// Shift the given string to the left
    //
    /// This function creates a shift effect with given hwlib::string<int>
    //
    /// A shift effect is created by the following steps:
    /// - Create a text buffer with the size of the string + 1
    /// - Create a loop as long as the size of the string + the matrix size (To get all the characters off screen in the end)
    /// - Fill the text buffer with the default value '0x00'
    /// - Set the first character of the string at the end of the text buffer (The next time the loop occures, the first character will be set at the end - count of the loop)
    /// - Fill the text buffer with the right characters at the right position
    /// - The content of the text buffer will be sent to the image buffer
    /// - The image buffer searches for the right window image that corresponds with the value at given location and loop count (this is used to retrieve a indexed value from the window image)
    /// - When all images are set, set all found codes the write buffer
    /// - The write buffer is writen on the matrix
    void shift_left(const hwlib::string<32> & input){

        hwlib::cout << "Shifting string: " << input << hwlib::endl << hwlib::endl;

        char text_buffer[input.length() + 1];

        for( unsigned int j = 0; j < input.length() + MATRIX_TOTAL; j++ ){

            fill( text_buffer, text_buffer + input.max_size(), 0x00 );

            for( unsigned int t = 0; t < input.length(); t++ ){
                text_buffer[ ( ( MATRIX_TOTAL - j ) + t)] = input[t];

            }

            //Set characters in image_buffer
            for( int i = 0; i < MATRIX_TOTAL + 1; i++ ){
                set_image( text_buffer[i], i );

            }

            // Shift characters out
            for( int amount = 0; amount < 8; amount++ ){

                clear_matrix();

                shift_count = amount;

                render_buffer();

                hwlib::wait_ms( 50 );

            }

        }

    }

};

#endif