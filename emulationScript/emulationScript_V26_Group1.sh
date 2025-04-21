#!/bin/bash

##### FILE 150 ###################################################
echo "running hltGetConfiguration (file 150)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_150.root  --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py

echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_150.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

##### FILE 151 ###################################################
echo "running hltGetConfiguration (file 151)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_151.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_151.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

##### FILE 152 ###################################################
echo "running hltGetConfiguration (file 152)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_152.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_152.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

##### FILE 154 ###################################################
echo "running hltGetConfiguration (file 154)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_154.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_154.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

##### FILE 155 ###################################################
echo "running hltGetConfiguration (file 155)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_155.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_155.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

##### FILE 156 ###################################################
echo "running hltGetConfiguration (file 156)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_156.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_156.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

##### FILE 157 ###################################################
echo "running hltGetConfiguration (file 157)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_157.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_157.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

##### FILE 158 ###################################################
echo "running hltGetConfiguration (file 158)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_158.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_158.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

##### FILE 159 ###################################################
echo "running hltGetConfiguration (file 159)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_159.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_159.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

##### FILE 16 ###################################################
echo "running hltGetConfiguration (file 16)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_16.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_16.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

##### FILE 160 ###################################################
echo "running hltGetConfiguration (file 160)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_160.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_160.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

##### FILE 161 ###################################################
echo "running hltGetConfiguration (file 161)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_161.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_161.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

##### FILE 162 ###################################################
echo "running hltGetConfiguration (file 162)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_162.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_162.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

##### FILE 163 ###################################################
echo "running hltGetConfiguration (file 163)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_163.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_163.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root

##### FILE 164 ###################################################
echo "running hltGetConfiguration (file 164)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_164.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_164.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root



##### FILE 165 ###################################################
echo "running hltGetConfiguration (file 165)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_165.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_165.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root



##### FILE 166 ###################################################
echo "running hltGetConfiguration (file 166)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_166.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_166.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root



##### FILE 167 ###################################################
echo "running hltGetConfiguration (file 167)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_167.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_167.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root



##### FILE 168 ###################################################
echo "running hltGetConfiguration (file 168)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_168.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_168.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root



##### FILE 169 ###################################################
echo "running hltGetConfiguration (file 169)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_169.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_169.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root



##### FILE 17 ###################################################
echo "running hltGetConfiguration (file 17)..."

hltGetConfiguration /users/cbennett/HLT_jetTriggerAnalysis_slim/V26  --globaltag auto:phase1_2023_realistic_hi --l1Xml L1Menu_CollisionsHeavyIons2022_v1_1_0.xml --l1-emulator uGT  --era Run3  --input root://cmsxrootd.fnal.gov//store/user/mnguyen/Run3MC/QCD_pThat15_Run3_HydjetEmbedded/QCD_pThat15_Run3_HydjetEmbedded_DIGI/220225_125759/0000/step2_DIGI_L1_DIGI2RAW_HLT_PU_17.root --process MyHLT --full --mc --unprescale --no-output --max-events -1 > ExportedMenu.py


echo "editing ExportedMenu.py..."

echo '
# Define the output
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("drop *", "keep *_TriggerResults_*_*", "keep *_hltTriggerSummaryAOD_*_*", "keep *_hltGtStage2Digis_*_*", "keep *_hltGtStage2ObjectMap_*_*"),
    fileName = cms.untracked.string("output.root"),
)
process.output_path = cms.EndPath(process.output)

process.schedule.append( process.output_path )  # enable this line if you want to get an output containing trigger info to be used for further analysis, e.g. "TriggerResults", digis etc

' >> ExportedMenu.py

echo "deleting lines in ExportedMenu.py..."

sed -in '12195,12210d' ExportedMenu.py; rm ExportedMenu.pyn;

echo "running the menu..."

cmsRun ExportedMenu.py &> menulog.txt

echo "creating Macro.py..."

echo '
import FWCore.ParameterSet.Config as cms
process = cms.Process("HLTANA")

# Input source
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring("file:output.root"))

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, "auto:phase1_2023_realistic_hi", "")

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

echo "running the code..."

cmsRun Macro.py &> macrolog.txt

echo "copying openHLT.root into files folder..."

cp openHLT.root files/openHLT_17.root

echo "deleting files..."

rm DQMIO.root ExportedMenu.py Macro.py macrolog.txt menulog.txt openHLT.root output.root
