#pragma once

#include "ComponentVisualizer.h"
#include "ProceduralSpider/Components/FootPlacementManagerComponent.h"

class FFootPlacementManagerComponentVisualizer : public FComponentVisualizer {

public:
	virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;


};
