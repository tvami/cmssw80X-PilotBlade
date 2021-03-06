import FWCore.ParameterSet.Config as cms

caloConfigSource = cms.ESSource(
    "EmptyESSource",
    recordName = cms.string('L1TCaloConfigRcd'),
    iovIsRunNotTime = cms.bool(True),
    firstValid = cms.vuint32(1)
)

caloConfig = cms.ESProducer(
    "L1TCaloConfigESProducer",
    l1Epoch         = cms.string("Stage1"),
    fwVersionLayer2 = cms.uint32(3)  ## 1=HI algo, 2= pp algo (obsolete), 3= pp algo in HW
)
