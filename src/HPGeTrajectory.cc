//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
//

#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4AttDefStore.hh"

#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"

#include "HPGeTrajectory.hh"
//#include "HPGeTrajectoryPoint.hh"
#include "G4ParticleTable.hh"

//#define G4ATTDEBUG
#ifdef G4ATTDEBUG
#include "G4AttCheck.hh"
#endif

G4Allocator<HPGeTrajectory> aTrajectoryAllocator;

HPGeTrajectory::HPGeTrajectory()
    : fpPointsContainer(0), fTrackID(0), fParentID(0),
      PDGCharge(0.0), PDGEncoding(0), ParticleName(""),
      initialMomentum(G4ThreeVector()), initialKineticEnergy(0.0),
      CreatorVolumeName(""), CreatorProcessName(""), CreatorPosition(G4ThreeVector()) {;}

HPGeTrajectory::HPGeTrajectory(const G4Track* aTrack)
{
    G4ParticleDefinition * fpParticleDefinition = aTrack->GetDefinition();
    ParticleName = fpParticleDefinition->GetParticleName();
    PDGCharge = fpParticleDefinition->GetPDGCharge();
    PDGEncoding = fpParticleDefinition->GetPDGEncoding();
    fTrackID = aTrack->GetTrackID();
    fParentID = aTrack->GetParentID();
    initialMomentum = aTrack->GetMomentum();
    initialKineticEnergy = aTrack->GetKineticEnergy();
    CreatorVolumeName  = aTrack->GetVolume()->GetName();
    if (aTrack->GetCreatorProcess()) CreatorProcessName = aTrack->GetCreatorProcess()->GetProcessName();
    CreatorPosition = aTrack->GetVertexPosition();
    fpPointsContainer = new TrajectoryPointContainer();
    // Following is for the first trajectory point
    fpPointsContainer->push_back(new HPGeTrajectoryPoint(aTrack));
}

HPGeTrajectory::HPGeTrajectory(HPGeTrajectory & right) : G4VTrajectory() 
{
    ParticleName = right.ParticleName;
    PDGCharge = right.PDGCharge;
    PDGEncoding = right.PDGEncoding;
    fTrackID = right.fTrackID;
    fParentID = right.fParentID;
    initialMomentum = right.initialMomentum;
    initialKineticEnergy = right.initialKineticEnergy;
    CreatorVolumeName  = right.CreatorVolumeName;
    CreatorProcessName = right.CreatorProcessName;
    fpPointsContainer = new TrajectoryPointContainer();

    for(size_t i=0;i<right.fpPointsContainer->size();++i) {
        HPGeTrajectoryPoint* rightPoint
            = (HPGeTrajectoryPoint*)((*(right.fpPointsContainer))[i]);
        fpPointsContainer->push_back(new HPGeTrajectoryPoint(*rightPoint));
    }
}

HPGeTrajectory::~HPGeTrajectory()
{
    for(size_t i=0;i<fpPointsContainer->size();++i){
        delete  (*fpPointsContainer)[i];
    }
    fpPointsContainer->clear();

    delete fpPointsContainer;
}

void HPGeTrajectory::ShowTrajectory(std::ostream& os) const
{
    // Invoke the default implementation in G4VTrajectory...
    G4VTrajectory::ShowTrajectory(os);
    // ... or override with your own code here.
}

void HPGeTrajectory::DrawTrajectory(G4int i_mode) const
{
    // Invoke the default implementation in G4VTrajectory...
    //G4VTrajectory::DrawTrajectory(i_mode);
    G4VTrajectory::DrawTrajectory();
    // ... or override with your own code here.
}

void HPGeTrajectory::AppendStep(const G4Step* aStep)
{
    //G4cout<<" astep volume "<<aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName()<<G4endl;
    fpPointsContainer->push_back(new HPGeTrajectoryPoint(aStep));
}

G4ParticleDefinition* HPGeTrajectory::GetParticleDefinition()
{
    return (G4ParticleTable::GetParticleTable()->FindParticle(ParticleName));
}

void HPGeTrajectory::MergeTrajectory(G4VTrajectory* secondTrajectory)
{
    if(!secondTrajectory) return;

    HPGeTrajectory* second = (HPGeTrajectory*)secondTrajectory;
    G4int ent = second->GetPointEntries();
    // initial point of the second trajectory should not be merged
    for(G4int i=1; i<ent; ++i) {
        fpPointsContainer->push_back((*(second->fpPointsContainer))[i]);
    }
    delete (*second->fpPointsContainer)[0];
    second->fpPointsContainer->clear();
}

const std::map<G4String,G4AttDef>* HPGeTrajectory::GetAttDefs() const
{
    G4bool isNew;
    std::map<G4String,G4AttDef>* store
        = G4AttDefStore::GetInstance("Trajectory",isNew);

    if (isNew) {

      G4String ID("ID");
      (*store)[ID] = G4AttDef(ID,"Track ID","Bookkeeping","","G4int");

      G4String PID("PID");
      (*store)[PID] = G4AttDef(PID,"Parent ID","Bookkeeping","","G4int");

      G4String PN("PN");
      (*store)[PN] = G4AttDef(PN,"Particle Name","Physics","","G4String");

      G4String Ch("Ch");
      (*store)[Ch] = G4AttDef(Ch,"Charge","Physics","e+","G4double");

      G4String PDG("PDG");
      (*store)[PDG] = G4AttDef(PDG,"PDG Encoding","Physics","","G4int");

      G4String IMom("IMom");
      (*store)[IMom] = G4AttDef(IMom,
                       "Momentum of track at start of trajectory",
                       "Physics","G4BestUnit","G4ThreeVector");

      G4String IMag("IMag");
      (*store)[IMag] = G4AttDef(IMag,
                       "Magnitude of momentum of track at start of trajectory",
                       "Physics","G4BestUnit","G4double");

        G4String NTP("NTP");
        (*store)[NTP] = G4AttDef(NTP,"No. of points","Bookkeeping","","G4int");

    }
    return store;
}

std::vector<G4AttValue>* HPGeTrajectory::CreateAttValues() const
{
  std::vector<G4AttValue>* values = new std::vector<G4AttValue>;

  values->push_back
    (G4AttValue("ID",G4UIcommand::ConvertToString(fTrackID),""));

  values->push_back
    (G4AttValue("PID",G4UIcommand::ConvertToString(fParentID),""));

  values->push_back(G4AttValue("PN",ParticleName,""));

  values->push_back
    (G4AttValue("Ch",G4UIcommand::ConvertToString(PDGCharge),""));

  values->push_back
    (G4AttValue("PDG",G4UIcommand::ConvertToString(PDGEncoding),""));

  values->push_back
    (G4AttValue("IMom",G4BestUnit(initialMomentum,"Energy"),""));

  values->push_back
    (G4AttValue("IMag",G4BestUnit(initialMomentum.mag(),"Energy"),""));

  values->push_back
    (G4AttValue("NTP",G4UIcommand::ConvertToString(GetPointEntries()),""));

#ifdef G4ATTDEBUG
  G4cout << G4AttCheck(values,GetAttDefs());
#endif
    return values;
}
