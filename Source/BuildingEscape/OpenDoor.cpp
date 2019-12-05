// Copyright Cyle Ven Dawson 2019


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

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Door = GetOwner();
	float CurrentTime = GetWorld()->GetTimeSeconds();

	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
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

