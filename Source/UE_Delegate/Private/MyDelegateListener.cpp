// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDelegateListener.h"
#include "MyGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"

// TestFunction for bindStatic
static void TF_BindStatic()
{
	UE_LOG(LogTemp, Error, TEXT("Delegate listener is bindStatic successed!"));
}

// Sets default values
AMyDelegateListener::AMyDelegateListener()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyDelegateListener::BeginPlay()
{
	Super::BeginPlay();

	MyCppSPtr = MakeShareable(new AMyCPP());
	
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(World);
		AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameModeBase);
		MyGameMode->MyDelegateListener = this;
		if (MyGameMode != nullptr)
		{
			BindStandardDelegate(MyGameMode);
			BindMulticastDelegate(MyGameMode);
		}
	}
}

// Called every frame
void AMyDelegateListener::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function for bind standard delegate
void AMyDelegateListener::BindStandardDelegate(AMyGameMode* MyGameMode)
{
	MyGameMode->MyStandardDelegate.BindUObject(this, &AMyDelegateListener::TF_BindUObject);
	//MyGameMode->MyStandardDelegate.BindStatic(TF_BindStatic);
	//MyGameMode->MyStandardDelegate.BindUFunction(this, "TF_BindUFUNCTION");
	//MyGameMode->MyStandardDelegate.BindRaw(&MyCpp, &AMyCPP::TF_BindRaw);
	//MyGameMode->MyStandardDelegate.BindSP(MyCppSPtr.ToSharedRef(), &AMyCPP::TF_BindSP);

	/*auto lambdaFunc = [&](){
		UE_LOG(LogTemp, Error, TEXT("Delegate listener is bindLambda successed!"));
	};
	MyGameMode->MyStandardDelegate.BindLambda(lambdaFunc);*/

	UE_LOG(LogTemp, Error, TEXT("Delegate listener is bind standard delegate!"));
}

void AMyDelegateListener::BindMulticastDelegate(AMyGameMode* MyGameMode)
{
	 MyGameMode->MyMulticastDelegate.AddUObject(this, &AMyDelegateListener::TF_BindUObject);
	 MyMulticastDelegateHandle_Static = MyGameMode->MyMulticastDelegate.AddStatic(TF_BindStatic);
	 MyGameMode->MyMulticastDelegate.AddUFunction(this, "TF_BindUFUNCTION");
	 MyMulticastDelegateHandle_Raw = MyGameMode->MyMulticastDelegate.AddRaw(&MyCpp, &AMyCPP::TF_BindRaw);
	 MyMulticastDelegateHandle_SP = MyGameMode->MyMulticastDelegate.AddSP(MyCppSPtr.ToSharedRef(), &AMyCPP::TF_BindSP);

	 auto lambdaFunc = [&](){
		UE_LOG(LogTemp, Error, TEXT("Delegate listener is bindLambda successed!"));
	 };
	 MyMulticastDelegateHandle_Lambda = MyGameMode->MyMulticastDelegate.AddLambda(lambdaFunc);

	UE_LOG(LogTemp, Error, TEXT("Delegate listener is bind multicast delegate!"));
}

// TestFunction for bindUObject
void AMyDelegateListener::TF_BindUObject()
{
	UE_LOG(LogTemp, Error, TEXT("Delegate listener is bindUObject successed!"));
}

// TestFunction for bindUFUNCTION
void AMyDelegateListener::TF_BindUFUNCTION()
{
	UE_LOG(LogTemp, Error, TEXT("Delegate listener is bindUFUNCTION successed!"));
}

AMyCPP::AMyCPP()
{
}

// TestFunction for bindRaw
void AMyCPP::TF_BindRaw()
{
	UE_LOG(LogTemp, Error, TEXT("Delegate listener is bindRaw successed!"));
}

// TestFunction for bind sharePtr
void AMyCPP::TF_BindSP()
{
	UE_LOG(LogTemp, Error, TEXT("Delegate listener is bindSP successed!"));
}