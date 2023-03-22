/*
this program is based on 
/remote/ceph2/user/x/xliu/work/minidex/code/analyze_simulation_runv/find_neutron_signal/sum_up_all_matched_neutron_histograms.cxx
and sum up all histograms under one directory gived as input, z.B., minidex_runv_mc_run1A
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <sstream>
#include <limits>
#include <utility>
#include <valarray>
#include <vector>
// Root headers.
#include "TSystem.h"
#include "TROOT.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TF1.h"
#include "TMath.h"
#include "TString.h"
#include "TStyle.h"
#include "TPaveText.h"
#include "TLatex.h"
#include "TPRegexp.h"
#include "TChain.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

int main(int argc, char**argv)
{
//
  if (argc != 3){
    cout << " \n Usage: " << argv[0] << " [INPUT 1 A]  "  << endl;
    cerr << " \n Error!! Not correct number of arguments" << endl;
    exit(0);
  }
//
   gROOT->SetStyle("Plain");
   gStyle->SetOptStat();
   gStyle->SetOptFit();
//
  const int nscint=18;
  const int n_muonevent_types=7;
//
//---> create the list of ntuple files
//
  TString histogram_file_list_name = TString("/ptmp/mpp/xliu/runv_summed_lists/list_of_histograms_files_in_runv_")
                                    +TString(argv[1])
                                    +TString("_")
                                    +TString(argv[2])
                                    +TString(".txt");
  TString command_to_remove_list_file = TString("rm ")+histogram_file_list_name;
  TString command_list_all_root_files = TString("find ")
                                       +TString("/ptmp/mpp/xliu/minidex_runv_mc_run")
                                       +TString(argv[1])
                                       +TString(argv[2])
                                       +TString(" -maxdepth 1 -name \"*.root\" | sort > ")+histogram_file_list_name;
  system(command_to_remove_list_file.Data());
  system(command_list_all_root_files.Data());
//
  TString inputlistfilename = histogram_file_list_name;
  TString outputhistogramfilename = TString("/ptmp/mpp/xliu/runv_summed_histograms/h.mc.systematics.sum.runv.")
                                   +TString(argv[1])+TString(argv[2])+TString(".root");
  cout<<" input list file "<<inputlistfilename.Data()<<endl;
//
//---> create the sum histograms, same as those in HPGeEventData.hh and .cc
//
//---> following copy-and-paste from HPGeEventData.hh
// there are two groups of histograms, first group: energy-time distributions of scintillators and hpges
  TH1D* heall_scint[18]; // 18 scintillators in MC
  TH1D* heall_hpge[4];   //  0 XTRaA, 1 XTRaB, 2 A+B after grouping
  TH1D* he_scint[7][18]; // this is for the tag, 
   // first index 0 T+B, 1 to 6, the 6 different muon-through and muon-capture types,
  TH1D* he_scint_xtra_signal[7][18]; // for at least one HPGe with 2.2MeV in signal time window from 8micro-second to 1ms
  TH1D* he_xtra[7][4][14]; // second is for two XtRas,0 A, 1 B, 2 A+B, 3, only A and B both firing, 
  double signal_time_range_cut[2][14]; //unit in MC ns
/* third index is for different time windows
0, plus-minus 50ns,
1, 8micro-s to 1ms 
2, 10micro-s to 1ms 
3, 12micro-s to 1ms 
4, 18micro-s to 1ms 
5, 20micro-s to 1ms 
6, 22micro-s to 1ms 
7, 48micro-s to 1ms 
8, 50micro-s to 1ms 
9, 52micro-s to 1ms 
10,98micro-s to 1ms 
11,100micro-s to 1ms 
12,102micro-s to 1ms 
13,10ms to 100ms for background 
*/
//--> following two histograms are only for 2.2MeV events (2223.5keV to 2225.0keV) from 10micro-second to 1ms
//    seems in MC the energy is 2224.35 to 2224.40keV
  TH1D* htpassed_xtra_signal[7]; // time passed
  TH1D* hn_2p2_multiplicity[7];  // 2.2MeV multiplicity
//
//---> second group of histograms: for muon-tag events, and muon-tag plus 2.2MeV events, the FLUKA input particles,
//     this is copy-and-paste from find_neutron_signal_from_single_mc_ntuple.cxx
//     first index: 7 types of muontags, 
//     second index: 0 mu-, 1 mu+, 2 gamma, 3 e-, 4 e+, 5 neutron, 6 proton
//     last index: 0 all muontag events, 1 events with at least one 2.2MeV HPGe inside 10microsecond-1ms signal time window
   TH1D* hmcp_logke [7][7][2];
   TH1D* hmcp_n     [7][7][2];
   TH1D* hmcp_theta [7][7][2]; // from -90 to 90 degrees
   TH1D* hmcp_phi   [7][7][2];
   TH2D* hmcp_logke_vs_theta[7][7][2];
   TH1D* hmcp_logtime       [7][7][2];
   TH2D* hmcp_xvsy  [7][7][2];
   TH1D* hmcp_z     [7][7][2];
   TH1D* hmcp_num_mus[7][2]; // total number of mu- and mu+ together
//---> following copy-and-paste from HPGeEventData.cc
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
//---> loop over all histogram files and add up
//
  TFile* finput;
   char  temp_txt[500];
   int number_of_processed_ntuples=0;
   std::ifstream finputlist(inputlistfilename.Data(), std::ifstream::in);
   while (!finputlist.eof()) {
      finputlist>>temp_txt;
      cout<<" now process "<<number_of_processed_ntuples<<" "<<temp_txt<<endl;
     //---> open ntuple file
      finput = new TFile(temp_txt);
     if (finput->GetListOfKeys()->Contains("type0")) {
      number_of_processed_ntuples++;
     //---> all events
      finput->cd("all_evts"); 
      for (int iscint=0; iscint<18; iscint++) heall_scint[iscint]->Add((TH1F*)gDirectory->Get(Form("heall_scint%d",iscint)));
      for (int ich=0; ich<4; ich++)           heall_hpge[ich]    ->Add((TH1F*)gDirectory->Get(Form("heall_hpge%d", ich)));
     //---> tags and HPGe in different signal-time-window
      for (int itype=0; itype<n_muonevent_types; itype++) {
        finput->cd(Form("type%d",itype));
        hn_2p2_multiplicity[itype] ->Add((TH1F*)gDirectory->Get(Form("hn_2p2_multiplicity_type%d",itype)));
        htpassed_xtra_signal[itype]->Add((TH1F*)gDirectory->Get(Form("htpassed_xtra_signal_type%d",itype)));
        for (int iscint=0; iscint<18; iscint++) {
          he_scint            [itype][iscint]->Add((TH1F*)gDirectory->Get(Form("he_scint%d_type%d"            ,iscint,itype)));
          he_scint_xtra_signal[itype][iscint]->Add((TH1F*)gDirectory->Get(Form("he_scint%d_type%d_xtra_signal",iscint,itype)));
        } 
        for (int irange=0; irange<14; irange++) {
          for (int ich=0; ich<4; ich++) he_xtra[itype][ich][irange]->Add((TH1F*)gDirectory->Get(Form("he_xtra_chn%d_type%d_time%d",ich,itype,irange)));
        } 
      } 
     //---> MC input particles
   for (int i=0; i<7; i++) { // muon tag types
     for (int j=0;j<7;j++) { // FLUKA particles
       finput -> cd   (Form("mcp_tagtype%d_mcp%d",i,j));
       if (j==0) for (int k=0;k<2;k++) hmcp_num_mus[i][k]->Add((TH1F*)gDirectory->Get(Form("hmcp_num_mus_tagtype%d_2p2%d",i,k)));
       for (int k=0;k<2;k++) {
         hmcp_logke  [i][j][k]->Add((TH1F*)gDirectory->Get(Form("hmcp_logke_tagtype%d_mcp%d_2p2%d"  ,i,j,k)));
         hmcp_n      [i][j][k]->Add((TH1F*)gDirectory->Get(Form("hmcp_n_tagtype%d_mcp%d_2p2%d"      ,i,j,k)));
         hmcp_theta  [i][j][k]->Add((TH1F*)gDirectory->Get(Form("hmcp_theta_tagtype%d_mcp%d_2p2%d"  ,i,j,k)));
         hmcp_phi    [i][j][k]->Add((TH1F*)gDirectory->Get(Form("hmcp_phi_tagtype%d_mcp%d_2p2%d"    ,i,j,k)));
         hmcp_logtime[i][j][k]->Add((TH1F*)gDirectory->Get(Form("hmcp_logtime_tagtype%d_mcp%d_2p2%d",i,j,k)));
         hmcp_xvsy   [i][j][k]->Add((TH1F*)gDirectory->Get(Form("hmcp_xvsy_tagtype%d_mcp%d_2p2%d"   ,i,j,k)));
         hmcp_z      [i][j][k]->Add((TH1F*)gDirectory->Get(Form("hmcp_z_tagtype%d_mcp%d_2p2%d"      ,i,j,k)));
         hmcp_logke_vs_theta[i][j][k]->Add((TH1F*)gDirectory->Get(Form("hmcp_logke_vs_theta_tagtype%d_mcp%d_2p2%d",i,j,k)));
       } 
     } 
   } 
     //
     } // finished read in all histograms from this file
      finput->Close();
   }// finished looping over all histogram files
//
//---> make plots
// types: 1 1b1-through, 2 2b2-through, 3 13-through, 4 24-through, 5 13-capture, 6 24-capture
//
   TLatex ll;
   ll.SetNDC();
   ll.SetTextSize(0.04);
//
//---> save summed histograms to output file
//
    TFile* fOutputFile = new TFile(outputhistogramfilename.Data(),"recreate");
    fOutputFile -> cd();
   fOutputFile->mkdir("all_evts");
   fOutputFile->cd("all_evts");
   for (int iscint=0; iscint<18; iscint++) heall_scint[iscint]->Write();
   for (int ich=0; ich<4; ich++)           heall_hpge[ich]->Write();
// 
   for (int itype=0; itype<7; itype++) {
     fOutputFile -> cd();
     fOutputFile -> mkdir(Form("type%d",itype));
     fOutputFile -> cd   (Form("type%d",itype));
     hn_2p2_multiplicity[itype]->Write();
     htpassed_xtra_signal[itype]->Write();
     for (int iscint=0; iscint<18; iscint++) {
       he_scint[itype][iscint]->Write();
       he_scint_xtra_signal[itype][iscint]->Write();
     } 
     for (int irange=0; irange<14; irange++) {
       for (int ich=0; ich<4; ich++) he_xtra[itype][ich][irange]->Write();
     } 
   } 
   for (int itype=0; itype<7; itype++) {
     for (int i=0;i<7;i++) {
       fOutputFile -> cd();
       fOutputFile -> mkdir(Form("mcp_tagtype%d_mcp%d",itype,i));
       fOutputFile -> cd   (Form("mcp_tagtype%d_mcp%d",itype,i));
       if (i==0) for (int j=0;j<2;j++) hmcp_num_mus[itype][j]->Write();
       for (int j=0;j<2;j++) {
         hmcp_logke  [itype][i][j]->Write();
         hmcp_n      [itype][i][j]->Write();
         hmcp_theta  [itype][i][j]->Write();
         hmcp_phi    [itype][i][j]->Write();
         hmcp_logtime[itype][i][j]->Write();
         hmcp_xvsy   [itype][i][j]->Write();
         hmcp_z      [itype][i][j]->Write();
         hmcp_logke_vs_theta[itype][i][j]->Write();
       } 
     } 
   } 
    fOutputFile->Write();
    fOutputFile->Close();
//
  return 0;
}

