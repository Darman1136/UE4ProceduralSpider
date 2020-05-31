#include "FootPlacementComponentVisualizer.h"
#include "SceneManagement.h"

void FFootPlacementComponentVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) {
	if (const UFootPlacementComponent* FPComponent = Cast<const UFootPlacementComponent>(Component)) {
		const TArray<FVector> TraceLocations = FPComponent->GetTraceLocationsWorld();
		for (int32 index = 0; index < TraceLocations.Num() - 1; index++) {
			FVector Start = TraceLocations[index];
			FVector End = TraceLocations[index + 1];

			PDI->DrawLine(Start, End, FColor::Red, SDPG_Foreground);
			PDI->DrawPoint(Start, FColor::White, 10.f, SDPG_Foreground);
		}
		PDI->DrawPoint(TraceLocations[TraceLocations.Num() - 1], FColor::White, 10.f, SDPG_Foreground);
	}
}
