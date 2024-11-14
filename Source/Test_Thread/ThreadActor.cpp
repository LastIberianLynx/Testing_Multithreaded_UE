// Fill out your copyright notice in the Description page of Project Settings.


#include "ThreadActor.h"


//https://www.youtube.com/watch?v=tGNaDagBq8E

// Sets default values
AThreadActor::AThreadActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AThreadActor::InitCalculations(int32 _Calculations)
{
	if (_Calculations > 0) {

		CalcThread = new FThreadCalculator(_Calculations, this);
		CurrentRunningThread = FRunnableThread::Create(CalcThread, TEXT("Calculation Thread"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT(" Calculations must be great than 0"));

	}
}

// Called when the game starts or when spawned
void AThreadActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AThreadActor::PrintCalcData()
{
	if (!ThreadCalcQueue.IsEmpty() && ThreadCalcQueue.Dequeue(ProcessedCalculation)) {

		UE_LOG(LogTemp, Warning, TEXT("Processed Calculation: %d"), ProcessedCalculation);
	}
}


// Called every frame
void AThreadActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PrintCalcData();
}

void AThreadActor::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (CurrentRunningThread && CalcThread) {
		CurrentRunningThread->Suspend(true);
		CalcThread->bStopThread = true;
		CurrentRunningThread->Suspend(false);
		CurrentRunningThread->Kill(false);
		CurrentRunningThread->WaitForCompletion();
		delete CalcThread;

	}
}

