That's very crappy code that I was written back in 2008 when I was young. Leaving it just for history.
--------------


Source code for back in 2008 site openlib.org.ua.

Techs:
  * C++
  * MySQL/PostgreSQL
  * XML/XSLT/XHTML
  * Torrents
  

1. Depends:

   - libpqxx ( PostgreSQL db )
   - libmysql++ ( MySQL db )
   - libconfig++ ( http://sourceforge.net/projects/config-plus/ )
   - libcgi ( http://www.infodrom.org/projects/cgilib/ )
   - hashlib++  ( http://hashlib2plus.sourceforge.net )
   - libcurl

2. Install

   make - build core
   make install - deploy site

3. Know Issue:

Path for cgilib v0.6


```cpp
--- /usr/include/cgi.h.default    2008-04-06 12:43:42.000000000 +0300
+++ /usr/include/cgi.h            2008-06-06 22:22:55.000000000 +0300
@@ -143,7 +143,7 @@
 char *cgiEscape (char *string);

#ifdef __cplusplus
-extern }
+}
#endif

#endif /* _CGI_H_ */
```
