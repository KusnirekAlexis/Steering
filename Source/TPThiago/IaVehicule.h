// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Vehicule.h"
#include "VehiculeJoueur.h"
#include "IaVehicule.generated.h"

UENUM()
enum AlgoUsing {
	SEEK	  UMETA(DisplayName = "Seek"),
	FLEE	  UMETA(DisplayName = "Flee"),
	PURSUIT	  UMETA(DisplayName = "Pursuit"),
	EVADE	  UMETA(DisplayName = "Evade"),
	ARRIVAL   UMETA(DisplayName = "Arrival"),
};

UCLASS()
class TPTHIAGO_API AIaVehicule : public AVehicule
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIaVehicule();
	virtual void Tick(float DeltaTime) override;
	FVector Seek(FVector TargetLocation);
	FVector Flee(FVector TargetLocation);
	FVector Evade();
	FVector Pursuit();
	FVector Arrival(FVector TargetLocation);
	AlgoUsing IntToEnum();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float Time = 0;
	UPROPERTY(EditAnywhere)
	int Index = 0;
	UPROPERTY(EditAnywhere)
		float SlowingDistance;
	UPROPERTY(EditAnywhere, Category = "Target")
		AVehiculeJoueur* Target;
	UPROPERTY(EditAnywhere)
		float DistanceChange;
	UPROPERTY(EditAnywhere)
		TEnumAsByte<AlgoUsing> Algorithme;

};
