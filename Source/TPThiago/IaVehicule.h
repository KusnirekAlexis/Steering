// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Vehicule.h"
#include "IaVehicule.generated.h"

UENUM()
enum AlgoUsing {
	SEEK	  UMETA(DisplayName = "Seek Algo"),
	//EVADE	  UMETA(DisplayName = "Evade Algo"),
	FLEE	  UMETA(DisplayName = "Flee Algo"),
	//ARRIVAL   UMETA(DisplayName = "Arrival Algo"),
	PURSUIT	  UMETA(DisplayName = "Pursuit Algo"),
};

UCLASS()
class TPTHIAGO_API AIaVehicule : public AVehicule
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIaVehicule();
	virtual void Tick(float DeltaTime) override;
	FVector SeekVelocity(FVector TargetLocation);
	FVector FleeVelocity(FVector TargetLocation);
	//FVector EvadeVelocity(FVector TargetLocation, FVector TargetVelocity);
	FVector PursuitVelocity(FVector TargetLocation, FVector TargetVelocity);
	//FVector ArrivalVelocity(FVector TargetLocation);
	void ChangeAlgo();
	AlgoUsing IntToEnum();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool IsNew = false;
	float Time = 0;
	int Index = 0;
	UPROPERTY(EditAnywhere, Category = "Algorithme")
		TEnumAsByte<AlgoUsing> UsingAlgo;
	UPROPERTY(EditAnywhere, Category = "Algorithme")
		float SlowingDistance;
	UPROPERTY(EditAnywhere, Category = "Target")
		AVehicule* Target;
	UPROPERTY(EditAnywhere, Category = "Algorithme")
		float DistanceChange;
	FVector NewTargetEvade;

};
