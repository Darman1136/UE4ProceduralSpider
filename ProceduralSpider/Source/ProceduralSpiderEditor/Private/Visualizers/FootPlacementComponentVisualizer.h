
#pragma once

#include "ComponentVisualizer.h"
#include "ProceduralSpider/Components/FootPlacementComponent.h"

class FFootPlacementComponentVisualizer : public FComponentVisualizer {

public:
	virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;
};
