#include "Database.h"
#include <vector>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

void Database::createConnection()
{
	
	try
	{
//		con = driver->connect("eu-cdbr-azure-north-d.cloudapp.net", "bc2a6cfa292f50", "1004b8f2");
//		con->setSchema("gamesfleadh2016");

	}		
	catch(sql::SQLException &e)
	{
		try
		{
			driver = get_driver_instance();
			con = driver->connect("localhost", "root", "password");
			con->setSchema("gamesfleadh2016");

			stmt = con->createStatement();
		}
		catch(sql::SQLException &e)
		{
			printf("CANNOT CONNECT");
		}
	}
	
}

void Database::write(std::string name, int s)
{
	try
	{
		driver = get_driver_instance();
		con = driver->connect("localhost", "root", "password");
		con->setSchema("gamesfleadh2016");
		stmt = con->createStatement();
		std::string t = "insert into profile values ('" + name + "', " + to_string(s) + ");";
		const char * x = t.c_str();
		stmt->executeUpdate(x);
	}
	catch (sql::SQLException &e)
	{
		printf("CANNOT CONNECT");
		CCLOG("CANNOT CONNECT");
	}
}


std::vector<Profile*> Database::read()
{
	std::vector<Profile*> leaderboard;
	try
	{
		try 
		{
		    /*
			online_driver = get_driver_instance();
			online_con = online_driver->connect("eu-cdbr-azure-north-d.cloudapp.net", "bc2a6cfa292f50", "1004b8f2");
			online_con->setSchema("gamesfleadh2016");

			stmt = online_con->createStatement();

			res = stmt->executeQuery("select username, score from profile order by score desc;");

			for (int x = 0; res->next() && x < 5; x++)
			{
				std::string user = res->getString("username").c_str();
				int userScore = res->getInt("score");
				leaderboard.push_back(new Profile(user, userScore));
			}
			*/
			CCLOG("Leaderboard size %d", leaderboard.size());
			
			if (leaderboard.size()!=4) 
			{
				if (leaderboard.size() == 0) 
				{
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
				}
				if (leaderboard.size() == 1)
				{
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
				}
				if (leaderboard.size() == 2)
				{
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
				}
				if (leaderboard.size() == 3)
				{
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
				}
				if (leaderboard.size() == 4)
				{
					leaderboard.push_back(new Profile("", 0));
				}
			
			}
		}
		catch (sql::SQLException &e) {
			CCLOG("Cannot connect to online database");
			//CCLOG("Leaderboard size %d", leaderboard.size());

			if (leaderboard.size() != 4)
			{
				if (leaderboard.size() == 0)
				{
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
				}
				if (leaderboard.size() == 1)
				{
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
				}
				if (leaderboard.size() == 2)
				{
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
				}
				if (leaderboard.size() == 3)
				{
					leaderboard.push_back(new Profile("", 0));
					leaderboard.push_back(new Profile("", 0));
				}
				if (leaderboard.size() == 4)
				{
					leaderboard.push_back(new Profile("", 0));
				}
			}
		}

		try
		{
			//for (int j = 0; j < 5; j++)
			//{
			//	leaderboard.push_back(new Profile("test", 100));
			//}

			driver = get_driver_instance();
			con = driver->connect("localhost", "root", "password");
			con->setSchema("gamesfleadh2016");

			stmt = con->createStatement();

			res = stmt->executeQuery("select username, score from profile order by score desc;");
			// 
			std::string data;


			for (int x = 0; res->next() && x < 5; x++)
			{
				std::string user = res->getString("username").c_str();
				int userScore = res->getInt("score");

				leaderboard.push_back(new Profile(user, userScore));
			}
		}
		catch (sql::SQLException &e)
		{

		}
		//leaderboard.push_back(new Profile("test", 60));
	}

	catch (sql::SQLException &e)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	return leaderboard;
}

void Database::del()
{
}