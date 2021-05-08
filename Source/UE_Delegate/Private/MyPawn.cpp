// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(World);
		MyGameMode = Cast<AMyGameMode>(GameModeBase);
	}
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ExecuteStandardDelegate", IE_Pressed, this, &AMyPawn::ExecuteStandardDelegate);
	PlayerInputComponent->BindAction("UnBindStandardDelegate", IE_Pressed, this, &AMyPawn::UnBindStandardDelegate);
	PlayerInputComponent->BindAction("ExecuteMulticastDelegate", IE_Pressed, this, &AMyPawn::ExecuteMulticastDelegate);
	PlayerInputComponent->BindAction("UnBindMulticastDelegate", IE_Pressed, this, &AMyPawn::UnBindMulticastDelegate);

}
// Execute standard delegate
void AMyPawn::ExecuteStandardDelegate()
{
	if (MyGameMode != nullptr)
	{
		if (MyGameMode->MyStandardDelegate.IsBound())
		{
			MyGameMode->MyStandardDelegate.Execute();
			UE_LOG(LogTemp, Warning, TEXT("Execute standard delegate is successed!"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Execute standard delegate is failed, because delegate is not bound!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Execute standard delegate is failed, because gamemode is null!"));
	}
}

// UnBind standard delegate
void AMyPawn::UnBindStandardDelegate()
{
	if (MyGameMode != nullptr)
	{
		if (MyGameMode->MyStandardDelegate.IsBound())
		{
			MyGameMode->MyStandardDelegate.Unbind();
			UE_LOG(LogTemp, Warning, TEXT("UnBind standard delegate is successed!"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UnBind standard delegate is failed, because delegate is already unbind!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UnBind standard delegate is failed, because gamemode is null!"));
	}
}

// Execute multicast delegate
void AMyPawn::ExecuteMulticastDelegate()
{
	if (MyGameMode != nullptr)
	{
		if (MyGameMode->MyMulticastDelegate.IsBound())
		{
			MyGameMode->MyMulticastDelegate.Broadcast();
			UE_LOG(LogTemp, Warning, TEXT("Execute multicast delegate is successed!"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Execute multicast delegate is failed, because delegate is not bound!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Execute multicast delegate is failed, because gamemode is null!"));
	}
}

// UnBind multicast delegate
void AMyPawn::UnBindMulticastDelegate()
{
	if (MyGameMode != nullptr)
	{
		if (MyGameMode->MyMulticastDelegate.IsBound())
		{
			MyGameMode->MyMulticastDelegate.RemoveAll(MyGameMode->MyDelegateListener);
			// Non uobject objects can only be removed with handle
			MyGameMode->MyMulticastDelegate.Remove(MyGameMode->MyDelegateListener->MyMulticastDelegateHandle_Static);
			MyGameMode->MyMulticastDelegate.Remove(MyGameMode->MyDelegateListener->MyMulticastDelegateHandle_Raw);
			MyGameMode->MyMulticastDelegate.Remove(MyGameMode->MyDelegateListener->MyMulticastDelegateHandle_SP);
			MyGameMode->MyMulticastDelegate.Remove(MyGameMode->MyDelegateListener->MyMulticastDelegateHandle_Lambda);
			UE_LOG(LogTemp, Warning, TEXT("UnBind multicast delegate is successed!"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UnBind multicast delegate is failed, because delegate is already unbind!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UnBind multicast delegate is failed, because gamemode is null!"));
	}
}

