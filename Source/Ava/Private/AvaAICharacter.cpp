#include "Ava.h"
#include "AvaAICharacter.h"


AAvaAICharacter::AAvaAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	pawn_sensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sensor"));
	pawn_sensor->SetPeripheralVisionAngle(70.0f);
	pawn_sensor->OnSeePawn.AddDynamic(this, &AAvaAICharacter::OnSeePawn);
	pawn_sensor->OnHearNoise.AddDynamic(this, &AAvaAICharacter::OnHearPawn);
}

void AAvaAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAvaAICharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AAvaAICharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}


void AAvaAICharacter::OnSeePawn(APawn* pawn) 
{
	AAvaCharacter* player = Cast<AAvaCharacter>(pawn);
	if (player)
	{
		if (!bAgro)
		{
			bAgro = true;
			OnSeePlayer(player);
		}
	}
}

void AAvaAICharacter::OnHearPawn(APawn *OtherActor, const FVector &Location, float Volume) 
{

}