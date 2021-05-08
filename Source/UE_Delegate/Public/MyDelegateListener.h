// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyDelegateListener.generated.h"

class AMyGameMode;

class AMyCPP
{
public:
	AMyCPP();
	
	// TestFunction for bindRaw
	void TF_BindRaw();

	// TestFunction for bind sharePtr
	void TF_BindSP();
};

UCLASS()
class UE_DELEGATE_API AMyDelegateListener : public AActor
{
	GENERATED_BODY()

private:
	AMyCPP MyCpp;

	TSharedPtr<AMyCPP> MyCppSPtr;
	
public:	
	// Sets default values for this actor's properties
	AMyDelegateListener();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Function for bind standard delegate
	void BindStandardDelegate(AMyGameMode* MyGameMode);

	// Function for bind multicast delegate
	void BindMulticastDelegate(AMyGameMode* MyGameMode);

	// TestFunction for bindUObject
	void TF_BindUObject();

	// TestFunction for bindUFUNCTION
	UFUNCTION()
		void TF_BindUFUNCTION();

public:
	FDelegateHandle MyMulticastDelegateHandle_Static;
	FDelegateHandle MyMulticastDelegateHandle_Raw;
	FDelegateHandle MyMulticastDelegateHandle_SP;
	FDelegateHandle MyMulticastDelegateHandle_Lambda;

};
