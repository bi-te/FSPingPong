#include "Framework/PongRacketPawn.h"

APongRacketPawn::APongRacketPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);

	RacketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RacketMesh"));
	RootComponent = RacketMesh;
}

void APongRacketPawn::BeginPlay()
{
	Super::BeginPlay();	
}

void APongRacketPawn::Server_UpdatePosition_Implementation(FVector DeltaLocation)
{
	AddActorWorldOffset(DeltaLocation, true);
}

void APongRacketPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector PengingInput = ConsumeMovementInputVector().GetClampedToMaxSize(1.f);
	if (PengingInput.IsZero()) return;

	FVector DeltaLocation = PengingInput * Speed * DeltaTime;
	AddActorWorldOffset(DeltaLocation, true);
	Server_UpdatePosition(DeltaLocation);
}





