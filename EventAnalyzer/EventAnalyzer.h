#ifndef EventAnalyzer_h
#define EventAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TGraph.h>

#include <vector>
#include <utility>

#include "ClusterConvexHullEstimator.h"
#include "ClusterMinimalEnclosingCircle.h"

class EventAnalyzer {
public :
    TTree *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t fCurrent; //!current Tree number in a TChain

    // Declaration of leaf types
    UInt_t evtIdx;
    UInt_t clusterIdx;
    UInt_t viewIdx;
    Double_t t_XV;
    Double_t x_XV;
    Double_t y_XV;
    Double_t z_XV;
    Double_t e_XV;
    Double_t t_YV;
    Double_t x_YV;
    Double_t y_YV;
    Double_t z_YV;
    Double_t e_YV;

    // List of branches
    TBranch *b_evtIdx;   //!
    TBranch *b_clusterIdx;   //!
    TBranch *b_viewIdx;   //!
    TBranch *b_t_XV;   //!
    TBranch *b_x_XV;   //!
    TBranch *b_y_XV;   //!
    TBranch *b_z_XV;   //!
    TBranch *b_e_XV;   //!
    TBranch *b_t_YV;   //!
    TBranch *b_x_YV;   //!
    TBranch *b_y_YV;   //!
    TBranch *b_z_YV;   //!
    TBranch *b_e_YV;   //!

    EventAnalyzer(std::string fileName, TTree *tree = 0);

    virtual ~EventAnalyzer();

    virtual Int_t Cut(Long64_t entry);

    virtual Int_t GetEntry(Long64_t entry);

    virtual Long64_t LoadTree(Long64_t entry);

    virtual void Init(TTree *tree);

    virtual void Loop(unsigned int evtId);

    virtual Bool_t Notify();

    virtual void Show(Long64_t entry = -1);

    virtual void CircularGrade();

    virtual void SetNEvents(unsigned int n);

    virtual std::pair<TH1D*, TH1D*> GetRatioHist();

    virtual std::pair<TH2D*, TH2D*> GetAreaTH2Hist();

    virtual void SetDiffString(std::string diffStr);

private:
    std::string kDiffString;

    unsigned int kNEvents;

    TH2D* ratioX_y;
    TH2D* ratioY_y;

    TH2D* ec_ch_X;
    TH2D* ec_ch_Y;

    TH1D* ratioX;
    TH1D* ratioY;

    ClusterMinimalEnclosingCircle* minimalEnclosingCircleFinderX;
    ClusterMinimalEnclosingCircle* minimalEnclosingCircleFinderY;
    ClusterConvexHullEstimator*    convexHullFinderX;
    ClusterConvexHullEstimator*    convexHullFinderY;
};

#endif
