#ifndef TREEHEADERS_SKIMANALYSISTREE_H_
#define TREEHEADERS_SKIMANALYSISTREE_H_

#include <TTree.h>
#include <TBranch.h>

#include <vector>

class skimAnalysis {
public :
    skimAnalysis(){
        has_ana_step = false;
        has_pcollisionEventSelection = false;
        has_pHBHENoiseFilterResultProducer = false;
        has_HBHENoiseFilterResult = false;
        has_HBHENoiseFilterResultRun1 = false;
        has_HBHENoiseFilterResultRun2Loose = false;
        has_HBHENoiseFilterResultRun2Tight = false;
        has_HBHEIsoNoiseFilterResult = false;
        has_pprimaryVertexFilter = false;
        has_phfCoincFilter1 = false;
        has_phfCoincFilter2 = false;
        has_phfCoincFilter3 = false;
        has_phfCoincFilter4 = false;
        has_phfCoincFilter5 = false;
        has_pclusterCompatibilityFilter = false;
        has_superFilterPath = false;
        // pp, pA
        has_pPAprimaryVertexFilter = false;
        has_pBeamScrapingFilter = false;
        has_pVertexFilterCutG = false;
        has_pVertexFilterCutGloose = false;
        has_pVertexFilterCutGtight = false;
        has_pVertexFilterCutGplus = false;
        has_pVertexFilterCutE = false;
        has_pVertexFilterCutEandG = false;
    };
    ~skimAnalysis(){};
    void setupTreeForReading(TTree *t);
    void setupTreeForWriting(TTree *t);
    void enableBranchesHI(TTree *t);
    void enableBranchesHI2018(TTree *t);
    void enableBranchesPP(TTree *t);
    void checkBranches(TTree *t);
    bool passedEventSelectionHI();
    bool passedEventSelectionHI2018();
    bool passedEventSelectionPP();

    // Declaration of leaf types
    // PbPb
    Int_t           ana_step;
    Int_t           pcollisionEventSelection;
    Int_t           pHBHENoiseFilterResultProducer;
    Int_t           HBHENoiseFilterResult;
    Int_t           HBHENoiseFilterResultRun1;
    Int_t           HBHENoiseFilterResultRun2Loose;
    Int_t           HBHENoiseFilterResultRun2Tight;
    Int_t           HBHEIsoNoiseFilterResult;
    Int_t           pprimaryVertexFilter;
    Int_t           phfCoincFilter1;
    Int_t           phfCoincFilter2;
    Int_t           phfCoincFilter3;
    Int_t           phfCoincFilter4;
    Int_t           phfCoincFilter5;
    Int_t           pclusterCompatibilityFilter;
    Int_t           superFilterPath;
    // pp, pA
    Int_t           pPAprimaryVertexFilter;
    Int_t           pBeamScrapingFilter;
    Int_t           pVertexFilterCutG;
    Int_t           pVertexFilterCutGloose;
    Int_t           pVertexFilterCutGtight;
    Int_t           pVertexFilterCutGplus;
    Int_t           pVertexFilterCutE;
    Int_t           pVertexFilterCutEandG;
    // 2018
    Int_t           collisionEventSelectionAOD;
    Int_t           collisionEventSelectionAODv2;
    Int_t           phfCoincFilter1Th3;
    Int_t           phfCoincFilter2Th3;
    Int_t           phfCoincFilter3Th3;
    Int_t           phfCoincFilter4Th3;
    Int_t           phfCoincFilter5Th3;
    Int_t           phfCoincFilter1Th4;
    Int_t           phfCoincFilter2Th4;
    Int_t           phfCoincFilter3Th4;
    Int_t           phfCoincFilter4Th4;
    Int_t           phfCoincFilter5Th4;
    Int_t           phfCoincFilter1Th5;
    Int_t           phfCoincFilter4Th2;

    // List of branches
    // PbPb
    TBranch        *b_ana_step;   //!
    TBranch        *b_pcollisionEventSelection;   //!
    TBranch        *b_pHBHENoiseFilterResultProducer;   //!
    TBranch        *b_HBHENoiseFilterResult;   //!
    TBranch        *b_HBHENoiseFilterResultRun1;   //!
    TBranch        *b_HBHENoiseFilterResultRun2Loose;   //!
    TBranch        *b_HBHENoiseFilterResultRun2Tight;   //!
    TBranch        *b_HBHEIsoNoiseFilterResult;   //!
    TBranch        *b_pprimaryVertexFilter;   //!
    TBranch        *b_phfCoincFilter1;   //!
    TBranch        *b_phfCoincFilter2;   //!
    TBranch        *b_phfCoincFilter3;   //!
    TBranch        *b_phfCoincFilter4;   //!
    TBranch        *b_phfCoincFilter5;   //!
    TBranch        *b_pclusterCompatibilityFilter;   //!
    TBranch        *b_superFilterPath;   //!
    // pp, pA
    TBranch        *b_pPAprimaryVertexFilter;   //!
    TBranch        *b_pBeamScrapingFilter;   //!
    TBranch        *b_pVertexFilterCutG;   //!
    TBranch        *b_pVertexFilterCutGloose;   //!
    TBranch        *b_pVertexFilterCutGtight;   //!
    TBranch        *b_pVertexFilterCutGplus;   //!
    TBranch        *b_pVertexFilterCutE;   //!
    TBranch        *b_pVertexFilterCutEandG;   //!
    // 2018
    TBranch        *b_collisionEventSelectionAOD;
    TBranch        *b_collisionEventSelectionAODv2;
    TBranch        *b_phfCoincFilter1Th3;
    TBranch        *b_phfCoincFilter2Th3;
    TBranch        *b_phfCoincFilter3Th3;
    TBranch        *b_phfCoincFilter4Th3;
    TBranch        *b_phfCoincFilter5Th3;
    TBranch        *b_phfCoincFilter1Th4;
    TBranch        *b_phfCoincFilter2Th4;
    TBranch        *b_phfCoincFilter3Th4;
    TBranch        *b_phfCoincFilter4Th4;
    TBranch        *b_phfCoincFilter5Th4;
    TBranch        *b_phfCoincFilter1Th5;
    TBranch        *b_phfCoincFilter4Th2;

    // flags to check if the tree has the branches
    bool has_ana_step;
    bool has_pcollisionEventSelection;
    bool has_pHBHENoiseFilterResultProducer;
    bool has_HBHENoiseFilterResult;
    bool has_HBHENoiseFilterResultRun1;
    bool has_HBHENoiseFilterResultRun2Loose;
    bool has_HBHENoiseFilterResultRun2Tight;
    bool has_HBHEIsoNoiseFilterResult;
    bool has_pprimaryVertexFilter;
    bool has_phfCoincFilter1;
    bool has_phfCoincFilter2;
    bool has_phfCoincFilter3;
    bool has_phfCoincFilter4;
    bool has_phfCoincFilter5;
    bool has_pclusterCompatibilityFilter;
    bool has_superFilterPath;
    // pp, pA
    bool has_pPAprimaryVertexFilter;
    bool has_pBeamScrapingFilter;
    bool has_pVertexFilterCutG;
    bool has_pVertexFilterCutGloose;
    bool has_pVertexFilterCutGtight;
    bool has_pVertexFilterCutGplus;
    bool has_pVertexFilterCutE;
    bool has_pVertexFilterCutEandG;
    // 2018
    bool has_collisionEventSelectionAOD;
    bool has_collisionEventSelectionAODv2;
    bool has_phfCoincFilter1Th3;
    bool has_phfCoincFilter2Th3;
    bool has_phfCoincFilter3Th3;
    bool has_phfCoincFilter4Th3;
    bool has_phfCoincFilter5Th3;
    bool has_phfCoincFilter1Th4;
    bool has_phfCoincFilter2Th4;
    bool has_phfCoincFilter3Th4;
    bool has_phfCoincFilter4Th4;
    bool has_phfCoincFilter5Th4;
    bool has_phfCoincFilter1Th5;
    bool has_phfCoincFilter4Th2;
};

void skimAnalysis::setupTreeForReading(TTree *t)
{
    // Set branch addresses and branch pointers
    if (t->GetBranch("ana_step"))  t->SetBranchAddress("ana_step", &ana_step, &b_ana_step);
    if (t->GetBranch("pcollisionEventSelection"))  t->SetBranchAddress("pcollisionEventSelection", &pcollisionEventSelection, &b_pcollisionEventSelection);
    if (t->GetBranch("pHBHENoiseFilterResultProducer"))  t->SetBranchAddress("pHBHENoiseFilterResultProducer", &pHBHENoiseFilterResultProducer, &b_pHBHENoiseFilterResultProducer);
    if (t->GetBranch("HBHENoiseFilterResult"))  t->SetBranchAddress("HBHENoiseFilterResult", &HBHENoiseFilterResult, &b_HBHENoiseFilterResult);
    if (t->GetBranch("HBHENoiseFilterResultRun1"))  t->SetBranchAddress("HBHENoiseFilterResultRun1", &HBHENoiseFilterResultRun1, &b_HBHENoiseFilterResultRun1);
    if (t->GetBranch("HBHENoiseFilterResultRun2Loose"))  t->SetBranchAddress("HBHENoiseFilterResultRun2Loose", &HBHENoiseFilterResultRun2Loose, &b_HBHENoiseFilterResultRun2Loose);
    if (t->GetBranch("HBHENoiseFilterResultRun2Tight"))  t->SetBranchAddress("HBHENoiseFilterResultRun2Tight", &HBHENoiseFilterResultRun2Tight, &b_HBHENoiseFilterResultRun2Tight);
    if (t->GetBranch("HBHEIsoNoiseFilterResult"))  t->SetBranchAddress("HBHEIsoNoiseFilterResult", &HBHEIsoNoiseFilterResult, &b_HBHEIsoNoiseFilterResult);
    if (t->GetBranch("pprimaryVertexFilter"))  t->SetBranchAddress("pprimaryVertexFilter", &pprimaryVertexFilter, &b_pprimaryVertexFilter);
    if (t->GetBranch("phfCoincFilter1"))  t->SetBranchAddress("phfCoincFilter1", &phfCoincFilter1, &b_phfCoincFilter1);
    if (t->GetBranch("phfCoincFilter2"))  t->SetBranchAddress("phfCoincFilter2", &phfCoincFilter2, &b_phfCoincFilter2);
    if (t->GetBranch("phfCoincFilter3"))  t->SetBranchAddress("phfCoincFilter3", &phfCoincFilter3, &b_phfCoincFilter3);
    if (t->GetBranch("phfCoincFilter4"))  t->SetBranchAddress("phfCoincFilter4", &phfCoincFilter4, &b_phfCoincFilter4);
    if (t->GetBranch("phfCoincFilter5"))  t->SetBranchAddress("phfCoincFilter5", &phfCoincFilter5, &b_phfCoincFilter5);
    if (t->GetBranch("pclusterCompatibilityFilter"))  t->SetBranchAddress("pclusterCompatibilityFilter", &pclusterCompatibilityFilter, &b_pclusterCompatibilityFilter);
    if (t->GetBranch("superFilterPath"))  t->SetBranchAddress("superFilterPath", &superFilterPath, &b_superFilterPath);

    if (t->GetBranch("pPAprimaryVertexFilter"))  t->SetBranchAddress("pPAprimaryVertexFilter", &pPAprimaryVertexFilter, &b_pPAprimaryVertexFilter);
    if (t->GetBranch("pBeamScrapingFilter"))  t->SetBranchAddress("pBeamScrapingFilter", &pBeamScrapingFilter, &b_pBeamScrapingFilter);
    if (t->GetBranch("pVertexFilterCutG"))  t->SetBranchAddress("pVertexFilterCutG", &pVertexFilterCutG, &b_pVertexFilterCutG);
    if (t->GetBranch("pVertexFilterCutGloose"))  t->SetBranchAddress("pVertexFilterCutGloose", &pVertexFilterCutGloose, &b_pVertexFilterCutGloose);
    if (t->GetBranch("pVertexFilterCutGtight"))  t->SetBranchAddress("pVertexFilterCutGtight", &pVertexFilterCutGtight, &b_pVertexFilterCutGtight);
    if (t->GetBranch("pVertexFilterCutGplus"))  t->SetBranchAddress("pVertexFilterCutGplus", &pVertexFilterCutGplus, &b_pVertexFilterCutGplus);
    if (t->GetBranch("pVertexFilterCutE"))  t->SetBranchAddress("pVertexFilterCutE", &pVertexFilterCutE, &b_pVertexFilterCutE);
    if (t->GetBranch("pVertexFilterCutEandG"))  t->SetBranchAddress("pVertexFilterCutEandG", &pVertexFilterCutEandG, &b_pVertexFilterCutEandG);

    if (t->GetBranch("collisionEventSelectionAOD"))  t->SetBranchAddress("collisionEventSelectionAOD", &collisionEventSelectionAOD, &b_collisionEventSelectionAOD);
    if (t->GetBranch("collisionEventSelectionAODv2"))  t->SetBranchAddress("collisionEventSelectionAODv2", &collisionEventSelectionAODv2, &b_collisionEventSelectionAODv2);
    if (t->GetBranch("phfCoincFilter1Th3"))  t->SetBranchAddress("phfCoincFilter1Th3", &phfCoincFilter1Th3, &b_phfCoincFilter1Th3);
    if (t->GetBranch("phfCoincFilter2Th3"))  t->SetBranchAddress("phfCoincFilter2Th3", &phfCoincFilter2Th3, &b_phfCoincFilter2Th3);
    if (t->GetBranch("phfCoincFilter3Th3"))  t->SetBranchAddress("phfCoincFilter3Th3", &phfCoincFilter3Th3, &b_phfCoincFilter3Th3);
    if (t->GetBranch("phfCoincFilter4Th3"))  t->SetBranchAddress("phfCoincFilter4Th3", &phfCoincFilter4Th3, &b_phfCoincFilter4Th3);
    if (t->GetBranch("phfCoincFilter5Th3"))  t->SetBranchAddress("phfCoincFilter5Th3", &phfCoincFilter5Th3, &b_phfCoincFilter5Th3);
    if (t->GetBranch("phfCoincFilter1Th4"))  t->SetBranchAddress("phfCoincFilter1Th4", &phfCoincFilter1Th4, &b_phfCoincFilter1Th4);
    if (t->GetBranch("phfCoincFilter2Th4"))  t->SetBranchAddress("phfCoincFilter2Th4", &phfCoincFilter2Th4, &b_phfCoincFilter2Th4);
    if (t->GetBranch("phfCoincFilter3Th4"))  t->SetBranchAddress("phfCoincFilter3Th4", &phfCoincFilter3Th4, &b_phfCoincFilter3Th4);
    if (t->GetBranch("phfCoincFilter4Th4"))  t->SetBranchAddress("phfCoincFilter4Th4", &phfCoincFilter4Th4, &b_phfCoincFilter4Th4);
    if (t->GetBranch("phfCoincFilter5Th4"))  t->SetBranchAddress("phfCoincFilter5Th4", &phfCoincFilter5Th4, &b_phfCoincFilter5Th4);
    if (t->GetBranch("phfCoincFilter1Th5"))  t->SetBranchAddress("phfCoincFilter1Th5", &phfCoincFilter1Th5, &b_phfCoincFilter1Th5);
    if (t->GetBranch("phfCoincFilter4Th2"))  t->SetBranchAddress("phfCoincFilter4Th2", &phfCoincFilter4Th2, &b_phfCoincFilter4Th2);
}

void skimAnalysis::setupTreeForWriting(TTree *t)
{
    t->Branch("ana_step",&ana_step,"ana_step/I");
    t->Branch("pcollisionEventSelection",&pcollisionEventSelection,"pcollisionEventSelection/I");
    t->Branch("pHBHENoiseFilterResultProducer",&pHBHENoiseFilterResultProducer,"pHBHENoiseFilterResultProducer/I");
    t->Branch("HBHENoiseFilterResult",&HBHENoiseFilterResult,"HBHENoiseFilterResult/I");
    t->Branch("HBHENoiseFilterResultRun1",&HBHENoiseFilterResultRun1,"HBHENoiseFilterResultRun1/I");
    t->Branch("HBHENoiseFilterResultRun2Loose",&HBHENoiseFilterResultRun2Loose,"HBHENoiseFilterResultRun2Loose/I");
    t->Branch("HBHENoiseFilterResultRun2Tight",&HBHENoiseFilterResultRun2Tight,"HBHENoiseFilterResultRun2Tight/I");
    t->Branch("HBHEIsoNoiseFilterResult",&HBHEIsoNoiseFilterResult,"HBHEIsoNoiseFilterResult/I");
    t->Branch("pprimaryVertexFilter",&pprimaryVertexFilter,"pprimaryVertexFilter/I");
    t->Branch("phfCoincFilter1",&phfCoincFilter1,"phfCoincFilter1/I");
    t->Branch("phfCoincFilter2",&phfCoincFilter2,"phfCoincFilter2/I");
    t->Branch("phfCoincFilter3",&phfCoincFilter3,"phfCoincFilter3/I");
    t->Branch("phfCoincFilter4",&phfCoincFilter4,"phfCoincFilter4/I");
    t->Branch("phfCoincFilter5",&phfCoincFilter5,"phfCoincFilter5/I");
    t->Branch("pclusterCompatibilityFilter",&pclusterCompatibilityFilter,"pclusterCompatibilityFilter/I");
    t->Branch("superFilterPath",&superFilterPath,"superFilterPath/I");

    t->Branch("pPAprimaryVertexFilter",&pPAprimaryVertexFilter,"pPAprimaryVertexFilter/I");
    t->Branch("pBeamScrapingFilter",&pBeamScrapingFilter,"pBeamScrapingFilter/I");
    t->Branch("pVertexFilterCutG",&pVertexFilterCutG,"pVertexFilterCutG/I");
    t->Branch("pVertexFilterCutGloose",&pVertexFilterCutGloose,"pVertexFilterCutGloose/I");
    t->Branch("pVertexFilterCutGtight",&pVertexFilterCutGtight,"pVertexFilterCutGtight/I");
    t->Branch("pVertexFilterCutGplus",&pVertexFilterCutGplus,"pVertexFilterCutGplus/I");
    t->Branch("pVertexFilterCutE",&pVertexFilterCutE,"pVertexFilterCutE/I");
    t->Branch("pVertexFilterCutEandG",&pVertexFilterCutEandG,"pVertexFilterCutEandG/I");

    t->Branch("collisionEventSelectionAOD",&collisionEventSelectionAOD,"collisionEventSelectionAOD/I");
    t->Branch("collisionEventSelectionAODv2",&collisionEventSelectionAODv2,"collisionEventSelectionAODv2/I");
    t->Branch("phfCoincFilter1Th3",&phfCoincFilter1Th3,"phfCoincFilter1Th3/I");
    t->Branch("phfCoincFilter2Th3",&phfCoincFilter2Th3,"phfCoincFilter2Th3/I");
    t->Branch("phfCoincFilter3Th3",&phfCoincFilter3Th3,"phfCoincFilter3Th3/I");
    t->Branch("phfCoincFilter4Th3",&phfCoincFilter4Th3,"phfCoincFilter4Th3/I");
    t->Branch("phfCoincFilter5Th3",&phfCoincFilter5Th3,"phfCoincFilter5Th3/I");
    t->Branch("phfCoincFilter1Th4",&phfCoincFilter1Th4,"phfCoincFilter1Th4/I");
    t->Branch("phfCoincFilter2Th4",&phfCoincFilter2Th4,"phfCoincFilter2Th4/I");
    t->Branch("phfCoincFilter3Th4",&phfCoincFilter3Th4,"phfCoincFilter3Th4/I");
    t->Branch("phfCoincFilter4Th4",&phfCoincFilter4Th4,"phfCoincFilter4Th4/I");
    t->Branch("phfCoincFilter5Th4",&phfCoincFilter5Th4,"phfCoincFilter5Th4/I");
    t->Branch("phfCoincFilter1Th5",&phfCoincFilter1Th5,"phfCoincFilter1Th5/I");
    t->Branch("phfCoincFilter4Th2",&phfCoincFilter4Th2,"phfCoincFilter4Th2/I");
}

void skimAnalysis::enableBranchesHI(TTree *t)
{
    t->SetBranchStatus("pcollisionEventSelection",1);
}

void skimAnalysis::enableBranchesHI2018(TTree *t)
{
    t->SetBranchStatus("pprimaryVertexFilter",1);
    t->SetBranchStatus("pclusterCompatibilityFilter",1);
    t->SetBranchStatus("phfCoincFilter2Th4",1);
}

void skimAnalysis::enableBranchesPP(TTree *t)
{
    t->SetBranchStatus("pPAprimaryVertexFilter",1);
    t->SetBranchStatus("pBeamScrapingFilter",1);
}

void skimAnalysis::checkBranches(TTree *t)
{
    has_ana_step = t->GetBranch("ana_step");
    has_pcollisionEventSelection = t->GetBranch("pcollisionEventSelection");
    has_pHBHENoiseFilterResultProducer = t->GetBranch("pHBHENoiseFilterResultProducer");
    has_HBHENoiseFilterResult = t->GetBranch("HBHENoiseFilterResult");
    has_HBHENoiseFilterResultRun1 = t->GetBranch("HBHENoiseFilterResultRun1");
    has_HBHENoiseFilterResultRun2Loose = t->GetBranch("HBHENoiseFilterResultRun2Loose");
    has_HBHENoiseFilterResultRun2Tight = t->GetBranch("HBHENoiseFilterResultRun2Tight");
    has_HBHEIsoNoiseFilterResult = t->GetBranch("HBHEIsoNoiseFilterResult");
    has_pprimaryVertexFilter = t->GetBranch("pprimaryVertexFilter");
    has_phfCoincFilter1 = t->GetBranch("phfCoincFilter1");
    has_phfCoincFilter2 = t->GetBranch("phfCoincFilter2");
    has_phfCoincFilter3 = t->GetBranch("phfCoincFilter3");
    has_phfCoincFilter4 = t->GetBranch("phfCoincFilter4");
    has_phfCoincFilter5 = t->GetBranch("phfCoincFilter5");
    has_pclusterCompatibilityFilter = t->GetBranch("pclusterCompatibilityFilter");
    has_superFilterPath = t->GetBranch("superFilterPath");

    has_pPAprimaryVertexFilter = t->GetBranch("pPAprimaryVertexFilter");
    has_pBeamScrapingFilter = t->GetBranch("pBeamScrapingFilter");
    has_pVertexFilterCutG = t->GetBranch("pVertexFilterCutG");
    has_pVertexFilterCutGloose = t->GetBranch("pVertexFilterCutGloose");
    has_pVertexFilterCutGtight = t->GetBranch("pVertexFilterCutGtight");
    has_pVertexFilterCutGplus = t->GetBranch("pVertexFilterCutGplus");
    has_pVertexFilterCutE = t->GetBranch("pVertexFilterCutE");
    has_pVertexFilterCutEandG = t->GetBranch("pVertexFilterCutEandG");

    has_collisionEventSelectionAOD = t->GetBranch("collisionEventSelectionAOD");
    has_collisionEventSelectionAODv2 = t->GetBranch("collisionEventSelectionAODv2");
    has_phfCoincFilter1Th3 = t->GetBranch("phfCoincFilter1Th3");
    has_phfCoincFilter2Th3 = t->GetBranch("phfCoincFilter2Th3");
    has_phfCoincFilter3Th3 = t->GetBranch("phfCoincFilter3Th3");
    has_phfCoincFilter4Th3 = t->GetBranch("phfCoincFilter4Th3");
    has_phfCoincFilter5Th3 = t->GetBranch("phfCoincFilter5Th3");
    has_phfCoincFilter1Th4 = t->GetBranch("phfCoincFilter1Th4");
    has_phfCoincFilter2Th4 = t->GetBranch("phfCoincFilter2Th4");
    has_phfCoincFilter3Th4 = t->GetBranch("phfCoincFilter3Th4");
    has_phfCoincFilter4Th4 = t->GetBranch("phfCoincFilter4Th4");
    has_phfCoincFilter5Th4 = t->GetBranch("phfCoincFilter5Th4");
    has_phfCoincFilter1Th5 = t->GetBranch("phfCoincFilter1Th5");
    has_phfCoincFilter4Th2 = t->GetBranch("phfCoincFilter4Th2");
}

bool skimAnalysis::passedEventSelectionHI()
{
    return (!has_pcollisionEventSelection || pcollisionEventSelection > 0);
}

bool skimAnalysis::passedEventSelectionHI2018()
{
    return ((!has_pprimaryVertexFilter || pprimaryVertexFilter > 0) &&
            (!has_pclusterCompatibilityFilter || pclusterCompatibilityFilter > 0) &&
            (!has_phfCoincFilter2Th4 || phfCoincFilter2Th4 > 0));
}

bool skimAnalysis::passedEventSelectionPP()
{
    return ((!has_pPAprimaryVertexFilter || pPAprimaryVertexFilter > 0) &&
            (!has_pBeamScrapingFilter || pBeamScrapingFilter > 0));
}

#endif
