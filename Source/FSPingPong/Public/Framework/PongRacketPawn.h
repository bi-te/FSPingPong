// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PongRacketPawn.generated.h"

UCLASS()
class FSPINGPONG_API APongRacketPawn : public APawn
{
	GENERATED_BODY()

public:
	APongRacketPawn();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> RacketMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Racket")
	float Speed;
	
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void Server_UpdatePosition(FVector DeltaLocation);
	
public:	
	virtual void Tick(float DeltaTime) override;

};
