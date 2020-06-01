#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TimerManager.h"
#include "FootPlacementManagerComponent.h"
#include "ProceduralSpiderGameMode.h"
#include "FootPlacementComponent.generated.h"


struct TraceResult {
	bool Valid;
	FVector Location;

	TraceResult() {
		this->Valid = false;
		this->Location = FVector();
	}

	TraceResult(FVector Location) {
		this->Valid = true;
		this->Location = Location;
	}
};

UCLASS(ClassGroup = (Custom), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class PROCEDURALSPIDER_API UFootPlacementComponent : public USceneComponent {
	GENERATED_BODY()

public:
	UFootPlacementComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Trace locations in world space and rotation relative
	TArray<FVector> GetTraceLocationsWorld(TArray<FVector> Locations) const;

	// Trace locations relative to its parent (idle foot location)
	TArray<FVector> GetTraceLocations() const { return TraceLocations; };

	// Gait trace locations relative to its parent (next forward step foot location)
	TArray<FVector> GetGaitTraceLocations() const { return GaitTraceLocations; };

	// Currently calculated position for IK in world space
	UFUNCTION(BlueprintCallable)
		FVector GetActivePlacementVector() const { return ActivePlacementVector; };

	bool IsExtendLastTrace() const { return ExtendLastTrace; };

	float GetExtendLastTraceDistance() const { return ExtendLastTraceDistance; };

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
		virtual void UpdateActivePlacementVector();

	bool IsOnGround();

	TraceResult Trace(const UWorld* World, FVector Start, FVector End) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FVector> TraceLocations;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FVector> GaitTraceLocations;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 StartUpOrderNumber = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool ExtendLastTrace = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "ExtendLastTrace"))
		float ExtendLastTraceDistance = 40.f;

private:
	bool IsDrawDebug() const {
		return ProceduralSpiderGameMode && ProceduralSpiderGameMode->IsDrawDebug();
	}

private:
	class AProceduralSpiderGameMode* ProceduralSpiderGameMode;

	class UFootPlacementManagerComponent* FootPlacementManager;

	class UCharacterMovementComponent* CharacterMovementComponent;

	FTimerHandle UpdateActivePlacementVectorTimerHandle;

	// Active location for the foot to be placed at. Considers moving geo.
	FVector ActivePlacementVector;

	// Desired location, updated every StepDelay
	FVector DesiredPlacementVector;
};
