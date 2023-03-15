#include<iostream>
#include<dungeon_network.h>
#include <iomanip>

enum class CustomMsgTypes : uint32_t
{
	ServerAccept,
	ServerDeny,
	SpellConsult,
	MessageAll,
	ServerMessage,
};

class CustomClient : public dungeon::server::client_interface<CustomMsgTypes>
{
public:
	void ConsultSpell(const char* spell)
	{
		std::cout << "\nRetrieving knowledge from the Arcane realm for [" << spell << "] spell...\n";
		dungeon::server::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::SpellConsult;

		//Copying to an array because we can't simply copy char* data
		char spellArray[40];
		strcpy_s(spellArray, spell);
		msg << spellArray;

		send(msg);
	}
};

void handle_input(CustomClient& client);
void handle_messages(CustomClient& client);
bool inputEnabled = true;
bool quit = false;

int main()
{
	CustomClient client;

	client.connect("192.168.18.30", 60000);

	std::cout << "<-~- . - ~-> D&D SPELL CONSULT <-~- . - ~->";
	std::cout << "\n1 - Burning Hands \n2 - Charm Person \n3 - Cure Wounds \n4 - Mage Armor \n5 - Thunderwave\n0 - Quit Application\n\n";

	while (!quit)
	{
		handle_messages(client);

		// if (inputEnabled)
		// 	handle_input(client);
	}

	return 0;
}

void handle_input(CustomClient& client)
{
	int input;
	std::cout << "[Type your wish] - ";
	std::cin >> input;
	inputEnabled = false;

	switch (input)
	{
	case 0:
		quit = true;
		break;
	case 1:
		client.ConsultSpell("BurningHands");
		break;
	case 2:
		client.ConsultSpell("CharmPerson");
		break;
	case 3:
		client.ConsultSpell("CureWounds");
		break;
	case 4:
		client.ConsultSpell("MageArmor");
		break;
	case 5:
		client.ConsultSpell("Thunderwave");
		break;
	default:
		std::cout << "Please type a number between 1 and 5";
		break;
	}
}

void handle_messages(CustomClient& client)
{
	if (!client.is_connected())
	{
		std::cout << "Oracle is dead :(\n";
		return;
	}

	if (!client.incoming().empty())
	{
		const auto msg = client.incoming().pop_front().msg;

		switch (msg.header.id)
		{
		case CustomMsgTypes::ServerMessage:

			std::cout << "the oracle says...\n\n_______________________\n" << msg.body.data() << "\n_______________________\n\n";
			inputEnabled = true;
			break;
		default:
			break;
		}
	}
}
