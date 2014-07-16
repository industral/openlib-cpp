window.onload = function() {
//    logo('init');
   loadContent ( null, 'first' );
   
   


   
   // Меню
   // Вешаем событые на сворачивание/разворачивание меню
   $("#menu li p").click(function() {
      $("div._hide" + $(this).attr('class').slice(5)).slideToggle("slow");
   });
   $("div.hide li a").click(function() {
//       alert ( 1 );
//       alert ( $("div#content").html() );
//       alert ( document.getElementById('content').innerHTML )
//       alert ( $(window).scrollTop() );
      var reg=/_subMenu\d*/;
      var idMenu = ($(this).parent().attr("class").match(reg) + '').slice(8);
      loadContent ( idMenu );
//          loadContent ( idMenu );
//       $("div#content").hide("scale", {}, 1000);
//       $(this).effect("highlight", {color: '#fff'}, 1000);
//       $(this).css('color', '#838383');
   });
   $("div.hide li").mouseover(function() {
      $(this).find("a").colorBlend([{action:"resume", param:"all"}]);
      $(this).find("a").colorBlend([{fromColor:"black", toColor:"white", param:"color"}]);
   }).mouseout(function() {
      $(this).find("a").colorBlend([{action:"pause", param:"all"}]).css('color', '#000');
   });

}

// if ( window.addEventListener ) {
//    document.getElementById('logo').addEventListener ( 'mouseover', function() { logo('show'); }, false );
//    document.getElementById('logo').addEventListener ( 'mouseout', function() { logo('hide'); }, false );
// }

// function chomp ( raw_text ) {
//    return raw_text.replace(/(\n|\r)+$/, '');
// }

// function draw() {
//    var image = $(".bookImg canvas img");
//    $(".bookImg canvas").each(function ( i, n ) {
//       if ( n.getContext ) {
//          var ctx = n.getContext('2d');
// 
// //          Рамка вокруг книги
//          ctx.strokeStyle = '#CCCCCC';
//          ctx.beginPath();
//          ctx.moveTo(208,0);
//          ctx.lineTo(208,308);
//          ctx.closePath();
//          ctx.stroke();
// 
//          ctx.beginPath();
//          ctx.moveTo(208,308);
//          ctx.lineTo(0,308);
//          ctx.closePath();
//          ctx.stroke();
//          
//          // Тень
//          ctx.fillStyle = '#DEDEDE';
//          ctx.fillRect (0, 0, 207, 307);
// 
//          ctx.fillStyle = '#C8C8C8';
//          ctx.fillRect (0, 0, 205, 305);
// 
//          ctx.fillStyle = '#919191';
//          ctx.fillRect (0, 0, 202, 302);
//          
//          // Накладываем изображение
//          var img = new Image();
//          img.src = image[i].getAttribute('src');
//          ctx.drawImage ( img, 0, 0, 200, 300 );
//       }
//    });
// }

// // Отображение логотипа. Установка прозрачности, цвет глаз
// function logo ( funcAction ) {
//    var image = document.getElementById('canvasLogo');
// 
//    if (image.getContext) {
//       var ctx = image.getContext('2d');
// 
//       // Инициалищация. Выводим логотип
//       if ( funcAction == 'init' ) {
//       // Накладываем изображение
//          var img = new Image();
//          img.src = '/images/main/logo/logo.png';
//          ctx.drawImage ( img, 0, 0, 478, 187 );
//       }
// 
//       fillColor = '#000'; // цвет глаза по умолчанию
//       if ( funcAction == 'show' ) {
//          fillColor = '#D86868';
// //          image.style.opacity = 1;
//       } else {
// //          image.style.opacity = 0.8;
//       }
// 
//       if ( funcAction == 'show' || funcAction == 'hide') {
//          a = function() {
//             ctx.save();
//             ctx.scale ( 1, 0.7 );
//             ctx.beginPath();
//             ctx.fillStyle = fillColor; // устанавливаем цвет глаза
//             ctx.arc ( 258, 97, 3, 0, Math.PI * 2, true );
//             ctx.closePath ();
//             ctx.fill();
// 
// //          ctx.beginPath();
// //          ctx.fillStyle = '#000';
// //          ctx.arc ( 258, 97, 1, 0, Math.PI * 2, true );
// //          ctx.closePath ();
// //          ctx.fill();
//             ctx.restore();
//          }
//          setTimeout ('a()', 1000 );
//       }
//    }
// }

function refreshFunc() {
   $('body').css('opacity', '1');
   var i = [];
   $("div.statistic a").click(function() {
      if ( i[$(this).attr('id')] != true ) {
         $(this).after ( "<div class='loading'></div>" );
         loadContent ( $(this).attr('id'), 'scrape' );
      }
      i[$(this).attr('id')] = true;
      var param = "div.statistic#" + $(this).attr('id') + " div";
      $(param).slideToggle("slow");
   }).toggle(
   function() {
      $(this).html ( "Скрыть статистику" );
   },
   function() {
      $(this).html ( "Показать статистику" );
   });
}

