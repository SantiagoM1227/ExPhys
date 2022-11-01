#include "mini.C"
#include "mini_mc.C"


void TTbar_comp{
   
   mini m;
   m.Loop();
   
   mini_mc m_mc;
   m_mc.Loop();
   	
	
   TCanvas *canvas_cutflow = new TCanvas("Cutflow","",800,600);
   cutflow-> SetTitle("cutflow");
   m_mc.cutflow->Draw("");
   m_mc.cutflow ->SetMarkerColor("kred")
   m_mc.cutflow ->SetMarkerStyle(20)
   m.cutflow->Draw("same");
   m_mc.cutflow ->SetMarkerStyle(21)
   canvas_cutflow->SetLogy();
   canvas_cutflow->Print("./Tarea3_output/cutflow_comp.pdf");
   
   TCanvas *canvas_hist_lep_pt = new TCanvas("lep_pt","",800,600);
   hist_lep_pt-> SetTitle("pT for Leptons");
   hist_lep_pt->Draw("");
   canvas_hist_lep_pt->SetLogy();
   canvas_hist_lep_pt->Print("./Tarea3_output/hist_lep_pt_comp.pdf");
   
   
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
