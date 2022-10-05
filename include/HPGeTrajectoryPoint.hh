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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef HPGeTrajectoryPoint_h
#define HPGeTrajectoryPoint_h 1

#include "globals.hh"

#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4TrajectoryPoint.hh"

#include "G4StepStatus.hh"

class G4Track;
class G4Step;
class G4VProcess;

class HPGeTrajectoryPoint : public G4TrajectoryPoint {

//--------
  public: // without description
//--------

// Constructor/Destructor

    HPGeTrajectoryPoint();
    HPGeTrajectoryPoint(const G4Track* aTrack);
    HPGeTrajectoryPoint(const G4Step* aStep);
    HPGeTrajectoryPoint(const HPGeTrajectoryPoint &right);
    virtual ~HPGeTrajectoryPoint();

// Operators

    inline void *operator new(size_t);
    inline void operator delete(void *aTrajectoryPoint);
    inline int operator==(const HPGeTrajectoryPoint& right) const
    { return (this==&right); };

// Get/Set functions

    inline G4double GetTime() const { return fTime; };
    inline G4double GetEnergyLost() const { return fEdep; };
    inline G4double GetStepLength() const { return fStepLength; };
    inline const G4ThreeVector GetMomentum() const { return fMomentum; };
    inline const G4ThreeVector GetPosition() const { return fPosition; };
    inline G4StepStatus GetStepStatus() const { return fStepStatus; };
    inline G4String GetVolumeName() const { return fVolumeName; };
    inline G4String GetProcessName() const { return fProcessName; };

// Get method for HEPRep style attributes

   virtual const std::map<G4String,G4AttDef>* GetAttDefs() const;
   virtual std::vector<G4AttValue>* CreateAttValues() const;

//---------
  private:
//---------

// Member data

    G4double fTime;
    G4double         fEdep;
    G4double         fStepLength;
    G4ThreeVector fMomentum;
    G4ThreeVector fPosition;
    G4StepStatus fStepStatus;
    G4String fVolumeName;
    G4String fProcessName;


};

#if defined G4TRACKING_ALLOC_EXPORT
  extern G4DLLEXPORT G4Allocator<HPGeTrajectoryPoint> aTrajPointAllocator;
#else
  extern G4DLLIMPORT G4Allocator<HPGeTrajectoryPoint> aTrajPointAllocator;
#endif

inline void* HPGeTrajectoryPoint::operator new(size_t)
{
    void *aTrajectoryPoint = (void *) aTrajPointAllocator.MallocSingle();
    return aTrajectoryPoint;
}

inline void HPGeTrajectoryPoint::operator delete(void *aTrajectoryPoint)
{
    aTrajPointAllocator.FreeSingle(
        (HPGeTrajectoryPoint *) aTrajectoryPoint);
}

#endif
