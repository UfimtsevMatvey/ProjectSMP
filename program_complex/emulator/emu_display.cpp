#include <iostream>
#include "headers/emu_display.h"
#include "headers/def.h"

emu_display::emu_display()
{
    port = NULL;
}
emu_display::~emu_display()
{
}

int emu_display::print_char()
{
    std::cout << &port;
    if(std::cout) return 1;
    else return 0;
}

int emu_display::init_display(SMP_word* external_port)
{
    if(external_port == NULL) return 1;
    port = external_port;
    flag_new_port = 0;   
    return 0;
}

int emu_display::update()
{
    if(print_char()) return 1;
    return 0;
}