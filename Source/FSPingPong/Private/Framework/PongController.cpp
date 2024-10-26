#include "Framework/PongController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"


void APongController::PawnLeavingGame()
{
	return;
}

void APongController::Move(const FInputActionValue& Value)
{
	float MoveDirection = Value.Get<float>();
	APawn* PossesedPawn = GetPawn();
	if (!IsValid(PossesedPawn)) return;
	
	PossesedPawn->AddMovementInput(MoveDirection * PossesedPawn->GetActorRightVector());
}

void APongController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (const ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(PongMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APongController::Move);
	}
}
