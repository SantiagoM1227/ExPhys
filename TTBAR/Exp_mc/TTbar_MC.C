#include "mini_mc.C"

void TTbar_MC(void){
   
   mini_mc m_mc;
   m_mc.Loop();
   	
   Graph_Histogram_one(m_mc.cutflow,"cutflow for MonteCarlo", "cutflow for MonteCarlo", true);
   
   
   Graph_Histogram_one(m_mc.hist_lep_pt, "Lepton pT for MonteCarlo", "Lepton pT for MonteCarlo", true);
   
   Graph_Histogram_one(m_mc.hist_lep_eta, "Lepton eta for MonteCarlo",  "Lepton eta for MonteCarlo", false);
   
   Graph_Histogram_one( m_mc.hist_njets_before, "Number of Jets for MonteCarlo",  "Number of Jets for MonteCarlo", false);
   
   Graph_Histogram_one( m_mc.hist_njets_before, "Number of Jets for MonteCarlo",  "Number of Jets for MonteCarlo", false);
   
   Graph_Histogram_one( m_mc.hist_njets_after, "Number of Jets after cut for MonteCarlo",  "Number of Jets after cut for MonteCarlo", false);
   
   Graph_Histogram_one(m_mc.hist_jet_pt, "Jet pT for MonteCarlo",  "Jet pT for MonteCarlo", true);
   
   Graph_Histogram_one(m_mc.hist_jet_eta, "Jet eta for MonteCarlo",  "Jet eta for MonteCarlo", false);
   
   Graph_Histogram_one(m_mc.hist_jet_jvf, "Jet JVF for MonteCarlo", "Jet JVF score for MonteCarlo", false);
   
   Graph_Histogram_one(m_mc.hist_jet_mv1, "Jet MV1 for MonteCarlo",  "Jet MV1 score for MonteCarlo", false);
   
   Graph_Histogram_one(m_mc.hist_nbjet, "Number of b-Jets for MonteCarlo",  "Number of b-Jets for MonteCarlo", false);
   
   Graph_Histogram_one(m_mc.hist_met, "meT for MonteCarlo",  "meT for MonteCarlo", false);
   
   Graph_Histogram_one(m_mc.hist_mtW, "mTW for MonteCarlo",  "mTW for MonteCarlo", false);
   
   
   
}
