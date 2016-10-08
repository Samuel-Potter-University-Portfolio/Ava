// Fill out your copyright notice in the Description page of Project Settings.

#include "Ava.h"
#include "AvaCharacter.h"


AAvaCharacter::AAvaCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(30.f, 80.0f);


	camera_boom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	camera_boom->SocketOffset = FVector(0, 0, 80.0f);
	camera_boom->SocketOffset = FVector(-100, 0, 0.0f);
	camera_boom->bUsePawnControlRotation = true;
	camera_boom->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	camera->SetupAttachment(camera_boom);
}

void AAvaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAvaCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AAvaCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	InputComponent->BindAxis("Move Forward", this, &AAvaCharacter::Input_MoveForward);
	InputComponent->BindAxis("Move Right", this, &AAvaCharacter::Input_MoveRight);
	InputComponent->BindAxis("Look Up", this, &AAvaCharacter::Input_LookUp);
	InputComponent->BindAxis("Look Right", this, &AAvaCharacter::Input_LookRight);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AAvaCharacter::InputStart_Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AAvaCharacter::InputEnd_Jump);

	InputComponent->BindAction("Crouch", IE_Pressed, this, &AAvaCharacter::InputStart_Crouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &AAvaCharacter::InputEnd_Crouch);

	Super::SetupPlayerInputComponent(InputComponent);
}

void AAvaCharacter::Input_MoveForward(float value)
{
	if (Controller && value)
	{
		FRotator rotation = Controller->GetControlRotation();

		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
			rotation.Pitch = 0.0f;

		const FVector direction = FRotationMatrix(rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(direction, value);
	}
}

void AAvaCharacter::Input_MoveRight(float value)
{
	if (Controller && value)
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FVector direction = FRotationMatrix(rotation).GetScaledAxis(EAxis::Y);

		AddMovementInput(direction, value);
	}
}

void AAvaCharacter::Input_LookUp(float value)
{
	if (value)
	{
		AddControllerPitchInput(value);
	}
}

void AAvaCharacter::Input_LookRight(float value)
{
	if (value)
	{
		AddControllerYawInput(value);
	}
}

void AAvaCharacter::InputStart_Jump()
{
	if (GetCharacterMovement()->IsMovingOnGround())
		bPressedJump = true;
}

void AAvaCharacter::InputEnd_Jump()
{
	bPressedJump = false;
}

void AAvaCharacter::InputStart_Crouch()
{
	if (!GetCharacterMovement()->IsFalling())
		bIsCrouched = true;
}

void AAvaCharacter::InputEnd_Crouch()
{
	bIsCrouched = false;
}