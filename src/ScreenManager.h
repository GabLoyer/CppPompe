
// Gère l'affichage de l'écran à l'aide d'une liste de lignes

#include "General.h"


class ScreenManager 
{
    public:
    ScreenManager();
    ~ScreenManager();

    void UpdateDisplay(bool bOnlyValue);
    void ClearDisplay(bool bOnlyValue);
    void SetLine(int nIndex, char* sText);
    void SetLine(int p_nIndex, char* sText, char* sValeur);

    private:
    TFT* mTFTScreen;
    char* pScreenText[MAX_LIGNES];
    char* pScreenValeurs[MAX_LIGNES];
};
