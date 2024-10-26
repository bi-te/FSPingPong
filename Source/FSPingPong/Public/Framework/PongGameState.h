#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PongGameState.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayersScoreUpdated, uint32, uint32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, bool);

UCLASS()
class FSPINGPONG_API APongGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	FOnPlayersScoreUpdated OnPlayersScoreUpdated;
	FOnGameStateChanged OnGameStateChanged;
	
	UPROPERTY(ReplicatedUsing = OnRep_PlayerScore)
	TArray<uint32> PlayersScore;

	UPROPERTY(ReplicatedUsing = OnRep_IsWaiting)
	bool bIsWaiting = false;

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	UFUNCTION()
	void OnRep_PlayerScore();

	UFUNCTION()
	void OnRep_IsWaiting();
};
