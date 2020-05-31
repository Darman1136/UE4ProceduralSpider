#include "ProceduralSpiderEditor.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"
#include "../Private/Visualizers/FootPlacementComponentVisualizer.h"
#include "ProceduralSpider/Components/FootPlacementComponent.h"

IMPLEMENT_GAME_MODULE(FProceduralSpiderEditorModule, ProceduralSpiderEditor);

DEFINE_LOG_CATEGORY(ProceduralSpiderEditor)

#define LOCTEXT_NAMESPACE "ProceduralSpiderEditor"

void FProceduralSpiderEditorModule::StartupModule() {
	UE_LOG(ProceduralSpiderEditor, Warning, TEXT("ProceduralSpiderEditor: Startup"));

	if (GUnrealEd != NULL) {
		TSharedPtr<FFootPlacementComponentVisualizer> Visualizer = MakeShareable(new FFootPlacementComponentVisualizer());
		if (Visualizer.IsValid()) {
			GUnrealEd->RegisterComponentVisualizer(UFootPlacementComponent::StaticClass()->GetFName(), Visualizer);
			Visualizer->OnRegister();
		}
	}
}

void FProceduralSpiderEditorModule::ShutdownModule() {
	UE_LOG(ProceduralSpiderEditor, Warning, TEXT("ProceduralSpiderEditor: Shutdown"));

	if (GUnrealEd != NULL) {
		GUnrealEd->UnregisterComponentVisualizer(UFootPlacementComponent::StaticClass()->GetFName());
	}
}

#undef LOCTEXT_NAMESPACE