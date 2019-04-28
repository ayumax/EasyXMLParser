// Copyright 2019 ayumax. All Rights Reserved.
#include "EasyXMLAttribute.h"
#include "EasyXMLElement.h"

UEasyXMLAttribute* UEasyXMLAttribute::CreateAttribute(UEasyXMLElement* ParentObject, FString _Name, FString _Value)
{
	auto newAttribute = NewObject<UEasyXMLAttribute>(ParentObject == nullptr ? (UObject*)GetTransientPackage() : ParentObject);
	newAttribute->Parent = ParentObject;
	newAttribute->Name = _Name;
	newAttribute->Value = _Value.TrimStartAndEnd();

	return newAttribute;
}