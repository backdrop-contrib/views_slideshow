<?php
// $Id$

/**
 *  @file
 *  Theme & preprocess functions for the Views Slideshow: ThumbnailHover module.
 */

/**
 *  Implement template_preprocess_hook_THEMENAME().
 */
function template_preprocess_views_slideshow_thumbnailhover(&$vars) {
  $options = $vars['options'];
  $base = drupal_get_path('module', 'views_slideshow_thumbnailhover');
  drupal_add_js($base . '/views_slideshow.js', 'module');
  drupal_add_css($base . '/views_slideshow.css', 'module');

  $num_divs = sizeof($vars['rows']);
  $teasers_last = $options['thumbnailhover']['teasers_last'] ? 'true' : 'false';

  $settings = array_merge(
    array(
      'num_divs' => $num_divs,
      'teasers_last' => $teasers_last,
      'id_prefix' => '#views_slideshow_thumbnailhover_main_',
      'div_prefix' => '#views_slideshow_thumbnailhover_div_',
      'id' => $vars['id'],
    ),
    $options['thumbnailhover']
  );

  drupal_add_js(array('viewsSlideshowThumbnailHover' => array('#views_slideshow_thumbnailhover_main_'. $vars['id'] => $settings)), 'setting');
  if ($settings['pager_event'] == 'hoverIntent') {
    if (module_exists('jq')) {
      if (in_array('hoverIntent', jq_plugins())) {
        jq_add('hoverIntent');
      }
    }
    if (module_exists('hoverintent')) {
      hoverintent_add();
    }
  }
}


/**
 *  These are the slideshow elements themselves; not actually displayed, but used to give the html to the main element.
 */
function theme_views_slideshow_thumbnailhover_no_display_section($view, $rows, $id, $mode, $teaser = TRUE) {
  // Add support for the jQuery Cycle plugin.
  // If we have the jQ module installed, use that to add the Cycle plugin if possible.
  // That allows for version control.
  if (module_exists('jq')) {
    if (in_array('cycle', jq_plugins())) {
      $js = jq_add('cycle');
    }
  }

  // Otherwise, we'll add the version included with this module.
  if (!$js) {
    drupal_add_js(drupal_get_path('module', 'views_slideshow') .'/js/jquery.cycle.all.min.js', 'module');
  }
  $output = '<div id="views_slideshow_thumbnailhover_teaser_section_' . $id . '" class="views_slideshow_thumbnailhover_teaser_section">' . "\n";
  foreach ($view->result as $count => $node) {
    $output .= theme('views_slideshow_thumbnailhover_no_display_teaser', node_view(node_load($node->nid), $teaser, FALSE, FALSE), $id, $count);
  }
  $output .= "</div><!--close views_slideshow_thumbnailhover_no_display-->\n\n";
  return $output;
}

/**
 *  The html that will be placed into the element in its turn during its frame.
 */
function theme_views_slideshow_thumbnailhover_no_display_teaser($item, $id, $count) {
  $class = 'class="views_slideshow_thumbnailhover_slide' . ($count ? ' views_slideshow_thumbnailhover_hidden"' : '"');
  $output = '  <div id="views_slideshow_thumbnailhover_div_' . $id . '_' . $count . '" '. $class .'>' . "\n  ";
  $output .= $item . "\n";
  $output .= '  </div><!--close views_slideshow_thumbnailhover_div_' . $id . '_' . $count . '-->' . "\n\n";
  return $output;
}

/**
 *  These are teasers that may be pointed at with a mouse to change the element directly.
 */
function theme_views_slideshow_thumbnailhover_breakout_teasers($items, $id) {
  $output = '<div id="views_slideshow_thumbnailhover_breakout_teasers_' . $id . '" class="views_slideshow_thumbnailhover_breakout_teasers clear-block">' . "\n";
  $js = "$(document).ready(function() {\n";
  foreach ($items as $count => $item) {
    $output .= theme('views_slideshow_thumbnailhover_breakout_teaser', $item, $id, $count);
    $js .= theme('views_slideshow_thumbnailhover_breakout_teaser_js', $id, $count);
  }
  $js .= "})\n";
  drupal_add_js($js, 'inline');

  $output .= "</div><!--close views_slideshow_thumbnailhover_breakout_teasers-->\n\n";

  return $output;
}

/**
 *  An individual breakout teaser.
 */
function theme_views_slideshow_thumbnailhover_breakout_teaser($item, $id, $count) {
  $class = 'views_slideshow_thumbnailhover_div_breakout_teaser';
  if (!$count) {
    $class .= ' views_slideshow_thumbnailhover_active_teaser';
  }

  if ($count % 2) {
    $class .= ' views-row-even';
  }
  else {
    $class .= ' views-row-odd';
  }
  $output = '  <div id="views_slideshow_thumbnailhover_div_breakout_teaser_' . $id . '_' . $count . '" class="' . $class . '">' . "\n  ";
  $output .= $item . "\n";
  $output .= '  </div><!--close views_slideshow_thumbnailhover_div_breakout_teaser_' . $id . '_' . $count . '-->' . "\n\n";
  return $output;
}


/**
 * Themed slideshow controls.
 */
function theme_views_slideshow_thumbnailhover_controls($id, $view, $options) {
  $output = '<div class="views_slideshow_thumbnailhover_controls" id="views_slideshow_thumbnailhover_controls_' . $id . '">' . "\n";
  $output .= theme('views_slideshow_thumbnailhover_control_previous', $id, $view, $options);
  $output .= theme('views_slideshow_thumbnailhover_control_pause', $id, $view, $options);
  $output .= theme('views_slideshow_thumbnailhover_control_next', $id, $view, $options);
  $output .= "</div>\n";
  return $output;
}

/**
 * Themed Previous Control
 */
function theme_views_slideshow_thumbnailhover_control_previous($id, $view, $options) {
  return '<a href="#" id="views_slideshow_thumbnailhover_prev_' . $id . '" class="views_slideshow_thumbnailhover_previous">' . t('Previous') . "</a>\n";
}

/**
 * Themed Pause Control
 */
function theme_views_slideshow_thumbnailhover_control_pause($id, $view, $options) {
  return '<a href="#" id="views_slideshow_thumbnailhover_playpause_' . $id . '" class="views_slideshow_thumbnailhover_pause">' . t('Pause') . "</a>\n";
}

/**
 * Themed Next Control
 */
function theme_views_slideshow_thumbnailhover_control_next($id, $view, $options) {
  return '<a href="#" id="views_slideshow_thumbnailhover_next_' . $id . '" class="views_slideshow_thumbnailhover_next">' . t('Next') . "</a>\n";
}
