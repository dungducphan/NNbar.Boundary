#include <iostream>
#include "EventAnalyzer.h"
#include "Style.C"

int main() {
    GeneralStyle();

    EventAnalyzer* eaCosmic = new EventAnalyzer("/Users/dphan90/NOvA.NNbar/EventAnalyzer/Data/CosmicVsSignal/NNbar_CosmicClusterEventDisplay_Cosmic.root");
    eaCosmic->SetDiffString("Cosmic");
    eaCosmic->SetNEvents(100);
    eaCosmic->CircularGrade();
    std::pair<TH1D*, TH1D*> RatioCosmic = eaCosmic->GetRatioHist();
    std::pair<TH2D*, TH2D*> RatioYCorrCosmic = eaCosmic->GetRatioYCorrTH2Hist();
    TH2D* RatioCosmicTH2 = eaCosmic->GetRatioTH2Hist();

    EventAnalyzer* eaSignal = new EventAnalyzer("/Users/dphan90/NOvA.NNbar/EventAnalyzer/Data/CosmicVsSignal/NNbar_CosmicClusterEventDisplay_Signal.root");
    eaSignal->SetDiffString("Signal");
    eaSignal->SetNEvents(100);
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
        RatioCosmic.second->SetBinContent(i, currentVal/maxValue_cosmicX);
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
    StyleLinearLinear(c);
    gStyle->SetOptStat(0);
    c->cd();
    c->Divide(2, 1);
    c->cd(1);
    RatioCosmic.first->Draw();
    RatioSignal.first->SetLineColor(kRed);
    RatioSignal.first->Draw("SAME");
    c->cd(2);
    RatioCosmic.second->Draw();
    RatioSignal.second->SetLineColor(kRed);
    RatioSignal.second->Draw("SAME");
    c->SaveAs("CircularDegreeCompare.pdf");
    delete c;

    TCanvas* d = new TCanvas("d", "d", 2400, 1200);
    StyleLinearLinear(d);
    gStyle->SetOptStat(0);
    d->cd();
    d->Divide(2, 1);
    d->cd(1);
    RatioCosmicTH2->Draw("COLZ");
    d->cd(2);
    RatioSignalTH2->Draw("COLZ");
    d->SaveAs("CircularDegreeTH2Compare.pdf");
    delete d;

    TCanvas* g = new TCanvas("g", "g", 2400, 2400);
    StyleLinearLinear(g);
    gStyle->SetOptStat(0);
    g->cd();
    g->Divide(2,2);
    g->cd(1);
    RatioYCorrCosmic.first->Draw("COLZ");
    g->cd(2);
    RatioYCorrCosmic.second->Draw("COLZ");
    g->cd(3);
    RatioYCorrSignal.first->Draw("COLZ");
    g->cd(4);
    RatioYCorrSignal.second->Draw("COLZ");
    g->SaveAs("CircularVsY.pdf");
    delete g;

    return 0;
}