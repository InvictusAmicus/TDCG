#include "Database.h"
#include <vector>
/*
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
*/
void Database::createConnection()
{
	/*
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
		catch
		{

		}
	}
	*/
}

void Database::write(std::string name, int s)
{
/*	
	stmt->execute("create table if not exists profile( username varchar(20), score int(6));");

	stmt->executeUpdate("insert into playerprofile values (name, s);");
*/
}

std::vector<Profile*> Database::read()
{
/*
	try
	{
		res = stmt->executeQuery("select username, score from profile order by score desc;");
		// 
		std::string data;
		std::vector<Profile*> leaderboard;

		while (res->next())
		{
			std::istream* retrievedPassword_stream = res->getBlob("username");
			//			cout << retrievedPassword_stream << endl;
			//if (retrievedPassword_stream)
			//{
			//	char pws[11] = "helloworld";
			//	retrievedPassword_stream->getline(pws, 10);
			//	std::string x = pws;
			//	//std::string retrievedPassword(pws);
			//	cout << x << endl;
			//	cout << res->getBlob("username") << "\t";
			//cout << res->getString("username") << ":\t";
			//cout << res->getBlob("name") << ":\t";
			//cout << res->getInt("score") << endl;
			
			std::string user = res->getBlob("username");
			int userScore = res->getInt(score);

			leaderboard.push_back(new Profile(user, userScore));
			
		
			}
		}

		
		delete res;
		delete stmt;
		delete con;
	}

	catch (sql::SQLException &e)
	{
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
*/
	std::vector<Profile*> p;
	return p;
	//return leaderboard;
}

void Database::del()
{
/*
	delete res;
	delete stmt;
	delete con;
*/
}