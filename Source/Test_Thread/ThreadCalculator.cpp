// Fill out your copyright notice in the Description page of Project Settings.


#include "ThreadCalculator.h"
#include "ThreadActor.h"

// Sets default values
FThreadCalculator::FThreadCalculator(int32 _Calculation, AThreadActor *FunActor)
{
	if (_Calculation > 0 && FunActor)
	{
		Calculations = _Calculation;
		CurrentThreadActor = FunActor;
	}
}

bool FThreadCalculator::Init()
{
	bStopThread = false;

	CalcCount = 0;
	return false;
}

uint32 FThreadCalculator::Run()
{
	while (!bStopThread) {
		if (CalcCount < Calculations) {

			CurrentCalculation += FMath::RandRange(20, 400);
			CurrentCalculation += FMath::RandRange(2, 500);
			CurrentCalculation += FMath::RandRange(10, 500);

			CurrentThreadActor->ThreadCalcQueue.Enqueue(CurrentCalculation);

			CalcCount++;
		}
		else {

			bStopThread = true;
		}

	}
	return 0;
}

void FThreadCalculator::Stop()
{
}
