from DQM.EcalBarrelMonitorClient.PNIntegrityClient_cfi import ecalPnIntegrityClient
from DQM.EcalBarrelMonitorClient.LaserClient_cfi import ecalLaserClient
from DQM.EcalBarrelMonitorClient.LedClient_cfi import ecalLedClient
from DQM.EcalBarrelMonitorClient.TestPulseClient_cfi import ecalTestPulseClient
from DQM.EcalBarrelMonitorClient.PedestalClient_cfi import ecalPedestalClient

ecalCalibrationSummaryClient = dict(
#    laserWavelengths = [1, 2, 3, 4],
    laserWavelengths = [3],
#    ledWavelengths = [1, 2],
#    testPulseMGPAGains = [1, 6, 12],
    testPulseMGPAGains = [12],
#    testPulseMGPAGainsPN = [1, 16],
    testPulseMGPAGainsPN = [16],
#    pedestalMGPAGains = [1, 6, 12],
#    pedestalMGPAGainsPN = [1, 16],
    activeSources = ["Laser", "Led", "TestPulse"],
    MEs = dict(
        QualitySummary = dict(path = '%(subdet)s/%(prefix)sSummaryClient/%(prefix)s global calibration quality%(suffix)s', otype = 'Ecal3P', btype = 'SuperCrystal', kind = 'TH2F'),
        PNQualitySummary = dict(path = '%(subdet)s/%(prefix)sSummaryClient/%(prefix)s PN global quality', otype = 'MEM2P', btype = 'Crystal', kind = 'TH2F')
    ),
    sources = dict(
        PNIntegrity = ecalPnIntegrityClient['MEs']['QualitySummary'],
        Laser = ecalLaserClient['MEs']['QualitySummary'],
        LaserPN = ecalLaserClient['MEs']['PNQualitySummary'],
        Led = ecalLedClient['MEs']['QualitySummary'],
        LedPN = ecalLedClient['MEs']['PNQualitySummary'],
        TestPulse = ecalTestPulseClient['MEs']['QualitySummary'],
        TestPulsePN = ecalTestPulseClient['MEs']['PNQualitySummary'],
        Pedestal = ecalPedestalClient['MEs']['QualitySummary'],
        PedestalPN = ecalPedestalClient['MEs']['PNQualitySummary']
    )
)
    
