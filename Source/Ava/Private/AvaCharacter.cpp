// Fill out your copyright notice in the Description page of Project Settings.

#include "Ava.h"
#include "AvaCharacter.h"


AAvaCharacter::AAvaCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	UCapsuleComponent* capsule = GetCapsuleComponent();
	capsule->InitCapsuleSize(30.f, 80.0f);

	camera_boom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	camera_boom->SocketOffset = FVector(-30.0f, 0, 75.0f);
	camera_boom->bUsePawnControlRotation = true;
	camera_boom->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	camera->SetupAttachment(camera_boom);

	UCharacterMovementComponent* movement = GetCharacterMovement();
	movement->GetNavAgentPropertiesRef().bCanCrouch = true;
	movement->MaxWalkSpeed = 270.0f;
	movement->MaxWalkSpeedCrouched = 115.0f;
	movement->CrouchedHalfHeight = 50.0f;
}

void AAvaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAvaCharacter::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);

	const float unit_speed = GetUnitSpeed();
	//Camera boom move
	{
		last_lerp_value = last_lerp_value * 0.93f + unit_speed * 0.07f;
		const float offset = bIsCrouched ? camera_crouch_offset * last_lerp_value : 0;
		const float distance = min_camera_distance * (1.0f - last_lerp_value) + max_camera_distance * last_lerp_value - offset;
		camera_boom->SocketOffset = FVector(distance, 0, 65.0f);
	}

	//Smooth movement
	if(frame_input_count)
	{
		frame_input_dir.Normalize();

		movement_vector = turn_factor * frame_input_dir + movement_vector * (1.0f - turn_factor);
		movement_vector.Normalize();

		AddMovementInput(movement_vector, frame_input_factor / (float)frame_input_count);

		frame_input_dir = FVector::ZeroVector;
		frame_input_factor = 0;
		frame_input_count = 0;
	}
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
		FRotator rotation = camera_boom->GetComponentRotation();

		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
			rotation.Pitch = 0.0f;
		
		if (value < 0)
		{
			frame_input_dir -= FRotationMatrix(rotation).GetScaledAxis(EAxis::X);
			frame_input_factor -= value;
		}
		else
		{
			frame_input_dir += FRotationMatrix(rotation).GetScaledAxis(EAxis::X);
			frame_input_factor += value;
		}
		frame_input_count++;
	}
}

void AAvaCharacter::Input_MoveRight(float value)
{
	if (Controller && value)
	{
		FRotator rotation = camera_boom->GetComponentRotation();

		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
			rotation.Pitch = 0.0f;
		
		if (value < 0)
		{
			frame_input_dir -= FRotationMatrix(rotation).GetScaledAxis(EAxis::Y);
			frame_input_factor -= value;
		}
		else
		{
			frame_input_dir += FRotationMatrix(rotation).GetScaledAxis(EAxis::Y);
			frame_input_factor += value;
		}
		frame_input_count++;
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
	{
		if (!bIsCrouched)
			Crouch();
		else
			UnCrouch();
	}
}

void AAvaCharacter::InputEnd_Crouch()
{
	
}

float AAvaCharacter::GetUnitSpeed()
{
	const float max_speed = GetCharacterMovement()->GetMaxSpeed();
	return max_speed ? GetVelocity().Size() / max_speed : 0;
}