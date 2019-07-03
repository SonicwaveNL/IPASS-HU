#include "hwlib.hpp"
#include "window-all.hpp"
#include "matrix-all.hpp"

using namespace std;

void test_window_x( window & get_window, int check ){

    int get_x = get_window.get_x();

    if( get_x != check ){
        hwlib::cout << "ERROR: TEST_WINDOW_X - Invalid 'x'";
        
    }

};

void test_window_y( window & get_window, int check ){

    int get_y = get_window.get_y();

    if( get_y != check ){
        hwlib::cout << "ERROR: TEST_WINDOW_Y - Invalid 'y'";
        
    }

};

void test_reverse_byte( window & get_window, uint8_t check){

    uint8_t get_value = get_window.reverse_byte( 0b11100000 );

    if( get_value != check ){
        hwlib::cout << "ERROR: TEST_REVERSE_BYTE";
        
    }

};

void test_settings(){
    if( MATRIX_X == 0 ){
        hwlib::cout << "ERROR: TEST_MATRIX_SETTINGS";
        
    }
    else if( MATRIX_Y == 0 ){
        hwlib::cout << "ERROR: TEST_MATRIX_SETTINGS";
        
    }

    else if( PIXELS_X == 0 ){
        hwlib::cout << "ERROR: TEST_MATRIX_SETTINGS";
        
    }

    else if( PIXELS_Y == 0 ){
        hwlib::cout << "ERROR: TEST_MATRIX_SETTINGS";
        
    }

}

void test_mapping_x( max7219 & get_matrix, int location_x, int check ){

    int map_matrix_x = get_matrix.map_matrix_x( location_x );

    if( map_matrix_x != check ){
        hwlib::cout << "ERROR: TEST_MAPPING_X";
        
    }

}

void test_mapping_y( max7219 & get_matrix, int location_y, int check ){

    int map_matrix_y = get_matrix.map_matrix_y( location_y );

    if( map_matrix_y != check ){
        hwlib::cout << "ERROR: TEST_MAPPING_Y";
        
    }

}

int main( ){

    namespace target = hwlib::target;

    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    auto clk    = target::pin_out( target::pins::d13 );
    auto cs     = target::pin_out( target::pins::d11 );
    auto din    = target::pin_out( target::pins::d10 );

    auto spi    = hwlib::spi_bus_bit_banged_sclk_mosi_miso( clk, din, hwlib::pin_in_dummy );
    window c_window( spi, cs, 4, 1 );
    auto t_matr = max7219( c_window );

    // Start testing - Window
    test_window_x( c_window, 4 );
    test_window_y( c_window, 1 );
    test_reverse_byte( c_window, 0b00000111 );

    // Start testing - Matrix
    test_settings();
    test_mapping_x( t_matr, 13, 2 );
    test_mapping_y( t_matr, 3, 1 );
    
    hwlib::cout << hwlib::endl;
    hwlib::cout << "===========================================" << hwlib::endl;
    hwlib::cout << "Run complete!" << hwlib::endl;
        
};

