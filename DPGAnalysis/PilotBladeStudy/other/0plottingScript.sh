mkdir clusters
mkdir rechits
cd /data/vami/projects/pilotBlade/uTCA-data/GlobalRuns/CMSSW_8_0_20_patch1/src
cmsenv
cd -
make clean
make -Wsign-compare
./PilotHistoMaker 
mkdir Cs
mv *.C Cs/.
mv Cs/PilotHistoMaker.C .
