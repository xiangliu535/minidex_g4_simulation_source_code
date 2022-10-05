#ifndef HPGeDetectorMessenger_h
#define HPGeDetectorMessenger_h 1

#include <G4UImessenger.hh>
#include <globals.hh>

class HPGeDetectorConstruction;

class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;
class G4UIcmdWithoutParameter;

class HPGeDetectorMessenger: public G4UImessenger
{
public:
	HPGeDetectorMessenger(HPGeDetectorConstruction *pHPGeDetector);
	~HPGeDetectorMessenger();

	void SetNewValue(G4UIcommand *pUIcommand, G4String hString);

private:
	HPGeDetectorConstruction* m_pHPGeDetector;

	G4UIdirectory *m_pDetectorDir;
        G4UIcmdWithAString *fSetGDMLsourceFileCmd;

};

#endif

