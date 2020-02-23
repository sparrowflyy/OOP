#include "Player.hpp"
#include <sstream>
#include <iostream>

const std::string Player::product_type = "player";

std::string& Player::serialize()const
{
	std::stringstream data;
	data << product_type<<" "<< player_id << " " << name << " " << team_id << "\n";			
	std::string* buf = new std::string(data.str());								  
	return *buf;
}
int Player::get_id()const
{
	 return player_id; 
}



Player::Player(std::string& str)			
{
	std::istringstream stream(str);
	std::string buf;
	stream >> buf;
	try
	{
		if (buf != product_type) throw buf;
		stream >> player_id;
		stream >> name;
		stream >> team_id;
		team = nullptr;
	}
	catch (std::string& type)
	{
		std::cout << "Wrong type of Product: " << type << std::endl;

	}
}
void Player::set_team(std::shared_ptr<Team> _team)
{
	 team = _team; 
}
