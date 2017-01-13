//
//  libmorph.c
//  morph
//
//  Created by Jeremy on 4/15/15.
//  Copyright (c) 2015 Jeremy March. All rights reserved.
//

#include <stdlib.h> // For random(), RAND_MAX
#include <string.h>  //for strlen()
#include <stdbool.h> //for bool type
#include "libmorph.h"
#include "GreekForms.h"
#include "GreekUnicode.h"

#define DECOMPOSED_AUGMENT_CHAR GREEK_SMALL_LETTER_EPSILON

bool onlyUseCombiningDiacritics = false; //not used yet

void rightShiftFromOffsetSteps(UCS2 *ucs2, int offset, int steps, int *len);
void leftShiftFromOffsetSteps(UCS2 *ucs2, int offset, int steps, int *len);

void combiningToPrecomposed(UCS2 *ucs2String, int i, int *len)
{
    //remove macron and change back to pre-composed character
    bool roughBreathing = false;
    bool smoothBreathing = false;
    bool acute = false;
    bool circumFlex = false;
    bool iotaSubscript = false;
    unsigned int spacesToRemove = 1; //1 for the macron
    
    if (ucs2String[i + 2] == COMBINING_ROUGH_BREATHING || ucs2String[ i + 2] == COMBINING_SMOOTH_BREATHING)
    {
        if (ucs2String[i + 2] == COMBINING_ROUGH_BREATHING)
            roughBreathing = true;
        else
            smoothBreathing = true;
        spacesToRemove++;
        
        if (ucs2String[i + 3] == COMBINING_ACUTE || ucs2String[i + 3] == COMBINING_CIRCUMFLEX)
        {
            if (ucs2String[i + 3] == COMBINING_ACUTE)
                acute = true;
            else
                circumFlex = true;
            spacesToRemove++;
            
            if (ucs2String[i + 4] == COMBINING_IOTA_SUBSCRIPT)
            {
                iotaSubscript = true;
                spacesToRemove++;
            }
        }
        else if (ucs2String[i + 3] == COMBINING_IOTA_SUBSCRIPT)
        {
            iotaSubscript = true;
            spacesToRemove++;
        }
    }
    else if (ucs2String[i + 2] == COMBINING_ACUTE || ucs2String[i + 2] == COMBINING_CIRCUMFLEX)
    {
        if (ucs2String[i + 2] == COMBINING_ACUTE)
            acute = true;
        else
            circumFlex = true;
        spacesToRemove++;
        
        if (ucs2String[i + 3] == COMBINING_IOTA_SUBSCRIPT)
        {
            iotaSubscript = true;
            spacesToRemove++;
        }
    }
    else if (ucs2String[i + 2] == COMBINING_IOTA_SUBSCRIPT)
    {
        iotaSubscript = true;
        spacesToRemove++;
    }
    
    for (int j = 0; j < spacesToRemove; j++)
        leftShiftFromOffsetSteps(ucs2String, i + 1, 1, len);
    
    //make the pre-composed character
    if (!roughBreathing && !smoothBreathing && !acute && !circumFlex && !iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON;
    }
    else if (roughBreathing && !smoothBreathing && !acute && !circumFlex && !iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA;
    }
    else if (!roughBreathing && smoothBreathing && !acute && !circumFlex && !iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI;
    }
    else if (!roughBreathing && !smoothBreathing && acute && !circumFlex && !iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_OXIA;
    }
    else if (!roughBreathing && !smoothBreathing && !acute && circumFlex && !iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI;
    }
    else if (!roughBreathing && !smoothBreathing && !acute && !circumFlex && iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI;
    }
    else if (roughBreathing && !smoothBreathing && acute && !circumFlex && !iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_OXIA;
    }
    else if (!roughBreathing && smoothBreathing && acute && !circumFlex && !iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_OXIA;
    }
    else if (roughBreathing && !smoothBreathing && !acute && circumFlex && !iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI;
    }
    else if (!roughBreathing && smoothBreathing && !acute && circumFlex && !iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_PERISPOMENI;
    }
    else if (!roughBreathing && !smoothBreathing && acute && !circumFlex && iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI;
    }
    else if (!roughBreathing && !smoothBreathing && !acute && circumFlex && iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
    }
    else if (roughBreathing && !smoothBreathing && !acute && !circumFlex && iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI;
    }
    else if (!roughBreathing && smoothBreathing && !acute && !circumFlex && iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI;
    }
    else if (roughBreathing && !smoothBreathing && acute && !circumFlex && iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
    }
    else if (!roughBreathing && smoothBreathing && acute && !circumFlex && iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
    }
    else if (roughBreathing && !smoothBreathing && !acute && circumFlex && iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
    }
    else if (!roughBreathing && smoothBreathing && !acute && circumFlex && iotaSubscript)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
    }
}
/*
void accentSyllableUtf8(char *utf8, int accent, bool toggleOff)
{
    
    UCS2 ucs2[20];
    unsigned long len = strlen(utf8);
    utf8_to_ucs2_string((unsigned char*)&utf8[len - 5], ucs2, (int*)&len);
    
    accentSyllable(ucs2, (int)len, (int*)&len, accent, toggleOff);
    
    ucs2_to_utf8_string(ucs2, (int)len, (unsigned char*)utf8);
}
*/
//helper function to make it easier to import into swift
void accentSyllable16(uint16_t *ucs2String, int i, int *len, int accent, bool toggleOff)
{
    accentSyllable((UCS2*)ucs2String, i, len, accent, toggleOff);
}

/**
 * Fix me: iPhone does not display combining acute if alpha macron breathing and subscript.  This should only affect alpha.
 * Update: this is a font issue
 */
void accentSyllable(UCS2 *ucs2String, int i, int *len, int accent, bool toggleOff)
{
    if (*len < 1)
        return;
    //add accent to syllable
    //add cases for if has breathing or iota subscript etc.
    if (accent == ACUTE)
    {
        /* NOT USING PRE-COMPOSED MACRONS
        if ( ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_MACRON || ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_MACRON || ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_MACRON )
        {
            rightShiftFromOffsetSteps(ucs2String, i + 1, 1, len);
            ucs2String[i + 1] = COMBINING_ACUTE;
        }
        else */if ((i < *len - 1 && ucs2String[i + 1] == COMBINING_MACRON) || onlyUseCombiningDiacritics)
        {
            //remove
            if (toggleOff && ucs2String[i + 2] == COMBINING_ACUTE)
            {
                leftShiftFromOffsetSteps(ucs2String, i + 2, 1, len);
            }
            else if (toggleOff && ucs2String[i + 3] == COMBINING_ACUTE)
            {
                leftShiftFromOffsetSteps(ucs2String, i + 3, 1, len);
            }
            else
            {
                //or should we use the private use area codes for this?  looks good on iphone as three combining characters
                if (ucs2String[i + 2] == COMBINING_SMOOTH_BREATHING || ucs2String[i + 2] == COMBINING_ROUGH_BREATHING)
                    i += 1;
                
                rightShiftFromOffsetSteps(ucs2String, i + 2, 1, len);
                ucs2String[i + 2] = COMBINING_ACUTE;
            }
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON)
            ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA_AND_OXIA;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_OXIA;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON)
            ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_DASIA_AND_OXIA;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_OXIA;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;

        else if (toggleOff)
        {
            if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_EPSILON;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMICRON;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_DASIA;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        }
    }
    else if (accent == CIRCUMFLEX)
    {
        //remove combining macron if a circumflex is going on that syllable.
        if ((i < *len - 1 && ucs2String[i + 1] == COMBINING_MACRON)  || onlyUseCombiningDiacritics)
        {
            if (i < *len - 1 && ucs2String[i + 1] == COMBINING_MACRON)
            {
                //leftShiftFromOffsetSteps(ucs2String, i + 1, 1, len);
                combiningToPrecomposed(ucs2String, i, len);
            }
        }
        
        /* no else here */ if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_PERISPOMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;

        else if (toggleOff)
        {
            if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;

            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_OXIA;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_YPOGEGRAMMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        }
    }
    else if (accent == MACRON)
    {
        //if already has a macron...
        if (ucs2String[i + 1] == COMBINING_MACRON && !onlyUseCombiningDiacritics)
        {
            if (toggleOff)
            {
                combiningToPrecomposed(ucs2String, i, len);
            }
            else
            {
                //don't remove macron
            }
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA || ucs2String[i] == GREEK_SMALL_LETTER_IOTA || ucs2String[i] == GREEK_SMALL_LETTER_UPSILON)
        {
            rightShiftFromOffsetSteps(ucs2String, i + 1, 1, len);
            ucs2String[i + 1] = COMBINING_MACRON;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI || ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI || ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI)
        {
            if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON;
            
            rightShiftFromOffsetSteps(ucs2String, i + 2, 2, len);
            ucs2String[i + 1] = COMBINING_MACRON;
            ucs2String[i + 2] = COMBINING_SMOOTH_BREATHING;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA || ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA || ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA)
        {
            if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON;
            
            rightShiftFromOffsetSteps(ucs2String, i + 1, 2, len);
            ucs2String[i + 1] = COMBINING_MACRON;
            ucs2String[i + 2] = COMBINING_ROUGH_BREATHING;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_OXIA || ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_OXIA || ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_OXIA)
        {
            if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON;
            
            rightShiftFromOffsetSteps(ucs2String, i + 1, 2, len);
            ucs2String[i + 1] = COMBINING_MACRON;
            ucs2String[i + 2] = COMBINING_ACUTE;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA || ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_OXIA || ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_OXIA)
        {
            if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON;
            rightShiftFromOffsetSteps(ucs2String, i + 1, 3, len);
            ucs2String[i + 1] = COMBINING_MACRON;
            ucs2String[i + 2] = COMBINING_ROUGH_BREATHING;
            ucs2String[i + 3] = COMBINING_ACUTE;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA || ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA || ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_OXIA)
        {
            if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON;
            rightShiftFromOffsetSteps(ucs2String, i + 1, 3, len);
            ucs2String[i + 1] = COMBINING_MACRON;
            ucs2String[i + 2] = COMBINING_SMOOTH_BREATHING;
            ucs2String[i + 3] = COMBINING_ACUTE;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI || ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI || ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI)
        {
            if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON;
            rightShiftFromOffsetSteps(ucs2String, i + 1, 1, len);
            ucs2String[i + 1] = COMBINING_MACRON;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI || ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI || ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_PERISPOMENI)
        {
            if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON;
            rightShiftFromOffsetSteps(ucs2String, i + 1, 2, len);
            ucs2String[i + 1] = COMBINING_MACRON;
            ucs2String[i + 2] = COMBINING_SMOOTH_BREATHING;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI || ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI || ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI)
        {
            if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON;
            rightShiftFromOffsetSteps(ucs2String, i + 1, 2, len);
            ucs2String[i + 1] = COMBINING_MACRON;
            ucs2String[i + 2] = COMBINING_ROUGH_BREATHING;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
        {
            rightShiftFromOffsetSteps(ucs2String, i + 1, 1, len);
            ucs2String[i + 1] = COMBINING_MACRON;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI)
        {
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI;
            rightShiftFromOffsetSteps(ucs2String, i + 1, 2, len);
            ucs2String[i + 1] = COMBINING_MACRON;
            ucs2String[i + 2] = COMBINING_ACUTE;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
        {
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI;
            rightShiftFromOffsetSteps(ucs2String, i + 1, 1, len);
            ucs2String[i + 1] = COMBINING_MACRON;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI)
        {
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI;
            rightShiftFromOffsetSteps(ucs2String, i + 1, 2, len);
            ucs2String[i + 1] = COMBINING_MACRON;
            ucs2String[i + 2] = COMBINING_SMOOTH_BREATHING;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI)
        {
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI;
            rightShiftFromOffsetSteps(ucs2String, i + 1, 2, len);
            ucs2String[i + 1] = COMBINING_MACRON;
            ucs2String[i + 2] = COMBINING_ROUGH_BREATHING;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
        {
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI;
            rightShiftFromOffsetSteps(ucs2String, i + 1, 3, len);
            ucs2String[i + 1] = COMBINING_MACRON;
            ucs2String[i + 2] = COMBINING_SMOOTH_BREATHING;
            ucs2String[i + 3] = COMBINING_ACUTE;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
        {
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI;
            rightShiftFromOffsetSteps(ucs2String, i + 1, 3, len);
            ucs2String[i + 1] = COMBINING_MACRON;
            ucs2String[i + 2] = COMBINING_ROUGH_BREATHING;
            ucs2String[i + 3] = COMBINING_ACUTE;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
        {
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI;
            rightShiftFromOffsetSteps(ucs2String, i + 1, 2, len);
            ucs2String[i + 1] = COMBINING_MACRON;
            ucs2String[i + 2] = COMBINING_SMOOTH_BREATHING;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
        {
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI;
            rightShiftFromOffsetSteps(ucs2String, i + 1, 2, len);
            ucs2String[i + 1] = COMBINING_MACRON;
            ucs2String[i + 2] = COMBINING_ROUGH_BREATHING;
        }
    }
    else if (accent == ROUGH_BREATHING)
    {
        if (ucs2String[i + 1] == COMBINING_MACRON || onlyUseCombiningDiacritics)  //if macron we use combining rough breathing, except iota subscript
        {
            //remove
            if (toggleOff && ucs2String[i + 2] == COMBINING_ROUGH_BREATHING)
            {
                //leftShift(&ucs2String[i + 2], len);
                leftShiftFromOffsetSteps(ucs2String, i + 2, 1, len);
            }
            else //add
            {
                //rightShift(&ucs2String[i + 2], len);
                if (ucs2String[i + 2] != COMBINING_SMOOTH_BREATHING)
                    rightShiftFromOffsetSteps(ucs2String, i + 2, 1, len);
                ucs2String[i + 2] = COMBINING_ROUGH_BREATHING;
                //(*len) += 1;
            }
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON)
            ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA_AND_OXIA;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON)
            ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_DASIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_DASIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_PSILI_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_DASIA_AND_OXIA;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_RHO)
            ucs2String[i] = GREEK_SMALL_LETTER_RHO_WITH_DASIA;
        else if (toggleOff)
        {
            if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_EPSILON;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_OXIA;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMICRON;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_PSILI_AND_OXIA;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_PERISPOMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_RHO_WITH_DASIA)
                ucs2String[i] = GREEK_SMALL_LETTER_RHO;
        }
    }
    else if (accent == SMOOTH_BREATHING)
    {
        if (ucs2String[i + 1] == COMBINING_MACRON || onlyUseCombiningDiacritics)  //if macron we use combining rough breathing, except iota subscript
        {
            //remove
            if (toggleOff && ucs2String[i + 2] == COMBINING_SMOOTH_BREATHING)
            {
                //leftShift(&ucs2String[i + 2], len);
                leftShiftFromOffsetSteps(ucs2String, i + 2, 1, len);
            }
            else //add
            {
                //rightShift(&ucs2String[i + 2], len);
                if (ucs2String[i + 2] != COMBINING_ROUGH_BREATHING)
                    rightShiftFromOffsetSteps(ucs2String, i + 2, 1, len);
                ucs2String[i + 2] = COMBINING_SMOOTH_BREATHING;
                //(*len) += 1;
            }
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;

        else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON)
            ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_PSILI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_PSILI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_DASIA_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_OXIA;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON)
            ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_PSILI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_PSILI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_DASIA_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_PSILI_AND_OXIA;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_PERISPOMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (toggleOff)
        {
            if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_EPSILON;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_EPSILON_WITH_DASIA_AND_OXIA;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMICRON;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMICRON_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMICRON_WITH_DASIA_AND_OXIA;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        }
    }
    else if (accent == IOTA_SUBSCRIPT)
    {
        if (onlyUseCombiningDiacritics)  //ONLY USE COMBINGING iota subscript, if all combining
        {
            //FIX ME, probably WRONG INDEX for iota subscript
            //rightShift(&ucs2String[i + 2], len);
            rightShiftFromOffsetSteps(ucs2String, i + 2, 1, len);
            ucs2String[i + 1] = COMBINING_IOTA_SUBSCRIPT;
            //(*len) += 1;
        }
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI)
            ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
        else if (toggleOff)
        {
            if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI;
            
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI;
            else if (ucs2String[i] == GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
                ucs2String[i] = GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI;
        }
    }
    else if (accent == SURROUNDING_PARENTHESES)
    {
        if (ucs2String[i] == GREEK_SMALL_LETTER_NU)
        {
            rightShiftFromOffsetSteps(ucs2String, i, 2, len);
            ucs2String[i] = LEFT_PARENTHESIS;
            ucs2String[i + 1] = GREEK_SMALL_LETTER_NU;
            ucs2String[i + 2] = RIGHT_PARENTHESIS;
        }
    }
}

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


/* Input: a Unicode code point, "ucs2".
 
 Output: UTF-8 characters in buffer "utf8".
 
 Return value: the number of bytes written into "utf8", or -1 if
 there was an error.
 
 This adds a zero byte to the end of the string. It assumes that the
 buffer "utf8" has at least four bytes of space to write to. */
// from http://www.lemoda.net/c/ucs2-to-utf8/
int ucs2_to_utf8 (UCS2 ucs2, unsigned char * utf8)
{
    if (ucs2 < 0x80) {
        utf8[0] = ucs2;
        utf8[1] = '\0';
        return 1;
    }
    if (ucs2 >= 0x80  && ucs2 < 0x800) {
        utf8[0] = (ucs2 >> 6)   | 0xC0;
        utf8[1] = (ucs2 & 0x3F) | 0x80;
        utf8[2] = '\0';
        return 2;
    }
    if (ucs2 >= 0x800 && ucs2 < 0xFFFF) {
        if (ucs2 >= 0xD800 && ucs2 <= 0xDFFF) {
            /* Ill-formed. */
            return UNICODE_SURROGATE_PAIR;
        }
        utf8[0] = ((ucs2 >> 12)       ) | 0xE0;
        utf8[1] = ((ucs2 >> 6 ) & 0x3F) | 0x80;
        utf8[2] = ((ucs2      ) & 0x3F) | 0x80;
        utf8[3] = '\0';
        return 3;
    }
    if (ucs2 >= 0x10000 && ucs2 < 0x10FFFF) {
        /* http://tidy.sourceforge.net/cgi-bin/lxr/source/src/utf8.c#L380 */
        utf8[0] = 0xF0 | (ucs2 >> 18);
        utf8[1] = 0x80 | ((ucs2 >> 12) & 0x3F);
        utf8[2] = 0x80 | ((ucs2 >> 6) & 0x3F);
        utf8[3] = 0x80 | ((ucs2 & 0x3F));
        utf8[4] = '\0';
        return 4;
    }
    return UNICODE_BAD_INPUT;
}

/* Convert a UTF-8 encoded character in "input" into a number. This
 function returns the unicode value of the UTF-8 character if
 successful, and -1 if not successful. "end_ptr" is set to the next
 character after the read character on success. "end_ptr" is set to
 the start of input on failure. "end_ptr" may not be null. */

UCS2 utf8_to_ucs2 (const unsigned char * input, const unsigned char ** end_ptr)
{
    *end_ptr = input;
    if (input[0] == 0)
        return -1;
    if (input[0] < 0x80) {
        * end_ptr = input + 1;
        return input[0];
    }
    if ((input[0] & 0xE0) == 0xE0) {
        if (input[1] == 0 || input[2] == 0)
            return -1;
        * end_ptr = input + 3;
        return
        (input[0] & 0x0F)<<12 |
        (input[1] & 0x3F)<<6  |
        (input[2] & 0x3F);
    }
    if ((input[0] & 0xC0) == 0xC0) {
        if (input[1] == 0)
            return -1;
        * end_ptr = input + 2;
        return
        (input[0] & 0x1F)<<6  |
        (input[1] & 0x3F);
    }
    return -1;
}

//FIX ME, this could probably be written more efficiently.
//only null terminate at the end and verify that it is null terminated properly
int ucs2_to_utf8_string(UCS2 *ucs2, int len, unsigned char *utf8)
{
    unsigned char *utf8Temp = utf8;
    if (len < 1)
    {
        utf8[0] = '\0';
        return 1;
    }
    
    for (int i = 0; i < len; i++)
    {
        int utf8Len;
        utf8Len = ucs2_to_utf8(ucs2[i], utf8Temp);
        if (utf8Len > -1)
            utf8Temp += utf8Len;
        else
            return 0;
        *utf8Temp = '\0';
    }
    
    return 1;
}

void utf8_to_ucs2_string(const unsigned char *utf8, UCS2 *ucs2, int *len)
{
    int temp; //because UCS2 is unsigned.
    *len = 0;
    
    for( int i = 0; *utf8 ; i++)
    {
        temp = utf8_to_ucs2 (utf8, &utf8);
        if (temp == -1)
        {
            break;
        }
        else
        {
            ucs2[i] = temp;
        }
        (*len)++;
    }
}



