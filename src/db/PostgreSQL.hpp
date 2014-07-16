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

#ifndef __SS_SITE_POSTGRESQL_HPP_
#define __SS_SITE_POSTGRESQL_HPP_

#include "config.hpp"
#include <pqxx/pqxx>

namespace Site {
   class PostgreSQL {
      public:
         PostgreSQL ( void );
         ~PostgreSQL ( void );
         
         bool init ( std::string host, std::string dbName, std::string dbUser );
         pqxx::connection * getConnection ( void ) const { return ( this -> C ); }
      private:
         pqxx::connection * C;
   };
}

#endif
