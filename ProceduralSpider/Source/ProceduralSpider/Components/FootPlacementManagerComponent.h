// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "FootPlacementManagerComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROCEDURALSPIDER_API UFootPlacementManagerComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UFootPlacementManagerComponent();

	float GetStepDelay() const { return StepDelay; };

	FVector GetFallbackTraceLocation() const { return FallbackTraceLocation; };

	FVector GetFallbackTraceLocationWorld() const { return GetOwner()->GetActorRotation().RotateVector(FallbackTraceLocation) + GetOwner()->GetActorLocation(); };

protected:
	// Delay between each step for foot placements, updates DesiredPlacementVector (in seconds)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float StepDelay = .10f;

	// Fallback trace location to check against if the normal traces didn't find a satisfiable location. (Usually the very bottom of the actor)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector FallbackTraceLocation;
};
