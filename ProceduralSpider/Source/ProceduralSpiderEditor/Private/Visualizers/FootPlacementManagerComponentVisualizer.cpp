#include "FootPlacementManagerComponentVisualizer.h"
#include "SceneManagement.h"

void FFootPlacementManagerComponentVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) {
	if (const UFootPlacementManagerComponent* FPMComponent = Cast<const UFootPlacementManagerComponent>(Component)) {
		PDI->DrawPoint(FPMComponent->GetFallbackTraceLocation(), FColor::Green, 10.f, SDPG_Foreground);
	}
}

