#ifndef __XENON10PANALYSISMANAGER_H__
#define __XENON10PANALYSISMANAGER_H__

#include <globals.hh>
 #include "G4PhysicalConstants.hh"
 #include "G4SystemOfUnits.hh"
#include <G4Navigator.hh>
 
#include <TParameter.h>

/*
update:
  2022.09.22, save only primary trajectories and neutron trajectories (and their trajectory points)
              no more directy daughter trajectories from primary (unless they are neutron)
*/

class G4Run;
class G4Event;
class G4Step;

class TFile;
class TTree;

class HPGeEventData;
class HPGePrimaryGeneratorAction;

class HPGeAnalysisManager
{
public:
	HPGeAnalysisManager(HPGePrimaryGeneratorAction *pPrimaryGeneratorAction);
	virtual ~HPGeAnalysisManager();

public:
	virtual void BeginOfRun(const G4Run *pRun); 
	virtual void EndOfRun(const G4Run *pRun); 
	virtual void BeginOfEvent(const G4Event *pEvent); 
	virtual void EndOfEvent(const G4Event *pEvent); 
	virtual void Step(const G4Step *pStep);	

	void SetDataFilename(const G4String &hFilename) { m_hDataFilename = hFilename; }
	void SetNbEventsToSimulate(G4int iNbEventsToSimulate) { m_iNbEventsToSimulate = iNbEventsToSimulate; }

    void FillHitsToNtuple(const G4Event *pEvent);
    void WritePartialEvent(const G4Event *pEvent);
    void ResetPartialEvent(const G4Event *pEvent); // remove all hits collections
    //void SaveBremsstrahlungGamma(G4float px, G4float py, G4float pz);

        bool GetNeedTrajectoryOrNot() {return NeedTrajectory;}
        bool GetNeedTrajectoryPointOrNot() {return NeedTrajectoryPoint;}

private:
	//G4bool FilterEvent(HPGeEventData *pEventData);

private:
	G4int m_iHPGeHitsCollectionID;

	G4String m_hDataFilename;
	G4int m_iNbEventsToSimulate;

	TFile *m_pTreeFile;
	TTree *m_pTree;
	TParameter<int> *m_pNbEventsToSimulateParameter;

	HPGePrimaryGeneratorAction *m_pPrimaryGeneratorAction;

	HPGeEventData *m_pEventData;

    bool NeedTrajectory;
    bool NeedTrajectoryPoint;

};

#endif // __XENON10PANALYSISMANAGER_H__

