// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AvaCharacter.generated.h"

UCLASS()
class AVA_API AAvaCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	UCameraComponent* camera;
	USpringArmComponent* camera_boom;

public:
	AAvaCharacter();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void Input_MoveForward(float value);
	virtual void Input_MoveRight(float value);
	virtual void Input_LookUp(float value);
	virtual void Input_LookRight(float value);
	virtual void InputStart_Jump();
	virtual void InputEnd_Jump();
	virtual void InputStart_Crouch();
	virtual void InputEnd_Crouch();
};
