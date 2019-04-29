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
		
		TestEqual(TEXT("success read"), rootNode->ReadString("root.abc"), "123");
		TestEqual(TEXT("success read"), rootNode->ReadString("root.abc[0]"), "123");
		TestEqual(TEXT("success read"), rootNode->ReadString("root.abc[1]"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("root.abc[2]"), "40");
		TestEqual(TEXT("success read"), rootNode->ReadString("root.abc[3]"), "ZZZZ");
		TestEqual(TEXT("success read"), rootNode->ReadString("root.bbb"), "bbbChild");
		TestEqual(TEXT("success read"), rootNode->ReadString("root.abc[0].@attr1"), "10");
		TestEqual(TEXT("success read"), rootNode->ReadString("root.abc[0].@attr2"), "false");
	}

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FNodeAccessTest2, "EasyXMLParser.NodeAccessTest2", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FNodeAccessTest2::RunTest(const FString& Parameters)
{
	{
		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromFile("PurchaseOrder.xml", false, result, errorMessage);

		TestEqual(TEXT("success read"), rootNode->ReadInt("PurchaseOrder.@PurchaseOrderNumber"), 99503);
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.@OrderDate"), "1999-10-20");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].@Type"), "Shipping");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].Name"), "Ellen Adams");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].Street"), "123 Maple Street");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].City"), "Mill Valley");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].State"), "CA");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].Zip"), "10999");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].Country"), "USA");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1].@Type"), "Billing");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1].Name"), "Tai Yee");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1].Street"), "8 Oak Avenue");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1].City"), "Old Town");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1].State"), "PA");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1].Zip"), "95819");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1].Country"), "USA");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.DeliveryNotes"), "Please leave packages in shed by driveway.");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[0].@PartNumber"), "872-AA");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[0].ProductName"), "Lawnmower");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[0].Quantity"), "1");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[0].USPrice"), "148.95");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[0].Comment"), "Confirm this is electric");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[1].@PartNumber"), "926-AA");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[1].ProductName"), "Baby Monitor");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[1].Quantity"), "2");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[1].USPrice"), "39.98");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[1].ShipDate"), "1999-05-21");
	}

	{
		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromFile("PurchaseOrder.xml", false, result, errorMessage);

		EEasyXMLParserFound retFound;
		auto Address0Node = rootNode->ReadElement("PurchaseOrder.Address[0]", retFound);
		TestTrue(TEXT("success read"), retFound == EEasyXMLParserFound::Found);
		auto Address1Node = rootNode->ReadElement("PurchaseOrder.Address[1]", retFound);
		TestTrue(TEXT("success read"), retFound == EEasyXMLParserFound::Found);
		auto Item0Node = rootNode->ReadElement("PurchaseOrder.Items.Item[0]", retFound);
		TestTrue(TEXT("success read"), retFound == EEasyXMLParserFound::Found);
		auto Item1Node = rootNode->ReadElement("PurchaseOrder.Items.Item[1]", retFound);
		TestTrue(TEXT("success read"), retFound == EEasyXMLParserFound::Found);

		TestEqual(TEXT("success read"), rootNode->ReadInt("PurchaseOrder.@PurchaseOrderNumber"), 99503);
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.@OrderDate"), "1999-10-20");
		TestEqual(TEXT("success read"), Address0Node->ReadString("@Type"), "Shipping");
		TestEqual(TEXT("success read"), Address0Node->ReadString("Name"), "Ellen Adams");
		TestEqual(TEXT("success read"), Address0Node->ReadString("Street"), "123 Maple Street");
		TestEqual(TEXT("success read"), Address0Node->ReadString("City"), "Mill Valley");
		TestEqual(TEXT("success read"), Address0Node->ReadString("State"), "CA");
		TestEqual(TEXT("success read"), Address0Node->ReadString("Zip"), "10999");
		TestEqual(TEXT("success read"), Address0Node->ReadString("Country"), "USA");
		TestEqual(TEXT("success read"), Address1Node->ReadString("@Type"), "Billing");
		TestEqual(TEXT("success read"), Address1Node->ReadString("Name"), "Tai Yee");
		TestEqual(TEXT("success read"), Address1Node->ReadString("Street"), "8 Oak Avenue");
		TestEqual(TEXT("success read"), Address1Node->ReadString("City"), "Old Town");
		TestEqual(TEXT("success read"), Address1Node->ReadString("State"), "PA");
		TestEqual(TEXT("success read"), Address1Node->ReadString("Zip"), "95819");
		TestEqual(TEXT("success read"), Address1Node->ReadString("Country"), "USA");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.DeliveryNotes"), "Please leave packages in shed by driveway.");
		TestEqual(TEXT("success read"), Item0Node->ReadString("@PartNumber"), "872-AA");
		TestEqual(TEXT("success read"), Item0Node->ReadString("ProductName"), "Lawnmower");
		TestEqual(TEXT("success read"), Item0Node->ReadString("Quantity"), "1");
		TestEqual(TEXT("success read"), Item0Node->ReadString("USPrice"), "148.95");
		TestEqual(TEXT("success read"), Item0Node->ReadString("Comment"), "Confirm this is electric");
		TestEqual(TEXT("success read"), Item1Node->ReadString("@PartNumber"), "926-AA");
		TestEqual(TEXT("success read"), Item1Node->ReadString("ProductName"), "Baby Monitor");
		TestEqual(TEXT("success read"), Item1Node->ReadString("Quantity"), "2");
		TestEqual(TEXT("success read"), Item1Node->ReadString("USPrice"), "39.98");
		TestEqual(TEXT("success read"), Item1Node->ReadString("ShipDate"), "1999-05-21");
	}


	{
		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromFile("PurchaseOrder.xml", false, result, errorMessage);

		EEasyXMLParserFound retFound;
		auto AddressNodes = rootNode->ReadElements("PurchaseOrder.Address", retFound);
		TestTrue(TEXT("success read"), retFound == EEasyXMLParserFound::Found);
		auto ItemNodes = rootNode->ReadElements("PurchaseOrder.Items.Item", retFound);
		TestTrue(TEXT("success read"), retFound == EEasyXMLParserFound::Found);

		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString("@Type"), "Shipping");
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString("Name"), "Ellen Adams");
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString("Street"), "123 Maple Street");
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString("City"), "Mill Valley");
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString("State"), "CA");
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString("Zip"), "10999");
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString("Country"), "USA");
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString("@Type"), "Billing");
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString("Name"), "Tai Yee");
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString("Street"), "8 Oak Avenue");
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString("City"), "Old Town");
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString("State"), "PA");
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString("Zip"), "95819");
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString("Country"), "USA");

		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString("@PartNumber"), "872-AA");
		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString("ProductName"), "Lawnmower");
		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString("Quantity"), "1");
		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString("USPrice"), "148.95");
		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString("Comment"), "Confirm this is electric");
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString("@PartNumber"), "926-AA");
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString("ProductName"), "Baby Monitor");
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString("Quantity"), "2");
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString("USPrice"), "39.98");
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString("ShipDate"), "1999-05-21");
	}

	{
		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromFile("PurchaseOrder.xml", false, result, errorMessage);

		TestEqual(TEXT("success read"), rootNode->ReadInt("PurchaseOrder.PurchaseOrderNumber"), 0);
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.OrderDate"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].Type"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].Name-"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrde-r.Address[0].Street"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address-[0].City"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0].State-"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder-.Address[0].Zip"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[0]-.Country"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1]-.@Type"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder-.Address[1].Name"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1].Stree-t"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1]-.City"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder-.Address[1].State"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1].Zip-"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Address[1]-.Country"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder-.DeliveryNotes"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[0].@PartNumber-"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[0]-.ProductName"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items-.Item[0].Quantity"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[4].USPrice"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[-1].Comment"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[8].@PartNumber"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[99].ProductName"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[7].Quantity"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[555].USPrice"), "");
		TestEqual(TEXT("success read"), rootNode->ReadString("PurchaseOrder.Items.Item[9999].ShipDate"), "");
	}

	{
		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromFile("PurchaseOrder.xml", false, result, errorMessage);

		EEasyXMLParserFound retFound;
		auto AddressNodes = rootNode->ReadElements("PurchaseOrder.Address", retFound);
		TestTrue(TEXT("success read"), retFound == EEasyXMLParserFound::Found);
		auto ItemNodes = rootNode->ReadElements("PurchaseOrder.Items.Item", retFound);
		TestTrue(TEXT("success read"), retFound == EEasyXMLParserFound::Found);

		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString("@Type-"), "");
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString("Name-"), "");
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString("Street-"), "");
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString("City-"), "");
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString("State-"), "");
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString("Zip-"), "");
		TestEqual(TEXT("success read"), AddressNodes[0]->ReadString("Country-"), "");
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString("@Type-"), "");
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString("Name-"), "");
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString("Street-"), "");
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString("City-"), "");
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString("State-"), "");
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString("Zip-"), "");
		TestEqual(TEXT("success read"), AddressNodes[1]->ReadString("Country-"), "");

		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString("@PartNumber-"), "");
		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString("ProductName-"), "");
		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString("Quantity-"), "");
		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString("USPrice-"), "");
		TestEqual(TEXT("success read"), ItemNodes[0]->ReadString("Comment-"), "");
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString("@PartNumber-"), "");
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString("ProductName-"), "");
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString("Quantity-"), "");
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString("USPrice-"), "");
		TestEqual(TEXT("success read"), ItemNodes[1]->ReadString("ShipDate-"), "");
	}

	return true;
}