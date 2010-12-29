<?php
// $Id$

/**
 * @file
 * The theme system, which controls the output of views slideshow.
 *
 * This just adds a wrapper div to the slideshow.
 */

function template_preprocess_views_slideshow(&$vars) {
  $options = $vars['options'];
  $main_frame_module = $options['slideshow_type'];
  $settings = $options[$main_frame_module];
  $view = $vars['view'];
  $rows = $vars['rows'];
  $num_divs = count($rows);
  $vss_id = $view->name . '-' . $view->current_display;
  
  $methods = module_invoke_all('views_slideshow_js_method_register');
  drupal_add_js(array('viewsSlideshow' => array($vss_id => array('methods' => $methods, 'paused' => 0))), 'setting');
  
  /**
   * Process Skins
   */
  $skin_info = $options['skin_info'];
  
  $vars['skin'] = $skin_info['class'];

  // Enqueue any stylesheets set for the skin on this view are added.
  $skin_path = drupal_get_path('module', $skin_info['module']);
  if ($skin_info['path']) {
    $skin_path .= '/'. $skin_info['path'];
  }
  
  // Add stylesheet.
  if (!empty($skin_info['stylesheets'])) {
    foreach ($skin_info['stylesheets'] as $stylesheet) {
      drupal_add_css($skin_path .'/'. $stylesheet);
    }
  }
  
  /**
   * Process Widgets
   */
  $widgets = module_invoke_all('views_slideshow_widget_info');

  // Build weights
  for ($i = 1; $i <= count($widgets); $i++) {
    $weight['top'][$i] = '';
    $weight['bottom'][$i] = '';
  }
  
  foreach($widgets as $widget_id => $widget_name) {
    // Put our widgets in the right location.
    if ($options['widgets']['top'][$widget_id . '_enable']) {
      $widget_weight = ($options['widgets']['top'][$widget_id]['weight'] > count($widgets)) ? count($widgets) : $options['widgets']['top'][$widget_id]['weight'];
      $weight['top'][$widget_weight][] = $widget_id;
    }
    
    if ($options['widgets']['bottom'][$widget_id . '_enable']) {
      $widget_weight = ($options['widgets']['bottom'][$widget_id]['weight'] > count($widgets)) ? count($widgets) : $options['widgets']['bottom'][$widget_id]['weight'];
      $weight['bottom'][$widget_weight][] = $widget_id;
    }
  }
  
  // Build our widgets
  foreach ($weight as $location => $order) {
    $vars[$location . '_widget_rendered'] = '';
    foreach ($order as $order_num => $widgets) {
      if (is_array($widgets)) {
        foreach ($widgets as $widget_id) {
          $vars[$widget_id . '_' . $location] = theme($widget_id . '_widget_render', $vss_id, $view, $options['widgets'][$location][$widget_id], $location, $rows);
          $vars[$location . '_widget_rendered'] .= $vars[$widget_id . '_' . $location];
        }
      }
    }
  }
  
  /**
   * Process Slideshow
   */
  $slides = theme($main_frame_module . '_main_frame', $vss_id, $view, $settings, $rows, $main_frame_module);
  $vars['slideshow'] = theme('views_slideshow_main_section', $vss_id, $slides, $main_frame_module);
}

/**
 * The current element of the slideshow.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_main_section($vss_id, $slides, $plugin) {
  $attributes['id'] = $plugin . '_main_' . $vss_id;
  $attributes['class'] = $plugin . '_main views_slideshow_main';
  $attributes = drupal_attributes($attributes);

  return "<div$attributes>$slides</div>";
}

/**
 * Views Slideshow: pager.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_pager_widget_render($vss_id, $view, $settings, $location, $rows) {
  // Create some attributes
  $attributes['class'] = 'widget_pager widget_pager_' . $location;
  $attributes['id'] = 'widget_pager_' . $location . '_' . $vss_id;
  
  return theme($settings['type'] . '_render', $vss_id, $view, $settings, $location, $rows, $attributes);
}

/**
 * Theme pager fields
 */
function template_preprocess_views_slideshow_pager_fields_render(&$vars) {
  // Build our javascript settings.
  $js_vars = array(
    'viewsSlideshowPagerFields' => array(
      $vars['vss_id'] => array(
        $vars['location'] => array(
          'activatePauseOnHover' => $vars['settings']['views_slideshow_pager_fields_hover'],
        ),
      ),
    ),
  );
  
  // Add the settings to the page.
  drupal_add_js($js_vars, 'setting');
  
  // Add our class to the wrapper.
  $vars['attributes']['class'] .= ' views_slideshow_pager_field';
  
  // Render all the fields.
  $vars['rendered_field_items'] = '';
  foreach ($vars['view']->result as $count => $node) {
    $rendered_fields = '';
    foreach ($vars['settings']['views_slideshow_pager_fields_fields'] as $field => $use) {
      if ($use !== 0 && is_object($vars['view']->field[$field])) {
        $rendered_fields .= theme('views_slideshow_pager_field_field', $vars['view'], $field, $count);
      }
    }
    $vars['rendered_field_items'] .= theme('views_slideshow_pager_field_item', $vars['vss_id'], $rendered_fields, $count);
  }
}

/**
 * Views Slideshow: pager item.
 *
 * @ingroup themeable
 */
function template_preprocess_views_slideshow_pager_field_item(&$vars) {
  $current = $vars['count'] + 1;
  $classes = array(
    'views_slideshow_pager_field_item',
  );
  if (!$vars['count']) {
    $classes[] = 'views_slideshow_active_pager_field_item';
  }
  $classes[] = ($vars['count'] % 2) ? 'views-row-even' : 'views-row-odd';

  $vars['attributes']['class'] = implode(' ', $classes);
  $vars['attributes']['id'] = 'views_slideshow_pager_field_item_' . $vars['vss_id'] . '_' . $vars['count'];
}

/**
 * Views Slideshow: Controls.
 *
 * @inggroup themeable
 */
function theme_views_slideshow_controls_widget_render($vss_id, $view, $settings, $location, $rows) {
  $output = '';
  if (count($rows) > 1) {
    $output = theme($settings['type'] . '_render', $vss_id, $view, $settings, $location, $rows);
  }
  
  return $output;
}

/**
 * The slideshow controls.
 *
 * @ingroup themeable
 */
function template_preprocess_views_slideshow_controls_text_render(&$vars) {
  $vars['attributes']['class'] = 'views_slideshow_controls_text';
  $vars['attributes']['id'] = "views_slideshow_controls_text_" . $vars['vss_id'];
  
  $vars['rendered_control_previous'] = theme('views_slideshow_controls_text_previous', $vars['vss_id'], $vars['view'], $vars['settings']);

  $vars['rendered_control_pause'] = theme('views_slideshow_controls_text_pause', $vars['vss_id'], $vars['view'], $vars['settings']);
  
  $vars['rendered_control_next'] = theme('views_slideshow_controls_text_next', $vars['vss_id'], $vars['view'], $vars['settings']);
}

/**
 * Views Slideshow: "previous" control.
 *
 * @ingroup themeable
 */
function template_preprocess_views_slideshow_controls_text_previous(&$vars) {
  $vars['attributes']['class'] = 'views_slideshow_controls_text_previous';
  $vars['attributes']['id'] = 'views_slideshow_controls_text_previous_' . $vars['vss_id'];
}

/**
 * Views Slideshow: "pause" control.
 *
 * @ingroup themeable
 */
function template_preprocess_views_slideshow_controls_text_pause(&$vars) {
  $vars['attributes']['class'] = 'views_slideshow_controls_text_pause';
  $vars['attributes']['id'] = 'views_slideshow_controls_text_pause_' . $vars['vss_id'];
  $vars['start_text'] = t('Pause');
}

/**
 * Views Slideshow: "next" control.
 *
 * @ingroup themeable
 */
function template_preprocess_views_slideshow_controls_text_next(&$vars) {
  $vars['attributes']['class'] = 'views_slideshow_controls_text_next';
  $vars['attributes']['id'] = 'views_slideshow_controls_text_next_' . $vars['vss_id'];
}

/**
 * Views Slideshow: Slide Counter.
 *
 * @inggroup themeable
 */
function theme_views_slideshow_slide_counter_widget_render($vss_id, $view, $settings, $location, $rows) {
  return theme('views_slideshow_slide_counter', $vss_id, $view, $settings, $location, $rows);
}

/**
 * Views Slideshow: slide counter.
 */
function template_preprocess_views_slideshow_slide_counter(&$vars) {
  $vars['attributes']['class'] = 'views_slideshow_slide_counter';
  $vars['attributes']['id'] = "views_slideshow_slide_counter_" . $vars['vss_id'];
}
