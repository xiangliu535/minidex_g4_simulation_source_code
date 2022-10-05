#include <G4ios.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleTypes.hh>
#include <G4Track.hh>
#include <G4Event.hh>
#include <G4VProcess.hh>
#include <G4StackManager.hh>
#include <G4RunManager.hh>

#include "HPGeAnalysisManager.hh"

#include "HPGeStackingAction.hh"

HPGeStackingAction::HPGeStackingAction(HPGeAnalysisManager *pAnalysisManager)
{
	m_pAnalysisManager = pAnalysisManager;
    fDoKillGammasOutsideCone = true;
    G4ThreeVector fGammaConeCut_ArrayCenter;
    fGammaConeCut_ArrayCenter.setX(-54.5*mm);
    fGammaConeCut_ArrayCenter.setY(0.0);
    fGammaConeCut_ArrayCenter.setZ(25.1*mm);
    fGammaConeCut_StartCutRadius=20.0*cm;
    fGammaConeCut_MaxAllowedOpeningAngle=50.*deg;
    fTimeWindow = 0.00001*second; // pile up 10 micro second
}

HPGeStackingAction::~HPGeStackingAction()
{
}

G4ClassificationOfNewTrack
HPGeStackingAction::ClassifyNewTrack(const G4Track *pTrack)
{
	G4ClassificationOfNewTrack hTrackClassification = fUrgent;
/*

	if(pTrack->GetDefinition()->GetParticleType() == "nucleus" && !pTrack->GetDefinition()->GetPDGStable())
	{
		if(   pTrack->GetParentID() > 0 
           && pTrack->GetCreatorProcess()->GetProcessName() == "RadioactiveDecay"
           && pTrack->GetGlobalTime() > fTimeWindow)
			//hTrackClassification = fPostpone;
			hTrackClassification = fWaiting;
            ((G4Track*) pTrack)->SetGlobalTime(0.0 * second);
	}
*/
// if the track is not going towards the detector, kill it
/*
  if( fDoKillGammasOutsideCone ) {
      if ( pTrack->GetDefinition()->GetPDGEncoding() == 22) {  // if the track is a gamma
          const G4ThreeVector& gammaMom( pTrack->GetMomentumDirection() );
          const G4ThreeVector& gammaPos( pTrack->GetPosition()          );
          if(fGammaConeCut_StartCutRadius< (fGammaConeCut_ArrayCenter-gammaPos).mag() ) {
              G4double angle = gammaMom.angle(fGammaConeCut_ArrayCenter-gammaPos);
              if(angle>fGammaConeCut_MaxAllowedOpeningAngle) {

//                G4cout<<" track "<<pTrack->GetDefinition()->GetPDGEncoding()<<" with momentum "
//                    <<" px "<<gammaMom.x()
//                    <<" py "<<gammaMom.y()
//                    <<" pz "<<gammaMom.z()
//                    <<" and position "
//                    <<" x "<<gammaPos.x()
//                    <<" y "<<gammaPos.y()
//                    <<" z "<<gammaPos.z()
//                    <<" is killed "<<G4endl;

                return fKill;
              }
          }
      }
  }
*/

/*
   if ( pTrack->GetDefinition()->GetParticleName() == "alpha") {  // if the track is an alpha kill
//     G4cout<<" track "<<pTrack->GetDefinition()->GetPDGEncoding()<<" killed "<<G4endl;
     return fKill;
   }
*/

	return hTrackClassification;
}

void
HPGeStackingAction::NewStage()
{
/*
    m_pAnalysisManager->WritePartialEvent(G4RunManager::GetRunManager()->GetCurrentEvent());
    m_pAnalysisManager->ResetPartialEvent(G4RunManager::GetRunManager()->GetCurrentEvent());
*/
}

void
HPGeStackingAction::PrepareNewEvent()
{ 
}

