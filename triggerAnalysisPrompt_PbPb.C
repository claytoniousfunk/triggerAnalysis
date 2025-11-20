using namespace std;

Float_t ptMin = 0.;
Float_t ptMax = 300.;
Int_t NPtBins = 300;

Float_t etaMin = -5.0;
Float_t etaMax = 5.0;
Float_t NEtaBins = 100;

Float_t phiMin = -TMath::Pi();
Float_t phiMax = TMath::Pi();
Float_t NPhiBins = 100;

TH1D *denom = new TH1D("denom","denom",NPtBins,ptMin,ptMax);
TH1D *denom_Fwd = new TH1D("denom_Fwd","denom_Fwd",NPtBins,ptMin,ptMax);

TH1D *num_40 = new TH1D("num_40","num_40",NPtBins,ptMin,ptMax);
TH1D *num_60 = new TH1D("num_60","num_60",NPtBins,ptMin,ptMax);
TH1D *num_80 = new TH1D("num_80","num_80",NPtBins,ptMin,ptMax);
TH1D *num_100 = new TH1D("num_100","num_100",NPtBins,ptMin,ptMax);
TH1D *num_120 = new TH1D("num_120","num_120",NPtBins,ptMin,ptMax);
TH1D *num_40_Fwd = new TH1D("num_40_Fwd","num_40_Fwd",NPtBins,ptMin,ptMax);
TH1D *num_60_Fwd = new TH1D("num_60_Fwd","num_60_Fwd",NPtBins,ptMin,ptMax);
TH1D *num_80_Fwd = new TH1D("num_80_Fwd","num_80_Fwd",NPtBins,ptMin,ptMax);
TH1D *num_100_Fwd = new TH1D("num_100_Fwd","num_100_Fwd",NPtBins,ptMin,ptMax);
TH1D *num_120_Fwd = new TH1D("num_120_Fwd","num_120_Fwd",NPtBins,ptMin,ptMax);




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





void triggerAnalysisPrompt_PbPb(int file_i = 1){

  std::ifstream infile("./fileNames/fileNames_HIPhysicsRawPrime0to9_399593.txt");
  if(!infile.is_open()){
    std::cerr << "Error: Could not open fileNames.txt" << std::endl;
    return;
  }

  std::vector<TString> fileList;
  std::string line;
  while(std::getline(infile,line)){
    if(line.empty()) continue;
    fileList.push_back(TString(line));
  }
  infile.close();

  TString input = fileList[file_i];
  std::cout << "Number of files: " << fileList.size() << std::endl;
  std::cout << "Processing file " << file_i << std::endl;


  TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_triggerAnalysisPrompt_HIPhysicsRawPrime0to9_399593_CaloJetPT/out_%i.root",file_i);
  

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


  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet40Eta5p1_MinBiasHF1AND_v8",1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet60Eta5p1_MinBiasHF1AND_v8",1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet80Eta5p1_v16",1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet100Eta5p1_v16",1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet120Eta5p1_v16",1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet40Fwd_v9",1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet60Fwd_v9",1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet80Fwd_v9",1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet100Fwd_v9",1);
  treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet120Fwd_v9",1);

			    
    
  
  
  //Int_t hlt_event;
  ULong64_t      hlt_event;
  Int_t          hlt_lumi;
  Int_t          hlt_run;
  Int_t          triggerDecision_40;
  Int_t          triggerDecision_60;
  Int_t          triggerDecision_80;
  Int_t          triggerDecision_100;
  Int_t          triggerDecision_120;
  Int_t          triggerDecision_40_Fwd;
  Int_t          triggerDecision_60_Fwd;
  Int_t          triggerDecision_80_Fwd;
  Int_t          triggerDecision_100_Fwd;
  Int_t          triggerDecision_120_Fwd;

  treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet40Eta5p1_MinBiasHF1AND_v8",&triggerDecision_40);
  treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet60Eta5p1_MinBiasHF1AND_v8",&triggerDecision_60);
  treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet80Eta5p1_v16",&triggerDecision_80);
  treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet100Eta5p1_v16",&triggerDecision_100);
  treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet120Eta5p1_v16",&triggerDecision_120);
  treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet40Fwd_v9",&triggerDecision_40_Fwd);
  treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet60Fwd_v9",&triggerDecision_60_Fwd);
  treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet80Fwd_v9",&triggerDecision_80_Fwd);
  treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet100Fwd_v9",&triggerDecision_100_Fwd);
  treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet120Fwd_v9",&triggerDecision_120_Fwd);
  

  
  std::cout << "Setting Event, lumi, and run branchAdresses...";
  treeTrig->SetBranchAddress("Event", &hlt_event);
  treeTrig->SetBranchAddress("LumiBlock", &hlt_lumi);
  treeTrig->SetBranchAddress("Run", &hlt_run);
    
  
    
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
    
  //treeJet = (TTree*)fileTmp->Get("ak0PFJetAnalyzer/t");
  treeJet = (TTree*)fileTmp->Get("akCs4PFJetAnalyzer/t");
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
  Float_t calopt[maxJets];
  Float_t caloeta[maxJets];
  Float_t calophi[maxJets];
  Int_t ncalo;
  

  // treeJet->SetBranchAddress("jtpt",&jtpt);
  // treeJet->SetBranchAddress("jteta",&jteta);
  // treeJet->SetBranchAddress("jtphi",&jtphi);
  // treeJet->SetBranchAddress("nref",&nref);
  treeJet->SetBranchAddress("calopt",&jtpt);
  treeJet->SetBranchAddress("caloeta",&jteta);
  treeJet->SetBranchAddress("calophi",&jtphi);
  treeJet->SetBranchAddress("ncalo",&nref);
    
    
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

    std::cout << "processing event " << j_entry << "\n";

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

    treeTrig->GetEntry(i_entry); // get trigger decision from HLT emulation

	
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
    //if() continue; // skip event if the leading jet is outside eta range

	
	
    if(fabs(maxEta_denom)<1.5 && maxPt_denom > 0) {
            
      denom->Fill(maxPt_denom,weight);
      if(triggerDecision_40==1) num_40->Fill(maxPt_denom,weight);
      if(triggerDecision_60==1) num_60->Fill(maxPt_denom,weight);
      if(triggerDecision_80==1) num_80->Fill(maxPt_denom,weight);
      if(triggerDecision_100==1) num_100->Fill(maxPt_denom,weight);
      if(triggerDecision_120==1) num_120->Fill(maxPt_denom,weight);
            
    }

    if(fabs(maxEta_denom)>3.2 && fabs(maxEta_denom)<4.7 && maxPt_denom > 0){

      denom_Fwd->Fill(maxPt_denom,weight);
      if(triggerDecision_40_Fwd==1) num_40_Fwd->Fill(maxPt_denom,weight);
      if(triggerDecision_60_Fwd==1) num_60_Fwd->Fill(maxPt_denom,weight);
      if(triggerDecision_80_Fwd==1) num_80_Fwd->Fill(maxPt_denom,weight);
      if(triggerDecision_100_Fwd==1) num_100_Fwd->Fill(maxPt_denom,weight);
      if(triggerDecision_120_Fwd==1) num_120_Fwd->Fill(maxPt_denom,weight);

    }


  }


 


  auto wf = TFile::Open(output,"recreate");

  denom->Write();
  denom_Fwd->Write();

  num_40->Write();
  num_60->Write();
  num_80->Write();
  num_100->Write();
  num_120->Write();

  num_40_Fwd->Write();
  num_60_Fwd->Write();
  num_80_Fwd->Write();
  num_100_Fwd->Write();
  num_120_Fwd->Write();


  wf->Close();

		     

}


