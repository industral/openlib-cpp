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

#ifndef __SS_SITE_DB_HPP_
#define __SS_SITE_DB_HPP_

#include "config.hpp"

namespace Site {
   class DB {
      public:
         DB ( void ) { };
         virtual ~DB ( void ) { };
         
         virtual bool init ( std::string host, std::string dbName, std::string dbUser, std::string pass ) = 0;
//          mysqlpp::Connection * getConnection ( void )  const { return ( this -> conn ); }
      private:
//          mysqlpp::Connection * conn;
   };
}

#endif
