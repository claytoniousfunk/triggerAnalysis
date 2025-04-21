

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




void rateCounter(std::string triggerFile = "/home/clayton/Analysis/code/HLTAnalysis/rootFiles/openHLT_PPRefZeroBias_373710.root",
                 std::string inputFile = "/home/clayton/Analysis/code/HLTAnalysis/rootFiles/HiForestMiniAOD_merge.root",
                 std::string outputFile = "out_rateCounter.root"){



    std::cout << "running triggerAnalysis()" << std::endl;
    std::cout << "inputFile   = " << inputFile.c_str()  << std::endl;
    std::cout << "outputFile  = " << outputFile.c_str() << std::endl;	


    std::cout << "### input file ###" << std::endl; 
    TFile* input = TFile::Open(inputFile.c_str(), "READ");


    TTree* treeggHiNtuplizer = 0;
    TTree* treeJet = 0;
    TTree* treeHiEvt = 0;
    TTree* treeTrig = 0;
        
    TFile* fileTmp = 0;
    TFile* fileTrig = 0;
    
    std::cout << "### HLT bit analysis file ###" << std::endl;
    fileTrig = TFile::Open(triggerFile.c_str(), "READ");
    fileTrig->cd();
    
    std::string treeTrigPath = "hltanalysis/HltTree";
    treeTrig = (TTree*)fileTrig->Get(treeTrigPath.c_str());
    treeTrig->SetBranchStatus("*",0);     // disable all branches

    // specify explicitly which branches to use
    treeTrig->SetBranchStatus("Event", 1);
    treeTrig->SetBranchStatus("LumiBlock", 1);
    treeTrig->SetBranchStatus("Run", 1);


    treeTrig->SetBranchStatus("HLT_HICsAK4PFJet40Eta2p1_v", 1);
    treeTrig->SetBranchStatus("HLT_HICsAK4PFJet60Eta2p1_v", 1);
    treeTrig->SetBranchStatus("HLT_HICsAK4PFJet80Eta2p1_v", 1);
    treeTrig->SetBranchStatus("HLT_HICsAK4PFJet100Eta2p1_v", 1);
    treeTrig->SetBranchStatus("HLT_HICsAK4PFJet120Eta2p1_v", 1);

    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet40Eta5p1_MinBiasHF1AND_ZDC1nOR_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet40Eta5p1_MinBiasHF1AND_ZDC2nOR_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet40Eta5p1_MinBiasHF1AND_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet40Fwd_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet60Eta5p1_MinBiasHF1AND_ZDC1nOR_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet60Eta5p1_MinBiasHF1AND_ZDC2nOR_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet60Eta5p1_MinBiasHF1AND_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet60Fwd_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet80Eta5p1_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet80Fwd_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet100Eta5p1_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet100Fwd_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet120Eta5p1_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet120Fwd_v", 1);

    treeTrig->SetBranchStatus("HLT_HIL3SingleMu3_SinglePuAK4CaloJet40_v", 1);
    treeTrig->SetBranchStatus("HLT_HIL3SingleMu3_SinglePuAK4CaloJet60_v", 1);
    treeTrig->SetBranchStatus("HLT_HIL3SingleMu3_SinglePuAK4CaloJet80_v", 1);
    treeTrig->SetBranchStatus("HLT_HIL3SingleMu5_SinglePuAK4CaloJet40_v", 1);
    treeTrig->SetBranchStatus("HLT_HIL3SingleMu5_SinglePuAK4CaloJet60_v", 1);
    treeTrig->SetBranchStatus("HLT_HIL3SingleMu5_SinglePuAK4CaloJet80_v", 1);


    treeTrig->SetBranchStatus("HLT_AK4PFJetFwd40_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4PFJetFwd60_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4PFJetFwd70_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4PFJetFwd80_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4PFJetFwd100_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4PFJetFwd120_v", 1);

    treeTrig->SetBranchStatus("HLT_AK4PFJet40_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4PFJet60_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4PFJet70_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4PFJet80_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4PFJet100_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4PFJet120_v", 1);
    
    treeTrig->SetBranchStatus("HLT_AK4CaloJet40_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4CaloJet60_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4CaloJet70_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4CaloJet80_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4CaloJet100_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4CaloJet120_v", 1);
    
    treeTrig->SetBranchStatus("HLT_AK4CaloJetFwd40_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4CaloJetFwd60_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4CaloJetFwd70_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4CaloJetFwd80_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4CaloJetFwd100_v", 1);
    treeTrig->SetBranchStatus("HLT_AK4CaloJetFwd120_v", 1);

    treeTrig->SetBranchStatus("HLT_PPRefL3SingleMu3_SingleAK4CaloJet40_v", 1);
    treeTrig->SetBranchStatus("HLT_PPRefL3SingleMu3_SingleAK4CaloJet60_v", 1);
    treeTrig->SetBranchStatus("HLT_PPRefL3SingleMu3_SingleAK4CaloJet80_v", 1);
    treeTrig->SetBranchStatus("HLT_PPRefL3SingleMu5_SingleAK4CaloJet40_v", 1);
    treeTrig->SetBranchStatus("HLT_PPRefL3SingleMu5_SingleAK4CaloJet60_v", 1);
    treeTrig->SetBranchStatus("HLT_PPRefL3SingleMu5_SingleAK4CaloJet80_v", 1);
    
    //Int_t hlt_event;
    ULong64_t       hlt_event;
    Int_t           hlt_lumi;
    Int_t           hlt_run;
    Bool_t          triggerDecision_40;
    Bool_t          triggerDecision_60;
    Bool_t          triggerDecision_70;
    Bool_t          triggerDecision_80;
    Bool_t          triggerDecision_100;
    Bool_t          triggerDecision_120;
    std::cout << "Setting Event, lumi, and run branchAdresses..." << endl;
    treeTrig->SetBranchAddress("Event", &hlt_event);
    treeTrig->SetBranchAddress("LumiBlock", &hlt_lumi);
    treeTrig->SetBranchAddress("Run", &hlt_run);

    // treeTrig->SetBranchAddress("HLT_HICsAK4PFJet40Eta2p1_v",&triggerDecision_40);
    // treeTrig->SetBranchAddress("HLT_HICsAK4PFJet60Eta2p1_v",&triggerDecision_60);
    // treeTrig->SetBranchAddress("HLT_HICsAK4PFJet80Eta2p1_v",&triggerDecision_80);
    // treeTrig->SetBranchAddress("HLT_HICsAK4PFJet100Eta2p1_v",&triggerDecision_100);
    // treeTrig->SetBranchAddress("HLT_HICsAK4PFJet120Eta2p1_v",&triggerDecision_120);

    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet40Eta5p1_MinBiasHF1AND_ZDC1nOR_v", &triggerDecision_40);
    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet40Eta5p1_MinBiasHF1AND_ZDC2nOR_v", &triggerDecision_60);
    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet40Eta5p1_MinBiasHF1AND_v", &triggerDecision_80);
    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet40Fwd_v", &triggerDecision_100);
    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet40Fwd_v", &triggerDecision_120);

    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet60Eta5p1_MinBiasHF1AND_ZDC1nOR_v", &triggerDecision_40);
    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet60Eta5p1_MinBiasHF1AND_ZDC2nOR_v", &triggerDecision_60);
    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet60Eta5p1_MinBiasHF1AND_v", &triggerDecision_80);
    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet60Fwd_v", &triggerDecision_100);
    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet40Fwd_v", &triggerDecision_120);

    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet40Eta5p1_MinBiasHF1AND_v", &triggerDecision_40);
    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet60Eta5p1_MinBiasHF1AND_v", &triggerDecision_60);
    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet80Eta5p1_v", &triggerDecision_80);
    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet100Eta5p1_v", &triggerDecision_100);
    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet120Eta2p1_v", &triggerDecision_120);


    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet40Fwd_v", &triggerDecision_40);
    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet60Fwd_v", &triggerDecision_60);
    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet80Fwd_v", &triggerDecision_80);
    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet100Fwd_v", &triggerDecision_100);
    // treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet120Fwd_v", &triggerDecision_120);
   
    
    // treeTrig->SetBranchAddress("HLT_AK4PFJetFwd40_v",&triggerDecision_40);
    // treeTrig->SetBranchAddress("HLT_AK4PFJetFwd60_v",&triggerDecision_60);
    // treeTrig->SetBranchAddress("HLT_AK4PFJetFwd70_v",&triggerDecision_70);
    // treeTrig->SetBranchAddress("HLT_AK4PFJetFwd80_v",&triggerDecision_80);
    // treeTrig->SetBranchAddress("HLT_AK4PFJetFwd100_v",&triggerDecision_100);
    // treeTrig->SetBranchAddress("HLT_AK4PFJetFwd120_v",&triggerDecision_120);

    // treeTrig->SetBranchAddress("HLT_AK4PFJet40_v",&triggerDecision_40);
    // treeTrig->SetBranchAddress("HLT_AK4PFJet60_v",&triggerDecision_60);
    // treeTrig->SetBranchAddress("HLT_AK4PFJet70_v",&triggerDecision_70);
    // treeTrig->SetBranchAddress("HLT_AK4PFJet80_v",&triggerDecision_80);
    // treeTrig->SetBranchAddress("HLT_AK4PFJet100_v",&triggerDecision_100);
    // treeTrig->SetBranchAddress("HLT_AK4PFJet120_v",&triggerDecision_120);
        
    treeTrig->SetBranchAddress("HLT_AK4CaloJet40_v",&triggerDecision_40);
    treeTrig->SetBranchAddress("HLT_AK4CaloJet60_v",&triggerDecision_60);
    treeTrig->SetBranchAddress("HLT_AK4CaloJet70_v",&triggerDecision_70);
    treeTrig->SetBranchAddress("HLT_AK4CaloJet80_v",&triggerDecision_80);
    treeTrig->SetBranchAddress("HLT_AK4CaloJet100_v",&triggerDecision_100);
    treeTrig->SetBranchAddress("HLT_AK4CaloJet120_v",&triggerDecision_120);

    // treeTrig->SetBranchAddress("HLT_PPRefL3SingleMu3_SingleAK4CaloJet40_v",&triggerDecision_40);
    // treeTrig->SetBranchAddress("HLT_PPRefL3SingleMu3_SingleAK4CaloJet60_v",&triggerDecision_60);
    // treeTrig->SetBranchAddress("HLT_PPRefL3SingleMu3_SingleAK4CaloJet80_v",&triggerDecision_70);
    // treeTrig->SetBranchAddress("HLT_PPRefL3SingleMu5_SingleAK4CaloJet40_v",&triggerDecision_80);
    // treeTrig->SetBranchAddress("HLT_PPRefL3SingleMu5_SingleAK4CaloJet60_v",&triggerDecision_100);
    // treeTrig->SetBranchAddress("HLT_PPRefL3SingleMu5_SingleAK4CaloJet80_v",&triggerDecision_120);

    // treeTrig->SetBranchAddress("HLT_HIL3SingleMu3_SinglePuAK4CaloJet40_v",&triggerDecision_40);
    // treeTrig->SetBranchAddress("HLT_HIL3SingleMu3_SinglePuAK4CaloJet60_v",&triggerDecision_60);
    // treeTrig->SetBranchAddress("HLT_HIL3SingleMu3_SinglePuAK4CaloJet80_v",&triggerDecision_70);
    // treeTrig->SetBranchAddress("HLT_HIL3SingleMu5_SinglePuAK4CaloJet40_v",&triggerDecision_80);
    // treeTrig->SetBranchAddress("HLT_HIL3SingleMu5_SinglePuAK4CaloJet60_v",&triggerDecision_100);
    // treeTrig->SetBranchAddress("HLT_HIL3SingleMu5_SinglePuAK4CaloJet80_v",&triggerDecision_120);
        
    // treeTrig->SetBranchAddress("HLT_AK4CaloJetFwd40_v",&triggerDecision_40);
    // treeTrig->SetBranchAddress("HLT_AK4CaloJetFwd60_v",&triggerDecision_60);
    // treeTrig->SetBranchAddress("HLT_AK4CaloJetFwd70_v",&triggerDecision_70);
    // treeTrig->SetBranchAddress("HLT_AK4CaloJetFwd80_v",&triggerDecision_80);
    // treeTrig->SetBranchAddress("HLT_AK4CaloJetFwd100_v",&triggerDecision_100);
    // treeTrig->SetBranchAddress("HLT_AK4CaloJetFwd120_v",&triggerDecision_120);
    
    Long64_t entriesHLT = treeTrig->GetEntries();

    Int_t triggerCount_all = 0;
    Int_t triggerCount_40 = 0;
    Int_t triggerCount_60 = 0;
    Int_t triggerCount_70 = 0;
    Int_t triggerCount_80 = 0;
    Int_t triggerCount_100 = 0;
    Int_t triggerCount_120 = 0;


    for(Long64_t i_entry = 0; i_entry < entriesHLT; i_entry++){

       treeTrig->GetEntry(i_entry);
       unsigned long long key = keyFromRunLumiEvent(hlt_run, hlt_lumi, hlt_event);
       runLumiEvtToEntryMap[key] = i_entry;

       triggerCount_all++; 
       if(triggerDecision_40) triggerCount_40++; 
       if(triggerDecision_60) triggerCount_60++; 
       if(triggerDecision_70) triggerCount_70++; 
       if(triggerDecision_80) triggerCount_80++; 
       if(triggerDecision_100) triggerCount_100++; 
       if(triggerDecision_120) triggerCount_120++;


    
    
    }
   

    Float_t countError_all = sqrt(1.0*triggerCount_all); 
    Float_t countError_40 = sqrt(1.0*triggerCount_40); 
    Float_t countError_60 = sqrt(1.0*triggerCount_60); 
    Float_t countError_70 = sqrt(1.0*triggerCount_70); 
    Float_t countError_80 = sqrt(1.0*triggerCount_80); 
    Float_t countError_100 = sqrt(1.0*triggerCount_100); 
    Float_t countError_120 = sqrt(1.0*triggerCount_120); 

    // Float_t PU_MC = 2.5;
    // Float_t PU_exp = 7.;
    Float_t PU_MC = 1.;
    Float_t PU_exp = 1.;
    // Float_t L_peak = 6.4e27;
    // Float_t L_avg = 3.0e26;
    Float_t L_peak = 2.4e33;
    Float_t L_avg = 1.87e31;
    Float_t Bunch = 40.;
    Float_t Freq = 11245.;
    // Float_t L_peak = 1.;
    // Float_t L_avg = 1.;
    // Float_t Bunch = 1.;
    // Float_t Freq = 1.;

    Float_t baseline = (PU_exp / PU_MC) * (L_peak / L_avg) * Bunch * Freq;
    //Float_t baseline = 100000.;
    //Float_t baseline = 50000.;

    Float_t triggerRate_40 = baseline*(triggerCount_40 * 1.0) / (triggerCount_all * 1.0); 
    Float_t triggerRate_60 = baseline*(triggerCount_60 * 1.0) / (triggerCount_all * 1.0); 
    Float_t triggerRate_70 = baseline*(triggerCount_70 * 1.0) / (triggerCount_all * 1.0); 
    Float_t triggerRate_80 = baseline*(triggerCount_80 * 1.0) / (triggerCount_all * 1.0); 
    Float_t triggerRate_100 = baseline*(triggerCount_100 * 1.0) / (triggerCount_all * 1.0); 
    Float_t triggerRate_120 = baseline*(triggerCount_120 * 1.0) / (triggerCount_all * 1.0); 
   
    Float_t rateError_40 = triggerRate_40 * sqrt(((countError_40) / (1.0 * triggerCount_40)) * ((countError_40) / (1.0 * triggerCount_40)) +
						 ((countError_all) / (1.0 * triggerCount_all)) * ((countError_all) / (1.0 * triggerCount_all))); 


    Float_t rateError_60 = triggerRate_60 * sqrt(((countError_60) / (1.0 * triggerCount_60)) * ((countError_60) / (1.0 * triggerCount_60)) +
						 ((countError_all) / (1.0 * triggerCount_all)) * ((countError_all) / (1.0 * triggerCount_all))); 


    Float_t rateError_70 = triggerRate_70 * sqrt(((countError_70) / (1.0 * triggerCount_70)) * ((countError_70) / (1.0 * triggerCount_70)) +
						 ((countError_all) / (1.0 * triggerCount_all)) * ((countError_all) / (1.0 * triggerCount_all))); 


    Float_t rateError_80 = triggerRate_80 * sqrt(((countError_80) / (1.0 * triggerCount_80)) * ((countError_80) / (1.0 * triggerCount_80)) +
						 ((countError_all) / (1.0 * triggerCount_all)) * ((countError_all) / (1.0 * triggerCount_all))); 


    Float_t rateError_100 = triggerRate_100 * sqrt(((countError_100) / (1.0 * triggerCount_100)) * ((countError_100) / (1.0 * triggerCount_100)) +
						 ((countError_all) / (1.0 * triggerCount_all)) * ((countError_all) / (1.0 * triggerCount_all))); 


    Float_t rateError_120 = triggerRate_120 * sqrt(((countError_120) / (1.0 * triggerCount_120)) * ((countError_120) / (1.0 * triggerCount_120)) +
						 ((countError_all) / (1.0 * triggerCount_all)) * ((countError_all) / (1.0 * triggerCount_all))); 



    cout << "COUNTS" << endl;
    cout << "total: " << triggerCount_all << "+/- " << countError_all << endl;
    cout << "Jet40: " << triggerCount_40 << " +/- " << countError_40  <<endl;
    cout << "Jet60: " << triggerCount_60 << " +/- " << countError_60  <<endl;
    cout << "Jet70: " << triggerCount_70 << " +/- " << countError_70  <<endl;
    cout << "Jet80: " << triggerCount_80 << " +/- " << countError_80  <<endl;
    cout << "Jet100: " << triggerCount_100 << " +/- " << countError_100  <<endl;
    cout << "Jet120: " << triggerCount_120 << " +/- " << countError_120  <<endl;

    cout << "FRACTIONS" << endl;
    cout << "Jet40: " << (1.*triggerCount_40)/(1.*triggerCount_all) << endl;
    cout << "Jet60: " << (1.*triggerCount_60)/(1.*triggerCount_all) << endl;
    cout << "Jet70: " << (1.*triggerCount_70)/(1.*triggerCount_all) << endl;
    cout << "Jet80: " << (1.*triggerCount_80)/(1.*triggerCount_all) << endl;
    cout << "Jet100: " << (1.*triggerCount_100)/(1.*triggerCount_all) << endl;
    cout << "Jet120: " << (1.*triggerCount_120)/(1.*triggerCount_all) << endl;

    
    cout << "RATES" << endl;
    cout << "Jet40: " << triggerRate_40 << " +/- " << rateError_40  <<endl;
    cout << "Jet60: " << triggerRate_60 << " +/- " << rateError_60  <<endl;
    cout << "Jet70: " << triggerRate_70 << " +/- " << rateError_70  <<endl;
    cout << "Jet80: " << triggerRate_80 << " +/- " << rateError_80  <<endl;
    cout << "Jet100: " << triggerRate_100 << " +/- " << rateError_100  <<endl;
    cout << "Jet120: " << triggerRate_120 << " +/- " << rateError_120  <<endl;

    cout << "BASELINE INTERACTION RATE = " << baseline << endl;


}
