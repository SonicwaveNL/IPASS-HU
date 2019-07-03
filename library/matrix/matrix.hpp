// ==========================================================================
//
// File      : matrix.hpp
// Part of   : IPASS: Matrix window library with MAX7219 implementation
// Copyright : Justin.van.ziel@gmail.com 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "hwlib.hpp"
#include "window-all.hpp"
#include "matrix-settings.hpp"
#include <algorithm>

using namespace std;

/// Window class defines matrix
//
/// This class construct a abstract interface of a matrix
/// The matrix uses a window to do the spi bus operations
//
/// The settings of the matrix are definded within the 'matrix-settings.hpp' file
class matrix : public window {

protected:
    int update_count = 0;
    int shift_count  = 0;

    char image_buffer[MATRIX_TOTAL + 1];
    uint8_t write_buffer[MATRIX_TOTAL + 1];

    uint8_t buffer_x = 0x00;
    uint8_t buffer_y = 0x00;
    uint8_t rows_x[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    uint8_t rows_y[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

public:

    /// Constructor method
    //
    /// Constructor method for the MAX2719 animation class. A MAX7219 animation is constructed by the following given value:
    /// - window, with hwlib::spi_bus, latch/cs pin, 'X' range and 'Y' parameters.
    matrix( window & get_window ):
        window( get_window )
    {
        clear_matrix();
    }

    virtual void init() = 0;

    /// Clear all pixels on matrix
    //
    /// This is done by the following steps:
    /// - Clear rows on 'X' position
    /// - Clear the 'X' buffer
    /// - Clear rows on 'Y' position
    /// - Clear the 'Y' buffer
    /// - Fill the write buffer with '0x00' values
    /// - Write the cleared write buffer to the matrix
    void clear_matrix(){

        clear_row('X');
        clear_buffer('X');

        clear_row('Y');
        clear_buffer('Y');

        fill( write_buffer, write_buffer + MATRIX_TOTAL, 0x00 );

        uint8_t cmd[2] = {0x00, 0x00};

        for(int i = 0; i < 8; i++){
            cmd[0] = (uint8_t)(i + 1);              
            write( 2, cmd );
        }

    }

    /// Writes a '0x00' value to the next matrix
    void push(){
        uint8_t cmd[2] = {0x00, 0x00};
        write( 2, cmd );

    }

    /// Writes buffer_x to the next matrix
    void push_buffer_x(){
        uint8_t cmd[2] = {buffer_x, 0x00};
        write( 2, cmd );

    }

    /// Writes buffer_y to the next matrix
    void push_buffer_y(){
        uint8_t cmd[2] = {buffer_y, 0x00};
        write( 2, cmd );

    }

    /// Set all pixels to given uint8_t on matrix
    void all( uint8_t set_byte ) {
        uint8_t cmd[2] = {0x00, set_byte};

        for( int j = 0; j < MATRIX_TOTAL; j++ ){
            for(int i = 0; i < 8; i++){
                cmd[0] = (uint8_t)(i + 1);          
                write( 2, cmd );
            }

        }
    }

    /// Find the corresponding matrix of the X pixel location
    //
    /// Example: when location_x = 13; the corresponding matrix is '2';
    int map_matrix_x( int location_x ){

        int map_location_x = 0;

        if( location_x <= RANGE_X && location_x > 0 ){
            
            for( int i = 1; i <= MATRIX_X; i++ ){
                int range_min = (( 8 * i ) - 8 ) + 1;
                int range_max = 8 * i;

                

                if( location_x >= range_min && location_x <= range_max ){
                    map_location_x = i;
                    return map_location_x;

                }                

            }

            
        } else {
            hwlib::cout << "--ERROR: location 'X' is out of range!" << hwlib::endl;
        }

        return map_location_x;

    }

    /// Find the corresponding matrix of the Y pixel location
    //
    /// Example: when location_y = 13; the corresponding matrix is '2';
    int map_matrix_y( int location_y ){

        int map_location_y = 0;

        if( location_y <= RANGE_Y && location_y > 0 ){
            
            for( int i = 1; i <= MATRIX_Y; i++ ){
                int range_min = (( 8 * i ) - 8 ) + 1;
                int range_max = 8 * i;

                if( location_y >= range_min && location_y <= range_max ){
                    map_location_y = i;
                    return map_location_y;
                    
                }                

            }

            
        } else {
            hwlib::cout << "--ERROR: location 'Y' is out of range!" << hwlib::endl;
        }

        return map_location_y;

    }

    /// Create a byte and location with within the given matrix and X mapping
    //
    /// Example: when matrix = 4 and location_x = 28; the byte will be: '01000000';
    void create_x( int matrix, int location_x ) { 

        clear_row( 'x' );
        int range_min = (( 8 * matrix ) - 8 ) + 1;
        int range_max = 8 * matrix;
        int count     = 0;

        for( int i = range_min; i <= range_max; i++ ){
            i == location_x ? rows_x[count] = 1 : count++;

        }

        buffer_x = 0b10000000;

        for( int i = range_min; i <= range_max; i++ ){

            if( i == location_x ){
                break;

            } else {
                buffer_x >>= 1;
            }

        }

    }
    
    /// Create a byte and location with within the given matrix and Y mapping
    //
    /// Example: when matrix = 4 and location_y = 28; the byte will be: '01000000';
    void create_y( int matrix, int location_y ) {

        clear_row( 'y' );
        int range_min = (( 8 * matrix ) - 8 ) + 1;
        int range_max = 8 * matrix;
        int count     = 0;

        for( int i = range_min; i <= range_max; i++ ){
            i == location_y ? rows_y[count] = 1 : count++;

        }

        buffer_y = 0b10000000;

        for( int i = range_min; i <= range_max; i++ ){
            if( i == location_y ){
                break;

            } else {
                buffer_y >>= 1;
            }

        }     

    }

    /// Clear a given type of row
    /// The type is specified with a character (accepted both upper- and lowercase )
    //
    /// Example character: 'X' 
    //
    /// When a invalid type is given, a error message will be displayed.
    void clear_row( char rows_type ){

        if( rows_type == 'X' || rows_type == 'x' ){
            for( int i = 0; i > 8; i++ ){
                rows_x[i] = 0;
            }

        } 
        else if( rows_type == 'Y' || rows_type == 'y' ) {

            for( int i = 0; i > 8; i++ ){
                rows_y[i] = 0;
            }

        } else {
            hwlib::cout << "--Error: Rows type doesn't exist!" << hwlib::endl;

        }

    }

    /// Clear a given type of buffer
    /// The type is specified with a character (accepted both upper- and lowercase )
    //
    /// Example character: 'X' 
    //
    /// When a invalid type is given, a error message will be displayed.
    void clear_buffer( char buffer_type ){

        if( buffer_type == 'X' || buffer_type == 'x' ){
            buffer_x = 0x00;

        } 
        else if( buffer_type == 'Y' || buffer_type == 'y' ) {
            buffer_y = 0x00;

        } else {
            hwlib::cout << "--Error: Buffer type doesn't exist!" << hwlib::endl;

        }

    }

    /// Set pixel on given X and Y coordinates
    //
    /// This is done by the following steps:
    /// - Clear the matrix
    /// - Find the right X and Y matrix
    /// - Create a byte with given X and Y locations
    /// - Generate positions so we know where to draw
    /// - Start drawing pixels on the matrix
    /// - Push the pixel to the right matrix  
    void set_pixel( int location_x, int location_y ){

        clear_matrix();

        // Find the right X and Y matrix
        int get_matrix_x = map_matrix_x( location_x );
        int get_matrix_y = map_matrix_y( location_y );

        // Create a byte with given X and Y locations
        create_x( get_matrix_x, location_x );
        create_y( get_matrix_y, location_y );

        // Generate positions so we know where to draw
        buffer_y = 0x00;

        for( int p = 0; p < 8; p++ ){
            if( rows_y[p] == 1 ){
                buffer_y = (uint8_t)(p + 1);
            }
        }
        
        uint8_t cmd[2] = { buffer_y, buffer_x };

        // Start drawing pixels on the matrix
        write( 2, cmd );

        // Push the pixel to the right matrix        
        for( int l = MATRIX_X; l >= get_matrix_x; l-- ){
            if( l == get_matrix_x ){
                break;

            } else {
                push_buffer_y();
            }

        } 

    }

    /// Set image in the image buffer with corresponding position and check if it isn't out of range
    void set_image( char character_image, int position ){
        
        if( position < MATRIX_TOTAL + 1 && position >= 0 ){
            image_buffer[position] = character_image;

        } else {
            hwlib::cout << "Position is out of range!" << hwlib::endl;

        }
        
    }

    /// Get the font with the current state and position of the Matrix. 
    /// Then update the writebuffer with the recieved font values.
    //
    /// This is a virtual function
    virtual void set_font(){

        update_count > 7 ? update_count = 0 : update_count;

        for( int i = 0; i < MATRIX_TOTAL + 1; i++ ){

            char get_char = image_buffer[i];

            auto get_font = window_font();
            auto get_image = get_font[get_char];

            uint8_t get_pos = get_image[update_count];

            write_buffer[i] = reverse_byte(get_pos);

        }

        update_count++;

    }

    /// Render the write buffer on the Matrix
    //
    // This is a virtual function
    virtual void render_buffer(){

        for(int i = 0; i < 8; i++){

            set_font();

            uint8_t cmd[8];

            for(int j = 0; j < 4; j++ ){
                cmd[j * 2]       = (uint8_t)(i + 1);
                cmd[(j * 2) + 1] = write_buffer[j];

            }

            write( 8, cmd );
        
        }

    }

    /// Set and render a given character at given location on the matrix
    //
    // Set character in imagebuffer and render it on the matrix
    void set_character( char text, int location ){
        
        clear_matrix();

        for( int i = 0; i < MATRIX_TOTAL; i++ ){

            if( location == (i + 1) ){
                set_image( text, i );
            } else {
                set_image( 0x00, i );
            }

        }

        render_buffer();

    };

    /// Set and render a given char array and character amount on the matrix
    //
    // Set characters in imagebuffer and render it on the matrix
    void set_characters( char text[], int amount ){

        clear_matrix();

        fill( image_buffer, image_buffer + MATRIX_TOTAL, 0x00 );

        for( int i = 0; i < amount; i++ ){
            set_image( text[i], i );

        }        

        render_buffer();

    }

};

#endif