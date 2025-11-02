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

TH1D *num_40_ZeroBiasCopy = new TH1D("num_40_ZeroBiasCopy","num_40_ZeroBiasCopy",NPtBins,ptMin,ptMax);
TH1D *num_40_L1Jet20 = new TH1D("num_40_L1Jet20","num_40_L1Jet20",NPtBins,ptMin,ptMax);
TH1D *num_40_L1Jet24 = new TH1D("num_40_L1Jet24","num_40_L1Jet24",NPtBins,ptMin,ptMax);
TH1D *num_60 = new TH1D("num_60","num_60",NPtBins,ptMin,ptMax);
TH1D *num_80_L1SingleJet60 = new TH1D("num_80_L1SingleJet60","num_80_L1SingleJet60",NPtBins,ptMin,ptMax);
TH1D *num_110 = new TH1D("num_110","num_110",NPtBins,ptMin,ptMax);
TH1D *num_140 = new TH1D("num_140","num_140",NPtBins,ptMin,ptMax);




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





void triggerAnalysisPrompt(int file_i = 1){

  std::ifstream infile("./fileNames/fileNames_SpecialZeroBias1_398683.txt");
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


  TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_triggerAnalysisPrompt_SpecialZeroBias1_2025-11-01/out_%i.root",file_i);
  

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


  treeTrig->SetBranchStatus("HLT_PFJet40_ZeroBiasCopy_v1",1);
  treeTrig->SetBranchStatus("HLT_PFJet40_L1Jet20_v1",1);
  treeTrig->SetBranchStatus("HLT_PFJet40_L1Jet24_v1",1);
  treeTrig->SetBranchStatus("HLT_PFJet60_v37",1);
  treeTrig->SetBranchStatus("HLT_PFJet80_L1SingleJet60_v1",1);
  treeTrig->SetBranchStatus("HLT_PFJet110_v16",1);
  treeTrig->SetBranchStatus("HLT_PFJet140_v35",1);
			    
    
  
  
  //Int_t hlt_event;
  ULong64_t      hlt_event;
  Int_t          hlt_lumi;
  Int_t          hlt_run;
  Int_t          triggerDecision_40_ZeroBiasCopy;
  Int_t          triggerDecision_40_L1Jet20;
  Int_t          triggerDecision_40_L1Jet24;
  Int_t          triggerDecision_60;
  Int_t          triggerDecision_80_L1SingleJet60;
  Int_t          triggerDecision_110;
  Int_t          triggerDecision_140;

  treeTrig->SetBranchAddress("HLT_PFJet40_ZeroBiasCopy_v1",&triggerDecision_40_ZeroBiasCopy);
  treeTrig->SetBranchAddress("HLT_PFJet40_L1Jet20_v1",&triggerDecision_40_L1Jet20);
  treeTrig->SetBranchAddress("HLT_PFJet40_L1Jet24_v1",&triggerDecision_40_L1Jet24);
  treeTrig->SetBranchAddress("HLT_PFJet60_v37",&triggerDecision_60);
  treeTrig->SetBranchAddress("HLT_PFJet80_L1SingleJet60_v1",&triggerDecision_80_L1SingleJet60);
  treeTrig->SetBranchAddress("HLT_PFJet110_v16",&triggerDecision_110);
  treeTrig->SetBranchAddress("HLT_PFJet140_v35",&triggerDecision_140);

  
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
    if(fabs(maxEta_denom)>1.5) continue; // skip event if the leading jet is outside eta range

	
	
    if(maxPt_denom > 0) {

      
            
      denom->Fill(maxPt_denom,weight);
      if(triggerDecision_40_ZeroBiasCopy==1) num_40_ZeroBiasCopy->Fill(maxPt_denom,weight);
      if(triggerDecision_40_L1Jet20==1) num_40_L1Jet20->Fill(maxPt_denom,weight);
      if(triggerDecision_40_L1Jet24==1) num_40_L1Jet24->Fill(maxPt_denom,weight);
      if(triggerDecision_60==1) num_60->Fill(maxPt_denom,weight);
      if(triggerDecision_80_L1SingleJet60==1) num_80_L1SingleJet60->Fill(maxPt_denom,weight);
      if(triggerDecision_110==1) num_110->Fill(maxPt_denom,weight);
      if(triggerDecision_140==1) num_140->Fill(maxPt_denom,weight);
            
    }


  }


 


  auto wf = TFile::Open(output,"recreate");

  denom->Write();

  num_40_ZeroBiasCopy->Write();
  num_40_L1Jet20->Write();
  num_40_L1Jet24->Write();
  num_60->Write();
  num_80_L1SingleJet60->Write();
  num_110->Write();
  num_140->Write();


  wf->Close();

		     

}


