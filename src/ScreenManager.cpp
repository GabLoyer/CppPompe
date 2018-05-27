

// Gère l'affichage de l'écran à l'aide d'une liste de lignes

#include "ScreenManager.h"
#include <string.h>

ScreenManager::ScreenManager()
{
    // Put this line at the beginning of every sketch that uses the GLCD:
    mTFTScreen = new TFT(cs, dc, rst);
    mTFTScreen->begin();
    Serial.println("Screen Begin");
    // clear the screen with a black background
    mTFTScreen->background(0, 0, 0);

    // write the static text to the screen
    // set the font color to white
    mTFTScreen->stroke(255,255,255);
    // set the font size
    mTFTScreen->setTextSize(2);
}

ScreenManager::~ScreenManager()
{
    
}

void ScreenManager::UpdateDisplay(bool bOnlyValue)
{
    for (int i = 0; i < MAX_LIGNES; ++i)
    {
        mTFTScreen->stroke(255, 255, 255);
        if (!bOnlyValue)
            mTFTScreen->text(pScreenText[i], 0, i * 25 + 1);
        mTFTScreen->text(pScreenValeurs[i], 120, i * 25 + 1);   
    }
}

void ScreenManager::ClearDisplay(bool bOnlyValue)
{
    for (int i = 0; i < MAX_LIGNES; ++i)
    {
        mTFTScreen->stroke(0,0,0);
        if (!bOnlyValue)
            mTFTScreen->text(pScreenText[i], 0, i * 25 + 1);
        mTFTScreen->text(pScreenValeurs[i], 120, i * 25 + 1);   
    }
}
/*
void ScreenManager::SetLine(int p_nIndex, char* sText)
{
    mTFTScreen->stroke(0,0,0);
    mTFTScreen->text(pScreenText[p_nIndex], 0, p_nIndex * 25 + 1);
    pScreenText[p_nIndex] = sText;
    mTFTScreen->stroke(255,255,255);
    mTFTScreen->text(pScreenText[p_nIndex], 0, p_nIndex * 25 + 1);
}*/

void ScreenManager::SetLine(int p_nIndex, char* sText, char* sValeur)
{
    /*mTFTScreen->stroke(0,0,0);
    mTFTScreen->text(pScreenText[p_nIndex], 0, p_nIndex * 25 + 1);
    mTFTScreen->text(pScreenValeurs[p_nIndex], 120, p_nIndex * 25 + 1);*/
    pScreenText[p_nIndex] = sText;
    pScreenValeurs[p_nIndex] = sValeur;
    /*mTFTScreen->stroke(255,255,255);
    mTFTScreen->text(pScreenText[p_nIndex], 0, p_nIndex * 25 + 1);
    mTFTScreen->text(pScreenValeurs[p_nIndex], 120, p_nIndex * 25 + 1);*/
}

void ScreenManager::SetLine(int p_nIndex, char* sValeur)
{
    pScreenValeurs[p_nIndex] = sValeur;
}

