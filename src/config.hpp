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

#ifndef __SS_SITE_CONFIG_HPP_
#define __SS_SITE_CONFIG_HPP_

#include <iostream>
#include <string>
#include <cstdlib> //system
#include <sstream>
#include <string.h> // strcmp

extern "C" {
   #include <cgi.h>
}

#include <libconfig.h++>

std::string toString ( int val );
int toInt ( std::string str );
std::string retExec ( std::string command );

namespace Site {
   class Config {
      public:
         ~Config ( void );

         static Config * Instance ( void );
         void init ( void );

         libconfig::Config * getCfg ( void ) { return ( this -> cfg ); }
         const int returnCurrentYear ( void ) const { return system ("date \"+%Y\""); }
      private:
         Config ( void );

         static Config * _config;
         
         // libconfig
         libconfig::Config * cfg;
   };
}

#endif

