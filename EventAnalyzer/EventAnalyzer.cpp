#include "EventAnalyzer.h"

EventAnalyzer::EventAnalyzer(std::string fileName, TTree *tree) : fChain(0) {
    if (tree == 0) {
        TFile *f = (TFile *) gROOT->GetListOfFiles()->FindObject(fileName.c_str());
        if (!f || !f->IsOpen()) {
            f = new TFile(fileName.c_str());
        }
        std::string folderStr = fileName + ":/cosmicclustereventdisplay";
        TDirectory *dir = (TDirectory *) f->Get(folderStr.c_str());
        dir->GetObject("clusterTree_", tree);

    }
    Init(tree);
}

EventAnalyzer::~EventAnalyzer() {
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

Int_t EventAnalyzer::GetEntry(Long64_t entry) {
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}

Long64_t EventAnalyzer::LoadTree(Long64_t entry) {
    if (!fChain) return -5;
    Long64_t centry = fChain->LoadTree(entry);
    if (centry < 0) return centry;
    if (fChain->GetTreeNumber() != fCurrent) {
        fCurrent = fChain->GetTreeNumber();
        Notify();
    }
    return centry;
}

void EventAnalyzer::Init(TTree *tree) {

    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("evtIdx", &evtIdx, &b_evtIdx);
    fChain->SetBranchAddress("clusterIdx", &clusterIdx, &b_clusterIdx);
    fChain->SetBranchAddress("viewIdx", &viewIdx, &b_viewIdx);
    fChain->SetBranchAddress("t_XV", &t_XV, &b_t_XV);
    fChain->SetBranchAddress("x_XV", &x_XV, &b_x_XV);
    fChain->SetBranchAddress("y_XV", &y_XV, &b_y_XV);
    fChain->SetBranchAddress("z_XV", &z_XV, &b_z_XV);
    fChain->SetBranchAddress("e_XV", &e_XV, &b_e_XV);
    fChain->SetBranchAddress("t_YV", &t_YV, &b_t_YV);
    fChain->SetBranchAddress("x_YV", &x_YV, &b_x_YV);
    fChain->SetBranchAddress("y_YV", &y_YV, &b_y_YV);
    fChain->SetBranchAddress("z_YV", &z_YV, &b_z_YV);
    fChain->SetBranchAddress("e_YV", &e_YV, &b_e_YV);
    Notify();
}

Bool_t EventAnalyzer::Notify() {
    return kTRUE;
}

void EventAnalyzer::Show(Long64_t entry) {
    if (!fChain) return;
    fChain->Show(entry);
}

Int_t EventAnalyzer::Cut(Long64_t entry) {
    return 1;
}

void EventAnalyzer::Loop(unsigned int evtId) {
    minimalEnclosingCircleFinderX = new ClusterMinimalEnclosingCircle();
    convexHullFinderX = new ClusterConvexHullEstimator();
    minimalEnclosingCircleFinderY = new ClusterMinimalEnclosingCircle();
    convexHullFinderY = new ClusterConvexHullEstimator();

    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();

    std::vector<std::pair<double, double> > XViewCluster;
    std::vector<std::pair<double, double> > YViewCluster;

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);
        nbytes += nb;

        if (evtIdx != evtId) continue;
        if (clusterIdx != 0) continue;
        if (viewIdx == 0) {
            XViewCluster.push_back(std::make_pair(z_XV, x_XV));
        } else {
            YViewCluster.push_back(std::make_pair(z_YV, y_YV));
        }
    }

    minimalEnclosingCircleFinderX->SetPoints(XViewCluster);
    std::pair<double, double> originX = minimalEnclosingCircleFinderX->GetCircleOrigin();
    double radiusX = minimalEnclosingCircleFinderX->GetCircleRadius();
    convexHullFinderX->SetPoints(XViewCluster);
    std::vector< std::pair<double, double> > ConvexSetX = convexHullFinderX->GetConvexHullPoints();

    minimalEnclosingCircleFinderY->SetPoints(YViewCluster);
    std::pair<double, double> originY = minimalEnclosingCircleFinderY->GetCircleOrigin();
    double radiusY = minimalEnclosingCircleFinderY->GetCircleRadius();
    convexHullFinderY->SetPoints(YViewCluster);
    std::vector< std::pair<double, double> > ConvexSetY = convexHullFinderY->GetConvexHullPoints();

    // EVD cluster
    TH2D* XViewEVD = new TH2D("XView", "XView", 12000, 0, 6000, 3200, -800, 800);
    TH2D* YViewEVD = new TH2D("YView", "YView", 12000, 0, 6000, 3200, -800, 800);
//    TH2D* XViewEVD = new TH2D("XView", "XView", 2000, 2500, 3500, 2000, -500, 500); // Zoom
//    TH2D* YViewEVD = new TH2D("YView", "YView", 2000, 2500, 3500, 2000, -500, 500); // Zoom

    for (unsigned int i = 0; i < XViewCluster.size(); i++) {
        double tmp_x = XViewCluster.at(i).first;
        double tmp_y = XViewCluster.at(i).second;
        XViewEVD->Fill(tmp_x, tmp_y);
    }

    for (unsigned int i = 0; i < YViewCluster.size(); i++) {
        double tmp_x = YViewCluster.at(i).first;
        double tmp_y = YViewCluster.at(i).second;
        YViewEVD->Fill(tmp_x, tmp_y);
    }

    // Minimal Enclosing Circle
    double circleXview_x[101];
    double circleXview_y[101];
    for (unsigned int i = 0; i < 101; i++) {
        double angle = 2*TMath::Pi()*((double)i/100.);
        circleXview_x[i] = originX.first + radiusX * TMath::Cos(angle);
        circleXview_y[i] = originX.second + radiusX * TMath::Sin(angle);
    }
    TGraph* gr_circleX = new TGraph(101, circleXview_x, circleXview_y);
    gr_circleX->SetLineColor(kRed);

    double circleYview_x[101];
    double circleYview_y[101];
    for (unsigned int i = 0; i < 101; i++) {
        double angle = 2*TMath::Pi()*((double)i/100.);
        circleYview_x[i] = originY.first + radiusY * TMath::Cos(angle);
        circleYview_y[i] = originY.second + radiusY * TMath::Sin(angle);
    }
    TGraph* gr_circleY = new TGraph(101, circleYview_x, circleYview_y);
    gr_circleY->SetLineColor(kRed);

    // Convex Hull
    const unsigned int convexHullNX = ConvexSetX.size();
    const unsigned int convexHullNY = ConvexSetY.size();
    double* ConvexSetArrayX_x = (double*) malloc(convexHullNX * sizeof(double));
    double* ConvexSetArrayX_y = (double*) malloc(convexHullNX * sizeof(double));
    double* ConvexSetArrayY_x = (double*) malloc(convexHullNY * sizeof(double));
    double* ConvexSetArrayY_y = (double*) malloc(convexHullNY * sizeof(double));

    for (unsigned int i = 0; i < convexHullNX; i++) {
        ConvexSetArrayX_x[i] = ConvexSetX.at(i).first;
        ConvexSetArrayX_y[i] = ConvexSetX.at(i).second;
    }

    for (unsigned int i = 0; i < convexHullNY; i++) {
        ConvexSetArrayY_x[i] = ConvexSetY.at(i).first;
        ConvexSetArrayY_y[i] = ConvexSetY.at(i).second;
    }

    TGraph* gr_convexX = new TGraph(convexHullNX, ConvexSetArrayX_x, ConvexSetArrayX_y);
    gr_convexX->SetLineColor(kBlue);
    gr_convexX->SetMarkerColor(kBlue);
    gr_convexX->SetMarkerSize(1);

    TGraph* gr_convexY = new TGraph(convexHullNY, ConvexSetArrayY_x, ConvexSetArrayY_y);
    gr_convexY->SetLineColor(kBlue);
    gr_convexY->SetMarkerColor(kBlue);
    gr_convexY->SetMarkerSize(1);

    // Drawing
//    TCanvas* c = new TCanvas("c", "c", 2400, 4800); // Zoom
    TCanvas* c = new TCanvas("c", "c", 2400, 1400);
    gStyle->SetOptStat(0);
    c->Divide(1,2);

    c->cd(1);
    gPad->SetFixedAspectRatio(1);
    XViewEVD->Draw();
    gr_circleX->Draw("L same");
    gr_convexX->Draw("PL same");

    c->cd(2);
    YViewEVD->Draw();
    gr_circleY->Draw("L same");
    gr_convexY->Draw("PL same");

    c->SaveAs(Form("Plots/Evt_%i-%s.pdf", evtId, kDiffString.c_str()));

    delete XViewEVD;
    delete YViewEVD;
    delete c;
}

void EventAnalyzer::CircularGrade() {
    if (fChain == 0) return;

    // Correlation between ratio and y position
    ratioX_y = new TH2D("ratioX_y", Form("%s - X view; Avg. Y position (cm); Area Ratio", kDiffString.c_str()), 100, -800., 800., 100, 0., 1.);
    ratioY_y = new TH2D("ratioY_y", Form("%s - Y view; Avg. Y position (cm); Area Ratio", kDiffString.c_str()), 100, -800., 800., 100, 0., 1.);

    // Convex Area and Enclosing Circle Area (TH2)
    ec_ch_X = new TH2D("ec_ch_X", Form("%s - X view; C-Hull Area (cm#{2}); MEC Area (cm#{2})", kDiffString.c_str()), 100, 0., 100000., 100, 0., 50000.);
    ec_ch_Y = new TH2D("ec_ch_Y", Form("%s - Y view; C-Hull Area (cm#{2}); MEC Area (cm#{2})", kDiffString.c_str()), 100, 0., 100000., 100, 0., 50000.);

    // Ratio of Convex Area and Enclosing Circle
    ratioX = new TH1D("ratioX", Form("%s - X view; Area Ratio;", kDiffString.c_str()), 50, 0, 1.);
    ratioY = new TH1D("ratioY", Form("%s - Y view; Area Ratio;", kDiffString.c_str()), 50, 0, 1.);
    rX_rY  = new TH2D("rX_rY",  Form("%s; Area Ratio in X view; Area Ratio in Y view", kDiffString.c_str()), 50, 0., 1., 50, 0., 1.);

    double convexHullAreaXV, convexHullAreaYV, minimalEnclosingCircleAreaXV, minimalEnclosingCircleAreaYV;
    double areaRatioXV, areaRatioYV;
    double averageYposition;
    bool   isCosmic;

    tree = new TTree("NNBarBoundary","NNBar Boundary Variables");
    tree->Branch("isCosmic", &isCosmic, "isCosmic/B");
    tree->Branch("convexHullAreaXV", &convexHullAreaXV, "convexHullAreaXV/D");
    tree->Branch("convexHullAreaYV", &convexHullAreaYV, "convexHullAreaYV/D");
    tree->Branch("minimalEnclosingCircleAreaXV", &minimalEnclosingCircleAreaXV, "minimalEnclosingCircleAreaXV/D");
    tree->Branch("minimalEnclosingCircleAreaYV", &minimalEnclosingCircleAreaYV, "minimalEnclosingCircleAreaYV/D");
    tree->Branch("areaRatioXV", &areaRatioXV, "areaRatioXV/D");
    tree->Branch("areaRatioYV", &areaRatioYV, "areaRatioYV/D");
    tree->Branch("averageYposition", &averageYposition, "averageYposition/D");

    isCosmic = (kDiffString == "Cosmic");
    Long64_t nentries = fChain->GetEntriesFast();
    for (unsigned int evtId = 0; evtId < kNEvents; evtId++) {
        if (evtId % 1000 == 0) std::cout << "Event number: " << evtId << "." << std::endl;
        minimalEnclosingCircleFinderX = new ClusterMinimalEnclosingCircle();
        convexHullFinderX = new ClusterConvexHullEstimator();
        minimalEnclosingCircleFinderY = new ClusterMinimalEnclosingCircle();
        convexHullFinderY = new ClusterConvexHullEstimator();

        std::vector<std::pair<double, double> > XViewCluster;
        std::vector<std::pair<double, double> > YViewCluster;
        std::vector<double> YViewCell;

        Long64_t nbytes = 0, nb = 0;
        for (Long64_t jentry = 0; jentry < nentries; jentry++) {
            Long64_t ientry = LoadTree(jentry);
            if (ientry < 0) break;
            nb = fChain->GetEntry(jentry);
            nbytes += nb;

            if (evtIdx != evtId) continue;
            if (clusterIdx != 0) continue;
            if (viewIdx == 0) {
                XViewCluster.push_back(std::make_pair(z_XV, x_XV));
            } else {
                YViewCluster.push_back(std::make_pair(z_YV, y_YV));
                YViewCell.push_back(y_YV);
            }
        }

        double avgYposition = 0.;
        for (unsigned int k = 0; k < YViewCell.size(); k++) {
            avgYposition += YViewCell.at(k);
        }
        avgYposition = avgYposition/YViewCell.size();

        minimalEnclosingCircleFinderX->SetPoints(XViewCluster);
        double enclosingAreaX = minimalEnclosingCircleFinderX->GetMinimalEnclosingCircleArea();
        convexHullFinderX->SetPoints(XViewCluster);
        double convexAreaX = convexHullFinderX->GetConvexHullArea();

        minimalEnclosingCircleFinderY->SetPoints(YViewCluster);
        double enclosingAreaY = minimalEnclosingCircleFinderY->GetMinimalEnclosingCircleArea();
        convexHullFinderY->SetPoints(YViewCluster);
        double convexAreaY = convexHullFinderY->GetConvexHullArea();

        delete minimalEnclosingCircleFinderX;
        delete minimalEnclosingCircleFinderY;
        delete convexHullFinderX;
        delete convexHullFinderY;

        bool recordThisEvt = !((convexAreaX == 0.) && (convexAreaY == 0.) && (enclosingAreaX == 0.) && (enclosingAreaY == 0.));
        if (recordThisEvt) {
            ratioX->Fill(convexAreaX/enclosingAreaX);
            ratioX_y->Fill(avgYposition, convexAreaX/enclosingAreaX);

            ratioY->Fill(convexAreaY/enclosingAreaY);
            ratioY_y->Fill(avgYposition, convexAreaY/enclosingAreaY);

            rX_rY->Fill(convexAreaX/enclosingAreaX, convexAreaY/enclosingAreaY);

            convexHullAreaXV = convexAreaX;
            minimalEnclosingCircleAreaXV = enclosingAreaX;
            averageYposition = avgYposition;
            areaRatioXV = convexAreaX/enclosingAreaX;

            convexHullAreaYV = convexAreaY;
            minimalEnclosingCircleAreaYV = enclosingAreaY;
            averageYposition = avgYposition;
            areaRatioYV = convexAreaY/enclosingAreaY;

            tree->Fill();
        }
    }

    TFile* outFile = new TFile(Form("NNbar-Boundary-%s.root", kDiffString.c_str()), "RECREATE");
    outFile->cd();
    tree->Write();
    outFile->Close();
}

void EventAnalyzer::SetNEvents(unsigned int n) {
    kNEvents = n;
}

std::pair<TH1D *, TH1D *> EventAnalyzer::GetRatioHist() {
    return std::make_pair(ratioX, ratioY);
}

std::pair<TH2D *, TH2D *> EventAnalyzer::GetRatioYCorrTH2Hist() {
    return std::make_pair(ratioX_y, ratioY_y);
}

void EventAnalyzer::SetDiffString(std::string diffStr) {
    kDiffString = diffStr;
}

TH2D *EventAnalyzer::GetRatioTH2Hist() {
    return rX_rY;
}
