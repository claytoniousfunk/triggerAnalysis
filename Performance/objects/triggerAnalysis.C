#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TObjArray.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TLine.h>
#include <TLegend.h>
#include <TLatex.h>

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "../../CorrelationTuple/EventMatcher.h"
#include "../../TreeHeaders/CutConfigurationTree.h"
#include "../../TreeHeaders/hltObjectTree.h"
#include "../../TreeHeaders/l1ObjectTree.h"
#include "../../TreeHeaders/ggHiNtuplizerTree.h"
#include "../../TreeHeaders/hiEvtTree.h"
#include "../../TreeHeaders/skimAnalysisTree.h"
#include "../../TreeHeaders/L1AnalysisEventDataFormat.h"
#include "../../TreeHeaders/L1AnalysisL1UpgradeDataFormat.h"
#include "../../Utilities/interface/ArgumentParser.h"
#include "../../Utilities/interface/ConfigurationParser.h"
#include "../../Utilities/interface/GraphicsConfigurationParser.h"
#include "../../Utilities/interface/InputConfigurationParser.h"
#include "../../Utilities/interface/HiForestInfoController.h"
#include "../../Utilities/eventUtil.h"
#include "../../Utilities/styleUtil.h"
#include "../../Utilities/th1Util.h"
#include "../../Utilities/fileUtil.h"
#include "../../Utilities/physicsUtil.h"
#include "../interface/triggerAnalyzer.h"
#include "../../TreeHeaders/jetTree.h"

std::vector<std::pair<std::string, int>> selectionBase;
std::vector<std::string> selectionBaseEntries;

int nSelectionBaseEntries;


std::vector<int> indicesMapNum;
std::vector<int> indicesMapDenomGlobal;
std::vector<int> indicesMapDenom;
std::vector<std::string> triggerBranches;  // list of all trigger branches to be used. Elements are unique

std::vector<int> indicesMapPrescaleNum;
std::vector<int> indicesMapPrescaleDenom;
std::vector<std::string> prescaleBranches;  // list of all prescale branches to be used. Elements are unique

std::vector<double> triggerThresholds;

// Trigger objects for matching to offline object
std::vector<std::string> triggerBranches4TrigObj;
std::vector<int> indicesMapNum2TrigObject;

// triggers that go into numerator
std::vector<std::string> triggerBranchesNum;
// global denominator : list of triggers that define the subset of events to consider.
std::vector<std::string> triggerBranchesDenomGlobal;
// individual denominators
std::vector<std::string> triggerBranchesDenom;
// prescales to check in numerators and denominators
std::vector<std::string> prescaleBranchesNum;
// prescales to check only in denominators
std::vector<std::string> prescaleBranchesDenom;
// input for TTree
std::string treePath;
int collisionType;

std::vector<float> bins_recoPt;
int nBins_recoPt;

int  readConfiguration(std::string configFile, std::string inputFile);
void printConfiguration();
void setRunLumiNumbers();
void indexTriggerBranches();
void indexTriggerBranches4TrigObj();
bool passedRunLumi(unsigned int run, unsigned int lumi);
bool passedDenomGlobal(bool triggerBits[]);
bool passedDenom(int iTriggerDenom, bool triggerBits[]);

TH1D *myHistDenom = new TH1D("myHistDenom","myHistDenom",20,0,120);


// enum RECOOBJS {
//     kPhoton,
//     kElectron,
//     kN_RECOOBJS
// };
// const std::string recoObjsStr[kN_RECOOBJS] = {"photon", "electron"};
// int recoObj;

// enum MODES {
//     kAnaType,
//     kEff,
//     kInEff,
//     kFakeRate,
//     kOfflineEnergy,
//     kN_MODES
// };
// const std::string modesStr[kN_MODES] = {"AnaType", "Eff", "InEff", "FakeRate", "OfflineEnergy"};
// std::vector<int> runMode;

// enum MODES_ANATYPE {
//     kData,
//     kEmulation,
//     kL1Objects,
//     kDataMatchL1ObjEvts,    // same analysis as kData, but the events are matched to the ones in L1Objects file.
//     kN_MODES_ANATYPE
// };

// enum MODES_EFF {
//     kNULL,
//     kTriggerBit,
//     kMatchHltObj,
//     kMatchL1Obj,
//     kMatchHltandL1Obj,
//     kN_MODES_EFF
// };

// enum MODES_OFFLINEENERGY {
//     k_off_RecoPt,
//     k_off_SCE,       // super cluster energy
//     k_off_SCRawE,       // super cluster raw energy
//     kN_MODES_OFFLINEENERGY
// };

// enum ANABINS {
//     kTrigger,
//     kEta,
//     kRecoPt,
//     kCent,
//     kSumIso,
//     kSieie,
//     kR9,
//     kN_ANABINS
// };

int nTriggerAna;
// object for set of all possible trigger analyzer objects
std::vector<triggerAnalyzer> tAna[TRIGGERANA::kN_DEPS];
// Each vector will have size nTriggerAna = nTriggerBranchesNum * nBins_eta * nBins_recoPt * nBins_cent * nBins_sumIso * nBins_sieie * nBins_r9

std::vector<int> indicesTriggerNum;
std::vector<int> indicesTriggerDenom;
// look up vector for which triggerAnalyzer object corresponds to which num/denom trigger
// triggerAnalyzer object with index j corresponds to num trigger with index indicesTriggerNum[j]


int nTriggers;

int nTriggerBranchesNum;
int nTriggerBranchesDenomGlobal;
int nTriggerBranchesDenom;
int nPrescaleBranchesNum;
int nPrescaleBranchesDenom;

std::vector<unsigned int> runNumbers;
std::vector<unsigned int> lumiStartNumbers;
std::vector<unsigned int> lumiEndNumbers;
int nRunNumbers;

// event cuts/weights
int doEventWeight;


void triggerAnalysis(std::string configFile = "triggerAnalysis.conf", 
					std::string triggerFile = "openHLT.root", 
					std::string inputFile = "pythiahydjet.root", 
					std::string outputFile = "out.root"){

	

    	std::cout << "running triggerAnalysis()" << std::endl;
    	std::cout << "configFile  = " << configFile.c_str() << std::endl;
    	std::cout << "inputFile   = " << inputFile.c_str()  << std::endl;
    	std::cout << "outputFile  = " << outputFile.c_str() << std::endl;

	
	// read the configuration.  Some from the configuration file triggerAnalysis.conf, 
	//       some from lines hard-coded in the readConfiguration function.
	if (readConfiguration(configFile, inputFile) != 0)  return;
	printConfiguration();

    

	std::cout << "### input file ###" << std::endl;
	TFile* input = TFile::Open(inputFile.c_str(), "READ");



	
	
	std::vector<std::string> inputFiles = InputConfigurationParser::ParseFiles(inputFile.c_str());
    	std::cout << "input ROOT files : num = " << inputFiles.size() << std::endl;
    	std::cout << "#####" << std::endl;
    	for (std::vector<std::string>::iterator it = inputFiles.begin() ; it != inputFiles.end(); ++it) {
        	std::cout << (*it).c_str() << std::endl;
   	 }
    	std::cout << "##### END #####" << std::endl;
	
	TTree* treeggHiNtuplizer = 0;
   	TTree* treeHiEvt = 0;
	TTree* treeJet = 0;
    	TTree* treeHiForestInfo = 0;
    	TTree* treeSkim = 0;

    	int nFiles = inputFiles.size();
    	TFile* fileTmp = 0;

    	std::cout << "initial reading to get the number of entries (if there is only one input file) and HiForest info" << std::endl;
    	// read the first file only to get the HiForest info
    	std::string inputPath = inputFiles.at(0).c_str();
    	fileTmp = TFile::Open(inputPath.c_str(), "READ");
    	fileTmp->cd();

    	if (nFiles == 1) {
        	// read one tree only to get the number of entries
        	treeggHiNtuplizer = (TTree*)fileTmp->Get(treePath.c_str());
        	Long64_t entriesTmp = treeggHiNtuplizer->GetEntries();
        	std::cout << "entries = " << entriesTmp << std::endl;
        	treeggHiNtuplizer->Delete();
    	}

	treeHiForestInfo = (TTree*)fileTmp->Get("HiForestInfo/HiForest");
    	HiForestInfoController hfic(treeHiForestInfo);
    	std::cout << "### HiForestInfo Tree ###" << std::endl;
    	hfic.printHiForestInfo();
    	std::cout << "###" << std::endl;

    	fileTmp->Close();

	TFile* fileTrig = 0;
    	TTree* treeTrig = 0;
    	std::string treeTrigPath = "";
    	std::vector<TTree*> treeTrigObjs;
    	std::vector<std::string> treeTrigObjPaths;
    	TTree* treeEventTrig = 0;

    	TTree* treeL1obj = 0;
    	std::string treeL1objPath = "";
    	l1Object l1Obj;

    	EventMatcher* emTrig = 0;

    	L1Analysis::L1AnalysisEventDataFormat* L1Event = 0;
    	L1Analysis::L1AnalysisL1UpgradeDataFormat* L1Upgrade = 0;

    	setRunLumiNumbers();
    	if (nRunNumbers > 0) {
        	std::cout << "nRunNumbers (Run and Lumi Section ranges to process) = " << nRunNumbers << std::endl;
        	for (int i = 0; i < nRunNumbers; ++i) {
            		std::cout << Form("{run, lumi start, lumi end}[%d] = {%d, %d, %d}", i, runNumbers.at(i), lumiStartNumbers.at(i), lumiEndNumbers.at(i)) << std::endl;
        	}
    	}

	indexTriggerBranches();
	int nTriggerBranches =  triggerBranches.size();
    	std::cout << "nTriggerBranches (trigger branches to read) = " << nTriggerBranches << std::endl;
    	for (int i = 0; i < nTriggerBranches; ++i) {
        	std::cout << Form("triggerBranches[%d] = %s", i, triggerBranches.at(i).c_str()) << std::endl;
    	}

	int nPrescaleBranches =  prescaleBranches.size();
    	std::cout << "nPrescaleBranches (prescale branches to read) = " << nPrescaleBranches << std::endl;
    	for (int i = 0; i < nPrescaleBranches; ++i) {
        	std::cout << Form("prescaleBranches[%d] = %s", i, prescaleBranches.at(i).c_str()) << std::endl;
        	if (prescaleBranches.at(i).size() > 0 && prescaleBranches.at(i).find("Prescl") == std::string::npos) {
            		std::cout << "Warning : Branch name does not contain 'Prescl'" << std::endl;
        	}
    	}

	int nTreeTrigObjPaths = 0;

	indexTriggerBranches4TrigObj();

	nTreeTrigObjPaths = triggerBranches4TrigObj.size();

	treeTrigObjs.clear();
	treeTrigObjs.resize(nTreeTrigObjPaths);

	treeTrigObjPaths.clear();
	treeTrigObjPaths.resize(nTreeTrigObjPaths);

	for (int i = 0; i < nTreeTrigObjPaths; ++i) {

            std::string hltObjectPath = "";
            std::string hltObjectName = triggerAnalyzer::getHLTObjectName(triggerBranches4TrigObj.at(i).c_str());
            if (hltObjectName.size() > 0)
                hltObjectPath = Form("hltobject/%s", hltObjectName.c_str());

            treeTrigObjPaths.at(i) = hltObjectPath;
    	}

	std::cout << "nTreeTrigObjPaths (Trigger object trees to read) = " << nTreeTrigObjPaths << std::endl;
    	for (int i = 0; i < nTreeTrigObjPaths; ++i) {
        	std::cout << Form("treeTrigObjPaths[%d] = ", i) << treeTrigObjPaths.at(i).c_str() << std::endl;
    	}

	bool hasPseudoTriggerBranches = false;
    	for (int i = 0; i < nTriggerBranches; ++i) {
        	if (triggerBranches.at(i).find("pseudo") != std::string::npos) {
            		hasPseudoTriggerBranches = true;
            		break;
        	}
    	}
    	std::cout << "hasPseudoTriggerBranches = " << hasPseudoTriggerBranches << std::endl;

	// These needed to be changed from both being Int_t -- maybe a change in MiniAOD?
	Bool_t triggerBits[nTriggerBranches];
    	Float_t triggerPrescales[nPrescaleBranches];

	std::vector<hltObject> hltObjs(nTreeTrigObjPaths);

	 std::cout << "### HLT bit analysis file ###" << std::endl;
     	fileTrig = TFile::Open(triggerFile.c_str(), "READ");
     	fileTrig->cd();

	 treeTrigPath = "hltanalysis/HltTree";
     	treeTrig = (TTree*)fileTrig->Get(treeTrigPath.c_str());
     	treeTrig->SetBranchStatus("*",0);     // disable all branches

	 // specify explicitly which branches to use
        treeTrig->SetBranchStatus("Event", 1);
        treeTrig->SetBranchStatus("LumiBlock", 1);
        treeTrig->SetBranchStatus("Run", 1);

        ULong64_t       hlt_event;
        Int_t           hlt_lumi;
        Int_t           hlt_run;
        std::cout << "Setting Event, lumi, and run branchAdresses...";
        treeTrig->SetBranchAddress("Event", &hlt_event);
        treeTrig->SetBranchAddress("LumiBlock", &hlt_lumi);
        treeTrig->SetBranchAddress("Run", &hlt_run);
        std::cout << "done" << std::endl;

		
        
        triggerAnalyzer::setBranchesTrigger(treeTrig, triggerBranches, triggerBits, nTriggerBranches);
        triggerAnalyzer::setBranchesTriggerPrescl(treeTrig, prescaleBranches, triggerPrescales, nPrescaleBranches);

		// set all the branches up for reading
        for (int i = 0; i < nTreeTrigObjPaths; ++i) {
            std::string treeHltObjectPath = treeTrigObjPaths.at(i).c_str();
            treeTrigObjs[i] = 0;
            treeTrigObjs[i] = (TTree*)fileTrig->Get(treeHltObjectPath.c_str());
            if (!treeTrigObjs[i]) {
                treeHltObjectPath = replaceAll(treeHltObjectPath, "_v", "");
            }
            treeTrigObjs[i] = (TTree*)fileTrig->Get(treeHltObjectPath.c_str());

            if (!treeTrigObjs[i]) {
                std::cout << "tree is not found in the path : "<< treeHltObjectPath.c_str() <<". skipping the tree." << std::endl;
                continue;
            }

            treeTrigObjs[i]->SetBranchStatus("*", 1);
            hltObjs[i].reset();
            hltObjs[i].setupTreeForReading(treeTrigObjs[i]);
        }

		
        
        emTrig = new EventMatcher();

        Long64_t duplicateEntriesHlt = 0;
        Long64_t entriesHlt = 0;
        Long64_t entriesAnalyzedHlt = 0;

	std::cout << "Loop HLT: " << treeTrigPath.c_str() << std::endl;
        entriesHlt = treeTrig->GetEntries();
        std::cout << "entries in HLT File = " << entriesHlt << std::endl;
        for (Long64_t j_entry = 0; j_entry < entriesHlt; ++j_entry)
        {
            if (j_entry % 2000 == 0)  {
                std::cout << "current entry = " <<j_entry<< " out of " <<entriesHlt<< " : " <<std::setprecision(2)<<(double)j_entry/entriesHlt*100<< " %" << std::endl;
            }

            treeTrig->GetEntry(j_entry);

            bool eventAdded = emTrig->addEvent(hlt_run, hlt_lumi, hlt_event, j_entry);
            if(!eventAdded) // this event is duplicate, skip this one.
            {
                duplicateEntriesHlt++;
                continue;
            }

            entriesAnalyzedHlt++;
        }
        std::cout << "Loop HLT ENDED : " << treeTrigPath.c_str() << std::endl;
        std::cout << "entries HLT          = " << entriesHlt << std::endl;
        std::cout << "duplicateEntries HLT = " << duplicateEntriesHlt << std::endl;
        std::cout << "entriesAnalyzed HLT  = " << entriesAnalyzedHlt << std::endl;
        std::cout << "###" << std::endl;

	EventMatcher* em = new EventMatcher();
	Long64_t duplicateEntries = 0;

	Long64_t entries = 0;
	Long64_t entriesNotFoundinTrigger = 0;
	Long64_t entriesPassedDenomGlobal = 0;
	Long64_t entriesAnalyzed = 0;

	int nFilesSkipped = 0;
	std::cout << "Loop : " << treePath.c_str() << std::endl;
    	for (int iFile = 0; iFile < nFiles; ++iFile)  {

		std::string inputPath = inputFiles.at(iFile).c_str();
		std::cout << "iFile = " << iFile << " , " ;
		std::cout << "reading input file : " << inputPath.c_str() << std::endl;
		fileTmp = TFile::Open(inputPath.c_str(), "READ");

		treeggHiNtuplizer = (TTree*)fileTmp->Get(treePath.c_str());
        	treeggHiNtuplizer->SetBranchStatus("*",0);     // disable all branches

		 // specify explicitly which branches to use, do not use wildcard
        	treeJet = (TTree*)fileTmp->Get("akCs4PFJetAnalyzer/t");
        	treeJet->SetBranchStatus("*",0);     // disable all branches
        	treeJet->SetBranchStatus("jtpt",1);   // enable event information
            	treeJet->SetBranchStatus("jteta",1);
            	treeJet->SetBranchStatus("nref",1);

		treeSkim = (TTree*)fileTmp->Get("skimanalysis/HltTree");
        	treeSkim->SetBranchStatus("*",0);     // disable all branches

            	treeHiEvt = (TTree*)fileTmp->Get("hiEvtAnalyzer/HiTree");
            	treeHiEvt->SetBranchStatus("*",0);     // disable all branches
            	treeHiEvt->SetBranchStatus("run",1);   // enable event information
            	treeHiEvt->SetBranchStatus("evt",1);
            	treeHiEvt->SetBranchStatus("lumi",1);
            	treeHiEvt->SetBranchStatus("vz",1);
            	treeHiEvt->SetBranchStatus("hiBin",1);
            	if (doEventWeight > 0) {
                	treeHiEvt->SetBranchStatus("weight", 1);
            	}

		ggHiNtuplizer ggHi;
        	ggHi.setupTreeForReading(treeggHiNtuplizer);

		hiEvt hiEvt;
		hiEvt.setupTreeForReading(treeHiEvt);

            	jet jet;
            	jet.setupTreeForReading(treeJet);

		// skimAnalysis skimAna;
		// skimAna.enableBranchesPP(treeSkim);
		// skimAna.setupTreeForReading(treeSkim);
		// skimAna.checkBranches(treeSkim);    // do the event selection if the branches exist.

		Long64_t entriesTmp = treeggHiNtuplizer->GetEntries();
		entries += entriesTmp;
        	std::cout << "entries in File = " << entriesTmp << std::endl;

		for (Long64_t j_entry = 0; j_entry < entriesTmp; ++j_entry){
				
			if (j_entry % 2000 == 0)  {
				std::cout << "current entry = " <<j_entry<< " out of " <<entriesTmp<< " : " <<std::setprecision(2)<<(double)j_entry/entriesTmp*100<< " %" << std::endl;
			}

			treeggHiNtuplizer->GetEntry(j_entry);
			treeHiEvt->GetEntry(j_entry);
           		treeSkim->GetEntry(j_entry);
			treeJet->GetEntry(j_entry);

			bool eventAdded = em->addEvent(hiEvt.run, hiEvt.lumi, hiEvt.evt, j_entry);
			if(!eventAdded) // this event is duplicate, skip this one.
			{
				duplicateEntries++;
				continue;
			}

                //std::cout << "Entry# " << j_entry << " passedRunLumi?...";

                if (!passedRunLumi(hiEvt.run, hiEvt.lumi)) {
                    //std::cout << "NO!" << std::endl;
                    continue;
                }
                //else std::cout << "YES!" << std::endl;
                //else std::cout << "event " << j_entry << " added!" << std::endl;

		Long64_t entryTrig = 0;

                // find the event in Hlt file
                entryTrig = emTrig->getEntry(hiEvt.run, hiEvt.lumi, hiEvt.evt);
                if (entryTrig < 0) {
                    std::cout << "Entry#" << j_entry << " not found in HLT file!" << std::endl;
                    entriesNotFoundinTrigger++;
                    continue;
                }
                
                emTrig->removeEvent(hiEvt.run, hiEvt.lumi, hiEvt.evt);
				
             
                if (!passedDenomGlobal(triggerBits)) {
                    std::cout << "Entry#" << j_entry << " failed passedDenomGlobal!" << std::endl;
                    continue;
                }
                entriesPassedDenomGlobal++;

                // event selection
                if (!(TMath::Abs(hiEvt.vz) < 15)){
                    std::cout << "Entry#" << j_entry << " failed vz selection!" << std::endl;
                    continue;
                }  

                entriesAnalyzed++;

		treeTrig->GetEntry(entryTrig);

		for (int i = 0; i < nTreeTrigObjPaths; ++i) {
                	treeTrigObjs[i]->GetEntry(entryTrig);
            	}

		double w = 1;
            	int hiBin = hiEvt.hiBin;
            	int cent = hiBin/2;          
                
                // jet loop
                for (int iAna = 0;  iAna < nTriggerAna; ++iAna) {

                    int iMax = -1;
                    double maxPt = 0;
                    int nObjs = 0;

                    nObjs = jet.njet;

                    for (int i=0; i<nObjs; ++i) {

                        double pt = jet.jtpt[i];

                        if (pt > maxPt) {
                            iMax = i;
                            maxPt = pt;
                        }

                    }

                    // leading object goes into histograms
                    if(iMax == -1) continue;


                    if (passedDenom(indicesTriggerDenom[iAna], triggerBits)) std::cout << "passedDenom = true" << std::endl;
                    else std::cout << "passedDenom = false" << std::endl;



                    double pt = maxPt;
                    double eta = -999;
                    double phi = -999;
                    double ecalIso = 0;
                    double hcalIso = 0;
                    double trkIso = 0;
                    double sumIso = ecalIso + hcalIso + trkIso;
                    double sieie = -1;
                    double r9 = -1;
                    double scEta = -999;

                    std::vector<double> vars = {eta, pt, (double)cent, sumIso, sieie, r9};
                    //tAna[TRIGGERANA::kRECOPT][iAna].FillHDenom(maxPt, w, vars);
                    
                    myHistDenom->Fill(maxPt,w);



                }

	}

}

auto wf = TFile::Open("out.root","recreate");

myHistDenom->Write();

wf->Close();

    

}

int readConfiguration(std::string configFile, std::string inputFile){

	ConfigurationParser confParser;
    	confParser.openConfigFile(configFile);

	confParser.parsedKeyWords = InputConfigurationParser::parseKeyWords(inputFile);

    	for(int i = 0; i < confParser.parsedKeyWords.size(); i++){
        	std::cout << "[triggerAnalysis::readConfiguration] confParser.parsedKeyWords(" << i << ") = " << confParser.parsedKeyWords.at(i) << std::endl;
    	}
    

	std::cout << "[triggerAnalysis::readConfiguration] reading treePath...";
    	//treePath = confParser.ReadConfigValue("treePath");
    	treePath = "ggHiNtuplizer/EventTree";
    	std::cout << "treePath = " << treePath << std::endl;

    	std::cout << "[triggerAnalysis::readConfiguration] reading collisionType...";
    	//collisionType = confParser.ReadConfigValueInteger("collisionType");
    	collisionType = 7;
    	std::cout << "collisionType = " << collisionType << std::endl;

	std::cout << "[triggerAnalysis::readConfiguration] reading selectionBase..." << std::endl;
    	//selectionBase = ConfigurationParser::ParseListOfList(confParser.ReadConfigValue("treeSelectionBase"));
    	selectionBase = {};
    	//std::cout << "selectionBase = " << selectionBase << std::endl;
    
    
    
    	std::cout << "[triggerAnalysis::readConfiguration] reading selectionBaseEntries..." << std::endl;
    	//selectionBaseEntries = ConfigurationParser::getVecString(selectionBase);
    	selectionBaseEntries = {};
	nSelectionBaseEntries = selectionBaseEntries.size();

	std::cout << "[triggerAnalysis::readConfiguration] reading triggerBranchesNum..." << std::endl;
    	//triggerBranchesNum = ConfigurationParser::ParseList(confParser.ReadConfigValue("triggerNum_List"));
    	triggerBranchesNum = {"HLT_HICsAK4PFJet60Eta1p5_v",
                          "HLT_HICsAK4PFJet80Eta1p5_v",
                          "HLT_HICsAK4PFJet100Eta1p5_v",
                          "HLT_HICsAK4PFJet120Eta1p5_v"};
    	//for(int i = 0; i < triggerBranchesNum.size(); i++){
    	//    std::cout << "[triggerAnalysis::readConfiguration] triggerBranchesNum(" << i << ") = " << triggerBranchesNum.at(i) << std::endl;
    	//}

    	std::cout << "[triggerAnalysis::readConfiguration] reading triggerBranchesDenomGlobal..." << std::endl;
    	//triggerBranchesDenomGlobal = ConfigurationParser::ParseList(confParser.ReadConfigValue("triggerDenomGlobal_List"));
    	triggerBranchesDenomGlobal = {};
    	std::cout << "[triggerAnalysis::readConfiguration] reading triggerBranchesDenom..." << std::endl;
    	//triggerBranchesDenom = ConfigurationParser::ParseList(confParser.ReadConfigValue("triggerDenom_List"));
    	triggerBranchesDenom = {};
    	std::cout << "[triggerAnalysis::readConfiguration] reading prescaleBranchesNum..." << std::endl;
    	//prescaleBranchesNum = ConfigurationParser::ParseList(confParser.ReadConfigValue("triggerNumPrescl_List"));
    	prescaleBranchesNum = {"HLT_HICsAK4PFJet60Eta1p5_v_Prescl",
                          "HLT_HICsAK4PFJet80Eta1p5_v_Prescl",
                          "HLT_HICsAK4PFJet100Eta1p5_v_Prescl",
                          "HLT_HICsAK4PFJet120Eta1p5_v_Prescl"};
    	std::cout << "[triggerAnalysis::readConfiguration] reading prescaleBranchesDenom..." << std::endl;
    	//prescaleBranchesDenom = ConfigurationParser::ParseList(confParser.ReadConfigValue("triggerDenomPrescl_List"));
    	prescaleBranchesDenom = {};

	nTriggerBranchesNum = triggerBranchesNum.size();
    	nTriggerBranchesDenomGlobal = triggerBranchesDenomGlobal.size();
    	nTriggerBranchesDenom = triggerBranchesDenom.size();
    	nPrescaleBranchesNum = prescaleBranchesNum.size();
    	nPrescaleBranchesDenom = prescaleBranchesDenom.size();

	if (nTriggerBranchesNum > 1 && nTriggerBranchesDenom > 1 && nTriggerBranchesNum != nTriggerBranchesDenom) {
        	std::cout << "mismatch in the number of numerators and denominators :" << std::endl;
        	std::cout << "nTriggerBranchesNum = " << nTriggerBranchesNum << std::endl;
        	std::cout << "nTriggerBranchesDenom = " << nTriggerBranchesDenom << std::endl;
        	std::cout << "exiting" << std::endl;
        	return -1;
    	}

    	nTriggers = nTriggerBranchesNum;
    	if (nTriggerBranchesDenom > 1) nTriggers = nTriggerBranchesDenom;

    	if (nPrescaleBranchesNum > 0 && nPrescaleBranchesNum != nTriggerBranchesNum)
    	{
        	std::cout << "mismatch in the number of numerators and prescales to be used for numerators :" << std::endl;
        	std::cout << "nTriggerBranchesNum = " << nTriggerBranchesNum << " and nPrescaleBranchesNum = " << nPrescaleBranchesNum << std::endl;
        	std::cout << "exiting" << std::endl;
        	return -1;
    	}
    	if (nPrescaleBranchesDenom > 0 && nPrescaleBranchesDenom != nTriggerBranchesDenom)
    	{
        	std::cout << "mismatch in the number of denominators and prescales to be used for denominators :" << std::endl;
        	std::cout << "nTriggerBranchesDenom = " << nTriggerBranchesDenom << " and nPrescaleBranchesDenom = " << nPrescaleBranchesDenom << std::endl;
        	std::cout << "exiting" << std::endl;
        	return -1;
    	}

    	bins_recoPt = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150};
    	nBins_recoPt = bins_recoPt.size();
	
  	nTriggerAna = nTriggers * nBins_recoPt;

    	std::cout << "[triggerAnalysis::readConfiguration] nTriggerAna = " << nTriggerAna << std::endl;

	return 0;

}

void printConfiguration(){

	std::cout << "nTriggerBranchesNum  = " << nTriggerBranchesNum << std::endl;
    	for (int i = 0; i<nTriggerBranchesNum; ++i) {
        	std::cout << Form("triggerBranchesNum[%d] = %s", i, triggerBranchesNum.at(i).c_str()) << std::endl;
    	}
    	std::cout << "nTriggerBranchesDenomGlobal  = " << nTriggerBranchesDenomGlobal << std::endl;
    	for (int i = 0; i<nTriggerBranchesDenomGlobal; ++i) {
        	std::cout << Form("triggerBranchesDenomGlobal[%d] = %s", i, triggerBranchesDenomGlobal.at(i).c_str()) << std::endl;
    	}
    	std::cout << "nTriggerBranchesDenom  = " << nTriggerBranchesDenom << std::endl;
    	for (int i = 0; i<nTriggerBranchesDenom; ++i) {
        	std::cout << Form("triggerBranchesDenom[%d] = %s", i, triggerBranchesDenom.at(i).c_str()) << std::endl;
    	}

    	std::cout << "nPrescaleBranchesNum = " << nPrescaleBranchesNum << std::endl;
    	for (int i = 0; i < nPrescaleBranchesNum; ++i) {
        	std::cout << Form("prescaleBranchesNum[%d] = ", i) << prescaleBranchesNum.at(i).c_str() << std::endl;
    	}
    	std::cout << "nPrescaleBranchesDenom = " << nPrescaleBranchesDenom << std::endl;
    	for (int i = 0; i < nPrescaleBranchesDenom; ++i) {
        	std::cout << Form("prescaleBranchesDenom[%d] = ", i) << prescaleBranchesDenom.at(i).c_str() << std::endl;
    	}
}

// int  preLoop(TFile* input, bool makeNew)
// {
//     if (!makeNew) {
//         // check if the file is available
//         if (input == 0 ) return -1;
//         else if (!input->IsOpen()) return -1;
//         input->cd();
//     }

//     TH1::SetDefaultSumw2();

// 	for (int iDep = 0; iDep < TRIGGERANA::kN_DEPS; ++iDep) {


// 		std::cout << "iDep = " << iDep << std::endl;



// 	}


void setRunLumiNumbers()
{
    runNumbers.clear();
    lumiStartNumbers.clear();
    lumiEndNumbers.clear();

    if (nSelectionBaseEntries % 3 != 0)  return;

    for (int i = 0; i < nSelectionBaseEntries; i+=3) {

        runNumbers.push_back(std::atoi(selectionBaseEntries.at(i).c_str()));
        lumiStartNumbers.push_back(std::atoi(selectionBaseEntries.at(i+1).c_str()));
        lumiEndNumbers.push_back(std::atoi(selectionBaseEntries.at(i+2).c_str()));
    }

    nRunNumbers = runNumbers.size();
}


void indexTriggerBranches()
{
    triggerBranches.clear();
    triggerBranches.insert(triggerBranches.end(), triggerBranchesNum.begin(), triggerBranchesNum.end());
    triggerBranches.insert(triggerBranches.end(), triggerBranchesDenomGlobal.begin(), triggerBranchesDenomGlobal.end());
    triggerBranches.insert(triggerBranches.end(), triggerBranchesDenom.begin(), triggerBranchesDenom.end());

    triggerBranches = vectorUnique(triggerBranches);

    indicesMapNum.clear();
    indicesMapNum.resize((int)triggerBranchesNum.size());
    for (int i = 0; i < (int)triggerBranchesNum.size(); ++i) {
        indicesMapNum[i] = findPositionInVector(triggerBranches, triggerBranchesNum[i].c_str());
    }

    indicesMapDenomGlobal.clear();
    indicesMapDenomGlobal.resize((int)triggerBranchesDenomGlobal.size());
    for (int i = 0; i < (int)triggerBranchesDenomGlobal.size(); ++i) {
        indicesMapDenomGlobal[i] = findPositionInVector(triggerBranches, triggerBranchesDenomGlobal[i].c_str());
    }

    indicesMapDenom.clear();
    indicesMapDenom.resize((int)triggerBranchesDenom.size());
    for (int i = 0; i < (int)triggerBranchesDenom.size(); ++i) {
        indicesMapDenom[i] = findPositionInVector(triggerBranches, triggerBranchesDenom[i].c_str());
    }

    // do the same for prescale branches
    prescaleBranches.clear();
    prescaleBranches.insert(prescaleBranches.end(), prescaleBranchesNum.begin(), prescaleBranchesNum.end());
    prescaleBranches.insert(prescaleBranches.end(), prescaleBranchesDenom.begin(), prescaleBranchesDenom.end());

    prescaleBranches = vectorUnique(prescaleBranches);

    indicesMapPrescaleNum.clear();
    indicesMapPrescaleNum.resize((int)prescaleBranchesNum.size());
    for (int i = 0; i < (int)prescaleBranchesNum.size(); ++i) {
        indicesMapPrescaleNum[i] = findPositionInVector(prescaleBranches, prescaleBranchesNum[i].c_str());
    }

    indicesMapPrescaleDenom.clear();
    indicesMapPrescaleDenom.resize((int)prescaleBranchesDenom.size());
    for (int i = 0; i < (int)prescaleBranchesDenom.size(); ++i) {
        indicesMapPrescaleDenom[i] = findPositionInVector(prescaleBranches, prescaleBranchesDenom[i].c_str());
    }
}

void indexTriggerBranches4TrigObj()
{
    triggerBranches4TrigObj.clear();
    triggerBranches4TrigObj.insert(triggerBranches4TrigObj.end(), triggerBranchesNum.begin(), triggerBranchesNum.end());

    triggerBranches4TrigObj = vectorUnique(triggerBranches4TrigObj);

    indicesMapNum2TrigObject.clear();
    indicesMapNum2TrigObject.resize((int)triggerBranchesNum.size());
    for (int i = 0; i < (int)triggerBranchesNum.size(); ++i) {
        indicesMapNum2TrigObject[i] = findPositionInVector(triggerBranches4TrigObj, triggerBranchesNum[i].c_str());
    }
}
bool passedRunLumi(unsigned int run, unsigned int lumi)
{
    if (nRunNumbers == 0)  return true;

    for (int i = 0; i < nRunNumbers; ++i) {
        if (run == runNumbers[i] && lumi >= lumiStartNumbers[i] && lumi <= lumiEndNumbers[i])
            return true;
    }

    return false;
}
bool passedDenomGlobal(bool triggerBits[])
{
    if (nTriggerBranchesDenomGlobal == 0) return true;

    // these triggers are "OR"ed.
    for (int i = 0; i < nTriggerBranchesDenomGlobal; ++i) {
        int iTrig = indicesMapDenomGlobal[i];
        if (triggerBits[iTrig] > 0)  return true;
    }

    return false;
}
bool passedDenom(int iTriggerDenom, bool triggerBits[])
{
    if (iTriggerDenom < 0) return true;

    int iTrig = indicesMapDenom[iTriggerDenom];
    return (triggerBits[iTrig] > 0);
}



// }
