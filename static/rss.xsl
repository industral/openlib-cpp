<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" 
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
   <xsl:strip-space elements="*" />
   <xsl:output method="xml" encoding="utf-8" indent="yes" />
   
<!--    http://beshenov.ru/rss2.htm -->

<!--    <xsl:variable name='projectURL' select="'http://openlib.org.ua'" /> -->
<!--    <xsl:variable name='imgURL' select="'http://openlib.org.ua'" /> -->
   <xsl:variable name='projectURL' select="'http://openlib.altermann'" />
   <xsl:variable name='imgURL' select="'http://openlib.altermann'" />
   <xsl:variable name='projectName' select="'OPENLIB.ORG.UA'" />
   
   <xsl:template match='MAIN/CENTER/MENU'>
   </xsl:template>
   <xsl:template match='PARAMS'>
   </xsl:template>
   
   <xsl:template match='MAIN/CENTER/BOOKS'>
      <rss version='2.0' xmlns:atom='http://www.w3.org/2005/Atom'>
         <channel>
            <atom:link href='{$projectURL}' rel='self' type='application/rss+xml' />
            <title><xsl:value-of select="$projectName" /> - Открытая IT-интернет библиотека</title>
            <link><xsl:value-of select="$projectURL" /></link>
            <description><xsl:value-of select="$projectName" /> - Новые книги на сайте</description>
            <language>ru-ru</language>
            <copyright>Copyright &#169; 2005-2008 SIEGERSTEIN</copyright>
            <managingEditor>rss@openlib.org.ua (Alex J. Ivasyuv)</managingEditor>
            <webMaster>rss@openlib.org.ua (Alex J. Ivasyuv)</webMaster>
            <docs>http://www.rssboard.org/rss-specification</docs>
            <ttl>1440</ttl>
            <image>
               <url><xsl:value-of select="$imgURL" />/images/main/logo/logo.png</url>
               <title><xsl:value-of select="$projectName" /> - Открытая IT-интернет библиотека</title>
               <link><xsl:value-of select="$projectURL" /></link>
               <width>144</width>
               <height>117</height>
               <description>Главная</description>
            </image>
            <xsl:apply-templates/>
         </channel>
      </rss>
   </xsl:template>
   
   <xsl:template match='book'>
      <item>
         <title><xsl:value-of select="name" /></title>
         <link><xsl:value-of select="$projectURL" />/book/<xsl:value-of select="id" /></link>
         <guid><xsl:value-of select="id" /></guid>
         <description>
            <xsl:text disable-output-escaping="yes">&lt;![CDATA[</xsl:text>
            <table>
               <tr>
                  <td align='left' width='5%'>
                     <xsl:variable name="imgPath">
                        <xsl:choose>
                           <xsl:when test="img = 1">
                              <xsl:value-of select="$imgURL" />/images/thumbnail/books/100/<xsl:value-of select="id" />.jpg
                           </xsl:when>
                           <xsl:otherwise>
                              <xsl:value-of select="$imgURL" />/images/thumbnail/default.png
                           </xsl:otherwise>
                        </xsl:choose>
                     </xsl:variable>
                     <xsl:choose>
                        <xsl:when test="img = 1">
                           <a href='{$imgPath}' target='_blank'>
                              <img src='{$imgPath}' align='left' hspace='5' border='0' alt='{name}' height='150' width='100' />
                           </a>
                        </xsl:when>
                        <xsl:otherwise>
                           <img src='{$imgPath}' align='left' hspace='5' border='0' alt='{name}' height='150' width='100' />
                        </xsl:otherwise>
                     </xsl:choose>
                  </td>
                  <td>
                     <xsl:choose>
                        <xsl:when test="contains(author, ',')">
                           Авторы:
                        </xsl:when>
                        <xsl:otherwise>
                           Автор:
                        </xsl:otherwise>
                     </xsl:choose>
                  <xsl:value-of select='author' /><br />
                  <xsl:if test='pages != 0'>
                     Страниц: <xsl:value-of select='pages' /><br />
                  </xsl:if>
                  Формат: 
                  <xsl:choose>
                     <xsl:when test="mime = 'djvu'">DjVu</xsl:when>
                     <xsl:when test="mime = 'pdf'">PDF</xsl:when>
                     <xsl:when test="mime = 'chm'">HTMLHelp</xsl:when>
                     <xsl:when test="mime = 'html'">HTML</xsl:when>
                     <xsl:when test="mime = 'odt'">OpenDocument</xsl:when>
                     <xsl:when test="mime = 'txt'">txt</xsl:when>
                  </xsl:choose>
                  <br/>
                  Размер: <xsl:value-of select='size'/>
                  <xsl:choose>
                     <xsl:when test="size/@char = 'mb'">
                        Мб
                     </xsl:when>
                     <xsl:when test="size/@char = 'kb'">
                        Кб
                     </xsl:when>
                        </xsl:choose>
                  </td>
               </tr>
               <tr>
                  <td colspan='2'><xsl:value-of select="short_descr" /></td>
               </tr>
            </table>
            <xsl:text disable-output-escaping="yes">]]&gt;</xsl:text>
         </description>
<!--          <pubDate></pubDate> -->
<!-- <xsl:variable name='date' select='date' /> -->
<!--          <xsl:variable name="gmt" select="adjust-dateTime-to-timezone($date, xdt:dayTimeDuration('PT0H'))"/> -->

      </item>
   </xsl:template>
</xsl:stylesheet>
