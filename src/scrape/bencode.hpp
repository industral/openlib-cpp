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

#ifndef __SS_BENCODE_BENCODE_HPP_
#define __SS_BENCODE_BENCODE_HPP_

#include "config.hpp"

namespace Bencode {
   class Bencode {
      public:
         Bencode ( void );
         ~Bencode ( void );
         
         bool open ( std::string torrentFile ); // взять содержимое файла в строку
         bool parse ( void );
         
         // curl
         void writeScrapeAnswer ( std::string answer ) { this -> scrapeAnswer = answer; }
         std::string showRawScrapeAnswer ( void ) { return ( this -> scrapeAnswer ); }
         
         // get-методы
         std::map < std::string, std::string > getTorrentInfo ( void ) const { return ( this -> torrentInfo ); }
         std::string getURLInfoHash ( void );
         bool makeScrape ( void );
         std::string getJSONScrapeAnswer ( void );
      private:
         std::string toString ( int val );
         int toInt ( std::string str );
         int toInt ( char str );
         int fileSize ( std::ifstream & ifile );
         
         hashwrapper * myWrapper; // объект sha1
         // Переменные
         std::map < std::string, std::string > torrentInfo;
         std::ifstream inputFile; // файловый дискриптор файла
         int size; // размер файла
         char * buffer;
         
         std::string dataString; // содержимое torrent-файла в виде строки
         
         // bittorrent
         std::string info;
         std::string URLInfoHash;
         
         // curl
         std::string scrapeAnswer;
         struct Scrape {
            std::string complete;
            std::string downloaded;
            std::string incomplete;
         } scrape;
   };
}

#endif
