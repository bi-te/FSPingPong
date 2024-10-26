#include "Framework/PongGameState.h"

#include "Net/UnrealNetwork.h"

void APongGameState::BeginPlay()
{
	Super::BeginPlay();

	PlayersScore.SetNum(2);
}

void APongGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APongGameState, PlayersScore);
	DOREPLIFETIME(APongGameState, bIsWaiting);
}

void APongGameState::OnRep_PlayerScore()
{
	OnPlayersScoreUpdated.Broadcast(PlayersScore[0], PlayersScore[1]);
}

void APongGameState::OnRep_IsWaiting()
{
	OnGameStateChanged.Broadcast(bIsWaiting);
}
