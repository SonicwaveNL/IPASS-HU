// ==========================================================================
//
// File      : window-image.hpp
// Part of   : IPASS: Matrix window library with MAX7219 implementation
// Copyright : Justin.van.ziel@gmail.com 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef WINDOW_IMAGE_HPP
#define WINDOW_IMAGE_HPP

#include "hwlib.hpp"
#include "window-all.hpp"

/// Window image class defines a accessable image.
//
/// This class defines an accessable window image.
/// Each window image is constructed with 8 given uint8_t hex codes.
//
/// The font of an can be accessed with the operator[].
/// This will return a uint8_t value that corresponds with the given position
//
/// This class is inspired by the hwlib's image class.
/// Link to file: https://github.com/wovo/hwlib/blob/master/library/graphics/hwlib-graphics-image.hpp
class window_image {

private:
    uint8_t data[8];

public:

    /// Constructor method
    //
    /// Constructor method for the window image class. A image constructed by the following given values:
    /// - uint8_t, index '0'
    /// - uint8_t, index '1'
    /// - uint8_t, index '2'
    /// - uint8_t, index '3'
    /// - uint8_t, index '4'
    /// - uint8_t, index '5'
    /// - uint8_t, index '6'
    /// - uint8_t, index '7'

    window_image( uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7 ):
        data{ d0, d1, d2, d3, d4, d5, d6, d7 }
    {}

    /// Access a value of a window image with given position
    //
    /// Returns a uint8_t value with given int position
    uint8_t operator[]( int position ) {
        return data[ position ];

    }

};

#endif
