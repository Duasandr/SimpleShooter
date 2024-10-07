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
	FVector ShotDirection;
	FHitResult HitResult;
	bool const bHasHit = GunTrace( HitResult, ShotDirection );
	if ( bHasHit )
	{
		FVector const ShotLocation{ HitResult.ImpactPoint };
		FRotator const ShotRotation{ ShotDirection.Rotation() };

		if ( HitParticle && MuzzleFlash && MuzzleSound && ImpactSound )
		{
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld(), HitParticle, ShotLocation, ShotRotation );
			UGameplayStatics::SpawnEmitterAttached( MuzzleFlash, SkeletalMesh, TEXT( "MuzzleFlashSocket" ) );
			UGameplayStatics::SpawnSoundAttached( MuzzleSound, SkeletalMesh, TEXT( "MuzzleFlashSocket" ) );
			UGameplayStatics::PlaySoundAtLocation( this, ImpactSound, ShotLocation );
		}

		if ( AActor* HitActor = HitResult.GetActor() )
		{
			AController* Controller = GetController();
			if ( Controller )
			{
				FPointDamageEvent DamageEvent( Damage, HitResult, ShotDirection, nullptr );
				HitActor->TakeDamage( Damage, DamageEvent, Controller, this );
			}
		}
	}
}

bool AGun::GunTrace(FHitResult& HitResult, FVector& ShotDirection) const
{
	AController* Controller = GetController();
	if ( !Controller )
	{
		return false;
	}

	FVector Location;
	FRotator Rotation;
	Controller->GetPlayerViewPoint( Location, Rotation );
	ShotDirection = -Rotation.Vector();

	FCollisionShape const CollisionShape = FCollisionShape::MakeSphere( HitRadius );
	FVector const End = Location + Rotation.Vector() * Range;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor( this );
	CollisionParams.AddIgnoredActor( Owner );

	return GetWorld()->SweepSingleByChannel(
		HitResult,
		Location,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		CollisionShape,
		CollisionParams );
}

AController* AGun::GetController() const
{
	APawn const* Owner = Cast< APawn >( GetOwner() );
	if ( !Owner )
	{
		return nullptr;
	}
	return Owner->GetController();
}
