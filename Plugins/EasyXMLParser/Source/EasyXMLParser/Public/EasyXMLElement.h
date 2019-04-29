// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "EasyXMLObject.h"
#include "EasyXMLParserEnums.h"
#include "EasyXMLElement.generated.h"

class UEasyXMLAttribute;

UCLASS(BlueprintType, Blueprintable)
class EASYXMLPARSER_API UEasyXMLElement : public UEasyXMLObject
{
	GENERATED_BODY()
	
public:
	static UEasyXMLElement* CreateElement(UEasyXMLObject* ParentObject, FString Tag, FString Content, int32 LineNumber);

public:
	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|ReadValue")
	int32 ReadInt(const FString& AccessString, int32 DefaultValue = 0);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|ReadValue")
	float ReadFloat(const FString& AccessString, float DefaultValue = 0.0f);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|ReadValue")
	FString ReadString(const FString& AccessString, const FString& DefaultValue = TEXT(""));

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|ReadValue")
	bool ReadBool(const FString& AccessString, bool DefaultValue = false);

	UFUNCTION(BlueprintCallable, Category = "EasyXMLParser|ReadValue", meta = (ExpandEnumAsExecs = "Result"))
	UEasyXMLElement* ReadElement(const FString& AccessString, EEasyXMLParserFound& Result);

	UFUNCTION(BlueprintCallable, Category = "EasyXMLParser|ReadValue", meta = (ExpandEnumAsExecs = "Result"))
	TArray<UEasyXMLElement*> ReadElements(const FString& AccessString, EEasyXMLParserFound& Result);

	UFUNCTION(BlueprintPure, Category = "EasyXMLParser|Object", meta = (ExpandEnumAsExecs = "Result"))
	UEasyXMLAttribute* GetAttribute(const FString& AtrributeName, EEasyXMLParserFound& Result);


public:
	UEasyXMLObject* ReadEasyXMLObject(const FString& AccessString);
	TArray<UEasyXMLElement*> GetElementsByTagName(const FString& TagName);
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
