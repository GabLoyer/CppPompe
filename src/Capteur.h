
/*
Implementation basique pour la gestion et le controle d'un capteur 
*/
class Capteur {
    
    public:
    Capteur(short nPinNumber, bool bIsOut);
    Capteur(short nPinNumber, float dResistanceValue, bool bIsOut);

    float GetValue();
    void loop();
    void setUp();

    private:

    short nPinNumber;
    float fValue;
    float fResistanceValue;
    
};
