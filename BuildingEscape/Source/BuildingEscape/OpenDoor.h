// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
    
    float getTotalMassOfActorOnPlate();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(BlueprintAssignable)
    FDoorEvent onOpen;
    
    UPROPERTY(BlueprintAssignable)
    FDoorEvent onClose;
    
private:
    
	UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate = nullptr;
    
    //GetWorld method in CPP replaces this in editable area in gameplay
//    UPROPERTY(EditAnywhere)
    AActor* Owner = nullptr; //The owning door
    
    
	
};
