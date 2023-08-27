// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	////Check to see if the tank is in range
	if (InFireRange()) {
		//if in range rotate turret to tank
		RotateTurret(Tank->GetActorLocation());
		
	}
}

void ATower::HandleDestruction() {
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	GetWorldTimerManager().SetTimer(FireRateTimerHandle,
		this, 
		&ATower::CheckFireCondition,
		FireRate,
		true);
}

void ATower::CheckFireCondition() {
	////Check to see if the tank is in range
	if (Tank == nullptr) {
		return;
	}
		
	if (InFireRange() && Tank->bAlive) {
		Fire();
	}
}

bool ATower::InFireRange() {
	if (!Tank) {
		return false;
	}
	float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
	//UE_LOG(LogTemp, Warning, TEXT("Distance is: %f"), Distance);
	//Check to see if the tank is in range
	if (Distance > FireRange) {
		//if in range rotate turret to tank
		return false;
	}
	return true;
}