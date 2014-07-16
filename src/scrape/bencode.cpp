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

#include "bencode.hpp"

static void write_data ( void * ptr, size_t size, size_t nmemb, void * data ) {
   std::stringstream ss;
   ss.write ( ( char * ) ptr, nmemb );
   static_cast < Bencode::Bencode * > ( data ) -> writeScrapeAnswer ( ss.str() );
}

namespace Bencode {
   // Конструктор
   Bencode::Bencode ( void ):
         myWrapper ( new sha1wrapper ), size ( -1 ), buffer ( NULL )
         { }
   
   // Деструктор
         Bencode::~Bencode ( void ) {
            delete[] this -> buffer; this -> buffer = NULL;
            delete this -> myWrapper; this -> myWrapper = NULL;
            this -> inputFile.close();
         }
   
         bool Bencode::open ( std::string torrentFile ) {
            this -> inputFile.open ( torrentFile.c_str(), std::ifstream::in | std::ifstream::binary ); // открываем файл для чтения
            if ( !this -> inputFile.good() ) {
               std::cerr << "Ошибка открытия файла `" << torrentFile << "`" << std::endl;
               exit ( 127 );
            }
            this -> size = this -> fileSize ( this -> inputFile ); // получаем размер файла
            this -> buffer = new char [ this -> size ]; // создаем буфер
            this -> inputFile.read ( this -> buffer, this -> size ); // считываем файл в буфер
      
            std::stringstream ss; // создаем stringstream объект
            ss.write ( buffer, this -> size ); // записываем все в него
            this -> dataString = ss.str(); // записываем содержимое файла в виде строки
            return true;
         }
         
         // Парсинг файла
         bool Bencode::parse ( void ) {
            int length = 0;
            unsigned int iterator = 0;
            int firstIt = 0;
            
            std::string tmpKey, tmpValue;
            // читаем первый символ
            // если это d
            if ( this -> dataString [ iterator ] == 'd' ) {
               ++iterator;
               // считываем число
               do {
//                   std::cout << firstIt << ":" << iterator + length << ":" << std::endl;
                  firstIt = iterator = iterator + length;
                  while ( this -> dataString [ iterator ] != ':' ) {
                     length = this -> toInt ( this -> dataString.substr ( firstIt, iterator ) );
                     ++iterator;
                  }
               // если далее `:` то читаем ключ и значение
                  if ( this -> dataString [ iterator ] == ':' ) {
                  // ключ
                     tmpKey =  this -> dataString.substr ( ++iterator, length ); // ключ
                  
                     if ( tmpKey == "info" ) {
                        this -> info = this -> dataString.substr ( iterator + 4, this -> size - iterator - 5 );
                        this -> torrentInfo [ "infoHash" ] = myWrapper -> getHashFromString ( this -> info );
                        return true;
                     }
                  
                     firstIt = iterator = iterator + length;
                  
                  // значение
                  // если далее `i` то читаем значение
                     if ( this -> dataString [ iterator ] == 'i' ) {
                        length = this -> dataString.find_first_of ( 'e', iterator ) - iterator - 1;
                        tmpValue = this -> dataString.substr ( ++iterator, length ); // значение
                        ++iterator;
                     } else {
                        while ( this -> dataString [ iterator ] != ':' ) {
                           length = this -> toInt ( this -> dataString.substr ( firstIt, iterator ) );
                           ++iterator;
                        }
                        tmpValue = this -> dataString.substr ( ++iterator, length ); // значение
                     }

                     this -> torrentInfo [ tmpKey ] = tmpValue; // записываем полученый результат
                  }
               } while ( this -> dataString.size() >= iterator );
            }
            return true;
         }
         
         std::string Bencode::getURLInfoHash ( void ) {
            this -> URLInfoHash = this -> torrentInfo [ "infoHash" ];
            int iterator = 0;
            for ( int i = 0; i < 20; ++i ) {
               this -> URLInfoHash.insert ( iterator, "%" );
               iterator += 3;
            }
            return ( this -> URLInfoHash );
         }

   // ---------------------------------------------------------------------------
   //  Private methods
   // ---------------------------------------------------------------------------
   
         std::string Bencode::toString ( int val ) {
            std::stringstream ss;
            ss << val;
            return ( ss.str() );
         }

         int Bencode::toInt ( std::string str ) {
            std::stringstream i;
            i << str;
            int resVal = -1;
            i >> resVal;
            return ( resVal );
         }
         
         int Bencode::toInt ( char str ) {
            std::stringstream i;
            i << str;
            return ( this -> toInt ( i.str() ) );
         }
         
         int Bencode::fileSize ( std::ifstream & ifile ) {
            ifile.seekg ( 0, std::ios::end );
            int size = ifile.tellg();
            ifile.seekg ( 0, std::ios::beg );
            return ( size );
         }
         
         bool Bencode::makeScrape ( void ) {
            CURL * curl = NULL;

            curl = curl_easy_init();
            if ( curl ) {
               std::string URL = ( ( this -> torrentInfo [ "announce" ].substr ( 0, this -> torrentInfo [ "announce" ].find ( "announce" ) ) ) + "scrape?info_hash=" + this -> getURLInfoHash() );

//                std::cout << URL << std::endl;
               curl_easy_setopt ( curl, CURLOPT_URL, URL.c_str() );
               curl_easy_setopt ( curl, CURLOPT_WRITEFUNCTION, write_data );
               curl_easy_setopt ( curl, CURLOPT_WRITEDATA, this );

               curl_easy_perform ( curl );
               curl_easy_cleanup ( curl );
            }
            return true;
         }
         
         std::string Bencode::getJSONScrapeAnswer ( void ) {
            std::map < std::string, std::string > keyList;
            keyList [ "complete" ];
            keyList [ "downloaded" ];
            keyList [ "incomplete" ];

            for ( std::map < std::string, std::string >::iterator it = keyList.begin(); it != keyList.end(); ++it ) {
               int iterator = this -> scrapeAnswer.find ( it -> first + "i" ) + it -> first.size() + 1;
               while ( this -> scrapeAnswer [ iterator ] != 'e' ) {
                  keyList [ it -> first ] += this -> scrapeAnswer [ iterator ];
                  ++iterator;
               }
            }

            std::string outJSONString;
            outJSONString += "{";
            for ( std::map < std::string, std::string >::iterator it = keyList.begin(); it != keyList.end(); ++it ) {
               outJSONString += "\"" + it -> first + "\":" + it -> second;
               if ( it != --keyList.end() ) {
                  outJSONString += ",";
               }
            }
            outJSONString += "}";
            return ( outJSONString );
         }
   
}
