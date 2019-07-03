// ==========================================================================
//
// File      : matrix-settings.hpp
// Part of   : IPASS: Matrix window library with MAX7219 implementation
// Copyright : Justin.van.ziel@gmail.com 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef MATRIX_SETTINGS_HPP
#define MATRIX_SETTINGS_HPP

#include "hwlib.hpp"

//Settings of the matrix
constexpr int MATRIX_X              = 4;                                                  //Amount of displays on the 'X'
constexpr int MATRIX_Y              = 1;                                                  //Amount of displays on the 'Y'
constexpr int PIXELS_X              = 8;                                                  //Amount of pixels on a 'X' display
constexpr int PIXELS_Y              = 8;                                                  //Amount of pixels on a 'Y' display
constexpr int MATRIX_TOTAL          = ( MATRIX_X * MATRIX_Y );                            //Total amount of displays on 'X' and 'Y'
constexpr int PIXELS_TOTAL          = ( MATRIX_X * PIXELS_X ) * ( MATRIX_Y * PIXELS_Y );  //Total amount of pixels on 'X' and 'Y'

//Calculate the range of both X and Y
constexpr int RANGE_X               = ( MATRIX_X * PIXELS_X );
constexpr int RANGE_Y               = ( MATRIX_Y * PIXELS_Y );

#endif