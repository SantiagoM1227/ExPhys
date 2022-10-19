#define mini_cxx
#include "mini.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <fstream>


void mini::Loop()
{
   ofstream Cutflow("Cutflow.txt");
   ofstream absolute_efficiency("absolute_efficiency.txt");
   ofstream relative_efficiency("relative_efficiency.txt");
	
   if (fChain == 0) return;
   
   //# of entries and bytes
   
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   
   // Declare Histograms
   	
   TH1F *cutflow = new TH1F("Cutflow","Cutflow; Cut; Events",10,0,10);

   TH1F *hist_njets = new TH1F("Number of jets","n-jets; Jet multiplicity; Events",10,0,10);
   
   //declare auxiliary variables
   
   vector<int> cut; cut.resize(8,0);
   
   
   for (Int_t jentry=0; jentry<nentries;jentry++) {
      GetEntry(jentry);
      //1st cut: good vertex
      if (!good_vtx) continue;
      cut[0]++;
      cutflow -> Fill(1);
  
      //2nd cut: Trigger
      if (!e_trig && !mu_trig) continue;
      cut[1]++;
      cutflow->Fill(2);	
	  
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
        if (jet_pt[j]<2500.) continue;
        if (TMath::Abs(jet_eta[j])>2.4&& jet_pt[j]>50000) continue;
        if (jet_jvf[j] < 0.5) continue;
        n_jets++;
        if (jet_MV1[j] > 0.7892){n_bjets++;}
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
   std::cout << "All events:" << nentries << std::endl;
   for (int k=0; k<8; k++){
     Cutflow<< "Cut"<<k+1<<": "<< cut[k] << std::endl;
   }
   for (int k=0; k<8; k++){
     absolute_efficiency<< "efficiency "<<k+1<<": "<< float(cut[k])/float(cut[0]) << std::endl;
   }
   for (int k=1; k<8; k++){
     relative_efficiency<< "relative efficiency "<<k<<": "<< float(cut[k])/float(cut[k-1]) << std::endl;
   }
   
   
   
   TCanvas *canvas_cutflow = new TCanvas("Cutflow","",800,600);
   cutflow-> SetTitle("cutflow");
   cutflow->Draw("");
   canvas_cutflow->SetLogy();
   canvas_cutflow->Print("./Tarea2_output/cutflow.pdf");
   
   TCanvas *canvas_hist_njets = new TCanvas("Cutflow","",800,600);
   hist_njets-> SetTitle("Number of jets");
   hist_njets->Draw("");
   canvas_hist_njets->SetLogy();
   canvas_hist_njets->Print("./Tarea2_output/hist_njets.pdf");
   
   
   
   
   
   
   
   
   
}
