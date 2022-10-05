#ifndef __XENON10PEVENTDATA_H__
#define __XENON10PEVENTDATA_H__


//---------------------------------------------------------------------------//
/**
 * AUTHOR:  Xiang Liu
 * CONTACT:
 * FIRST SUBMISSION:
 * 
 * REVISION:
added the process id for each trajectory point
--->>> not necessary any more, save process name as string <<<---
initstep              0
LowEnRayleigh         1
LowEnPhotoElec        2
LowEnergyIoni         3
LowEnCompton          4
LowEnBrem             5
hLowEIoni             6
RadioactiveDecay      7
Transportation        8
unknown              -1
 * Feb-07-2005, X. Liu, added particle mass, lepton and baryon numbers
 *  05-09-2006, X. Liu, added more physics processes
msc                     9
eIoni                   10
eBrem                   11
annihil                 12
SynRad                  13
PositronNuclear         14
ElectroNuclear          15
LowEnConversion         16
PhotonInelastic         17
muIoni                  18
muBrems                 19
muPairProd              20
muMinusCaptureAtRest    21
hIoni                   22
Decay                   23
muNuclear               24
LElastic                25
AlphaInelastic          26
AntiNeutronInelastic    27
AntiNeutronAnnihilationAtRest   28
AntiProtonInelastic     29
AntiProtonAnnihilationAtRest    30
DeuteronInelastic       31
KaonPlusInelastic       32
KaonMinusInelastic      33
KaonMinusAbsorptionAtRest       34
KaonZeroLInelastic      35
KaonZeroSInelastic      36
NeutronInelastic        37
LCapture                38
PionPlusInelastic       39
PionMinusInelastic      40
PiMinusAbsorptionAtRest 41
ProtonInelastic         42
TritonInelastic         43

update 2022.09.22, to save hpgeevt and scinevt, at least one scintillator (HPGe) must have energy above 500keV.
*/

#include <string>
#include <vector>
#include <globals.hh>
#include <TMath.h>


using std::string;
using std::vector;

class HPGeEventData
{
public:
	 HPGeEventData();
	~HPGeEventData();

public:
	void Clear();

public:

  // switch to turn on trajectory storage
  bool NeedTrajectoryInformation;

  // variables to be saved to ntuples
  int    eventnumber;

  // list of primary vertexes with their position and time
  //  and how many particles are generated at these primary vertexes
  vector<float> *vertex_xpos;
  vector<float> *vertex_ypos;
  vector<float> *vertex_zpos;
  vector<float> *vertex_time;
  vector<int>   *vertex_numparticle;
  vector<string>*vertex_volumename;

  // list of primary particles with their momentum and starting positions
  vector<int>    *mc_pdgcode;
  vector<string> *mc_particlename;
  int             mc_nvertex;
  vector<float>  *mc_px;
  vector<float>  *mc_py;
  vector<float>  *mc_pz;
  vector<float>  *mc_ke; // kinetic energy
  vector<float>  *mc_mass;

  // mother nuclei charge and baryon number
  float  nuclei_baryonnumber;
  float  nuclei_charge;

  // total energy deposit in HPGes and in Scintillators
  double hpge_tote[2];
  double hpge_time[2];
  double scintillator_tote[18];
  double scintillator_time[18];
  void  CalculateScintillatorHPGeEnergyAndTime();
  void  FindPrimaryMuonTagTypeID();

  // hits
  int    hits_totnum;
  double  hits_tote;
  vector<double> *hits_edep;
  vector<float> *hits_xpos;
  vector<float> *hits_ypos;
  vector<float> *hits_zpos;
  vector<double> *hits_time;
  vector<int>   *hits_trackid;
  vector<int>   *hits_trackpdg;
  vector<string>  *hits_particletype;
  vector<string>  *hits_parenttype;
  vector<string>  *hits_createprocess;
  vector<string>  *hits_depositingprocess;
  vector<string>  *hits_volumename;

  // after sorting hits in time cluster (100ns time window)
  vector<double>          *scinevt_time;
  vector<vector<double>*> *scinevt_edep;
  vector<vector<int>*>    *scinevt_id;
  int primary_muontag_typeid;
  int primary_muontag_index;
 //
  vector<double>          *hpgeevt_time;
  vector<vector<double>*> *hpgeevt_edep;
  vector<vector<int>*>    *hpgeevt_id;
 //
  // first step, separate scintillator hits and hpge hits
  vector<double> *scinevt_hits_edep;
  vector<double> *scinevt_hits_time;
  vector<int>    *scinevt_hits_volumeid;
  vector<double> *hpgeevt_hits_edep;
  vector<double> *hpgeevt_hits_time;
  vector<int>    *hpgeevt_hits_volumeid;

  // second step, pass these hits to buffer hits, and cluster them in time (30ns)
  void ClusterBufferHitsInTime();

  vector<double> *buffer_hits_time;
  vector<double> *buffer_hits_edep;
  vector<int>    *buffer_hits_volumeid;
  vector<int>    *buffer_hits_seedid;
  // what comes out of the time-clustering
  int  iflag_scintillator_hits; // 1 for scintillator 0 for hpge
  int  number_of_bufferevts;
  double bufferevt_edep[1000][18];
  double bufferevt_time[1000];
  // time seeds
  vector<double> *seed_time;
  vector<double> *seed_tote;
  vector<double> *seed_maxhite;
  // trajectories (including secondary) and their points
  int   trj_totnum;
  vector<int>   *trj_id;
  vector<int>   *trj_pid;
  vector<int>   *trj_pdgencode;
  vector<float> *trj_charge;
  vector<float> *trj_px; // initial momentum and kinetic energy
  vector<float> *trj_py;
  vector<float> *trj_pz;
  vector<float> *trj_ke;
  vector<float> *trj_x;  //vertex position
  vector<float> *trj_y;
  vector<float> *trj_z;
  vector<string> *trj_creatorvolumename;
  vector<string> *trj_creatorprocessname;
  vector<int>   *trj_npoints;
  vector<int>   *trj_istart;
  vector<int>   *trj_iend;
  vector<float> *trj_mass;
  vector<int>   *trj_leptonnumber;
  vector<int>   *trj_baryonnumber;
  vector<int>   *trj_pdgencoding;
  vector<int>   *trj_pdgcharge;
  vector<string>   *trj_particletype;

  // points of the trajectories
  int   trjp_totnum;
  vector<int>   *trjp_trjid;
  vector<float> *trjp_xpos;
  vector<float> *trjp_ypos;
  vector<float> *trjp_zpos;
  vector<float> *trjp_de;
  vector<float> *trjp_steplength;
  vector<string>   *trjp_processtype;
  vector<string>   *trjp_volumename;

};

#endif // __XENON10PEVENTDATA_H__
