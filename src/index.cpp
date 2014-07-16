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

#include <iostream>
//#include <pqxx/pqxx>
#include "config.hpp"
#include "main.hpp"


std::string toString ( int val ) {
   std::stringstream ss;
   ss << val;
   return ( ss.str() );
}

int toInt ( std::string str ) {
   std::istringstream i ( str );
   int resVal = -1;
   i >> resVal;
   return ( resVal );
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


int main ( int argc, char** argv ) {
	
   Site::Config * config = Site::Config::Instance();
   Site::Page * page = new Site::Page;
   
   config -> init();
   page -> init();

//    if ( std::string ( argv[1] ) == "--rss" ) {
//       page -> showContentType ( "rss" );
// //       page -> showHead ( "rss" );
// //       page -> showRSS();
//       return 0;
//    } else if ( std::string ( argv[1] ) == "--atom" ) {
//       page -> showContentType ( "atom" );
//       page -> showHead ( "atom" );
// //       page -> showAtom();
//       return 0;
//    } else if ( std::string ( argv[1] ) == "--xhtml" ) {
//       page -> showContentType ( "xhtml" );
// //       page -> showHead ( "xhtml" );
//    } else if ( std::string ( argv[1] ) == "--parse" ) {
//       page -> showHead ( "stuff" );
//    }

   std::cout << "<ROOT>" << std::endl;
   std::cout << "<MAIN>" << std::endl;
   
   std::cout << "<MENU>" << std::endl;
//    std::cout << "<CATEGORY>" << std::endl;
   page -> showMenu();
//    std::cout << "</CATEGORY>" << std::endl;
   std::cout << "</MENU>" << std::endl;
   
   std::cout << "<CENTER>" << std::endl;
   
   std::cout << "<BOOKS>" << std::endl;
   page -> showMainPage();
   std::cout << "</BOOKS>\n" << std::endl;
   
   std::cout << "<PARAMS>" << std::endl;
   page -> showParams();
   std::cout << "</PARAMS>" << std::endl;

   std::cout << "</CENTER>" << std::endl;
   
   std::cout << "</MAIN>" << std::endl;

   std::cout << "<BOTTOM>" << std::endl; // <---- Оставить!
   std::cout << "</BOTTOM>" << std::endl;
   std::cout << "</ROOT>" << std::endl;


   delete config; config = NULL;
   delete page; page = NULL;
	
   return 0;
}
