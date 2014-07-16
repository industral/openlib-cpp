<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" 
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:xlink="http://www.w3.org/1999/xlink"
                exclude-result-prefixes="xlink">

   <xsl:output method="xml" encoding="utf-8" omit-xml-declaration='yes' />

         <xsl:strip-space elements="*" />
   <!--    <xsl:variable name='imgURL' select="'http://i.openlib.org.ua'" /> -->
   <xsl:variable name='imgURL' select="''" />
   
   <!--Замена символов-->
   <xsl:template name="replaceCharsInString">
      <xsl:param name="stringIn"/>
      <xsl:param name="charsIn"/>
      <xsl:param name="charsOut"/>
      <xsl:choose>
         <xsl:when test="contains($stringIn,$charsIn)">
            <xsl:value-of select="concat(substring-before($stringIn,$charsIn),$charsOut)"/>
            <xsl:call-template name="replaceCharsInString">
               <xsl:with-param name="stringIn" select="substring-after($stringIn,$charsIn)"/>
               <xsl:with-param name="charsIn" select="$charsIn"/>
               <xsl:with-param name="charsOut" select="$charsOut"/>
            </xsl:call-template>
         </xsl:when>
         <xsl:otherwise>
            <xsl:value-of select="$stringIn"/>
         </xsl:otherwise>
      </xsl:choose>
   </xsl:template>

   <xsl:template match='MAIN'>
         <xsl:apply-templates/>
   </xsl:template>
   
   <xsl:template match='MENU' />
   <xsl:template match='category' />
   <xsl:template match='PARAMS' />
   
   <xsl:template match='BOOKS'>
      <xsl:apply-templates />
      
      <!--      <div class='menuBottom'>
         <a href='/rss' title='RSS 2.0' onclick="target='_blank';">
            <img src='{$imgURL}images/main/rss20.png' alt='RSS 2.0' />
         </a><xsl:text> </xsl:text><a href='/atom' title='ATOM 1.0' onclick="target='_blank';">
            <img src='{$imgURL}images/main/atom.png' alt='ATOM 1.0' />
         </a>
      </div>-->
   </xsl:template>
   
   <xsl:template match='book'>
      <div class='bookBorder'>
         <span class='border'>
            <xsl:text>Книги » </xsl:text>
            <xsl:value-of select='//category/menu[id=current()/category]/../@name' />
            <xsl:text> » </xsl:text>
            <xsl:value-of select='//category/menu[id=current()/category]/name' />
         </span>
         
         <h2>
            <xsl:value-of select='name' />
         </h2>
         <div class='book_id'>
            <a href='javascript:void(0)' onclick='loadContent({id}, "book")' title='Перейти к книге'>#<xsl:value-of select='id' /></a>
         </div>
         <xsl:variable name="imgPath">
            <xsl:choose>
               <xsl:when test="img = 1">
                  <xsl:value-of select="$imgURL" />/images/thumbnail/books/100/<xsl:value-of select="id" /><xsl:text>.jpg</xsl:text>
               </xsl:when>
               <xsl:otherwise>
                  <xsl:value-of select="$imgURL" />/images/thumbnail/default.png
               </xsl:otherwise>
            </xsl:choose>
         </xsl:variable>
         
         <div class='bookImg'>
<!--             <canvas width='210' height='310'> -->
               <img src='{$imgPath}' alt='{name}' title='{name}' />
<!--             </canvas> -->
         </div>
         <ul class='bookInfo'>
            <li>
               <span>
                  <xsl:choose>
                     <xsl:when test="contains(author, ',')">
                        <xsl:text>Авторы: </xsl:text>
                     </xsl:when>
                     <xsl:otherwise>
                        <xsl:text>Автор: </xsl:text>
                     </xsl:otherwise>
                  </xsl:choose>
               </span>
               <xsl:value-of select='author' />
            </li>
            <xsl:if test='pages != 0'>
               <li><span>Страниц: </span><xsl:value-of select='pages' /></li>
            </xsl:if>
            <xsl:if test='publisher != ""'>
               <li><span>Издатель: </span><xsl:value-of select='publisher' /></li>
            </xsl:if>
            <xsl:if test='isbn != ""'>
               <li><span>ISBN: </span><xsl:value-of select='isbn' /></li>
            </xsl:if>
            <li><span class='bold' >Язык: </span>
               <xsl:choose>
                  <xsl:when test="lang = 'ru'">
                     <xsl:text>Русский</xsl:text>
                  </xsl:when>
                  <xsl:when test="lang = 'en'">
                     <xsl:text>Английский</xsl:text>
                  </xsl:when>
               </xsl:choose>
            </li>
            <li><span>Формат: </span>
               <xsl:choose>
                  <xsl:when test="mime = 'djvu'">
                     <a href='http://ru.wikipedia.org/wiki/DjVu' onclick="target='_blank';" title='Информация на Википедии'>
                        <xsl:text>DjVu</xsl:text>
                     </a>
                  </xsl:when>
                  <xsl:when test="mime = 'pdf'">
                     <a href='http://ru.wikipedia.org/wiki/PDF' onclick="target='_blank';" title='Информация на Википедии'>
                        <xsl:text>PDF</xsl:text>
                     </a>
                  </xsl:when>
                  <xsl:when test="mime = 'chm'">
                     <a href='http://ru.wikipedia.org/wiki/Microsoft_Compiled_HTML_Help' onclick="target='_blank';" title='Информация на Википедии'>
                        <xsl:text>HTMLHelp</xsl:text>
                     </a>
                  </xsl:when>
                  <xsl:when test="mime = 'html'">
                     <a href='http://ru.wikipedia.org/wiki/HTML' onclick="target='_blank';" title='Информация на Википедии'>
                        <xsl:text>HTML</xsl:text>
                     </a>
                  </xsl:when>
                  <xsl:when test="mime = 'odt'">
                     <a href='http://ru.wikipedia.org/wiki/OpenDocument' onclick="target='_blank';" title='Информация на Википедии'>
                        <xsl:text>OpenDocument</xsl:text>
                     </a>
                  </xsl:when>
                  <xsl:when test="mime = 'txt'">
                     <xsl:text>txt</xsl:text>
                  </xsl:when>
               </xsl:choose>
            </li>
            <li><span>Размер: </span><xsl:value-of select='size' />
               <xsl:choose>
                  <xsl:when test="size/@char = 'mb'">
                     <xsl:text>Мб</xsl:text>
                  </xsl:when>
                  <xsl:when test="size/@char = 'kb'">
                     <xsl:text>Кб</xsl:text>
                  </xsl:when>
               </xsl:choose>
            </li>
         </ul>
         <blockquote>
            <p>
               <xsl:choose>
                  <xsl:when test="//PARAMS/target = 'book'">
                     <xsl:value-of select='full_descr' />
                  </xsl:when>
                  <xsl:otherwise>
                     <xsl:value-of select='short_descr' />
                  </xsl:otherwise>
               </xsl:choose>
            </p>
         </blockquote>
         <div class='statistic' id='{id}'>
            <a href='javascript:void(0)' id='{id}'>Показать статистику</a>
         </div>
         <xsl:if test="lang = 'en'">
            <a href='javascript:void(0)' onclick='loadContent(880)'>Проблемы с английским языком?</a>
         </xsl:if>
         <p>
            <xsl:choose>
               <xsl:when test='url != ""'>
                  
                  <xsl:variable name="downloadURL">
                     <xsl:call-template name="replaceCharsInString">
                        <xsl:with-param name="stringIn" select="url"/>
                        <xsl:with-param name="charsIn" select="'%'"/>
                        <xsl:with-param name="charsOut" select="'%25'"/>
                     </xsl:call-template>
                  </xsl:variable>
                  
                  <xsl:variable name="showURL">
                     <xsl:call-template name="replaceCharsInString">
                        <xsl:with-param name="stringIn" select="url"/>
                        <xsl:with-param name="charsIn" select="'%2f'"/>
                        <xsl:with-param name="charsOut" select="'/'"/>
                     </xsl:call-template>
                  </xsl:variable>
                  <xsl:variable name="showURL2">
                     <xsl:call-template name="replaceCharsInString">
                        <xsl:with-param name="stringIn" select="$showURL"/>
                        <xsl:with-param name="charsIn" select="'%%'"/>
                        <xsl:with-param name="charsOut" select="'%'"/>
                     </xsl:call-template>
                  </xsl:variable>
                  
                  <a href='torrents/{$downloadURL}' title='Скачать книгу "{name}"'>
                     <span>Скачать торрент-файл "<xsl:value-of select='$showURL2' />"</span>
                  </a>
                  
               </xsl:when>
               <xsl:otherwise>
                  <!--                   <br /> -->
                  <xsl:text>Торрент-файл отсутствует</xsl:text>
               </xsl:otherwise>
            </xsl:choose>
         </p>
      </div>
   </xsl:template>
   
   <xsl:template match='PARAMS'>
      <!--Переменная адресса-->
      <xsl:variable name="hrefVar">
         <xsl:choose>
            <xsl:when test="target = 'first'">
               <xsl:value-of select="''" />
            </xsl:when>
            <xsl:when test="target = 'category'">
               <xsl:value-of select="'/books/category/'" />
               <xsl:value-of select="id" />
            </xsl:when>
         </xsl:choose>
      </xsl:variable>
      
      <!--Не показываем страницы при выборе книги-->
      <xsl:if test="target != 'book'">
         <div class='nav'>
            <div class='navigation'>
               <span>
                  <xsl:variable name="prev" select="'&lt; Предыдущая'"/>
                  <xsl:if test="curPage &gt; 1">
                     <xsl:choose>
                        <xsl:when test="target = 'first'">
                           <a href='javascript:void(0)' onclick='loadContent({curPage - 1}, "page")'><xsl:value-of select="$prev" /></a>
                        </xsl:when>
                        <xsl:when test="target = 'category'">
                           <a href='javascript:void(0)' onclick='loadContent({curPage - 1}, "page", "category", {id})'><xsl:value-of select="$prev" /></a>
                        </xsl:when>
                     </xsl:choose>
                  </xsl:if>
                  <xsl:if test="curPage &lt;= 1">
                     <xsl:value-of select="$prev" />
                  </xsl:if>
               </span>
               
               <xsl:variable name="steps">
                  <xsl:choose>
                     <xsl:when test="pages &lt;= 9">
                        <xsl:value-of select="9" />
                     </xsl:when>
                     <xsl:otherwise>
                        <xsl:value-of select="3" />
                     </xsl:otherwise>
                  </xsl:choose>
               </xsl:variable>
               
               <xsl:variable name="min">
                  <xsl:choose>
                     <xsl:when test="curPage - $steps &lt; 1">
                        <xsl:value-of select="1" />
                     </xsl:when>
                     <xsl:otherwise>
                        <xsl:value-of select="curPage - $steps" />
                     </xsl:otherwise>
                  </xsl:choose>
               </xsl:variable>
               
               <xsl:if test="curPage &gt;= $steps">
                  <span>
                     <a href='javascript:void(0)' onclick='loadContent(1, "page")'><xsl:value-of select="1" /></a>
                  </span>
                  <span>
                     <xsl:value-of select="'...'" />
                  </span>
               </xsl:if>
               
               <xsl:call-template name="showPages">
                  <xsl:with-param name="href" select="$hrefVar" />
                  <xsl:with-param name="i" select="$min" />
                  <xsl:with-param name="curr" select="curPage" />
                  <xsl:with-param name="n" select="pages" />
                  <xsl:with-param name="step" select="$steps" />
               </xsl:call-template>
               
               <xsl:if test="curPage &lt;= pages - $steps">
                  <span>
                     <xsl:value-of select="'...'" />
                  </span>
                  <span>
                     <xsl:choose>
                        <xsl:when test="target = 'first'">
                           <a href='javascript:void(0)' onclick='loadContent({pages}, "page")'><xsl:value-of select="pages" /></a>
                        </xsl:when>
                        <xsl:when test="target = 'category'">
                           <a href='javascript:void(0)' onclick='loadContent({pages}, "page", "category", {id})'><xsl:value-of select="pages" /></a>
                        </xsl:when>
                     </xsl:choose>
                  </span>
               </xsl:if>
               
               <span>
                  <xsl:variable name="forw" select="'Следующая &gt;'" />
                  <xsl:if test="curPage != pages">
                     <xsl:choose>
                        <xsl:when test="target = 'first'">
                           <a href='javascript:void(0)' onclick='loadContent({curPage + 1}, "page")'><xsl:value-of select="$forw" /></a>
                        </xsl:when>
                        <xsl:when test="target = 'category'">
                           <a href='javascript:void(0)' onclick='loadContent({curPage + 1}, "page", "category", {id})'><xsl:value-of select="$forw" /></a>
                        </xsl:when>
                     </xsl:choose>
                  </xsl:if>
                  <xsl:if test="curPage = pages">
                     <xsl:value-of select="$forw" />
                  </xsl:if>
               </span>
            </div>
         </div>
      </xsl:if>
   </xsl:template>
   
   <xsl:template name="showPages">
      <xsl:param name="href" />
      <xsl:param name="i" />
      <xsl:param name="curr" />
      <xsl:param name="n" />
      <xsl:param name="step" />
      <span>
         <xsl:choose>
            <xsl:when test="$i != curPage">
               <xsl:choose>
                  <xsl:when test="target = 'first'">
                     <a href='javascript:void(0)' onclick='loadContent({$i}, "page")'><xsl:value-of select="$i" /></a>
                  </xsl:when>
                  <xsl:when test="target = 'category'">
                     <a href='javascript:void(0)' onclick='loadContent({$i}, "page", "category", {id})'><xsl:value-of select="$i" /></a>
                  </xsl:when>
                     </xsl:choose>
            </xsl:when>
            <xsl:otherwise>
               <xsl:value-of select="$i"/>
            </xsl:otherwise>
         </xsl:choose>
      </span>
      
      <xsl:variable name="max">
         <xsl:choose>
            <xsl:when test="$curr + $step &gt;= $n">
               <xsl:value-of select="$n" />
            </xsl:when>
            <xsl:otherwise>
               <xsl:value-of select="$curr + $step" />
            </xsl:otherwise>
         </xsl:choose>
      </xsl:variable>
      
      <xsl:choose>
         <xsl:when test="$i &lt; $max">
            <xsl:call-template name="showPages">
               <xsl:with-param name="href" select="$href" />
               <xsl:with-param name="i" select="$i+1" />
               <xsl:with-param name="curr" select="$curr" />
               <xsl:with-param name="n" select="$n" />
               <xsl:with-param name="step" select="$step" />
            </xsl:call-template>
         </xsl:when>
      </xsl:choose>
   </xsl:template>
</xsl:stylesheet>
