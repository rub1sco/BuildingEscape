// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    Owner = GetOwner();
    
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    //Poll trigger Volume at every frame
    if (getTotalMassOfActorOnPlate() > 50.f){                   //TODO make into parameter
        OpenDoor();
        DoorLastOpenTime = GetWorld()->GetTimeSeconds();
    }
    
    //TODO Check if time to close door
    if(GetWorld()-> GetTimeSeconds() - DoorLastOpenTime > DoorCloseDelay){
        CloseDoor();
    }
    
    
	// ...
}

void UOpenDoor::OpenDoor(){
    Owner -> SetActorRotation(FRotator(0.0f, OpenAngle,0.0f));
    
}

void UOpenDoor::CloseDoor(){
    Owner -> SetActorRotation(FRotator(0.0f, 90.0f,0.0f));
}

float UOpenDoor::getTotalMassOfActorOnPlate() {
    float totalMass = 0;
    TArray<AActor*> OverlappingActors;
    
    //Find overlapping actors
    PressurePlate -> GetOverlappingActors(OUT OverlappingActors);
    //Iterate through them adding masses
    for (const auto* Actor : OverlappingActors){
        totalMass += Actor-> FindComponentByClass<UPrimitiveComponent>()->GetMass();
        UE_LOG(LogTemp,Warning,TEXT("%s on pressure plate"), *Actor->GetName());
    }
    
    return totalMass;
};
