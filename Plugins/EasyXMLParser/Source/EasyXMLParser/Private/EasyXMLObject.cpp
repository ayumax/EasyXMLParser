// Copyright 2019 ayumax. All Rights Reserved.

#include "EasyXMLObject.h"
#include "XmlParser.h"

UEasyXMLObject* UEasyXMLObject::CreateEasyXMLObject(const FString& ContentString)
{
	auto xmlObject = NewObject<UEasyXMLObject>();
	xmlObject->Content = ContentString;
	return xmlObject;
}

FString UEasyXMLObject::GetXMLNodeContent(const FString& AccessString)
{
	FXmlFile xmlFile(Content, EConstructMethod::ConstructFromBuffer);
	if (!xmlFile.IsValid()) return TEXT("");

	TArray<FString> Accessers;
	AccessString.ParseIntoArray(Accessers, TEXT("."), true);

	if (Accessers.Num() == 0) return TEXT("");

	auto parentNode = xmlFile.GetRootNode();

	for (auto accesseName : Accessers)
	{
		if (accesseName[0] == TEXT('@'))
		{
			return parentNode->GetAttribute(accesseName.Mid(1));
		}
		else
		{
			parentNode = parentNode->FindChildNode(accesseName);

			if (!parentNode) return TEXT("");
		}
	}

	return parentNode ? parentNode->GetContent() : TEXT("");
}

int32 UEasyXMLObject::ReadInt(const FString& AccessString)
{
	auto targetNodeContent = GetXMLNodeContent(AccessString);
	if (!targetNodeContent.IsEmpty()) return 0;

	return FCString::Atoi(*targetNodeContent);
}

float UEasyXMLObject::ReadFloat(const FString& AccessString)
{
	auto targetNodeContent = GetXMLNodeContent(AccessString);
	if (!targetNodeContent.IsEmpty()) return 0;

	return FCString::Atof(*targetNodeContent);
}

FString UEasyXMLObject::ReadString(const FString& AccessString)
{
	return GetXMLNodeContent(AccessString);
}

bool UEasyXMLObject::ReadBool(const FString& AccessString)
{
	auto targetNodeContent = GetXMLNodeContent(AccessString);
	if (!targetNodeContent.IsEmpty()) return false;

	return targetNodeContent.ToLower() == TEXT("true") ? true : false;
}

UEasyXMLObject* UEasyXMLObject::ReadXMLObject(const FString& AccessString)
{
	auto targetNodeContent = GetXMLNodeContent(AccessString);
	if (!targetNodeContent.IsEmpty()) return nullptr;

	return CreateEasyXMLObject(targetNodeContent);
}
