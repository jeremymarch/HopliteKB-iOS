//
//  accent.h
//  HCPolytonicGreekKBapp
//
//  Created by Jeremy March on 3/4/17.
//  Copyright © 2017 Jeremy March. All rights reserved.
//

#ifndef accent_h
#define accent_h

#include <stdbool.h> //for bool type

typedef unsigned short UCS2;

void accentSyllable(UCS2 *ucs2String, int i, int *len, int accentToAdd, bool toggleOff, int unicodeMode);

int analyzeLetter(UCS2 *ucs2String, int i, int len, int *letterCode, int *accentBitMask);

bool makeLetter(UCS2 *ucs2String, int *newLetterLen, int letterCode, int accentBitMask, int unicodeMode);

#endif /* accent_h */
