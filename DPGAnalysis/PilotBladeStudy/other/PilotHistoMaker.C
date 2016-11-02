#include "TROOT.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TChainElement.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "TProfile.h"
#include "TLegend.h"
#include <iostream>
#include <sys/stat.h>
#include <vector>
#include <stdlib.h>

#include "PilotHistoMaker.h"
#include "/data/vami/projects/pilotBlade/PilotHistoMakerDelays.h"
//#include "PilotHistoMakerDelays.h"

std::string name(int detid) {
    if (detid==344130820) return std::string("FPix_BmI_D3_BLD3_PNL1_PLQ1");
    if (detid==344131844) return std::string("FPix_BmI_D3_BLD2_PNL1_PLQ1");
    if (detid==344132868) return std::string("FPix_BmO_D3_BLD10_PNL1_PLQ1");
    if (detid==344133892) return std::string("FPix_BmO_D3_BLD11_PNL1_PLQ1");
    if (detid==344131076) return std::string("FPix_BmI_D3_BLD3_PNL2_PLQ1");
    if (detid==344132100) return std::string("FPix_BmI_D3_BLD2_PNL2_PLQ1");
    if (detid==344133124) return std::string("FPix_BmO_D3_BLD10_PNL2_PLQ1");
    if (detid==344134148) return std::string("FPix_BmO_D3_BLD11_PNL2_PLQ1");
    // Disk2
    if (detid==344081668) return std::string("FPix_BmO_D2_BLD11_PNL1_MOD1");
    if (detid==344081672) return std::string("FPix_BmO_D2_BLD11_PNL1_MOD2");
    if (detid==344081676) return std::string("FPix_BmO_D2_BLD11_PNL1_MOD3");
    if (detid==344081680) return std::string("FPix_BmO_D2_BLD11_PNL1_MOD4");
    
    if (detid==1) return std::string("FPix_BmO_D2_BLD10+11");
    return std::string("");
}

// ---------------------------------------------------------------------------
// -----------------------------Rechits---------------------------------------
// ---------------------------------------------------------------------------

void rechits(bool saveAll, std::string save_dir, const char* format, TChain* filechain)
{
    bool saveRecHits = 0;
    if (saveAll) saveRecHits = 1;
    Int_t selectDelay=-9999;
    Long64_t reduceFraction=0;
    Int_t skipFiles=0;
 
    int _detids[] = { 344132868};
    //int _detids[] = { 344132868, 344134148, 344131076, 344132100, 344130820, 1, 344131844 };
    //int _detids[] = { 344130820, 344131844, 344132868, 344133892, 344131076, 344132100, 344133124, 344134148 };
    std::vector<int> detids(_detids, _detids + sizeof(_detids) / sizeof(int) );
    
    std::map<int,int> idx_map;
    for (size_t i=0; i<detids.size(); i++) {
        idx_map[detids[i]]=i;
        std::cout << "define detector id " << detids[i] << " as " << idx_map[detids[i]]<<std::endl;
    }
    const std::map<int,int>& idx = idx_map;
    
    // Create the histograms
    std::vector<std::vector<TH1*> > hists;
        
    std::vector<TH1F *> PBHitCluDx;
    std::vector<TH1F *> PBHitCluDy;
        
    for (size_t imod=0; imod<detids.size(); imod++) {
        
        std::vector<TH1*> vh;
        TH1 *h;
        
        PBHitCluDx.push_back((TH1F*)(h=new TH1F(Form("PBHitCluDx_%d", detids[imod]),  Form("Rechit to nearest cluster distance in %s;dx [cm];Yield", name(detids[imod]).c_str()), 400,-2,2))); vh.push_back(h);
        PBHitCluDy.push_back((TH1F*)(h=new TH1F(Form("PBHitCluDy_%d", detids[imod]),  Form("Rechit to nearest cluster distance in %s;dy [cm];Yield", name(detids[imod]).c_str()), 1000,-7,3))); vh.push_back(h);
       
        hists.push_back(vh);
    }
    
    for (size_t i=0; i<hists.size(); i++) {
        for (size_t j=0; j<hists[i].size(); j++) {
            std::cout<<hists[i][j]->GetName()<< " : "<<hists[i][j]->GetTitle()<<std::endl;
            hists[i][j]->SetMarkerColor(i==7 ? 46 : i+1);
            hists[i][j]->SetMarkerStyle(hists[i][j]->GetDimension()==1 ? 20 : 1);
            hists[i][j]->SetLineColor(i==7 ? 46 : i+1);
            hists[i][j]->SetLineWidth(2);
        }
        std::cout<<std::endl;
    }
    
    DigiData digi;
    ModuleData module_on;
    EventData evt;
    ClustData clusters;
    TrajMeasData traj;
    TrackData trk;
    
    TObjArray* fileElements = filechain->GetListOfFiles();
    TIter next(fileElements);
    TChainElement* chEl=0;
    Int_t fileCounter=0;
    
    while (( chEl=(TChainElement*)next() )) {
        fileCounter++;
        if ((skipFiles!=0) && (fileCounter%skipFiles!=0)) continue;
        TFile f(chEl->GetTitle());
        std::cout << "Opening "<<chEl->GetTitle()<<std::endl;
        //TTree* clustTree = (TTree*)f.Get("clustTree");
        TTree* trajTree = (TTree*)f.Get("trajTree");
        
        trajTree->GetBranch("traj")->SetAddress(&traj);
        trajTree->GetBranch("module_on")->SetAddress(&module_on);
        trajTree->GetBranch("event")->SetAddress(&evt);
        trajTree->GetBranch("track")->SetAddress(&trk);
        
        //if (trk.highPurity==0) continue;
        
        for (Long64_t i=0, ntraj=trajTree->GetEntries(); i<ntraj; ++i) {
            if (reduceFraction!=0 && i%reduceFraction!=0) continue;
            trajTree->GetEntry(i);
            int del=delay(evt.run, evt.ls);
            if (del==-9999) {
                std::cout << "Run " << evt.run << " LS " << evt.ls << "has no delay set up -- exiting" << std::endl; 
                continue; 
            }
            if (selectDelay!=-9999 && del!=selectDelay) continue;
            
            if (module_on.disk!=-3 && !(module_on.disk==-2 && (module_on.blade==-10 || module_on.blade==-11)) ) continue;
            int rawid=module_on.rawid;
            if (module_on.disk==-2) rawid=1;
            
            std::map<int,int>::const_iterator it_idx=idx.find(rawid);
            if (it_idx==idx.end()) continue;
            if (traj.type!=102) continue;
            int imod = it_idx->second;
            
            // Correction to cluster positions  344132868, 344134148, 344131076, 344132100, 344130820
            float dx_cl = traj.dx_cl;
            float dy_cl = traj.dy_cl;

            if (evt.federrs_size==0 && module_on.federr==0) { 
                PBHitCluDx[imod]->Fill(dx_cl);
                PBHitCluDy[imod]->Fill(dy_cl);
            }
            
        }
        // -------------------------------------------- 
    } // End of loop on files
    
    // Create the canvas and save
    
    for (size_t j=0; j<hists[0].size(); j++) { // loop on plots
        for (size_t i=0; i<hists.size(); i++) { // loop on modules
            if (hists[i][j]->GetEntries()==0) continue;
            TCanvas *c = new TCanvas(Form("c%d_%d", int(i), int(j)), Form("%d_%d", int(i), int(j)), 600, 600);
            // ---------------------- Events ---------------------- 
            
            while (( chEl=(TChainElement*)next() )) {
                fileCounter++;
                if ((skipFiles!=0) && (fileCounter%skipFiles!=0)) continue;
                TFile f(chEl->GetTitle());
                std::cout << "Opening "<<chEl->GetTitle()<<std::endl;
                TTree* eventTree = (TTree*)f.Get("eventTree");
                eventTree->GetBranch("event")->SetAddress(&evt_);
                
                for (Long64_t z=0; z<eventTree->GetEntries(); z++) {
                    if (reduceFraction!=0 && i%reduceFraction!=0) continue;
                    eventTree->GetEntry(z);
                    int del=delay(evt.run, evt.ls);
                    //WBC=168 === WBC="+2"
                    //if (del==65) {
                    //    hists[i][j]->SetLineColor(20);
                    //    hists[i][j]->Draw();
                    //}  
                    //WBC=167 === WBC="+1"
                    if (del==90) {
                        hists[i][j]->SetLineColor(30);
//                         hists[i][j]->Draw("SAME");
//                         gPad->Update();
                    }
                    //WBC=169 === WBC="+3"
                    else if (del==40) {
                        hists[i][j]->SetLineColor(40);
//                         hists[i][j]->Draw("SAME");
//                         gPad->Update();
                    }
                    //WBC=166 === WBC="0"
                    else if (del==115) {
                        hists[i][j]->SetLineColor(42);
//                         hists[i][j]->Draw("SAME");
//                         gPad->Update();
                    }
                    //WBC=170 === WBC="+4"
                    else if (del==15) {
                        hists[i][j]->SetLineColor(44);   
//                         hists[i][j]->Draw("SAME");
//                         gPad->Update();
                    }
                    //WBC=165 === WBC="-1"
                    else if (del==140) {
                        hists[i][j]->SetLineColor(46);
//                         hists[i][j]->Draw("SAME");
//                         gPad->Update();
                    }
                }
                hists[i][j]->Draw();
                
s                 gPad->Update();
                
                if (saveRecHits) {
                    c->SaveAs(Form("%s%s%s", save_dir.c_str(), hists[i][j]->GetName(),format));
                    c->SaveAs(Form("%s%s%s", save_dir.c_str(), hists[i][j]->GetName(),".C"));
                }
            }
        }
    }
    std::vector<double> maxis(hists[0].size(), FLT_MIN);
    std::vector<double> minis(hists[0].size(), FLT_MAX);
    
    for (size_t j=0; j<hists[0].size(); j++) { // loop on plots
        for (size_t i=0; i<hists.size(); i++) { // loop on modules
            if (detids[i]<300000000) continue;
            if (hists[i][j]->GetEntries()==0) continue;
            if (hists[i][j]->GetBinContent(hists[i][j]->GetMaximumBin()) > maxis[j]) maxis[j]=hists[i][j]->GetBinContent(hists[i][j]->GetMaximumBin());
            if (hists[i][j]->GetBinContent(hists[i][j]->GetMinimumBin()) < minis[j]) minis[j]=hists[i][j]->GetBinContent(hists[i][j]->GetMinimumBin());
        }
        std::cout<<"Plots like "<<hists[0][j]->GetName()<<" have overall minimums of "<<minis[j]<<" and maximum of "<<maxis[j]<<std::endl;
    }
    
    for (size_t j=0; j<hists[0].size(); j++) { // loop on plots
        std::string n=Form("%s", hists[0][j]->GetName());
        n.erase(n.find_last_of("_"));
        std::cout<<n<<std::endl;
        std::string t=Form("%s", hists[0][j]->GetTitle());
        t.erase(t.find_last_of(" in ")-6);
        std::cout<<t<<std::endl;
        
        TCanvas *c = new TCanvas(n.c_str(), t.c_str(), 600, 600);
        c->Draw();
        if (hists[0][j]->GetDimension()==1) hists[0][j]->SetAxisRange(minis[j], maxis[j]*1.1, "Y");
        TH1 *h = (TH1*) hists[0][j]->Clone("h");
        h->Reset();
        h->SetTitle(t.c_str());
        h->Draw();
        //TLegend *l = new TLegend(0.55, 0.15, 0.89, 0.30, "Modules");
        TLegend *l = new TLegend(0.15, 0.70, 0.49, 0.85, "Modules");
        l->SetLineColor(0);
        for (size_t i=0; i<hists.size(); i++) { // loop on modules
            if (detids[i]<300000000) continue;
            if (hists[i][j]->GetEntries()==0) continue;
            if (hists[0][j]->GetDimension()==1) {
                hists[i][j]->Draw("SAMEP");
            } else hists[i][j]->Draw("SAME");
            l->AddEntry(hists[i][j], name(detids[i]).c_str());
            std::cout<<name(detids[i]).c_str()<<std::endl;
            gPad->Update();
        }
        l->Draw();
    }
}

int main(int argc, char* argv[]) {
    
    //   gStyle->SetOptStat(1100);
    //   gStyle->SetOptTitle(1);
    bool saveAll = true;
    std::string save_dir = "./";
    const char* format = ".png";
    
    TChain* filechain = new TChain("filechain");
    //filechain->Add("/data/vami/projects/0RootFiles/2016H/PB-Ntuples/Runs283834-283835_ZeroBias/Fidu3/nTuplePilotBlade_All_19.root");
    filechain->Add("/data/vami/projects/0RootFiles/2016H/PB-Ntuples/Runs283834-283835_ZeroBias/Fidu3/*.root");
    //filechain->Add("/data/vami/projects/pilotBlade/uTCA-data/GlobalRuns/CMSSW_8_0_20_patch1/src/0crab/3Ntuple/Runs283834-283835/crab_PilotBlade_data_Ntuplizer_pp_Runs283834-283835_CMSSW8020_ZeroBias_Fidu3_v2/results/*.root");
    //filechain->Add("/data/vami/projects/0RootFiles/2016H/PB-Ntuples/Runs283834-283835_Express/nTuplePilotBlade_All_1.root");

    rechits(saveAll, "./rechits/", format, filechain);
}
