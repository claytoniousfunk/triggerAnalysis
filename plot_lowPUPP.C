

void configurePad(TPad *pad){

  double leftMargin = 0.15;
  double bottomMargin = 0.15;

  pad->SetLeftMargin(leftMargin);
  pad->SetBottomMargin(bottomMargin);

}

void configureGraph(TGraphAsymmErrors *g){
  
  double labelSize = 0.04;
  double titleSize = 0.05;
  g->SetTitle("");
  g->SetStats(0);
  g->GetYaxis()->SetLabelSize(labelSize);
  g->GetYaxis()->SetTitleSize(titleSize);
  g->GetXaxis()->SetLabelSize(labelSize);
  g->GetXaxis()->SetTitleSize(titleSize);
  g->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  g->GetYaxis()->SetTitle("Trigger Efficiency");
  g->SetMarkerStyle(20);
  g->GetYaxis()->SetRangeUser(0,1.05);
 

}

void configureLatex(TLatex *la){

  double textSize = 0.033;
  
  la->SetTextFont(42);
  la->SetTextSize(textSize);

}

void configureLegend(TLegend *leg){

  double textSize = 0.031;

  leg->SetBorderSize(0);
  leg->SetTextSize(textSize);
  
}

void plot_lowPUPP(){

  TFile *inputFile = TFile::Open("/home/clayton/Analysis/code/triggerAnalysis/rootFiles/triggerAnalysisPrompt_SpecialZeroBias1_398683_2025-11-02.root");

  TString runInfo = "Run 398683 SpecialZeroBias1";
  TString cmsInfo = "#font[62]{CMS} low-PU PPRef #sqrt{s} = 13.6 TeV";
  TLatex *la = new TLatex();
  configureLatex(la);

  TH1D *num_40_ZeroBiasCopy;
  TH1D *num_40_L1Jet20;
  TH1D *num_40_L1Jet24;
  TH1D *num_60;
  TH1D *num_80_L1SingleJet60;
  TH1D *num_110;
  TH1D *num_140;
  TH1D *denom;

  inputFile->GetObject("num_40_ZeroBiasCopy",num_40_ZeroBiasCopy);
  inputFile->GetObject("num_40_L1Jet20",num_40_L1Jet20);
  inputFile->GetObject("num_40_L1Jet24",num_40_L1Jet24);
  inputFile->GetObject("num_60",num_60);
  inputFile->GetObject("num_80_L1SingleJet60",num_80_L1SingleJet60);
  inputFile->GetObject("num_110",num_110);
  inputFile->GetObject("num_140",num_140);
  inputFile->GetObject("denom",denom);

  TGraphAsymmErrors *g_40_ZeroBiasCopy = new TGraphAsymmErrors();
  TGraphAsymmErrors *g_40_L1Jet20 = new TGraphAsymmErrors();
  TGraphAsymmErrors *g_40_L1Jet24 = new TGraphAsymmErrors();
  TGraphAsymmErrors *g_60 = new TGraphAsymmErrors();
  TGraphAsymmErrors *g_80_L1SingleJet60 = new TGraphAsymmErrors();
  TGraphAsymmErrors *g_110 = new TGraphAsymmErrors();
  TGraphAsymmErrors *g_140 = new TGraphAsymmErrors();

  g_40_ZeroBiasCopy->Divide(num_40_ZeroBiasCopy,denom,"cl=0.683 b(1,1) mode");
  g_40_L1Jet20->Divide(num_40_L1Jet20,denom,"cl=0.683 b(1,1) mode");
  g_40_L1Jet24->Divide(num_40_L1Jet24,denom,"cl=0.683 b(1,1) mode");
  g_60->Divide(num_60,denom,"cl=0.683 b(1,1) mode");
  g_80_L1SingleJet60->Divide(num_80_L1SingleJet60,denom,"cl=0.683 b(1,1) mode");
  g_110->Divide(num_110,denom,"cl=0.683 b(1,1) mode");
  g_140->Divide(num_140,denom,"cl=0.683 b(1,1) mode");

  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_40_ZeroBiasCopy = new TCanvas("canv_40_ZeroBiasCopy","canv_40_ZeroBiasCopy",700,700);
  canv_40_ZeroBiasCopy->cd();
  TPad *pad_40_ZeroBiasCopy = new TPad("pad_40_ZeroBiasCopy","pad_40_ZeroBiasCopy",0,0,1,1);
  configurePad(pad_40_ZeroBiasCopy);
  pad_40_ZeroBiasCopy->Draw();
  pad_40_ZeroBiasCopy->cd();
  configureGraph(g_40_ZeroBiasCopy);
  g_40_ZeroBiasCopy->Draw("AP");
  la->DrawLatexNDC(0.16,0.92,cmsInfo.Data());
  la->DrawLatexNDC(0.45,0.38,runInfo.Data());
  TLegend *leg_40_ZeroBiasCopy = new TLegend(0.40,0.3,0.7,0.35);
  configureLegend(leg_40_ZeroBiasCopy);
  leg_40_ZeroBiasCopy->AddEntry(g_40_ZeroBiasCopy,"HLT_PFJet40_ZeroBiasCopy_v1");
  leg_40_ZeroBiasCopy->Draw();

  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_40_L1Jet20 = new TCanvas("canv_40_L1Jet20","canv_40_L1Jet20",700,700);
  canv_40_L1Jet20->cd();
  TPad *pad_40_L1Jet20 = new TPad("pad_40_L1Jet20","pad_40_L1Jet20",0,0,1,1);
  configurePad(pad_40_L1Jet20);
  pad_40_L1Jet20->Draw();
  pad_40_L1Jet20->cd();
  configureGraph(g_40_L1Jet20);
  g_40_L1Jet20->Draw("AP");
  la->DrawLatexNDC(0.16,0.92,cmsInfo.Data());
  la->DrawLatexNDC(0.45,0.38,runInfo.Data());
  TLegend *leg_40_L1Jet20 = new TLegend(0.40,0.3,0.7,0.35);
  configureLegend(leg_40_L1Jet20);
  leg_40_L1Jet20->AddEntry(g_40_L1Jet20,"HLT_PFJet40_L1Jet20_v1");
  leg_40_L1Jet20->Draw();

  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_40_L1Jet24 = new TCanvas("canv_40_L1Jet24","canv_40_L1Jet24",700,700);
  canv_40_L1Jet24->cd();
  TPad *pad_40_L1Jet24 = new TPad("pad_40_L1Jet24","pad_40_L1Jet24",0,0,1,1);
  configurePad(pad_40_L1Jet24);
  pad_40_L1Jet24->Draw();
  pad_40_L1Jet24->cd();
  configureGraph(g_40_L1Jet24);
  g_40_L1Jet24->Draw("AP");
  la->DrawLatexNDC(0.16,0.92,cmsInfo.Data());
  la->DrawLatexNDC(0.45,0.38,runInfo.Data());
  TLegend *leg_40_L1Jet24 = new TLegend(0.40,0.3,0.7,0.35);
  configureLegend(leg_40_L1Jet24);
  leg_40_L1Jet24->AddEntry(g_40_L1Jet24,"HLT_PFJet40_L1Jet24_v1");
  leg_40_L1Jet24->Draw();

  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_60 = new TCanvas("canv_60","canv_60",700,700);
  canv_60->cd();
  TPad *pad_60 = new TPad("pad_60","pad_60",0,0,1,1);
  configurePad(pad_60);
  pad_60->Draw();
  pad_60->cd();
  configureGraph(g_60);
  g_60->Draw("AP");
  la->DrawLatexNDC(0.16,0.92,cmsInfo.Data());
  la->DrawLatexNDC(0.45,0.38,runInfo.Data());
  TLegend *leg_60 = new TLegend(0.40,0.3,0.7,0.35);
  configureLegend(leg_60);
  leg_60->AddEntry(g_60,"HLT_PFJet60_v1");
  leg_60->Draw();

  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_80_L1SingleJet60 = new TCanvas("canv_80_L1SingleJet60","canv_80_L1SingleJet60",700,700);
  canv_80_L1SingleJet60->cd();
  TPad *pad_80_L1SingleJet60 = new TPad("pad_80_L1SingleJet60","pad_80_L1SingleJet60",0,0,1,1);
  configurePad(pad_80_L1SingleJet60);
  pad_80_L1SingleJet60->Draw();
  pad_80_L1SingleJet60->cd();
  configureGraph(g_80_L1SingleJet60);
  g_80_L1SingleJet60->Draw("AP");
  la->DrawLatexNDC(0.16,0.92,cmsInfo.Data());
  la->DrawLatexNDC(0.45,0.38,runInfo.Data());
  TLegend *leg_80_L1SingleJet60 = new TLegend(0.40,0.3,0.7,0.35);
  configureLegend(leg_80_L1SingleJet60);
  leg_80_L1SingleJet60->AddEntry(g_80_L1SingleJet60,"HLT_PFJet80_L1SingleJet60_v1");
  leg_80_L1SingleJet60->Draw();

  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_110 = new TCanvas("canv_110","canv_110",700,700);
  canv_110->cd();
  TPad *pad_110 = new TPad("pad_110","pad_110",0,0,1,1);
  configurePad(pad_110);
  pad_110->Draw();
  pad_110->cd();
  configureGraph(g_110);
  g_110->Draw("AP");
  la->DrawLatexNDC(0.16,0.92,cmsInfo.Data());
  la->DrawLatexNDC(0.48,0.38,runInfo.Data());
  TLegend *leg_110 = new TLegend(0.48,0.3,0.7,0.35);
  configureLegend(leg_110);
  leg_110->AddEntry(g_110,"HLT_PFJet110_v1");
  leg_110->Draw();

  /////////////////////////////////////////////////////////////////////////////////////////////////
  
  TCanvas *canv_140 = new TCanvas("canv_140","canv_140",700,700);
  canv_140->cd();
  TPad *pad_140 = new TPad("pad_140","pad_140",0,0,1,1);
  configurePad(pad_140);
  pad_140->Draw();
  pad_140->cd();
  configureGraph(g_140);
  g_140->Draw("AP");
  la->DrawLatexNDC(0.16,0.92,cmsInfo.Data());
  la->DrawLatexNDC(0.48,0.38,runInfo.Data());
  TLegend *leg_140 = new TLegend(0.48,0.3,0.7,0.35);
  configureLegend(leg_140);
  leg_140->AddEntry(g_140,"HLT_PFJet140_v1");
  leg_140->Draw();


  ///////////////////////////////////////////////

  canv_40_ZeroBiasCopy->SaveAs("./figures/lowPUPP/398683/HLT_PFJet40_ZeroBiasCopy.pdf");
  canv_40_L1Jet20->SaveAs("./figures/lowPUPP/398683/HLT_PFJet40_L1Jet20.pdf");
  canv_40_L1Jet24->SaveAs("./figures/lowPUPP/398683/HLT_PFJet40_L1Jet24.pdf");
  canv_60->SaveAs("./figures/lowPUPP/398683/HLT_PFJet60.pdf");
  canv_80_L1SingleJet60->SaveAs("./figures/lowPUPP/398683/HLT_PFJet80_L1SingleJet60.pdf");
  canv_110->SaveAs("./figures/lowPUPP/398683/HLT_PFJet110.pdf");
  canv_140->SaveAs("./figures/lowPUPP/398683/HLT_PFJet140.pdf");
  

}
