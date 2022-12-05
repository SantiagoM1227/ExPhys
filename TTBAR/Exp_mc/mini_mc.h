//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Oct 31 20:40:33 2022 by ROOT version 6.26/06
// from TTree mini/4-vectors + variables required for scaling factors
// found on file: ../ttbar_8TeV.root
//////////////////////////////////////////////////////////

#ifndef mini_mc_h
#define mini_mc_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class mini_mc {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declare Histograms
   	
   TH1F *cutflow = new TH1F("Cutflow_mc","Cutflow; Cut; Events",10,0,10);

   TH1F *hist_lep_pt = new TH1F("pT for Leptons_mc","pT for Leptons; pT; Events",140,0,140);

   TH1F *hist_lep_eta = new TH1F("eta for Leptons_mc","eta for Leptons; eta; Events",60,-3,3);
   
   TH1F *hist_njets_before  = new TH1F("Number of Jets before cut_mc","n-jets; Jet multiplicity; Events",10,0,10);
   TH1F *hist_njets_after = new TH1F("Number of Jets_mc","n-jets; Jet multiplicity; Events",10,0,10);
   
   TH1F *hist_jet_pt = new TH1F("pT for Jets_mc","pT for Jets; pT; Events",200,0,200);

   TH1F *hist_jet_eta = new TH1F("eta for Jets_mc","eta for Jets; eta; Events",60,-3,3);
   
   TH1F *hist_jet_jvf = new TH1F("JVF score for Jets_mc","JVF score for Jets; JVF score; Events",100,0,1);
   
   TH1F *hist_jet_mv1 = new TH1F("Mv1 score for Jets_mc","Mv1 score for Jets; Mv1 score; Events",100,0,1);
   
   TH1F *hist_nbjet = new TH1F("Number of b-Jets_mc","Number of b-Jets; Number of b-Jets; Events",10,0,10);

   TH1F *hist_met = new TH1F("MET score for Jets_mc","MET score for Jets; MET score; Events",150,0,150);
   
   TH1F *hist_mtW = new TH1F("mTW_mc","mT W; mT W; Events",150,0,150);

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           runNumber;
   Int_t           eventNumber;
   Int_t           channelNumber;
   Float_t         mcWeight;
   Int_t           pvxp_n;
   Float_t         vxp_z;
   Float_t         scaleFactor_PILEUP;
   Float_t         scaleFactor_ELE;
   Float_t         scaleFactor_MUON;
   Float_t         scaleFactor_BTAG;
   Float_t         scaleFactor_TRIGGER;
   Float_t         scaleFactor_JVFSF;
   Float_t         scaleFactor_ZVERTEX;
   Bool_t          trigE;
   Bool_t          trigM;
   Bool_t          passGRL;
   Bool_t          hasGoodVertex;
   UInt_t          lep_n;
   Bool_t          lep_truthMatched[6];   //[lep_n]
   UShort_t        lep_trigMatched[6];   //[lep_n]
   Float_t         lep_pt[6];   //[lep_n]
   Float_t         lep_eta[6];   //[lep_n]
   Float_t         lep_phi[6];   //[lep_n]
   Float_t         lep_E[6];   //[lep_n]
   Float_t         lep_z0[6];   //[lep_n]
   Float_t         lep_charge[6];   //[lep_n]
   UInt_t          lep_type[6];   //[lep_n]
   UInt_t          lep_flag[6];   //[lep_n]
   Float_t         lep_ptcone30[6];   //[lep_n]
   Float_t         lep_etcone20[6];   //[lep_n]
   Float_t         lep_trackd0pvunbiased[6];   //[lep_n]
   Float_t         lep_tracksigd0pvunbiased[6];   //[lep_n]
   Float_t         met_et;
   Float_t         met_phi;
   UInt_t          jet_n;
   UInt_t          alljet_n;
   Float_t         jet_pt[16];   //[alljet_n]
   Float_t         jet_eta[16];   //[alljet_n]
   Float_t         jet_phi[16];   //[alljet_n]
   Float_t         jet_E[16];   //[alljet_n]
   Float_t         jet_m[16];   //[alljet_n]
   Float_t         jet_jvf[16];   //[alljet_n]
   Int_t           jet_trueflav[16];   //[alljet_n]
   Int_t           jet_truthMatched[16];   //[alljet_n]
   Float_t         jet_SV0[16];   //[alljet_n]
   Float_t         jet_MV1[16];   //[alljet_n]

   // List of branches
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_channelNumber;   //!
   TBranch        *b_mcWeight;   //!
   TBranch        *b_pvxp_n;   //!
   TBranch        *b_vxp_z;   //!
   TBranch        *b_scaleFactor_PILEUP;   //!
   TBranch        *b_scaleFactor_ELE;   //!
   TBranch        *b_scaleFactor_MUON;   //!
   TBranch        *b_scaleFactor_BTAG;   //!
   TBranch        *b_scaleFactor_TRIGGER;   //!
   TBranch        *b_scaleFactor_JVFSF;   //!
   TBranch        *b_scaleFactor_ZVERTEX;   //!
   TBranch        *b_trigE;   //!
   TBranch        *b_trigM;   //!
   TBranch        *b_passGRL;   //!
   TBranch        *b_hasGoodVertex;   //!
   TBranch        *b_lep_n;   //!
   TBranch        *b_lep_truthMatched;   //!
   TBranch        *b_lep_trigMatched;   //!
   TBranch        *b_lep_pt;   //!
   TBranch        *b_lep_eta;   //!
   TBranch        *b_lep_phi;   //!
   TBranch        *b_lep_E;   //!
   TBranch        *b_lep_z0;   //!
   TBranch        *b_lep_charge;   //!
   TBranch        *b_lep_type;   //!
   TBranch        *b_lep_flag;   //!
   TBranch        *b_lep_ptcone30;   //!
   TBranch        *b_lep_etcone20;   //!
   TBranch        *b_lep_trackd0pvunbiased;   //!
   TBranch        *b_lep_tracksigd0pvunbiased;   //!
   TBranch        *b_met_et;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_jet_n;   //!
   TBranch        *b_alljet_n;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_E;   //!
   TBranch        *b_jet_m;   //!
   TBranch        *b_jet_jvf;   //!
   TBranch        *b_jet_trueflav;   //!
   TBranch        *b_jet_truthMatched;   //!
   TBranch        *b_jet_SV0;   //!
   TBranch        *b_jet_MV1;   //!

   mini_mc(TTree *tree=0);
   virtual ~mini_mc();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   
};

#endif

#ifdef mini_mc_cxx


mini_mc::mini_mc(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../ttbar_8TeV.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../../ttbar_8TeV.root");
      }
      f->GetObject("mini",tree);

   }
   Init(tree);
}

mini_mc::~mini_mc()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t mini_mc::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t mini_mc::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void mini_mc::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);
   
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("channelNumber", &channelNumber, &b_channelNumber);
   fChain->SetBranchAddress("mcWeight", &mcWeight, &b_mcWeight);
   fChain->SetBranchAddress("pvxp_n", &pvxp_n, &b_pvxp_n);
   fChain->SetBranchAddress("vxp_z", &vxp_z, &b_vxp_z);
   fChain->SetBranchAddress("scaleFactor_PILEUP", &scaleFactor_PILEUP, &b_scaleFactor_PILEUP);
   fChain->SetBranchAddress("scaleFactor_ELE", &scaleFactor_ELE, &b_scaleFactor_ELE);
   fChain->SetBranchAddress("scaleFactor_MUON", &scaleFactor_MUON, &b_scaleFactor_MUON);
   fChain->SetBranchAddress("scaleFactor_BTAG", &scaleFactor_BTAG, &b_scaleFactor_BTAG);
   fChain->SetBranchAddress("scaleFactor_TRIGGER", &scaleFactor_TRIGGER, &b_scaleFactor_TRIGGER);
   fChain->SetBranchAddress("scaleFactor_JVFSF", &scaleFactor_JVFSF, &b_scaleFactor_JVFSF);
   fChain->SetBranchAddress("scaleFactor_ZVERTEX", &scaleFactor_ZVERTEX, &b_scaleFactor_ZVERTEX);
   fChain->SetBranchAddress("trigE", &trigE, &b_trigE);
   fChain->SetBranchAddress("trigM", &trigM, &b_trigM);
   fChain->SetBranchAddress("passGRL", &passGRL, &b_passGRL);
   fChain->SetBranchAddress("hasGoodVertex", &hasGoodVertex, &b_hasGoodVertex);
   fChain->SetBranchAddress("lep_n", &lep_n, &b_lep_n);
   fChain->SetBranchAddress("lep_truthMatched", lep_truthMatched, &b_lep_truthMatched);
   fChain->SetBranchAddress("lep_trigMatched", lep_trigMatched, &b_lep_trigMatched);
   fChain->SetBranchAddress("lep_pt", lep_pt, &b_lep_pt);
   fChain->SetBranchAddress("lep_eta", lep_eta, &b_lep_eta);
   fChain->SetBranchAddress("lep_phi", lep_phi, &b_lep_phi);
   fChain->SetBranchAddress("lep_E", lep_E, &b_lep_E);
   fChain->SetBranchAddress("lep_z0", lep_z0, &b_lep_z0);
   fChain->SetBranchAddress("lep_charge", lep_charge, &b_lep_charge);
   fChain->SetBranchAddress("lep_type", lep_type, &b_lep_type);
   fChain->SetBranchAddress("lep_flag", lep_flag, &b_lep_flag);
   fChain->SetBranchAddress("lep_ptcone30", lep_ptcone30, &b_lep_ptcone30);
   fChain->SetBranchAddress("lep_etcone20", lep_etcone20, &b_lep_etcone20);
   fChain->SetBranchAddress("lep_trackd0pvunbiased", lep_trackd0pvunbiased, &b_lep_trackd0pvunbiased);
   fChain->SetBranchAddress("lep_tracksigd0pvunbiased", lep_tracksigd0pvunbiased, &b_lep_tracksigd0pvunbiased);
   fChain->SetBranchAddress("met_et", &met_et, &b_met_et);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("jet_n", &jet_n, &b_jet_n);
   fChain->SetBranchAddress("alljet_n", &alljet_n, &b_alljet_n);
   fChain->SetBranchAddress("jet_pt", jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_eta", jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_E", jet_E, &b_jet_E);
   fChain->SetBranchAddress("jet_m", jet_m, &b_jet_m);
   fChain->SetBranchAddress("jet_jvf", jet_jvf, &b_jet_jvf);
   fChain->SetBranchAddress("jet_trueflav", jet_trueflav, &b_jet_trueflav);
   fChain->SetBranchAddress("jet_truthMatched", jet_truthMatched, &b_jet_truthMatched);
   fChain->SetBranchAddress("jet_SV0", jet_SV0, &b_jet_SV0);
   fChain->SetBranchAddress("jet_MV1", jet_MV1, &b_jet_MV1);
   Notify();
}

Bool_t mini_mc::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void mini_mc::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t mini_mc::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef mini_mc_cxx
