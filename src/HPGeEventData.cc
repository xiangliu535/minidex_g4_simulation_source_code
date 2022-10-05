#include "HPGeEventData.hh"

HPGeEventData::HPGeEventData()
{
    NeedTrajectoryInformation=true;
    vertex_xpos = new vector<float>;
    vertex_ypos = new vector<float>;
    vertex_zpos = new vector<float>;
    vertex_time = new vector<float>;
    vertex_numparticle = new vector<int>;
    vertex_volumename  = new vector<string>;

    mc_pdgcode = new vector<int>;
    mc_particlename    = new vector<string>;
    mc_nvertex   = 0;
    mc_px = new vector<float>;
    mc_py = new vector<float>;
    mc_pz = new vector<float>;
    mc_ke = new vector<float>;
    mc_mass = new vector<float>;

    nuclei_baryonnumber=0;
    nuclei_charge=0;

    for (int icha=0; icha<2; icha++) {
      hpge_tote[icha]=0.0;
      hpge_time[icha]=0.0;
    }
    for (int icha=0; icha<18; icha++) {
      scintillator_tote[icha]=0.0;
      scintillator_time[icha]=0.0;
    }

    hits_totnum=0;
    hits_tote  =0.0;
    hits_edep = new vector<double>;
    hits_xpos = new vector<float>;
    hits_ypos = new vector<float>;
    hits_zpos = new vector<float>;
    hits_time = new vector<double>;
    hits_trackid  = new vector<int>;
    hits_trackpdg = new vector<int>;
    hits_particletype = new vector<string>;
    hits_parenttype = new vector<string>;
    hits_createprocess = new vector<string>;
    hits_depositingprocess = new vector<string>;
    hits_volumename = new vector<string>;

    scinevt_time = new vector<double>;
    scinevt_edep = new vector<vector<double>*>;
    scinevt_id   = new vector<vector<int>*>;
    primary_muontag_typeid=-1;
    primary_muontag_index =-1;
    hpgeevt_time = new vector<double>;
    hpgeevt_edep = new vector<vector<double>*>;
    hpgeevt_id   = new vector<vector<int>*>;

   scinevt_hits_edep = new vector<double>;
   scinevt_hits_time = new vector<double>;
   scinevt_hits_volumeid = new vector<int>;
   hpgeevt_hits_edep = new vector<double>;
   hpgeevt_hits_time = new vector<double>;
   hpgeevt_hits_volumeid = new vector<int>;

   buffer_hits_time = new vector<double>;
   buffer_hits_edep = new vector<double>;
   buffer_hits_seedid = new vector<int>;
   buffer_hits_volumeid = new vector<int>;

   seed_time = new vector<double>;
   seed_tote = new vector<double>;
   seed_maxhite = new vector<double>;

    trj_totnum=0;
    trj_id = new vector<int>;
    trj_pid = new vector<int>;
    trj_pdgencode = new vector<int>;
    trj_charge    = new vector<float>;
    trj_px        = new vector<float>;
    trj_py        = new vector<float>;
    trj_pz        = new vector<float>;
    trj_ke        = new vector<float>;
    trj_x         = new vector<float>;
    trj_y         = new vector<float>;
    trj_z         = new vector<float>;
    trj_creatorvolumename     = new vector<string>;
    trj_creatorprocessname    = new vector<string>;
    trj_npoints   = new vector<int>;
    trj_istart    = new vector<int>;
    trj_iend      = new vector<int>;
    trj_mass      = new vector<float>;
    trj_leptonnumber   = new vector<int>;
    trj_baryonnumber   = new vector<int>;
    trj_particletype   = new vector<string>;

    trjp_totnum=0;
    trjp_trjid= new vector<int>;
    trjp_xpos = new vector<float>;
    trjp_ypos = new vector<float>;
    trjp_zpos = new vector<float>;
    trjp_de   = new vector<float>;
    trjp_steplength   = new vector<float>;
    trjp_processtype  = new vector<string>;
    trjp_volumename   = new vector<string>;

}

HPGeEventData::~HPGeEventData()
{
    delete vertex_xpos;
    delete vertex_ypos;
    delete vertex_zpos;
    delete vertex_time;
    delete vertex_numparticle;
    delete vertex_volumename;

    delete mc_pdgcode;
    delete mc_particlename;
    delete mc_px;
    delete mc_py;
    delete mc_pz;
    delete mc_ke;
    delete mc_mass;

    delete hits_edep;
    delete hits_xpos;
    delete hits_ypos;
    delete hits_zpos;
    delete hits_time;
    delete hits_trackid;
    delete hits_trackpdg;
    delete hits_particletype;
    delete hits_parenttype;
    delete hits_createprocess;
    delete hits_depositingprocess;
    delete hits_volumename;

    for (int i=0; i<scinevt_edep->size(); i++) delete (*scinevt_edep)[i];
    for (int i=0; i<scinevt_id  ->size(); i++) delete (*scinevt_id)  [i];
    for (int i=0; i<hpgeevt_edep->size(); i++) delete (*hpgeevt_edep)[i];
    for (int i=0; i<hpgeevt_id  ->size(); i++) delete (*hpgeevt_id)  [i];
    delete scinevt_time;
    delete scinevt_edep;
    delete scinevt_id;
    delete hpgeevt_time;
    delete hpgeevt_edep;
    delete hpgeevt_id;

    delete scinevt_hits_edep;
    delete scinevt_hits_time;
    delete scinevt_hits_volumeid;
    delete hpgeevt_hits_edep;
    delete hpgeevt_hits_time;
    delete hpgeevt_hits_volumeid;

    delete buffer_hits_time;
    delete buffer_hits_edep;
    delete buffer_hits_seedid;
    delete buffer_hits_volumeid;

    delete seed_time;
    delete seed_tote;
    delete seed_maxhite;

    delete trj_id;
    delete trj_pid;
    delete trj_pdgencode;
    delete trj_particletype;
    delete trj_charge;
    delete trj_px;
    delete trj_py;
    delete trj_pz;
    delete trj_ke;
    delete trj_x;
    delete trj_y;
    delete trj_z;
    delete trj_creatorvolumename;
    delete trj_creatorprocessname;
    delete trj_npoints;
    delete trj_istart;
    delete trj_mass;
    delete trj_leptonnumber;
    delete trj_baryonnumber;

    delete trjp_trjid;
    delete trjp_xpos;
    delete trjp_ypos;
    delete trjp_zpos;
    delete trjp_de;
    delete trjp_steplength;
    delete trjp_processtype;
    delete trjp_volumename;

}

void
HPGeEventData::Clear()
{
    eventnumber=0;
    NeedTrajectoryInformation=true;
    hits_totnum=0;
    hits_tote=0.0;
    trj_totnum=0;
    trjp_totnum=0;

     vertex_xpos->clear();
     vertex_ypos->clear();
     vertex_zpos->clear();
     vertex_time->clear();
     vertex_numparticle->clear();
     vertex_volumename ->clear();

     mc_pdgcode->clear();
     mc_particlename->clear();
     mc_nvertex=0;
     mc_px->clear();
     mc_py->clear();
     mc_pz->clear();
     mc_ke->clear();
     mc_mass->clear();

   for (int icha=0; icha<2; icha++) {
       hpge_tote[icha]=0.0;
       hpge_time[icha]=0.0;
    }
    for (int icha=0; icha<18; icha++) {
       scintillator_tote[icha]=0.0;
       scintillator_time[icha]=0.0;
    }

     hits_edep->clear();
     hits_xpos->clear();
     hits_ypos->clear();
     hits_zpos->clear();
     hits_time->clear();
     hits_trackid->clear();
     hits_trackpdg->clear();
     hits_particletype->clear();
     hits_parenttype->clear();
     hits_createprocess->clear();
     hits_depositingprocess->clear();
     hits_volumename->clear();

//---> must be very careful in cleaning multi-dimensional vectors
     scinevt_time->clear();
    for (int i=0; i<scinevt_edep->size(); i++) delete (*scinevt_edep)[i];
    for (int i=0; i<scinevt_id->size(); i++) delete (*scinevt_id)[i];
     scinevt_edep->clear();
     scinevt_id  ->clear();
     hpgeevt_time->clear();
    for (int i=0; i<hpgeevt_edep->size(); i++) delete (*hpgeevt_edep)[i];
    for (int i=0; i<hpgeevt_id->size(); i++) delete (*hpgeevt_id)[i];
     hpgeevt_edep->clear();
     hpgeevt_id  ->clear();
     primary_muontag_typeid=-1;
     primary_muontag_index =-1;

     scinevt_hits_edep->clear();
     scinevt_hits_time->clear();
     scinevt_hits_volumeid->clear();
     hpgeevt_hits_edep->clear();
     hpgeevt_hits_time->clear();
     hpgeevt_hits_volumeid->clear();

     buffer_hits_time->clear();
     buffer_hits_edep->clear();
     buffer_hits_volumeid->clear();
     buffer_hits_seedid->clear();

     number_of_bufferevts=0;
     for (int ievt=0; ievt<1000; ievt++) {
       bufferevt_time[ievt]=0.0;
       for (int j=0; j<6; j++) {
         bufferevt_edep[ievt][j]=0.0;
       }
     }

     seed_time->clear();
     seed_tote->clear();
     seed_maxhite->clear();


     trj_id->clear();
     trj_pid->clear();
     trj_pdgencode->clear();
     trj_charge->clear();
     trj_px->clear();
     trj_py->clear();
     trj_pz->clear();
     trj_ke->clear();
     trj_x->clear();
     trj_y->clear();
     trj_z->clear();
     trj_creatorvolumename->clear();
     trj_creatorprocessname->clear();
     trj_npoints->clear();
     trj_istart->clear();
     trj_iend->clear();
     trj_mass->clear();
     trj_leptonnumber->clear();
     trj_baryonnumber->clear();
     trj_particletype->clear();

     trjp_trjid->clear();
     trjp_xpos->clear();
     trjp_ypos->clear();
     trjp_zpos->clear();
     trjp_de->clear();
     trjp_steplength->clear();
     trjp_processtype->clear();
     trjp_volumename->clear();
}

void HPGeEventData::CalculateScintillatorHPGeEnergyAndTime()
{
    int index_scintillator;
    int index_hpge;
    float component_scintillator_energy_threshold=500.0; // unit keV
    float component_hpge_energy_threshold=5.0; // unit keV
    bool at_least_one_component_energy_above_threshold;
  //--> first clear up
    for (int icha=0; icha<2; icha++) {
       hpge_tote[icha]=0.0;
       hpge_time[icha]=0.0;
    }
    for (int icha=0; icha<18; icha++) {
       scintillator_tote[icha]=0.0;
       scintillator_time[icha]=0.0;
    }
     scinevt_hits_edep  ->clear();
     scinevt_hits_time  ->clear();
     scinevt_hits_volumeid->clear();
   //
     hpgeevt_hits_edep  ->clear();
     hpgeevt_hits_time  ->clear();
     hpgeevt_hits_volumeid->clear();
   //
   //--> second loop over all hits and sort them according to scintillator or hpge hits
    for (int ihit=0; ihit<hits_totnum; ihit++) {
       // hits with energy eV or below are not processed (in simulation there are many hits with e-05 eV energy) (why???)
       // if ((*hits_edep)[ihit]<=0.001) continue; // this cut is already applied in HPGeAnalysisManager::FillHitsToNtuple(const G4Event *pEvent)
        index_scintillator=-1;
        index_hpge=-1;
        if      ((*hits_volumename)[ihit].find("Sensitive_Scint_BigTop")     != std::string::npos) index_scintillator=0;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_BigBottom")  != std::string::npos) index_scintillator=1;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_Small1")     != std::string::npos) index_scintillator=2;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_Small2")     != std::string::npos) index_scintillator=3;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_Small3")     != std::string::npos) index_scintillator=4;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_Small4")     != std::string::npos) index_scintillator=5;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_BigSide1")   != std::string::npos) index_scintillator=6;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_BigSide2")   != std::string::npos) index_scintillator=7;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_SmallSide1") != std::string::npos) index_scintillator=8;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_SmallSide2") != std::string::npos) index_scintillator=9;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_SmallSide3") != std::string::npos) index_scintillator=10;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_SmallSide4") != std::string::npos) index_scintillator=11;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_BottomSide1")!= std::string::npos) index_scintillator=12;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_BottomSide2")!= std::string::npos) index_scintillator=13;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_BottomBack") != std::string::npos) index_scintillator=14;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_BottomFront")!= std::string::npos) index_scintillator=15;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_Extra1")     != std::string::npos) index_scintillator=16;
        else if ((*hits_volumename)[ihit].find("Sensitive_Scint_Extra2")     != std::string::npos) index_scintillator=17;
        else if ((*hits_volumename)[ihit].find("XtRaA_SensitiveCrystal")     != std::string::npos) index_hpge=0;
        else if ((*hits_volumename)[ihit].find("XtRaB_SensitiveCrystal")     != std::string::npos) index_hpge=1;
        if (index_scintillator>=0) {
           scinevt_hits_edep    ->push_back((*hits_edep)[ihit]);
           scinevt_hits_time    ->push_back((*hits_time)[ihit]);
           scinevt_hits_volumeid->push_back(index_scintillator);
        }
        if (index_hpge>=0) {
           hpgeevt_hits_edep    ->push_back((*hits_edep)[ihit]);
           hpgeevt_hits_time    ->push_back((*hits_time)[ihit]);
           hpgeevt_hits_volumeid->push_back(index_hpge);
        }
   //--> gross scintillator and hpge energy and time without time-clustering
        if (index_scintillator>=0) {
           scintillator_tote[index_scintillator]+=(*hits_edep)[ihit];
           scintillator_time[index_scintillator]+=(*hits_edep)[ihit]*(*hits_time)[ihit];
        }
        else if (index_hpge>=0) {
           hpge_tote[index_hpge]+=(*hits_edep)[ihit];
           hpge_time[index_hpge]+=(*hits_edep)[ihit]*(*hits_time)[ihit];
        }
    }
   //--> gross scintillator and hpge energy and time without time-clustering
    for (int iscin=0; iscin<18; iscin++) {
      if (scintillator_tote[iscin]>0.0)
          scintillator_time[iscin]=scintillator_time[iscin]/scintillator_tote[iscin];
    }
    for (int ihpge=0; ihpge<2; ihpge++) {
      if (hpge_tote[ihpge]>0.0)
          hpge_time[ihpge]=hpge_time[ihpge]/hpge_tote[ihpge];
    }
    //G4cout<<" finished with gross calculation, now time clustering"<<G4endl;
   //--> pass scintillator hits to buffer hits, do the clustering, pass the clustered events back to ntuple variables
     buffer_hits_time    ->clear();
     buffer_hits_edep    ->clear();
     buffer_hits_volumeid->clear();
     buffer_hits_seedid  ->clear();
     iflag_scintillator_hits=1;
    for (int ihit=0; ihit<scinevt_hits_edep->size(); ihit++) {
      buffer_hits_time    ->push_back((*scinevt_hits_time)[ihit]);
      buffer_hits_edep    ->push_back((*scinevt_hits_edep)[ihit]);
      buffer_hits_volumeid->push_back((*scinevt_hits_volumeid)[ihit]);
      buffer_hits_seedid  ->push_back(-1);
    }
    ClusterBufferHitsInTime();
  //---> 2022.09.22, save events when at least one component with energy above 500 keV
    for (int ievt=0; ievt<number_of_bufferevts; ievt++) {
      at_least_one_component_energy_above_threshold=kFALSE;
      for (int icomp=0;icomp<18;icomp++) {
       if (bufferevt_edep[ievt][icomp]>component_scintillator_energy_threshold)
          at_least_one_component_energy_above_threshold=kTRUE;
      }
      if (at_least_one_component_energy_above_threshold) {
       scinevt_time->push_back(bufferevt_time[ievt]);
       vector<int>    *temp_id   = new vector<int>;
       vector<double> *temp_edep = new vector<double>;
       for (int ich=0; ich<18; ich++) {
         if (bufferevt_edep[ievt][ich]>0.0) {
           temp_id  ->push_back(ich);
           temp_edep->push_back(bufferevt_edep[ievt][ich]);
         }
       }
       scinevt_edep->push_back(temp_edep);
       scinevt_id  ->push_back(temp_id  );
      }
    }
   //--> pass hpge hits to buffer hits, do the clustering, pass the clustered events back to ntuple variables
     buffer_hits_time    ->clear();
     buffer_hits_edep    ->clear();
     buffer_hits_volumeid->clear();
     buffer_hits_seedid  ->clear();
     iflag_scintillator_hits=0;
    for (int ihit=0; ihit<hpgeevt_hits_edep->size(); ihit++) {
      buffer_hits_time    ->push_back((*hpgeevt_hits_time)[ihit]);
      buffer_hits_edep    ->push_back((*hpgeevt_hits_edep)[ihit]);
      buffer_hits_volumeid->push_back((*hpgeevt_hits_volumeid)[ihit]);
      buffer_hits_seedid  ->push_back(-1);
    }
    ClusterBufferHitsInTime();
  //---> 2022.09.22, save events when at least one component with energy above 500 keV
    for (int ievt=0; ievt<number_of_bufferevts; ievt++) {
      at_least_one_component_energy_above_threshold=kFALSE;
      for (int icomp=0;icomp<18;icomp++) {
       if (bufferevt_edep[ievt][icomp]>component_hpge_energy_threshold)
          at_least_one_component_energy_above_threshold=kTRUE;
      }   
      if (at_least_one_component_energy_above_threshold) {
       hpgeevt_time->push_back(bufferevt_time[ievt]);
       vector<int>    *temp_id   = new vector<int>;
       vector<double> *temp_edep = new vector<double>;
       for (int ich=0; ich<18; ich++) {
         if (bufferevt_edep[ievt][ich]>0.0) {
           temp_id  ->push_back(ich);
           temp_edep->push_back(bufferevt_edep[ievt][ich]);
         }
       }
       hpgeevt_edep->push_back(temp_edep);
       hpgeevt_id  ->push_back(temp_id  );
      }
    }
    return;
}

void HPGeEventData::ClusterBufferHitsInTime()
{
 //--->  this macro assumes that the hits information are already put in the buffer_hits vector variables
//       and all buffer_hits_seedid are set to -1
    seed_time   ->clear();
    seed_tote   ->clear();
    seed_maxhite->clear();
    double time_cluster_window_size=100.0; //unit ns
  //--> first loop over all hits, assign them to seed_time, if no match, create a new seed_time
    for (int ihit=0; ihit<buffer_hits_time->size(); ihit++) {
       bool found_time_seed=kFALSE;
       int  time_seed_index=0;
       while (time_seed_index<seed_time->size()) {
           if ( TMath::Abs((*buffer_hits_time)[ihit]-(*seed_time)[time_seed_index])<time_cluster_window_size ) {
               found_time_seed=kTRUE;
               (*buffer_hits_seedid)[ihit]=time_seed_index;
               (*seed_tote)[time_seed_index]+=(*buffer_hits_edep)[ihit];
//---> before, recalculate seed_time, even long double is NOT enough for long half-life time (Co60)
//     now, the seed time is simply updated by the time from the hit with the by-far largest energy 
               if ((*buffer_hits_edep)[ihit]>(*seed_maxhite)[time_seed_index]) {
                  (*seed_time)   [time_seed_index]=(*buffer_hits_time)[ihit];
                  (*seed_maxhite)[time_seed_index]=(*buffer_hits_edep)[ihit];
               }
/*
              //--> recalculate seed energy-weighted time
               long double temp_time_tag=( (*seed_time)[time_seed_index] * (*seed_tote)[time_seed_index]
                                         +(*buffer_hits_time)[ihit]     * (*buffer_hits_edep)[ihit] )
                                         /((*seed_tote)[time_seed_index]+(*buffer_hits_edep)[ihit]);
               (*seed_tote)[time_seed_index]+=(*buffer_hits_edep)[ihit];
               (*seed_time)[time_seed_index]=double(temp_time_tag);
*/
               break;  // no need to search more seeds
            }
            time_seed_index++;
       }
       if (!found_time_seed) {
          seed_time   ->push_back((*buffer_hits_time)[ihit]);
          seed_tote   ->push_back((*buffer_hits_edep)[ihit]);
          seed_maxhite->push_back((*buffer_hits_edep)[ihit]);
          (*buffer_hits_seedid)[ihit]=seed_time->size()-1;
       }
    } // end for looping over all hits
  //--> second, clear up all bufferevt variables;
    for (int ievt=0; ievt<1000; ievt++) {
       bufferevt_time[ievt]=0.0;
       for (int i=0; i<18; i++) bufferevt_edep[ievt][i]=0.0;
    }
  //--> third, add up hits from the same time seed to bufferevt variables, using buffer_hits_volumeid
  // protection of bufferevt_edep and _time maximum size
    number_of_bufferevts=seed_time->size();
    if (number_of_bufferevts>=1000) number_of_bufferevts=1000;
    for (int ihit=0; ihit<buffer_hits_time->size(); ihit++) {
      if (    (*buffer_hits_seedid)[ihit]<1000
           && (*buffer_hits_volumeid)[ihit]>=0
           && (*buffer_hits_volumeid)[ihit]<=17     ) {
       bufferevt_edep [(*buffer_hits_seedid)[ihit]] [(*buffer_hits_volumeid)[ihit]] += (*buffer_hits_edep)[ihit];
       bufferevt_time [(*buffer_hits_seedid)[ihit]]                                  = (*seed_time)[(*buffer_hits_seedid)[ihit]];
      }
    }
//
    return;
}

void HPGeEventData::FindPrimaryMuonTagTypeID()
{
   primary_muontag_typeid=-1;
   primary_muontag_index =-1;
   bool all_rest_scint_less_than_eveto;
   double muontag_ethreshold=4000.0;     // unit keV
   double muontag_evetothreshold=3000.0; // unit keV
   if (scinevt_time->size()<=0) return;  // no single scintillator with registered energy
   double Muon_E[18];
//---> start looping over all scinevt
   for (int imu=0; imu<scinevt_time->size(); imu++) {
     for (int iscint=0; iscint<18; iscint++) Muon_E[iscint]=0.0;
     for (int ich=0; ich<(*scinevt_edep)[imu]->size(); ich++) 
          Muon_E     [(*(*scinevt_id)[imu])[ich]] = (*(*scinevt_edep)[imu])[ich]; // uni keV
       if ( Muon_E[0]>muontag_ethreshold && Muon_E[1]>muontag_ethreshold ) primary_muontag_typeid=0;
   //---> muonthrough-1b1
       if (   Muon_E[0] >muontag_ethreshold && Muon_E[1]>muontag_ethreshold
          &&Muon_E[2] >muontag_ethreshold
          &&Muon_E[12]>muontag_ethreshold )  primary_muontag_typeid=1;
    //---> muonthrough-2b2
       if (    Muon_E[0]>muontag_ethreshold && Muon_E[1]>muontag_ethreshold
          &&Muon_E[3]>muontag_ethreshold
          &&Muon_E[13]>muontag_ethreshold )  primary_muontag_typeid=2;
    //---> muonthrough-13
       if (    Muon_E[0]>muontag_ethreshold && Muon_E[1]>muontag_ethreshold
          &&Muon_E[2]>muontag_ethreshold && Muon_E[4]>muontag_ethreshold
          &&Muon_E[12]>muontag_ethreshold )  primary_muontag_typeid=3;
    //---> muonthrough-24
       if (    Muon_E[0]>muontag_ethreshold && Muon_E[1]>muontag_ethreshold
          &&Muon_E[3]>muontag_ethreshold && Muon_E[5]>muontag_ethreshold
          &&Muon_E[13]>muontag_ethreshold )  primary_muontag_typeid=4;
    //---> muoncapture-13
    //---> 2022.09.26, for 13-capture tag, no cuts on small 2 and 4, same for 24-capture tag
       if (    Muon_E[0]>muontag_ethreshold && Muon_E[2]>muontag_ethreshold && Muon_E[4]>muontag_ethreshold ){
         all_rest_scint_less_than_eveto=kTRUE;
         for (int icha=0; icha<16; icha++) {  // here Extra1(16) and Extra2(17) are not included in the veto
           if (icha!=0 && icha!=2 && icha!=3 && icha!=4 && icha!=5) {
             if (Muon_E[icha]>muontag_evetothreshold) all_rest_scint_less_than_eveto=kFALSE;
           }
         }
         if (all_rest_scint_less_than_eveto) primary_muontag_typeid=5;
       }
    //---> muoncapture-24
       if (    Muon_E[0]>muontag_ethreshold && Muon_E[3]>muontag_ethreshold && Muon_E[5]>muontag_ethreshold ){
         all_rest_scint_less_than_eveto=kTRUE;
         for (int icha=0; icha<16; icha++) {
           if (icha!=0 && icha!=2 && icha!=3 && icha!=4 && icha!=5) {
             if (Muon_E[icha]>muontag_evetothreshold) all_rest_scint_less_than_eveto=kFALSE;
           }
         }
         if (all_rest_scint_less_than_eveto) primary_muontag_typeid=6;
       }
    //---> index
       if (primary_muontag_typeid>=0&&primary_muontag_index<0) primary_muontag_index=imu;
//--> finished looping over all scinevt
   }
   return;
}
