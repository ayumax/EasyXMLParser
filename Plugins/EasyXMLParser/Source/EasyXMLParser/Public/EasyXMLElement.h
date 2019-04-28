// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "EasyXMLObject.h"
#include "EasyXMLElement.generated.h"

class UEasyXMLAttribute;

UCLASS(BlueprintType, Blueprintable)
class EASYXMLPARSER_API UEasyXMLElement : public UEasyXMLObject
{
	GENERATED_BODY()
	
public:
	static UEasyXMLElement* CreateElement(UEasyXMLObject* ParentObject, FString Tag, FString Content, int32 LineNumber);

public:
	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	int32 ReadInt(const FString& AccessString, bool& isSuccess);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	float ReadFloat(const FString& AccessString, bool& isSuccess);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	FString ReadString(const FString& AccessString, bool& isSuccess);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	bool ReadBool(const FString& AccessString, bool& isSuccess);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	UEasyXMLElement* ReadElement(const FString& AccessString, bool& isSuccess);


	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	UEasyXMLObject* ReadEasyXMLObject(const FString& AccessString);

	UFUNCTION(BlueprintCallable, Category = "EasyXMLParser|Object")
	TArray<UEasyXMLElement*> GetElementsByTagName(const FString& TagName);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	UEasyXMLAttribute* GetAttribute(const FString& AtrributeName);


	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object")
	bool IsContainAttributeKeys(const TArray<FString>& Keys, TArray<FString>& FoundAttributeKeys);

private:
	bool IsAccessAsArray(const FString& AccessName, FString& ElementName, int32& ArrayIndex);


public:
	UPROPERTY(BlueprintReadOnly, Category = "EasyXMLParser|Object")
	int32 LineNumber = 0;

	UPROPERTY(BlueprintReadOnly, Category = "EasyXMLParser|Object")
	TArray<UEasyXMLElement*> Children;

	UPROPERTY(BlueprintReadOnly, Category = "EasyXMLParser|Object")
	TMap<FString, UEasyXMLAttribute*> Attributes;

	UPROPERTY(BlueprintReadOnly, Category = "EasyXMLParser|Object")
	TArray<FString> Comments;
};
