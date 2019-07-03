#include "hwlib.hpp"
#include "window-all.hpp"
#include "matrix-all.hpp"

using namespace std;

int main( ){

    namespace target = hwlib::target;

    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    auto clk    = target::pin_out( target::pins::d13 );
    auto cs     = target::pin_out( target::pins::d11 );
    auto din    = target::pin_out( target::pins::d10 );

    auto spi    = hwlib::spi_bus_bit_banged_sclk_mosi_miso( clk, din, hwlib::pin_in_dummy );
    window c_window( spi, cs, 4, 1 );
    auto t_matr = max7219_shift( c_window );

    // Create startup
    hwlib::wait_ms(1000);
    hwlib::cout << "Starting demo >>>---" << hwlib::endl;
 
    hwlib::string< 32 > text = "This is the shift demo!";

    t_matr.shift_left( text );

    while(true){
        t_matr.shift_left( text );
    }

}