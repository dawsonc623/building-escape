// Copyright Cyle Ven Dawson 2019


#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing a PressurePlate"), *(GetOwner()->GetName()))
	}
}

float UOpenDoor::GetMassOnPlate()
{
	float TotalMass = 0.0f;

	if (PressurePlate)
	{
		TArray<AActor*> OverlappingActors;

		PressurePlate->GetOverlappingActors(
			OverlappingActors
		);

		for (AActor* Actor : OverlappingActors)
		{
			TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}

	return TotalMass;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Door = GetOwner();
	float CurrentTime = GetWorld()->GetTimeSeconds();

	if (GetMassOnPlate() >= 30)
	{
		Door->SetActorRotation(
			FRotator(
				0.0f,
				OpenAngle,
				0.0f
			)
		);

		LastDoorOpenTime = CurrentTime;
	}
	// TODO Do not close if the door is already closed
	else if (CurrentTime - LastDoorOpenTime > CloseDoorDelay)
	{
		Door->SetActorRotation(
			FRotator(
				0.0f,
				0.0f,
				0.0f
			)
		);
	}
}

