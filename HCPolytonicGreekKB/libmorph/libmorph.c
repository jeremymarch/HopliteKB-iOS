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

/*
 if macron was pressed
    is there already a macron?
        change to pre-composed without macron
    else, is the syllable combining or pre-composed?
 
 
 */
enum {
    NORMAL,
    PSILI,                                  //smooth
    DASIA,                                  //rough
    OXIA,
    PSILI_AND_OXIA,
    DASIA_AND_OXIA,
    VARIA,
    PSILI_AND_VARIA,
    DASIA_AND_VARIA,
    PERISPOMENI,
    PSILI_AND_PERISPOMENI,
    DASIA_AND_PERISPOMENI,
    YPOGEGRAMMENI,
    PSILI_AND_YPOGEGRAMMENI,
    DASIA_AND_YPOGEGRAMMENI,
    OXIA_AND_YPOGEGRAMMENI,
    PSILI_AND_OXIA_AND_YPOGEGRAMMENI,
    DASIA_AND_OXIA_AND_YPOGEGRAMMENI,
    VARIA_AND_YPOGEGRAMMENI,
    PSILI_AND_VARIA_AND_YPOGEGRAMMENI,
    DASIA_AND_VARIA_AND_YPOGEGRAMMENI,
    PERISPOMENI_AND_YPOGEGRAMMENI,
    PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI,
    DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI,
    NUM_ACCENT_CODES
};

enum {
    ALPHA,
    EPSILON,
    ETA,
    IOTA,
    OMICRON,
    UPSILON,
    OMEGA,
    NUM_VOWEL_CODES
};

unsigned short letters[NUM_VOWEL_CODES][NUM_ACCENT_CODES] = {
    {GREEK_SMALL_LETTER_ALPHA, GREEK_SMALL_LETTER_ALPHA_WITH_PSILI, GREEK_SMALL_LETTER_ALPHA_WITH_DASIA, GREEK_SMALL_LETTER_ALPHA_WITH_OXIA, GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA, GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA, GREEK_SMALL_LETTER_ALPHA_WITH_VARIA, GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_VARIA, GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_VARIA, GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI, GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI, GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI, GREEK_SMALL_LETTER_ALPHA_WITH_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ALPHA_WITH_OXIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ALPHA_WITH_VARIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_VARIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_VARIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ALPHA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ALPHA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ALPHA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI },
    
    {GREEK_SMALL_LETTER_EPSILON, GREEK_SMALL_LETTER_EPSILON_WITH_PSILI, GREEK_SMALL_LETTER_EPSILON_WITH_DASIA, GREEK_SMALL_LETTER_EPSILON_WITH_OXIA, GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_OXIA, GREEK_SMALL_LETTER_EPSILON_WITH_DASIA_AND_OXIA, GREEK_SMALL_LETTER_EPSILON_WITH_VARIA, GREEK_SMALL_LETTER_EPSILON_WITH_PSILI_AND_VARIA, GREEK_SMALL_LETTER_EPSILON_WITH_DASIA_AND_VARIA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    
    {GREEK_SMALL_LETTER_ETA, GREEK_SMALL_LETTER_ETA_WITH_PSILI, GREEK_SMALL_LETTER_ETA_WITH_DASIA, GREEK_SMALL_LETTER_ETA_WITH_OXIA, GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA, GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA, GREEK_SMALL_LETTER_ETA_WITH_VARIA, GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_VARIA, GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_VARIA, GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI, GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI, GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI, GREEK_SMALL_LETTER_ETA_WITH_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ETA_WITH_OXIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ETA_WITH_VARIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_VARIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_VARIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ETA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ETA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_ETA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI },
    
    {GREEK_SMALL_LETTER_IOTA, GREEK_SMALL_LETTER_IOTA_WITH_PSILI, GREEK_SMALL_LETTER_IOTA_WITH_DASIA, GREEK_SMALL_LETTER_IOTA_WITH_OXIA, GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_OXIA, GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_OXIA, GREEK_SMALL_LETTER_IOTA_WITH_VARIA, GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_VARIA, GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_VARIA, GREEK_SMALL_LETTER_IOTA_WITH_PERISPOMENI, GREEK_SMALL_LETTER_IOTA_WITH_PSILI_AND_PERISPOMENI, GREEK_SMALL_LETTER_IOTA_WITH_DASIA_AND_PERISPOMENI, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    
    {GREEK_SMALL_LETTER_OMICRON, GREEK_SMALL_LETTER_OMICRON_WITH_PSILI, GREEK_SMALL_LETTER_OMICRON_WITH_DASIA, GREEK_SMALL_LETTER_OMICRON_WITH_OXIA, GREEK_SMALL_LETTER_OMICRON_WITH_PSILI_AND_OXIA, GREEK_SMALL_LETTER_OMICRON_WITH_DASIA_AND_OXIA, GREEK_SMALL_LETTER_OMICRON_WITH_VARIA, GREEK_SMALL_LETTER_OMICRON_WITH_PSILI_AND_VARIA, GREEK_SMALL_LETTER_OMICRON_WITH_DASIA_AND_VARIA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    
    {GREEK_SMALL_LETTER_UPSILON, GREEK_SMALL_LETTER_UPSILON_WITH_PSILI, GREEK_SMALL_LETTER_UPSILON_WITH_DASIA, GREEK_SMALL_LETTER_UPSILON_WITH_OXIA, GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_OXIA, GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_OXIA, GREEK_SMALL_LETTER_UPSILON_WITH_VARIA, GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_VARIA, GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_VARIA, GREEK_SMALL_LETTER_UPSILON_WITH_PERISPOMENI, GREEK_SMALL_LETTER_UPSILON_WITH_PSILI_AND_PERISPOMENI, GREEK_SMALL_LETTER_UPSILON_WITH_DASIA_AND_PERISPOMENI, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    
    {GREEK_SMALL_LETTER_OMEGA, GREEK_SMALL_LETTER_OMEGA_WITH_PSILI, GREEK_SMALL_LETTER_OMEGA_WITH_DASIA, GREEK_SMALL_LETTER_OMEGA_WITH_OXIA, GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA, GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA, GREEK_SMALL_LETTER_OMEGA_WITH_VARIA, GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_VARIA, GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_VARIA, GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI, GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI, GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI, GREEK_SMALL_LETTER_OMEGA_WITH_YPOGEGRAMMENI, GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_OMEGA_WITH_OXIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_OXIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_OXIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_OMEGA_WITH_VARIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_VARIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_VARIA_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_OMEGA_WITH_PERISPOMENI_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_OMEGA_WITH_PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI, GREEK_SMALL_LETTER_OMEGA_WITH_DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI }
};

bool analyzePrecomposedLetter(short letter, int *l, int *a)
{
    for (*l = 0; *l < NUM_VOWEL_CODES; (*l)++)
    {
        for (*a = 0; *a < NUM_ACCENT_CODES; (*a)++)
        {
            if (letter == letters[*l][*a])
                return true;
        }
    }
    return false;
}

void accentCodeToAnalysis(int accentCode, bool *smooth, bool *rough, bool *acute, bool *grave, bool *circumflex, bool *iota_sub)
{
    *smooth = false;
    *rough = false;
    *acute = false;
    *grave = false;
    *circumflex = false;
    *iota_sub = false;
    
    if (accentCode == PSILI)
    {
        *smooth = true;
    }
    else if (accentCode == DASIA)
    {
        *rough = true;
    }
    else if (accentCode == OXIA)
    {
        *acute = true;
    }
    else if (accentCode == PSILI_AND_OXIA)
    {
        *smooth = true;
        *acute = true;
    }
    else if (accentCode == DASIA_AND_OXIA)
    {
        *rough = true;
        *acute = true;
    }
    else if (accentCode == VARIA)
    {
        *grave = true;
    }
    else if (accentCode == PSILI_AND_VARIA)
    {
        *smooth = true;
        *grave = true;
    }
    else if (accentCode == DASIA_AND_VARIA)
    {
        *rough = true;
        *grave = true;
    }
    else if (accentCode == PERISPOMENI)
    {
        *circumflex = true;
    }
    else if (accentCode == PSILI_AND_PERISPOMENI)
    {
        *smooth = true;
        *circumflex = true;
    }
    else if (accentCode == DASIA_AND_PERISPOMENI)
    {
        *rough = true;
        *circumflex = true;
    }
    else if (accentCode == YPOGEGRAMMENI)
    {
        *iota_sub = true;
    }
    else if (accentCode == PSILI_AND_YPOGEGRAMMENI)
    {
        *smooth = true;
        *iota_sub = true;
    }
    else if (accentCode == DASIA_AND_YPOGEGRAMMENI)
    {
        *rough = true;
        *iota_sub = true;
    }
    else if (accentCode == OXIA_AND_YPOGEGRAMMENI)
    {
        *acute = true;
        *iota_sub = true;
    }
    else if (accentCode == PSILI_AND_OXIA_AND_YPOGEGRAMMENI)
    {
        *smooth = true;
        *acute = true;
        *iota_sub = true;
    }
    else if (accentCode == DASIA_AND_OXIA_AND_YPOGEGRAMMENI)
    {
        *rough = true;
        *acute = true;
        *iota_sub = true;
    }
    else if (accentCode == VARIA_AND_YPOGEGRAMMENI)
    {
        *grave = true;
        *iota_sub = true;
    }
    else if (accentCode == PSILI_AND_VARIA_AND_YPOGEGRAMMENI)
    {
        *smooth = true;
        *grave = true;
        *iota_sub = true;
    }
    else if (accentCode == DASIA_AND_VARIA_AND_YPOGEGRAMMENI)
    {
        *rough = true;
        *grave = true;
        *iota_sub = true;
    }
    else if (accentCode == PERISPOMENI_AND_YPOGEGRAMMENI)
    {
        *circumflex = true;
        *iota_sub = true;
    }
    else if (accentCode == PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
    {
        *smooth = true;
        *circumflex = true;
        *iota_sub = true;
    }
    else if (accentCode == DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI)
    {
        *rough = true;
        *circumflex = true;
        *iota_sub = true;
    }
}

//return 0 for invalid letter
short getPrecomposedLetter(int letterCode, bool smooth, bool rough, bool acute, bool grave, bool circumflex, bool iota_sub, bool macron)
{
    short l = -1;
    int accent = 0;

    if (!smooth && !rough && !acute && !grave && !circumflex && !iota_sub && !macron)
        accent = NORMAL;
    else if (smooth && !rough && !acute && !grave && !circumflex && !iota_sub && !macron)
        accent = PSILI;
    else if (!smooth && rough && !acute && !grave && !circumflex && !iota_sub && !macron)
        accent = DASIA;
    else if (!smooth && !rough && acute && !grave && !circumflex && !iota_sub && !macron)
        accent = OXIA;
    else if (smooth && !rough && acute && !grave && !circumflex && !iota_sub && !macron)
        accent = PSILI_AND_OXIA;
    else if (!smooth && rough && acute && !grave && !circumflex && !iota_sub && !macron)
        accent = DASIA_AND_OXIA;
    else if (!smooth && !rough && !acute && grave && !circumflex && !iota_sub && !macron)
        accent = VARIA;
    else if (smooth && !rough && !acute && grave && !circumflex && !iota_sub && !macron)
        accent = PSILI_AND_VARIA;
    else if (!smooth && rough && !acute && grave && !circumflex && !iota_sub && !macron)
        accent = DASIA_AND_VARIA;
    else if (!smooth && !rough && !acute && !grave && circumflex && !iota_sub && !macron)
        accent = PERISPOMENI;
    else if (smooth && !rough && !acute && !grave && circumflex && !iota_sub && !macron)
        accent = PSILI_AND_PERISPOMENI;
    else if (!smooth && rough && !acute && !grave && circumflex && !iota_sub && !macron)
        accent = DASIA_AND_PERISPOMENI;
    else if (!smooth && !rough && !acute && !grave && !circumflex && iota_sub && !macron)
        accent = YPOGEGRAMMENI;
    else if (smooth && !rough && !acute && !grave && !circumflex && iota_sub && !macron)
        accent = PSILI_AND_YPOGEGRAMMENI;
    else if (!smooth && rough && !acute && !grave && !circumflex && iota_sub && !macron)
        accent = DASIA_AND_YPOGEGRAMMENI;
    else if (!smooth && !rough && acute && !grave && !circumflex && iota_sub && !macron)
        accent = OXIA_AND_YPOGEGRAMMENI;
    else if (smooth && !rough && acute && !grave && !circumflex && iota_sub && !macron)
        accent = PSILI_AND_OXIA_AND_YPOGEGRAMMENI;
    else if (!smooth && rough && acute && !grave && !circumflex && iota_sub && !macron)
        accent = DASIA_AND_OXIA_AND_YPOGEGRAMMENI;
    else if (!smooth && !rough && !acute && grave && !circumflex && iota_sub && !macron)
        accent = VARIA_AND_YPOGEGRAMMENI;
    else if (smooth && !rough && !acute && grave && !circumflex && iota_sub && !macron)
        accent = PSILI_AND_VARIA_AND_YPOGEGRAMMENI;
    else if (!smooth && rough && !acute && grave && !circumflex && iota_sub && !macron)
        accent = DASIA_AND_VARIA_AND_YPOGEGRAMMENI;
    else if (!smooth && !rough && !acute && !grave && circumflex && iota_sub && !macron)
        accent = PERISPOMENI_AND_YPOGEGRAMMENI;
    else if (smooth && !rough && !acute && !grave && circumflex && iota_sub && !macron)
        accent = PSILI_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
    else if (!smooth && rough && !acute && !grave && circumflex && iota_sub && !macron)
        accent = DASIA_AND_PERISPOMENI_AND_YPOGEGRAMMENI;
    else
        return 0;
    
    if (letterCode > -1)
        return letters[letterCode][accent];
    else
        return 0;
}

#define DECOMPOSED_AUGMENT_CHAR GREEK_SMALL_LETTER_EPSILON
#define MAX_COMBINING 5 //macron, breathing, accent, iota subscript

bool onlyUseCombiningDiacritics = false; //not used yet

void combiningToPrecomposed(UCS2 *ucs2String, int i, int *len);
void rightShiftFromOffsetSteps(UCS2 *ucs2, int offset, int steps, int *len);
void leftShiftFromOffsetSteps(UCS2 *ucs2, int offset, int steps, int *len);

#define NUM_COMBINING_ACCENTS 7
int combiningAccents[NUM_COMBINING_ACCENTS] = { COMBINING_MACRON, COMBINING_ROUGH_BREATHING, COMBINING_SMOOTH_BREATHING, COMBINING_ACUTE, COMBINING_GRAVE, COMBINING_CIRCUMFLEX, COMBINING_IOTA_SUBSCRIPT };

bool isCombiningDiacritic(UCS2 l)
{
    switch (l)
    {
        case COMBINING_MACRON:
        case COMBINING_ACUTE:
        case COMBINING_GRAVE:
        case COMBINING_CIRCUMFLEX:
        case COMBINING_IOTA_SUBSCRIPT:
        case COMBINING_SMOOTH_BREATHING:
        case COMBINING_ROUGH_BREATHING:
        //case COMBINING_DIAERESIS:
            return true;
    }
    
    return false;
}

bool isBareVowel(UCS2 l)
{
    switch (l)
    {
        case GREEK_SMALL_LETTER_ALPHA:
        case GREEK_SMALL_LETTER_EPSILON:
        case GREEK_SMALL_LETTER_ETA:
        case GREEK_SMALL_LETTER_IOTA:
        case GREEK_SMALL_LETTER_UPSILON:
        case GREEK_SMALL_LETTER_OMEGA:
            return true;
    }
    
    return false;
}

int ucs2ToLetterCode(short l)
{
    if (l == GREEK_SMALL_LETTER_ALPHA)
        return ALPHA;
    else if (l == GREEK_SMALL_LETTER_EPSILON)
        return EPSILON;
    else if (l == GREEK_SMALL_LETTER_ETA)
        return ETA;
    else if (l == GREEK_SMALL_LETTER_IOTA)
        return IOTA;
    else if (l == GREEK_SMALL_LETTER_OMICRON)
        return OMICRON;
    else if (l == GREEK_SMALL_LETTER_UPSILON)
        return UPSILON;
    else if (l == GREEK_SMALL_LETTER_OMEGA)
        return OMEGA;
    else
        return 0;
}

int letterCodeToUCS2(short l)
{
    if (l == ALPHA)
        return GREEK_SMALL_LETTER_ALPHA;
    else if (l == EPSILON)
        return GREEK_SMALL_LETTER_EPSILON;
    else if (l == ETA)
        return GREEK_SMALL_LETTER_ETA;
    else if (l == IOTA)
        return GREEK_SMALL_LETTER_IOTA;
    else if (l == OMICRON)
        return GREEK_SMALL_LETTER_OMICRON;
    else if (l == UPSILON)
        return GREEK_SMALL_LETTER_UPSILON;
    else if (l == OMEGA)
        return GREEK_SMALL_LETTER_OMEGA;
    else
        return 0;
}

void accentSyllable2(UCS2 *ucs2String, int i, int *len, int accent, bool toggleOff)
{
    if (*len < 1)
        return;
    
    //1. handle consonants
    if (ucs2String[i] == GREEK_SMALL_LETTER_RHO && accent == ROUGH_BREATHING)
    {
        ucs2String[i] = GREEK_SMALL_LETTER_RHO_WITH_DASIA;
        return;
    }
    else if (ucs2String[i] == GREEK_SMALL_LETTER_RHO_WITH_DASIA && accent == ROUGH_BREATHING)
    {
        ucs2String[i] = GREEK_SMALL_LETTER_RHO;
        return;
    }
    else if (ucs2String[i] == GREEK_SMALL_LETTER_NU && accent == SURROUNDING_PARENTHESES)
    {
        ucs2String[i] = LEFT_PARENTHESIS;
        ucs2String[i+1] = GREEK_SMALL_LETTER_NU;
        ucs2String[i+2] = RIGHT_PARENTHESIS;
        *len = 3;
        return;
    }
    
    //2. now analyze what is currently there
    int letterCode = 0;
    int accentCode = 0;
    bool smooth = false;
    bool rough = false;
    bool acute = false;
    bool grave = false;
    bool circumflex = false;
    bool iota_sub = false;
    bool macron = false;
    
    if (*len > 1 && ucs2String[i+1] == COMBINING_MACRON)
    {
        for (int j = 1; j <= MAX_COMBINING && j <= (*len + 1); j++)
        {
            if (ucs2String[i + j] == COMBINING_ROUGH_BREATHING)
                rough = true;
            else if (ucs2String[i + j] == COMBINING_SMOOTH_BREATHING)
                smooth = true;
            else if (ucs2String[i + j] == COMBINING_ACUTE)
                acute = true;
            else if (ucs2String[i + j] == COMBINING_GRAVE)
                grave = true;
            else if (ucs2String[i + j] == COMBINING_CIRCUMFLEX)
                circumflex = true;
            else if (ucs2String[i + j] == COMBINING_MACRON)
                macron = true;
            else if (ucs2String[i + j] == COMBINING_IOTA_SUBSCRIPT)
                iota_sub = true;
            else if (ucs2String[i + j] == COMBINING_DIAERESIS)
                ;//rough = true;
            else
                break;
        }
        
        letterCode = ucs2ToLetterCode(ucs2String[i]);
    }
    else
    {
        if (!analyzePrecomposedLetter(ucs2String[i], &letterCode, &accentCode))
            return;
    
        accentCodeToAnalysis(accentCode, &smooth, &rough, &acute, &grave, &circumflex, &iota_sub);
    }
    
    //3. this changes old letter analysis to the one we want
    if (accent == ACUTE)
    {
        acute = (toggleOff) ? !acute : true;
        grave = false;
        circumflex = false;
    }
    else if (accent == GRAVE)
    {
        grave = (toggleOff) ? !grave : true;
        acute = false;
        circumflex = false;
    }
    else if (accent == SMOOTH_BREATHING)
    {
        smooth = (toggleOff) ? !smooth : true;
        rough = false;
    }
    else if (accent == ROUGH_BREATHING)
    {
        rough = (toggleOff) ? !rough : true;
        smooth = false;
    }
    else if (accent == CIRCUMFLEX)
    {
        if (letterCode != ALPHA && letterCode != ETA && letterCode != IOTA && letterCode != UPSILON && letterCode != OMEGA)
            return;
        
        circumflex = (toggleOff) ? !circumflex : true;
        acute = false;
        grave = false;
        macron = false;
    }
    else if (accent == IOTA_SUBSCRIPT)
    {
        if (letterCode != ALPHA && letterCode != ETA && letterCode != OMEGA)
            return;
        
        iota_sub = (toggleOff) ? !iota_sub : true;
    }
    else if (accent == MACRON)
    {
        if (letterCode != ALPHA && letterCode != IOTA && letterCode != UPSILON)
            return;
        macron = (toggleOff) ? !macron : true;
        circumflex = false;
    }
    
    //4. this creates the new letter, either with combining or precomposed accents
    
    if (macron || onlyUseCombiningDiacritics) //if there is a macron we use combining accents, else precomposed
    {
        ucs2String[i] = letterCodeToUCS2(letterCode);
        *len = 1;
        for (int k = 0; k < NUM_COMBINING_ACCENTS; k++)
        {
            if (combiningAccents[k] == COMBINING_MACRON && macron)
            {
                ucs2String[i + *len] = combiningAccents[k];
                ++(*len);
            }
            else if (combiningAccents[k] == COMBINING_ROUGH_BREATHING && rough)
            {
                ucs2String[i + *len] = combiningAccents[k];
                ++(*len);
            }
            else if (combiningAccents[k] == COMBINING_SMOOTH_BREATHING && smooth)
            {
                ucs2String[i + *len] = combiningAccents[k];
                ++(*len);
            }
            else if (combiningAccents[k] == COMBINING_ACUTE && acute)
            {
                ucs2String[i + *len] = combiningAccents[k];
                ++(*len);
            }
            else if (combiningAccents[k] == COMBINING_GRAVE && grave)
            {
                ucs2String[i + *len] = combiningAccents[k];
                ++(*len);
            }
            else if (combiningAccents[k] == COMBINING_CIRCUMFLEX && circumflex)
            {
                ucs2String[i + *len] = combiningAccents[k];
                ++(*len);
            }
            else if (combiningAccents[k] == COMBINING_IOTA_SUBSCRIPT && iota_sub)
            {
                ucs2String[i + *len] = combiningAccents[k];
                ++(*len);
            }
        }
    }
    else
    {
        short ucs2 = getPrecomposedLetter(letterCode, smooth, rough, acute, grave, circumflex, iota_sub, macron);
    
        ucs2String[i] = ucs2;
        *len = 1;
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
    accentSyllable2((UCS2*)ucs2String, i, len, accent, toggleOff);
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



