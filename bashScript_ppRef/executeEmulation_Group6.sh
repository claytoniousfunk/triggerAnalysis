#!/bin/bash

echo "~~~~~~  running hltGetConfiguration (file 30/53) ~~~~~~"

hltGetConfiguration /users/cbennett/HLT_ppRef/V2 --globaltag auto:phase1_2022_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v0_0_0.xml --l1-emulator FullMC --era Run3 --input root://cmsxrootd.fnal.gov//store/user/katatar/run3/run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI/CRAB_UserFiles/crab_run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI_userInput/220906_145055/0000/step2_DIGI_30.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py

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

cp openHLT.root files/openHLT_30.root

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

echo "done."
echo " ".


echo "~~~~~~  running hltGetConfiguration (file 31/53) ~~~~~~"

hltGetConfiguration /users/cbennett/HLT_ppRef/V2 --globaltag auto:phase1_2022_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v0_0_0.xml --l1-emulator FullMC --era Run3 --input root://cmsxrootd.fnal.gov//store/user/katatar/run3/run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI/CRAB_UserFiles/crab_run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI_userInput/220906_145055/0000/step2_DIGI_31.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py

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

cp openHLT.root files/openHLT_31.root

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

echo "done."
echo " ".


echo "~~~~~~  running hltGetConfiguration (file 32/53) ~~~~~~"

hltGetConfiguration /users/cbennett/HLT_ppRef/V2 --globaltag auto:phase1_2022_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v0_0_0.xml --l1-emulator FullMC --era Run3 --input root://cmsxrootd.fnal.gov//store/user/katatar/run3/run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI/CRAB_UserFiles/crab_run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI_userInput/220906_145055/0000/step2_DIGI_32.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py

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

cp openHLT.root files/openHLT_32.root

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

echo "done."
echo " ".


echo "~~~~~~  running hltGetConfiguration (file 33/53) ~~~~~~"

hltGetConfiguration /users/cbennett/HLT_ppRef/V2 --globaltag auto:phase1_2022_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v0_0_0.xml --l1-emulator FullMC --era Run3 --input root://cmsxrootd.fnal.gov//store/user/katatar/run3/run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI/CRAB_UserFiles/crab_run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI_userInput/220906_145055/0000/step2_DIGI_33.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py

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

cp openHLT.root files/openHLT_33.root

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

echo "done."
echo " ".


echo "~~~~~~  running hltGetConfiguration (file 34/53) ~~~~~~"

hltGetConfiguration /users/cbennett/HLT_ppRef/V2 --globaltag auto:phase1_2022_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v0_0_0.xml --l1-emulator FullMC --era Run3 --input root://cmsxrootd.fnal.gov//store/user/katatar/run3/run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI/CRAB_UserFiles/crab_run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI_userInput/220906_145055/0000/step2_DIGI_34.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py

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

cp openHLT.root files/openHLT_34.root

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

echo "done."
echo " ".


echo "~~~~~~  running hltGetConfiguration (file 35/53) ~~~~~~"

hltGetConfiguration /users/cbennett/HLT_ppRef/V2 --globaltag auto:phase1_2022_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v0_0_0.xml --l1-emulator FullMC --era Run3 --input root://cmsxrootd.fnal.gov//store/user/katatar/run3/run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI/CRAB_UserFiles/crab_run3_pp22_privateMC_QCDPhoton15_pythia8_5p36TeV_DIGI_userInput/220906_145055/0000/step2_DIGI_35.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py

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

cp openHLT.root files/openHLT_35.root

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

echo "done."
echo " ".
