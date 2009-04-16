<?php
// $Id$

/**
 *  @file
 *  Theme & preprocess functions for the Views Slideshow: SingleFrame module.
 */

/**
 *  Implement template_preprocess_hook_THEMENAME().
 */
function template_preprocess_views_slideshow_singleframe(&$vars) {
  $options = $vars['options'];
  $base = drupal_get_path('module', 'views_slideshow_singleframe');
  drupal_add_js($base . '/views_slideshow.js', 'module');
  drupal_add_css($base . '/views_slideshow.css', 'module');

  $hover = 'hover';
  if ($options['hover'] == 'hoverIntent') {
    if (module_exists('jq')) {
      $hover = jq_add('hoverIntent') ? 'hoverIntent' : 'hover';
    }
    else if (module_exists('hoverintent')) {
      $hover = hoverintent_add() ? 'hoverIntent' : 'hover';
    }
  }

  $num_divs = sizeof($vars['rows']);
  $fade = $options['fade'] ? 'true' : 'false';

  $settings = array(
    'num_divs' => $num_divs,
    'timer_delay' => $options['timer_delay'],
    'sort' => intval($options['sort']),
    'fade' => $fade,
    'fade_speed' => $options['fade_speed'],
    'fade_value' => $options['fade_value'],
    'hoverFunction' => $hover,
    'id_prefix' => '#views_slideshow_main_',
    'div_prefix' => '#views_slideshow_div_',
    'id' => $vars['id'],
  );

  drupal_add_js(array('viewsSlideshowSingleFrame' => array('#views_slideshow_main_'. $vars['id'] => $settings)), 'setting');

/*  $js = theme('views_slideshow_div_js', $vars['rows'], $vars['options'], $vars['id']);
  drupal_add_js($js, 'inline');*/
}
