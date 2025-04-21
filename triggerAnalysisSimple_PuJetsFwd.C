using namespace std;

Float_t ptMin = 0.;
Float_t ptMax = 300.;
Int_t Nbins = 60;

TH1D *denom = new TH1D("denom","denom",Nbins,ptMin,ptMax);

TH1D *num_40 = new TH1D("num_40","num_40",Nbins,ptMin,ptMax);
TH1D *r_40 = new TH1D("r_40","r_40",Nbins,ptMin,ptMax);

TH1D *num_60 = new TH1D("num_60","num_60",Nbins,ptMin,ptMax);
TH1D *r_60 = new TH1D("r_60","r_60",Nbins,ptMin,ptMax);

TH1D *num_80 = new TH1D("num_80","num_80",Nbins,ptMin,ptMax);
TH1D *r_80 = new TH1D("r_80","r_80",Nbins,ptMin,ptMax);

TH1D *num_100 = new TH1D("num_100","num_100",Nbins,ptMin,ptMax);
TH1D *r_100 = new TH1D("r_100","r_100",Nbins,ptMin,ptMax);

TH1D *num_120 = new TH1D("num_120","num_120",Nbins,ptMin,ptMax);
TH1D *r_120 = new TH1D("r_120","r_120",Nbins,ptMin,ptMax);



std::map<unsigned long long, int> runLumiEvtToEntryMap;



unsigned long long keyFromRunLumiEvent(Int_t run,
				       Int_t lumi,
				       ULong64_t event);


float findNcoll(int hiBin) {
   const int nbins = 200;
   const float Ncoll[nbins] = {1976.95, 1944.02, 1927.29, 1891.9, 1845.3, 1807.2, 1760.45, 1729.18, 1674.8, 1630.3, 1590.52, 1561.72, 1516.1, 1486.5, 1444.68, 1410.88, 1376.4, 1347.32, 1309.71, 1279.98, 1255.31, 1219.89, 1195.13, 1165.96, 1138.92, 1113.37, 1082.26, 1062.42, 1030.6, 1009.96, 980.229, 955.443, 936.501, 915.97, 892.063, 871.289, 847.364, 825.127, 806.584, 789.163, 765.42, 751.187, 733.001, 708.31, 690.972, 677.711, 660.682, 640.431, 623.839, 607.456, 593.307, 576.364, 560.967, 548.909, 530.475, 519.575, 505.105, 490.027, 478.133, 462.372, 451.115, 442.642, 425.76, 416.364, 405.154, 392.688, 380.565, 371.167, 360.28, 348.239, 340.587, 328.746, 320.268, 311.752, 300.742, 292.172, 281.361, 274.249, 267.025, 258.625, 249.931, 240.497, 235.423, 228.63, 219.854, 214.004, 205.425, 199.114, 193.618, 185.644, 180.923, 174.289, 169.641, 161.016, 157.398, 152.151, 147.425, 140.933, 135.924, 132.365, 127.017, 122.127, 117.817, 113.076, 109.055, 105.16, 101.323, 98.098, 95.0548, 90.729, 87.6495, 84.0899, 80.2237, 77.2201, 74.8848, 71.3554, 68.7745, 65.9911, 63.4136, 61.3859, 58.1903, 56.4155, 53.8486, 52.0196, 49.2921, 47.0735, 45.4345, 43.8434, 41.7181, 39.8988, 38.2262, 36.4435, 34.8984, 33.4664, 31.8056, 30.351, 29.2074, 27.6924, 26.7754, 25.4965, 24.2802, 22.9651, 22.0059, 21.0915, 19.9129, 19.1041, 18.1487, 17.3218, 16.5957, 15.5323, 14.8035, 14.2514, 13.3782, 12.8667, 12.2891, 11.61, 11.0026, 10.3747, 9.90294, 9.42648, 8.85324, 8.50121, 7.89834, 7.65197, 7.22768, 6.7755, 6.34855, 5.98336, 5.76555, 5.38056, 5.11024, 4.7748, 4.59117, 4.23247, 4.00814, 3.79607, 3.68702, 3.3767, 3.16309, 2.98282, 2.8095, 2.65875, 2.50561, 2.32516, 2.16357, 2.03235, 1.84061, 1.72628, 1.62305, 1.48916, 1.38784, 1.28366, 1.24693, 1.18552, 1.16085, 1.12596, 1.09298, 1.07402, 1.06105, 1.02954};
   return Ncoll[hiBin];
}


void triggerAnalysisSimple_PuJetsFwd(std::string triggerFile = "openHLTFiles_21Sep22.root",
                           std::string inputFile = "HiForestMiniAOD_CB_merge.root",
                           std::string outputFile = "rootFiles/out_PuJetsFwd.root"){


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
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet40Fwd_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet60Fwd_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet80Fwd_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet100Fwd_v", 1);
    treeTrig->SetBranchStatus("HLT_HIPuAK4CaloJet120Fwd_v", 1);

    //Int_t hlt_event;
    ULong64_t       hlt_event;
    Int_t           hlt_lumi;
    Int_t           hlt_run;
    Bool_t          triggerDecision_40;
    Bool_t          triggerDecision_60;
    Bool_t          triggerDecision_80;
    Bool_t          triggerDecision_100;
    Bool_t          triggerDecision_120;
    std::cout << "Setting Event, lumi, and run branchAdresses...";
    treeTrig->SetBranchAddress("Event", &hlt_event);
    treeTrig->SetBranchAddress("LumiBlock", &hlt_lumi);
    treeTrig->SetBranchAddress("Run", &hlt_run);
    treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet40Fwd_v",&triggerDecision_40);
    treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet60Fwd_v",&triggerDecision_60);
    treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet80Fwd_v",&triggerDecision_80);
    treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet100Fwd_v",&triggerDecision_100);
    treeTrig->SetBranchAddress("HLT_HIPuAK4CaloJet120Fwd_v",&triggerDecision_120);
    std::cout << "done" << std::endl;


    std::cout << "get number of entries from HLT file..." << std::endl;

    Long64_t entriesHLT = treeTrig->GetEntries();
    std::cout << "HLT entries = " << entriesHLT << std::endl;
    
    
    
    
    std::cout << "get number of entries from reco file.." << std::endl;
    // read the first file only to get the HiForest info
    std::string inputPath = inputFile.c_str();
    fileTmp = TFile::Open(inputPath.c_str(), "READ");
    fileTmp->cd();


    std::string treePath = "ggHiNtuplizer/EventTree";

    // read one tree only to get the number of entries
    treeggHiNtuplizer = (TTree*)fileTmp->Get(treePath.c_str());
    Long64_t entriesTmp = treeggHiNtuplizer->GetEntries();
    std::cout << "reco entries = " << entriesTmp << std::endl;
 //   treeggHiNtuplizer->Delete();

 //   treeggHiNtuplizer = (TTree*)fileTmp->Get(treePath.c_str());
    treeggHiNtuplizer->SetBranchStatus("*",0);     // disable all branches
    
    std::map<unsigned long long, int> runLumiEvtToEntryMap;
    
    treeJet = (TTree*)fileTmp->Get("akCs4PFJetAnalyzer/t");
    treeJet->SetBranchStatus("*",0);     // disable all branches
    treeJet->SetBranchStatus("jtpt",1);   // enable event information
    treeJet->SetBranchStatus("jteta",1);
    treeJet->SetBranchStatus("nref",1);
    treeJet->SetBranchStatus("calopt",1);   // enable event information
    treeJet->SetBranchStatus("caloeta",1);
    treeJet->SetBranchStatus("ncalo",1);

    const unsigned int maxJets = 10000;
    
    Float_t jtpt[maxJets];
    Float_t jteta[maxJets];
    Int_t nref;

    treeJet->SetBranchAddress("calopt",&jtpt);
    treeJet->SetBranchAddress("caloeta",&jteta);
    treeJet->SetBranchAddress("ncalo",&nref);
    
    
    treeHiEvt = (TTree*)fileTmp->Get("hiEvtAnalyzer/HiTree");
    treeHiEvt->SetBranchStatus("*",0);     // disable all branches
    treeHiEvt->SetBranchStatus("run",1);   // enable event information
    treeHiEvt->SetBranchStatus("evt",1);
    treeHiEvt->SetBranchStatus("lumi",1);
    treeHiEvt->SetBranchStatus("vz",1);
    treeHiEvt->SetBranchStatus("hiBin",1);
    treeHiEvt->SetBranchStatus("weight",1);
    treeHiEvt->SetBranchStatus("pthat",1);

    Float_t vz;
    Int_t hiBin;
    UInt_t run;
    UInt_t lumi;
    ULong64_t evt;
    Float_t weight;
    Float_t pthat;

    treeHiEvt->SetBranchAddress("vz",&vz);
    treeHiEvt->SetBranchAddress("hiBin",&hiBin);
    treeHiEvt->SetBranchAddress("run",&run);
    treeHiEvt->SetBranchAddress("lumi",&lumi);
    treeHiEvt->SetBranchAddress("evt",&evt);
    treeHiEvt->SetBranchAddress("weight",&weight);
    treeHiEvt->SetBranchAddress("pthat",&pthat);






    // loop through HLT and create a key for each event

    for(Long64_t i_entry = 0; i_entry < entriesHLT; i_entry++){

       treeTrig->GetEntry(i_entry);
       unsigned long long key = keyFromRunLumiEvent(hlt_run, hlt_lumi, hlt_event);
       runLumiEvtToEntryMap[key] = i_entry;

    }




    // loop through reco objects
    for (Long64_t j_entry = 0; j_entry < entriesTmp; ++j_entry){

        treeggHiNtuplizer->GetEntry(j_entry);
        treeHiEvt->GetEntry(j_entry);
        treeJet->GetEntry(j_entry);
    
	//if(pthat < 30) continue;
	// event cuts
 	if(fabs(vz)>15.0) continue;
        if(hiBin>180) continue;	
	
	double weight_Ncoll = findNcoll(hiBin);

	weight *= weight_Ncoll;

        
        auto j_entry_status = treeJet->GetEntry(j_entry);
        
        if(j_entry_status < 0) {
            std::cout << Form("bad entry %lld in jet tree",j_entry) << std::endl;
            continue;
        }
	
        unsigned long long key = keyFromRunLumiEvent(run,lumi,evt);

        long long i_entry = -1;
        
        if(runLumiEvtToEntryMap.count(key) == 0) continue; // skip reco event if there is no HLT event match
        else i_entry = runLumiEvtToEntryMap.at(key);

        //std::cout << "i_entry = " << i_entry << std::endl;
        
        // now fill the denominator
        Float_t maxPt_denom = 0;
        Float_t maxEta_denom = 0;
        
        for(Int_t i_jet = 0; i_jet < nref; i_jet++){

	   	    
            if(jtpt[i_jet] > maxPt_denom) { // find the leading jetPt in the event, regardless of trigger.
                maxPt_denom = jtpt[i_jet];
                maxEta_denom = jteta[i_jet];
            }


	    }

        if(pthat < 0.35 * maxPt_denom) continue; // pthat filtering
	
	if(fabs(maxEta_denom)>4.7 || fabs(maxEta_denom)<3.2) continue; // skip event if the leading jet is outside eta range

	    if(maxPt_denom > 0) {
            
            denom->Fill(maxPt_denom,weight);
            //std::cout << "maxPt = " << maxPt_denom <<std::endl;
        }





        treeTrig->GetEntry(i_entry); // get trigger decision from HLT emulation

        
        
        if(triggerDecision_40) {// only fill the numerator if the trigger is on.

            Float_t maxPt_num = 0;
            
            // now fill the numerator
            for(Int_t i_jet = 0; i_jet < nref; i_jet++){

                // no eta cut needed since already applied after the first jet loop.  

                if(jtpt[i_jet] > maxPt_num) { // find the leading jetPt in events with trigger on.
                    maxPt_num = jtpt[i_jet];
                }


            }

            if(maxPt_num > 0){

                num_40->Fill(maxPt_num,weight);
                //std::cout << "maxPt_num = " << maxPt_num << std::endl <<  std::endl;
            } 

        }

        
        
        if(triggerDecision_60) {// only fill the numerator if the trigger is on.

            Float_t maxPt_num = 0;
            
            // now fill the numerator
            for(Int_t i_jet = 0; i_jet < nref; i_jet++){

                // no eta cut needed since already applied after the first jet loop.  

                if(jtpt[i_jet] > maxPt_num) { // find the leading jetPt in events with trigger on.
                    maxPt_num = jtpt[i_jet];
                }


            }

            if(maxPt_num > 0){

                num_60->Fill(maxPt_num,weight);
                //std::cout << "maxPt_num = " << maxPt_num << std::endl <<  std::endl;
            } 

        }

        if(triggerDecision_80) {// only fill the numerator if the trigger is on.

            Float_t maxPt_num = 0;
            
            // now fill the numerator
            for(Int_t i_jet = 0; i_jet < nref; i_jet++){

                // no eta cut needed since already applied after the first jet loop.  

                if(jtpt[i_jet] > maxPt_num) { // find the leading jetPt in events with trigger on.
                    maxPt_num = jtpt[i_jet];
                }


            }

            if(maxPt_num > 0){

                num_80->Fill(maxPt_num,weight);
                //std::cout << "maxPt_num = " << maxPt_num << std::endl <<  std::endl;
            } 

        }

        if(triggerDecision_100) {// only fill the numerator if the trigger is on.

            Float_t maxPt_num = 0;
            
            // now fill the numerator
            for(Int_t i_jet = 0; i_jet < nref; i_jet++){

                // no eta cut needed since already applied after the first jet loop.  

                if(jtpt[i_jet] > maxPt_num) { // find the leading jetPt in events with trigger on.
                    maxPt_num = jtpt[i_jet];
                }


            }

            if(maxPt_num > 0){

                num_100->Fill(maxPt_num,weight);
                //std::cout << "maxPt_num = " << maxPt_num << std::endl <<  std::endl;
            } 

        }

        if(triggerDecision_120) {// only fill the numerator if the trigger is on.

            Float_t maxPt_num = 0;
            
            // now fill the numerator
            for(Int_t i_jet = 0; i_jet < nref; i_jet++){

                // no eta cut needed since already applied after the first jet loop.  

                if(jtpt[i_jet] > maxPt_num) { // find the leading jetPt in events with trigger on.
                    maxPt_num = jtpt[i_jet];
                }


            }

            if(maxPt_num > 0){

                num_120->Fill(maxPt_num,weight);
                //std::cout << "maxPt_num = " << maxPt_num << std::endl <<  std::endl;
            } 

        }




    }

    r_40->Divide(num_40,denom,1,1,"B");
    r_60->Divide(num_60,denom,1,1,"B");
    r_80->Divide(num_80,denom,1,1,"B");
    r_100->Divide(num_100,denom,1,1,"B");
    r_120->Divide(num_120,denom,1,1,"B");

    r_40->SetLineColor(kRed);
    r_60->SetLineColor(kBlue);
    r_80->SetLineColor(kGreen);
    r_100->SetLineColor(kMagenta);
    r_120->SetLineColor(kCyan+2);

    r_40->SetMarkerColor(kRed);
    r_60->SetMarkerColor(kBlue);
    r_80->SetMarkerColor(kGreen);
    r_100->SetMarkerColor(kMagenta);
    r_120->SetMarkerColor(kCyan+2);

    r_40->SetMarkerStyle(24);
    r_60->SetMarkerStyle(25);
    r_80->SetMarkerStyle(26);
    r_100->SetMarkerStyle(32);
    r_120->SetMarkerStyle(28);

    TCanvas *c1 = new TCanvas("c1","c1",700,600);
    c1->cd();
    TPad *p1 = new TPad("p1","p1",0,0,1,1);
    p1->SetLeftMargin(0.13);
    p1->SetBottomMargin(0.14);
    p1->Draw();
    p1->cd();
    r_40->SetTitle("");
    r_40->SetStats(0);
    r_40->GetXaxis()->SetTitleSize(0.05);
    r_40->GetYaxis()->SetTitleSize(0.05);
    r_40->GetXaxis()->SetTitle("leading caloJet #font[52]{p}_{T} [GeV]");
    r_40->GetYaxis()->SetTitle("Trigger efficiency");
    r_40->GetYaxis()->SetRangeUser(0.4,1.25);
    TLegend *leg = new TLegend(0.48,0.72,0.88,0.88);
    leg->AddEntry(r_40,"HLT_HIPuAK4CaloJet40Fwd_v","p");
    leg->AddEntry(r_60,"HLT_HIPuAK4CaloJet60Fwd_v","p");
    leg->AddEntry(r_80,"HLT_HIPuAK4CaloJet80Fwd_v","p");
    leg->AddEntry(r_100,"HLT_HIPuAK4CaloJet100Fwd_v","p");
    leg->AddEntry(r_120,"HLT_HIPuAK4CaloJet120Fwd_v","p");
    leg->SetTextSize(0.028);
    leg->SetBorderSize(0);
    r_40->Draw();
    leg->Draw();
    r_60->Draw("same");
    r_80->Draw("same");
    r_100->Draw("same");
    r_120->Draw("same");




    TF1 *fit_40 = new TF1("fit_40","0.5+0.5*tanh([0]*(x - [1]))",0,500);
    fit_40->SetParameter(0,1.8e-01);
    fit_40->SetParameter(1,40);
    fit_40->SetLineStyle(7);
    fit_40->SetLineColor(kRed);

    TF1 *fit_60 = new TF1("fit_60","0.5+0.5*tanh([0]*(x - [1]))",0,500);
    fit_60->SetParameter(0,7.04514e-02);
    fit_60->SetLineStyle(7);
    fit_60->SetLineColor(kBlue);

    TF1 *fit_80 = new TF1("fit_80","0.5+0.5*tanh([0]*(x - [1]))",0,500);
    fit_80->SetLineStyle(7);
    fit_80->SetLineColor(kGreen);

    TF1 *fit_100 = new TF1("fit_100","0.5+0.5*tanh([0]*(x - [1]))",0,500);
    fit_100->SetLineStyle(7);
    fit_100->SetLineColor(kMagenta);

    TF1 *fit_120 = new TF1("fit_120","0.5+0.5*tanh([0]*(x - [1]))",0,500);
    fit_120->SetParameter(0,7.04514e-02);
    fit_120->SetParameter(1,120);
    fit_120->SetLineStyle(7);
    fit_120->SetLineColor(kCyan+2);

    r_40->Fit("fit_40","R N");
    r_60->Fit("fit_60","R N");
    r_80->Fit("fit_80","R N");
    r_100->Fit("fit_100","R N");
    r_120->Fit("fit_120","R N");


     // fit_40->Draw("same");
     // fit_60->Draw("same");
     // fit_80->Draw("same");
     // fit_100->Draw("same");
     // fit_120->Draw("same");














    TLatex *la = new TLatex();
    la->SetTextFont(42);
    la->SetTextSize(0.03);

    la->DrawLatexNDC(0.18,0.85,"PYTHIA+HYDJET 0-10%");
    la->DrawLatexNDC(0.18,0.79,"Run 3 MC");
    la->DrawLatexNDC(0.18,0.73,"3.2 < |#eta^{jet}| < 4.7");

 


    auto wf = TFile::Open("rootFiles/out_PuJetsFwd.root","recreate");

        denom->Write();
        
        num_40->Write();
        num_60->Write();
        num_80->Write();
        num_100->Write();
        num_120->Write();

        r_40->Write();
        r_60->Write();
        r_80->Write();
        r_100->Write();
        r_120->Write();

    wf->Close();



}


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
