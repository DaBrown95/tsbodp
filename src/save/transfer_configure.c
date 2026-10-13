#include "save_transfer.h"

unsigned short save_transfer_configure_4c8f4(unsigned short size)
{
    unsigned short status = 0;
    if (size == 4)
        SAVE_TRANSFER_PARAMETERS = SAVE_TRANSFER_PARAMETERS_4;
    else if (size == 64)
        SAVE_TRANSFER_PARAMETERS = SAVE_TRANSFER_PARAMETERS_64;
    else {
        SAVE_TRANSFER_PARAMETERS = SAVE_TRANSFER_PARAMETERS_4;
        status = 1;
    }
    return status;
}
asm(".align 2, 0");
