#include "ProceduralSpiderEditor.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"
#include "../Private/Visualizers/FootPlacementComponentVisualizer.h"
#include "ProceduralSpider/Components/FootPlacementComponent.h"
#include "../Private/Visualizers/FootPlacementManagerComponentVisualizer.h"
#include "ProceduralSpider/Components/FootPlacementManagerComponent.h"

IMPLEMENT_GAME_MODULE(FProceduralSpiderEditorModule, ProceduralSpiderEditor);

DEFINE_LOG_CATEGORY(ProceduralSpiderEditor)

#define LOCTEXT_NAMESPACE "ProceduralSpiderEditor"

void FProceduralSpiderEditorModule::StartupModule() {
	UE_LOG(ProceduralSpiderEditor, Warning, TEXT("ProceduralSpiderEditor: Startup"));

	if (GUnrealEd != NULL) {
		AddVisualizer<FFootPlacementComponentVisualizer>(UFootPlacementComponent::StaticClass()->GetFName());
		AddVisualizer<FFootPlacementManagerComponentVisualizer>(UFootPlacementManagerComponent::StaticClass()->GetFName());
	}
}

template <typename T>
void FProceduralSpiderEditorModule::AddVisualizer(FName ComponentClassName) {
	TSharedPtr<T> Visualizer = MakeShareable(new T());
	if (Visualizer.IsValid()) {
		GUnrealEd->RegisterComponentVisualizer(ComponentClassName, Visualizer);
		Visualizer->OnRegister();
	}
}

void FProceduralSpiderEditorModule::ShutdownModule() {
	UE_LOG(ProceduralSpiderEditor, Warning, TEXT("ProceduralSpiderEditor: Shutdown"));

	if (GUnrealEd != NULL) {
		GUnrealEd->UnregisterComponentVisualizer(UFootPlacementComponent::StaticClass()->GetFName());
		GUnrealEd->UnregisterComponentVisualizer(UFootPlacementManagerComponent::StaticClass()->GetFName());
	}
}

#undef LOCTEXT_NAMESPACE