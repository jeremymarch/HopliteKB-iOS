//
//  utilities.c
//  HCPolytonicGreekKBapp
//
//  Created by Jeremy March on 3/4/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

#include "utilities.h"

void rightShiftFromOffsetSteps(UCS2 *ucs2, int offset, int steps, int *len)
{
    int j = offset + *len - 1;
    for ( ; j >= offset; j--)
    {
        ucs2[j + steps] = ucs2[j];
    }
    *len += steps;
}

//Moves everything over to the left, eating the first letter
void leftShiftFromOffsetSteps(UCS2 *ucs2, int offset, int steps, int *len)
{
    int j = offset;
    for ( ; j < *len - 1; j++)
    {
        ucs2[j] = ucs2[j + steps];
    }
    *len -= steps;
}
