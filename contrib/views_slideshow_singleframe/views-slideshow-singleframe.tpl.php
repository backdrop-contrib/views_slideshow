<?php
// $Id$

/**
 *  @file
 *  Views Slideshow: Single Frame
 */

  // these are hidden elements, used to cycle through the main div
  $hidden_elements = theme('views_slideshow_no_display_section', $view, $rows, $id, $options['mode'], $teaser);
  print theme('views_slideshow_main_section', $id, $hidden_elements);

?>
