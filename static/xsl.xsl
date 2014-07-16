<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" 
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns="http://www.w3.org/1999/xhtml">
   <xsl:output method="xml" encoding="utf-8" media-type="application/xhtml+xml" indent="yes"
               doctype-public="-//W3C//DTD XHTML 1.1//EN" 
               doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd" />
   
   <!--    <xsl:variable name='imgURL' select="'http://i.openlib.org.ua'" /> -->
   
   <xsl:variable name='imgURL' select="''" />
   
   <xsl:variable name='downloadKeywords'>
      <strong>Скачать книги</strong><xsl:text> </xsl:text>
      <xsl:for-each select='//MAIN/MENU/category/menu'>
            <strong><xsl:value-of select='name' /></strong>
            <xsl:if test='position() != last()'>, </xsl:if>
      </xsl:for-each>
   </xsl:variable>
   
   <xsl:template match='/'>
      <html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru">
         <head>
            <base href='http://test.altermann/' />
            <meta http-equiv='Content-Type' content='application/xhtml+xml; charset=utf-8' />
            <meta name='language' content='ru, en' />
            <meta name='description' content='OPENLIB.ORG.UA - Открытая IT-интернет библиотека' />
            <meta name='robots' content='all' />
            <meta name='generator' content='SIEGERSTEIN (OPENLIB 2.0)' />
            <meta name='author' content='Alex J. Ivasyuv' />
            
            <link rel='copyright' href='http://creativecommons.org/licenses/by-nc-sa/3.0/' />
            <link rel='shortcut icon' href='favicon.png' type='image/png' />
            
            <!--             <link rel="Prev" href="chapter4.html" /> -->
            <!--                <link rel="Next" href="chapter6.html" /> -->
            
            <!-- RSS -->
            <xsl:for-each select="//MAIN/MENU/category">
               <xsl:if test="@id_menu = 'm'">
                  <link href="/rss/{num}" rel="alternate" type="application/rss+xml" title="[RSS 2.0] {name}" />
               </xsl:if>
            </xsl:for-each>
            <!-- ATOM -->
            <xsl:for-each select="//MAIN/MENU/category">
               <xsl:if test="@id_menu = 'm'">
                  <link href="/atom/{num}" rel="alternate" type="application/atom+xml" title="[ATOM 1.0] {name}" />
               </xsl:if>
            </xsl:for-each>
            
            <title>
               <xsl:choose>
                  <xsl:when test="//MAIN/PARAMS/target = 'category'">
                     <xsl:text>Скачать книги по </xsl:text><xsl:value-of select='//category[id=//MAIN/PARAMS/id]/name' /><xsl:text> » </xsl:text>
                  </xsl:when>
                  <xsl:when test="//MAIN/PARAMS/target = 'book'">
                     <xsl:text>Скачать книгу "</xsl:text>
                     <xsl:value-of select='//BOOKS/book[id=//MAIN/PARAMS/id]/name' /><xsl:text> » </xsl:text>
                     <xsl:text>"</xsl:text>
                  </xsl:when>
               </xsl:choose>
               <xsl:text>OPENLIB.ORG.UA - Открытая IT-интернет библиотека</xsl:text>
            </title>
            
            <xsl:element name='meta'>
               <xsl:attribute name='name'>keywords</xsl:attribute>
               <xsl:attribute name='content'>
                  <xsl:value-of select="$downloadKeywords" />
               </xsl:attribute>
            </xsl:element>
            
            <link rel='stylesheet' href='style.css' type='text/css' />
         </head>
         
         <body>
            <!--             <script type="text/javascript" src="/js/pseudocursor.js"></script> -->
            <div class='topDescr'>
               <h3><strong>OPENLIB.ORG.UA</strong> - Открытая IT-интернет библиотека</h3>
               <h4>Здесь можно <strong>свободно</strong> и <strong>бесплатно</strong><xsl:text> </xsl:text><strong>скачать</strong><xsl:text> </xsl:text><strong>электронные</strong><xsl:text> </xsl:text><strong>книги</strong> на <strong>компьютерную</strong> тематику</h4>
            </div>
            <!--             <span id="pseudoCursor">|</span> -->
<!--             <div id='logo'> -->
               <!--             <canvas id='canvasLogo'> -->
                  <div id='logoM' />
                  <!--             </canvas> -->
<!--             </div> -->
            
            <div class='keyWords'>
               <h4><xsl:copy-of select="$downloadKeywords" /></h4>
            </div>
            
            <div class='center'>
               <ul class='topMenu'>
                  <li><a href='' title='Главная' >Главная</a></li>
                  <li><a href='rules' title='Правила'>Правила</a></li>
                  <li><a href='faq' title='FAQ'>FAQ</a></li>
                  <li><a href='site' title='О сайте'>О сайте</a></li>
                  <li><a href='about' title='О проекте'>О проекте</a></li>
                  <li><a href='sponsors' title='Спонсоры'>Спонсоры</a></li>
                  <li><a href='feedback' title='Обратная связь'>Связь</a></li>
               </ul>
            </div>
            
            <!--            <p>
               <a href="javascript:history.go(-1)">Go back</a>
            </p>-->
            
            <ul class='points'>
               <li><strong>Без регистрации!</strong></li>
               <li><strong>Скачивание через BitTorrent-сеть без учета трафика</strong></li>
               <li><strong>Скачивание одним кликом, прямые ссылки</strong></li>
            </ul>
            
            <xsl:apply-templates/>
         </body>
      </html>
   </xsl:template>
   
   <xsl:template match='MAIN'>
<!--       <div class='browser' /> -->
      <div>
         <xsl:apply-templates/>
      </div>
   </xsl:template>
   
   <xsl:template match='MENU'>
      <ul class='menu' id='menu'>
         <!--          <fieldset> -->
            <!--             <legend>Меню</legend> -->
            <xsl:apply-templates/>
            <!--       </fieldset> -->
      </ul>
   </xsl:template>
   
   <xsl:template match='category'>
      <xsl:if test="@name != ''">
         <li>
            <p class="_menu{@id}">
               <a href='/rss/{@id}' title='RSS 2.0' onclick="target='_blank';">
                  <img src='{$imgURL}images/main/feed-icon-14x14.png' alt='RSS 2.0' class='button14x14' />
               </a><xsl:text> </xsl:text><a href='/atom/{@id}' title='ATOM 1.0' onclick="target='_blank';">
                  <img src='{$imgURL}images/main/atom-14x14.png' alt='ATOM 1.0' class='button14x14' />
               </a>
               <xsl:text> </xsl:text><xsl:value-of select='@name' />
            </p>
         </li>
      </xsl:if>
      
      <div class="_hide{@id} hide">
      <xsl:for-each select="menu">
         <li class='_subMenu{id}'>
            <a href='javascript:void(0)' title='Скачать книги по {name}'>
               <strong><xsl:value-of select='name' /></strong>
               <xsl:value-of select='count'/>
            </a>
         </li>
      </xsl:for-each>
   </div>
   </xsl:template>
   
   <xsl:template match='CENTER'>
      <div class='content' id='content'>
         <xsl:apply-templates />
      </div>
   </xsl:template>
   
   <xsl:template match='BOOKS' />
   <xsl:template match='PARAMS' />
   
   
   <xsl:template match='BOTTOM'>
      <!--               <script type="text/javascript" charset="utf-8" src="/js/main.js"></script>
      <script type="text/javascript" charset="utf-8" src="/js/liveinternet.js"></script>
      <xsl:text> </xsl:text>
      <a href='http://www.yandex.ru/cy?base=0&amp;host=openlib.org.ua' onclick="target='_blank';">
         <img src='http://www.yandex.ru/cycounter?openlib.org.ua' width='88' height='31' alt='Яндекс цитирования' />
      </a>
      <xsl:text> </xsl:text>
      <br /><br />-->
      
      <ul  class='button'>
         <li>
            <a href='http://validator.w3.org/check?uri=referer' onclick="target='_blank';"
               title='Valid XHTML 1.0 Transitional'>
               <img src='{$imgURL}images/main/valid-xhtml11.png'
                    alt='Valid XHTML 1.1' />
            </a>
         </li>
         <li>
            <a href='http://jigsaw.w3.org/css-validator/' onclick="target='_blank';"
               title='CSS level 3'>
               <img src='{$imgURL}images/main/vcss.png'
                    alt='CSS level 3' />
            </a>
         </li>
         <li>
            <a href='http://validator.w3.org/feed/check.cgi?url=http://openlib.org.ua/rss' onclick="target='_blank';"
               title='Valid RSS 2.0'>
               <img src='{$imgURL}images/main/valid-rss.png'
                    alt='Valid RSS 2.0' />
            </a>
         </li>
         <li>
            <a href='http://validator.w3.org/feed/check.cgi?url=http://openlib.org.ua/atom' onclick="target='_blank';"
               title='Validate Atom 1.0 feed'>
               <img src='{$imgURL}images/main/valid-atom.png'
                    alt='Valid Atom 1.0' />
            </a>
         </li>
      </ul>
      <ul class='buttonSmall'>
         <li>
            <a href='http://www.mysql.com' onclick="target='_blank';"
               title='MySQL'>
               <img src='{$imgURL}images/main/mysql.png'
                    alt='MySQL' />
            </a>
         </li>
         <li>
            <a href='http://httpd.apache.org' onclick="target='_blank';"
               title='Apache'>
               <img src='{$imgURL}images/main/apache.png'
                    alt='Apache' />
            </a>
         </li>
         <li>
            <a href='http://www.unicode.org' onclick="target='_blank';"
               title='UNICODE'>
               <img src='{$imgURL}images/main/utf-8.gif'
                    alt='UNICODE' />
            </a>
         </li>
      </ul>
      <div class='copyright'>
         <xsl:text>Copyright © 2005 - 2008 by </xsl:text><a href='http://blog.siegerstein.org.ua' title='SIEGERSTEIN Blog' onclick="target='_blank';">SIEGERSTEIN</a>
      </div>
      <div class='license'>
         <a href=''>Открытая IT-интернет библиотека</a> is licensed under a<a rel='license' href='http://creativecommons.org/licenses/by-nc-sa/3.0/' onclick="target='_blank';">
            <xsl:text>Creative Commons Attribution-Noncommercial-Share Alike 3.0 Unported License</xsl:text>
         </a>
         <br /><br />
         <a rel='license' href='http://creativecommons.org/licenses/by-nc-sa/3.0/' onclick="target='_blank';">
            <img src='{$imgURL}/images/main/80x15.png' alt='Creative Commons License' 
                 title='Creative Commons Attribution-Noncommercial-Share Alike 3.0 Unported License' class='button80x15' />
         </a>
      </div>
      <script type="application/x-javascript" src="js/json2.js"></script>
      <script type="application/x-javascript" src='js/jquery/jquery.js'></script>
      <script type="application/x-javascript" src='js/jquery/jQuery.colorBlend.js'></script>
      <script type="application/x-javascript" src='js/jquery/effects.core.js'></script>
<!--       <script type="application/x-javascript" src='js/jquery/effects.explode.js'></script> -->
      <script type="application/x-javascript" src='js/jquery/effects.scale.js'></script>
      <script type="application/x-javascript" src='js/js.js'></script>
      <script type="application/x-javascript" src='js/ajax.js'></script>
   </xsl:template>
</xsl:stylesheet>
