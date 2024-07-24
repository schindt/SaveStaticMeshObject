// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMesh.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SaveStaticMeshObject.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API USaveStaticMeshObject : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "ProceduralMesh")
	static bool SaveStaticMeshToDisk(UStaticMesh* StaticMesh, const FString& FileName);

};
