#define mini_cxx
#include "mini.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <fstream>

void mini::Loop()
{
   
   ofstream Cutflow("cutflow.txt");
   ofstream absolute_efficiency("absolute_efficiency.txt");
   ofstream relative_efficiency("relative_efficiency.txt");
   
   
   
   if (fChain == 0) return;
   
   //# of entries and bytes
   
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   
   // Declare Histograms
   	
   TH1F *cutflow = new TH1F("Cutflow","Cutflow; Cut; Events",10,0,10);

   TH1F *hist_lep_pt = new TH1F("pT for Leptons","pT for Leptons; pT; Events",140,0,140);

   TH1F *hist_lep_eta = new TH1F("eta for Leptons","eta for Leptons; eta; Events",60,-3,3);
   
   TH1F *hist_njets_before  = new TH1F("Number of Jets before cut","n-jets; Jet multiplicity; Events",10,0,10);
   TH1F *hist_njets_after = new TH1F("Number of Jets","n-jets; Jet multiplicity; Events",10,0,10);
   
   TH1F *hist_jet_pt = new TH1F("pT for Jets","pT for Jets; pT; Events",200,0,200);

   TH1F *hist_jet_eta = new TH1F("eta for Jets","eta for Jets; eta; Events",60,-3,3);
   
   TH1F *hist_jet_jvf = new TH1F("JVF score for Jets","JVF score for Jets; JVF score; Events",100,0,1);
   
   TH1F *hist_jet_mv1 = new TH1F("Mv1 score for Jets","Mv1 score for Jets; Mv1 score; Events",100,0,1);
   
   TH1F *hist_nbjet = new TH1F("Number of b-Jets","Number of b-Jets; Number of b-Jets; Events",10,0,10);

   TH1F *hist_met = new TH1F("MET score for Jets","MET score for Jets; MET score; Events",150,0,150);
   
   TH1F *hist_mtW = new TH1F("mT W","mT W; mT W; Events",150,0,150);
   
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
      	hist_mtW     -> Fill(mTW/1000.);
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
      hist_met -> Fill(met_et/1000.);
      
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
      hist_njets_after -> Fill(jet_n);
	  
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
   
   TCanvas *canvas_cutflow = new TCanvas("Cutflow","",800,600);
   cutflow-> SetTitle("cutflow");
   cutflow->Draw("");
   canvas_cutflow->SetLogy();
   canvas_cutflow->Print("./Tarea2_output/cutflow.pdf");
   
   TCanvas *canvas_hist_lep_pt = new TCanvas("lep_pt","",800,600);
   hist_lep_pt-> SetTitle("pT for Leptons");
   hist_lep_pt->Draw("");
   canvas_hist_lep_pt->SetLogy();
   canvas_hist_lep_pt->Print("./Tarea2_output/hist_lep_pt.pdf");
   
   
   TCanvas *canvas_hist_lep_eta = new TCanvas("lep_eta","",800,600);
   hist_lep_eta-> SetTitle("eta for Leptons");
   hist_lep_eta->Draw("");
   canvas_hist_lep_eta->Print("./Tarea2_output/hist_lep_eta.pdf");
   
   
   TCanvas *canvas_hist_njets_before = new TCanvas("njets before","",800,600);
   hist_njets_before-> SetTitle("Number of jets before cut");
   hist_njets_before->Draw("");
   canvas_hist_njets_before->SetLogy();
   canvas_hist_njets_before->Print("./Tarea2_output/hist_njets_before.pdf");   
   
   TCanvas *canvas_hist_njets_after = new TCanvas("njets after","",800,600);
   hist_njets_after-> SetTitle("Number of jets after cut");
   hist_njets_after->Draw("");
   canvas_hist_njets_after->SetLogy();
   canvas_hist_njets_after->Print("./Tarea2_output/hist_njets_after.pdf"); 
   
   TCanvas *canvas_hist_jet_pt = new TCanvas("Jet_pt","",800,600);
   hist_jet_pt-> SetTitle("pT for Jets");
   hist_jet_pt->Draw("");
   canvas_hist_jet_pt->SetLogy();
   canvas_hist_jet_pt->Print("./Tarea2_output/hist_jet_pt.pdf");
   
   
   TCanvas *canvas_hist_jet_eta = new TCanvas("jet_eta","",800,600);
   hist_jet_eta-> SetTitle("eta for Jets");
   hist_jet_eta->Draw("");
   canvas_hist_jet_eta->Print("./Tarea2_output/hist_jet_eta.pdf");
   
   
   TCanvas *canvas_hist_jet_jvf = new TCanvas("Jet_jvf","",800,600);
   hist_jet_jvf-> SetTitle("JVF score for Jets");
   hist_jet_jvf->Draw("");
   canvas_hist_jet_jvf->Print("./Tarea2_output/hist_jet_jvf.pdf");
   
   
   TCanvas *canvas_hist_jet_mv1 = new TCanvas("jet_mv1","",800,600);
   hist_jet_mv1-> SetTitle("MV1 score for Jets");
   hist_jet_mv1->Draw("");
   canvas_hist_jet_mv1->Print("./Tarea2_output/hist_jet_mv1.pdf");
   
   
   TCanvas *canvas_hist_nbjet = new TCanvas("n b-Jets","",800,600);
   hist_nbjet-> SetTitle("Number of jets");
   hist_nbjet->Draw("");
   canvas_hist_nbjet->SetLogy();
   canvas_hist_nbjet->Print("./Tarea2_output/hist_nbjets.pdf");
   
   
   TCanvas *canvas_hist_met = new TCanvas("met","",800,600);
   hist_met-> SetTitle("meT");
   hist_met->Draw("");
   canvas_hist_met->Print("./Tarea2_output/hist_mets.pdf");
   
   
   TCanvas *canvas_hist_mtW = new TCanvas("mTw","",800,600);
   hist_mtW-> SetTitle("Transverse mass W-boson");
   hist_mtW->Draw("");
   canvas_hist_mtW->Print("./Tarea2_output/hist_mtW.pdf");
   
   
   
   
   
   
   
   
   
}
