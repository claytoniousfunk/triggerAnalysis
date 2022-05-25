# triggerAnalysis
Code for HLT analysis work.

Heavily borrows from https://github.com/CmsHI/ElectroWeak-Jet-Track-Analyses.git, including the event matching method, configuration, and design.

# How to run
All the files necessary to run the code are in the /Performance/objects folder.  Simply run "root -l triggerAnalysis.C" in  that folder.

# Files contained
pythiahydjet.root - This is the HiForestMiniAOD file with the jet information.

openHLT.root - This is the trigger emulation file.

triggerAnalysis.conf - This is the configuration file, designed to be read by the "ConfigurationParser" object.

# Problems

At the moment of this writing (5/25/22 17:17 Chicago time), the code is not successfully analyzing the trigger bits.  This problem is still being debuged.



