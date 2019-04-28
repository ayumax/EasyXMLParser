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
	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|GetValue")
	int32 GetIntValue(bool& isSuccess);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|GetValue")
	float GetFloatValue(bool& isSuccess);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|GetValue")
	FString GetStringValue(bool& isSuccess);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|GetValue")
	bool GetBoolValue(bool& isSuccess);

public:
	UPROPERTY(BlueprintReadOnly, Category = "EasyXMLParser|Object")
	FString Name = TEXT("");

	UPROPERTY(BlueprintReadOnly, Category = "EasyXMLParser|Object")
	FString Value = TEXT("");
	
	UPROPERTY(BlueprintReadOnly, Category = "EasyXMLParser|Object")
	UEasyXMLObject* Parent = nullptr;

};
