#include "FootPlacementComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

UFootPlacementComponent::UFootPlacementComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UFootPlacementComponent::BeginPlay() {
	Super::BeginPlay();

	ProceduralSpiderGameMode = Cast<AProceduralSpiderGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetOwner()->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	FootPlacementManager = Cast<UFootPlacementManagerComponent>(GetOwner()->GetComponentByClass(UFootPlacementManagerComponent::StaticClass()));
	checkf(FootPlacementManager, TEXT("Actor [%s] missing UFootPlacementManagerComponent"), *GetOwner()->GetName());

	int32 FootComponentCount = GetOwner()->GetComponentsByClass(UFootPlacementComponent::StaticClass()).Num();
	GetWorld()->GetTimerManager().SetTimer(UpdateActivePlacementVectorTimerHandle, this, &UFootPlacementComponent::UpdateActivePlacementVector, FootComponentCount * FootPlacementManager->GetStepDelay(), true, StartUpOrderNumber * FootPlacementManager->GetStepDelay());
}

void UFootPlacementComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void UFootPlacementComponent::UpdateActivePlacementVector() {
	ActivePlacementVector = DesiredPlacementVector;
}

void UFootPlacementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UWorld* World = GetWorld();
	if (World) {
		// Are trace locations set up?
		if (GaitTraceLocations.Num() > 1 && TraceLocations.Num() > 1) {
			// Are we standing or moving
			TArray<FVector> LocationInWorld;
			if (FMath::IsNearlyZero(GetOwner()->GetVelocity().Size()) && IsOnGround()) {
				LocationInWorld = GetTraceLocationsWorld(TraceLocations);
			} else {
				LocationInWorld = GetTraceLocationsWorld(GaitTraceLocations);
			}

			TraceResult FoundTraceResult;
			for (int32 index = 0; index < LocationInWorld.Num() - 1; index++) {
				FVector Start = LocationInWorld[index];
				FVector End = LocationInWorld[index + 1];
				FoundTraceResult = Trace(World, Start, End);
				if (FoundTraceResult.Valid) break;
			}

			if (!FoundTraceResult.Valid && ExtendLastTrace) {
				// Didn't find a normal foot placement location, try to find one by extending last trace location
				FVector Start = LocationInWorld[LocationInWorld.Num() - 1];
				FVector End = Start + GetOwner()->GetActorUpVector() * -1.f * ExtendLastTraceDistance;
				FoundTraceResult = Trace(World, Start, End);
			}

			// Didn't find a normal foot placement location, try to find one from last trace location to location specified in FootPlacementManager. Maybe we're standing over an edge.
			if (!FoundTraceResult.Valid) {
				FVector Start = LocationInWorld[LocationInWorld.Num() - 1];
				FVector End = FootPlacementManager->GetFallbackTraceLocationWorld();
				FoundTraceResult = Trace(World, Start, End);
			}

			if (FoundTraceResult.Valid) {
				DesiredPlacementVector = FoundTraceResult.Location;
			} else {
				// No location found, fallback to default location
				DesiredPlacementVector = LocationInWorld[LocationInWorld.Num() - 1];
			}
		}
	}
}

TraceResult UFootPlacementComponent::Trace(const UWorld* World, FVector Start, FVector End) const {
	FHitResult Hit;
	World->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility);
	if (IsDrawDebug()) DrawDebugLine(World, Start, End, FColor::Green, false, 1.f);

	if (Hit.bBlockingHit) {
		if (IsDrawDebug()) DrawDebugSphere(World, Hit.Location, 10, 8, FColor::Red, false, 1.f);
		return TraceResult(Hit.Location);
	}
	return TraceResult();
}

TArray<FVector> UFootPlacementComponent::GetTraceLocationsWorld(TArray<FVector> Locations) const {
	TArray<FVector> LocationInWorld;
	FRotator RotationInWorld = GetComponentRotation() - GetAttachParent()->RelativeRotation;
	for (FVector Vec : Locations) {
		LocationInWorld.Add(RotationInWorld.RotateVector(Vec) + GetComponentLocation());
	}
	return LocationInWorld;
}

bool UFootPlacementComponent::IsOnGround() {
	if (!CharacterMovementComponent) return true;

	return !CharacterMovementComponent->IsFalling();
}
