#include "detector.hh"


MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name) {}

MySensitiveDetector::~MySensitiveDetector() {}


G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {

    G4Track *track = aStep->GetTrack();
    track->SetTrackStatus(fStopAndKill);


    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();


    G4ThreeVector posPhoton = preStepPoint->GetPosition();

    //G4cout <<" PHOTON POSITION: "<< posPhoton <<G4endl; // display all orginal position of the photons/ coordinates(display position when photon entern into detector)


    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    G4int copyNo = touchable->GetCopyNumber(); //copy number construction

    // G4cout << "Copy number of detector: "<< copyNo << G4endl; //display copy Number(the number of the detector that fired- mapping of touches)


    G4VPhysicalVolume *physVol = touchable->GetVolume(); // access the real pos.
    G4ThreeVector posDetector = physVol->GetTranslation();// get the exact position of the detectors/voxels

    G4cout << "Detector Position: " << posDetector << G4endl; //display the real pos.

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleIColumn(0, evt);

    man->FillNtupleDColumn(1, posDetector[0]);
    man->FillNtupleDColumn(2, posDetector[1]);
    man->FillNtupleDColumn(3, posDetector[2]);

    man->AddNtupleRow(0);

    return true;
}

