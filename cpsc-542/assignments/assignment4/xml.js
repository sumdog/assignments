//Taken from http://www.captain.at/howto-ajax-process-xml.php
   var http_request = false;
   function makeRequest(url, parameters) {
      http_request = false;
      if (window.XMLHttpRequest) { // Mozilla, Safari,...
         http_request = new XMLHttpRequest();
         if (http_request.overrideMimeType) {
            http_request.overrideMimeType('text/xml');
         }
      } else if (window.ActiveXObject) { // IE
         try {
            http_request = new ActiveXObject("Msxml2.XMLHTTP");
         } catch (e) {
            try {
               http_request = new ActiveXObject("Microsoft.XMLHTTP");
            } catch (e) {}
         }
      }
      if (!http_request) {
         alert('Cannot create XMLHTTP instance');
         return false;
      }
      http_request.onreadystatechange = alertContents;
      http_request.open('GET', url + parameters, true);
      http_request.send(null);
   }

   function sendPost(url, data) {
      http_request = false;
      if (window.XMLHttpRequest) { // Mozilla, Safari,...
         http_request = new XMLHttpRequest();
         if (http_request.overrideMimeType) {
            http_request.overrideMimeType('text/xml');
         }
      } else if (window.ActiveXObject) { // IE
         try {
            http_request = new ActiveXObject("Msxml2.XMLHTTP");
         } catch (e) {
            try {
               http_request = new ActiveXObject("Microsoft.XMLHTTP");
            } catch (e) {}
         }
      }
      if (!http_request) {
         alert('Cannot create XMLHTTP instance');
         return false;
      }
      http_request.onreadystatechange = alertContents;
      http_request.open('POST', url, true);
      http_request.send(data);
   }

   function alertContents() {
      if (http_request.readyState == 4) {
         if (http_request.status == 200) {

            var xmldoc = http_request.responseXML;
            var root = xmldoc.getElementsByTagName('application').item(0);

            //var pre = document.createElement('pre'); 
            //pre.appendChild(document.createTextNode(http_request.responseText)); 
            //document.body.appendChild(pre);
            sendPost('http://zog.utc.edu/~ssmullen/cgi-bin/echoxml.pl',http_request.responseText)

            //document.write(http_request.responseText); 
            /*for (var iNode = 0; iNode < root.childNodes.length; iNode++) {
               var node = root.childNodes.item(iNode);
               for (i = 0; i < node.childNodes.length; i++) {
                  var sibl = node.childNodes.item(i);
                  var len = parseInt(sibl.childNodes.length / 2);
                  var arr = new Array(len);
                  var cnt = 0;
                  for (x = 0; x < sibl.childNodes.length; x++) {
                     var sibl2 = sibl.childNodes.item(x);
                     var sibl3;
                     if (sibl2.childNodes.length > 0) {
                        sibl3 = sibl2.childNodes.item(0);
                        arr[cnt] = sibl3.data;   
                        cnt++;
                     }
                  }
                  addrow("mytable", arr);
               }
            }*/
         } else {
            alert('There was a problem with the request.');
         }
      }
   }
   function do_xml() {
      makeRequest('app.xml', '?test=2');
   }
   function addrow(tablename, arr) {
   var tbl = document.getElementById(tablename);
   var lastRow = tbl.rows.length;
   var row = tbl.insertRow(lastRow);
      for (r = 0; r < arr.length; r++) {   
         var cell = row.insertCell(r);
         cell.innerHTML = arr[r];
      }
   }

//<input type="button" name="button" value="GET XML" 
//   onclick="javascript:do_xml();">

//Table filled with data requested from the server:<br>
//<table border="1" id="mytable">
//</table>



