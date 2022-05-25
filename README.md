# triggerAnalysis
Code for HLT analysis work.

Heavily borrows from https://github.com/CmsHI/ElectroWeak-Jet-Track-Analyses.git, including the event matching method, configuration, and design.

# How to run
All the files necessary to run the code are in the /Performance/objects folder.  Simply run "root -l triggerAnalysis.C" in  that folder.

# Files contained
pythiahydjet.root - This is the HiForestMiniAOD file with the jet information.

openHLT.root - This is the trigger emulation file.

triggerAnalysis.conf - This is the configuration file, designed to be read by the "ConfigurationParser" object.

# Logic & Problems

The code begins here https://github.com/claytoniousfunk/triggerAnalysis/blob/ab514d6b3e6af7dc415fc6383fddfb107585473d/Performance/objects/triggerAnalysis.C#L173 We open up the 3 main files, listed above.

We read the configuration here https://github.com/claytoniousfunk/triggerAnalysis/blob/ab514d6b3e6af7dc415fc6383fddfb107585473d/Performance/objects/triggerAnalysis.C#L188  I had some problems with the ConfigurationParser and could not get it to properly load the trigger list.  As a work-around, I hard coded the list of triggers into the code here https://github.com/claytoniousfunk/triggerAnalysis/blob/ab514d6b3e6af7dc415fc6383fddfb107585473d/Performance/objects/triggerAnalysis.C#L624  We print the configuration to see that everything is configured properly.

We parse the input data files (even though in this case we only have one), define some trees that may be of interest, count and ouput the number of files to be analyzed, and print out the hiForest information, done here https://github.com/claytoniousfunk/triggerAnalysis/blob/ab514d6b3e6af7dc415fc6383fddfb107585473d/Performance/objects/triggerAnalysis.C#L200-L238

We then define indices for our trigger branches and get the HLT object names, here https://github.com/claytoniousfunk/triggerAnalysis/blob/ab514d6b3e6af7dc415fc6383fddfb107585473d/Performance/objects/triggerAnalysis.C#L255-L314

We then open up the HLT trigger file that was generated from the emulation process, here https://github.com/claytoniousfunk/triggerAnalysis/blob/ab514d6b3e6af7dc415fc6383fddfb107585473d/Performance/objects/triggerAnalysis.C#L321-L343

We then define the trigger values for our list of triggers through the triggerAnalyzer::setBranchesTrigger function, here https://github.com/claytoniousfunk/triggerAnalysis/blob/ab514d6b3e6af7dc415fc6383fddfb107585473d/Performance/objects/triggerAnalysis.C#L345-L346

We then create a map of events for event matching with an EventMatcher object, here https://github.com/claytoniousfunk/triggerAnalysis/blob/ab514d6b3e6af7dc415fc6383fddfb107585473d/Performance/objects/triggerAnalysis.C#L370-L401

We then loop through the events from the reco forest file and match events, here https://github.com/claytoniousfunk/triggerAnalysis/blob/ab514d6b3e6af7dc415fc6383fddfb107585473d/Performance/objects/triggerAnalysis.C#L461-L514

However, I am getting stuck on an error here https://github.com/claytoniousfunk/triggerAnalysis/blob/ab514d6b3e6af7dc415fc6383fddfb107585473d/Performance/objects/triggerAnalysis.C#L549.  The input trigger bits are crashing the code, or something I dont fully understand is wrong with my configuration or reading of the triggerBits.




