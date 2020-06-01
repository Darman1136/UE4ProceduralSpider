// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProceduralSpiderGameMode.h"
#include "ProceduralSpiderCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProceduralSpiderGameMode::AProceduralSpiderGameMode() {
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character/SpiderCharacter"));
	if (PlayerPawnBPClass.Class != NULL) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
