#pragma once
#include "Product.hpp"
#include "Player.hpp"
#include <vector>
class Team : public Product
{
public:
	Team(std::string& str);
	int get_id() const;
	std::string& serialize() const;
	void add_player(std::shared_ptr<Player> _player);
	bool operator==(const Team& another) const
	{
		return team_id == another.team_id && name == another.name && players_id == another.players_id;
	}
	int get_type() const { return 1; };
	
	std::string get_name() const { return name; }
	std::vector<std::shared_ptr<Player>> get_vector_of_players() const { return players; };
	static const std::string product_type;
	std::vector<int> players_id;
private:
	int team_id;
	std::string name;
	std::vector<std::shared_ptr<Player>> players;

};