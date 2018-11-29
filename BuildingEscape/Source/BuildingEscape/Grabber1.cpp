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

}

// Called when the game starts
void UGrabber1::BeginPlay()
{
	Super::BeginPlay();
    FindPhysicsComponent();
    FindInputComponent();
    
}



void UGrabber1::FindPhysicsComponent(){
    //Look for physics handle
    PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle == nullptr){
        UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName());
    }

}



void UGrabber1::FindInputComponent(){
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
    //Try and reach any actors with physics body Collision channel set
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    auto ActorHit = HitResult.GetActor();
    
        //If  we hit something, attach a physics handle
    if (ActorHit != nullptr){
        ///TODO attach physics handle
        PhysicsHandle -> GrabComponent(ComponentToGrab,
                        NAME_None,
                        ComponentToGrab->GetOwner()->GetActorLocation(),
                        true //Allow rotation
                        );
    }
}



void UGrabber1::Release(){
    PhysicsHandle -> ReleaseComponent();
}


// Called every frame
void UGrabber1::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    
    //If physics handle is attached
    if(PhysicsHandle->GrabbedComponent){
        //move attached body to end of reach line
        PhysicsHandle->SetTargetLocation(GetReachLineEnd());
    }
    
    
	// ...
}



const FHitResult UGrabber1::GetFirstPhysicsBodyInReach(){


    //Setup query params
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    
    
    //Ray-castout to reach distance
    FHitResult HitResult;
    
    GetWorld()-> LineTraceSingleByObjectType( OUT HitResult,
                GetReachLineStart(),
                GetReachLineEnd(),
                FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                TraceParameters);
    return HitResult;
};

FVector UGrabber1::GetReachLineStart(){
    //Get Player view point
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld() -> GetFirstPlayerController()-> GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
    
    return PlayerViewPointLocation;
    
};

FVector UGrabber1::GetReachLineEnd(){
    
    //Get Player view point
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld() -> GetFirstPlayerController()-> GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
    
    return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
};
