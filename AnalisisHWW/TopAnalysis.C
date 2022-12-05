#define TopAnalysis_cxx
// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.

#include "TopAnalysis.h"
#include "Tophistograms.h"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>

#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLorentzVector.h>

string name;

void TopAnalysis::Begin(TTree * )
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).
}

void TopAnalysis::SlaveBegin(TTree * )
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());

  name=option;

  define_histograms();

  FillOutputList();
}

Bool_t TopAnalysis::Process(Long64_t entry)
{
    // The Process() function is called for each entry in the tree (or possibly
    // keyed object in the case of PROOF) to be processed. The entry argument
    // specifies which entry in the currently loaded tree is to be processed.
    // When processing keyed objects with PROOF, the object is already loaded
    // and is available via the fObject pointer.
    //
    // This function should contain the \"body\" of the analysis. It can contain
    // simple or elaborate selection criteria, run algorithms on the data
    // of the event and typically fill histograms.
    //
    // The processing can be stopped by calling return kTRUE.
    //
    // Use fStatus to set the return value of TTree::Process().
    //
    // The return value is currently not used.

    fChain->GetTree()->GetEntry(entry);
    if( !(fChain->GetTree()->GetEntries()>0) )
    {
        return kTRUE;
    }
    // ANALYSIS:
    // WEIGHTS
    // SF
    Float_t scaleFactor = scaleFactor_ELE*
                          scaleFactor_MUON*
                          scaleFactor_TRIGGER;
    //EventW
    Float_t eventWeight = mcWeight*
                          scaleFactor_PILEUP*
                          scaleFactor_ZVERTEX;
    Double_t weight = scaleFactor*
                      eventWeight;
    // Make difference between data and MC
    if (weight == 0. 
        && 
        channelNumber != 110090 
        && 
        channelNumber != 110091) 
        {weight = 1.;};
    // PRESELECTION: 
    if ( !(trigE || trigM) )
    {
        return kTRUE;
    }
    // Chek if the even are in the Good Run List
    if(!passGRL)
    {
        return kTRUE;
    }
    // Check if the event has a good vertex 
    if(!hasGoodVertex)
    {
        return kTRUE;
    }
    // Find good leptons
    int good_lep_number = 0;
    std::vector<int> good_lep_indexes;
    // Loop over leptons
    for(int ii = 0; ii < lep_n; ii++)
    {
        // Check if the leptons has a good trigger
        bool good_trigger = (lep_pt[ii] / 1000. > 25)
                            &&
                            (lep_ptcone30[ii]/lep_pt[ii]) < 0.15
                            &&
                            (lep_etcone20[ii]/lep_pt[ii]) < 0.15;
        if(!good_trigger)
        {
            continue;
        }
        // For electrons:
        if(lep_type[ii] == 11)
        {
            // Check if the leptons are in a good region
            // True if the electron is not in the fiducial region
            bool fid_reg = TMath::Abs(lep_eta[ii]) < 2.47
                           &&
                           ( TMath::Abs(lep_eta[ii]) < 1.37
                             ||
                             TMath::Abs(lep_eta[ii]) > 1.52
                           );
            if(!fid_reg)
            {
                continue;
            }
            good_lep_number ++;
            good_lep_indexes.push_back(ii);
        } 
        // For muons:
        if(lep_type[ii] == 13)
        {
            // Check if muons are in a good region
            // True if the muon is in a good region
            bool good_reg = TMath::Abs(lep_eta[ii]) < 2.5;
            if(!good_reg)
            {
                continue;
            }
            good_lep_number ++;
            good_lep_indexes.push_back(ii);
        }
    }
    // SELECTION
    // Cuts
    // The event has exactly two good leptons 
    bool two_good_lep = good_lep_number == 2;
    if(!two_good_lep)
    {
        return kTRUE;
    }
    int indx0 = good_lep_indexes[0];
    int indx1 = good_lep_indexes[1];
    // The two leptons has opposite charges
    bool opposite_charge = lep_charge[indx0]
                           != 
                           lep_charge[indx1];
    if(!opposite_charge)
    {
        return kTRUE;
    }
    // No jets with pt > 30 GeV
    // This should work because jets are ordered...
    bool no_jets = jet_pt[0] / 1000. < 30;
    if(!no_jets)
    {
        return kTRUE;
    }
    // construct Lorentz vectors
    TLorentzVector lep_0 = TLorentzVector();
    TLorentzVector lep_1 = TLorentzVector();
    TLorentzVector dilep = TLorentzVector();
    TLorentzVector met   = TLorentzVector();
    lep_0.SetPtEtaPhiE( lep_pt [indx0],
                        lep_eta[indx0],
                        lep_phi[indx0],
                        lep_E  [indx0]
                      );
    lep_1.SetPtEtaPhiE( lep_pt [indx1],
                        lep_eta[indx1],
                        lep_phi[indx1],
                        lep_E  [indx1]
                      );
    met.SetPtEtaPhiE  ( met_et,
                        0,
                        met_phi,
                        met_et
                      );
    dilep = lep_0 + lep_1;
    // IMPORTANT VARIABLES
    // masses on GeV
    float m_ll = dilep.M() / 1000.;
    float m_vis = m_ll;
    // Z bosson's mass in GeV
    float m_z = 91.1876;
    float pt_ll = dilep.Pt() / 1000.;
    // Invariant mass in GeV
    float inv_mass = ( dilep.M() + met.M() ) / 1000.;
    // missing Et in GeV
    float E_T_miss = met_et / 1000.;
    // DeltaPhi_{ll}
    float DeltaPhi = lep_0.DeltaPhi(lep_1);
    // global mt in GeV
    float mt = std::sqrt( 2 * dilep.Pt()
                            * met.Et()
                            * (1-std::cos(dilep.DeltaPhi(met)))
                        ) / 1000.;
    // CONDITIONS
    // pt_{ll} > 30 GeV
    bool cond1 = pt_ll > 30;
    if(!cond1)
    {
        return kTRUE;
    }
    // DeltaPhi(ll, E_{T}^{miss}) > \pi / 2
    bool cond2 = dilep.DeltaPhi( met ) > M_PI*0.5;
    if(!cond2)
    {
        return kTRUE;
    }
    // m_{ll} < 55 GeV
    bool cond3 = m_ll < 55;
    if(!cond3)
    {
        return kTRUE;
    }
    // \DeltaPhi(l,l) < 1.8 rad
    bool cond4 = DeltaPhi < 1.8;
    if(!cond4)
    {
        return kTRUE;
    }
    // if leptons have the same flavor...
    bool same_flavor = lep_type[indx0] 
                       ==
                       lep_type[indx1];
    if( same_flavor )
    {
        // m^{vis} > 12 GeV bool 
        bool cond5 = m_vis > 12;
        if(!cond5)
        {
            return kTRUE;
        }
        // | m^{vis} - m_{Z} | > 15 GeV
        bool cond6 = TMath::Abs( m_vis - m_z ) > 15;
        if(!cond6)
        {
            return kTRUE;
        }
        // E_{T}^{miss} > 40 GeV 
        bool cond7 = E_T_miss > 40;
        if(!cond7)
        {
            return kTRUE;
        }
    } 
    else
    {
        // m_{ll} > 10 GeV
        bool cond8 = m_ll > 10;
        if(!cond8)
        {
            return kTRUE;
        }
        // E_{T}^{miss} > 20 GeV
        bool cond9 = E_T_miss > 20;
        if(!cond9)
        {
            return kTRUE;
        }
    }
    // FILLING THE HISOTGRAMS
    // If everithing is true fill the histograms...
    double names_of_global_variable[] = {
                                         m_vis, 
                                         E_T_miss, 
                                         vxp_z, 
                                         (double)pvxp_n, 
                                         mt
                                        };
    double names_of_leadlep_variable[] = {
                                          lep_0.Pt()/1000., 
                                          lep_0.Eta(), 
                                          lep_0.E()/1000., 
                                          lep_0.Phi(), 
                                          lep_charge[indx0],
                                          (double)lep_type[indx0], 
                                          lep_ptcone30[indx0], 
                                          lep_etcone20[indx0], 
                                          lep_z0[indx0], 
                                          lep_trackd0pvunbiased[indx0]
                                         };
    double names_of_traillep_variable[] = {
                                          lep_1.Pt()/1000., 
                                          lep_1.Eta(), 
                                          lep_1.E()/1000., 
                                          lep_1.Phi(), 
                                          lep_charge[indx1],
                                          (double)lep_type[indx1], 
                                          lep_ptcone30[indx1], 
                                          lep_etcone20[indx1], 
                                          lep_z0[indx1], 
                                          lep_trackd0pvunbiased[indx1]
                                         };
    double names_of_jet_variable[] = {
                                      (double)jet_n, 
                                      jet_pt[0]/1000., 
                                      jet_eta[0], 
                                      jet_m[0]/1000., 
                                      jet_jvf[0], 
                                      jet_MV1[0]
                                     };
    
    TString histonames_of_global_variable[] = {
                                               "hist_vismass",
                                               "hist_etmiss",
                                               "hist_vxp_z",
                                               "hist_pvxp_n", 
                                               "hist_mt"
                                              };
    TString histonames_of_leadlep_variable[] = {
                                                "hist_leadleptpt", 
                                                "hist_leadlepteta",
                                                "hist_leadleptE",
                                                "hist_leadleptphi",
                                                "hist_leadleptch",
                                                "hist_leadleptID",
                                                "hist_leadlept_ptc",
                                                "hist_leadleptetc",
                                                "hist_leadlepz0",
                                                "hist_leadlepd0"
                                               };
    TString histonames_of_traillep_variable[] = {
                                                "hist_trailleptpt", 
                                                "hist_traillepteta",
                                                "hist_trailleptE",
                                                "hist_trailleptphi",
                                                "hist_trailleptch",
                                                "hist_trailleptID",
                                                "hist_traillept_ptc",
                                                "hist_trailleptetc",
                                                "hist_traillepz0",
                                                "hist_traillepd0"
                                               };
    
    int length_global = sizeof(names_of_global_variable)
                        /
                        sizeof(names_of_global_variable[0]);
    int length_leadlep = sizeof(names_of_leadlep_variable)
                        /
                        sizeof(names_of_leadlep_variable[0]);
    int length_traillep = sizeof(names_of_traillep_variable)
                        /
                        sizeof(names_of_traillep_variable[0]);
    
    for (int i=0; i<length_global; i++)
    {
        FillHistogramsGlobal( names_of_global_variable[i], 
                              weight, 
                              histonames_of_global_variable[i]
                            );
    }
    for (int i=0; i<length_leadlep; i++)
    {
        FillHistogramsLeadlept( names_of_leadlep_variable[i], 
                                weight, 
                                histonames_of_leadlep_variable[i]
                              );
    }
    for (int i=0; i<length_traillep; i++)
    {
        FillHistogramsTraillept( names_of_traillep_variable[i], 
                                weight, 
                                histonames_of_traillep_variable[i]
                              );
    }

    hist_deltaphi->Fill(TMath::Abs(Lepton1.DeltaPhi(Lepton2)),weight);
    hist_ptleptons->Fill(Lepton1_2.Pt()/1000.,weight);
 
    return kTRUE;
}

void TopAnalysis::SlaveTerminate()
{
    // The SlaveTerminate() function is called after all entries or objects
    // have been processed. When running with PROOF SlaveTerminate() is called
    // on each slave server.
}

void TopAnalysis::Terminate()
{
    // The Terminate() function is the last function to be called during
    // a query. It always runs on the client, it can be used to present
    // the results graphically or save the results to file.

    name="output_Top/"+name+".root";

    const char* filename = name.c_str();

    TFile physicsoutput_Top(filename,"recreate");
    WriteHistograms();
    physicsoutput_Top.Close();
}
