// Copyright 2019 ayumax. All Rights Reserved.
#include "CustomXMLParser.h"

#include "Misc/FeedbackContext.h"
#include "EasyXMLElement.h"
#include "EasyXMLAttribute.h"

CustomXMLParser::CustomXMLParser()
{
}

CustomXMLParser::~CustomXMLParser()
{
}

UEasyXMLElement *CustomXMLParser::Parse(FString xmlString, FString &ErrorMessage)
{
	RootElement = NewObject<UEasyXMLElement>();
	XMLObjectStack.Emplace(RootElement);

	FText _errorMessage;
	int32 _errorMessageNumber;

	if (!FFastXml::ParseXmlFile(this, TEXT(""), &xmlString[0], nullptr, false, false, _errorMessage, _errorMessageNumber))
	{
		ErrorMessage = FString::Printf(TEXT("line=%d, %s"), _errorMessageNumber, *_errorMessage.ToString());
		return nullptr;
	}

	return RootElement;
}

bool CustomXMLParser::ProcessXmlDeclaration(const TCHAR *ElementData, int32 XmlFileLineNumber)
{
	return true;
}

bool CustomXMLParser::ProcessElement(const TCHAR *ElementName, const TCHAR *ElementData, int32 XmlFileLineNumber)
{
	auto currentNode = XMLObjectStack.Num() > 0 ? XMLObjectStack.Last() : nullptr;

	auto newNode = UEasyXMLElement::CreateElement(currentNode, ElementName, ElementData, XmlFileLineNumber);

	if (currentNode)
	{
		currentNode->Children.Emplace(newNode);
	}

	XMLObjectStack.Emplace(newNode);

	return true;
}

bool CustomXMLParser::ProcessAttribute(const TCHAR *AttributeName, const TCHAR *AttributeValue)
{
	auto currentNode = XMLObjectStack.Last();

	if (!currentNode) return false;
	if (currentNode->Attributes.Contains(AttributeName)) return false;

	auto newAttribute = UEasyXMLAttribute::CreateAttribute(currentNode, AttributeName, AttributeValue);
	currentNode->Attributes.Add(AttributeName, newAttribute);

	return true;
}

bool CustomXMLParser::ProcessClose(const TCHAR *Element)
{
	if (XMLObjectStack.Num() == 0) return false;

	XMLObjectStack.RemoveAt(XMLObjectStack.Num() - 1);

	return true;
}

bool CustomXMLParser::ProcessComment(const TCHAR *Comment)
{
	if (XMLObjectStack.Num() == 0) return false;

	XMLObjectStack.Last()->Comments.Emplace(Comment);

	return true;
}
