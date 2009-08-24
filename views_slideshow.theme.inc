<?php
// $Id$

/**
 *  This displays the main element, where the current slide is shown.
 */
function theme_views_slideshow_main_section($id, $hidden_elements) {
  $output = "\n\n" . '<div id="views_slideshow_main_' . $id . '" class="views_slideshow_main">' . "\n  ";
  $output .= $hidden_elements;
  $output .= '</div><!--close views_slideshow_main_' . $id . "-->\n\n";
  return $output;
}
