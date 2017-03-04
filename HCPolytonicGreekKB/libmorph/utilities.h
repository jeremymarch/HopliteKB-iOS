//
//  utilities.h
//  HCPolytonicGreekKBapp
//
//  Created by Jeremy March on 3/4/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

#ifndef utilities_h
#define utilities_h

#include <stdio.h>

typedef unsigned short UCS2;

void rightShiftFromOffsetSteps(UCS2 *ucs2, int offset, int steps, int *len);
void leftShiftFromOffsetSteps(UCS2 *ucs2, int offset, int steps, int *len);

#endif /* utilities_h */
