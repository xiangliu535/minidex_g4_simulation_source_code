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

//--->time range cut defined here
/* third index is for different time windows
 * 0, plus-minus 50ns,
 * 1, 8micro-s to 1ms 
 * 2, 10micro-s to 1ms 
 * 3, 12micro-s to 1ms 
 * 4, 18micro-s to 1ms 
 * 5, 20micro-s to 1ms 
 * 6, 22micro-s to 1ms 
 * 7, 48micro-s to 1ms 
 * 8, 50micro-s to 1ms 
 * 9, 52micro-s to 1ms 
 * 10,98micro-s to 1ms 
 * 11,100micro-s to 1ms 
 * 12,102micro-s to 1ms 
 * 13,10ms to 100ms for background 
 * */
   signal_time_range_cut[0][0]=-50.0; // unit ns
   signal_time_range_cut[1][0]=50.0;
 //
   signal_time_range_cut[0][1]=8000.0; // 8micros
   signal_time_range_cut[0][2]=10000.0; // 10micros
   signal_time_range_cut[0][3]=12000.0; // 12micros
   signal_time_range_cut[0][4]=18000.0; // 18micros
   signal_time_range_cut[0][5]=20000.0; // 20micros
   signal_time_range_cut[0][6]=22000.0; // 22micros
   signal_time_range_cut[0][7]=48000.0; // 48micros
   signal_time_range_cut[0][8]=50000.0; // 50micros
   signal_time_range_cut[0][9]=52000.0; // 52micros
   signal_time_range_cut[0][10]=98000.0; //   98micros
   signal_time_range_cut[0][11]=100000.0; // 100micros
   signal_time_range_cut[0][12]=102000.0; // 102micros
   for (int itemp=1; itemp<=12; itemp++) 
    signal_time_range_cut[1][itemp]=1000000.0;  // 1ms = 1.0e6 ns
 //
   signal_time_range_cut[0][13]=10000000.0; // 10ms
   signal_time_range_cut[1][13]=100000000.0; // 100ms

//---> create Tag-related histograms here
     for (int iscint=0; iscint<18; iscint++) {
         heall_scint[iscint] = new TH1D(Form("heall_scint%d",iscint),
                                        Form("heall_scint%d",iscint),
                                            500, 0.0, 50000.0);
     }
     for (int icha=0; icha<4; icha++) {
         heall_hpge[icha] = new TH1D(Form("heall_hpge%d",icha),
                                     Form("heall_hpge%d",icha),
                                     10000,0.0,10000.0);
     }
  for (int itype=0; itype<7; itype++) {
     for (int iscint=0; iscint<18; iscint++) {
         he_scint[itype][iscint] = new TH1D(Form("he_scint%d_type%d",iscint,itype),
                                            Form("he_scint%d_type%d",iscint,itype),
                                            500, 0.0, 50000.0);
         he_scint_xtra_signal[itype][iscint] = new TH1D(Form("he_scint%d_type%d_xtra_signal",iscint,itype),
                                                        Form("he_scint%d_type%d_xtra_signal",iscint,itype),
                                            500, 0.0, 50000.0); //keV
     }
     for (int irange=0; irange<14; irange++) {
      for (int icha=0; icha<4; icha++){
       he_xtra[itype][icha][irange] = new TH1D(Form("he_xtra_chn%d_type%d_time%d",icha,itype,irange),
                                               Form("he_xtra_chn%d_type%d_time%d",icha,itype,irange),
                                    10000, 0.0, 10000.0); //keV
      }
     }
     htpassed_xtra_signal[itype] = new TH1D(Form("htpassed_xtra_signal_type%d",itype),
                                            Form("htpassed_xtra_signal_type%d",itype),
                                    1000, 0.0, 1000000.0); // unit ns
    hn_2p2_multiplicity[itype] =  new TH1D(Form("hn_2p2_multiplicity_type%d",itype),
                                           Form("hn_2p2_multiplicity_type%d",itype),
                                                10,-0.5,9.5);
  }
//---> FLUKA input particles for various MuonTag type
   char* mcp_name[7];
   mcp_name[0]="mu-";
   mcp_name[1]="mu+";
   mcp_name[2]="gamma";
   mcp_name[3]="e-";
   mcp_name[4]="e+";
   mcp_name[5]="neutron";
   mcp_name[6]="proton";
//
   for (int i=0; i<7; i++) { // MuonTag types
     for (int j=0; j<7; j++) { // 7 types of FLUKA input particles
       for (int k=0; k<2; k++) {
          hmcp_logke[i][j][k] = new TH1D(
                          Form("hmcp_logke_tagtype%d_mcp%d_2p2%d",i,j,k),
                          Form("hmcp_logke_tagtype%d_mcp%d_%s_2p2%d",i,j,mcp_name[j],k),
                         180,0.0,9.0); // from keV to EeV
          hmcp_n[i][j][k] = new TH1D(
                            Form("hmcp_n_tagtype%d_mcp%d_2p2%d",i,j,k),
                            Form("hmcp_n_tagtype%d_mcp%d_%s_2p2%d",i,j,mcp_name[j],k),
                         100,-0.5,99.5); // how many of these second particles from each primary muon
          hmcp_theta[i][j][k] = new TH1D(
                            Form("hmcp_theta_tagtype%d_mcp%d_2p2%d",i,j,k),
                            Form("hmcp_theta_tagtype%d_mcp%d_%s_2p2%d",i,j,mcp_name[j],k),
                         180,0.0,180.0);  // theta
          hmcp_phi[i][j][k] = new TH1D(
                            Form("hmcp_phi_tagtype%d_mcp%d_2p2%d",i,j,k),
                            Form("hmcp_phi_tagtype%d_mcp%d_%s_2p2%d",i,j,mcp_name[j],k),
                         360,-180.0,180.0);  // phi
          hmcp_logke_vs_theta[i][j][k] = new TH2D(
                            Form("hmcp_logke_vs_theta_tagtype%d_mcp%d_2p2%d",i,j,k),
                            Form("hmcp_logke_vs_theta_tagtype%d_mcp%d_%s_2p2%d",i,j,mcp_name[j],k),
                         180,0.0,9.0,     // logke
                         180,0.0,180.0);  // theta
          hmcp_logtime[i][j][k] = new TH1D(
                                 Form("hmcp_logtime_tagtype%d_mcp%d_2p2%d",i,j,k),
                                 Form("hmcp_logtime_tagtype%d_mcp%d_%s_2p2%d",i,j,mcp_name[j],k),
                                 100,0.0,10.0); // unit log10(ns)
          hmcp_xvsy[i][j][k] = new TH2D(
                            Form("hmcp_xvsy_tagtype%d_mcp%d_2p2%d",i,j,k),
                            Form("hmcp_xvsy_tagtype%d_mcp%d_%s_2p2%d",i,j,mcp_name[j],k),
                         100,-2000.0,2000.0,  // unit mm
                         100,-2000.0,2000.0);
          hmcp_z[i][j][k] = new TH1D(
                            Form("hmcp_z_tagtype%d_mcp%d_2p2%d",i,j,k),
                            Form("hmcp_z_tagtype%d_mcp%d_%s_2p2%d",i,j,mcp_name[j],k),
                         100,-2000.0,2000.0); // unit mm
       }
     }
   }
   for (int i=0; i<7; i++) {
     for (int k=0; k<2; k++) {
        hmcp_num_mus[i][k] = new TH1D(
              Form("hmcp_num_mus_tagtype%d_2p2%d",i,k),
              Form("hmcp_num_mus_tagtype%d_2p2%d",i,k),
             10,-0.5,9.5);
     }
   }
//
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

    for (unsigned int i=0; i<scinevt_edep->size(); i++) delete (*scinevt_edep)[i];
    for (unsigned int i=0; i<scinevt_id  ->size(); i++) delete (*scinevt_id)  [i];
    for (unsigned int i=0; i<hpgeevt_edep->size(); i++) delete (*hpgeevt_edep)[i];
    for (unsigned int i=0; i<hpgeevt_id  ->size(); i++) delete (*hpgeevt_id)  [i];
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
    for (unsigned int i=0; i<scinevt_edep->size(); i++) delete (*scinevt_edep)[i];
    for (unsigned int i=0; i<scinevt_id->size(); i++) delete (*scinevt_id)[i];
     scinevt_edep->clear();
     scinevt_id  ->clear();
     hpgeevt_time->clear();
    for (unsigned int i=0; i<hpgeevt_edep->size(); i++) delete (*hpgeevt_edep)[i];
    for (unsigned int i=0; i<hpgeevt_id->size(); i++) delete (*hpgeevt_id)[i];
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
       // if ((*hits_edep)[ihit]<=0.001) continue; 
       // this cut is already applied in HPGeAnalysisManager::FillHitsToNtuple(const G4Event *pEvent),
       // latest update, this cut is applied in HPGeHPGeSensitiveDetector::ProcessHits(G4Step* pStep, G4TouchableHistory *pHistory)
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
    for (unsigned int ihit=0; ihit<scinevt_hits_edep->size(); ihit++) {
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
    for (unsigned int ihit=0; ihit<hpgeevt_hits_edep->size(); ihit++) {
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
    for (unsigned int ihit=0; ihit<buffer_hits_time->size(); ihit++) {
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
    for (unsigned int ihit=0; ihit<buffer_hits_time->size(); ihit++) {
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
   vector<int> *vec_primary_muontag_typeid = new vector<int>;
   vector<int> *vec_primary_muontag_index  = new vector<int>;
//---> first loop over all scinevt to pick out all primary tags
   for (unsigned int imu=0; imu<scinevt_time->size(); imu++) {
     if ((*scinevt_edep)[imu]->size()<3) continue; // scinevt with less than 3 scintillators firing can not be any type of primary tag
     big_top_above_energy_threshold   =kFALSE; 
     big_bottom_above_energy_threshold=kFALSE; 
     small_1_above_energy_threshold   =kFALSE; 
     small_2_above_energy_threshold   =kFALSE; 
     small_3_above_energy_threshold   =kFALSE; 
     small_4_above_energy_threshold   =kFALSE; 
     bottom_side1_above_energy_threshold   =kFALSE; 
     bottom_side2_above_energy_threshold   =kFALSE; 
     all_rest_scint_otherthan_4321t_less_than_eveto =kTRUE;
     for (unsigned int ich=0; ich<(*scinevt_edep)[imu]->size(); ich++) {
        if ( (*(*scinevt_edep)[imu])[ich]>muontag_ethreshold ) {
           if      ((*(*scinevt_id)[imu])[ich]==0)  big_top_above_energy_threshold     =kTRUE;
           else if ((*(*scinevt_id)[imu])[ich]==1)  big_bottom_above_energy_threshold  =kTRUE;
           else if ((*(*scinevt_id)[imu])[ich]==2)  small_1_above_energy_threshold     =kTRUE;
           else if ((*(*scinevt_id)[imu])[ich]==3)  small_2_above_energy_threshold     =kTRUE;
           else if ((*(*scinevt_id)[imu])[ich]==4)  small_3_above_energy_threshold     =kTRUE;
           else if ((*(*scinevt_id)[imu])[ich]==5)  small_4_above_energy_threshold     =kTRUE;
           else if ((*(*scinevt_id)[imu])[ich]==12) bottom_side1_above_energy_threshold=kTRUE;
           else if ((*(*scinevt_id)[imu])[ich]==13) bottom_side2_above_energy_threshold=kTRUE;
        }
        if ( (*(*scinevt_edep)[imu])[ich]>muontag_evetothreshold ) {
          if ( (*(*scinevt_id)[imu])[ich]>5 || (*(*scinevt_id)[imu])[ich]==1 ) 
                    all_rest_scint_otherthan_4321t_less_than_eveto=kFALSE;
        }
     }// finished looping over all scintillators for this event, 
    // now check what MuonTag Type it is, notice, 
    //
     int itemp_muoneventtype=-1;
     if (   big_top_above_energy_threshold
         && big_bottom_above_energy_threshold ) itemp_muoneventtype=0;
     if (   big_top_above_energy_threshold
         && big_bottom_above_energy_threshold
         && small_1_above_energy_threshold
         && bottom_side1_above_energy_threshold ) itemp_muoneventtype=1;
     if (   big_top_above_energy_threshold
         && big_bottom_above_energy_threshold
         && small_2_above_energy_threshold
         && bottom_side2_above_energy_threshold ) itemp_muoneventtype=2;
     if (   big_top_above_energy_threshold
         && big_bottom_above_energy_threshold
         && small_3_above_energy_threshold
         && small_1_above_energy_threshold
         && bottom_side1_above_energy_threshold ) itemp_muoneventtype=3;
     if (   big_top_above_energy_threshold
         && big_bottom_above_energy_threshold
         && small_4_above_energy_threshold
         && small_2_above_energy_threshold
         && bottom_side2_above_energy_threshold ) itemp_muoneventtype=4;
     if (   big_top_above_energy_threshold
         && small_3_above_energy_threshold
         && small_1_above_energy_threshold
         && all_rest_scint_otherthan_4321t_less_than_eveto ) itemp_muoneventtype=5;
     if (   big_top_above_energy_threshold
         && small_4_above_energy_threshold
         && small_2_above_energy_threshold
         && all_rest_scint_otherthan_4321t_less_than_eveto ) itemp_muoneventtype=6;
     if (itemp_muoneventtype>=0) {
       vec_primary_muontag_typeid->push_back(itemp_muoneventtype);
       vec_primary_muontag_index ->push_back(imu);
     }
   } // finished looping over all scinevt 
//--> second loop over vec_primary_muontag to pick the primary tag earliest in time as THE tag for this simulated event
   if (vec_primary_muontag_index->size()<=0) return;
   primary_muontag_typeid=(*vec_primary_muontag_typeid)[0];
   primary_muontag_index =(*vec_primary_muontag_index) [0];
   for (unsigned int ipritag=1; ipritag<vec_primary_muontag_index->size(); ipritag++) {
      if (   (*scinevt_time)[(*vec_primary_muontag_index)[ipritag]]
            <(*scinevt_time)[primary_muontag_index]                 )
          primary_muontag_typeid=(*vec_primary_muontag_typeid)[ipritag];
          primary_muontag_index =(*vec_primary_muontag_index) [ipritag];
   }
   delete vec_primary_muontag_typeid;
   delete vec_primary_muontag_index;
   return;
}


void HPGeEventData::FillEnergyandMonteCarloHistograms()
{
//--> first fill histograms for all HPGes and Scintillators
   double HPGe_E[3]; // 
   for (unsigned int ihpge=0; ihpge<hpgeevt_time->size(); ihpge++) {
        for (int ich=0; ich<3; ich++) HPGe_E[ich]=0.0;
        for (unsigned int ich=0; ich<(*hpgeevt_edep)[ihpge]->size(); ich++) 
          HPGe_E[(*(*hpgeevt_id)[ihpge])[ich]] = (*(*hpgeevt_edep)[ihpge])[ich];
        HPGe_E[2]=HPGe_E[0]+HPGe_E[1];
        if (HPGe_E[0]>0.0) heall_hpge[0]->Fill(HPGe_E[0]);
        if (HPGe_E[1]>0.0) heall_hpge[1]->Fill(HPGe_E[1]);
                           heall_hpge[2]->Fill(HPGe_E[2]);
        if (HPGe_E[0]>0.0 && HPGe_E[1]>0.0) 
                           heall_hpge[3]->Fill(HPGe_E[2]);
   }
   for (unsigned int imu=0; imu<scinevt_time->size(); imu++) {
       for (unsigned int ich=0; ich<(*scinevt_edep)[imu]->size(); ich++) {
          heall_scint[(*(*scinevt_id)[imu])[ich]] -> Fill((*(*scinevt_edep)[imu])[ich]);
       }
   }
//--> then fill scintillator energy histograms from primary tag
   if (primary_muontag_typeid<0) return;
   for (unsigned int ich=0; ich<(*scinevt_edep)[primary_muontag_index]->size(); ich++) {
         he_scint[primary_muontag_typeid][(*(*scinevt_id)  [primary_muontag_index])[ich]]
                                   ->Fill((*(*scinevt_edep)[primary_muontag_index])[ich]);
   }
//--> then loop over all hpgeevt and
//    fill Xtra energy histograms for the 14 different time range
   int itemp_number_of_2p2_in_signal_time_window=0;
   for (unsigned int ihpge=0; ihpge<hpgeevt_time->size(); ihpge++) {
     for (int ich=0; ich<3; ich++) HPGe_E[ich]=0.0;
     for (unsigned int ich=0; ich<(*hpgeevt_edep)[ihpge]->size(); ich++) 
       HPGe_E[(*(*hpgeevt_id)[ihpge])[ich]] = (*(*hpgeevt_edep)[ihpge])[ich];
     HPGe_E[2]=HPGe_E[0]+HPGe_E[1];
     double time_difference_hpge_muontag=((*hpgeevt_time)[ihpge]-(*scinevt_time)[primary_muontag_index]); // unit ns
     for (int irange=0; irange<14; irange++) {
       if (   time_difference_hpge_muontag>=signal_time_range_cut[0][irange]
            &&time_difference_hpge_muontag< signal_time_range_cut[1][irange] ) {
          if (HPGe_E[0]>0.0) he_xtra[primary_muontag_typeid][0][irange]->Fill(HPGe_E[0]);
          if (HPGe_E[1]>0.0) he_xtra[primary_muontag_typeid][1][irange]->Fill(HPGe_E[1]);
                             he_xtra[primary_muontag_typeid][2][irange]->Fill(HPGe_E[2]);
          if (HPGe_E[0]>0.0 && HPGe_E[1]>0.0) 
                             he_xtra[primary_muontag_typeid][3][irange]->Fill(HPGe_E[2]);
       }
     }// finished looping over all time range
     if (   time_difference_hpge_muontag>=signal_time_range_cut[0][2]
          &&time_difference_hpge_muontag< signal_time_range_cut[1][2] 
          &&HPGe_E[2] > 2223.0
          &&HPGe_E[2] < 2225.0 ) { // hpgeevt energy within range inside 10micro-s to 1ms, default signal window
        itemp_number_of_2p2_in_signal_time_window++;
        htpassed_xtra_signal[primary_muontag_typeid]->Fill(time_difference_hpge_muontag);
     }
   } // finished looping over all hpgeevt
//---> if there is at least one 2.2MeV in 10micros to 1ms
   hn_2p2_multiplicity[primary_muontag_typeid]->Fill(itemp_number_of_2p2_in_signal_time_window);
   if (itemp_number_of_2p2_in_signal_time_window>0) {
      for (unsigned int ich=0; ich<(*scinevt_edep)[primary_muontag_index]->size(); ich++)
         he_scint_xtra_signal[primary_muontag_typeid][(*(*scinevt_id)  [primary_muontag_index])[ich]]
                                               ->Fill((*(*scinevt_edep)[primary_muontag_index])[ich]);
   }
//---> finally loop over all FLUKA input particles
//---> fill all histograms for Geant4-input MC particles
   int itemp_number_of_mcp[7];
     int itemp_num_mus=0;
     for (unsigned int imcp=0; imcp<mc_pdgcode->size(); imcp++) {
        int index_mcp=-1;
        if      ( (*mc_pdgcode)[imcp]==13 )  index_mcp=0;  // mu-
        else if ( (*mc_pdgcode)[imcp]==-13)  index_mcp=1;  // mu+
        else if ( (*mc_pdgcode)[imcp]==22 )  index_mcp=2;  // gamma
        else if ( (*mc_pdgcode)[imcp]==11 )  index_mcp=3;  // e-
        else if ( (*mc_pdgcode)[imcp]==-11)  index_mcp=4;  // e+
        else if ( (*mc_pdgcode)[imcp]==2112) index_mcp=5;  // neutron
        else if ( (*mc_pdgcode)[imcp]==2212) index_mcp=5;  // proton
        if (index_mcp>=0) { // fill histograms only for the above 7 types of mc input particles
           if (index_mcp==0||index_mcp==1) itemp_num_mus++;
           itemp_number_of_mcp[index_mcp]++;
          //
           float mcp_theta = atan2(     (*mc_pz)[imcp],
                                   sqrt((*mc_px)[imcp]*(*mc_px)[imcp]+(*mc_py)[imcp]*(*mc_py)[imcp]) )*180.0/TMath::Pi();
           mcp_theta = 90.0-mcp_theta;
           float mcp_phi =  atan2((*mc_py)[imcp],(*mc_px)[imcp])*180.0/TMath::Pi();
          //
           hmcp_logke  [primary_muontag_typeid][index_mcp][0]->Fill(log10((*mc_ke)[imcp]));
           hmcp_theta  [primary_muontag_typeid][index_mcp][0]->Fill(mcp_theta);
           hmcp_phi    [primary_muontag_typeid][index_mcp][0]->Fill(mcp_phi);
           hmcp_logtime[primary_muontag_typeid][index_mcp][0]->Fill(log10((*vertex_time)[imcp]));
           hmcp_xvsy   [primary_muontag_typeid][index_mcp][0]->Fill((*vertex_xpos)[imcp],(*vertex_ypos)[imcp]);
           hmcp_z      [primary_muontag_typeid][index_mcp][0]->Fill((*vertex_zpos)[imcp]);
           hmcp_logke_vs_theta[primary_muontag_typeid][index_mcp][0]->Fill(log10((*mc_ke)[imcp]), mcp_theta);
          //
          if (itemp_number_of_2p2_in_signal_time_window>0) {
           hmcp_logke  [primary_muontag_typeid][index_mcp][1]->Fill(log10((*mc_ke)[imcp]));
           hmcp_theta  [primary_muontag_typeid][index_mcp][1]->Fill(mcp_theta);
           hmcp_phi    [primary_muontag_typeid][index_mcp][1]->Fill(mcp_phi);
           hmcp_logtime[primary_muontag_typeid][index_mcp][1]->Fill(log10((*vertex_time)[imcp]));
           hmcp_xvsy   [primary_muontag_typeid][index_mcp][1]->Fill((*vertex_xpos)[imcp],(*vertex_ypos)[imcp]);
           hmcp_z      [primary_muontag_typeid][index_mcp][1]->Fill((*vertex_zpos)[imcp]);
           hmcp_logke_vs_theta[primary_muontag_typeid][index_mcp][1]->Fill(log10((*mc_ke)[imcp]), mcp_theta);
          }
        }
     }
     for (int i=0;i<7;i++) {
         hmcp_n[primary_muontag_typeid][i][0]->Fill(itemp_number_of_mcp[i]);
       if (itemp_number_of_2p2_in_signal_time_window>0)
         hmcp_n[primary_muontag_typeid][i][1]->Fill(itemp_number_of_mcp[i]);
     }
     hmcp_num_mus[primary_muontag_typeid][0]->Fill(itemp_num_mus);
    if (itemp_number_of_2p2_in_signal_time_window>0) 
     hmcp_num_mus[primary_muontag_typeid][1]->Fill(itemp_num_mus);
//
    return;
}
