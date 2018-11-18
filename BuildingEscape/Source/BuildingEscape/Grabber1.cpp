// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber1.h"
#define OUT

// Sets default values for this component's properties
UGrabber1::UGrabber1()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
    bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber1::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp,Warning, TEXT("Grabber says what upppp"));
	// ...
	
}


// Called every frame
void UGrabber1::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    //Get Player view point this tick
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld() -> GetFirstPlayerController()-> GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );
    
    
    //Log out every tick
    UE_LOG(LogTemp,Warning, TEXT("Location %s and Rotation %s"),
           *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

    
    FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
    
    //Draw red trace
    DrawDebugLine(
        GetWorld(),
        PlayerViewPointLocation,
        LineTraceEnd,
        FColor(255,0,0),
        false,
        0.f,
        0.f,
        10.f
    );
    
    
    
    //Ray-castout to reach distance
    
    //See what we hit
    
	// ...
}

