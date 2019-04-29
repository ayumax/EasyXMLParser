// Copyright 2019 ayumax. All Rights Reserved.
#include "Misc/AutomationTest.h"
#include "EasyXMLParseManager.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FNodeAccessTest, "EasyXMLParser.NodeAccessTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FNodeAccessTest::RunTest(const FString& Parameters)
{
	{
		FString xmlString = TEXT("<root>\r")
			TEXT("<!-- comment desu -->\r")
			TEXT("<abc attr1=\"10\" attr2=\"false\">\r")
			TEXT("123\r")
			TEXT("</abc>\r")
			TEXT("<abc/>\r")
			TEXT("<abc>40</abc>\r")
			TEXT("<abc>ZZZZ</abc>\r")
			TEXT("<bbb>\r")
			TEXT("bbbChild\r")
			TEXT("</bbb>\r")
			TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);
		
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("root.abc")), TEXT("123"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("root.abc[0]")), TEXT("123"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("root.abc[1]")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("root.abc[2]")), TEXT("40"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("root.abc[3]")), TEXT("ZZZZ"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("root.bbb")), TEXT("bbbChild"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("root.abc[0].@attr1")), TEXT("10"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("root.abc[0].@attr2")), TEXT("false"));
	}

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FNodeAccessTest2, "EasyXMLParser.NodeAccessTest2", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FNodeAccessTest2::RunTest(const FString& Parameters)
{
	FString XMLSource =
		TEXT("<PurchaseOrder PurchaseOrderNumber=\"99503\" OrderDate=\"1999-10-20\">\r")
			TEXT("<Address Type=\"Shipping\">\r")
				TEXT("<Name>Ellen Adams</Name>\r")
				TEXT("<Street>123 Maple Street</Street>\r")
				TEXT("<City>Mill Valley</City>\r")
				TEXT("<State>CA</State>\r")
				TEXT("<Zip>10999</Zip>\r")
				TEXT("<Country>USA</Country>\r")
			TEXT("</Address>\r")
			TEXT("<Address Type=\"Billing\">\r")
				TEXT("<Name>Tai Yee</Name>\r")
				TEXT("<Street>8 Oak Avenue</Street>\r")
				TEXT("<City>Old Town</City>\r")
				TEXT("<State>PA</State>\r")
				TEXT("<Zip>95819</Zip>\r")
				TEXT("<Country>USA</Country>\r")
			TEXT("</Address>\r")
			TEXT("<DeliveryNotes>Please leave packages in shed by driveway.</DeliveryNotes>\r")
			TEXT("<Items>\r")
				TEXT("<Item PartNumber=\"872-AA\">\r")
					TEXT("<ProductName>Lawnmower</ProductName>\r")
					TEXT("<Quantity>1</Quantity>\r")
					TEXT("<USPrice>148.95</USPrice>\r")
					TEXT("<Comment>Confirm this is electric</Comment>\r")
				TEXT("</Item>\r")
				TEXT("<Item PartNumber=\"926-AA\">\r")
					TEXT("<ProductName>Baby Monitor</ProductName>\r")
					TEXT("<Quantity>2</Quantity>\r")
					TEXT("<USPrice>39.98</USPrice>\r")
					TEXT("<ShipDate>1999-05-21</ShipDate>\r")
				TEXT("</Item>\r")
			TEXT("</Items>\r")
		TEXT("</PurchaseOrder>\r");

	{
		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(XMLSource, result, errorMessage);

		TestEqual(TEXT("success read"), rootNode->ReadInt(TEXT("PurchaseOrder.@PurchaseOrderNumber")), 99503);
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.@OrderDate")), TEXT("1999-10-20"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[0].@Type")), TEXT("Shipping"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[0].Name")), TEXT("Ellen Adams"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[0].Street")), TEXT("123 Maple Street"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[0].City")), TEXT("Mill Valley"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[0].State")), TEXT("CA"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[0].Zip")), TEXT("10999"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[0].Country")), TEXT("USA"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[1].@Type")), TEXT("Billing"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[1].Name")), TEXT("Tai Yee"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[1].Street")), TEXT("8 Oak Avenue"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[1].City")), TEXT("Old Town"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[1].State")), TEXT("PA"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[1].Zip")), TEXT("95819"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[1].Country")), TEXT("USA"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.DeliveryNotes")), TEXT("Please leave packages in shed by driveway."));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[0].@PartNumber")), TEXT("872-AA"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[0].ProductName")), TEXT("Lawnmower"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[0].Quantity")), TEXT("1"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[0].USPrice")), TEXT("148.95"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[0].Comment")), TEXT("Confirm this is electric"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[1].@PartNumber")), TEXT("926-AA"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[1].ProductName")), TEXT("Baby Monitor"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[1].Quantity")), TEXT("2"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[1].USPrice")), TEXT("39.98"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[1].ShipDate")), TEXT("1999-05-21"));
	}

	{
		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(XMLSource, result, errorMessage);

		EEasyXMLParserFound retFound;
		auto Address0Node = rootNode->ReadElement(TEXT("PurchaseOrder.Address[0]"), retFound);
		TestTrue(TEXT("success read"), retFound == EEasyXMLParserFound::Found);
		auto Address1Node = rootNode->ReadElement(TEXT("PurchaseOrder.Address[1]"), retFound);
		TestTrue(TEXT("success read"), retFound == EEasyXMLParserFound::Found);
		auto Item0Node = rootNode->ReadElement(TEXT("PurchaseOrder.Items.Item[0]"), retFound);
		TestTrue(TEXT("success read"), retFound == EEasyXMLParserFound::Found);
		auto Item1Node = rootNode->ReadElement(TEXT("PurchaseOrder.Items.Item[1]"), retFound);
		TestTrue(TEXT("success read"), retFound == EEasyXMLParserFound::Found);

		TestEqual(TEXT("success read"), rootNode->ReadInt(TEXT("PurchaseOrder.@PurchaseOrderNumber")), 99503);
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.@OrderDate")), TEXT("1999-10-20"));
		TestEqual(TEXT("success read"), Address0Node->ReadString(TEXT("@Type")), TEXT("Shipping"));
		TestEqual(TEXT("success read"), Address0Node->ReadString(TEXT("Name")), TEXT("Ellen Adams"));
		TestEqual(TEXT("success read"), Address0Node->ReadString(TEXT("Street")), TEXT("123 Maple Street"));
		TestEqual(TEXT("success read"), Address0Node->ReadString(TEXT("City")), TEXT("Mill Valley"));
		TestEqual(TEXT("success read"), Address0Node->ReadString(TEXT("State")), TEXT("CA"));
		TestEqual(TEXT("success read"), Address0Node->ReadString(TEXT("Zip")), TEXT("10999"));
		TestEqual(TEXT("success read"), Address0Node->ReadString(TEXT("Country")), TEXT("USA"));
		TestEqual(TEXT("success read"), Address1Node->ReadString(TEXT("@Type")), TEXT("Billing"));
		TestEqual(TEXT("success read"), Address1Node->ReadString(TEXT("Name")), TEXT("Tai Yee"));
		TestEqual(TEXT("success read"), Address1Node->ReadString(TEXT("Street")), TEXT("8 Oak Avenue"));
		TestEqual(TEXT("success read"), Address1Node->ReadString(TEXT("City")), TEXT("Old Town"));
		TestEqual(TEXT("success read"), Address1Node->ReadString(TEXT("State")), TEXT("PA"));
		TestEqual(TEXT("success read"), Address1Node->ReadString(TEXT("Zip")), TEXT("95819"));
		TestEqual(TEXT("success read"), Address1Node->ReadString(TEXT("Country")), TEXT("USA"));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.DeliveryNotes")), TEXT("Please leave packages in shed by driveway."));
		TestEqual(TEXT("success read"), Item0Node->ReadString(TEXT("@PartNumber")), TEXT("872-AA"));
		TestEqual(TEXT("success read"), Item0Node->ReadString(TEXT("ProductName")), TEXT("Lawnmower"));
		TestEqual(TEXT("success read"), Item0Node->ReadString(TEXT("Quantity")), TEXT("1"));
		TestEqual(TEXT("success read"), Item0Node->ReadString(TEXT("USPrice")), TEXT("148.95"));
		TestEqual(TEXT("success read"), Item0Node->ReadString(TEXT("Comment")), TEXT("Confirm this is electric"));
		TestEqual(TEXT("success read"), Item1Node->ReadString(TEXT("@PartNumber")), TEXT("926-AA"));
		TestEqual(TEXT("success read"), Item1Node->ReadString(TEXT("ProductName")), TEXT("Baby Monitor"));
		TestEqual(TEXT("success read"), Item1Node->ReadString(TEXT("Quantity")), TEXT("2"));
		TestEqual(TEXT("success read"), Item1Node->ReadString(TEXT("USPrice")), TEXT("39.98"));
		TestEqual(TEXT("success read"), Item1Node->ReadString(TEXT("ShipDate")), TEXT("1999-05-21"));
	}


	{
		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(XMLSource, result, errorMessage);

		EEasyXMLParserFound retFound;
		auto AddressNodes = rootNode->ReadElements(TEXT("PurchaseOrder.Address"), retFound);
		TestTrue(TEXT("success read"), retFound == EEasyXMLParserFound::Found);
		auto ItemNodes = rootNode->ReadElements(TEXT("PurchaseOrder.Items.Item"), retFound);
		TestTrue(TEXT("success read"), retFound == EEasyXMLParserFound::Found);

		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString(TEXT("@Type")), TEXT("Shipping"));
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString(TEXT("Name")), TEXT("Ellen Adams"));
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString(TEXT("Street")), TEXT("123 Maple Street"));
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString(TEXT("City")), TEXT("Mill Valley"));
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString(TEXT("State")), TEXT("CA"));
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString(TEXT("Zip")), TEXT("10999"));
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString(TEXT("Country")), TEXT("USA"));
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString(TEXT("@Type")), TEXT("Billing"));
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString(TEXT("Name")), TEXT("Tai Yee"));
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString(TEXT("Street")), TEXT("8 Oak Avenue"));
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString(TEXT("City")), TEXT("Old Town"));
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString(TEXT("State")), TEXT("PA"));
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString(TEXT("Zip")), TEXT("95819"));
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString(TEXT("Country")), TEXT("USA"));

		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString(TEXT("@PartNumber")), TEXT("872-AA"));
		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString(TEXT("ProductName")), TEXT("Lawnmower"));
		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString(TEXT("Quantity")), TEXT("1"));
		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString(TEXT("USPrice")), TEXT("148.95"));
		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString(TEXT("Comment")), TEXT("Confirm this is electric"));
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString(TEXT("@PartNumber")), TEXT("926-AA"));
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString(TEXT("ProductName")), TEXT("Baby Monitor"));
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString(TEXT("Quantity")), TEXT("2"));
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString(TEXT("USPrice")), TEXT("39.98"));
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString(TEXT("ShipDate")), TEXT("1999-05-21"));
	}

	{
		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(XMLSource, result, errorMessage);

		TestEqual(TEXT("success read"), rootNode->ReadInt(TEXT("PurchaseOrder.PurchaseOrderNumber")), 0);
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.OrderDate")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[0].Type")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[0].Name-")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrde-r.Address[0].Street")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address-[0].City")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[0].State-")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder-.Address[0].Zip")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[0]-.Country")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[1]-.@Type")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder-.Address[1].Name")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[1].Stree-t")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[1]-.City")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder-.Address[1].State")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[1].Zip-")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Address[1]-.Country")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder-.DeliveryNotes")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[0].@PartNumber-")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[0]-.ProductName")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items-.Item[0].Quantity")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[4].USPrice")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[-1].Comment")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[8].@PartNumber")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[99].ProductName")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[7].Quantity")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[555].USPrice")), TEXT(""));
		TestEqual(TEXT("success read"), rootNode->ReadString(TEXT("PurchaseOrder.Items.Item[9999].ShipDate")), TEXT(""));
	}

	{
		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(XMLSource, result, errorMessage);

		EEasyXMLParserFound retFound;
		auto AddressNodes = rootNode->ReadElements(TEXT("PurchaseOrder.Address"), retFound);
		TestTrue(TEXT("success read"), retFound == EEasyXMLParserFound::Found);
		auto ItemNodes = rootNode->ReadElements(TEXT("PurchaseOrder.Items.Item"), retFound);
		TestTrue(TEXT("success read"), retFound == EEasyXMLParserFound::Found);

		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString(TEXT("@Type-")), TEXT(""));
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString(TEXT("Name-")), TEXT(""));
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString(TEXT("Street-")), TEXT(""));
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString(TEXT("City-")), TEXT(""));
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString(TEXT("State-")), TEXT(""));
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString(TEXT("Zip-")), TEXT(""));
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString(TEXT("Country-")), TEXT(""));
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString(TEXT("@Type-")), TEXT(""));
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString(TEXT("Name-")), TEXT(""));
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString(TEXT("Street-")), TEXT(""));
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString(TEXT("City-")), TEXT(""));
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString(TEXT("State-")), TEXT(""));
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString(TEXT("Zip-")), TEXT(""));
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString(TEXT("Country-")), TEXT(""));

		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString(TEXT("@PartNumber-")), TEXT(""));
		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString(TEXT("ProductName-")), TEXT(""));
		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString(TEXT("Quantity-")), TEXT(""));
		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString(TEXT("USPrice-")), TEXT(""));
		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString(TEXT("Comment-")), TEXT(""));
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString(TEXT("@PartNumber-")), TEXT(""));
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString(TEXT("ProductName-")), TEXT(""));
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString(TEXT("Quantity-")), TEXT(""));
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString(TEXT("USPrice-")), TEXT(""));
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString(TEXT("ShipDate-")), TEXT(""));
	}

	return true;
}