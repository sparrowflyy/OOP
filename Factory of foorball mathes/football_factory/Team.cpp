#include "Team.hpp"
#include <sstream>
#include <iterator>
#include <iostream>
const std::string Team::product_type = "team";

Team::Team(std::string& str)
{
	std::istringstream stream(str);		 //type id name players_id*11
	std::string buf;
	stream >> buf;
	try
	{
		if (buf != product_type) throw buf;
		stream >> team_id;
		stream >> name;
		std::copy(std::istream_iterator<int>(stream), {}, std::back_inserter(players_id));
	}
	catch (std::string& type)
	{
		std::cout << "Wrong type of Product: " << type << std::endl;

	}
}
int Team::get_id ()	const
{
	return team_id; 
}

std::string& Team::serialize() const
{
	std::stringstream data;
	data << product_type<<" "<< team_id << " " << name;
	for (auto it = players_id.begin(); it != players_id.end(); ++it)
	{
		data <<" "<< *it;
	}
	data << "\n";
	std::string* buf = new std::string(data.str());
	return *buf;
}
void Team::add_player(std::shared_ptr<Player> _player)
{
	players.push_back(_player);
}
