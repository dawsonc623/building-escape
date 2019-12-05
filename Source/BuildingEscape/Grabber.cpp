// Copyright Cyle Ven Dawson 2019


#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("GRABBY GRABBY"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector	PlayerLocation;
	FRotator PlayerRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerLocation,
		PlayerRotator
	);

	FVector GrabEnd = PlayerLocation + PlayerRotator.Vector() * Reach;

	// Printing ray

	FColor LineTraceColor(255, 0, 0);

	DrawDebugLine(
		GetWorld(),
		PlayerLocation,
		GrabEnd,
		LineTraceColor,
		false,
		0.0f,
		0,
		5
	);

	// Find an object to grab

	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerLocation,
		GrabEnd,
		FCollisionObjectQueryParams(
			ECollisionChannel::ECC_PhysicsBody
		),
		FCollisionQueryParams(
			FName(TEXT("")),
			false,
			GetOwner()
		)
	);

	AActor* HitActor = Hit.GetActor();

	if (HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabbing %s"), *(Hit.GetActor()->GetName()))
	}
}

