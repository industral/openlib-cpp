/***************************************************************************
*   Copyright (C) 2008 by Alex J. Ivasyuv                                 *
*   admin@openlib.org.ua                                               *
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

#include "config.hpp"

#ifdef POSTGRESQL
   #include "db/PostgreSQL.hpp"
#elif MYSQL
   #include "db/MySQL.hpp"
#endif

namespace Site {
   class Page {
      public:
         Page();
         ~Page();

         void showContentType ( std::string type );
         void showHead ( std::string type );

         int showMainPage ( void );
         void init ( void );
         void initCGI ( void );
         void showTop ( void );
         void showMenu ( void );
         void showParams ( void );
         // Feeds
//          bool showRSS ( void );
//          bool showAtom ( void );
         
         inline int bookCount ( std::string target, std::string category );
      private:
#ifdef POSTGRESQL
         PostgreSQL * sql;
         PostgreSQL * sql2;
         pqxx::connection * C;
         pqxx::connection * C2;
#elif MYSQL
         MySQL * sql;
         MySQL * sql2;
         mysqlpp::Connection * C;
         mysqlpp::Connection * C2;
#endif
         s_cgi * cgi;
         int currentYear;
         
         std::string paramTarget;
         std::string paramCategory;
         int paramPages;
         std::string paramCurrPage;

         // config
         Config * config;
         libconfig::Config * cfg; // libconfig
   };
}
