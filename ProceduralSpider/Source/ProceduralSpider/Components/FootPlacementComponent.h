#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FootPlacementComponent.generated.h"


UCLASS(ClassGroup = (Custom), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class PROCEDURALSPIDER_API UFootPlacementComponent : public USceneComponent {
	GENERATED_BODY()

public:
	UFootPlacementComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Trace locations in world space and rotation relative
	TArray<FVector> GetTraceLocationsWorld() const;

	// Trace locations relative to its parent
	TArray<FVector> GetTraceLocations() const { return TraceLocations; };

	// Currently calculated position for IK in world space
	UFUNCTION(BlueprintCallable)
		FVector GetActivePlacementVector() const { return ActivePlacementVector; };

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FVector> TraceLocations;

	FVector ActivePlacementVector;
};
