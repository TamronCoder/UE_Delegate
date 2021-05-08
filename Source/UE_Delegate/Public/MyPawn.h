// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class AMyGameMode;

UCLASS()
class UE_DELEGATE_API AMyPawn : public APawn
{
	GENERATED_BODY()

private:
	AMyGameMode* MyGameMode;

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Execute standard delegate
	void ExecuteStandardDelegate();

	// UnBind standard delegate
	void UnBindStandardDelegate();

	// Execute multicast delegate
	void ExecuteMulticastDelegate();

	// UnBind multicast delegate
	void UnBindMulticastDelegate();
};
