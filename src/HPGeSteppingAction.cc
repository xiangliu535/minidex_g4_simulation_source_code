#include <G4ios.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleTypes.hh>
#include <G4Track.hh>
#include <G4Event.hh>
#include <G4VProcess.hh>
#include <G4StackManager.hh>
#include <G4TrackStatus.hh>

#include "HPGeAnalysisManager.hh"

#include "HPGeSteppingAction.hh"
#include "HPGeDetectorConstruction.hh"
#include <G4Step.hh>


HPGeSteppingAction::HPGeSteppingAction(HPGeAnalysisManager *pAnalysisManager)
{
	m_pAnalysisManager = pAnalysisManager;
}

HPGeSteppingAction::~HPGeSteppingAction()
{
}

void HPGeSteppingAction::UserSteppingAction(const G4Step* theStep) 
{
/*
//--> kill bremsstrahlung
    G4String particleName = theStep->GetTrack()->GetDefinition()->GetParticleName();
    G4String fPreVolumeName;
    G4String fPostVolumeName;
    G4double ke;
    G4ThreeVector temppos;
    G4ThreeVector tempmom;
    if (particleName == "gamma") {
       //if (theStep->GetPhysicsProcess()->GetName()=="Bremssstrahlung") {
       if (theStep->GetTrack()->GetCreatorProcess()->GetProcessName()=="eBrem") {
          tempmom=theStep->GetTrack()->GetMomentum();
          temppos=theStep->GetPreStepPoint()->GetPosition();
//          m_pAnalysisManager->SaveBremsstrahlungGamma(px,py,pz);
          ke=theStep->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/keV;
          G4cout<<" Brems gamma "<<tempmom.x()/keV<<" "<<tempmom.y()/keV<<" "<<tempmom.z()/keV<<""<<G4endl;
          G4cout<<" kE "<<ke<<" keV"<<G4endl;
          G4cout<<" killed at "<<temppos.x()<<" "<<temppos.y()<<" "<<temppos.z()<<""<<G4endl;
          theStep->GetTrack()->SetTrackStatus(fStopAndKill);
       }
    }
*/
}









