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

#include "config.hpp"

namespace Site {
   Config * Config ::_config = NULL;
   
   Config::Config ( void ) { }
   Config::~Config ( void ) {
      delete this -> cfg; this -> cfg = NULL;
   }

   Config * Config::Instance ( void ) {
      if ( _config == NULL ) {
            _config = new Config();
      }
      return ( _config );
   }

   void Config::init ( void ) {
      this -> cfg = new libconfig::Config;

      try {
         this -> cfg -> readFile ( "../../config.cfg" );
      }
      catch ( ... ) {
         std::cerr << "libconfig::Error: Fail to open config file ../../config.cfg" << std::endl;
         exit ( -1 );
      }
   }
}

