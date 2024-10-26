#include "Actors/PongBall.h"

#include "Net/UnrealNetwork.h"

APongBall::APongBall()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicatingMovement(true);	

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>("BallMesh");
	BallMesh->SetupAttachment(RootComponent);
	RootComponent = BallMesh;
}

void APongBall::BeginPlay()
{
	Super::BeginPlay();

	DefaultDirection.Normalize();
	Velocity = DefaultDirection * Speed;
}

void APongBall::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APongBall, Velocity);
}

void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FHitResult SweepResult{};
	FVector DeltaLocation = Velocity * DeltaTime;
	bool bMove = true;
	while (bMove)
	{
		AddActorWorldOffset(DeltaLocation, true, &SweepResult);
		if (SweepResult.IsValidBlockingHit())
		{
			FVector RemainingOffset = SweepResult.TraceEnd - SweepResult.Location;
			DeltaLocation = FMath::GetReflectionVector(RemainingOffset, SweepResult.ImpactNormal);
			DeltaLocation.Z = 0.0;
			Velocity = FMath::GetReflectionVector(Velocity, SweepResult.ImpactNormal);
			Velocity.Z = 0.0;
		}
		else
		{
			bMove = false;
		}
	}
	Velocity.Normalize();
	Velocity *= Speed;
}

