<?php
// $Id$

/**
 * @file
 * Theme & preprocess functions for the Views Slideshow: cycle module.
 */

/**
 * Implements template_preprocess_hook_THEMENAME().
 */
function template_preprocess_views_slideshow_cycle(&$vars) {
  $options = $vars['options'];
  $rows = $vars['rows'];
  $view = $vars['view'];
  $vss_id = $view->name . '-' . $view->current_display;

  $settings = array_merge(
    array(
      'num_divs' => sizeof($vars['rows']),
      'id_prefix' => '#views_slideshow_cycle_main_',
      'div_prefix' => '#views_slideshow_cycle_div_',
      'vss_id' => $vss_id,
    ),
    $options['views_slideshow_cycle']
  );

  // We need to go through the current js setting values to make sure the one we
  // want to add is not already there. If it is already there then append -[num]
  // to the id to make it unique.
  $slideshow_count = 1;
  $current_settings = drupal_add_js();
  foreach ($current_settings['setting'] AS $current_setting) {
    if (isset($current_setting['viewsSlideshowCycle'])) {
      $current_keys = array_keys($current_setting['viewsSlideshowCycle']);
      if (stristr($current_keys[0], '#views_slideshow_cycle_main_' . $vss_id)) {
        $slideshow_count++;
      }
    }
  }

  if ($slideshow_count > 1) {
    $vss_id .= '-' . $slideshow_count;
    $settings['vss_id'] = $vss_id;  
  }

  drupal_add_js(array('viewsSlideshowCycle' => array('#views_slideshow_cycle_main_' . $vss_id => $settings)), 'setting');

  $hidden_elements = theme('views_slideshow_cycle_no_display_section', $view, $rows, $vss_id, $options['mode']);
  $vars['slideshow'] = theme('views_slideshow_main_section', $vss_id, $hidden_elements, 'views_slideshow_cycle');

  $cycle = $vars['options']['views_slideshow_cycle'];

  // Only show controls when there is more than one result.
  if ($settings['num_divs'] > 1) {
    if ($cycle['controls'] == 1) {
      $vars['controls_top'] = theme('views_slideshow_cycle_controls', $vss_id, $view, $options);
    }
    elseif ($cycle['controls'] == 2) {
      $vars['controls_bottom'] = theme('views_slideshow_cycle_controls', $vss_id, $view, $options);
    }
  }

  if ($cycle['pager'] == 1) {
    $vars['pager_top'] = theme('views_slideshow_cycle_pager', $vss_id, $view, $options);
  }
  elseif ($cycle['pager'] == 2) {
    $vars['pager_bottom'] = theme('views_slideshow_cycle_pager', $vss_id, $view, $options);
  }
  
  if ($cycle['image_count'] == 1) {
    $vars['image_count_top'] = theme('views_slideshow_cycle_image_count', $vss_id, $view, $options);
  }
  elseif ($cycle['image_count'] == 2) {
    $vars['image_count_bottom'] = theme('views_slideshow_cycle_image_count', $vss_id, $view, $options);
  }
}

/**
 * Add the HTML for the hidden slideshow elements.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_cycle_no_display_section($view, $rows, $vss_id, $mode) {
  // Retrive the number of itmes per frame
  if (isset($view->display_handler->display->display_options['style_options']['views_slideshow_cycle']['items_per_slide']) && $view->display_handler->display->display_options['style_options']['views_slideshow_cycle']['items_per_slide'] > 0) {
    $items_per_slide = $view->display_handler->display->display_options['style_options']['views_slideshow_cycle']['items_per_slide'];
  }
  elseif (isset($view->display['default']->display_options['style_options']['views_slideshow_cycle']['items_per_slide']) && $view->display['default']->display_options['style_options']['views_slideshow_cycle']['items_per_slide'] > 0) {
    $items_per_slide = $view->display['default']->display_options['style_options']['views_slideshow_cycle']['items_per_slide'];
  }
  else {
    $items_per_slide = 1;
  }
  
  // Add the slideshow elements.
  $attributes['id'] = "views_slideshow_cycle_teaser_section_" . $vss_id;
  $attributes['class'] = 'views_slideshow_cycle_teaser_section';
  $attributes = drupal_attributes($attributes);

  $output = "<div$attributes>";
  
  $items = array();
  $slideshow_count = 0;
  foreach ($rows as $count => $item) {
    $items[] = $item;
    if (count($items) == $items_per_slide || $count == (count($rows)-1)) {
      $output .= theme('views_slideshow_cycle_no_display_teaser', $items, $vss_id, $slideshow_count);
      $items = array();
      $slideshow_count++;
    }
  }
  $output .= "</div>\n";

  return $output;
}

/**
 * Views Slideshow slideshow elements.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_cycle_no_display_teaser($items, $vss_id, $count) {
  $current = $count + 1;
  $classes = array(
    'views_slideshow_cycle_slide',
    "views_slideshow_slide views-row-$current",
  );
  if ($count) {
    $classes[] = 'views_slideshow_cycle_hidden';
  }
  $classes[] = ($count % 2) ? 'views-row-even' : 'views-row-odd';

  $attributes['class'] = implode(' ', $classes);
  $attributes['id'] = "views_slideshow_cycle_div_" . $vss_id . "_" . $count;
  $attributes = drupal_attributes($attributes);

  $output = "<div$attributes>";
  foreach ($items as $item_count => $item) {
    $item_class = 'views-row views-row-' . $item_count;
    if (!$item_count) {
      $item_class .= ' views-row-first';
    }
    if ($item_count % 2) {
      $item_class .= ' views-row-even';
    }
    else {
      $item_class .= ' views-row-odd';
    }
    $output .= '<div class="' . $item_class . '">' . "\n";
    $output .= $item . "\n";
    $output .= '</div>' . "\n";
  }

  $output .= "</div>\n";
  return $output;
}

/**
 * The slideshow controls.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_cycle_controls($vss_id, $view, $options) {
  $classes = array(
    'views_slideshow_cycle_controls',
    'views_slideshow_controls',
  );

  $attributes['class'] = implode(' ', $classes);
  $attributes['id'] = "views_slideshow_cycle_controls_" . $vss_id;
  $attributes = drupal_attributes($attributes);

  $output = "<div$attributes>";
  $output .= theme('views_slideshow_cycle_control_previous', $vss_id, $view, $options);
  if ($options['views_slideshow_cycle']['timeout']) {
    $output .= theme('views_slideshow_cycle_control_pause', $vss_id, $view, $options);
  }
  $output .= theme('views_slideshow_cycle_control_next', $vss_id, $view, $options);
  $output .= "</div>\n";
  return $output;
}

/**
 * Views Slideshow: "previous" control.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_cycle_control_previous($vss_id, $view, $options) {
  return l(t('Previous'), '#', array(
    'attributes' => array(
      'class' => 'views_slideshow_cycle_previous views_slideshow_previous',
      'id' => "views_slideshow_cycle_prev_" . $vss_id,
    ),
    'fragment' => ' ',
    'external' => TRUE,
  ));
}

/**
 * Views Slideshow: "pause" control.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_cycle_control_pause($vss_id, $view, $options) {
  return l(t('Pause'), '', array(
    'attributes' => array(
      'class' => 'views_slideshow_cycle_pause views_slideshow_pause',
      'id' => "views_slideshow_cycle_playpause_" . $vss_id,
    ),
    'fragment' => ' ',
    'external' => TRUE,
  ));
}

/**
 * Views Slideshow: "next" control.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_cycle_control_next($vss_id, $view, $options) {
  return l(t('Next'), '#', array(
    'attributes' => array(
      'class' => 'views_slideshow_cycle_next views_slideshow_next',
      'id' => "views_slideshow_cycle_next_" . $vss_id,
    ),
    'fragment' => ' ',
    'external' => TRUE,
  ));
}

/**
 * Views Slideshow: pager.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_cycle_pager($vss_id, $view, $options) {
  $pager_type = $options['views_slideshow_cycle']['pager_type'];

  $attributes['class'] = "views_slideshow_cycle_pager views_slideshow_pager$pager_type";
  $attributes['id'] = "views_slideshow_cycle_pager_" . $vss_id;
  $attributes = drupal_attributes($attributes);

  return "<div$attributes></div>";
}

/**
 * Views Slideshow: image counter.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_cycle_image_count($vss_id, $view, $options) {
  $attributes['class'] = 'views_slideshow_cycle_image_count views_slideshow_image_count';
  $attributes['id'] = "views_slideshow_cycle_image_count_" . $vss_id;
  $attributes = drupal_attributes($attributes);

  $counter = '<span class="num">1</span> ' . t('of') . ' <span class="total">1</span>';

  return "<div$attributes>$counter</div>";
}
