#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongBall.generated.h"

UCLASS()
class FSPINGPONG_API APongBall : public AActor
{
	GENERATED_BODY()
	
public:	
	APongBall();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> BallMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	FVector DefaultDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float Speed;

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(Replicated)
	FVector Velocity;
};
