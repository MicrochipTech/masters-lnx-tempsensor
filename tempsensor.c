/*
 * Copyright (C) 2024 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include "libtempsensor.h"

int main(int argc, char *argv[])
{
    unsigned char *temp;

    temp = getTemp();
    
    printf("Temperature is %d\n", *temp);

    return 0;
}
