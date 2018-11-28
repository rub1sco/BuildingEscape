// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport1.h"


// Sets default values for this component's properties
UPositionReport1::UPositionReport1()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
//    bWantsBeginPlay = true;               bWantsBeginPlay is deprecated.. removed and code still works
    
    
	// ...
}


// Called when the game starts
void UPositionReport1::BeginPlay()
{
	Super::BeginPlay();
    
    FString ObjectName = GetOwner() -> GetName();
    FString ObjectPos = GetOwner() -> GetTransform().GetLocation().ToString();
    UE_LOG(LogTemp,Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPos);
    
	// ...
	
}


// Called every frame
void UPositionReport1::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

