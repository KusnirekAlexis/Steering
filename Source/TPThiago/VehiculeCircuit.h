// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IaVehicule.h"
#include "VehiculeCircuit.generated.h"

UENUM()
enum AlgoCuircuit
{
	CIRCUIT UMETA(DisplayName = "Circuit"),
	ONE_PATH UMETA(DisplayName = "One path"),
	TWO_PATH UMETA(DisplayName = "Two path"),
};

/**
 *
 */
UCLASS()
class TPTHIAGO_API AVehiculeCircuit : public AIaVehicule
{
	GENERATED_BODY()

public:
	AVehiculeCircuit();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<AlgoCuircuit> AlgoCircuit;
	UPROPERTY(EditAnywhere)
		TArray<AVehicule*> ListeTarget;
	UPROPERTY(EditAnywhere)
		float DistanceChangeTarget = 10;
	UPROPERTY(EditAnywhere)
		float TempsDattente;

	int Direction = 1;
	int NbListe = 0;
	bool Arriver = false;
	bool IsTarget = false;
	float TimeWaitCurrent = 0;

public:
	virtual void Tick(float DeltaTime) override;

	FVector CalculDirection();
	void ChangeTargetCircuit();
	void ChangeTargetOne();
	void ChangeTargetTwo();
};
