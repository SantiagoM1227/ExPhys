#include "mini.C"
#include "mini_mc.C"


void TTbar_comp(void){
   
   mini m;
   m.Loop();
   
   mini_mc m_mc;
   m_mc.Loop();
   	
   Graph_Histogram(m.cutflow,m_mc.cutflow, "cutflow", "cutflow for Data", "cutflow for MonteCarlo", true);
   
   Graph_Histogram(m.hist_lep_pt,m_mc.hist_lep_pt, "Lepton pT", "Lepton pT for Data", "Lepton pT for MonteCarlo", true);
   
   Graph_Histogram(m.hist_lep_eta,m_mc.hist_lep_eta, "Lepton eta", "Lepton eta for Data", "Lepton eta for MonteCarlo", false);
   
   Graph_Histogram(m.hist_njets_before, m_mc.hist_njets_before, "Number of Jets", "Number of Jets for Data", "Number of Jets for MonteCarlo", false);
   
   Graph_Histogram(m.hist_njets_before, m_mc.hist_njets_before, "Number of Jets", "Number of Jets for Data", "Number of Jets for MonteCarlo", false);
   
   Graph_Histogram(m.hist_njets_after, m_mc.hist_njets_after, "Number of Jets after cut", "Number of Jets after cut for Data", "Number of Jets after cut for MonteCarlo", false);
   
   Graph_Histogram(m.hist_jet_pt,m_mc.hist_jet_pt, "Jet pT", "Jet pT for Data", "Jet pT for MonteCarlo", true);
   
   Graph_Histogram(m.hist_jet_eta,m_mc.hist_jet_eta, "Jet eta", "Jet eta for Data", "Jet eta for MonteCarlo", false);
   
   Graph_Histogram(m.hist_jet_jvf,m_mc.hist_jet_jvf, "Jet JVF", "Jet JVF score for Data", "Jet JVF score for MonteCarlo", false);
   
   Graph_Histogram(m.hist_jet_mv1,m_mc.hist_jet_mv1, "Jet MV1", "Jet MV1 score for Data", "Jet MV1 score for MonteCarlo", false);
   
   Graph_Histogram(m.hist_nbjet, m_mc.hist_nbjet, "Number of b-Jets", "Number of b-Jets for Data", "Number of b-Jets for MonteCarlo", false);
   
   Graph_Histogram(m.hist_met,m_mc.hist_met, "meT", "meT for Data", "meT for MonteCarlo", false);
   
   Graph_Histogram(m.hist_mtW,m_mc.hist_mtW, "mTW", "mTW for Data", "mTW for MonteCarlo", false);
   
   
}
