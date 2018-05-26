
/*
Implementation basique pour la gestion et le controle d'un capteur 
*/
class Capteur {
    
    public:
    Capteur(short nPinNumber);
    Capteur(short nPinNumber, float dResistanceValue);

    float GetValue();
    void loop();
    void setUp();

    private:

    short nPinNumber;
    float fValue;
    float fResistanceValue;
    
}