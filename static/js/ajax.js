var httpRequest;
if ( window.XMLHttpRequest ) {
   httpRequest = new XMLHttpRequest();
}

var gid = null;

function loadContent ( id, ajaxAction, addParam, addId ) {
   var url = '';
//    var hash = '';
   if ( ajaxAction == 'first' ) {
      url = '/first';
//       hash = 'first';
   } else if ( ajaxAction == 'scrape' ) {
      url = '/scrape/' + id;
//       url = '/ht/first';
   } else if ( ajaxAction == 'page' && addParam == 'category' && addId ) {
      url = '/books/category/' + addId + '/' + id;
   } else if ( ajaxAction == 'book' && id ) {
      url = '/book/' + id;
   } else if ( ajaxAction == 'page' ) {
      url = '/' + id;
   } else {
      url = '/books/category/' + id + '/1';
//       hash = 'books/category/' +id + '/1' ;
   }
//    window.location.hash = hash;
   gid = id;
   httpRequest.open ( 'GET', url, true );
   if ( ajaxAction == 'scrape' ) {
      httpRequest.onreadystatechange = scrapeAjax;
   } else {
      httpRequest.onreadystatechange = processResponse;
      $('body').addClass('loadingContent').css('opacity', '0.2');
   }
   httpRequest.send(null);
}

function processResponse() {
   if ( httpRequest.readyState == 4 ) {
      $("body").removeClass ("loadingContent");
      document.getElementById('content').innerHTML = httpRequest.responseText;
//       setTimeout (draw, 300 ); // Нужна задержка, так как canvas не успевает прорисовать все
      refreshFunc();
   }
}

function scrapeAjax() {
   if ( httpRequest.readyState == 4 ) {
      var jsonData = JSON.parse( httpRequest.responseText );
//       var jsonData = JSON.parse( '{"complete":1,"downloaded":7,"incomplete":0}' );

      var insertData = "<strong>Сидеров: </strong>" + jsonData.complete + "<br />" + "<strong>Личеров: </strong>" + jsonData.incomplete + "<br />" + "<strong>Скачали: </strong>" + jsonData.downloaded;
      var param = "div.statistic#" + gid + " div";
      $(param).removeClass('loading').addClass('loaded');
      $(param).html( insertData );
   }
}
