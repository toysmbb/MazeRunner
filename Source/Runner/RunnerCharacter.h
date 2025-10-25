// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Blueprint/UserWidget.h"
#include "UMG_Hud.h"
#include "Switcher.h"
#include "RunnerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class ARunnerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;
    
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UUserWidget> InteractWidgetClass;

	UPROPERTY()
	UUserWidget* InteractWidget;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY()
	UUMG_Hud* HealthBarWidget;
public:

	/** Constructor */
	ARunnerCharacter();	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	

public:

	void Die();

	FHitResult InteractionHitResult;
	FVector ViewVector;
	FRotator ViewRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="HealthBar")
	int32 MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HealthBar")
	int32 CurrentHealth;

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentHealth() { return CurrentHealth; }

	UFUNCTION(BlueprintCallable)
	void ModifyHealth(int32 Delta);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetPercentHealth() const { return (float)CurrentHealth / (float)MaxHealth; }

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	UFUNCTION(BlueprintCallable, Category="Input")
	void CanInteract();

	UFUNCTION(BlueprintCallable, Category="Input")
	void Interact();
public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

