// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "FastXml.h"

class UEasyXMLElement;

class CustomXMLParser : public IFastXmlCallback
{
public:
	CustomXMLParser();
	virtual ~CustomXMLParser();

	UEasyXMLElement* Parse(FString xmlString, FString& ErrorMessage);

	/**
	 * Called after the XML's header is parsed.  This is usually the first call that you'll get back.
	 *
	 * @param	ElementData			Optional data for this element, nullptr if none
	 * @param	XmlFileLineNumber	Line number in the XML file we're on
	 *
	 * @return	You should return true to continue processing the file, or false to stop processing immediately.
	 */
	virtual bool ProcessXmlDeclaration(const TCHAR* ElementData, int32 XmlFileLineNumber) override;

	/**
	 * Called when a new XML element is encountered, starting a new scope.  You'll receive a call to ProcessClose()
	 * when this element's scope has ended.
	 *
	 * @param	ElementName			The name of the element
	 * @param	ElementData			Optional data for this element, nullptr if none
	 * @param	XmlFileLineNumber	The line number in the XML file we're on
	 *
	 * @return	You should return true to continue processing the file, or false to stop processing immediately.
	 */
	virtual bool ProcessElement(const TCHAR* ElementName, const TCHAR* ElementData, int32 XmlFileLineNumber) override;

	/**
	 * Called when an XML attribute is encountered for the current scope's element.
	 *
	 * @param	AttributeName	The name of the attribute
	 * @param	AttributeValue	The value of the attribute
	 *
	 * @return	You should return true to continue processing the file, or false to stop processing immediately.
	 */
	virtual bool ProcessAttribute(const TCHAR* AttributeName, const TCHAR* AttributeValue) override;

	/**
	 * Called when an element's scope ends in the XML file
	 *
	 * @param	ElementName		Name of the element whose scope closed
	 *
	 * @return	You should return true to continue processing the file, or false to stop processing immediately.
	 */
	virtual bool ProcessClose(const TCHAR* Element) override;

	/**
	 * Called when a comment is encountered.  This can happen pretty much anywhere in the file.
	 *
	 * @param	Comment		The comment text
	 */
	virtual bool ProcessComment(const TCHAR* Comment) override;

private:
	TArray<UEasyXMLElement*> XMLObjectStack;
	UEasyXMLElement* RootElement;
};
