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

#include "bencode.hpp"

extern "C" {
   #include <cgi.h>
}

// Ф-ция для выполнения комманды, сохранения ее результата в переменной + удаления перевода каретки
std::string retExec ( std::string command ) {
   FILE * ptr; // file hand
   char buf [ 255 ]; // buffer
   std::string str; // возращаемая строка
   if ( ( ptr = popen ( command.c_str(), "r" ) ) != NULL ) { // открываем
      while ( fgets ( buf, 255, ptr ) != NULL ) {
         str += buf; // записываем результат
      }
   }
   pclose ( ptr ); // закрываем
   // Удаляем \n \t символы ( chomp в Perl )
   std::string::size_type pos = str.find_last_not_of ( "\n \t" );
   if ( pos != std::string::npos ) {
      str = str.substr ( 0, pos + 1 );
   }
   return str;
}

int main ( void ) {
   Bencode::Bencode * be = new Bencode::Bencode();
   
   s_cgi * cgi;
   cgi = cgiInit();
   
   std::string torrentPath = "../../torrents";
   std::string id;
   if ( cgiGetValue ( cgi, "id" ) != NULL ) {
      id = cgiGetValue ( cgi, "id" );
   }

   std::string torrentFile = retExec ( "ls \"" + torrentPath + "/[" + id + "]\""  + "*" );
   be -> open ( torrentFile );
   be -> parse();

   be -> makeScrape();
   std::cout << be -> getJSONScrapeAnswer() << std::endl;

   delete be; be = NULL;
   cgiFree ( cgi );
   
   return 0;
}
