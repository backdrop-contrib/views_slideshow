<?php
// $Id$

/**
 *  @file
 *  Views Slideshow: Thumbnail Hover
 */
  if ($options['thumbnailhover']['controls'] == 1) {
    print theme('views_slideshow_thumbnailhover_controls', $id, $view, $options);
  }
  
  if ($options['thumbnailhover']['image_count'] == 1) {
    print theme('views_slideshow_thumbnailhover_image_count', $id, $view, $options);
  }
  
  $teaser = ($options['thumbnailhover']['hover_breakout'] == 'teaser' ? TRUE : FALSE);
  $output = '';
  $view_teasers = FALSE;

  // As we're using the 'thumbnail hover' mode, then we need to display all the view thumbnails.
  $view_teasers = theme('views_slideshow_thumbnailhover_breakout_teasers', $view, $rows, $id, $options);
  if (!$options['thumbnailhover']['teasers_last']) {
    $output .= $view_teasers;
  }

  // These are hidden elements, used to cycle through the main div
  $hidden_elements = theme('views_slideshow_thumbnailhover_no_display_section', $view, $rows, $id, $options, $teaser);
  $output .= theme('views_slideshow_main_section', $id, $hidden_elements, 'thumbnailhover');

  if ($view_teasers && $options['thumbnailhover']['teasers_last']) {
    $output .= $view_teasers;
  }
  if ($options['thumbnailhover']['controls'] == 2) {
    print theme('views_slideshow_thumbnailhover_controls',$id, $view, $options);
  }
  
  if ($options['thumbnailhover']['image_count'] == 2) {
    print theme('views_slideshow_thumbnailhover_image_count', $id, $view, $options);
  }
  print $output;

?>
