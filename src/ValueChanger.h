// Gère la modification de valeur runtime

#include "General.h"

class ValueChanger 
{
    public:

     enum eVariable {
        eDUREE_MIN,
        eDUREE_MAX,
        eINTERVAL_MIN,
        eINTERVAL_MAX,
        eSOLEIL_NUIT,
        eUNKNOWN
    };

    ValueChanger();
    ~ValueChanger();

    eVariable getCurrentVariable();
    void setCurrentVariable(eVariable variable);
    void modifyValueofVariable(int delta);
    void updateLoop();


    private:
    eVariable mCurrentVariable;

};
