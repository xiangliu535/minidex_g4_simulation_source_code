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
//

/*
update 2020.05.16 add the following variables for trajectory:

initialKinenticEnergy
creatorprocess
creatorvolumename
creatorvertex_x y z

*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef HPGeTrajectory_h
#define HPGeTrajectory_h 1

#include <vector>
#include <stdlib.h>

#include "globals.hh"

#include "G4ios.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Allocator.hh"
#include "G4VTrajectory.hh"
#include "G4ParticleDefinition.hh" 
#include "G4TrajectoryPoint.hh"
#include <G4VProcess.hh>

#include "HPGeTrajectoryPoint.hh"

//typedef std::vector<G4VTrajectoryPoint*> TrajectoryPointContainer;
typedef std::vector<HPGeTrajectoryPoint*> TrajectoryPointContainer;

class HPGeTrajectory : public G4VTrajectory
{

//--------
   public: // without description
//--------

// Constructor/Destructor

     HPGeTrajectory();
     HPGeTrajectory(const G4Track* aTrack);
     HPGeTrajectory(HPGeTrajectory &);
     virtual ~HPGeTrajectory();

// Operators

     inline void* operator new(size_t);
     inline void  operator delete(void*);
     inline int operator == (const HPGeTrajectory& right) const
     { return (this==&right); }

// Get/Set functions 

     inline G4int GetTrackID() const { return fTrackID; }
     inline G4int GetParentID() const { return fParentID; }
     inline G4String GetParticleName() const { return ParticleName; }
     inline G4double GetCharge() const { return PDGCharge; }
     inline G4int GetPDGEncoding() const { return PDGEncoding; }
     inline G4ThreeVector GetInitialMomentum() const { return initialMomentum; }
     inline G4double GetInitialKineticEnergy() const { return initialKineticEnergy; }
     inline G4String GetCreatorVolumeName()  const { return CreatorVolumeName; }
     inline G4String GetCreatorProcessName() const { return CreatorProcessName; }
     inline G4ThreeVector GetCreatorPosition() const { return CreatorPosition; }

// Other member functions

     virtual void ShowTrajectory(std::ostream& os=G4cout) const;
     virtual void DrawTrajectory(G4int i_mode=0) const;
     virtual void AppendStep(const G4Step* aStep);
     virtual void MergeTrajectory(G4VTrajectory* secondTrajectory);

     G4ParticleDefinition* GetParticleDefinition();

     virtual int GetPointEntries() const 
     { return fpPointsContainer->size(); }
     virtual G4VTrajectoryPoint* GetPoint(G4int i) const
     { return (*fpPointsContainer)[i]; }

    virtual const std::map<G4String,G4AttDef>* GetAttDefs() const;
    virtual std::vector<G4AttValue>* CreateAttValues() const;

//---------
   private:
//---------

// Member data

     TrajectoryPointContainer* fpPointsContainer;

     G4int fTrackID;
     G4int fParentID;
     G4double PDGCharge;
     G4int    PDGEncoding;
     G4String ParticleName;
     G4ThreeVector initialMomentum;
     G4double      initialKineticEnergy;
     G4String      CreatorVolumeName;
     G4String      CreatorProcessName;
     G4ThreeVector CreatorPosition;
 
};

#if defined G4TRACKING_ALLOC_EXPORT
  extern G4DLLEXPORT G4Allocator<HPGeTrajectory> aTrajectoryAllocator;
#else
  extern G4DLLIMPORT G4Allocator<HPGeTrajectory> aTrajectoryAllocator;
#endif

inline void* HPGeTrajectory::operator new(size_t) {
    void* aTrajectory = (void*) aTrajectoryAllocator.MallocSingle();
    return aTrajectory;
}

inline void HPGeTrajectory::operator delete(void* aTrajectory) {
    aTrajectoryAllocator.FreeSingle((HPGeTrajectory*)aTrajectory);
}

#endif
