mkdir digis
mkdir clusters
mkdir rechits
cd /data/vami/projects/pilotBlade/uTCA-data/GlobalRuns/CMSSW_8_0_20_patch1/src
cmsenv
cd -
make clean
make -Wsign-compare
./PilotHistoMaker
cd clusters/
mkdir Cs
mv *.C Cs/.
cd ..
cd rechits/
mkdir Cs
mv *.C Cs/.
cd ..
