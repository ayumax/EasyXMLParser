// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EasyXMLObject.generated.h"

class FXmlNode;

UCLASS(BlueprintType, Blueprintable)
class EASYXMLPARSER_API UEasyXMLObject : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	static UEasyXMLObject* CreateEasyXMLObject(const FString& ContentString);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	int32 ReadInt(const FString& AccessString);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	float ReadFloat(const FString& AccessString);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	FString ReadString(const FString& AccessString);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	bool ReadBool(const FString& AccessString);

	UFUNCTION(BlueprintCallable, Category = "EasyXMLParser|Object")
	UEasyXMLObject* ReadXMLObject(const FString& AccessString);

public:
	UPROPERTY(Transient, BlueprintReadOnly, Category = "EasyXMLParser|Object")
	FString Content = TEXT("");

private:
	FString GetXMLNodeContent(const FString& AccessString);
};
