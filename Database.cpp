#include "Database.h"
#include <vector>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

void Database::createConnection()
{
	
	try
	{
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
//		stmt->executeUpdate("insert into profile values ('" + name + "', " + to_string(s) + ");");
		std::string x = "insert into profile (username, score) values ( '" +  name + "', " + to_string(s) + " )";
//		stmt->executeUpdate(x);
	}
	catch (sql::SQLException &e)
	{
		printf("CANNOT CONNECT");
		CCLOG("CANNOT CONNECT");
	}
}

std::vector<Profile*> Database::read()
{
	try
	{
		res = stmt->executeQuery("select username, score from profile order by score desc;");
		// 
		std::string data;
		std::vector<Profile*> leaderboard;

		for (int x = 0; res->next() && x < 5; x++)
		{
			std::string user = res->getString("username").c_str();
			int userScore = res->getInt("score");

			leaderboard.push_back(new Profile(user, userScore));
		}
	}

	catch (sql::SQLException &e)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	std::vector<Profile*> p;
	return p;
	//return leaderboard;
}

void Database::del()
{
}