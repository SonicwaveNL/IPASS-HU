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

    //Create a window with x:3 and y:3
    window c_window( spi, cs, 3, 3 );

    //Construct command
    uint8_t command[2] = { 0x00, 0x01 };

    //Write to the window and clean after 500ms
    c_window.write( 2, command );
    hwlib::wait_ms(500);

    c_window.clear();

}