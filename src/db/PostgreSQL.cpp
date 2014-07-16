/***************************************************************************
*   Copyright (C) 2008 by Alex J. Ivasyuv                                 *
*   admin@openlib.org.ua                                                  *
*                                                                         *
*   This program is free software: you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation, either version 3 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
***************************************************************************/

#include "PostgreSQL.hpp"

namespace Site {
   PostgreSQL::PostgreSQL ( void ) { }
   PostgreSQL::~PostgreSQL ( void ) {
      delete this -> C; this -> C = 0;
   }
   
   bool PostgreSQL::init ( std::string host, std::string dbName, std::string dbUser ) {
      std::string connectString = "host=" + host + " dbname=" + dbName + " user=" + dbUser;
      try {
         this -> C = new pqxx::connection ( connectString );
//          this -> C -> trace ( stderr );
      }
      catch ( const pqxx::sql_error &e ) {
         std::cerr << "SQL error: " << e.what() << std::endl
               << "Query was: " << e.query() << std::endl;
         return 1;
      }
      catch ( const std::exception &e ) {
         std::cerr << "Exception: " << e.what() << std::endl;
         return 2;
      }
      catch (...) {
         std::cerr << "Unhandled exception" << std::endl;
         return 100;
      }
      return true;
   }
}
