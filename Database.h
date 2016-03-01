#ifndef _DATABASE_H_

#define _DATABASE_H_

#include <string>
#include <iostream>
#include <vector>
#include "Profile.h"
class Database
{
public:
/*
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
*/
	Database() { createConnection(); }
	/*!
	* Create database connection
	*/
	void createConnection();

	/*
	* Insert Data to the database
	*/
	void write(std::string, int);

	/*
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