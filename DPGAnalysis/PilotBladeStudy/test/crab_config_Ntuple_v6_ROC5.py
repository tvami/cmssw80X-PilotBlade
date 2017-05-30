from CRABClient.UserUtilities import config 
config = config()

config.section_('General')
config.General.requestName = 'PilotBlade_data_Ntuplizer_pA_Runs286520_CMSSW8023_RAW_FiduAlign_ROC5_Margin25_AlignAgain_v1'
config.General.transferOutputs = True
config.General.transferLogs = True

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '3ppReco2Ntuple_CMSSW80X_TrackerZminusOnly_Fidu_ROC5.py'
#config.JobType.maxMemoryMB = 3000
#config.JobType.inputFiles = ['WBCSetup.txt']
config.JobType.inputFiles = ['tracker_alignment_80X_dataRun2_Prompt_v8.db']
config.JobType.outputFiles = ['nTuplePilotBlade_All.root']
config.JobType.allowUndistributedCMSSW = True

config.section_('Data')
#config.Data.inputDBS = 'global'
config.Data.inputDBS = 'phys03'
#NJOBS = 100
#config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.inputDataset = '/ZeroBias/tvami-PilotBlade_pA_data_RECO_Filtered_ZeroBias_RAW-2016HI_Runs286520_CMSSW8023_v1-01d89551f6d39ecac8c03bedefbd04e0/USER'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 10
config.Data.outLFNDirBase = '/store/user/tvami/PB/December/'
config.Data.publication = True
config.Data.outputDatasetTag  = config.General.requestName

config.section_('Site')
#config.Site.whitelist = ['T2_HU_Budapest']
config.Site.storageSite = 'T2_HU_Budapest'
