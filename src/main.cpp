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

#include "main.hpp"

namespace Site {
   Page::Page ( void ) : config ( Config::Instance() )
   { }

   Page::~Page ( void ) {
      delete this -> sql; this -> sql = NULL;
#ifdef POSTGRESQL
      delete this -> sql2; this -> sql2 = NULL;
#endif
      cgiFree ( this -> cgi );
   }

   void Page::init ( void ) {
      this -> cfg = this -> config -> getCfg();

      std::string db_Host = this -> cfg -> lookup ( "dbHost" );
      std::string db_Db = this -> cfg -> lookup ( "dbName" );
      std::string db_UserName = this -> cfg -> lookup ( "dbUser" );
      std::string db_Password = this -> cfg -> lookup ( "dbPassword" );

      this -> initCGI();
#ifdef POSTGRESQL
      this -> sql = new PostgreSQL;
      this -> sql2 = new PostgreSQL;
      this -> sql -> init ( db_Host, db_Db, db_UserName );
      this -> sql2 -> init ( db_Host, db_Db, db_UserName );

      this -> C = this -> sql -> getConnection();
      this -> C2 = this -> sql2 -> getConnection();
#elif MYSQL
      this -> sql = new MySQL;
      this -> sql -> init ( db_Host, db_Db, db_UserName, db_Password );
      this -> C = this -> sql -> getConnection();
#endif
   }

   void Page::initCGI ( void ) {
      this -> cgi = cgiInit();
   }

   int Page::bookCount ( std::string target, std::string category ) {
      std::string queryString;
      if ( target == "category" && !category.empty() ) {
         queryString = "SELECT COUNT(*) FROM books WHERE category=\'" + category + "\'";
      } else if ( target == "first" ) {
         queryString = "SELECT COUNT(*) FROM books WHERE books.show = '1'";
      }
#ifdef POSTGRESQL
         pqxx::work W ( *this -> C2 );
         size_t Rows = 0;
         try {
//          std::string resultString = "SELECT COUNT(*) FROM books WHERE category=" + category;
//          std::cout << "RESULT_STRING: " << resultString << std::endl;
            pqxx::result R ( W . exec ( queryString ) );

            if ( R . empty() ) {
               throw std::logic_error ( "No tables found!" );
            } else {
               R[0][0].to(Rows);
            }
         }
         catch ( const pqxx::sql_error &e ) {
            std::cerr << "SQL error: " << e.what() << std::endl
                  << "Query was: " << e.query() << std::endl;
            return 1;
         }
         catch ( const std::exception &e ) {
            std::cerr << "Exception in PostgreSQL at bookCount() with Query: " << queryString << e.what() << std::endl;
            return 2;
         }
         catch (...) {
            std::cerr << "Unhandled exception" << std::endl;
            return 100;
         }
         return Rows;
#elif MYSQL
         mysqlpp::Query query = this -> C -> query ( queryString );
         mysqlpp::StoreQueryResult R = query.store();
         if ( R.size() == 0) {
            std::cerr << "No result!: " << queryString << std::endl;
         } else {
            return ( R[0][0] );
         }
#endif
      }


   int Page::showMainPage ( void ) {
      std::string _id;
      std::string _page;
      std::string queryString;
      std::string _target;
      int count = -1;

//       std::cerr << "2: " << ( std::string ( cgiGetValue ( cgi, "first" ) ) != "" ) << std::endl;
//       std::cerr << "3: " << ( cgiGetValue ( cgi, "category" ) != NULL ) << std::endl;
      try {
         int _pages = -1; // количество страниц в данной категории
          // если на главной странице или выбрали категорию
         if ( ( cgiGetValue ( cgi, "first" ) != NULL ) || ( cgiGetValue ( cgi, "category" ) != NULL ) ) {
          // если на главной странице
         if ( cgiGetValue ( cgi, "first" ) != NULL ) {
            _target = "first";
            count = this -> bookCount ( _target, "" );
            // показать все книги из категории
         } else if ( cgiGetValue ( cgi, "category" ) != NULL ) {
            _target = "category";
            _id = std::string ( cgiGetValue ( cgi, "category" ) );
            count = this -> bookCount ( _target, _id );
         }

         if ( cgiGetValue ( cgi, "page" ) == NULL ) {
            _page = "1";
         } else {
            _page = std::string ( cgiGetValue ( cgi, "page" ) );
         }

            if ( count <= 0 ) { // ошибка, количество книг должно быть > 0
//                std::cout << "</BOOKS>\n" << std::endl; // чтобы страница была валидной
               std::cerr << "No result!: " << queryString << std::endl;
               return false;
            }
            /*
            Если число книг к примеру 36, то делим это число на количество показываемых книг на страницу ( 10 )
            В итоге получаем 3 ( int ).
            Потом смотрим нету ли остатка от деления, если есть - добавляем единицу.
            Вот и получили количество страниц в данной категории
            */
            // получить число страниц
            int result = count / 10;
            // если есть остаток от деления, значит добавляем еще одну страницу
            if ( count % 10 > 0 ) { ++result; }
            _pages = result;
            this -> paramPages = result; // записываем параметр

            // }
            int page = toInt ( _page );
            if ( page <= 0 ) { // если GET - запрос страницы <= 0, ставим в 1
               page = 1;
               _page = "1"; // меняем глобальную переменную
            } else if ( page > this -> paramPages ) { // если больше максимального - ставим в максимальное
               page = this -> paramPages;
               _page = toString ( this -> paramPages ); // меняем глобальную перенменную
            }

            std::string offset = toString ( page * 10 - 10 );

/*            if ( cgiGetValue ( cgi, "category" ) != NULL &&
                 strcmp ( cgiGetValue ( cgi, "type" ), "feed" ) == 0 ) { // если выбираем категорию
               std::string category = std::string ( cgiGetValue ( cgi, "category" ) );
               queryString = "SELECT bc.category_name, b . * FROM books b INNER JOIN books_category bc ON "
                     "b.category = bc.id_category WHERE bc.category = '" + category + "' AND b.show = '1' ORDER BY date DESC LIMIT 30 OFFSET 0";
            } else */if ( cgiGetValue ( cgi, "category" ) != NULL ) {
               queryString = "SELECT * FROM books WHERE category = \'" + _id + "\' AND books.show = '1' ORDER BY date DESC LIMIT 10 OFFSET " + offset;
            } else if ( cgiGetValue ( cgi, "first" ) != NULL ) {
               queryString = "SELECT * FROM books WHERE books.show = '1' ORDER BY date DESC LIMIT 10 OFFSET " + offset;
            } else {
               std::cerr << "Can't build query! No target present" << std::endl;
               exit ( -1 );
            }
//             std::cerr << "QUERY: " << queryString << std::endl;
         } else if ( cgiGetValue ( cgi, "book" ) != NULL ) { // если выбрали книгу
            _target = "book";
            _id = std::string ( cgiGetValue ( cgi, "book" ) );
            std::string _book_id = std::string ( cgiGetValue ( cgi, "book" ) );
            queryString = "SELECT * FROM books WHERE book_id = '" + _book_id + "\' AND books.show = '1' ORDER BY date DESC";
         } else {
            std::cout << "</BOOKS>\n" << std::endl; // чтобы страница была валидной
            std::cerr << "No result!: " << queryString << std::endl;
            return false;
         }
#ifdef POSTGRESQL
         pqxx::work W ( *this -> C );
         pqxx::result R = W . exec ( queryString );
         if ( R . empty() ) {
            throw std::logic_error ( "No result!" );
         }
#elif MYSQL
         mysqlpp::Query query = this -> C -> query ( queryString );
         mysqlpp::StoreQueryResult R = query.store();
         if ( R.size() == 0) {
            std::cerr << "No result!: " << queryString << std::endl;
         }
#endif
#ifdef POSTGRESQL
         for ( pqxx::result::size_type i = 0; i != R.size(); ++i )
#elif MYSQL
            for ( size_t i = 0; i < R.num_rows(); ++i )
#endif
         {
            std::cout <<
                  "<book>\n" << 
                  "<id>" << R [i]["book_id"] << "</id>\n" <<
                  "<category>" << R[i]["category"] << "</category>\n" <<
//                   "<book id=\'" << R [i]["book_id"] << "\' category=\'" << R[i]["category"] << "\'>\n" <<
                  "<name>" << R [i]["name"] << "</name>\n" <<
                  "<orig>" << R [i]["orig"] << "</orig>\n" <<
                  "<author>" << R[i]["author"] << "</author>\n" <<
                  "<pages>" << R[i]["pages"] << "</pages>\n" <<
                  "<publisher>" << R[i]["publisher"] << "</publisher>\n" <<
                  "<isbn>" << R[i]["isbn"] << "</isbn>\n" <<
                  "<lang>" << R[i]["lang"] << "</lang>\n" <<
                  "<mime>" << R[i]["mime"] << "</mime>\n" <<
                  "<size char='" << R[i]["size_char"] << "\'>" << R[i]["size"] << "</size>\n" <<
//       "<show>" << R[i]["show"] << "</show>" <<
                  "<short_descr>" << R[i]["short_descr"] << "</short_descr>\n" <<
                  "<full_descr>" << R[i]["full_descr"] << "</full_descr>\n" <<
                  "<date>" << R[i]["date"] << "</date>\n" <<
//                   "<watch>" << R[i]["watch"] << "</watch>\n" <<
//                   "<rate>" << R[i]["rate"] << "</rate>\n" <<
                  "<url>" << R[i]["url"] << "</url>\n" <<
                  "<img>" << R[i]["img"] << "</img>\n" <<
                  "</book>\n" <<
                  std::endl;
         }
         // записываем параметры страницы:
         this -> paramTarget = _target;
         this -> paramCategory = _id;
         this -> paramCurrPage = _page;
      }
#ifdef POSTGRESQL
      catch ( const pqxx::sql_error &e ) {
         std::cerr << "SQL error: " << e.what() << std::endl
               << "Query was: '" << e.query() << "'" << std::endl;
         return 1;
      } catch ( const std::exception &e  ) {
         std::cerr << "Exception in PostgreSQL at showMainPage() with Query: " << queryString << e.what() << std::endl;
         return 2;
      } catch ( ... ) {
         std::cerr << "Unhandled exception" << std::endl;
         return 100;
      }
#elif MYSQL
      catch ( const mysqlpp::BadQuery& er ) {
        // Handle any query errors
         std::cerr << "Query error: " << er.what() << std::endl;
         return false;
      }
      catch ( const mysqlpp::BadConversion& er ) {
        // Handle bad conversions; e.g. type mismatch populating 'stock'
         std::cerr << "Conversion error: " << er.what() << std::endl <<
               "\tretrieved data size: " << er.retrieved <<
               ", actual size: " << er.actual_size << std::endl;
         return false;
      }
      catch ( const mysqlpp::Exception& er ) {
        // Catch-all for any other MySQL++ exceptions
         std::cerr << "Error: " << er.what() << std::endl;
         return false;
      }
#endif
      return 0;
   }

   void Page::showTop ( void ) {
      std::cout << "<table><tr><td>"
            "<img src='logo.jpg' alt = '' />"
            "МЕТА-портал компьютерной литературы"
            "</td></tr></table>"
            << std::endl;
   }

   void Page::showMenu ( void ) {
      std::string queryString = "SELECT * FROM books_category ORDER BY step";
      std::string _id;
      bool lastId = false;
#ifdef POSTGRESQL
      pqxx::work W ( *this -> C );
      pqxx::result R = W . exec ( queryString );
      if ( R.size() == 0) {
         std::cerr << "No result!: " << queryString << std::endl;
      }
      for ( pqxx::result::size_type i = 0; i < R.size(); ++i )
#elif MYSQL
      mysqlpp::Query query = this -> C -> query ( queryString );
      mysqlpp::StoreQueryResult R = query.store();
      if ( R.size() == 0) {
         std::cerr << "No result!: " << queryString << std::endl;
      }
      for ( size_t i = 0; i < R.num_rows(); ++i )
#endif
      {
         _id = std::string ( R [i]["id_menu"].c_str() );
         if ( _id == "m" ) {
            if ( lastId ) {
               std::cout << "</category>\n";
            }
            lastId = true;
            std::cout << "<category id='" << R [i]["category"] << "' name='" << R [i]["category_name"] << "'>\n";
         }
         if ( _id == "s" ) {
            std::cout <<
                  "\t<menu>\n" <<
                  "\t\t<name>" << R [i]["category_name"] << "</name>\n" <<
                  "\t\t<id>" << R [i]["id_category"] << "</id>\n" <<
                  "\t\t<count>" << this -> bookCount ( "category", std::string ( R [i]["id_category"].c_str() ) ) << "</count>\n" <<
                  "\t</menu>\n";
         }
      }
      std::cout << "</category>\n";
   }

   void Page::showParams ( void ) {
      //FIXME: Как это перебрать напрямую в XLST без указания RSS & ATOM здесь?
      std::cout << "<feed>rss</feed>\n"
            "<feed>atom</feed>\n"
            "<target>" << this -> paramTarget << "</target>\n"
            "<id>" << this -> paramCategory << "</id>\n"
            "<pages>" << this -> paramPages << "</pages>\n"
            "<curPage>" << this -> paramCurrPage << "</curPage>\n";
   }
   
//    bool Page::showRSS ( void ) {
// //       http://beshenov.ru/rss2.html
// 
//       std::string OS = this -> cfg -> lookup ( "OS" );
//       std::string imageURL = this -> cfg -> lookup ( "imageURL" );
// 
//       std::string queryString;
//       std::string category;
//       if ( cgiGetValue ( cgi, "category" ) != NULL ) { // если выбираем категорию
//          category = std::string ( cgiGetValue ( cgi, "category" ) );
//          queryString = "SELECT bc.category_name, b . * FROM books b INNER JOIN books_category bc ON "
//                "b.category = bc.id_category WHERE bc.category = '" + category + "' AND b.show = '1' LIMIT 0, 30";
//       } else {
//          queryString = "SELECT * FROM books WHERE books.show = '1' ORDER BY book_id DESC LIMIT 0, 30";
//       }
// 
//       std::string projectName = this -> cfg -> lookup ( "projectName" );
//       std::string projectURL = this -> cfg -> lookup ( "projectURL" );
// 
//       std::cout <<
//             "<rss version='2.0' xmlns:atom='http://www.w3.org/2005/Atom'>\n"
//             "<channel>\n"
//             "<atom:link href='" << projectURL << "/rss/" << category << "' " << "rel='self' type='application/rss+xml' />\n"
//             // обязательные параметры {
//             "<title>" << projectName + " - Открытая IT-интернет библиотека" << "</title>\n"
//             "<link>" << projectURL << "</link>\n"
//             "<description>" << projectName + " - Новые книги на сайте" << "</description>\n"
//             // }
//             // Необязательные параметры {
//             "<language>ru-ru</language>\n"
//             "<copyright>Copyright &#169; 2005-2008 SIEGERSTEIN</copyright>\n"
//             "<managingEditor>rss@openlib.org.ua (Alex J. Ivasyuv)</managingEditor>\n"
//             "<webMaster>rss@openlib.org.ua (Alex J. Ivasyuv)</webMaster>\n"
// //             "<pubDate>" << std::flush;
// //       system ("date -R");
// //       std::cout << "</pubDate>\n"
// //             "<lastBuildDate></lastBuildDate>\n"
// //             "<generator></generator>\n"
//             "<docs>http://www.rssboard.org/rss-specification</docs>\n"
//             "<ttl>1440</ttl>\n" /*12 часов*/
//             "<image>\n"
//             "<url>" << imageURL << "/images/main/logo/logo.png</url>\n"
//             "<title>" << projectName + " - Открытая IT-интернет библиотека" << "</title>\n"
//             "<link>" << projectURL << "</link>\n"
//             // необязательные параметры {
//             "<width>144</width>\n"
//             "<height>117</height>\n"
//             "<description>Главная</description>\n"
//             // }
//             "</image>\n"
// //             "<textInput>\n"
// //             "<title>Отправить</title>\n"
// //             "<description>Написать комментарий</description>\n"
// //             "<name>Комментарий</name>\n"
// //             "<link>" << projectURL << "/rss/feedback</link>\n"
// //             "</textInput>\n"
//             // }
//             << std::endl;
// 
//       mysqlpp::Query query = this -> C -> query ( queryString );
//       mysqlpp::StoreQueryResult R = query.store();
//       if ( R.size() == 0) {
//          std::cerr << "No result!: " << queryString << std::endl;
//          std::cout <<
//                "</channel>\n"
//                "</rss>\n"
//                << std::endl;
//          return true;
//       }
// 
//       for ( size_t i = 0; i < R.num_rows(); ++i ) {
//          std::cout <<
//                "<item>\n"
//                "<title>" << R[i]["name"] << "</title>\n"
//                "<link>" << projectURL << "/book/" << R[i]["book_id"] << "</link>\n"
//                "<guid>" << projectURL << "/book/" << R[i]["book_id"] << "</guid>\n"
//                "<description>" << 
// 
//                "<![CDATA["
//                "<table>"
// //             "<tr>"
// //             "<td colspan='2'>"
// //             "<strong>"
// //             "<a href='" << projectURL << "/book/" << R[i]["id"] << "' target='_blank'>" << R[i]["name"] << "</a>"
// //             "</strong>"
// //             "</td>"
// //             "</tr>"
//                "<tr>"
//                "<td width='5%'>"
//                "<a href='" << imageURL << "/images/thumbnail/books/100/" << R[i]["book_id"] << ".jpg' target='_blank'>"
//                "<img src='" << imageURL << "/images/thumbnail/books/0/" << R[i]["book_id"] << ".jpg' align='left' hspace='5' border='0' alt='' height='86' width='60' />"
//                "</a>"
//                "</td>"
//                "<td align='left'>" << R[i]["author"] << "<br /><br />"
//                "<strong> Издательство: " << R[i]["publisher"] << "</strong><br />"
//                "<strong> ISBN: " << R[i]["isbn"] << "</strong>"
//                "</td>"
//                "</tr>"
//                "<tr>"
//                "<td colspan='2'>" << R[i]["short_descr"] << "</td>"
//                "</tr>"
//                "</table>"
//                "]]>"
// 
//                << "</description>\n";
//       /*
//          Переводим дату типа 2006-04-24 04:06:41 в RFC-822 http://www.w3.org/Protocols/rfc822/
//          http://validator.w3.org/feed/docs/warning/ProblematicalRFC822Date.html
//          ( Mon, 24 Apr 2006 04:06:41 GMT )
//          date -d'2006-04-15 04:12:06' -R // GNU/Linux
//          date -j -f '%Y-%m-%d %T' '2006-04-15 04:12:06' +'%a, %e %b %Y %T GMT' // FreeBSD
//                {
//       */
//                   std::string date = R[i]["date"].c_str();
//                   std::string execString;
//                   if ( OS == "Linux" ) {
//                      execString = "date -d'";
//                      execString += date + "' -R";
//                   } else if ( OS == "FreeBSD" ) {
//                      execString = "date -j -f '%Y-%m-%d %T' '";
//                      execString += date + "' +'%a, %d %b %Y %T GMT'";
//                   }
//                   std::string result = retExec (execString);
//       // }
//                   std::cout << "<pubDate>" << result << "</pubDate>\n"
//                         "</item>\n"
//                         << std::endl;
//                }
//                std::cout <<
//                      "</channel>\n"
//                      "</rss>\n"
//                      << std::endl; // закрываем теги
//       }
   
//       bool Page::showAtom ( void ) {
//       // http://atompub.org/rfc4287.html
//       // http://tools.ietf.org/html/rfc4946
// 
//       //TODO: При наличии коментариев добавить http://tools.ietf.org/html/rfc4685
//       //TODO: Добавить http://tools.ietf.org/html/rfc5005
// 
//          std::string imageURL = this -> cfg -> lookup ( "imageURL" );
//          
//          std::string queryString;
//          std::string category;
//          if ( cgiGetValue ( cgi, "category" ) != NULL ) { // если выбираем категорию
//             category = std::string ( cgiGetValue ( cgi, "category" ) );
//             queryString = "SELECT bc.category_name, b . * FROM books b INNER JOIN books_category bc ON "
//                   "b.category = bc.id_category WHERE bc.category = '" + category + "' AND b.show = '1' LIMIT 0, 30";
//          } else {
//             queryString = "SELECT * FROM books WHERE books.show = '1' ORDER BY book_id DESC LIMIT 0, 30";
//          }
// 
//          std::string OS = this -> cfg -> lookup ( "OS" );
//          std::string projectName = this -> cfg -> lookup ( "projectName" );
//          std::string projectURL = this -> cfg -> lookup ( "projectURL" );
// 
//          std::cout <<
//                "<feed xmlns='http://www.w3.org/2005/Atom'>\n"
//                "<link href='" << projectURL << "/atom/" << category << "' " << "rel='self' type='application/atom+xml' />\n"
//                "<icon>" << projectURL << "/favicon.ico</icon>\n"
//                "<logo>" << imageURL << "/images/main/logo/logo.png</logo>\n"
//                "<title>" << projectName + " - Открытая IT-интернет библиотека" << "</title>\n"
//                "<link href='" << projectURL << "' />\n"
//             // http://tools.ietf.org/html/rfc4946
//                "<link rel='license' type='application/rdf+xml' href='http://creativecommons.org/licenses/by-nc-sa/3.0/rdf' />\n"
//                "<rights>\n"
//                "Открытая IT-интернет библиотека is licensed under a"
//                "Creative Commons Attribution-Noncommercial-Share Alike 3.0 Unported License"
//                "</rights>\n";
// 
//             /*
//          Переводим текущею дату в rfc3339 http://www.ietf.org/rfc/rfc3339.txt ( 2006-04-24T04:06:41Z )
//          date +%FT%TZ // GNU/Linux + FreeBSD
//             */
//          std::string result = retExec ("date +%FT%TZ");
//          std::cout << "<updated>" << result << "</updated>\n"
//                "<author>\n"
//                "<name>Alex J. Ivasyuv</name>\n"
//                "<email>rss@openlib.org.ua</email>\n"
//                "</author>\n"
// 
//                "<id>" << projectURL << "/atom/" << category << "</id>\n"
//                << std::endl;
// 
//          mysqlpp::Query query = this -> C -> query ( queryString );
//          mysqlpp::StoreQueryResult R = query.store();
//          if ( R.size() == 0) {
//             std::cerr << "No result!: " << queryString << std::endl;
//             std::cout << "</feed>" << std::endl;
//             return true;
//          }
// 
//          for ( size_t i = 0; i < R.num_rows(); ++i ) {
//             std::cout <<
//                   "<entry>\n"
//                // http://tools.ietf.org/html/rfc4946
//                   "<link rel='license' type='text/html' href='http://creativecommons.org/licenses/by-nc-sa/3.0/' />"
//                   "<title>" << R[i]["name"] << "</title>\n"
//                   "<link href='" << projectURL << "/book/" << R[i]["book_id"] << "' />\n"
//                   "<id>" << projectURL << "/book/" << R[i]["book_id"] << "</id>"
//                   "<summary type='xhtml'>"
//                   "<div xmlns='http://www.w3.org/1999/xhtml'>"
//                   "<table>"
// //             "<tr>"
// //             "<td colspan='2'>"
// //             "<strong>"
// //             "<a href='" << projectURL << "/book/" << R[i]["id"] << "' target='_blank'>" << R[i]["name"] << "</a>"
// //             "</strong>"
// //             "</td>"
// //             "</tr>"
//                   "<tr>"
//                   "<td width='5%'>"
//                   "<a href='" << imageURL << "/images/thumbnail/books/100/" << R[i]["book_id"] << ".jpg' target='_blank'>"
//                   "<img src='" << imageURL << "/images/thumbnail/books/0/" << R[i]["book_id"] << ".jpg' align='left' hspace='5' border='0' alt='' height='86' width='60' />"
//                   "</a>"
//                   "</td>"
//                   "<td align='left'>" << R[i]["author"] << "<br /><br />"
//                   "<strong> Издательство: " << R[i]["publisher"] << "</strong><br />"
//                   "<strong> ISBN: " << R[i]["isbn"] << "</strong>"
//                   "</td>"
//                   "</tr>"
//                   "<tr>"
//                   "<td colspan='2'>" << R[i]["short_descr"] << "</td>"
//                   "</tr>"
//                   "</table>"
//                   "</div>"
//                   << "</summary>\n";
//             /*
//             Переводим дату типа 2006-04-24 04:06:4 в rfc3339 http://www.ietf.org/rfc/rfc3339.txt
//             ( 2006-04-24T04:06:41Z )
//             date -d'2006-04-24 04:06:41' +%FT%TZ // GNU/Linux
//             date -j -f '%Y-%m-%d %T' '2006-04-24 04:06:41' +%FT%TZ // FreeBSD
//             */
// 
//             std::string date = R[i]["date"].c_str();
//             std::string execString;
//             if ( OS == "Linux" ) {
//                execString = "date -d'" + date + "' +%FT%TZ";
//             } else if ( OS == "FreeBSD" ) {
//                execString = "date -j -f '%Y-%m-%d %T' '" + date + "' +%FT%TZ";
//             }
//             std::string result = retExec (execString);
//             std::cout << "<updated>" << result << "</updated>\n"
//                   "</entry>\n"
//                   << std::endl;
//          }
//          std::cout << "</feed>" << std::endl; // закрываем теги
//       }
   }
