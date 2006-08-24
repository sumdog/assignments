<?

function load_assignments() {
  $ass = file("ass.dat");
  foreach($ass as $a) {
   $item = split(":",$a);
   $retval[] = Array('num'=>$item[0], 'link'=>$item[1], 'title'=>$item[2]);
  }
  return $retval;
}

function display_assignments($ass) {
  foreach($ass as $row) {
   $retval .= "<tr>";
   $retval .= "<td><a href=\"{$row['link']}\">{$row['num']}</a></td>";
   $retval .= "<td>{$row['title']}</td>";
   $retval .= "</tr>";
  }
  return $retval;
}

?>
