#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameMode.generated.h"

class APongGameState;
class APongBall;
class APongRacketPawn;

UCLASS()
class FSPINGPONG_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> BallClass;

	virtual void BeginPlay() override;
	
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

private:
	UPROPERTY()
	TArray<APongRacketPawn*> PongRackets;

	UPROPERTY()
	TObjectPtr<APongGameState> PongGameState;

	UPROPERTY()
	TObjectPtr<APongBall> SpawnedBall;

	FVector FirstPlayerDirection;

	UPROPERTY(EditDefaultsOnly)
	FVector BallSpawnPosition = FVector(0, 0, 60);
	
	UPROPERTY(EditDefaultsOnly)
	FName PlayAreaCollisionBoxTag = FName("PlayAreaCollisionBox");

	void StartGame();
	void StopGame();

	UFUNCTION()
	void OnBallOutsidePlayArea(AActor* OverlappedActor, AActor* OtherActor);
};
