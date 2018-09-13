#ifndef STYLE_C
#define STYLE_C

#include "TCanvas.h"
#include "TH1.h"
#include "TROOT.h"
#include "TColor.h"
#include "TLine.h"
#include "TStyle.h"
#include "Rtypes.h"
#include "TAttLine.h"

// General style
void GeneralStyle();

// Styling TLine
void StyleLine(TLine* line,
               EColor color = kRed,
               int thickness = 1,
               ELineStyle lineStyle = kSolid);

// Styling TCanvas
void StyleLogLog(TCanvas*);
void StyleLinearLog(TCanvas*);
void StyleLogLinear(TCanvas*);

// Styling TH1
void StyleTH1(TH1* histo,
              EColor color = kRed,
              int thickness = 1,
              ELineStyle lineStyle = kSolid,
              bool sumw2 = false,
              EMarkerStyle markerStyle = kOpenSquare,
              int markerSize = 1);

void GeneralStyle() {
    TStyle* generalStyle = new TStyle("generalStyle", "General Plotting Style");

    // Centre title
    generalStyle->SetTitleAlign(22);
    generalStyle->SetTitleX(.5);
    generalStyle->SetTitleY(.95);
    generalStyle->SetTitleBorderSize(0);

    // No info box
    generalStyle->SetOptStat(0);

    //set the background color to white
    generalStyle->SetFillColor(10);
    generalStyle->SetFrameFillColor(10);
    generalStyle->SetCanvasColor(10);
    generalStyle->SetPadColor(10);
    generalStyle->SetTitleFillColor(0);
    generalStyle->SetStatColor(10);

    // Don't put a colored frame around the plots
    generalStyle->SetFrameBorderMode(0);
    generalStyle->SetCanvasBorderMode(0);
    generalStyle->SetPadBorderMode(0);

    // Set the default line color for a fit function to be red
    generalStyle->SetFuncColor(kRed);

    // Marker settings
    generalStyle->SetMarkerStyle(kFullCircle);
    //generalStyle->SetLineStyle(kDashed);

    // No border on legends
    generalStyle->SetLegendBorderSize(0);

    // Axis titles
    generalStyle->SetTitleSize(.065, "xyz");
    generalStyle->SetTitleOffset(.8, "xyz");
    // More space for y-axis to avoid clashing with big numbers
    generalStyle->SetTitleOffset(1.2, "y");
    generalStyle->SetTitleOffset(1.2, "x");
    // This applies the same settings to the overall plot title
    generalStyle->SetTitleSize(.075, "");
    generalStyle->SetTitleOffset(.8, "");
    // Axis labels (numbering)
    generalStyle->SetLabelSize(.055, "xyz");
    generalStyle->SetLabelOffset(.005, "xyz");

    // Prevent ROOT from occasionally automatically zero-suppressing
    generalStyle->SetHistMinimumZero();

    // Thicker lines
    generalStyle->SetHistLineWidth(2);
    generalStyle->SetFrameLineWidth(2);
    generalStyle->SetFuncWidth(2);

    // Set the number of tick marks to show
    generalStyle->SetNdivisions(504, "xyz");

    // Set the tick mark style
    generalStyle->SetPadTickX(1);
    generalStyle->SetPadTickY(1);

    // Fonts
    const int kGeneralFont = 42;
    generalStyle->SetStatFont(kGeneralFont);
    generalStyle->SetLabelFont(kGeneralFont, "xyz");
    generalStyle->SetTitleFont(kGeneralFont, "xyz");
    generalStyle->SetTitleFont(kGeneralFont, ""); // Apply same setting to plot titles
    generalStyle->SetTextFont(kGeneralFont);
    generalStyle->SetLegendFont(kGeneralFont);

    // Get moodier colours for colz
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;
    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    generalStyle->SetNumberContours(NCont);

    gROOT->SetStyle("generalStyle");
}

void StyleLinearLinear(TCanvas* c) {
    c->SetRightMargin(0.15);
    c->SetLeftMargin(0.15);
    c->SetBottomMargin(0.15);
}

void StyleLogLog(TCanvas* c) {
    c->SetRightMargin(0.15);
    c->SetLeftMargin(0.15);
    c->SetBottomMargin(0.15);
    c->SetLogx();
    c->SetLogy();
}

void StyleLinearLog(TCanvas* c) {
    c->SetRightMargin(0.15);
    c->SetLeftMargin(0.15);
    c->SetBottomMargin(0.15);
    c->SetLogy();
}

void StyleLogLinear(TCanvas* c) {
    c->SetRightMargin(0.15);
    c->SetLeftMargin(0.15);
    c->SetBottomMargin(0.15);
    c->SetLogx();
}

void StyleLine(TLine* line,
               EColor color,
               int thickness,
               ELineStyle lineStyle) {
    line->SetLineColor(color);
    line->SetLineWidth(thickness);
    line->SetLineStyle(lineStyle);
}

void StyleTH1(TH1* histo,
              EColor color,
              int thickness,
              ELineStyle lineStyle,
              bool sumw2,
              EMarkerStyle markerStyle,
              int markerSize) {
    histo->GetXaxis()->CenterTitle();
    histo->GetYaxis()->CenterTitle();

    histo->SetLineColor(color);
    histo->SetLineWidth(thickness);
    histo->SetLineStyle(lineStyle);

    if (sumw2) {
        histo->Sumw2();
        histo->SetMarkerStyle(markerStyle);
        histo->SetMarkerColor(color);
        histo->SetMarkerSize(markerSize);
    }
}


#endif