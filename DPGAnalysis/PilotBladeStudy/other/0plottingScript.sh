mkdir clusters
mkdir rechits
wget https://raw.githubusercontent.com/tvami/cmssw80X-PilotBlade/PilotBladeStudy/DPGAnalysis/PilotBladeStudy/other/Makefile
wget https://raw.githubusercontent.com/tvami/cmssw80X-PilotBlade/PilotBladeStudy/DPGAnalysis/PilotBladeStudy/other/Makefile.arch
wget https://raw.githubusercontent.com/tvami/cmssw80X-PilotBlade/PilotBladeStudy/DPGAnalysis/PilotBladeStudy/other/PilotHistoMaker.C
wget https://raw.githubusercontent.com/tvami/cmssw80X-PilotBlade/PilotBladeStudy/DPGAnalysis/PilotBladeStudy/other/PilotHistoMaker.h
cd /data/vami/projects/pilotBlade/uTCA-data/GlobalRuns/CMSSW_8_0_20_patch1/src
cmsenv
cd -
make clean
make -Wsign-compare
./PilotHistoMaker 
cd clusters
mkdir Cs
mv *.C Cs/.
cd ..
cd rechits
mkdir Cs
mv *.C Cs/.
