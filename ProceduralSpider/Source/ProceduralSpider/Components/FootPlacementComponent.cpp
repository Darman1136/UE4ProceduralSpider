#include "FootPlacementComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

UFootPlacementComponent::UFootPlacementComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UFootPlacementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UWorld* World = GetWorld();
	if (World) {
		if (TraceLocations.Num() > 1) {
			TArray<FVector> LocationInWorld = GetTraceLocationsWorld();
			for (int32 index = 0; index < LocationInWorld.Num() - 1; index++) {
				FVector Start = LocationInWorld[index];
				FVector End = LocationInWorld[index + 1];

				FHitResult Hit;
				World->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility);
				//DrawDebugLine(World, Start, End, FColor::Green, false, 1.f);

				if (Hit.bBlockingHit) {
					//DrawDebugSphere(World, Hit.Location, 10, 32, FColor::Red, false, 1.f);
					ActivePlacementVector = Hit.Location;
					break;
				}
			}
		}
	}
}

TArray<FVector> UFootPlacementComponent::GetTraceLocationsWorld() const {
	TArray<FVector> LocationInWorld;
	FRotator RotationInWorld = GetComponentRotation() - GetAttachParent()->RelativeRotation;
	for (FVector Vec : TraceLocations) {
		LocationInWorld.Add(RotationInWorld.RotateVector(Vec) + GetComponentLocation());
	}
	return LocationInWorld;
}
