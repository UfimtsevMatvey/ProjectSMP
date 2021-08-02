#include "device.h"
#include "def.h"

class emu_display : public device
{
private:
    SMP_word* port;
    SMP_word flag_new_port;
    int print_char();
public:
    int update();
    int init_display(SMP_word* external_port);
    emu_display();
    ~emu_display();
};