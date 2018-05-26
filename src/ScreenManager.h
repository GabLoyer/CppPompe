

// Gère l'affichage de l'écran à l'aide d'une liste de lignes

#include "General.h"
#include <TFT.h>  // Arduino LCD library

class ScreenManager 
{
    public:
    ScreenManager();
    ~ScreenManager();

    void UpdateDisplay();
    void ClearDisplay();
    void SetLine(int nIndex, char* sText);

    private:
    TFT mTFTScreen = TFT(cs, dc, rst);
    char* pScreenText[MAX_LIGNES];
};
