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

#include "PilotLSHistoMaker.h"

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
// -----------------------------Digis---------------------------------------
// ---------------------------------------------------------------------------
void digis(bool saveAll, std::string save_dir, const char* format, TChain* filechain, int runNumber)
{
    
    bool saveDigis = 0;
    if (saveAll) saveDigis = 1;
    Long64_t reduceFraction=0;
    Int_t skipFiles=0;
    
    int _detids[] = { 344132868, 344134148, 344131076, 344132100, 344130820, 1, 344131844 };
    //int _detids[] = { 344130820, 344131844, 344132868, 344133892, 344131076, 344132100, 344133124, 344134148, 1 };
    std::vector<int> detids(_detids, _detids + sizeof(_detids) / sizeof(int) );
    
    std::map<int,int> idx_map;
    for (size_t i=0; i<detids.size(); i++) {
        idx_map[detids[i]]=i;
        std::cout << "define detector id " << detids[i] << " as " << idx_map[detids[i]]<<std::endl;
    }
    const std::map<int,int>& idx = idx_map;
    
    // Create the histograms
    std::vector<std::vector<TH1*> > hists;    
    std::vector<TProfile *> PBDigiVsLS;
    
    for (size_t imod=0; imod<detids.size(); imod++) {
        std::vector<TH1*> vh;
        TH1 *h;
        PBDigiVsLS.push_back((TProfile*)(h=new TProfile(Form("PBDigiVsLS_%d", detids[imod]),  Form("Avg num of pixels per event vs LumiSection in %s;LumiSection;Avg num of pixels", name(detids[imod]).c_str()), 150, 0, 150, 0, 100))); vh.push_back(h);
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
    
    TObjArray* fileElements = filechain->GetListOfFiles();
    TIter next(fileElements);
    TChainElement* chEl=0;
    Int_t fileCounter=0;
    
    while (( chEl=(TChainElement*)next() )) {
        fileCounter++;
        if ((skipFiles!=0) && (fileCounter%skipFiles!=0)) continue;
        TFile f(chEl->GetTitle());
        std::cout << "Opening "<<chEl->GetTitle()<<std::endl;
        
        // ---------------------- Digis ---------------------- 
        
        TTree* digiTree = (TTree*)f.Get("digiTree");
        digiTree->GetBranch("digi")->SetAddress(&digi);
        digiTree->GetBranch("module_on")->SetAddress(&module_on);
        digiTree->GetBranch("event")->SetAddress(&evt);
        
        std::vector<int> currentEvent(detids.size(), -1);
        std::vector<std::pair<int,int> > currentRunLs;
        for (size_t ii=0; ii<currentEvent.size(); ii++) currentRunLs.push_back(std::make_pair(-1, -1));
        std::vector<int> digiCounter(detids.size(), 0);
        
        for (Long64_t i=0, ndigi=digiTree->GetEntries(); i<ndigi; ++i) {
            if (reduceFraction!=0 && i%reduceFraction!=0) continue;
            digiTree->GetEntry(i);
            if (module_on.disk!=-3 && !(module_on.disk==-2 && (module_on.blade==-10 || module_on.blade==-11)) ) continue;
            
            int rawid=module_on.rawid;
            if (module_on.disk==-2) rawid=1;
            
            std::map<int,int>::const_iterator it_idx=idx.find(rawid);
            if (it_idx==idx.end()) continue;
            int imod = it_idx->second;
            if (evt.run!=runNumber) continue;
            
            if (evt.evt!=currentEvent[imod]) {
                if (currentEvent[imod]!=-1) PBDigiVsLS[imod]->Fill(evt.ls, digiCounter[imod]);
                currentEvent[imod]=evt.evt;
                digiCounter[imod]=0;
            }
            ++digiCounter[imod];
        }
        
        // ---------------------- Events ---------------------- 
        TTree* eventTree = (TTree*)f.Get("eventTree");
        eventTree->GetBranch("event")->SetAddress(&evt_);
        
        for (Long64_t i=0; i<eventTree->GetEntries(); i++) {
            if (reduceFraction!=0 && i%reduceFraction!=0) continue;
            eventTree->GetEntry(i);
        }
        
        
        // -------------------------------------------- 
    } // End of loop on files
    
    // Create the canvas and save
    
    for (size_t j=0; j<hists[0].size(); j++) { // loop on plots
        for (size_t i=0; i<hists.size(); i++) { // loop on modules
            if (hists[i][j]->GetEntries()==0) continue;
            TCanvas *c = new TCanvas(Form("c%d_%d", int(i), int(j)), Form("%d_%d", int(i), int(j)), 600, 600);
            hists[i][j]->Draw();
            gPad->Update();
            if (saveDigis) {
                c->SaveAs(Form("%s%s_Run%s%s", save_dir.c_str(), hists[i][j]->GetName(), (std::to_string(runNumber)).c_str(),format));
                c->SaveAs(Form("%s%s_Run%s%s", save_dir.c_str(), hists[i][j]->GetName(), (std::to_string(runNumber)).c_str(),".C"));
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
        if (saveDigis) {
            c->SaveAs(Form("%sAll_%s_Run%s%s", save_dir.c_str(), n.c_str(), (std::to_string(runNumber)).c_str(), format));
            c->SaveAs(Form("%sAll_%s_Run%s%s", save_dir.c_str(), n.c_str(), (std::to_string(runNumber)).c_str(), ".C"));
        }
    }
}

// ---------------------------------------------------------------------------
// -----------------------------Clusters---------------------------------------
// ---------------------------------------------------------------------------
void clusters(bool saveAll, std::string save_dir, const char* format, TChain* filechain, int runNumber)
{
    bool saveClusters = 0;
    if (saveAll) saveClusters = 1;
    Long64_t reduceFraction=0;
    Int_t skipFiles=0;
    
    int _detids[] = { 344132868, 344134148, 344131076, 344132100, 344130820, 1, 344131844 };
    //int _detids[] = { 344130820, 344131844, 344132868, 344133892, 344131076, 344132100, 344133124, 344134148, 1 };
    std::vector<int> detids(_detids, _detids + sizeof(_detids) / sizeof(int) );
    
    std::map<int,int> idx_map;
    for (size_t i=0; i<detids.size(); i++) {
        idx_map[detids[i]]=i;
        std::cout << "define detector id " << detids[i] << " as " << idx_map[detids[i]]<<std::endl;
    }
    const std::map<int,int>& idx = idx_map;
    
    // Create the histograms
    std::vector<std::vector<TH1*> > hists;
    
    std::vector<TProfile *> PBClusterChargeVsLS;
    std::vector<TProfile *> PBClusterSizeVsLS;
    std::vector<TProfile *> PBClustersVsLS;
    
    
    
    for (uint imod=0; imod<detids.size(); imod++) {
        
        std::vector<TH1*> vh;
        TH1 *h;
        
        PBClusterChargeVsLS.push_back((TProfile*)(h=new TProfile(Form("PBClusterChargeVsLS_%d", uint(detids[imod])),  Form("Avg cluster charge vs LumiSection in %s;LumiSection;Avg cluster charge", name(uint(detids[imod])).c_str()), 150, 0, 150, 0, 150))); vh.push_back(h);
        PBClusterSizeVsLS.push_back((TProfile*)(h=new TProfile(Form("PBClusterSizeVsLS_%d", uint(detids[imod])),  Form("Avg cluster size vs LumiSection in %s;LumiSection;Avg cluster size", name(uint(detids[imod])).c_str()), 150, 0, 150, 0, 15))); vh.push_back(h);
        PBClustersVsLS.push_back((TProfile*)(h=new TProfile(Form("PBClustersVsLS_%d", uint(detids[imod])),  Form("Avg num of clusters per event vs LumiSection in %s;LumiSection;Avg num of clusters", name(uint(detids[imod])).c_str()), 150, 0, 150, 0, 100))); vh.push_back(h);
        
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
    
    TObjArray* fileElements = filechain->GetListOfFiles();
    TIter next(fileElements);
    TChainElement* chEl=0;
    Int_t fileCounter=0;
    
    while (( chEl=(TChainElement*)next() )) {
        fileCounter++;
        if ((skipFiles!=0) && (fileCounter%skipFiles!=0)) continue;
        TFile f(chEl->GetTitle());
        std::cout << "Opening "<<chEl->GetTitle()<<std::endl;
        TTree* clustTree = (TTree*)f.Get("clustTree");
        clustTree->GetBranch("clust")->SetAddress(&clusters);
        clustTree->GetBranch("module_on")->SetAddress(&module_on);
        clustTree->GetBranch("event")->SetAddress(&evt);
        
        std::vector<int> currentEvent(detids.size(), -1);
        std::vector<std::pair<int,int> > currentRunLs;
        for (size_t ii=0; ii<currentEvent.size(); ii++) currentRunLs.push_back(std::make_pair(-1, -1));
        for (size_t i=0; i<currentEvent.size(); i++) currentEvent[i]=-1;
        std::vector<int> clusterCounter(detids.size(), 0);
        for (Long64_t i=0, nclust=clustTree->GetEntries(); i<nclust; ++i) {
            if (reduceFraction!=0 && i%reduceFraction!=0) continue;
            clustTree->GetEntry(i);
            if (evt.run!=runNumber) continue;
            if (module_on.disk!=-3 && !(module_on.disk==-2 && (module_on.blade==-10 || module_on.blade==-11)) ) continue;
            size_t rawid=module_on.rawid;
            if (module_on.disk==-2) rawid=1;
            
            std::map<int,int>::const_iterator it_idx=idx.find(rawid);
            if (it_idx==idx.end()) continue;
            int imod = it_idx->second;
            // if we want the disk2 modules before the PB then include:
            if((module_on.disk==-3) || (module_on.disk==-2 && module_on.blade==-11) ) {
                PBClusterChargeVsLS[imod]->Fill(evt.ls,clusters.charge);
                PBClusterSizeVsLS[imod]->Fill(evt.ls,clusters.size);
                if (evt.evt!=currentEvent[imod]) {
                    if (currentEvent[imod]!=-1) {
                        std::map<int,int>::const_iterator it_idx=idx.find(1);
                    }
                    for (size_t ii=0; ii<currentEvent.size(); ii++) {
                        currentEvent[ii]=evt.evt;
                        currentRunLs[ii].first=evt.run;
                        currentRunLs[ii].second=evt.ls;
                        clusterCounter[ii]=0;
                    }
                }
                ++clusterCounter[imod];  
            }
        }
        
        // ---------------------- Events ---------------------- 
        TTree* eventTree = (TTree*)f.Get("eventTree");
        eventTree->GetBranch("event")->SetAddress(&evt_);
        for (Long64_t i=0; i<eventTree->GetEntries(); i++) {
            if (reduceFraction!=0 && i%reduceFraction!=0) continue;
            eventTree->GetEntry(i);            
        }
        // -------------------------------------------- 
    } // End of loop on files
    
    // Create the canvas and save
    
    for (size_t j=0; j<hists[0].size(); j++) { // loop on plots
        for (size_t i=0; i<hists.size(); i++) { // loop on modules
            if (hists[i][j]->GetEntries()==0) continue;
            TCanvas *c = new TCanvas(Form("c%d_%d", int(i), int(j)), Form("%d_%d", int(i), int(j)), 600, 600);
            hists[i][j]->Draw();
            gPad->Update();
            if (saveClusters) {
                c->SaveAs(Form("%s%s_Run%s%s", save_dir.c_str(), hists[i][j]->GetName(), (std::to_string(runNumber)).c_str(),format));
                c->SaveAs(Form("%s%s_Run%s%s", save_dir.c_str(), hists[i][j]->GetName(), (std::to_string(runNumber)).c_str(),".C"));
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
        if (saveClusters) {
            c->SaveAs(Form("%sAll_%s_Run%s%s", save_dir.c_str(), n.c_str(), (std::to_string(runNumber)).c_str(), format));
            c->SaveAs(Form("%sAll_%s_Run%s%s", save_dir.c_str(), n.c_str(), (std::to_string(runNumber)).c_str(), ".C"));
        }
    }
}


int main(int argc, char* argv[]) {
    
    int runNumber = 283834;
    bool saveAll = true;
    const char* format = ".png";
    
    TChain* filechain = new TChain("filechain");
    filechain->Add("/data/vami/projects/0RootFiles/2016H/PB-Ntuples/Runs283834-283835_Express/*.root");
    //filechain->Add("/data/vami/projects/0RootFiles/2016H/PB-Ntuples/Runs283834-283835_Express/nTuplePilotBlade_All_1.root");
    
    digis(saveAll, "./digis/", format, filechain, runNumber);
    clusters(saveAll, "./clusters/", format, filechain, runNumber);
}
