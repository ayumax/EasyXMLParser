// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EasyXMLObject.generated.h"


UCLASS(BlueprintType, Blueprintable)
class EASYXMLPARSER_API UEasyXMLObject : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	int32 ReadIntValue(bool& isSuccess);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	float ReadFloatValue(bool& isSuccess);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	FString ReadStringValue(bool& isSuccess);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	bool ReadBoolValue(bool& isSuccess);

public:
	UPROPERTY(BlueprintReadOnly, Category = "EasyXMLParser|Object")
	FString Name = TEXT("");

	UPROPERTY(BlueprintReadOnly, Category = "EasyXMLParser|Object")
	FString Value = TEXT("");
	
	UPROPERTY(BlueprintReadOnly, Category = "EasyXMLParser|Object")
	UEasyXMLObject* Parent = nullptr;

};
