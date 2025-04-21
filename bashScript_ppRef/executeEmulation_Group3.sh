#!/bin/bash

echo "~~~~~~  running hltGetConfiguration (file 12/53) ~~~~~~"

hltGetConfiguration /users/cbennett/HLT_ppRef/V2 --globaltag auto:phase1_2022_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v0_0_0.xml --l1-emulator FullMC --era Run3 --input root://cmsxrootd.fnal.gov//store/user/katatar/run3/run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI/CRAB_UserFiles/crab_run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI_userInput/220906_145055/0000/step2_DIGI_12.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

sed -n '12961,12976d' ExportedMenu.py

echo " -- running ExportedMenu.py ... ---"

cmsRun ExportedMenu.py &> menulog.txt

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:run2_hlt_relval", "")

# add HLTBitAnalyzer
process.load("HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi")
process.hltanalysis.hltResults = cms.InputTag("TriggerResults::MyHLT")
process.hltanalysis.l1tAlgBlkInputTag = cms.InputTag("hltGtStage2Digis::MyHLT")
process.hltanalysis.l1tExtBlkInputTag = cms.InputTag("hltGtStage2Digis::MyHLT")

process.load("HeavyIonsAnalysis.EventAnalysis.hltobject_cfi")
process.hltobject.triggerResults = cms.InputTag("TriggerResults::MyHLT")
process.hltobject.triggerEvent = cms.InputTag("hltTriggerSummaryAOD::MyHLT")

process.hltAnalysis = cms.EndPath(process.hltanalysis + process.hltobject)
process.TFileService = cms.Service("TFileService", fileName=cms.string("openHLT.root"))
' &> Macro.py

echo " -- running Macro.py ... ---"

cmsRun Macro.py &> macrolog.txt

cp openHLT.root files/openHLT_12.root

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

echo "done."
echo " ".


echo "~~~~~~  running hltGetConfiguration (file 13/53) ~~~~~~"

hltGetConfiguration /users/cbennett/HLT_ppRef/V2 --globaltag auto:phase1_2022_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v0_0_0.xml --l1-emulator FullMC --era Run3 --input root://cmsxrootd.fnal.gov//store/user/katatar/run3/run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI/CRAB_UserFiles/crab_run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI_userInput/220906_145055/0000/step2_DIGI_13.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

sed -n '12961,12976d' ExportedMenu.py

echo " -- running ExportedMenu.py ... ---"

cmsRun ExportedMenu.py &> menulog.txt

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:run2_hlt_relval", "")

# add HLTBitAnalyzer
process.load("HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi")
process.hltanalysis.hltResults = cms.InputTag("TriggerResults::MyHLT")
process.hltanalysis.l1tAlgBlkInputTag = cms.InputTag("hltGtStage2Digis::MyHLT")
process.hltanalysis.l1tExtBlkInputTag = cms.InputTag("hltGtStage2Digis::MyHLT")

process.load("HeavyIonsAnalysis.EventAnalysis.hltobject_cfi")
process.hltobject.triggerResults = cms.InputTag("TriggerResults::MyHLT")
process.hltobject.triggerEvent = cms.InputTag("hltTriggerSummaryAOD::MyHLT")

process.hltAnalysis = cms.EndPath(process.hltanalysis + process.hltobject)
process.TFileService = cms.Service("TFileService", fileName=cms.string("openHLT.root"))
' &> Macro.py

echo " -- running Macro.py ... ---"

cmsRun Macro.py &> macrolog.txt

cp openHLT.root files/openHLT_13.root

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

echo "done."
echo " ".


echo "~~~~~~  running hltGetConfiguration (file 14/53) ~~~~~~"

hltGetConfiguration /users/cbennett/HLT_ppRef/V2 --globaltag auto:phase1_2022_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v0_0_0.xml --l1-emulator FullMC --era Run3 --input root://cmsxrootd.fnal.gov//store/user/katatar/run3/run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI/CRAB_UserFiles/crab_run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI_userInput/220906_145055/0000/step2_DIGI_14.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

sed -n '12961,12976d' ExportedMenu.py

echo " -- running ExportedMenu.py ... ---"

cmsRun ExportedMenu.py &> menulog.txt

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:run2_hlt_relval", "")

# add HLTBitAnalyzer
process.load("HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi")
process.hltanalysis.hltResults = cms.InputTag("TriggerResults::MyHLT")
process.hltanalysis.l1tAlgBlkInputTag = cms.InputTag("hltGtStage2Digis::MyHLT")
process.hltanalysis.l1tExtBlkInputTag = cms.InputTag("hltGtStage2Digis::MyHLT")

process.load("HeavyIonsAnalysis.EventAnalysis.hltobject_cfi")
process.hltobject.triggerResults = cms.InputTag("TriggerResults::MyHLT")
process.hltobject.triggerEvent = cms.InputTag("hltTriggerSummaryAOD::MyHLT")

process.hltAnalysis = cms.EndPath(process.hltanalysis + process.hltobject)
process.TFileService = cms.Service("TFileService", fileName=cms.string("openHLT.root"))
' &> Macro.py

echo " -- running Macro.py ... ---"

cmsRun Macro.py &> macrolog.txt

cp openHLT.root files/openHLT_14.root

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

echo "done."
echo " ".


echo "~~~~~~  running hltGetConfiguration (file 15/53) ~~~~~~"

hltGetConfiguration /users/cbennett/HLT_ppRef/V2 --globaltag auto:phase1_2022_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v0_0_0.xml --l1-emulator FullMC --era Run3 --input root://cmsxrootd.fnal.gov//store/user/katatar/run3/run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI/CRAB_UserFiles/crab_run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI_userInput/220906_145055/0000/step2_DIGI_15.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

sed -n '12961,12976d' ExportedMenu.py

echo " -- running ExportedMenu.py ... ---"

cmsRun ExportedMenu.py &> menulog.txt

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:run2_hlt_relval", "")

# add HLTBitAnalyzer
process.load("HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi")
process.hltanalysis.hltResults = cms.InputTag("TriggerResults::MyHLT")
process.hltanalysis.l1tAlgBlkInputTag = cms.InputTag("hltGtStage2Digis::MyHLT")
process.hltanalysis.l1tExtBlkInputTag = cms.InputTag("hltGtStage2Digis::MyHLT")

process.load("HeavyIonsAnalysis.EventAnalysis.hltobject_cfi")
process.hltobject.triggerResults = cms.InputTag("TriggerResults::MyHLT")
process.hltobject.triggerEvent = cms.InputTag("hltTriggerSummaryAOD::MyHLT")

process.hltAnalysis = cms.EndPath(process.hltanalysis + process.hltobject)
process.TFileService = cms.Service("TFileService", fileName=cms.string("openHLT.root"))
' &> Macro.py

echo " -- running Macro.py ... ---"

cmsRun Macro.py &> macrolog.txt

cp openHLT.root files/openHLT_15.root

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

echo "done."
echo " ".


echo "~~~~~~  running hltGetConfiguration (file 16/53) ~~~~~~"

hltGetConfiguration /users/cbennett/HLT_ppRef/V2 --globaltag auto:phase1_2022_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v0_0_0.xml --l1-emulator FullMC --era Run3 --input root://cmsxrootd.fnal.gov//store/user/katatar/run3/run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI/CRAB_UserFiles/crab_run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI_userInput/220906_145055/0000/step2_DIGI_16.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

sed -n '12961,12976d' ExportedMenu.py

echo " -- running ExportedMenu.py ... ---"

cmsRun ExportedMenu.py &> menulog.txt

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:run2_hlt_relval", "")

# add HLTBitAnalyzer
process.load("HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi")
process.hltanalysis.hltResults = cms.InputTag("TriggerResults::MyHLT")
process.hltanalysis.l1tAlgBlkInputTag = cms.InputTag("hltGtStage2Digis::MyHLT")
process.hltanalysis.l1tExtBlkInputTag = cms.InputTag("hltGtStage2Digis::MyHLT")

process.load("HeavyIonsAnalysis.EventAnalysis.hltobject_cfi")
process.hltobject.triggerResults = cms.InputTag("TriggerResults::MyHLT")
process.hltobject.triggerEvent = cms.InputTag("hltTriggerSummaryAOD::MyHLT")

process.hltAnalysis = cms.EndPath(process.hltanalysis + process.hltobject)
process.TFileService = cms.Service("TFileService", fileName=cms.string("openHLT.root"))
' &> Macro.py

echo " -- running Macro.py ... ---"

cmsRun Macro.py &> macrolog.txt

cp openHLT.root files/openHLT_16.root

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

echo "done."
echo " ".


echo "~~~~~~  running hltGetConfiguration (file 17/53) ~~~~~~"

hltGetConfiguration /users/cbennett/HLT_ppRef/V2 --globaltag auto:phase1_2022_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v0_0_0.xml --l1-emulator FullMC --era Run3 --input root://cmsxrootd.fnal.gov//store/user/katatar/run3/run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI/CRAB_UserFiles/crab_run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI_userInput/220906_145055/0000/step2_DIGI_17.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

sed -n '12961,12976d' ExportedMenu.py

echo " -- running ExportedMenu.py ... ---"

cmsRun ExportedMenu.py &> menulog.txt

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:run2_hlt_relval", "")

# add HLTBitAnalyzer
process.load("HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi")
process.hltanalysis.hltResults = cms.InputTag("TriggerResults::MyHLT")
process.hltanalysis.l1tAlgBlkInputTag = cms.InputTag("hltGtStage2Digis::MyHLT")
process.hltanalysis.l1tExtBlkInputTag = cms.InputTag("hltGtStage2Digis::MyHLT")

process.load("HeavyIonsAnalysis.EventAnalysis.hltobject_cfi")
process.hltobject.triggerResults = cms.InputTag("TriggerResults::MyHLT")
process.hltobject.triggerEvent = cms.InputTag("hltTriggerSummaryAOD::MyHLT")

process.hltAnalysis = cms.EndPath(process.hltanalysis + process.hltobject)
process.TFileService = cms.Service("TFileService", fileName=cms.string("openHLT.root"))
' &> Macro.py

echo " -- running Macro.py ... ---"

cmsRun Macro.py &> macrolog.txt

cp openHLT.root files/openHLT_17.root

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

echo "done."
echo " ".
