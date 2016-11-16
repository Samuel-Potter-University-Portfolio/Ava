#include "Ava.h"
#include "AvaMonster.h"


AAvaMonster::AAvaMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	UCapsuleComponent* capsule = GetCapsuleComponent();
	capsule->InitCapsuleSize(34.f, 95.0f);

	UCharacterMovementComponent* movement = GetCharacterMovement();
	movement->GetNavAgentPropertiesRef().bCanCrouch = false;
	movement->MaxWalkSpeed = 360.0f;
}

void AAvaMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAvaMonster::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AAvaMonster::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

