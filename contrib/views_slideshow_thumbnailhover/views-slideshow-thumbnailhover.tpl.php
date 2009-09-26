<?php
// $Id$

/**
 *  @file
 *  Views Slideshow: Thumbnail Hover
 */

  $base = drupal_get_path('module', 'views_slideshow_thumbnailhover');

  $js = theme('views_slideshow_div_js', $rows, $options, $id);
  drupal_add_js($js, 'inline');

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
  $view_teasers = theme('views_slideshow_thumbnailhover_breakout_teasers', $rows, $id);
  if (!$options['thumbnailhover']['teasers_last']) {
    $output .= $view_teasers;
  }

  // These are hidden elements, used to cycle through the main div
  $hidden_elements = theme('views_slideshow_thumbnailhover_no_display_section', $view, $rows, $id, $options['mode'], $teaser);
  $output .= theme('views_slideshow_main_section', $id, $hidden_elements, 'thumbnailhover');

  if ($view_teasers && $options['thumbnailhover']['teasers_last']) {
    $output .= $view_teasers;
  }
  if ($options['thumbnailhover']['controls'] == 2) {
    print theme('views_slideshow_thumbnailhover_controls',$id,$view,$options);
  }
  
  if ($options['thumbnailhover']['image_count'] == 2) {
    print theme('views_slideshow_thumbnailhover_image_count', $id, $view, $options);
  }
  print $output;

?>
