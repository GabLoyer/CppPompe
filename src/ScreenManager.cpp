

// Gère l'affichage de l'écran à l'aide d'une liste de lignes

#include "ScreenManager.h"
#include <string.h>

ScreenManager::ScreenManager()
{
    // Put this line at the beginning of every sketch that uses the GLCD:
    mTFTScreen.begin();

    // clear the screen with a black background
    mTFTScreen.background(0, 0, 0);

    // write the static text to the screen
    // set the font color to white
    mTFTScreen.stroke(255,255,255);
    // set the font size
    mTFTScreen.setTextSize(2);

    for (int i = 0; i < MAX_LIGNES; ++i)
    {
        pScreenText[i] = "";
    }
}

ScreenManager::~ScreenManager()
{
    
}

void ScreenManager::UpdateDisplay()
{
    for (int i = 0; i < MAX_LIGNES; ++i)
    {
        mTFTScreen.stroke(0,0,0);
        mTFTScreen.text(pScreenText[i], 0, MAX_CARACTERES_PAR_LIGNES);   
    }
}

void ScreenManager::ClearDisplay()
{
    for (int i = 0; i < MAX_LIGNES; ++i)
    {
        mTFTScreen.stroke(255, 255, 255);
        mTFTScreen.text(pScreenText[i], 0, MAX_CARACTERES_PAR_LIGNES);   
    }
}

void ScreenManager::SetLine(int p_nIndex, char* sText)
{
    mTFTScreen.stroke(0,0,0);
    mTFTScreen.text(pScreenText[p_nIndex], 0, MAX_CARACTERES_PAR_LIGNES);
    pScreenText[p_nIndex] = sText;
    mTFTScreen.stroke(255,255,255);
    mTFTScreen.text(pScreenText[p_nIndex], 0, MAX_CARACTERES_PAR_LIGNES);    
}

