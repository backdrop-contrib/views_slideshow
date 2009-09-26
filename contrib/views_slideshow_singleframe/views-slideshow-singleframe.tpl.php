<?php
// $Id$

/**
 *  @file
 *  Views Slideshow: Single Frame
 */

  // these are hidden elements, used to cycle through the main div
  $hidden_elements = theme('views_slideshow_singleframe_no_display_section', $view, $rows, $id, $options['mode'], $teaser);
  if ($options['singleframe']['controls'] == 1) {
    print theme('views_slideshow_singleframe_controls',$id,$view,$options);
  }
  if ($options['singleframe']['pager'] == 1) {
    print theme('views_slideshow_singleframe_pager', $id, $view, $options);
  }
  if ($options['singleframe']['image_count'] == 1) {
    print theme('views_slideshow_singleframe_image_count', $id, $view, $options);
  }
  print theme('views_slideshow_main_section', $id, $hidden_elements, 'singleframe');
  if ($options['singleframe']['controls'] == 2) {
    print theme('views_slideshow_singleframe_controls',$id,$view,$options);
  }
  if ($options['singleframe']['pager'] == 2) {
    print theme('views_slideshow_singleframe_pager', $id, $view, $options);
  }
  if ($options['singleframe']['image_count'] == 2) {
    print theme('views_slideshow_singleframe_image_count', $id, $view, $options);
  }
?>
