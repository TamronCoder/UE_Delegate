// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyDelegateListener.h"
#include "MyGameMode.generated.h"

// Declare standard delegate class
DECLARE_DELEGATE(FStandardDelegate)

// Declare multicast delegate class
DECLARE_MULTICAST_DELEGATE(FMulticastDelegate)

/**
 * 
 */
UCLASS()
class UE_DELEGATE_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMyDelegateListener* MyDelegateListener;
public:
	AMyGameMode();

	// Declare standard delegate object
	FStandardDelegate MyStandardDelegate;

	// Declare multicast delegate object
	FMulticastDelegate MyMulticastDelegate;

	// Declare dynamic multicast delegate class
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDyMulticastDelegate);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDyMulticastDelegateOneParam, FString, Str);

	// Declare dynamic standard delegate object
	UPROPERTY(BlueprintAssignable)
		FDyMulticastDelegate MyDyMulticastDelegate;

	UPROPERTY(BlueprintAssignable)
		FDyMulticastDelegateOneParam MyDyMulticastDelegateOneParam;

	// Declare dynamic standard delegate class
	DECLARE_DYNAMIC_DELEGATE(FDyStandardDelegate);

	FDyStandardDelegate MyDyStandardDelegateBindUFuntion;

	// TestFunction for dynamic standard delegate bind ufunction
	UFUNCTION()
		void TestFunc_DynamicStandardDelegate_BindUFunction()
	{
		UE_LOG(LogTemp, Error, TEXT("Dynamic standard delegate bind ufuntion!"));
	}

	// TestFunction for dynamic standard delegate
	UFUNCTION(BlueprintCallable)
	void TestFunc_DynamicStandardDelegate(const FDyStandardDelegate& MyDyStandardDelegate)
	{
		UE_LOG(LogTemp, Error, TEXT("Dynamic standard delegate!"));

		MyDyStandardDelegateBindUFuntion.BindUFunction(this, "TestFunc_DynamicStandardDelegate_BindUFunction");

		if (MyDyStandardDelegate.IsBound())
		{
			MyDyStandardDelegate.Execute();
		}

		// MyDyStandardDelegateBindUFuntion.Unbind();
		if (MyDyStandardDelegateBindUFuntion.IsBound())
		{
			MyDyStandardDelegateBindUFuntion.Execute();
		}
	}

	// TestFunction for dynamic multicast delegate
	UFUNCTION(BlueprintCallable)
		void TestFunc_DynamicMulticastDelegate(const FDyStandardDelegate& MyDyStandardDelegate1, const FDyStandardDelegate& MyDyStandardDelegate2)
	{
		MyDyMulticastDelegate.Add(MyDyStandardDelegate1);
		MyDyMulticastDelegate.Add(MyDyStandardDelegate2);
		MyDyMulticastDelegate.Broadcast();

		UE_LOG(LogTemp, Error, TEXT("Dynamic multicast delegate!"));

		// MyDyMulticastDelegate.Remove(MyDyStandardDelegate1);

		MyDyMulticastDelegate.RemoveAll(this);
		MyDyMulticastDelegate.Broadcast();

	}

};