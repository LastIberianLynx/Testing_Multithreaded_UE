#include "MyActorAsyncFunction.h"

//https://www.youtube.com/watch?v=tGNaDagBq8E

// Sets default values
AMyActorAsyncFunction::AMyActorAsyncFunction()
{
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyActorAsyncFunction::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AMyActorAsyncFunction::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyActorAsyncFunction::MyAsyncFunction() {   
    UE_LOG(LogTemp, Log, TEXT("Async Task is running!"));
    for (int32 i = 0; i < 9999999 && bIsTaskRunning; i++) {
        // cant log every iteration or it will start halting, Logging every 1000 iterations for performance
        if (i % 1000 == 0) {
            UE_LOG(LogTemp, Log, TEXT("i = %d"), i);
        }
        FPlatformProcess::Sleep(0.001f);  // Sleep for 1 ms
    }
    bIsTaskRunning = false;  // Stop the task when done
    UE_LOG(LogTemp, Log, TEXT("Async Task has ended."));
}

void AMyActorAsyncFunction::StartAsyncTask() {
    bIsTaskRunning = true;  // Start the task
    Async(EAsyncExecution::Thread, [this]() {
            MyAsyncFunction();
            Async(EAsyncExecution::TaskGraphMainThread, [this]() {
                    UE_LOG(LogTemp, Log, TEXT("Back on Main Thread!"));
                });
        });
}

void AMyActorAsyncFunction::StartAsyncTaskCustomFunction(FMyAsyncDelegate InFunction)
{
    bIsTaskRunning = true;  // Ensure task can run

    Async(EAsyncExecution::Thread, [this, InFunction]()
        {
            // Call the delegate (the function passed from Blueprint)
            FString ResultString = TEXT("Task completed!");  // Sample result to pass
            InFunction.ExecuteIfBound(ResultString);

            // Callback to main thread
            Async(EAsyncExecution::TaskGraphMainThread, [this]()
                {
                    UE_LOG(LogTemp, Log, TEXT("Back on Main Thread!"));
                });
        });
}

// Called when the game stops or the actor is destroyed
void AMyActorAsyncFunction::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // Set the flag to false to stop the loop
    bIsTaskRunning = false;
}
