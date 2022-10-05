#ifndef __XENON10PHPGeSENSITIVEDETECTOR_H__
#define __XENON10PHPGeSENSITIVEDETECTOR_H__

#include "G4VSensitiveDetector.hh"

#include "HPGeHPGeHit.hh"

#include <map>

using std::map;

class G4Step;
class G4HCofThisEvent;

class HPGeHPGeSensitiveDetector: public G4VSensitiveDetector
{
public:
	HPGeHPGeSensitiveDetector(G4String hName);
	~HPGeHPGeSensitiveDetector();

	void Initialize(G4HCofThisEvent *pHitsCollectionOfThisEvent);
	G4bool ProcessHits(G4Step *pStep, G4TouchableHistory *pHistory);
	void EndOfEvent(G4HCofThisEvent *pHitsCollectionOfThisEvent);

private:
	HPGeHPGeHitsCollection* m_pHPGeHitsCollection;

	map<int,G4String> m_hParticleTypes;
};

#endif // __XENON10PHPGeSENSITIVEDETECTOR_H__

