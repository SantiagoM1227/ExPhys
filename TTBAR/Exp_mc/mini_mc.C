#define mini_mc_cxx
#include "mini_mc.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Graph_Histogram(TH1F *histogram1, TH1F *histogram2, const char* title, const char* Label1, const char* Label2, bool log){
   
   
   std::string Folder = "./Tarea3_output/";
   std::string Title  = title;
   std::string Format = ".pdf";
   std::string Path = Folder+title+Format;
   
   const char *path = Path.c_str();
   
   THStack *h_stack = new THStack("h_stack","");

   
   histogram1->SetMarkerSize(1);
   histogram1->SetMarkerStyle(20);
   histogram1->SetMarkerColor(kRed);
   
   histogram2->SetLineStyle(7);
   histogram2->SetLineWidth(3);
   histogram2->SetLineColor(kBlack);
      
   TCanvas *canvas = new TCanvas(title,"",800,600);
   
   histogram1->Draw("ep");
   histogram2->Draw("histsame");
   
   TLegend *leg = new TLegend(0.7, 0.8, 0.89, 0.6);
   leg->SetBorderSize(0);
   leg->SetTextFont(42);
   leg->SetTextSize(0.035);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   leg->SetHeader("#sqrt{s} = 8 TeV, 1 fb^{-1}");
   leg->AddEntry(histogram1,"Data","p");
   leg->AddEntry(histogram2,"MonteCarlo","f");
   
  
   
   leg -> Draw();
   if (log){canvas ->SetLogy();}
   
   canvas->Print(path);
}

void Graph_Histogram_one(TH1F *histogram1, const char* title, const char* Label1, bool log){
   
   
   std::string Folder = "./Tarea3_output/";
   std::string Title  = title;
   std::string Format = ".pdf";
   std::string Path = Folder+title+Format;
   
   const char *path = Path.c_str();
   
   TCanvas *canvas = new TCanvas(title,"",800,600);
   histogram1 -> SetTitle(title);
   histogram1 -> SetMarkerColor(kRed);
   histogram1 -> SetMarkerStyle(20);
   histogram1 -> Draw("*H");
   auto legend = new TLegend(0.7, 0.8, 0.89, 0.6);
   legend -> SetBorderSize(0);
;
   legend -> AddEntry(histogram1, Label1, "lep");  
   
   legend -> Draw();
   if (log){canvas ->SetLogy();}
   
   canvas->Print(path);
}




void mini_mc::Loop()
{

   
   ofstream Cutflow("cutflow_mc.txt");
   ofstream absolute_efficiency("absolute_efficiency_mc.txt");
   ofstream relative_efficiency("relative_efficiency_mc.txt");
   
   
   
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   
   
   Float_t weight = (1000.*137.29749)/(1500000.*0.072212854);
   
   //declare auxiliary variables
   
   vector<double> cut; cut.resize(8,0);
   
   
   
   for (Int_t jentry=0; jentry<nentries;jentry++) {
      GetEntry(jentry);
      
      //auxiliary variables
      TLorentzVector Lepton_before = TLorentzVector();
      TLorentzVector MeT_before = TLorentzVector();
      MeT_before.SetPtEtaPhiM(met_et,0.,met_phi,0.);
      int n_bjet_before =0;
      
      
      
      //SF
      Float_t scaleFactor = scaleFactor_ELE*scaleFactor_MUON*scaleFactor_TRIGGER;
      //EventW
      Float_t eventWeight = mcWeight*scaleFactor_PILEUP*scaleFactor_ZVERTEX;
      //weight = SF * EventW
      Double_t weight = scaleFactor*eventWeight;
      
      
            
      //Fill Histograms    
      
      for (int n_aux_lep = 0; n_aux_lep < lep_n;n_aux_lep ++){
      	hist_lep_pt  -> Fill(lep_pt[n_aux_lep]/1000.,weight);
      	hist_lep_eta -> Fill(lep_eta[n_aux_lep],weight);      	Lepton_before.SetPtEtaPhiM(lep_pt[n_aux_lep],lep_eta[n_aux_lep],lep_phi[n_aux_lep],lep_E[n_aux_lep]);
      	Float_t mTW = sqrt(2*Lepton_before.Pt()*MeT_before.Et()*(1-TMath::Cos(Lepton_before.DeltaPhi(MeT_before))));
      	hist_mtW     -> Fill(mTW/1000.,weight);
      }
   
      hist_njets_before   -> Fill(jet_n);
      
      for (int n_aux_jet = 0; n_aux_jet < jet_n;n_aux_jet ++){
      	hist_jet_pt  -> Fill(jet_pt[n_aux_jet]/1000.,weight);
      	hist_jet_eta -> Fill(lep_eta[n_aux_jet],weight);
      	hist_jet_jvf  -> Fill(jet_jvf[n_aux_jet],weight);
      	hist_jet_mv1 -> Fill(jet_MV1[n_aux_jet],weight);
      	if (jet_MV1[n_aux_jet] >= 0.7892){n_bjet_before++;}
      	
      }

      
      hist_nbjet -> Fill(n_bjet_before,weight);
      hist_met -> Fill(met_et/1000.,weight);
      
      
      
      
      
      
      //1st cut: good vertex
      if (!hasGoodVertex) continue;
      cut[0]++;
      cutflow -> Fill(1,1.0);
  
      //2nd cut: Trigger
      if (!trigE && !trigM) continue;
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
      cutflow-> Fill(3,1.0);
      cut[2]++;
	  
      int n_jets = 0;
      int n_bjets = 0;
	  
      //# of jets distribution
      hist_njets_after -> Fill(jet_n,1.0);
	  
      //4th cut: At least 4 jets
	 
      if (jet_n<4) continue;
      cutflow -> Fill(4,1.0);
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
      cutflow -> Fill(5,1.0);
      cut[4]++;
      
	 
      //6th cut: at least one b-jet
      if (n_bjets<2) continue;
      cutflow -> Fill(6,1.0);
      cut[5]++;
	 
      //7th cut: MET > 30 GeV
	 
      if(met_et<30000.) continue;
      cutflow -> Fill(7,1.0);
      cut[6]++;
	 
      //TLorentzVector definition
      TLorentzVector Lepton = TLorentzVector();
      TLorentzVector MeT = TLorentzVector();
      
      MeT.SetPtEtaPhiM(met_et,0.,met_phi,0.);
      Lepton.SetPtEtaPhiM(lep_pt[lep_index],lep_eta[lep_index],lep_phi[lep_index],lep_E[lep_index]); 	 
      Float_t mTW = sqrt(2*Lepton.Pt()*MeT.Et()*(1-cos(Lepton.DeltaPhi(MeT))));
      //8th cut mTW > 30GeV
        
      if (mTW<30000.) continue;
      cutflow -> Fill(8,1.0);
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
