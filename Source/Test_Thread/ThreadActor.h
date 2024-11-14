// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThreadCalculator.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "ThreadActor.generated.h"

//https://www.youtube.com/watch?v=tGNaDagBq8E

UCLASS()
class TEST_THREAD_API AThreadActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThreadActor();

	UFUNCTION(BlueprintCallable, Category = "Calculations")
		void InitCalculations(int32 _Calculations);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PrintCalcData();

	int32 ProcessedCalculation;

	class FThreadCalculator* CalcThread = nullptr;

	FRunnableThread* CurrentRunningThread = nullptr;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	TQueue<int32> ThreadCalcQueue;

};
