// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class UE_MABINOGI_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	APlayerCharacter();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// Character input Function // 
private:

	void MoveCameraStart(const FInputActionValue& InputValue);
	void CameraMode();

	void Move(const FInputActionValue& InputValue);




private:
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
	class USpringArmComponent* SpringArm;

protected:
	UPROPERTY(EditAnywhere , Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* CameraAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* Action;
	

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UCOptionComponent* Option;



	// Character input Function // 


protected:

	bool IsCamearaMode = false;

};
