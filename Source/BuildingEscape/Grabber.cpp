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
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	BindPhysicsHandleComponent();
	BindInputComponent();
}

void UGrabber::BindPhysicsHandleComponent()
{
	AActor* Actor = GetOwner();

	PhysicsHandle = Actor->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find Physics Handle for %s"), *(Actor->GetName()))
	}
}

void UGrabber::BindInputComponent()
{
	AActor* Actor = GetOwner();

	Input = Actor->FindComponentByClass<UInputComponent>();

	if (Input)
	{
		Input->BindAction(
			"Grab",
			IE_Pressed,
			this,
			&UGrabber::Grab
		);

		Input->BindAction(
			"Grab",
			IE_Released,
			this,
			&UGrabber::Release
		);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find Input component for %s"), *(Actor->GetName()))
	}
}

void UGrabber::Grab()
{
	// Calculate reach

	FVector	PlayerLocation;
	FRotator PlayerRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerLocation,
		PlayerRotator
	);

	FVector GrabEnd = PlayerLocation + PlayerRotator.Vector() * Reach;

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
		GrabbedActor = HitActor;
		UE_LOG(LogTemp, Warning, TEXT("Grabbing %s"), *(HitActor->GetName()))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Nothing to grab"))
	}
}

void UGrabber::Release()
{
	if (GrabbedActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Releasing %s"), *(GrabbedActor->GetName()))
		GrabbedActor = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Nothing to release"))
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
