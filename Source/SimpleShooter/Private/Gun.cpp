// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Particles/ParticleSystemComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// memory allocation
	Root = CreateDefaultSubobject< USceneComponent >( TEXT( "Root" ) );
	SkeletalMesh = CreateDefaultSubobject< USkeletalMeshComponent >( TEXT( "Skeletal Mesh" ) );

	// attachments
	RootComponent = Root;
	SkeletalMesh->SetupAttachment( Root );
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
}

void AGun::PullTrigger()
{
	APawn const* Owner = Cast< APawn >( GetOwner() );
	AController* Controller;
	if ( !( Owner && ( ( Controller = Owner->GetController() ) ) ) )
	{
		return;
	}

	FVector Location;
	FRotator Rotation;
	Controller->GetPlayerViewPoint( Location, Rotation );

	FHitResult HitResult;
	FCollisionShape const CollisionShape = FCollisionShape::MakeSphere( HitRadius );
	FVector const End = Location + Rotation.Vector() * Range;

	bool const bHasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Location,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		CollisionShape );

	if ( bHasHit )
	{
		if ( HitParticle )
		{
			FVector const ShotLocation{ HitResult.ImpactPoint };
			FVector const ShotDirection{ Rotation.Vector() * -1.0f };
			FRotator const ShotRotation{ ShotDirection.Rotation() };
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld(), HitParticle, ShotLocation, ShotRotation );

			if ( AActor* HitActor = HitResult.GetActor() )
			{
				FPointDamageEvent DamageEvent( Damage, HitResult, ShotDirection, nullptr );
				HitActor->TakeDamage( Damage, DamageEvent, Controller, this );
			}
		}
	}

	if ( MuzzleFlash )
	{
		UGameplayStatics::SpawnEmitterAttached( MuzzleFlash, SkeletalMesh, TEXT( "MuzzleFlashSocket" ) );
	}
}
