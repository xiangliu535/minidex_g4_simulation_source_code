#include <G4SDManager.hh>
#include <G4Run.hh>
#include <G4Event.hh>
#include <G4HCofThisEvent.hh>
#include <G4TransportationManager.hh>
#include <G4VPhysicalVolume.hh>

#include <numeric>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TParameter.h>
#include <TInterpreter.h>

#include "HPGeDetectorConstruction.hh"
#include "HPGeHPGeHit.hh"
#include "HPGePrimaryGeneratorAction.hh"
#include "HPGeEventData.hh"
#include "HPGeTrajectory.hh"
#include "HPGeTrajectoryPoint.hh"

#include "HPGeAnalysisManager.hh"

using namespace CLHEP;

HPGeAnalysisManager::HPGeAnalysisManager(HPGePrimaryGeneratorAction *pPrimaryGeneratorAction)
{
	m_iHPGeHitsCollectionID = -1;

	m_hDataFilename = "events.root";

	m_pPrimaryGeneratorAction = pPrimaryGeneratorAction;

	m_pEventData = new HPGeEventData();

    NeedTrajectory = kFALSE;
    NeedTrajectoryPoint = kFALSE;
    //NeedTrajectory = kTRUE;
    //NeedTrajectoryPoint = kTRUE;
}

HPGeAnalysisManager::~HPGeAnalysisManager()
{
}

void
HPGeAnalysisManager::BeginOfRun(const G4Run *pRun)
{
	m_pTreeFile = new TFile(m_hDataFilename.c_str(), "RECREATE", "File containing event data for HPGe");
	m_pTree = new TTree("t1", "Tree containing event data for HPGe");

    gROOT->ProcessLine("#include <vector>");
    gInterpreter->GenerateDictionary("vector<vector<double>*>", "vector");
    gInterpreter->GenerateDictionary("vector<vector<float>*>" , "vector");
    gInterpreter->GenerateDictionary("vector<vector<int>*>"   , "vector");
    gROOT->SetStyle("Plain");


    // MC true vertex information
    m_pTree->Branch("eventnumber",       &m_pEventData->eventnumber);
    m_pTree->Branch("vertex_xpos",       &m_pEventData->vertex_xpos);
    m_pTree->Branch("vertex_ypos",       &m_pEventData->vertex_ypos);
    m_pTree->Branch("vertex_zpos",       &m_pEventData->vertex_zpos);
    m_pTree->Branch("vertex_time",       &m_pEventData->vertex_time);
    m_pTree->Branch("vertex_numpartilce",&m_pEventData->vertex_numparticle);
    m_pTree->Branch("vertex_volumename", &m_pEventData->vertex_volumename);

    // MC true primary particle information
    m_pTree->Branch("mc_pdgcode",     &m_pEventData->mc_pdgcode);
    m_pTree->Branch("mc_particlename",&m_pEventData->mc_particlename);
    m_pTree->Branch("mc_nvertex",  &m_pEventData->mc_nvertex);
    m_pTree->Branch("mc_px",&m_pEventData->mc_px);
    m_pTree->Branch("mc_py",&m_pEventData->mc_py);
    m_pTree->Branch("mc_pz",&m_pEventData->mc_pz);
    m_pTree->Branch("mc_ke",&m_pEventData->mc_ke);
    m_pTree->Branch("mc_mass",&m_pEventData->mc_mass);

/*
    // mother nuclei
    m_pTree->Branch("nuclei_baryonnumber",&m_pEventData->nuclei_baryonnumber);
    m_pTree->Branch("nuclei_charge",&m_pEventData->nuclei_charge);
*/
   // hpge and scintillator energies (sum of hits energies), 2-dim variable, NOT 2-dim vector yet
    m_pTree->Branch("hpge_tote",&m_pEventData->hpge_tote,"hpge_tote[2]/D");
    m_pTree->Branch("hpge_time",&m_pEventData->hpge_time,"hpge_time[2]/D");
    m_pTree->Branch("scintillator_tote",&m_pEventData->scintillator_tote,"scintillator_tote[18]/D");
    m_pTree->Branch("scintillator_time",&m_pEventData->scintillator_time,"scintillator_time[18]/D");
/*
    // hits in sensitive detectors
    m_pTree->Branch("hits_totnum",&m_pEventData->hits_totnum);
    m_pTree->Branch("hits_tote",  &m_pEventData->hits_tote);
    m_pTree->Branch("hits_edep",  &m_pEventData->hits_edep);
    m_pTree->Branch("hits_xpos",  &m_pEventData->hits_xpos);
    m_pTree->Branch("hits_ypos",  &m_pEventData->hits_ypos);
    m_pTree->Branch("hits_zpos",  &m_pEventData->hits_zpos);
    m_pTree->Branch("hits_time",  &m_pEventData->hits_time);
    m_pTree->Branch("hits_trackid",          &m_pEventData->hits_trackid);
    m_pTree->Branch("hits_trackpdg",         &m_pEventData->hits_trackpdg);
    m_pTree->Branch("hits_particletype",     &m_pEventData->hits_particletype);
    m_pTree->Branch("hits_parenttype",       &m_pEventData->hits_parenttype);
    m_pTree->Branch("hits_createprocess",    &m_pEventData->hits_createprocess);
    m_pTree->Branch("hits_depositingprocess",&m_pEventData->hits_depositingprocess);
    m_pTree->Branch("hits_volumename",       &m_pEventData->hits_volumename);
*/
   // hpgeevt and scinevt
    m_pTree->Branch("scinevt_time",&m_pEventData->scinevt_time);
    m_pTree->Branch("scinevt_edep",&m_pEventData->scinevt_edep);
    m_pTree->Branch("scinevt_id",  &m_pEventData->scinevt_id);
    m_pTree->Branch("hpgeevt_time",&m_pEventData->hpgeevt_time);
    m_pTree->Branch("hpgeevt_edep",&m_pEventData->hpgeevt_edep);
    m_pTree->Branch("hpgeevt_id",  &m_pEventData->hpgeevt_id);
    m_pTree->Branch("primary_muontag_typeid",  &m_pEventData->primary_muontag_typeid);
    m_pTree->Branch("primary_muontag_index",   &m_pEventData->primary_muontag_index );

    // trajectory and trajectory points
    if (NeedTrajectory) {
    m_pTree->Branch("trj_totnum",&m_pEventData->trj_totnum,"trj_totnum/I");
    m_pTree->Branch("trj_id","vector<int>",&m_pEventData->trj_id);
    m_pTree->Branch("trj_pid","vector<int>",&m_pEventData->trj_pid);
    m_pTree->Branch("trj_pdgencode","vector<int>",&m_pEventData->trj_pdgencode);
    m_pTree->Branch("trj_charge","vector<float>",&m_pEventData->trj_charge);
    m_pTree->Branch("trj_px","vector<float>",&m_pEventData->trj_px);
    m_pTree->Branch("trj_py","vector<float>",&m_pEventData->trj_py);
    m_pTree->Branch("trj_pz","vector<float>",&m_pEventData->trj_pz);
    m_pTree->Branch("trj_ke","vector<float>",&m_pEventData->trj_ke); // kinetic energy
    m_pTree->Branch("trj_x","vector<float>",&m_pEventData->trj_x);
    m_pTree->Branch("trj_y","vector<float>",&m_pEventData->trj_y);
    m_pTree->Branch("trj_z","vector<float>",&m_pEventData->trj_z);
    m_pTree->Branch("trj_creatorvolumename","vector<string>",&m_pEventData->trj_creatorvolumename);
    m_pTree->Branch("trj_creatorprocessname","vector<string>",&m_pEventData->trj_creatorprocessname);
    m_pTree->Branch("trj_npoints","vector<int>",&m_pEventData->trj_npoints);
    //m_pTree->Branch("trj_mass","vector<float>",&m_pEventData->trj_mass);
    //m_pTree->Branch("trj_leptonnumber","vector<int>",&m_pEventData->trj_leptonnumber);
    //m_pTree->Branch("trj_baryonnumber","vector<int>",&m_pEventData->trj_baryonnumber);
    m_pTree->Branch("trj_particletype","vector<string>",&m_pEventData->trj_particletype);
    m_pTree->Branch("trjp_totnum",&m_pEventData->trjp_totnum,"trjp_totnum/I");
   if (NeedTrajectoryPoint) {
    m_pTree->Branch("trj_istart","vector<int>",&m_pEventData->trj_istart);
    m_pTree->Branch("trj_iend","vector<int>",&m_pEventData->trj_iend);
    m_pTree->Branch("trjp_trjid","vector<int>",&m_pEventData->trjp_trjid);
    m_pTree->Branch("trjp_xpos","vector<float>",&m_pEventData->trjp_xpos);
    m_pTree->Branch("trjp_ypos","vector<float>",&m_pEventData->trjp_ypos);
    m_pTree->Branch("trjp_zpos","vector<float>",&m_pEventData->trjp_zpos);
    m_pTree->Branch("trjp_de","vector<float>",&m_pEventData->trjp_de);
    m_pTree->Branch("trjp_steplength","vector<float>",&m_pEventData->trjp_steplength);
    m_pTree->Branch("trjp_processtype","vector<string>",&m_pEventData->trjp_processtype);
    m_pTree->Branch("trjp_volumename","vector<string>",&m_pEventData->trjp_volumename);
   }
    }

	m_pTree->SetMaxTreeSize(10e11);
	m_pTree->AutoSave();

	m_pNbEventsToSimulateParameter = new TParameter<int>("nbevents", m_iNbEventsToSimulate);
	m_pNbEventsToSimulateParameter->Write();
}

void
HPGeAnalysisManager::EndOfRun(const G4Run *pRun)
{
	m_pTreeFile->Write();
	m_pTreeFile->Close();
}

void
HPGeAnalysisManager::BeginOfEvent(const G4Event *pEvent)
{
	if(m_iHPGeHitsCollectionID == -1)
	{
		G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
		m_iHPGeHitsCollectionID = pSDManager->GetCollectionID("HPGeHitsCollection");
	} 

}

void
HPGeAnalysisManager::WritePartialEvent(const G4Event *pEvent)
{
    FillHitsToNtuple(pEvent);
}

void
HPGeAnalysisManager::ResetPartialEvent(const G4Event *pEvent)
{

    G4int iNbHPGeHits=0;
    if(m_iHPGeHitsCollectionID == -1)
    {
        G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
        m_iHPGeHitsCollectionID = pSDManager->GetCollectionID("HPGeHitsCollection");
    }

    G4HCofThisEvent* pHCofThisEvent = pEvent->GetHCofThisEvent();
    HPGeHPGeHitsCollection* pHPGeHitsCollection = 0;
    if(pHCofThisEvent)
    {
        if(m_iHPGeHitsCollectionID != -1)
        {
            pHPGeHitsCollection = (HPGeHPGeHitsCollection *)(pHCofThisEvent->GetHC(m_iHPGeHitsCollectionID));
            iNbHPGeHits = (pHPGeHitsCollection)?(pHPGeHitsCollection->entries()):(0);
            //m_pEventData->hits_totnum = pHPGeHitsCollection->entries();
            for (int i=0; i<iNbHPGeHits; i++) delete (*pHPGeHitsCollection)[i];
            pHPGeHitsCollection->GetVector()->clear();
        }
    }

   pEvent->GetTrajectoryContainer()->clearAndDestroy();
   //m_pEventData->Clear();

}

void
HPGeAnalysisManager::EndOfEvent(const G4Event *pEvent)
{
    FillHitsToNtuple(pEvent);
}


void
HPGeAnalysisManager::FillHitsToNtuple(const G4Event *pEvent)
{
//---> primary vertex

	m_pEventData->eventnumber = pEvent->GetEventID();
    G4PrimaryParticle *primaryParticle;
    G4PrimaryVertex   *primaryVertex;
    G4Navigator *m_pNavigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
    G4ThreeVector m_hParticlePosition;
    for (G4int i=0; i<pEvent->GetNumberOfPrimaryVertex(); i++) {
       primaryVertex = pEvent->GetPrimaryVertex(i);
       m_pEventData->vertex_xpos->push_back(primaryVertex->GetX0()/mm);
       m_pEventData->vertex_ypos->push_back(primaryVertex->GetY0()/mm);
       m_pEventData->vertex_zpos->push_back(primaryVertex->GetZ0()/mm);
       m_pEventData->vertex_time->push_back(primaryVertex->GetT0()/ns);
       m_pEventData->vertex_numparticle->push_back(primaryVertex->GetNumberOfParticle());
//
       G4ThreeVector null(0., 0., 0.);
       G4ThreeVector *ptr;
       ptr = &null;
       G4VPhysicalVolume *theVolume = m_pNavigator->LocateGlobalPointAndSetup(
             G4ThreeVector(primaryVertex->GetX0(),
                           primaryVertex->GetY0(),
                           primaryVertex->GetZ0()), ptr, true);
       G4String theVolName = theVolume->GetName();
       m_pEventData->vertex_volumename->push_back(theVolName);
//
       for (G4int j=0; j<primaryVertex->GetNumberOfParticle(); j++) {
          primaryParticle = primaryVertex->GetPrimary(j);
          m_pEventData->mc_pdgcode->push_back(primaryParticle->GetPDGcode());
          m_pEventData->mc_particlename->push_back(primaryParticle->GetParticleDefinition()->GetParticleName());
          m_pEventData->mc_px->push_back(primaryParticle->GetPx()/keV);
          m_pEventData->mc_py->push_back(primaryParticle->GetPy()/keV);
          m_pEventData->mc_pz->push_back(primaryParticle->GetPz()/keV);
          m_pEventData->mc_ke->push_back(primaryParticle->GetKineticEnergy()/keV);
          m_pEventData->mc_mass->push_back(primaryParticle->GetMass()/keV);
          m_pEventData->mc_nvertex++;
       } 
    }

//---> hits in Germanium detector

    m_pEventData->hits_totnum=0;
	G4HCofThisEvent* pHCofThisEvent = pEvent->GetHCofThisEvent();
	HPGeHPGeHitsCollection* pHPGeHitsCollection = 0;
	if(pHCofThisEvent)
	{
		if(m_iHPGeHitsCollectionID != -1)
		{
			pHPGeHitsCollection = (HPGeHPGeHitsCollection *)(pHCofThisEvent->GetHC(m_iHPGeHitsCollectionID));
			//m_pEventData->hits_totnum = (pHPGeHitsCollection)?(pHPGeHitsCollection->entries()):(0);
			//m_pEventData->hits_totnum = pHPGeHitsCollection->entries();
		}
	}

   for (int icha=0; icha<2; icha++) m_pEventData->hpge_tote[icha]=0.0;
   for (int icha=0; icha<2; icha++) m_pEventData->hpge_time[icha]=0.0;
   for (int icha=0; icha<6; icha++) m_pEventData->scintillator_tote[icha]=0.0;
   for (int icha=0; icha<6; icha++) m_pEventData->scintillator_time[icha]=0.0;

    for (G4int i=0; i<pHPGeHitsCollection->entries(); i++) {
		HPGeHPGeHit *pHit = (*pHPGeHitsCollection)[i];
        m_pEventData->hits_tote += (pHit->GetEnergyDeposited()/keV);
      if (pHit->GetEnergyDeposited()>0.0) {  // save only hits with positive deposited energy above 1eV
      //if (  pHit->GetEnergyDeposited()>0.0
      //    &&pHit->GetTime()/ns>1.0e+9      ) {  // save only hits deposited within 1s (this function is applied already in HPGeSensitiveDetector
      // energy cut of >1keV is already applied in HPGeHPGeSensitiveDetector(), no time cut will be applied
        m_pEventData->hits_edep->push_back(pHit->GetEnergyDeposited()/keV);
        m_pEventData->hits_time->push_back(pHit->GetTime()/ns);
        m_pEventData->hits_xpos->push_back(pHit->GetPosition().x()/mm);
        m_pEventData->hits_ypos->push_back(pHit->GetPosition().y()/mm);
        m_pEventData->hits_zpos->push_back(pHit->GetPosition().z()/mm);
        m_pEventData->hits_trackid          ->push_back(pHit->GetTrackId()); 
        m_pEventData->hits_trackpdg         ->push_back(pHit->GetTrackPDG()); 
        m_pEventData->hits_particletype     ->push_back(pHit->GetParticleType()); 
        m_pEventData->hits_parenttype       ->push_back(pHit->GetParentType()); 
        m_pEventData->hits_createprocess    ->push_back(pHit->GetCreatorProcess()); 
        m_pEventData->hits_depositingprocess->push_back(pHit->GetDepositingProcess()); 
        m_pEventData->hits_volumename       ->push_back(pHit->GetVolumeName());
      }
    }
    m_pEventData->hits_totnum = m_pEventData->hits_edep->size();
//---> trajectory and trajectory point information
    if (NeedTrajectory) {
    m_pEventData->trj_totnum=0;
    G4TrajectoryContainer* trajectoryContainer = pEvent->GetTrajectoryContainer();
    if (trajectoryContainer) m_pEventData->trj_totnum = trajectoryContainer->entries();
    //G4cout<<" this event has "<<m_pEventData->trj_totnum<<" trajectories"<<G4endl;
    m_pEventData->trjp_totnum=0;
    G4int itemp_trjp_totnum=0;
    //---> locate the mu- or mu+ TrackID
    int primary_muon_trackid=-1;
    int itemp_index=0;
    while (primary_muon_trackid<0) {
      HPGeTrajectory* trj = (HPGeTrajectory*)
         ((*(pEvent->GetTrajectoryContainer()))[itemp_index]);
      if ( (   trj->GetParticleName().find("mu-") != std::string::npos
            || trj->GetParticleName().find("mu+") != std::string::npos )
           &&  trj->GetParentID()==0 )
          primary_muon_trackid = trj->GetTrackID();
      itemp_index++;
      if (itemp_index>=m_pEventData->trj_totnum) primary_muon_trackid=0; 
    }

  for (G4int i=0; i<m_pEventData->trj_totnum; i++) {
    HPGeTrajectory* trj = (HPGeTrajectory*)
         ((*(pEvent->GetTrajectoryContainer()))[i]);
//---> only the following trajectories with their trajectory points will be saved
//        || trj->GetParentID()==primary_muon_trackid // direct daugher of primary mu- or mu+
   if (    trj->GetParentID()==0  // primary particles, include input-level secondaries from FLUKA
        || trj->GetParticleName().find("neutron") != std::string::npos ) {
    m_pEventData->trj_id->push_back(trj->GetTrackID());
    m_pEventData->trj_pid->push_back(trj->GetParentID());
    m_pEventData->trj_pdgencode->push_back(trj->GetPDGEncoding());
    m_pEventData->trj_charge->push_back(trj->GetCharge());
    m_pEventData->trj_px->push_back(trj->GetInitialMomentum().x()/keV);
    m_pEventData->trj_py->push_back(trj->GetInitialMomentum().y()/keV);
    m_pEventData->trj_pz->push_back(trj->GetInitialMomentum().z()/keV);
    m_pEventData->trj_ke->push_back(trj->GetInitialKineticEnergy()/keV);
    m_pEventData->trj_x->push_back(trj->GetCreatorPosition().x()/mm);
    m_pEventData->trj_y->push_back(trj->GetCreatorPosition().y()/mm);
    m_pEventData->trj_z->push_back(trj->GetCreatorPosition().z()/mm);
    m_pEventData->trj_creatorvolumename ->push_back(trj->GetCreatorVolumeName());
    m_pEventData->trj_creatorprocessname->push_back(trj->GetCreatorProcessName());
    //m_pEventData->trj_mass->push_back(trj->GetMass()/keV);
    //m_pEventData->trj_leptonnumber->push_back(trj->GetLeptonNumber());
    //m_pEventData->trj_baryonnumber->push_back(trj->GetBaryonNumber());
    m_pEventData->trj_particletype->push_back(trj->GetParticleName());

    m_pEventData->trj_npoints->push_back(trj->GetPointEntries());

   if (NeedTrajectoryPoint) {
    m_pEventData->trj_istart->push_back(itemp_trjp_totnum);
    itemp_trjp_totnum+=trj->GetPointEntries();
    m_pEventData->trj_iend->push_back(itemp_trjp_totnum-1);

    for (G4int j=0; j<trj->GetPointEntries(); j++) {
      HPGeTrajectoryPoint* trjp = (HPGeTrajectoryPoint*)(trj->GetPoint(j));
   //   G4int jj=j+itemp_trjp_totnum;
      m_pEventData->trjp_trjid->push_back(trj->GetTrackID());
      m_pEventData->trjp_xpos->push_back(trjp->GetPosition().x()/mm);
      m_pEventData->trjp_ypos->push_back(trjp->GetPosition().y()/mm);
      m_pEventData->trjp_zpos->push_back(trjp->GetPosition().z()/mm);
      m_pEventData->trjp_de->push_back(trjp->GetEnergyLost()/keV);
      m_pEventData->trjp_steplength->push_back(trjp->GetStepLength()/mm);
      m_pEventData->trjp_volumename->push_back(trjp->GetVolumeName());
      m_pEventData->trjp_processtype->push_back(trjp->GetProcessName());
    }
   }
   } // end of if loop
  } // end of looping over all Trajectory
  m_pEventData->trjp_totnum=itemp_trjp_totnum;
  }

  if(m_pEventData->hits_tote > 500. )
    m_pEventData->CalculateScintillatorHPGeEnergyAndTime();

  //if(m_pEventData->hits_tote > 0. )
  //if(m_pEventData->number_of_scinevts > 0)
  if(m_pEventData->hits_tote > 500. ) {
    m_pEventData->FindPrimaryMuonTagTypeID();
    if (m_pEventData->primary_muontag_typeid>=0) m_pTree->Fill();
  }

  m_pEventData->Clear();

}

/*
void 
HPGeAnalysisManager::SaveBremsstrahlungGamma(G4float px, G4float py, G4float pz)
{
//---> save px py pz to ntuple
}
*/

void
HPGeAnalysisManager::Step(const G4Step *pStep)
{

}

