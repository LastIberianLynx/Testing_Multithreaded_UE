#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Async/Async.h"
#include "HAL/PlatformProcess.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "MyActorAsyncFunction.generated.h"

//https://www.youtube.com/watch?v=tGNaDagBq8E

// Change to singlecast delegate
DECLARE_DYNAMIC_DELEGATE_OneParam(FMyAsyncDelegate, FString, Sample);

UCLASS()
class TEST_THREAD_API AMyActorAsyncFunction : public AActor
{
	GENERATED_BODY()

public:
	AMyActorAsyncFunction();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Using singlecast delegate
	UFUNCTION(BlueprintCallable, Category = "Async Task")
		void StartAsyncTaskCustomFunction(FMyAsyncDelegate InFunction);

	UFUNCTION(BlueprintCallable)
		void StartAsyncTask();

	void MyAsyncFunction();

	bool bIsTaskRunning;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
