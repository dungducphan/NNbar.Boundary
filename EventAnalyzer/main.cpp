#include <iostream>
#include "EventAnalyzer.h"

int main() {
    EventAnalyzer* eaCosmic = new EventAnalyzer("/Users/dphan90/NOvA.NNbar/EventAnalyzer/Data/CosmicVsSignal/NNbar_CosmicClusterEventDisplay_Cosmic.root");
    eaCosmic->SetDiffString("Cosmic");
    eaCosmic->SetNEvents(10000);
    eaCosmic->CircularGrade();
    std::pair<TH1D*, TH1D*> RatioCosmic = eaCosmic->GetRatioHist();
    std::pair<TH2D*, TH2D*> RatioCosmicTH2 = eaCosmic->GetAreaTH2Hist();

    EventAnalyzer* eaSignal = new EventAnalyzer("/Users/dphan90/NOvA.NNbar/EventAnalyzer/Data/CosmicVsSignal/NNbar_CosmicClusterEventDisplay_Signal.root");
    eaSignal->SetDiffString("Signal");
    eaSignal->SetNEvents(10000);
    eaSignal->CircularGrade();
    std::pair<TH1D*, TH1D*> RatioSignal = eaSignal->GetRatioHist();
    std::pair<TH2D*, TH2D*> RatioSignalTH2 = eaSignal->GetAreaTH2Hist();

    double maxValue_cosmicX = RatioCosmic.first->GetMaximum();
    unsigned int maxBin_cosmicX = RatioCosmic.first->GetMaximumBin();
    for (unsigned int i = 0; i < RatioCosmic.first->GetSize(); i++) {
        double currentVal = RatioCosmic.first->GetBinContent(i);
        RatioCosmic.first->SetBinContent(maxBin_cosmicX, currentVal/maxValue_cosmicX);
    }

    double maxValue_cosmicY = RatioCosmic.second->GetMaximum();
    unsigned int maxBin_cosmicY = RatioCosmic.second->GetMaximumBin();
    for (unsigned int i = 0; i < RatioCosmic.second->GetSize(); i++) {
        double currentVal = RatioCosmic.second->GetBinContent(i);
        RatioCosmic.second->SetBinContent(maxBin_cosmicX, currentVal/maxValue_cosmicX);
    }

    double maxValue_signalX = RatioSignal.first->GetMaximum();
    unsigned int maxBin_signalX = RatioSignal.first->GetMaximumBin();
    for (unsigned int i = 0; i < RatioSignal.first->GetSize(); i++) {
        double currentVal = RatioSignal.first->GetBinContent(i);
        RatioSignal.first->SetBinContent(maxBin_signalX, currentVal/maxValue_signalX);
    }

    double maxValue_signalY = RatioSignal.second->GetMaximum();
    unsigned int maxBin_signalY = RatioSignal.second->GetMaximumBin();
    for (unsigned int i = 0; i < RatioSignal.second->GetSize(); i++) {
        double currentVal = RatioSignal.second->GetBinContent(i);
        RatioSignal.second->SetBinContent(maxBin_signalY, currentVal/maxValue_signalY);
    }

    TCanvas* c = new TCanvas("c", "c", 2400, 1200);
    gStyle->SetOptStat(0);
    c->cd();
    c->Divide(2,1);
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

    TCanvas* d = new TCanvas("d", "d", 2400, 2400);
    gStyle->SetOptStat(0);
    d->cd();
    d->Divide(2,2);
    d->cd(1);
    RatioCosmicTH2.first->Draw("COLZ");
    d->cd(2);
    RatioCosmicTH2.second->Draw("COLZ");
    d->cd(3);
    RatioSignalTH2.first->Draw("COLZ");
    d->cd(4);
    RatioSignalTH2.second->Draw("COLZ");
    d->SaveAs("CircularDegreeTH2Compare.pdf");
    delete d;

    return 0;
}