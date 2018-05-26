
#include "General.h"
#include "Capteur.h"

class TomatoController 
{
    public:

    TomatoController();
    ~TomatoController();

    void loop();

    void setUp();

    static void StartArroser();
    static void StopArroser();

    static bool bEstEnTrainDArroser;

    private:

    static SimpleTimer pStopTimer;
    static int pStopTimerId;
    
    Capteur capteurTemp = Capteur(PIN_SOLEIL, false);
};
