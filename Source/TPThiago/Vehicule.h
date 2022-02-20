// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Vehicule.generated.h"

UCLASS()
class TPTHIAGO_API AVehicule : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVehicule();
	UPROPERTY(EditAnywhere, Category = "Variable")
		FVector Velocity;
	UPROPERTY(EditAnywhere, Category = "Variable")
		float max_force = 10;
	UPROPERTY(EditAnywhere, Category = "Variable")
		float max_speed = 10;
	UPROPERTY(EditAnywhere, Category = "Variable")
		float masse = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector Truncate(FVector v, float max);

};
