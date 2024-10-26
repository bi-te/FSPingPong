#include "Framework/PongGameMode.h"

#include "Actors/PongBall.h"
#include "Framework/PongGameState.h"
#include "Framework/PongRacketPawn.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogPongGameMode, Log, All);

void APongGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(this, APongRacketPawn::StaticClass(), reinterpret_cast<TArray<AActor*>&>(PongRackets));
	checkf(PongRackets.Num() == 2, TEXT("number of racket on level must be 2"));

	FirstPlayerDirection = PongRackets[0]->GetActorLocation() - BallSpawnPosition;
	FirstPlayerDirection.Normalize();
	
	PongGameState = Cast<APongGameState>(GameState);
	checkf(IsValid(PongGameState), TEXT("game state is not subclass of PongGameState"));
}

void APongGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 PlayersNum = GetNumPlayers();
	if (PlayersNum > 2) return;
	
	for (const auto& Racket : PongRackets)
	{
		if (!Racket->IsPlayerControlled())
		{
			NewPlayer->Possess(Racket);
			break;
		}
	}
	
	if (PlayersNum == 2)
	{
		StartGame();
		PongGameState->bIsWaiting = false;
	}
	else
	{
		PongGameState->bIsWaiting = true;
	}
}

void APongGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	int32 PlayersNum = GetNumPlayers() - 1;
	PongGameState->bIsWaiting = PlayersNum == 1;

	if (PlayersNum < 2)
	{
		StopGame();
	}
}

void APongGameMode::StartGame()
{
	UWorld* World = GetWorld();
	if (!IsValid(World)) return;

	TArray<AActor*> PlayAreaActors;
	UGameplayStatics::GetAllActorsWithTag(this, PlayAreaCollisionBoxTag, PlayAreaActors);
	checkf(PlayAreaActors.Num() > 0 && IsValid(PlayAreaActors[0]),TEXT("Play area was not found"));
	PlayAreaActors[0]->OnActorEndOverlap.AddDynamic(this, &APongGameMode::OnBallOutsidePlayArea);
	
	SpawnedBall = World->SpawnActor<APongBall>(BallClass, BallSpawnPosition, FRotator(0));
	checkf(IsValid(SpawnedBall), TEXT("ball was not spawned"));
}

void APongGameMode::StopGame()
{
	SpawnedBall->Destroy();
}

void APongGameMode::OnBallOutsidePlayArea(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor != SpawnedBall) return;
	
	FVector ScoredVector = OtherActor->GetActorLocation() - BallSpawnPosition;	
	PongGameState->PlayersScore[ScoredVector.Dot(FirstPlayerDirection) > 0 ? 1 : 0] += 1;

	SpawnedBall->SetActorLocation(BallSpawnPosition);
}
