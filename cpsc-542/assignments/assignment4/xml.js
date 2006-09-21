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


   function alterText(xmldoc,na,nb,nc,docnode) {
      var a = xmldoc.getElementsByTagName(na).item(0);
      var b = a.getElementsByTagName(nb).item(0);
      var c = b.getElementsByTagName(nc).item(0);
      var tnode = xmldoc.createTextNode(document.getElementById(docnode).value);
      c.appendChild(tnode);
   }

   function alterUTCID(xmldoc,na,docnode) {
      var a = xmldoc.getElementsByTagName(na).item(0);
      var b = a.getElementsByTagName('utcid').item(0);
      var tnode = xmldoc.createTextNode(document.getElementById(docnode).value);
      b.appendChild(tnode);
   }


   function alertContents() {
      if (http_request.readyState == 4) {
         if (http_request.status == 200) {

            var xmldoc = http_request.responseXML;
            var root = xmldoc.getElementsByTagName('application').item(0);

            alterUTCID(xmldoc,'namechange','utcid');
            alterUTCID(xmldoc,'addresschange','addrutcid');

            alterText(xmldoc,'namechange','current','first','cfirst');
            alterText(xmldoc,'namechange','current','middle','cmiddle');
            alterText(xmldoc,'namechange','current','last','clast');
            alterText(xmldoc,'namechange','current','maiden','cmaiden');
            alterText(xmldoc,'namechange','new','first','nfirst');
            alterText(xmldoc,'namechange','new','middle','nmiddle');
            alterText(xmldoc,'namechange','new','last','nlast');
            alterText(xmldoc,'namechange','new','maiden','nmaiden');

            alterText(xmldoc,'addresschange','name','first','afirst');
            alterText(xmldoc,'addresschange','name','middle','amiddle');
            alterText(xmldoc,'addresschange','name','last','alast');
            alterText(xmldoc,'addresschange','name','maiden','amaiden');

            alterText(xmldoc,'addresschange','permanentaddr','street','perstreet');
            alterText(xmldoc,'addresschange','permanentaddr','city','percity');
            alterText(xmldoc,'addresschange','permanentaddr','state','perstate');
            alterText(xmldoc,'addresschange','permanentaddr','zip','perzip');
            alterText(xmldoc,'addresschange','permanentaddr','phone','perphone');

            alterText(xmldoc,'addresschange','presentaddr','street','prestreet');
            alterText(xmldoc,'addresschange','presentaddr','city','precity');
            alterText(xmldoc,'addresschange','presentaddr','state','prestate');
            alterText(xmldoc,'addresschange','presentaddr','zip','prezip');
            alterText(xmldoc,'addresschange','presentaddr','phone','prephone');

            var xmlout = "";
            if (window.XMLHttpRequest) { // Mozilla, Safari,...
              var serializer = new XMLSerializer();
              xmlout = serializer.serializeToString(xmldoc);
            } else {
              xmlout = xmldoc.xml;
            }
            
            /*
            var pre = document.createElement('pre'); 
            pre.appendChild(document.createTextNode(http_request.responseText)); 
            pre.appendChild(document.createTextNode(xmlout));
            document.body.appendChild(pre);
            */

            if (confirm( xmlout ) ) {
              document.getElementById('val').value = xmlout;
              document.getElementById('mainform').submit();
            }

         } else {
            alert('There was a problem with the request.');
         }
      }
   }
   function do_xml() {
      makeRequest('app.xml', '');
   }
