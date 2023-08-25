// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:	

	void RotateTurret(FVector LootAtTarget);

	void Fire();

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

};
