#ifndef __XENON10PSTACKINGACTION_H__
#define __XENON10PSTACKINGACTION_H__

#include <globals.hh>
#include <G4UserStackingAction.hh>
#include <G4ThreeVector.hh>

class HPGeAnalysisManager;

class HPGeStackingAction: public G4UserStackingAction
{
public:
	HPGeStackingAction(HPGeAnalysisManager *pAnalysisManager=0);
       ~HPGeStackingAction();
  
	virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
	virtual void NewStage();
	virtual void PrepareNewEvent();

private:
	HPGeAnalysisManager *m_pAnalysisManager;

  G4bool             fDoKillGammasOutsideCone;
  G4ThreeVector      fGammaConeCut_ArrayCenter;
  G4double           fGammaConeCut_StartCutRadius;
  G4double           fGammaConeCut_MaxAllowedOpeningAngle;
  G4double           fTimeWindow;

};

#endif // __XENON10PSTACKINGACTION_H__

