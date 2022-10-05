#ifndef __XENON10PDETECTORCONSTRUCTION_H__
#define __XENON10PDETECTORCONSTRUCTION_H__

//----------------------------------------------------------
// from outside inwards
//   20cm Pb, 10cmCu, inner chamber 20cmx20cm space, 40cm high
//   HPGe at the very origin
//   all these logical volumes should be put directly into Mother volume
//   therefore, all shield volumes are subtracted volumes
//
//  2011.8.7 move the detector 9mm away from the copper wall and add PE hat
//           following 3 components are moved towards +x direction by 9 mm within the Chamber
//           Cryostat
//           ChamberCoolingFinger
//           CryostatinnerVolume 
//
// 2013.5.18 construct GEMMX detector with modified shielding
//           the counting chamber volume is 20cm x 20cm x 35cm
//           the copper shield is 40cm x 40cm, total height is 70cm, top 10cm thick, bottom 25cm thick,
//           the lead shield is 80cm x 80cm, total height is 110cm,
//
// 2013.6.20 put eight blocks of stainlesssteel samples ,3.844kg
//           100x100x50 mm3
//----------------------------------------------------------

#include <globals.hh>

#include <vector>
#include <map>

using std::vector;
using std::map;

class G4LogicalVolume;
class G4VPhysicalVolume;
class HPGeDetectorMessenger;

#include <G4VUserDetectorConstruction.hh>

class HPGeDetectorConstruction: public G4VUserDetectorConstruction
{
public:
	HPGeDetectorConstruction();
	~HPGeDetectorConstruction();

	G4VPhysicalVolume* Construct();

        void setGDMLsourceFile( G4String );

private:
    G4LogicalVolume *m_pMotherLogicalVolume;
    G4LogicalVolume *m_pLabLogicalVolume;
    G4VPhysicalVolume *m_pMotherPhysicalVolume;
    G4VPhysicalVolume *m_pLabPhysicalVolume;

	void CheckOverlapping();
	void PrintGeometryInformation();

private:
	
	HPGeDetectorMessenger *m_pDetectorMessenger;
        G4String fGDMLsourceFile;
};

#endif // __XENON10PDETECTORCONSTRUCTION_H__

