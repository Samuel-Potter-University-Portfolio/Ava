#pragma once

#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "AvaCharacter.h"
#include "AvaAICharacter.generated.h"

UCLASS()
class AVA_API AAvaAICharacter : public ACharacter
{
	GENERATED_BODY()
private:
	bool bAgro;

protected:
	UPawnSensingComponent* pawn_sensor;

public:
	AAvaAICharacter();

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

private:
	UFUNCTION()
	void OnSeePawn(APawn* pawn);

	UFUNCTION()
	void OnHearPawn(APawn *OtherActor, const FVector &Location, float Volume);

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnSeePlayer(const AAvaCharacter* player);

	UFUNCTION(BlueprintImplementableEvent)
	void OnHearPlayer(const AAvaCharacter *OtherActor, const FVector &Location, float Volume);
	
	UFUNCTION(BlueprintPure, Category ="Ava|AI")
	FORCEINLINE bool IsAgro() { return bAgro; }
};
