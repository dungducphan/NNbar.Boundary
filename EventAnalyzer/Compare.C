#include "Style.C"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TFile.h"

/*
void Compare() {
    GeneralStyle();

    std::string CosmicFile = "./NNbar-Boundary-Cosmic.root";
    std::string SignalFile = "./NNbar-Boundary-Signal.root";

    TFile *fCosmic = (TFile*) gROOT->GetListOfFiles()->FindObject(CosmicFile.c_str());
    if (!fCosmic || !fCosmic->IsOpen()) {
        fCosmic = new TFile(CosmicFile.c_str());
    }
    TTree *tCosmic = (TTree*) fCosmic->Get("NNBarBoundary");

    TFile *fSignal = (TFile*) gROOT->GetListOfFiles()->FindObject(SignalFile.c_str());
    if (!fSignal || !fSignal->IsOpen()) {
        fSignal = new TFile(SignalFile.c_str());
    }
    TTree *tSignal = (TTree*) fSignal->Get("NNBarBoundary");

    double cosmic_convexHullAreaXV;
    double cosmic_convexHullAreaYV;
    double cosmic_minimalEnclosingCircleAreaXV;
    double cosmic_minimalEnclosingCircleAreaYV;
    double cosmic_areaRatioXV;
    double cosmic_areaRatioYV;
    double cosmic_averageYposition;
    bool   cosmic_isCosmic;

    double signal_convexHullAreaXV;
    double signal_convexHullAreaYV;
    double signal_minimalEnclosingCircleAreaXV;
    double signal_minimalEnclosingCircleAreaYV;
    double signal_areaRatioXV;
    double signal_areaRatioYV;
    double signal_averageYposition;
    bool   signal_isCosmic;

    TBranch *b_cosmic_convexHullAreaXV;
    TBranch *b_cosmic_convexHullAreaYV;
    TBranch *b_cosmic_minimalEnclosingCircleAreaXV;
    TBranch *b_cosmic_minimalEnclosingCircleAreaYV;
    TBranch *b_cosmic_areaRatioXV;
    TBranch *b_cosmic_areaRatioYV;
    TBranch *b_cosmic_averageYposition;
    TBranch *b_cosmic_isCosmic;

    TBranch *b_signal_convexHullAreaXV;
    TBranch *b_signal_convexHullAreaYV;
    TBranch *b_signal_minimalEnclosingCircleAreaXV;
    TBranch *b_signal_minimalEnclosingCircleAreaYV;
    TBranch *b_signal_areaRatioXV;
    TBranch *b_signal_areaRatioYV;
    TBranch *b_signal_averageYposition;
    TBranch *b_signal_isCosmic;

    tCosmic->SetBranchAddress("convexHullAreaXV", &cosmic_convexHullAreaXV, &b_cosmic_convexHullAreaXV);
    tCosmic->SetBranchAddress("convexHullAreaYV", &cosmic_convexHullAreaYV, &b_cosmic_convexHullAreaYV);
    tCosmic->SetBranchAddress("minimalEnclosingCircleAreaXV", &cosmic_minimalEnclosingCircleAreaXV, &b_cosmic_minimalEnclosingCircleAreaXV);
    tCosmic->SetBranchAddress("minimalEnclosingCircleAreaYV", &cosmic_minimalEnclosingCircleAreaYV, &b_cosmic_minimalEnclosingCircleAreaYV);
    tCosmic->SetBranchAddress("areaRatioXV", &cosmic_areaRatioXV, &b_cosmic_areaRatioXV);
    tCosmic->SetBranchAddress("areaRatioYV", &cosmic_areaRatioYV, &b_cosmic_areaRatioYV);
    tCosmic->SetBranchAddress("averageYposition", &cosmic_averageYposition, &b_cosmic_averageYposition);
    tCosmic->SetBranchAddress("isCosmic", &cosmic_isCosmic, &b_cosmic_isCosmic);

    tSignal->SetBranchAddress("convexHullAreaXV", &signal_convexHullAreaXV, &b_signal_convexHullAreaXV);
    tSignal->SetBranchAddress("convexHullAreaYV", &signal_convexHullAreaYV, &b_signal_convexHullAreaYV);
    tSignal->SetBranchAddress("minimalEnclosingCircleAreaXV", &signal_minimalEnclosingCircleAreaXV, &b_signal_minimalEnclosingCircleAreaXV);
    tSignal->SetBranchAddress("minimalEnclosingCircleAreaYV", &signal_minimalEnclosingCircleAreaYV, &b_signal_minimalEnclosingCircleAreaYV);
    tSignal->SetBranchAddress("areaRatioXV", &signal_areaRatioXV, &b_signal_areaRatioXV);
    tSignal->SetBranchAddress("areaRatioYV", &signal_areaRatioYV, &b_signal_areaRatioYV);
    tSignal->SetBranchAddress("averageYposition", &signal_averageYposition, &b_signal_averageYposition);
    tSignal->SetBranchAddress("isCosmic", &signal_isCosmic, &b_signal_isCosmic);

    TH1D* cosmic_areaRatioTH1HistXview = new TH1D("cosmic_areaRatioTH1HistXview", "X View; Area Ratio; ", 50, 0, 1.);
    TH1D* cosmic_areaRatioTH1HistYview = new TH1D("cosmic_areaRatioTH1HistYview", "Y View; Area Ratio; ", 50, 0, 1.);
    for (int i = 0; i < tCosmic->GetEntries(); i++) {
        tCosmic->GetEntry(i);
        if ((cosmic_convexHullAreaXV != 0.) && (cosmic_convexHullAreaYV != 0.)) {
            cosmic_areaRatioTH1HistXview->Fill(cosmic_convexHullAreaXV/cosmic_minimalEnclosingCircleAreaXV);
            cosmic_areaRatioTH1HistYview->Fill(cosmic_convexHullAreaYV/cosmic_minimalEnclosingCircleAreaYV);
        }
    }

    TH1D* signal_areaRatioTH1HistXview = new TH1D("signal_areaRatioTH1HistXview", "X View; Area Ratio; ", 50, 0, 1.);
    TH1D* signal_areaRatioTH1HistYview = new TH1D("signal_areaRatioTH1HistYview", "Y View; Area Ratio; ", 50, 0, 1.);
    for (int i = 0; i < tSignal->GetEntries(); i++) {
        tSignal->GetEntry(i);
        if ((signal_convexHullAreaXV != 0.) && (signal_convexHullAreaYV != 0.)) {
            signal_areaRatioTH1HistXview->Fill(signal_convexHullAreaXV/signal_minimalEnclosingCircleAreaXV);
            signal_areaRatioTH1HistYview->Fill(signal_convexHullAreaYV/signal_minimalEnclosingCircleAreaYV);
        }
    }

    double maxValue_cosmicX = cosmic_areaRatioTH1HistXview->GetMaximum();
    int maxBin_cosmicX = cosmic_areaRatioTH1HistXview->GetMaximumBin();
    for (int i = 0; i < cosmic_areaRatioTH1HistXview->GetSize(); i++) {
        double currentVal = cosmic_areaRatioTH1HistXview->GetBinContent(i);
        cosmic_areaRatioTH1HistXview->SetBinContent(i, currentVal/maxValue_cosmicX);
    }

    double maxValue_cosmicY = cosmic_areaRatioTH1HistYview->GetMaximum();
    int maxBin_cosmicY = cosmic_areaRatioTH1HistYview->GetMaximumBin();
    for (int i = 0; i < cosmic_areaRatioTH1HistYview->GetSize(); i++) {
        double currentVal = cosmic_areaRatioTH1HistYview->GetBinContent(i);
        cosmic_areaRatioTH1HistYview->SetBinContent(i, currentVal/maxValue_cosmicY);
    }

    double maxValue_signalX = signal_areaRatioTH1HistXview->GetMaximum();
    int maxBin_signalX = signal_areaRatioTH1HistXview->GetMaximumBin();
    for (int i = 0; i < signal_areaRatioTH1HistXview->GetSize(); i++) {
        double currentVal = signal_areaRatioTH1HistXview->GetBinContent(i);
        signal_areaRatioTH1HistXview->SetBinContent(i, currentVal/maxValue_signalX);
    }

    double maxValue_signalY = signal_areaRatioTH1HistYview->GetMaximum();
    int maxBin_signalY = signal_areaRatioTH1HistYview->GetMaximumBin();
    for (int i = 0; i < signal_areaRatioTH1HistYview->GetSize(); i++) {
        double currentVal = signal_areaRatioTH1HistYview->GetBinContent(i);
        signal_areaRatioTH1HistYview->SetBinContent(i, currentVal/maxValue_signalY);
    }

    TCanvas* c1 = new TCanvas("c1", "c1", 1200, 600);
    StyleLinearLinear(c1);
    c1->cd();
    c1->Divide(2,1);
    c1->cd(1);
    cosmic_areaRatioTH1HistXview->GetXaxis()->CenterTitle();
    cosmic_areaRatioTH1HistXview->Draw();
    signal_areaRatioTH1HistXview->SetLineColor(kRed);
    signal_areaRatioTH1HistXview->Draw("SAME");
    gPad->SetRightMargin(0.15);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    gPad->SetTopMargin(0.15);
    c1->cd(2);
    cosmic_areaRatioTH1HistYview->GetXaxis()->CenterTitle();
    cosmic_areaRatioTH1HistYview->Draw();
    signal_areaRatioTH1HistYview->SetLineColor(kRed);
    signal_areaRatioTH1HistYview->Draw("SAME");
    gPad->SetRightMargin(0.15);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    gPad->SetTopMargin(0.15);
    c1->SetFixedAspectRatio();
    c1->SaveAs("CircularDegreeCompare.pdf");
}
*/

void Compare() {
    GeneralStyle();

    std::string CosmicFile = "./NNbar-Boundary-Cosmic.root";
    std::string SignalFile = "./NNbar-Boundary-Signal.root";

    TFile *fCosmic = (TFile*) gROOT->GetListOfFiles()->FindObject(CosmicFile.c_str());
    if (!fCosmic || !fCosmic->IsOpen()) {
        fCosmic = new TFile(CosmicFile.c_str());
    }
    TTree *tCosmic = (TTree*) fCosmic->Get("NNBarBoundary");

    TFile *fSignal = (TFile*) gROOT->GetListOfFiles()->FindObject(SignalFile.c_str());
    if (!fSignal || !fSignal->IsOpen()) {
        fSignal = new TFile(SignalFile.c_str());
    }
    TTree *tSignal = (TTree*) fSignal->Get("NNBarBoundary");

    double cosmic_convexHullAreaXV;
    double cosmic_convexHullAreaYV;
    double cosmic_minimalEnclosingCircleAreaXV;
    double cosmic_minimalEnclosingCircleAreaYV;
    double cosmic_areaRatioXV;
    double cosmic_areaRatioYV;
    double cosmic_averageYposition;
    bool   cosmic_isCosmic;

    double signal_convexHullAreaXV;
    double signal_convexHullAreaYV;
    double signal_minimalEnclosingCircleAreaXV;
    double signal_minimalEnclosingCircleAreaYV;
    double signal_areaRatioXV;
    double signal_areaRatioYV;
    double signal_averageYposition;
    bool   signal_isCosmic;

    TBranch *b_cosmic_convexHullAreaXV;
    TBranch *b_cosmic_convexHullAreaYV;
    TBranch *b_cosmic_minimalEnclosingCircleAreaXV;
    TBranch *b_cosmic_minimalEnclosingCircleAreaYV;
    TBranch *b_cosmic_areaRatioXV;
    TBranch *b_cosmic_areaRatioYV;
    TBranch *b_cosmic_averageYposition;
    TBranch *b_cosmic_isCosmic;

    TBranch *b_signal_convexHullAreaXV;
    TBranch *b_signal_convexHullAreaYV;
    TBranch *b_signal_minimalEnclosingCircleAreaXV;
    TBranch *b_signal_minimalEnclosingCircleAreaYV;
    TBranch *b_signal_areaRatioXV;
    TBranch *b_signal_areaRatioYV;
    TBranch *b_signal_averageYposition;
    TBranch *b_signal_isCosmic;

    tCosmic->SetBranchAddress("convexHullAreaXV", &cosmic_convexHullAreaXV, &b_cosmic_convexHullAreaXV);
    tCosmic->SetBranchAddress("convexHullAreaYV", &cosmic_convexHullAreaYV, &b_cosmic_convexHullAreaYV);
    tCosmic->SetBranchAddress("minimalEnclosingCircleAreaXV", &cosmic_minimalEnclosingCircleAreaXV, &b_cosmic_minimalEnclosingCircleAreaXV);
    tCosmic->SetBranchAddress("minimalEnclosingCircleAreaYV", &cosmic_minimalEnclosingCircleAreaYV, &b_cosmic_minimalEnclosingCircleAreaYV);
    tCosmic->SetBranchAddress("areaRatioXV", &cosmic_areaRatioXV, &b_cosmic_areaRatioXV);
    tCosmic->SetBranchAddress("areaRatioYV", &cosmic_areaRatioYV, &b_cosmic_areaRatioYV);
    tCosmic->SetBranchAddress("averageYposition", &cosmic_averageYposition, &b_cosmic_averageYposition);
    tCosmic->SetBranchAddress("isCosmic", &cosmic_isCosmic, &b_cosmic_isCosmic);

    tSignal->SetBranchAddress("convexHullAreaXV", &signal_convexHullAreaXV, &b_signal_convexHullAreaXV);
    tSignal->SetBranchAddress("convexHullAreaYV", &signal_convexHullAreaYV, &b_signal_convexHullAreaYV);
    tSignal->SetBranchAddress("minimalEnclosingCircleAreaXV", &signal_minimalEnclosingCircleAreaXV, &b_signal_minimalEnclosingCircleAreaXV);
    tSignal->SetBranchAddress("minimalEnclosingCircleAreaYV", &signal_minimalEnclosingCircleAreaYV, &b_signal_minimalEnclosingCircleAreaYV);
    tSignal->SetBranchAddress("areaRatioXV", &signal_areaRatioXV, &b_signal_areaRatioXV);
    tSignal->SetBranchAddress("areaRatioYV", &signal_areaRatioYV, &b_signal_areaRatioYV);
    tSignal->SetBranchAddress("averageYposition", &signal_averageYposition, &b_signal_averageYposition);
    tSignal->SetBranchAddress("isCosmic", &signal_isCosmic, &b_signal_isCosmic);

    TH2D* cosmic_areaRatioVsYposXview = new TH2D("cosmic_areaRatioVsYposXview", "Cosmic - X view; Avg. Y position (cm); Area Ratio", 100, -800., 800., 100, 0., 1.);
    TH2D* cosmic_areaRatioVsYposYview = new TH2D("cosmic_areaRatioVsYposYview", "Cosmic - Y view; Avg. Y position (cm); Area Ratio", 100, -800., 800., 100, 0., 1.);
    for (int i = 0; i < tCosmic->GetEntries(); i++) {
        tCosmic->GetEntry(i);
        if ((cosmic_convexHullAreaXV != 0.) && (cosmic_convexHullAreaYV != 0.)) {
            cosmic_areaRatioVsYposXview->Fill(cosmic_averageYposition, cosmic_convexHullAreaXV/cosmic_minimalEnclosingCircleAreaXV);
            cosmic_areaRatioVsYposYview->Fill(cosmic_averageYposition, cosmic_convexHullAreaYV/cosmic_minimalEnclosingCircleAreaYV);
        }
    }

    TH2D* signal_areaRatioVsYposXview = new TH2D("signal_areaRatioVsYposXview", "Signal - X view; Avg. Y position (cm); Area Ratio", 100, -800., 800., 100, 0., 1.);
    TH2D* signal_areaRatioVsYposYview = new TH2D("signal_areaRatioVsYposYview", "Signal - Y view; Avg. Y position (cm); Area Ratio", 100, -800., 800., 100, 0., 1.);
    for (int i = 0; i < tSignal->GetEntries(); i++) {
        tSignal->GetEntry(i);
        if ((signal_convexHullAreaXV != 0.) && (signal_convexHullAreaYV != 0.)) {
            signal_areaRatioVsYposXview->Fill(signal_averageYposition, signal_convexHullAreaXV/signal_minimalEnclosingCircleAreaXV);
            signal_areaRatioVsYposYview->Fill(signal_averageYposition, signal_convexHullAreaYV/signal_minimalEnclosingCircleAreaYV);
        }
    }


    TCanvas* g = new TCanvas("g", "g", 1600, 2400);
    g->cd();
    g->Divide(2,2);
    g->cd(1);
    cosmic_areaRatioVsYposXview->GetXaxis()->CenterTitle();
    cosmic_areaRatioVsYposXview->GetYaxis()->CenterTitle();
    cosmic_areaRatioVsYposXview->Draw("COLZ");
    gPad->SetRightMargin(0.15);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    gPad->SetTopMargin(0.15);
    g->cd(2);
    cosmic_areaRatioVsYposYview->GetXaxis()->CenterTitle();
    cosmic_areaRatioVsYposYview->GetYaxis()->CenterTitle();
    cosmic_areaRatioVsYposYview->Draw("COLZ");
    gPad->SetRightMargin(0.15);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    gPad->SetTopMargin(0.15);
    g->cd(3);
    signal_areaRatioVsYposXview->GetXaxis()->CenterTitle();
    signal_areaRatioVsYposXview->GetYaxis()->CenterTitle();
    signal_areaRatioVsYposXview->Draw("COLZ");
    gPad->SetRightMargin(0.15);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    gPad->SetTopMargin(0.15);
    g->cd(4);
    signal_areaRatioVsYposYview->GetXaxis()->CenterTitle();
    signal_areaRatioVsYposYview->GetYaxis()->CenterTitle();
    signal_areaRatioVsYposYview->Draw("COLZ");
    gPad->SetRightMargin(0.15);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    gPad->SetTopMargin(0.15);
    g->SetFixedAspectRatio();
    g->SaveAs("CircularVsY.pdf");
}