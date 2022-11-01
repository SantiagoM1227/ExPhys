#define mini_mc_cxx
#include "mini_mc.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>



void mini_mc::Loop()
{

   
   ofstream Cutflow("cutflow_mc.txt");
   ofstream absolute_efficiency("absolute_efficiency_mc.txt");
   ofstream relative_efficiency("relative_efficiency_mc.txt");
   
   Long64_t L_Data = 1000.
   Long64_t L_MC = 
   
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   
   
   
   //declare auxiliary variables
   
   vector<double> cut; cut.resize(8,0);
   
   TLorentzVector Lepton_before = TLorentzVector();
   TLorentzVector MeT_before = TLorentzVector();
   MeT_before.SetPtEtaPhiM(met_et,0.,met_phi,0.);
   int n_bjet_before =0;
   
   for (Int_t jentry=0; jentry<nentries;jentry++) {
      GetEntry(jentry);
      //Fill Histograms
      
      for (int n_aux_lep = 0; n_aux_lep < lep_n;n_aux_lep ++){
      	hist_lep_pt  -> Fill(lep_pt[n_aux_lep]/1000.);
      	hist_lep_eta -> Fill(lep_eta[n_aux_lep]);      	Lepton_before.SetPtEtaPhiM(lep_pt[n_aux_lep],lep_eta[n_aux_lep],lep_phi[n_aux_lep],lep_E[n_aux_lep]);
      	Float_t mTW = sqrt(2*Lepton_before.Pt()*MeT_before.Et()*(1-cos(Lepton_before.DeltaPhi(MeT_before))));
      	hist_mtW     -> Fill(mTW);
      }
   
      hist_njets_before   -> Fill(jet_n);
      
      for (int n_aux_jet = 0; n_aux_jet < jet_n;n_aux_jet ++){
      	hist_jet_pt  -> Fill(jet_pt[n_aux_jet]/1000.);
      	hist_jet_eta -> Fill(lep_eta[n_aux_jet]);
      	hist_jet_jvf  -> Fill(jet_jvf[n_aux_jet]);
      	hist_jet_mv1 -> Fill(jet_MV1[n_aux_jet]);
      	if (jet_MV1[n_aux_jet] >= 0.7892){n_bjet_before++;}
      	
      }

      
      hist_nbjet -> Fill(n_bjet_before);
      hist_met -> Fill(met_et);
      
      
      //define evtw
      /*
      Float_t evtw_PILEUP = mcWeight*scaleFactor_PILEUP;
      Float_t evtw_ELE = mcWeight*scaleFactor_ELE;
      Float_t evtw_MUON = mcWeight*scaleFactor_MUON;
      Float_t evtw_BTAG = mcWeight*scaleFactor_BTAG;
      Float_t evtw_TRIGGER = mcWeight*scaleFactor_TRIGGER;
      Float_t evtw_JVFSF = mcWeight*scaleFactor_JVFSF;
      Float_t evtw_ZVERTEX = mcWeight*scaleFactor_ZVERTEX;
      */
      
      Float_t SF = scaleFactor_PILEUP*scaleFactor_ELE*scaleFactor_MUON*scaleFactor_BTAG *scaleFactor_TRIGGER*scaleFactor_JVFSF*scaleFactor_ZVERTEX;
      
      
      //1st cut: good vertex
      if (!good_vtx) continue;
      cut[0]++;
      cutflow -> Fill(1,1.0);
  
      //2nd cut: Trigger
      if (!e_trig && !mu_trig) continue;
      cut[1]++;
      cutflow->Fill(2,1.0);	
	  
      //select good leptons
	  
      int n_mu = 0;
      int n_el = 0;
      int n_lep = 0;
      int lep_index;
      
      //loop over leptons
	
      for (unsigned int i = 0; i<lep_n; i++){
        if (lep_pt[i]<25000.) continue;
	if (lep_ptcone30[i]/lep_pt[i] > 0.15) continue;
	if (lep_etcone20[i]/lep_pt[i] > 0.15) continue;
	if (lep_type[i]==13 and TMath::Abs(lep_eta[i])< 2.5){n_mu++;lep_index = i;}
	if(lep_type[i]==11 and ((TMath::Abs(lep_eta[i])<2.47 and TMath::Abs(lep_eta[i])>1.52) or TMath::Abs(lep_eta[i])<1.37 )){n_el++;lep_index = i;}
     }
	  
      n_lep = n_mu+n_el;
          
      //3rd cut: processes with ONLY ONE good LEPTON
      if (n_lep!=1)continue;
      cutflow-> Fill(3);
      cut[2]++;
	  
      int n_jets = 0;
      int n_bjets = 0;
	  
      //# of jets distribution
      hist_njets -> Fill(jet_n);
	  
      //4th cut: At least 4 jets
	 
      if (jet_n<4) continue;
      cutflow -> Fill(4);
      cut[3]++;
	
      for (unsigned int j=0; j<jet_n; j++){
        if (jet_pt[j]<=25000.) continue;
        if (TMath::Abs(jet_eta[j])>=2.5) continue;
        if (jet_jvf[j] <= 0.5&&jet_pt[j]<50000.&& TMath::Abs(jet_eta[j])<2.4) continue;
        n_jets++;
        if (jet_MV1[j] >= 0.7892){n_bjets++;}
      }
      
      //5th cut: At least 4 good jets
      if (n_jets<4) continue;
      cutflow -> Fill(5);
      cut[4]++;
      
	 
      //6th cut: at least one b-jet
      if (n_bjets<2) continue;
      cutflow -> Fill(6);
      cut[5]++;
	 
      //7th cut: MET > 30 GeV
	 
      if(met_et<30000.) continue;
      cutflow -> Fill(7);
      cut[6]++;
	 
      //TLorentzVector definition
      TLorentzVector Lepton = TLorentzVector();
      TLorentzVector MeT = TLorentzVector();
      
      MeT.SetPtEtaPhiM(met_et,0.,met_phi,0.);
      Lepton.SetPtEtaPhiM(lep_pt[lep_index],lep_eta[lep_index],lep_phi[lep_index],lep_E[lep_index]); 	 
      Float_t mTW = sqrt(2*Lepton.Pt()*MeT.Et()*(1-cos(Lepton.DeltaPhi(MeT))));
      //8th cut mTW > 30GeV
        
      if (mTW<30000.) continue;
      cutflow -> Fill(8);
      cut[7]++; 
        
      
	 
            
   }
   std::cout << "Done!" << std::endl;
   std::cout << "All events: " << nentries << std::endl;
   for (int k=0; k<8; k++){
     Cutflow<< "Cut"<<k+1<<": "<< cut[k] << std::endl;
   }
   for (int k=0; k<8; k++){
     absolute_efficiency<< "efficiency "<<k+1<<": "<< float(cut[k])/float(cut[0]) << std::endl;
   }
   for (int k=1; k<8; k++){
     relative_efficiency<< "relative efficiency "<<k<<": "<< float(cut[k])/float(cut[k-1]) << std::endl;
   }
  
   
}
