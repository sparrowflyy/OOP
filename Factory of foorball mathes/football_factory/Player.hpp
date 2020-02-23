#pragma once
#include "Product.hpp"
#include "Team.hpp"

class Player : public Product
{
public:
	Player(std::string& str);
	std::string& serialize()const;
	int get_id () const;
	bool operator==(const Player& another) const
	{
		return (player_id == another.player_id) && (name == another.name) && (team_id==another.team_id);
	}
	int get_type() const { return 0; };
	
	std::string get_name() const { return name; }
	std::shared_ptr<Team> get_team() const { return team; };

	void set_team(std::shared_ptr<Team> _team);
	int team_id;
	static const std::string product_type;
private:
	int player_id;

	std::string name;
	std::shared_ptr<Team> team;
};