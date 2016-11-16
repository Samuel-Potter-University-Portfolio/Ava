#pragma once

#include "GameFramework/Character.h"
#include "AvaAICharacter.h"
#include "AvaMonster.generated.h"

UCLASS()
class AVA_API AAvaMonster : public AAvaAICharacter
{
	GENERATED_BODY()

public:
	AAvaMonster();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	
};
