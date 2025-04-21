#!/bin/bash

echo "running cmsrel..."

cmsrel CMSSW_12_5_0_pre5

cd CMSSW_12_5_0_pre5/src

cmsenv

echo "retrieving packages from git..."

git cms-addpkg HLTrigger/Configuration

git cms-addpkg L1Trigger/L1TGlobal

mkdir -p L1Trigger/L1TGlobal/data/Luminosity/startup/ && cd L1Trigger/L1TGlobal/data/Luminosity/startup/

echo "retrieving L1 menu..."

wget https://raw.githubusercontent.com/mitaylor/HIMenus/main/Menus/L1Menu_CollisionsHeavyIons2022_v0_0_0.xml

cd $CMSSW_BASE/src

echo "retrieving more info from git..."

git cms-merge-topic denerslemos:HLTBitAna_CMSSW_12_5_X

echo "compiling code..."

scram b -j 8

cd HLTrigger/Configuration/test && mkdir workstation && cd workstation

echo "done!"




