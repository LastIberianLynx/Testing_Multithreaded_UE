// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Public/HAL/Runnable.h"


class FRunnableThread;
class AThreadActor;


class FThreadCalculator : public FRunnable
{

public:	
	// Sets default values for this actor's properties
	FThreadCalculator(int32 _Calculation, AThreadActor * FunActor);

	bool bStopThread;

	virtual bool Init();

	virtual uint32 Run();

	virtual void Stop();

private:
	int32 Calculations;

	int32 CalcCount;

	AThreadActor* CurrentThreadActor;

	int32 CurrentCalculation;




};
