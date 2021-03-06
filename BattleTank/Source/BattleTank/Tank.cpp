// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("TANK Aiming Component"));
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet) {
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret * TurretToSet) {
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire() {
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;

	if (Barrel && isReloaded) {
		//UE_LOG(LogTemp, Warning, TEXT("[%f]%s Fire!"), Time, *GetName());
		LastFireTime = FPlatformTime::Seconds();
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("FirePos")),
			Barrel->GetSocketRotation(FName("FirePos"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay() {
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent) {
	Super::SetupPlayerInputComponent(InputComponent);
}

void ATank::AimAt(FVector HitLoc) {
	TankAimingComponent->AimAt(HitLoc, LaunchSpeed);
}