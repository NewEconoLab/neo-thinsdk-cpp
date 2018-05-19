//
//  SecureRandom.cpp
//  Test
//
//  Created by xgc on 12/18/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#include "SecureRandom.h"
#include <bitcoin/bitcoin.hpp>

using namespace bc;
using namespace bc::wallet;

int SecureRandom::random_number(uint8_t array[16], int len)
{
    /*
    static int dev_random_fd = -1;
    char *next_random_byte;
    int bytes_to_read;
    
    
    if (dev_random_fd == -1)
    {
        dev_random_fd = open("/dev/urandom", O_RDONLY);
        assert(dev_random_fd != -1);
    }
    
    next_random_byte = (char *)&array[0];
    bytes_to_read = len;
    
    
    do
    {
        int bytes_read;
        bytes_read = read(dev_random_fd, next_random_byte, bytes_to_read);
        bytes_to_read -= bytes_read;
        next_random_byte += bytes_read;
        
    }while(bytes_to_read > 0);
    */

    srand((unsigned)time(NULL));
    int i;
    for (i = 0; i < len; i++) {
        array[i] = rand() % 0xFF;
    }

    
    return 0;
}
