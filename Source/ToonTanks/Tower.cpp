// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
		RotateTurret(Tank->GetActorLocation());
}


void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandler, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (InFireRange())
		ATower::Fire();

}

bool ATower::InFireRange() const
{
	if (Tank)
	{
		float Distance = FVector::Distance(GetActorLocation(), Tank->GetActorLocation());
		return Distance <= FireRange;
	}

	return false;
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}
