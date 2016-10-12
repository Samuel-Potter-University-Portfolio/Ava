// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AvaCharacter.generated.h"

UCLASS()
class AVA_API AAvaCharacter : public ACharacter
{
	GENERATED_BODY()
private:
	FVector movement_vector;
	FVector frame_input_dir;
	float frame_input_factor;
	int frame_input_count;

protected:
	UCameraComponent* camera;
	USpringArmComponent* camera_boom;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float turn_factor = 0.2f;

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

	UFUNCTION(BlueprintPure, Category = "Ava|Player")
	float GetUnitSpeed();
	
	UPROPERTY(EditAnywhere)
	float max_camera_distance = 20;
	UPROPERTY(EditAnywhere)
	float min_camera_distance = 60;
	UPROPERTY(EditAnywhere)
	float camera_crouch_offset = -70;

	float last_lerp_value = 0.0f;
};
