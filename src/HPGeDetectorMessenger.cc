#include <G4ThreeVector.hh>
#include <G4RotationMatrix.hh>
#include <G4ParticleTable.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UIcmdWith3Vector.hh>
#include <G4UIcmdWith3VectorAndUnit.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithADouble.hh>
#include <G4UIcmdWithABool.hh>
#include <G4Tokenizer.hh>
#include <G4ios.hh>
#include <fstream>
#include <iomanip>

#include "HPGeDetectorMessenger.hh"

#include "HPGeDetectorConstruction.hh"

#include "HPGeParticleSource.hh"

HPGeDetectorMessenger::HPGeDetectorMessenger(HPGeDetectorConstruction *pHPGeDetector)
:m_pHPGeDetector(pHPGeDetector)
{ 
	m_pDetectorDir = new G4UIdirectory("/HPGe/det/");
	m_pDetectorDir->SetGuidance("detecotor control");
	
        fSetGDMLsourceFileCmd = new G4UIcmdWithAString("/HPGe/det/GDMLsourceFile",this);
        fSetGDMLsourceFileCmd->SetGuidance("Set the GDML source file.");
        fSetGDMLsourceFileCmd->AvailableForStates(G4State_PreInit);
	
}

HPGeDetectorMessenger::~HPGeDetectorMessenger()
{
	delete m_pDetectorDir;
        delete fSetGDMLsourceFileCmd;
}

void HPGeDetectorMessenger::SetNewValue(G4UIcommand *pUIcommand, G4String hNewValue)
{
  if (pUIcommand == fSetGDMLsourceFileCmd) {
    m_pHPGeDetector->setGDMLsourceFile(hNewValue);
  }

}


