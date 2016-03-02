#ifndef _DATABASE_H_

#define _DATABASE_H_

#include <string>
#include <iostream>
#include <vector>
#include "Profile.h"
#include <stdlib.h>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class Database
{
public:

	sql::Driver *driver;
	sql::Connection *con;
	sql::Driver *online_driver;
	sql::Connection *online_con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	sql::PreparedStatement *prep;

	Database()
	{
		createConnection();
	}
	~Database()
	{
//		con->close();
//		delete this;
	}


	/*!
	* Create database connection
	*/
	void createConnection();

	/*!
	* Insert Data to the database
	*/
	void write(std::string, int);

	/*!
	*Read data from database
	*/
	std::vector<Profile*> read();
	
	/*!
	Close the database connection
	*/
	void del();

private:

};

#endif