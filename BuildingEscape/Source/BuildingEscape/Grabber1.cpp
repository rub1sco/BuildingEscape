// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber1.h"
#define OUT

// Sets default values for this component's properties
UGrabber1::UGrabber1()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
//    bWantsBeginPlay = true;                   bWantsBeginPlay is deprecated.. removed and code still works
	PrimaryComponentTick.bCanEverTick = true;
    
	// ...
}


// Called when the game starts
void UGrabber1::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp,Warning, TEXT("Grabber says what upppp"));
	// ...
     
	//Look for physics handle
    PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle){
        
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName());
    }
    
    
    //Look for attached Input Component(Only appears at runtime)
    InputComponent = GetOwner() -> InputComponent;
    if (InputComponent){
        //InputComponent found
         UE_LOG(LogTemp, Warning, TEXT("Input Component found"));
        InputComponent -> BindAction("Grab", IE_Pressed, this, &UGrabber1::Grab);
        InputComponent -> BindAction("Grab", IE_Released, this, &UGrabber1::Release);
        
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName());
    }
    
}

void UGrabber1::Grab(){
     UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
}

void UGrabber1::Release(){
    UE_LOG(LogTemp, Warning, TEXT("Released pressed"));
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
//    UE_LOG(LogTemp,Warning, TEXT("Location %s and Rotation %s"),
//           *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

    
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
    
    //Setup query params
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    
    
    //Ray-castout to reach distance
    FHitResult Hit;
    GetWorld()-> LineTraceSingleByObjectType( OUT Hit,
                 PlayerViewPointLocation,
                 LineTraceEnd,
                 FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                 TraceParameters);
    
    //See what we hit
    AActor* ActorHit = Hit.GetActor();
    if (ActorHit){
        UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit ->GetName()));
    }
    
	// ...
}

