#include<iostream>
#include "C:\Users\cauec\DungeonCrawlerCMD\SimpleOnline\NetCommon\dungeon_network.h"

enum class CustomMsgTypes : uint32_t
{
	ServerAccept,
	ServerDeny,
	SpellConsult,
	MessageAll,
	ServerMessage,
};

class CustomServer : public dungeon::network::server_interface<CustomMsgTypes>
{
private:
	std::string spells_[5] = {"BurningHands", "CharmPerson", "CureWounds", "MageArmor", "Thunderwave"};
public:
	CustomServer(uint16_t nPort) : dungeon::network::server_interface<CustomMsgTypes>(nPort)
	{

	}

protected:
	virtual bool on_client_connect(std::shared_ptr<dungeon::network::connection<CustomMsgTypes>> client) override
	{
		dungeon::network::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::ServerAccept;
		client->send(msg);

		return true;
	}

	virtual void OnClientDisconnect(std::shared_ptr<dungeon::network::connection<CustomMsgTypes>> client) override
	{
		std::cout << "Removing client [" << client->get_id() << "]\n";
	}

	void on_message(const std::shared_ptr<dungeon::network::connection<CustomMsgTypes>> client, dungeon::network::message<CustomMsgTypes>& msg) override
	{
		switch (msg.header.id)
		{
		case CustomMsgTypes::SpellConsult:
			std::cout << "\n[" << client->get_id() << "]: Server Ping\n";

			std::string msg_body;
			//read msg body
			for (size_t i = 0; i < msg.body.size() - 1; i++)
			{
				if (msg.body[i] == '\0')
					break;

				msg_body += msg.body[i];
			}

			dungeon::network::message<CustomMsgTypes> answer;
			
			if (msg_body == spells_[0])
				answer << "As you hold your hands with thumbs touching and fingers spread, a thin sheet of flames shoots forth from your outstretched fingertips. Each creature in a 15-foot cone must make a dexterity saving throw. A creature takes 3d6 fire damage on a failed save, or half as much damage on a successful one. The fire ignites any flammable objects in the area that aren’t being worn or carried.";
			else if (msg_body == spells_[1])
				answer << "You attempt to charm a humanoid you can see within range. It must make a wisdom saving throw, and does so with advantage if you or your companions are fighting it. If it fails the saving throw, it is charmed by you until the spell ends or until you or your companions do anything harmful to it. The charmed creature regards you as a friendly acquaintance. When the spell ends, the creature knows it was charmed by you.";
			else if (msg_body == spells_[2])
				answer << "A creature you touch regains a number of hit points equal to 1d8 + your spellcasting ability modifier. This spell has no effect on undead or constructs.";
			else if (msg_body == spells_[3])
				answer << "You touch a willing creature who isn’t wearing armor, and a protective magical force surrounds it until the spell ends. The target’s base AC becomes 13 + its Dexterity modifier. The spell ends if the target dons armor or if you dismiss the spell as an action.";
			else if (msg_body == spells_[4])
				answer << "A wave of thunderous force sweeps out from you. Each creature in a 15-foot cube originating from you must make a constitution saving throw. On a failed save, a creature takes 2d8 thunder damage and is pushed 10 feet away from you. On a successful save, the creature takes half as much damage and isn’t pushed.In addition, unsecured objects that are completely within the area of effect are automatically pushed 10 feet away from you by the spell’s effect, and the spell emits a thunderous boom audible out to 300 feet.";
			else
			{
				answer << "Unidentified spell";
				std::cout << "Unidentified spell";
			}

			std::cout << "Player is requesting knowledge for " << msg_body.data() << " spell";
			answer.header.id = CustomMsgTypes::ServerMessage;
			client->send(answer);
			break;
		default:
			std::cout << "Invalid MsgType";
			break;
		}
	}
};

int main()
{
	CustomServer server(60000);
	server.start();

	while (true)
	{
		server.update(150, false);
	}

	return 0;
}