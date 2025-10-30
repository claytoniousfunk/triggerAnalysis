using namespace std;

Float_t ptMin = 0.;
Float_t ptMax = 300.;
Int_t NPtBins = 30;

Float_t etaMin = -5.0;
Float_t etaMax = 5.0;
Float_t NEtaBins = 100;

Float_t phiMin = -TMath::Pi();
Float_t phiMax = TMath::Pi();
Float_t NPhiBins = 100;

TH1D *denom = new TH1D("denom","denom",NPtBins,ptMin,ptMax);
TH1D *denomEta_40 = new TH1D("denomEta_40","denomEta_40",NEtaBins,etaMin,etaMax);
TH1D *denomEta_60 = new TH1D("denomEta_60","denomEta_60",NEtaBins,etaMin,etaMax);
TH1D *denomEta_70 = new TH1D("denomEta_70","denomEta_70",NEtaBins,etaMin,etaMax);
TH1D *denomEta_80 = new TH1D("denomEta_80","denomEta_80",NEtaBins,etaMin,etaMax);
TH1D *denomEta_100 = new TH1D("denomEta_100","denomEta_100",NEtaBins,etaMin,etaMax);
TH1D *denomEta_120 = new TH1D("denomEta_120","denomEta_120",NEtaBins,etaMin,etaMax);
TH1D *denomPhi_40 = new TH1D("denomPhi_40","denomPhi_40",NPhiBins,phiMin,phiMax);
TH1D *denomPhi_60 = new TH1D("denomPhi_60","denomPhi_60",NPhiBins,phiMin,phiMax);
TH1D *denomPhi_70 = new TH1D("denomPhi_70","denomPhi_70",NPhiBins,phiMin,phiMax);
TH1D *denomPhi_80 = new TH1D("denomPhi_80","denomPhi_80",NPhiBins,phiMin,phiMax);
TH1D *denomPhi_100 = new TH1D("denomPhi_100","denomPhi_100",NPhiBins,phiMin,phiMax);
TH1D *denomPhi_120 = new TH1D("denomPhi_120","denomPhi_120",NPhiBins,phiMin,phiMax);

TH1D *num_40 = new TH1D("num_40","num_40",NPtBins,ptMin,ptMax);
TH1D *numEta_40 = new TH1D("numEta_40","numEta_40",NEtaBins,etaMin,etaMax);
TH1D *numPhi_40 = new TH1D("numPhi_40","numPhi_40",NPhiBins,phiMin,phiMax);
TH1D *r_40 = new TH1D("r_40","r_40",NPtBins,ptMin,ptMax);

TH1D *num_60 = new TH1D("num_60","num_60",NPtBins,ptMin,ptMax);
TH1D *numEta_60 = new TH1D("numEta_60","numEta_60",NEtaBins,etaMin,etaMax);
TH1D *numPhi_60 = new TH1D("numPhi_60","numPhi_60",NPhiBins,phiMin,phiMax);
TH1D *r_60 = new TH1D("r_60","r_60",NPtBins,ptMin,ptMax);

TH1D *num_70 = new TH1D("num_70","num_70",NPtBins,ptMin,ptMax);
TH1D *numEta_70 = new TH1D("numEta_70","numEta_70",NEtaBins,etaMin,etaMax);
TH1D *numPhi_70 = new TH1D("numPhi_70","numPhi_70",NPhiBins,phiMin,phiMax);
TH1D *r_70 = new TH1D("r_70","r_70",NPtBins,ptMin,ptMax);

TH1D *num_80 = new TH1D("num_80","num_80",NPtBins,ptMin,ptMax);
TH1D *numEta_80 = new TH1D("numEta_80","numEta_80",NEtaBins,etaMin,etaMax);
TH1D *numPhi_80 = new TH1D("numPhi_80","numPhi_80",NPhiBins,phiMin,phiMax);
TH1D *r_80 = new TH1D("r_80","r_80",NPtBins,ptMin,ptMax);

TH1D *num_100 = new TH1D("num_100","num_100",NPtBins,ptMin,ptMax);
TH1D *numEta_100 = new TH1D("numEta_100","numEta_100",NEtaBins,etaMin,etaMax);
TH1D *numPhi_100 = new TH1D("numPhi_100","numPhi_100",NPhiBins,phiMin,phiMax);
TH1D *r_100 = new TH1D("r_100","r_100",NPtBins,ptMin,ptMax);

TH1D *num_120 = new TH1D("num_120","num_120",NPtBins,ptMin,ptMax);
TH1D *numEta_120 = new TH1D("numEta_120","numEta_120",NEtaBins,etaMin,etaMax);
TH1D *numPhi_120 = new TH1D("numPhi_120","numPhi_120",NPhiBins,phiMin,phiMax);
TH1D *r_120 = new TH1D("r_120","r_120",NPtBins,ptMin,ptMax);



std::map<unsigned long long, int> runLumiEvtToEntryMap;



unsigned long long keyFromRunLumiEvent(Int_t run,
                                       Int_t lumi,
                                       ULong64_t event)
{
  const unsigned long long runMult = 1;
  const unsigned long long lumiMult = 1000000;
  const unsigned long long evtMult = 10000000000;
  const unsigned long long evtLimit = 10000000000;

  unsigned long long key = 0;
  if(event >= evtLimit){
    std::cout << "RUNLUMIEVENTKEY WARNING : \'" << event
              << "\' is greated that event limit 10^10. returning key 0"
              << std::endl;
    return key;
  }

  key += runMult* static_cast<unsigned long long>(run);
  key += lumiMult*static_cast<unsigned long long>(lumi);
  key += evtMult*event;

  //std::cout << "key = " << key << std::endl;
  
  return key;
  
}





void triggerAnalysisPrompt(TString input = "/eos/cms/store/group/phys_heavyions/jdlang/Run3_2025LowPUpp_ExpressForests/LowPUpp_SpecialHLTPhysics0_398683_PARTIAL/crab_LowPUpp_SpecialHLTPhysics0_398683_PARTIAL/251030_131553/0000/HiForest_2025LowPUpp_1.root", TString output = "out.root"){

  std::cout << "running triggerAnalysisPrompt()" << std::endl;
  std::cout << "inputFile   = " << input  << std::endl;
  std::cout << "outputFile  = " << output << std::endl;	


  std::cout << "### input file ###" << std::endl; 
  TFile* inputFile = TFile::Open(input);


  TTree* treeggHiNtuplizer = 0;
  TTree* treeJet = 0;
  TTree* treeHiEvt = 0;
  TTree* treeTrig = 0;
        
  TFile* fileTmp = 0;
  TFile* fileTrig = 0;
    
  std::cout << "### HLT bit analysis file ###" << std::endl;
  fileTrig = TFile::Open(input);
  fileTrig->cd();
    
  std::string treeTrigPath = "hltanalysis/HltTree";
  treeTrig = (TTree*)fileTrig->Get(treeTrigPath.c_str());
  treeTrig->SetBranchStatus("*",0);     // disable all branches

  // specify explicitly which branches to use
  treeTrig->SetBranchStatus("Event", 1);
  treeTrig->SetBranchStatus("LumiBlock", 1);
  treeTrig->SetBranchStatus("Run", 1);
   
  treeTrig->SetBranchStatus("HLT_AK4PFJet40_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4PFJet60_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4PFJet80_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4PFJet100_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4PFJet120_v", 1);
    
  treeTrig->SetBranchStatus("HLT_AK4PFJet40_noL1Seed_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4PFJet60_noL1Seed_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4PFJet80_noL1Seed_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4PFJet100_noL1Seed_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4PFJet120_noL1Seed_v", 1);

  treeTrig->SetBranchStatus("HLT_AK4PFJetFwd40_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4PFJetFwd60_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4PFJetFwd80_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4PFJetFwd100_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4PFJetFwd120_v", 1);
    
  treeTrig->SetBranchStatus("HLT_AK4PFJetFwd40_noL1Seed_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4PFJetFwd60_noL1Seed_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4PFJetFwd80_noL1Seed_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4PFJetFwd100_noL1Seed_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4PFJetFwd120_noL1Seed_v", 1);
    
  treeTrig->SetBranchStatus("HLT_AK4CaloJet40_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4CaloJet60_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4CaloJet70_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4CaloJet100_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4CaloJet120_v", 1);
    
  treeTrig->SetBranchStatus("HLT_AK4CaloJet40_noL1Seed_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4CaloJet60_noL1Seed_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4CaloJet70_noL1Seed_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4CaloJet100_noL1Seed_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4CaloJet120_noL1Seed_v", 1);

  treeTrig->SetBranchStatus("HLT_AK4CaloJetFwd40_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4CaloJetFwd60_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4CaloJetFwd70_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4CaloJetFwd100_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4CaloJetFwd120_v", 1);
    
  treeTrig->SetBranchStatus("HLT_AK4CaloJetFwd40_noL1Seed_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4CaloJetFwd60_noL1Seed_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4CaloJetFwd70_noL1Seed_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4CaloJetFwd100_noL1Seed_v", 1);
  treeTrig->SetBranchStatus("HLT_AK4CaloJetFwd120_noL1Seed_v", 1);

  treeTrig->SetBranchStatus("HLT_HICsAK4PFJet40Eta2p1_v1", 1);
  treeTrig->SetBranchStatus("HLT_HICsAK4PFJet60Eta2p1_v1", 1);
  treeTrig->SetBranchStatus("HLT_HICsAK4PFJet80Eta2p1_v1", 1);
  treeTrig->SetBranchStatus("HLT_HICsAK4PFJet100Eta2p1_v1", 1);
  treeTrig->SetBranchStatus("HLT_HICsAK4PFJet120Eta2p1_v1", 1);

  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet40Eta5p1_v8", 1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet60Eta5p1_v8", 1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet80Eta5p1_v8", 1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet100Eta5p1_v8", 1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet120Eta5p1_v8", 1);
    
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet40Fwd_v8", 1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet60Fwd_v8", 1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet80Fwd_v8", 1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet100Fwd_v8", 1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet120Fwd_v8", 1);


  treeTrig->SetBranchStatus("HLT_PFJet40_L1Jet20_v1", 1);
  treeTrig->SetBranchStatus("HLT_PFJet40_ZeroBiasCopy_v1", 1);
  
  treeTrig->SetBranchStatus("HLT_AK8PFJet140_v31", 1);
  
  treeTrig->SetBranchStatus("HLT_PFJet40_L1Jet24_v1", 1);
  treeTrig->SetBranchStatus("HLT_PFJet60_v37", 1);
  treeTrig->SetBranchStatus("HLT_PFJet80_L1SingleJet60_v1", 1);
  treeTrig->SetBranchStatus("HLT_PFJet110_v16", 1);
  treeTrig->SetBranchStatus("HLT_PFJet140_v35", 1);
  // treeTrig->SetBranchStatus("HLT_PFJet40_L1Jet20_v1", 1);
  // treeTrig->SetBranchStatus("HLT_PFJet40_L1Jet20_v1", 1);
  // treeTrig->SetBranchStatus("HLT_PFJet40_L1Jet20_v1", 1);
  // treeTrig->SetBranchStatus("HLT_PFJet40_L1Jet20_v1", 1);

  







    
    
  //Int_t hlt_event;
  ULong64_t       hlt_event;
  Int_t           hlt_lumi;
  Int_t           hlt_run;
  Int_t          triggerDecision_40;
  Int_t          triggerDecision_60;
  Int_t          triggerDecision_70;
  Int_t          triggerDecision_80;
  Int_t          triggerDecision_100;
  Int_t          triggerDecision_120;
  std::cout << "Setting Event, lumi, and run branchAdresses...";
  treeTrig->SetBranchAddress("Event", &hlt_event);
  treeTrig->SetBranchAddress("LumiBlock", &hlt_lumi);
  treeTrig->SetBranchAddress("Run", &hlt_run);
    
  // treeTrig->SetBranchAddress("HLT_AK4PFJetFwd40_v",&triggerDecision_40);
  // treeTrig->SetBranchAddress("HLT_AK4PFJetFwd60_v",&triggerDecision_60);
  // treeTrig->SetBranchAddress("HLT_AK4PFJetFwd80_v",&triggerDecision_80);
  // treeTrig->SetBranchAddress("HLT_AK4PFJetFwd100_v",&triggerDecision_100);
  // treeTrig->SetBranchAddress("HLT_AK4PFJetFwd120_v",&triggerDecision_120);

  // treeTrig->SetBranchAddress("HLT_AK4PFJetFwd40_noL1Seed_v",&triggerDecision_40);
  // treeTrig->SetBranchAddress("HLT_AK4PFJetFwd60_noL1Seed_v",&triggerDecision_60);
  // treeTrig->SetBranchAddress("HLT_AK4PFJetFwd80_noL1Seed_v",&triggerDecision_80);
  // treeTrig->SetBranchAddress("HLT_AK4PFJetFwd100_noL1Seed_v",&triggerDecision_100);
  // treeTrig->SetBranchAddress("HLT_AK4PFJetFwd120_noL1Seed_v",&triggerDecision_120);
    
  //treeTrig->SetBranchAddress("HLT_AK4PFJet40_v",&triggerDecision_40);
  //treeTrig->SetBranchAddress("HLT_AK4PFJet60_v",&triggerDecision_60);
  //treeTrig->SetBranchAddress("HLT_AK4PFJet70_v",&triggerDecision_70);
  //treeTrig->SetBranchAddress("HLT_AK4PFJet80_v",&triggerDecision_80);
  //treeTrig->SetBranchAddress("HLT_AK4PFJet100_v",&triggerDecision_100);
  //treeTrig->SetBranchAddress("HLT_AK4PFJet120_v",&triggerDecision_120);
     
  //treeTrig->SetBranchAddress("HLT_AK4PFJet40_noL1Seed_v",&triggerDecision_40);
  //treeTrig->SetBranchAddress("HLT_AK4PFJet60_noL1Seed_v",&triggerDecision_60);
  //treeTrig->SetBranchAddress("HLT_AK4PFJet70_noL1Seed_v",&triggerDecision_70);
  //treeTrig->SetBranchAddress("HLT_AK4PFJet80_noL1Seed_v",&triggerDecision_80);
  //treeTrig->SetBranchAddress("HLT_AK4PFJet100_noL1Seed_v",&triggerDecision_100);
  //treeTrig->SetBranchAddress("HLT_AK4PFJet120_noL1Seed_v",&triggerDecision_120);
    
  // treeTrig->SetBranchAddress("HLT_AK4CaloJet40_v",&triggerDecision_40);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJet60_v",&triggerDecision_60);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJet70_v",&triggerDecision_70);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJet80_v",&triggerDecision_80);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJet100_v",&triggerDecision_100);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJet120_v",&triggerDecision_120);
    
  //treeTrig->SetBranchAddress("HLT_AK4CaloJet40_noL1Seed_v",&triggerDecision_40);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJet60_noL1Seed_v",&triggerDecision_60);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJet70_noL1Seed_v",&triggerDecision_80);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJet100_noL1Seed_v",&triggerDecision_100);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJet120_noL1Seed_v",&triggerDecision_120);

  // treeTrig->SetBranchAddress("HLT_AK4CaloJetFwd40_v",&triggerDecision_40);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJetFwd60_v",&triggerDecision_60);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJetFwd70_v",&triggerDecision_80);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJetFwd100_v",&triggerDecision_100);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJetFwd120_v",&triggerDecision_120);
    
  // treeTrig->SetBranchAddress("HLT_AK4CaloJetFwd40_noL1Seed_v",&triggerDecision_40);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJetFwd60_noL1Seed_v",&triggerDecision_60);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJetFwd70_noL1Seed_v",&triggerDecision_80);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJetFwd100_noL1Seed_v",&triggerDecision_100);
  // treeTrig->SetBranchAddress("HLT_AK4CaloJetFwd120_noL1Seed_v",&triggerDecision_120);

  // treeTrig->SetBranchAddress("HLT_HICsAK4PFJet40Eta2p1_v", &triggerDecision_40);
  // treeTrig->SetBranchAddress("HLT_HICsAK4PFJet60Eta2p1_v", &triggerDecision_60);
  // treeTrig->SetBranchAddress("HLT_HICsAK4PFJet80Eta2p1_v", &triggerDecision_80);
  // treeTrig->SetBranchAddress("HLT_HICsAK4PFJet100Eta2p1_v", &triggerDecision_100);
  // treeTrig->SetBranchAddress("HLT_HICsAK4PFJet120Eta2p1_v", &triggerDecision_120);

  // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet40Eta5p1_v8", &triggerDecision_40);
  // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet60Eta5p1_v8", &triggerDecision_60);
  // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet80Eta5p1_v8", &triggerDecision_80);
  // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet100Eta5p1_v8", &triggerDecision_100);
  // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet120Eta5p1_v8", &triggerDecision_120);

  // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet40Fwd_v8", &triggerDecision_40);
  // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet60Fwd_v8", &triggerDecision_60);
  // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet80Fwd_v8", &triggerDecision_80);
  // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet100Fwd_v8", &triggerDecision_100);
  // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet120Fwd_v8", &triggerDecision_120);

  treeTrig->SetBranchAddress("HLT_PFJet40_L1Jet24_v1", &triggerDecision_40);
  treeTrig->SetBranchAddress("HLT_PFJet60_v37", &triggerDecision_60);
  treeTrig->SetBranchAddress("HLT_PFJet80_L1SingleJet60_v1", &triggerDecision_80);
  treeTrig->SetBranchAddress("HLT_PFJet110_v16", &triggerDecision_100);
  treeTrig->SetBranchAddress("HLT_PFJet140_v35", &triggerDecision_120);

    
    

    
  std::cout << "done" << std::endl;

  std::cout << "get number of entries from HLT file..." << std::endl;

  Long64_t entriesHLT = treeTrig->GetEntries();
  std::cout << "HLT entries = " << entriesHLT << std::endl;
    
  std::cout << "get number of entries from reco file.." << std::endl;
  // read the first file only to get the HiForest info
  //std::string inputPath = inputFile.c_str();
  fileTmp = TFile::Open(input);
  fileTmp->cd();


  std::string treePath = "hiEvtAnalyzer/HiTree";

  // read one tree only to get the number of entries
  treeggHiNtuplizer = (TTree*)fileTmp->Get(treePath.c_str());
  Long64_t entriesTmp = treeggHiNtuplizer->GetEntries();
  std::cout << "reco entries = " << entriesTmp << std::endl;
  //   treeggHiNtuplizer->Delete();

  //   treeggHiNtuplizer = (TTree*)fileTmp->Get(treePath.c_str());
  treeggHiNtuplizer->SetBranchStatus("*",0);     // disable all branches
    
  std::map<unsigned long long, int> runLumiEvtToEntryMap;
    
  treeJet = (TTree*)fileTmp->Get("ak0PFJetAnalyzer/t");
  //treeJet = (TTree*)fileTmp->Get("akCs4PFJetAnalyzer/t");
  treeJet->SetBranchStatus("*",0);     // disable all branches
  treeJet->SetBranchStatus("jtpt",1);   // enable event information
  treeJet->SetBranchStatus("jteta",1);
  treeJet->SetBranchStatus("jtphi",1);
  treeJet->SetBranchStatus("nref",1);
  treeJet->SetBranchStatus("calopt",1);
  treeJet->SetBranchStatus("caloeta",1);
  treeJet->SetBranchStatus("calophi",1);
  treeJet->SetBranchStatus("ncalo",1);

  const unsigned int maxJets = 10000;
    
  Float_t jtpt[maxJets];
  Float_t jteta[maxJets];
  Float_t jtphi[maxJets];
  Int_t nref;

  treeJet->SetBranchAddress("jtpt",&jtpt);
  treeJet->SetBranchAddress("jteta",&jteta);
  treeJet->SetBranchAddress("jtphi",&jtphi);
  treeJet->SetBranchAddress("nref",&nref);
  // treeJet->SetBranchAddress("calopt",&jtpt);
  // treeJet->SetBranchAddress("caloeta",&jteta);
  // treeJet->SetBranchAddress("calophi",&jtphi);
  // treeJet->SetBranchAddress("ncalo",&nref);
    
    
  treeHiEvt = (TTree*)fileTmp->Get("hiEvtAnalyzer/HiTree");
  treeHiEvt->SetBranchStatus("*",0);     // disable all branches
  treeHiEvt->SetBranchStatus("run",1);   // enable event information
  treeHiEvt->SetBranchStatus("evt",1);
  treeHiEvt->SetBranchStatus("lumi",1);
  treeHiEvt->SetBranchStatus("vz",1);
  treeHiEvt->SetBranchStatus("hiBin",1);
  //treeHiEvt->SetBranchStatus("weight",1);

  Float_t vz;
  Int_t hiBin;
  UInt_t run;
  UInt_t lumi;
  ULong64_t evt;
  Float_t weight;

  treeHiEvt->SetBranchAddress("vz",&vz);
  treeHiEvt->SetBranchAddress("hiBin",&hiBin);
  treeHiEvt->SetBranchAddress("run",&run);
  treeHiEvt->SetBranchAddress("lumi",&lumi);
  treeHiEvt->SetBranchAddress("evt",&evt);
  //treeHiEvt->SetBranchAddress("weight",&weight);
  weight = 1.0;

    
  // loop through HLT and create a key for each event
   

  //for(Long64_t i_entry = 0; i_entry < entriesHLT; i_entry++){

  // treeTrig->GetEntry(i_entry);
  // unsigned long long key = keyFromRunLumiEvent(hlt_run, hlt_lumi, hlt_event);
  // runLumiEvtToEntryMap[key] = i_entry;

  // }




  // loop through reco objects
  for (Long64_t j_entry = 0; j_entry < entriesTmp; ++j_entry){

    treeggHiNtuplizer->GetEntry(j_entry);
    treeHiEvt->GetEntry(j_entry);
    treeJet->GetEntry(j_entry);

    //cout << "weight = " << weight << endl;
  	
    // event cuts
    if(fabs(vz)>15.0) continue;
    //if(hiBin>180) continue;	
       
    auto j_entry_status = treeJet->GetEntry(j_entry);
        
    //if(j_entry_status < 0) {
    //    std::cout << Form("bad entry %lld in jet tree",j_entry) << std::endl;
    //    continue;
    //}
	
    unsigned long long key = keyFromRunLumiEvent(run,lumi,evt);

    //long long i_entry = -1;
    Long64_t i_entry = j_entry;


	
    //if(runLumiEvtToEntryMap.count(key) == 0) continue; // skip reco event if there is no HLT event match
    //else i_entry = runLumiEvtToEntryMap.at(key);

    //std::cout << "i_entry = " << i_entry << std::endl;
        
    // now fill the denominator
    Float_t maxPt_denom = 0;
    Float_t maxEta_denom = 0;
    Float_t maxPhi_denom = 0;
        
    for(Int_t i_jet = 0; i_jet < nref; i_jet++){

      //cout << "i_jet = " << i_jet << endl;

      if(jtpt[i_jet] > maxPt_denom) { // find the leading jetPt in the event, regardless of trigger.
	maxPt_denom = jtpt[i_jet];
	maxEta_denom = jteta[i_jet];
	maxPhi_denom = jtphi[i_jet];
		
      }

    }

    //if(fabs(maxEta_denom)<3.2 || fabs(maxEta_denom)>4.7) continue; // skip event if the leading jet is outside eta range
    if(fabs(maxEta_denom)>1.5) continue; // skip event if the leading jet is outside eta range

	
	
    if(maxPt_denom > 0) {
            
      denom->Fill(maxPt_denom,weight);
      if(maxPt_denom > 30){
	denomEta_40->Fill(maxEta_denom,weight);
	if(fabs(maxEta_denom) < 5.0){
	  denomPhi_40->Fill(maxPhi_denom,weight);
	}
      }
      if(maxPt_denom > 50){
	denomEta_60->Fill(maxEta_denom,weight);
	if(fabs(maxEta_denom) < 5.0){
	  denomPhi_60->Fill(maxPhi_denom,weight);
	}
      }
      if(maxPt_denom > 60){
	denomEta_70->Fill(maxEta_denom,weight);
	if(fabs(maxEta_denom) < 5.0){
	  denomPhi_70->Fill(maxPhi_denom,weight);
	}
      }
      if(maxPt_denom > 70){
	denomEta_80->Fill(maxEta_denom,weight);
	if(fabs(maxEta_denom) < 5.0){
	  denomPhi_80->Fill(maxPhi_denom,weight);
	}
      }
      if(maxPt_denom > 90){
	denomEta_100->Fill(maxEta_denom,weight);
	if(fabs(maxEta_denom) < 5.0){
	  denomPhi_100->Fill(maxPhi_denom,weight);
	}
      }
      if(maxPt_denom > 110.0){
	denomEta_120->Fill(maxEta_denom,weight);
	if(fabs(maxEta_denom) < 5.0){
	  denomPhi_120->Fill(maxPhi_denom,weight);
	}
      }
	    
      //std::cout << "maxPt = " << maxPt_denom <<std::endl;
    }





    treeTrig->GetEntry(i_entry); // get trigger decision from HLT emulation

    //cout << "triggerDecision_40 = " << triggerDecision_40 << endl;


    if(triggerDecision_40==1) {// only fill the numerator if the trigger is on.

      Float_t maxPt_num = 0;
      Float_t maxEta_num = 0;
      Float_t maxPhi_num = 0;
            
      // now fill the numerator
      for(Int_t i_jet = 0; i_jet < nref; i_jet++){

	// no eta cut needed since already applied after the first jet loop.  

	if(jtpt[i_jet] > maxPt_num) { // find the leading jetPt in events with trigger on.
	  maxPt_num = jtpt[i_jet];
	  maxEta_num = jteta[i_jet];
	  maxPhi_num = jtphi[i_jet];
	}


      }

      if(maxPt_num > 0){

	num_40->Fill(maxPt_num,weight);
	if(maxPt_num > 30){
	  numEta_40->Fill(maxEta_num,weight);
	  if(fabs(maxEta_num) < 5.0){
	    numPhi_40->Fill(maxPhi_num,weight);
	  }
	}
		
	//std::cout << "maxPt_num = " << maxPt_num << std::endl <<  std::endl;
      } 

    }

        
        
    if(triggerDecision_60==1) {// only fill the numerator if the trigger is on.

      Float_t maxPt_num = 0;
      Float_t maxEta_num = 0;
      Float_t maxPhi_num = 0;
            
      // now fill the numerator
      for(Int_t i_jet = 0; i_jet < nref; i_jet++){

	// no eta cut needed since already applied after the first jet loop.  

	if(jtpt[i_jet] > maxPt_num) { // find the leading jetPt in events with trigger on.
	  maxPt_num = jtpt[i_jet];
	  maxEta_num = jteta[i_jet];
	  maxPhi_num = jtphi[i_jet];
	}


      }

      if(maxPt_num > 0){

	num_60->Fill(maxPt_num,weight);
	if(maxPt_num > 50){
	  numEta_60->Fill(maxEta_num,weight);
	  if(fabs(maxEta_num) < 5.0){
	    numPhi_60->Fill(maxPhi_num,weight);
	  }
	}
	//std::cout << "maxPt_num = " << maxPt_num << std::endl <<  std::endl;
      } 

    }


    if(triggerDecision_70==1) {// only fill the numerator if the trigger is on.

      Float_t maxPt_num = 0;
      Float_t maxEta_num = 0;
      Float_t maxPhi_num = 0;
            
      // now fill the numerator
      for(Int_t i_jet = 0; i_jet < nref; i_jet++){

	// no eta cut needed since already applied after the first jet loop.  

	if(jtpt[i_jet] > maxPt_num) { // find the leading jetPt in events with trigger on.
	  maxPt_num = jtpt[i_jet];
	  maxEta_num = jteta[i_jet];
	  maxPhi_num = jtphi[i_jet];
	}


      }

      if(maxPt_num > 0){

	num_70->Fill(maxPt_num,weight);
	if(maxPt_num > 60){
	  numEta_70->Fill(maxEta_num,weight);
	  if(fabs(maxEta_num) < 5.0){
	    numPhi_70->Fill(maxPhi_num,weight);
	  }
	}
	//std::cout << "maxPt_num = " << maxPt_num << std::endl <<  std::endl;
      } 

    }



	
    //cout << "--- CaloJet80 Jets ---" << endl;

    if(triggerDecision_80==1) {// only fill the numerator if the trigger is on.

      Float_t maxPt_num = 0;
      Float_t maxEta_num = 0;
      Float_t maxPhi_num = 0;
            
      // now fill the numerator
      for(Int_t i_jet = 0; i_jet < nref; i_jet++){

	// no eta cut needed since already applied after the first jet loop.  
		    
	// cout << "(jtpt, jteta, jtphi) = (" << jtpt[i_jet] << ", " << jteta[i_jet] << ", " << jtphi[i_jet] << ")" << endl;
		    
	if(jtpt[i_jet] > maxPt_num) { // find the leading jetPt in events with trigger on.
	  maxPt_num = jtpt[i_jet];
	  maxEta_num = jteta[i_jet];
	  maxPhi_num = jtphi[i_jet];
	}
                


      }

      if(maxPt_num > 0){

	num_80->Fill(maxPt_num,weight);
	if(maxPt_num > 60){
	  numEta_80->Fill(maxEta_num,weight);
	  if(fabs(maxEta_num) < 5.0){
	    numPhi_80->Fill(maxPhi_num,weight);
	  }
	}
	//std::cout << "maxPt_num = " << maxPt_num << std::endl <<  std::endl;
      } 

    }


    //cout << "--- CaloJet100 Jets ---" << endl;
		
    if(triggerDecision_100==1) {// only fill the numerator if the trigger is on.

      Float_t maxPt_num = 0;
      Float_t maxEta_num = 0;
      Float_t maxPhi_num = 0;
            
      // now fill the numerator
      for(Int_t i_jet = 0; i_jet < nref; i_jet++){


	//cout << "(jtpt, jteta, jtphi) = (" << jtpt[i_jet] << ", " << jteta[i_jet] << ", " << jtphi[i_jet] << ")" << endl;

	// no eta cut needed since already applied after the first jet loop.  

	if(jtpt[i_jet] > maxPt_num) { // find the leading jetPt in events with trigger on.
	  maxPt_num = jtpt[i_jet];
	  maxEta_num = jteta[i_jet];
	  maxPhi_num = jtphi[i_jet];
	}


      }

      if(maxPt_num > 0){

	num_100->Fill(maxPt_num,weight);
	if(maxPt_num > 90){
	  numEta_100->Fill(maxEta_num,weight);
	  if(fabs(maxEta_num) < 5.0){
	    numPhi_100->Fill(maxPhi_num,weight);
	  }
	}
	//std::cout << "maxPt_num = " << maxPt_num << std::endl <<  std::endl;
      } 

    }

    if(triggerDecision_120==1) {// only fill the numerator if the trigger is on.

      Float_t maxPt_num = 0;
      Float_t maxEta_num = 0;
      Float_t maxPhi_num = 0;
            
      // now fill the numerator
      for(Int_t i_jet = 0; i_jet < nref; i_jet++){

	// no eta cut needed since already applied after the first jet loop.  

	if(jtpt[i_jet] > maxPt_num) { // find the leading jetPt in events with trigger on.
	  maxPt_num = jtpt[i_jet];
	  maxEta_num = jteta[i_jet];
	  maxPhi_num = jtphi[i_jet];
	}


      }

      if(maxPt_num > 0){

	num_120->Fill(maxPt_num,weight);
	if(maxPt_num > 110.0){
	  numEta_120->Fill(maxEta_num,weight);
	  if(fabs(maxEta_num) < 5.0){
	    numPhi_120->Fill(maxPhi_num,weight);
	  }
	}
	//std::cout << "maxPt_num = " << maxPt_num << std::endl <<  std::endl;
      } 

    }




  }

  r_40->Divide(num_40,denom,1,1,"B");
  r_60->Divide(num_60,denom,1,1,"B");
  r_70->Divide(num_70,denom,1,1,"B");
  r_80->Divide(num_80,denom,1,1,"B");
  r_100->Divide(num_100,denom,1,1,"B");
  r_120->Divide(num_120,denom,1,1,"B");


  r_40->SetLineColor(kRed-4);
  r_60->SetLineColor(kBlue-4);
  r_80->SetLineColor(kGreen+2);
  r_100->SetLineColor(kMagenta-9);
  r_120->SetLineColor(kPink+6);

  r_40->SetMarkerColor(kRed-4);
  r_60->SetMarkerColor(kBlue-4);
  r_80->SetMarkerColor(kGreen+2);
  r_100->SetMarkerColor(kMagenta-9);
  r_120->SetMarkerColor(kPink+6);

  double line_width = 1.8;
  r_40->SetLineWidth(line_width);
  r_60->SetLineWidth(line_width);
  r_80->SetLineWidth(line_width);
  r_100->SetLineWidth(line_width);
  r_120->SetLineWidth(line_width);

  double marker_size = 1.6;
  r_40->SetMarkerSize(marker_size);
  r_60->SetMarkerSize(marker_size);
  r_80->SetMarkerSize(marker_size);
  r_100->SetMarkerSize(marker_size);
  r_120->SetMarkerSize(marker_size);
    
  r_40->SetMarkerStyle(20);
  r_60->SetMarkerStyle(21);
  r_80->SetMarkerStyle(22);
  r_100->SetMarkerStyle(23);
  r_120->SetMarkerStyle(34);

  TCanvas *c1 = new TCanvas("c1","c1",700,600);
  c1->cd();
  TPad *p1 = new TPad("p1","p1",0,0,1,1);
  p1->SetLeftMargin(0.13);
  p1->SetBottomMargin(0.14);
  p1->Draw();
  p1->cd();
  r_60->SetTitle("");
  r_60->SetStats(0);
  r_60->GetXaxis()->SetTitleSize(0.05);
  r_60->GetYaxis()->SetTitleSize(0.05);
  r_60->GetXaxis()->SetTitle("leading jet #font[52]{p}_{T} [GeV]");
  r_60->GetYaxis()->SetTitle("Trigger efficiency");
  TLegend *leg = new TLegend(0.55,0.3,0.88,0.5);
  leg->AddEntry(r_40,"HLT_PFJet40_L1Jet24_v1");
  leg->AddEntry(r_60,"HLT_PFJet60_v37");
  //leg->AddEntry(r_70,"");
  leg->AddEntry(r_80,"HLT_PFJet80_L1SingleJet60_v1");
  leg->AddEntry(r_100,"HLT_PFJet110_v16");
  leg->AddEntry(r_120,"HLT_PFJet140_v35");
  //leg->SetBorderSize(0);
  r_60->Draw();
  leg->Draw();
  r_70->Draw("same");
  r_80->Draw("same");
  r_100->Draw("same");
  r_120->Draw("same");
  r_40->Draw("same");

  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.03);

  la->DrawLatexNDC(0.22,0.92,"2025 PPRef #sqrt{#it{s}} = 5.36 TeV");
  la->DrawLatexNDC(0.72,0.92,"Run 398683");
  //la->DrawLatexNDC(0.6,0.69,"2025 Run 3 MC");
  la->DrawLatexNDC(0.6,0.69,"|#eta^{jet}| < 1.5");

 


  auto wf = TFile::Open(output,"recreate");

  denom->Write();

  denomEta_40->Write();
  denomEta_60->Write();
  denomEta_70->Write();
  denomEta_80->Write();
  denomEta_100->Write();
  denomEta_120->Write();

  denomPhi_40->Write();
  denomPhi_60->Write();
  denomPhi_70->Write();
  denomPhi_80->Write();
  denomPhi_100->Write();
  denomPhi_120->Write();

  num_40->Write();
  num_60->Write();
  num_70->Write();
  num_80->Write();
  num_100->Write();
  num_120->Write();

  numEta_40->Write();
  numEta_60->Write();
  numEta_70->Write();
  numEta_80->Write();
  numEta_100->Write();
  numEta_120->Write();

  numPhi_40->Write();
  numPhi_60->Write();
  numPhi_70->Write();
  numPhi_80->Write();
  numPhi_100->Write();
  numPhi_120->Write();

  r_40->Write();
  r_60->Write();
  r_70->Write();
  r_80->Write();
  r_100->Write();
  r_120->Write();

  wf->Close();

		     

}


