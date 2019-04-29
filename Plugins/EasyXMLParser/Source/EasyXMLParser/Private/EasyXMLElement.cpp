// Copyright 2019 ayumax. All Rights Reserved.
#include "EasyXMLElement.h"
#include "EasyXMLAttribute.h"
#include "Internationalization/Regex.h"

UEasyXMLElement* UEasyXMLElement::CreateElement(UEasyXMLObject* ParentObject, FString Tag, FString Content, int32 _LineNumber)
{
	auto newElement = NewObject<UEasyXMLElement>(ParentObject == nullptr ? (UObject*)GetTransientPackage() : ParentObject);
	newElement->Parent = ParentObject;
	newElement->Name = Tag;
	newElement->Value = Content.TrimStartAndEnd();
	newElement->LineNumber = _LineNumber;

	return newElement;
}


int32 UEasyXMLElement::ReadInt(const FString& AccessString, int32 DefaultValue)
{
	auto foundElement = ReadEasyXMLObject(AccessString);
	if (!foundElement) return DefaultValue;

	return foundElement->GetIntValue(DefaultValue);
}


float UEasyXMLElement::ReadFloat(const FString& AccessString, float DefaultValue)
{
	auto foundElement = ReadEasyXMLObject(AccessString);
	if (!foundElement) return DefaultValue;

	return foundElement->GetFloatValue(DefaultValue);
}

FString UEasyXMLElement::ReadString(const FString& AccessString, const FString& DefaultValue)
{
	auto foundElement = ReadEasyXMLObject(AccessString);
	if (!foundElement) return DefaultValue;

	return foundElement->GetStringValue(DefaultValue);
}

bool UEasyXMLElement::ReadBool(const FString& AccessString, bool DefaultValue)
{
	auto foundElement = ReadEasyXMLObject(AccessString);
	if (!foundElement) return DefaultValue;

	return foundElement->GetBoolValue(DefaultValue);
}

UEasyXMLElement* UEasyXMLElement::ReadElement(const FString& AccessString, EEasyXMLParserFound& Result)
{
	auto filterArray = ReadElements(AccessString, Result);

	return filterArray.Num() > 0 ? filterArray[0] : nullptr;
}

TArray<UEasyXMLElement*> UEasyXMLElement::ReadElements(const FString& AccessString, EEasyXMLParserFound& Result)
{
	TArray<UEasyXMLElement*> foundElements;

	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);

	Result = EEasyXMLParserFound::NotFound;

	auto parentNode = this;

	for (int i = 0; i < Accessers.Num(); ++i)
	{
		auto accesseName = Accessers[i];

		if (accesseName.IsEmpty()) return foundElements;

		if (accesseName[0] == TEXT('@'))
		{
			return foundElements;
		}

		FString elementName;
		int32 arrayIndex = 0;
		bool IsArrayAccess = IsAccessAsArray(accesseName, elementName, arrayIndex);

		auto filterNodes = parentNode->GetElementsByTagName(elementName);

		if (i == (Accessers.Num() - 1))
		{
			if (IsArrayAccess)
			{
				if (filterNodes.Num() > arrayIndex)
				{
					foundElements.Emplace(filterNodes[arrayIndex]);
				}	
			}
			else
			{
				foundElements = filterNodes;
			}
		}
		else
		{
			if (filterNodes.Num() > arrayIndex)
			{
				parentNode = filterNodes[arrayIndex];
			}

			if (!parentNode) return foundElements;
		}
	}

	Result = EEasyXMLParserFound::Found;

	return foundElements;
}

UEasyXMLObject* UEasyXMLElement::ReadEasyXMLObject(const FString& AccessString)
{
	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);

	auto parentNode = this;

	for (auto accesseName : Accessers)
	{
		if (!parentNode) return nullptr;
		if (accesseName.IsEmpty()) return nullptr;

		if (accesseName[0] == TEXT('@'))
		{
			EEasyXMLParserFound retFound;
			return parentNode->GetAttribute(accesseName.Mid(1), retFound);
		}
		
		FString elementName;
		int32 arrayIndex = 0;
		IsAccessAsArray(accesseName, elementName, arrayIndex);

		auto filterNodes = parentNode->GetElementsByTagName(elementName);
		if (filterNodes.Num() > arrayIndex)
		{
			parentNode = filterNodes[arrayIndex];
		}
		else
		{
			return nullptr;
		}	
	}

	return parentNode;
}

TArray<UEasyXMLElement*> UEasyXMLElement::GetElementsByTagName(const FString& TagName)
{
	TArray<UEasyXMLElement*> foundElements = Children.FilterByPredicate(
		[TagName](UEasyXMLElement* child)
		{
			return child->Name.Equals(TagName, ESearchCase::IgnoreCase);
		});

	return foundElements;
}

UEasyXMLAttribute* UEasyXMLElement::GetAttribute(const FString& AtrributeName, EEasyXMLParserFound& Result)
{
	if (Attributes.Contains(AtrributeName))
	{
		Result = EEasyXMLParserFound::Found;
		return Attributes[AtrributeName];
	}

	Result = EEasyXMLParserFound::NotFound;
	return nullptr;
}

bool UEasyXMLElement::IsAccessAsArray(const FString& AccessName, FString& ElementName, int32& ArrayIndex)
{
	const FRegexPattern pattern = FRegexPattern(FString(TEXT("(.*)\\[([0-9]+)\\]$")));
	FRegexMatcher matcher(pattern, AccessName);

	while (matcher.FindNext())
	{
		ElementName = matcher.GetCaptureGroup(1);

		FString numStr = matcher.GetCaptureGroup(2);
		if (numStr.IsNumeric())
		{
			ArrayIndex = (FCString::Atoi(*numStr));
		}

		return true;
	}

	ElementName = AccessName;
	ArrayIndex = 0;

	return false;
}
	


bool UEasyXMLElement::IsContainAttributeKeys(const TArray<FString>& Keys, TArray<FString>& FoundAttributeKeys)
{
	TArray<FString> attributeKeys;
	Attributes.GetKeys(attributeKeys);

	for (auto key : Keys)
	{
		bool found = false;
		for (auto attributeKey : attributeKeys)
		{
			if (key.Equals(attributeKey, ESearchCase::IgnoreCase))
			{
				found = true;
				FoundAttributeKeys.Emplace(attributeKey);
			}

		}

		if (!found) return false;
	}

	return true;
}
