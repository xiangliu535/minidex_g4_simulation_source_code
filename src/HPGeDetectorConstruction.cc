#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4Sphere.hh>
#include <G4Torus.hh>
#include <G4Trap.hh>
#include <G4Orb.hh>
#include <G4Polycone.hh>
#include <G4Polyhedra.hh>
#include <G4Trd.hh>
#include <G4Cons.hh>
#include <G4UnionSolid.hh>
#include <G4IntersectionSolid.hh>
#include <G4SubtractionSolid.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4PVParameterised.hh>
#include <G4OpBoundaryProcess.hh>
#include <G4SDManager.hh>
#include <G4ThreeVector.hh>
#include <G4RotationMatrix.hh>
#include <G4VisAttributes.hh>
#include <G4Colour.hh>
#include <globals.hh>
#include <G4GDMLParser.hh>
#include <G4LogicalVolumeStore.hh>
#include <G4PhysicalVolumeStore.hh>

#include <vector>
#include <utility>
#include <string>
#include <numeric>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cassert>

using std::vector;
using std::stringstream;
using std::max;

using namespace CLHEP;

#include "HPGeHPGeSensitiveDetector.hh"
#include "HPGeDetectorConstruction.hh"
#include "HPGeDetectorMessenger.hh"

HPGeDetectorConstruction::HPGeDetectorConstruction()
{
    m_pDetectorMessenger = new HPGeDetectorMessenger(this);
    //fGDMLsourceFile="tueb_runIII_WithRoom_ONLY_Detectors_Sensitive.gdml";
    fGDMLsourceFile="";
}

HPGeDetectorConstruction::~HPGeDetectorConstruction()
{
	delete m_pDetectorMessenger;
}

G4VPhysicalVolume*
HPGeDetectorConstruction::Construct()
{

//
//--> fGDMLsourceFile must be there
//
      G4GDMLParser fParser;
      fParser.Read(fGDMLsourceFile);
//
//-->set sensitive detector
//
    G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
    HPGeHPGeSensitiveDetector *pHPGeSD = new HPGeHPGeSensitiveDetector("HPGe/HPGeSD");
    pSDManager->AddNewDetector(pHPGeSD);
  const G4GDMLAuxMapType* auxmap = fParser.GetAuxMap();
  G4cout << "Found " << auxmap->size()
            << " volume(s) with auxiliary information."
            << G4endl << G4endl;

  for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();
      iter!=auxmap->end(); iter++)
  {
    G4cout << "Volume " << ((*iter).first)->GetName()
           << " has the following list of auxiliary information: "
           << G4endl << G4endl;
    for (G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();
         vit!=(*iter).second.end(); vit++)
    {
      G4cout << "--> Type: " << (*vit).type
                << " Value: " << (*vit).value << G4endl;
    }
    for (G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();
         vit!=(*iter).second.end();vit++)
    {
      if ((*vit).type=="SensDet")
      {
        G4cout << "Attaching sensitive detector " << (*vit).value
               << " to volume " << ((*iter).first)->GetName()
               <<  G4endl << G4endl;

        //G4VSensitiveDetector* mydet =
        //  pSDmanager->FindSensitiveDetector((*vit).value);
        //if(mydet)
        //{
          G4LogicalVolume* myvol = (*iter).first;
          myvol->SetSensitiveDetector(pHPGeSD);
        //}
        //else
        //{
        //  G4cout << (*vit).value << " detector not found" << G4endl;
        //}
      }
    }
  }
      m_pLabPhysicalVolume = fParser.GetWorldVolume();
      m_pLabPhysicalVolume->GetLogicalVolume()->SetVisAttributes(G4VisAttributes::Invisible);
//
//--> 2020.05.06 already checked and ok
//
//      CheckOverlapping();
//
	return m_pLabPhysicalVolume;
}

void HPGeDetectorConstruction::CheckOverlapping()
{
//
//--> loop over all physical volume and check overlap
//
        G4cout << "Checking for overlapping... " << G4endl;
        int iOverlapped = 0;
     G4int res = 100000;
     G4bool verbose = true;
     const G4PhysicalVolumeStore* lvs = G4PhysicalVolumeStore::GetInstance();
      std::vector<G4VPhysicalVolume*>::const_iterator lvciter;
      for( lvciter = lvs->begin(); lvciter != lvs->end(); lvciter++ )
      {
        G4cout<<"check overlapping for physical volume "
              <<(*lvciter)->GetName()
              <<" copy number "
              <<(*lvciter)->GetCopyNo()<<G4endl;
        iOverlapped += (*lvciter)->CheckOverlaps(res, 0, verbose);
      }
        G4cout << "Done." << G4endl << G4endl;
        assert(iOverlapped==0);
}

void HPGeDetectorConstruction::setGDMLsourceFile( G4String sourcefile)
{
   std::ifstream fin(sourcefile);
   if (fin.is_open()) {
      fin.close();
      fGDMLsourceFile=sourcefile;
      G4cout<<"GDML source file is set to be "<<fGDMLsourceFile<<G4endl;
/*
      if (theDetector)
         G4cout<<"The command /MG/geometry/detector "<<fGDMLdefaultOutput
                       <<" has been overridden."<<G4endl;
*/
   }
   else
      G4cout<<"failed to read the GDML source file. Please check your setting again."<<G4endl;
}


void
HPGeDetectorConstruction::PrintGeometryInformation()
{
;
}
