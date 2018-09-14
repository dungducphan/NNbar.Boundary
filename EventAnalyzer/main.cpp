#include <iostream>
#include "EventAnalyzer.h"
#include "Style.C"

int main() {
    GeneralStyle();

    EventAnalyzer* eaCosmic = new EventAnalyzer("../Data/CosmicVsSignal/NNbar_CosmicClusterEventDisplay_Cosmic.root");
    eaCosmic->SetDiffString("Cosmic");
    eaCosmic->SetNEvents(2000);
    eaCosmic->CircularGrade();
    std::pair<TH1D*, TH1D*> RatioCosmic = eaCosmic->GetRatioHist();
    std::pair<TH2D*, TH2D*> RatioYCorrCosmic = eaCosmic->GetRatioYCorrTH2Hist();
    TH2D* RatioCosmicTH2 = eaCosmic->GetRatioTH2Hist();

    EventAnalyzer* eaSignal = new EventAnalyzer("../Data/CosmicVsSignal/NNbar_CosmicClusterEventDisplay_Signal.root");
    eaSignal->SetDiffString("Signal");
    eaSignal->SetNEvents(2000);
    eaSignal->CircularGrade();
    std::pair<TH1D*, TH1D*> RatioSignal = eaSignal->GetRatioHist();
    std::pair<TH2D*, TH2D*> RatioYCorrSignal = eaSignal->GetRatioYCorrTH2Hist();
    TH2D* RatioSignalTH2 = eaSignal->GetRatioTH2Hist();

    double maxValue_cosmicX = RatioCosmic.first->GetMaximum();
    unsigned int maxBin_cosmicX = RatioCosmic.first->GetMaximumBin();
    for (unsigned int i = 0; i < RatioCosmic.first->GetSize(); i++) {
        double currentVal = RatioCosmic.first->GetBinContent(i);
        RatioCosmic.first->SetBinContent(i, currentVal/maxValue_cosmicX);
    }

    double maxValue_cosmicY = RatioCosmic.second->GetMaximum();
    unsigned int maxBin_cosmicY = RatioCosmic.second->GetMaximumBin();
    for (unsigned int i = 0; i < RatioCosmic.second->GetSize(); i++) {
        double currentVal = RatioCosmic.second->GetBinContent(i);
        RatioCosmic.second->SetBinContent(i, currentVal/maxValue_cosmicY);
    }

    double maxValue_signalX = RatioSignal.first->GetMaximum();
    unsigned int maxBin_signalX = RatioSignal.first->GetMaximumBin();
    for (unsigned int i = 0; i < RatioSignal.first->GetSize(); i++) {
        double currentVal = RatioSignal.first->GetBinContent(i);
        RatioSignal.first->SetBinContent(i, currentVal/maxValue_signalX);
    }

    double maxValue_signalY = RatioSignal.second->GetMaximum();
    unsigned int maxBin_signalY = RatioSignal.second->GetMaximumBin();
    for (unsigned int i = 0; i < RatioSignal.second->GetSize(); i++) {
        double currentVal = RatioSignal.second->GetBinContent(i);
        RatioSignal.second->SetBinContent(i, currentVal/maxValue_signalY);
    }

    TCanvas* c = new TCanvas("c", "c", 2400, 1200);
    gStyle->SetOptStat(0);
    c->cd();
    c->Divide(2, 1);
    c->cd(1);
    RatioCosmic.first->GetXaxis()->CenterTitle();
    RatioCosmic.first->Draw();
    RatioSignal.first->SetLineColor(kRed);
    RatioSignal.first->Draw("SAME");
    gPad->SetRightMargin(0.15);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    gPad->SetTopMargin(0.15);
    c->cd(2);
    RatioCosmic.second->GetXaxis()->CenterTitle();
    RatioCosmic.second->Draw();
    RatioSignal.second->SetLineColor(kRed);
    RatioSignal.second->Draw("SAME");
    gPad->SetRightMargin(0.15);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    gPad->SetTopMargin(0.15);
    c->SaveAs("CircularDegreeCompare.pdf");
    delete c;

    TCanvas* d = new TCanvas("d", "d", 2400, 1200);
//    StyleLinearLinear(d);
    gStyle->SetOptStat(0);
    d->cd();
    d->Divide(2, 1);
    d->cd(1);
    RatioCosmicTH2->GetXaxis()->CenterTitle();
    RatioCosmicTH2->GetYaxis()->CenterTitle();
    RatioCosmicTH2->Draw("COLZ");
    gPad->SetRightMargin(0.15);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    gPad->SetTopMargin(0.15);
    d->cd(2);
    RatioSignalTH2->GetXaxis()->CenterTitle();
    RatioSignalTH2->GetYaxis()->CenterTitle();
    RatioSignalTH2->Draw("COLZ");
    gPad->SetRightMargin(0.15);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    gPad->SetTopMargin(0.15);
    d->SaveAs("CircularDegreeTH2Compare.pdf");
    delete d;

    TCanvas* g = new TCanvas("g", "g", 2400, 2400);
//    StyleLinearLinear(g);
    gStyle->SetOptStat(0);
    g->cd();
    g->Divide(2,2);
    g->cd(1);
    RatioYCorrCosmic.first->GetXaxis()->CenterTitle();
    RatioYCorrCosmic.first->GetYaxis()->CenterTitle();
    RatioYCorrCosmic.first->Draw("COLZ");
    gPad->SetRightMargin(0.15);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    gPad->SetTopMargin(0.15);
    g->cd(2);
    RatioYCorrCosmic.second->GetXaxis()->CenterTitle();
    RatioYCorrCosmic.second->GetYaxis()->CenterTitle();
    RatioYCorrCosmic.second->Draw("COLZ");
    gPad->SetRightMargin(0.15);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    gPad->SetTopMargin(0.15);
    g->cd(3);
    RatioYCorrSignal.first->GetXaxis()->CenterTitle();
    RatioYCorrSignal.first->GetYaxis()->CenterTitle();
    RatioYCorrSignal.first->Draw("COLZ");
    gPad->SetRightMargin(0.15);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    gPad->SetTopMargin(0.15);
    g->cd(4);
    RatioYCorrSignal.second->GetXaxis()->CenterTitle();
    RatioYCorrSignal.second->GetYaxis()->CenterTitle();
    RatioYCorrSignal.second->Draw("COLZ");
    gPad->SetRightMargin(0.15);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    gPad->SetTopMargin(0.15);
    g->SaveAs("CircularVsY.pdf");
    delete g;

    return 0;
}