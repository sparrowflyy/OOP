#include "./gtest/gtest.h"
#include "..//football_team/Football_factory.hpp"

static std::vector<std::string> players = { "player 10 Messi 100\n","player 7 Ronaldo 100\n","player 11 Rooni 100\n","player 12 Kerzhakov 100\n","player 8 Lampard 100\n",
											"player 13 Drofa 66\n","player 22 Surzhikov 66\n","player 43 Vorobyov 66\n","player 18 Semushev 66\n","player 33 Aidakov 66\n"};
static std::vector<std::string> teams = { "team 100 Barcelona 10 7 11 12 8\n","team 66 Fizfuk 13 22 43 18 33\n" };
static std::vector<std::string> matches = { "match 1377 30.11.2019 Novosibirsk 7:0 66 100\n", "match 1388 31.12.2019 Milan 23:0 66 100\n" };

static void insert_data_to_stream(std::stringstream& stream)
{
	for (auto it = players.begin(); it != players.end(); ++it)
	{
		stream << *it;
	}
	for (auto it = teams.begin(); it != teams.end(); ++it)
	{
		stream << *it;
	}
	for (auto it = matches.begin(); it != matches.end(); ++it)
	{
		stream << *it;
	}
}
TEST(player,player_constructor)
{
	Player test_player(players[0]);
	EXPECT_TRUE(test_player.get_id() == 10);
	EXPECT_TRUE(test_player.team_id == 100);
	EXPECT_TRUE(test_player.get_name() == "Messi");
}
TEST(player,serialize)
{
	Player test_player(players[0]);
	std::string player_info = test_player.serialize();
	EXPECT_TRUE(player_info==players[0]);
}
TEST(player, set_team_get_team)
{
	Player player(players[0]);
	Team team(teams[0]);
	player.set_team(std::make_shared<Team>(team));
	EXPECT_TRUE(team == *player.get_team().get());
}
TEST(player, equal)
{
	Player player1(players[0]);
	Player player2(players[0]);
	EXPECT_TRUE(player1==player2);
}
TEST(player,get_name)
{
	Player player(players[0]);
	EXPECT_EQ("Messi", player.get_name());
}
TEST(team,team_constructor)
{
	std::vector<int> pl = { 10,7,11,12,8 };
	Team test_team(teams[0]);
	EXPECT_TRUE(test_team.get_id() == 100);
	EXPECT_TRUE(test_team.players_id == pl);
	EXPECT_TRUE(test_team.get_name() == "Barcelona");
}
TEST(team, serialize)
{
	Team test_team(teams[0]);
	std::string team_info = test_team.serialize();
	EXPECT_TRUE(team_info == teams[0]);
}

TEST(team, equal)
{
	Team team1(teams[0]);
	Team team2(teams[0]);
	EXPECT_TRUE(team1 == team2);
}
TEST(team, get_name)
{
	Team team(teams[0]);
	EXPECT_EQ("Barcelona", team.get_name());
}
TEST(match,match_constructor)
{
	Match test_match(matches[0]);				//match 1377 30.11.2019 Novosibirsk 7:0 66 100
	EXPECT_TRUE(test_match.get_id() == 1377);
	EXPECT_TRUE(test_match.get_date() == "30.11.2019");
	EXPECT_TRUE(test_match.get_location() == "Novosibirsk");
	EXPECT_TRUE(test_match.get_result() == "7:0");
	EXPECT_TRUE(test_match.teamid1 == 66);
	EXPECT_TRUE(test_match.teamid2 == 100);
}
TEST(match, serialize)
{
	Match test_match(matches[0]);
	std::string match_info = test_match.serialize();
	EXPECT_TRUE(match_info == matches[0]);
}
TEST(match, equal)
{
	Match match1(matches[0]);
	Match match2(matches[0]);
	EXPECT_TRUE(match1 == match2);
}
TEST(football_factory, correct_read) {
	Football_factory factory;
	std::stringstream stream;
	insert_data_to_stream(stream);
	factory.read(stream);
	int i = 0;
	for (auto it = factory.players_begin();it!=factory.players_end();++it)
	{
		EXPECT_EQ((*it)->serialize(), players[i]);
		i++;
	}
	i = 0;
	for (auto it = factory.teams_begin();it!=factory.teams_end();++it)
	{
		EXPECT_EQ((*it)->serialize(),teams[i]);
		i++;
	}
	i = 0;
	for (auto it = factory.mathes_begin(); it != factory.mathes_end(); ++it)
	{
		EXPECT_EQ((*it)->serialize(), matches[i]);
		i++;
	}
}
TEST(football_factory,correct_write)
{
	Football_factory factory;
	std::stringstream stream;
	insert_data_to_stream(stream);
	factory.read(stream);
	std::stringstream first_out;
	factory.write(first_out);
	std::string written_by_factory = first_out.str();
	
	Football_factory another_factory;
	another_factory.read(first_out);
	std::stringstream second_out;
	another_factory.write(second_out);
	std::string written_by_another_factory = second_out.str();
	
	EXPECT_TRUE(written_by_factory == written_by_another_factory);
}

TEST(football_factory,binding_and_finding_players)
{
	Football_factory factory;
	std::stringstream stream;
	insert_data_to_stream(stream);					//"player 10 Messi 100\n","player 7 Ronaldo 100\n","player 11 Rooni 100\n","player 12 Kerzhakov 100\n","player 8 Lampard 100\n",
	factory.read(stream);						 //"player 13 Drofa 66\n", "player 22 Surzhikov 66\n", "player 43 Vorobyov 66\n", "player 18 Semushev 66\n", "player 33 Aidakov 66\n"
	std::vector<int> players_id = { 10,7,11,12,8,13,22,43,18,33};
	for (size_t i =0; i<players_id.size()/2;i++)
	{
		auto it = factory.find_player(players_id[i]);
		EXPECT_TRUE((*it).get()->get_team().get()->serialize() == teams[0]);
	}
	for (size_t i = players_id.size() / 2; i < players_id.size(); i++)
	{
		auto it = factory.find_player(players_id[i]);
		EXPECT_TRUE((*it).get()->get_team().get()->serialize() == teams[1]);
	}
}

TEST(football_factory, binding_and_finding_teams)
{
	Football_factory factory;
	std::stringstream stream;
	insert_data_to_stream(stream);					
	factory.read(stream);
	std::vector<std::shared_ptr<Player>> players_from_first_team = factory.find_team(100)->get()->get_vector_of_players();
	for (auto it = players_from_first_team.begin();it!=players_from_first_team.end();++it)
	{
		auto player_iter=factory.find_player((*it).get()->get_id());
		EXPECT_TRUE(player_iter != factory.players_end());
		EXPECT_TRUE((*it).get()->serialize() == player_iter->get()->serialize());
	}
	std::vector<std::shared_ptr<Player>> players_from_second_team = factory.find_team(66)->get()->get_vector_of_players();
	for (auto it = players_from_second_team.begin(); it != players_from_second_team.end(); ++it)
	{
		auto player_iter = factory.find_player((*it).get()->get_id());
		EXPECT_TRUE(player_iter != factory.players_end());
		EXPECT_TRUE((*it).get()->serialize() == player_iter->get()->serialize());
	}
}
TEST(football_factory,binding_and_finding_matches)
{
	Football_factory factory;
	std::stringstream stream;
	insert_data_to_stream(stream);
	factory.read(stream);
	auto first_match = factory.find_match(1377);
	auto first_team = factory.find_team(66);
	auto second_team = factory.find_team(100);
	EXPECT_TRUE(first_match->get()->get_team_first() == *first_team);
	EXPECT_TRUE(first_match->get()->get_team_second() == *second_team);
}