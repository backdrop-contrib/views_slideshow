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
  $settings = $options['views_slideshow_cycle'];
  $skin_info = $settings['skin_info'];

  // Cast the strings into int or bool as necessary.
  $new_settings = array();
  foreach ($settings as $key => $value) {
    if (stristr($value, "\n")) {
      $value = str_replace("\n", ' ', $value);
    }
    $value = trim($value);

    if (is_numeric($value)) {
      $value = (int)$value;
    }
    else if (strtolower($value) == 'true') {
      $value = true;
    }
    else if (strtolower($value) == 'false') {
      $value = false;
    }
    
    $new_settings[$key] = $value;
  }
  
  // Remove any unused advanced settings.
  foreach ($settings as $key => $value) {
    if (substr($key, 0, 13) == 'advanced_use_' && !$value) {
      $setting_name = str_replace('advanced_use_', '', $key);
      unset($new_settings[$key]);
      unset($new_settings['advanced_' . $setting_name]);
    }
  }

  $settings = array_merge(
    array(
      'num_divs' => sizeof($vars['rows']),
      'id_prefix' => '#views_slideshow_cycle_main_',
      'div_prefix' => '#views_slideshow_cycle_div_',
      'vss_id' => $vss_id,
    ),
    $new_settings
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

  // Enqueue any stylesheets set for the skin on this view are added.
  $skin_path = drupal_get_path('module', $skin_info['module']);
  if ($skin_info['path']) {
    $skin_path .= '/'. $skin_info['path'];
  }
  
  if (!empty($skin_info['stylesheets'])) {
    foreach ($skin_info['stylesheets'] as $stylesheet) {
      drupal_add_css($skin_path .'/'. $stylesheet);
    }
  }
  
  drupal_add_js(array('viewsSlideshowCycle' => array('#views_slideshow_cycle_main_' . $vss_id => $settings)), 'setting');

  $hidden_elements = theme('views_slideshow_cycle_no_display_section', $view, $rows, $vss_id, $options['mode']);
  $vars['slideshow'] = theme('views_slideshow_main_section', $vss_id, $hidden_elements, 'views_slideshow_cycle');
  
  $weight = array(
    'top' => array(),
    'bottom' => array(),
  );
  
  // Put our pager in the right location.
  $vars['pager_location'] = (isset($skin_info['pager_location'])) ? $skin_info['pager_location'] : $settings['pager'];  
  $vars['pager'] = '';
  if ($vars['pager_location']) {
    $weight[$vars['pager_location']]['pager'] = (isset($skin_info['pager_weight'])) ? $skin_info['pager_weight'] : $settings['pager_weight'];
  }

  // Put our controls in the right location.
  // Only show controls when there is more than one result.
  $vars['controls_location'] = (isset($skin_info['controls_location'])) ? $skin_info['controls_location'] : $settings['controls'];
  $vars['controls_location'] = ($settings['num_divs'] > 1) ? $vars['controls_location'] : 0;
  $vars['controls'] = '';
  if ($vars['controls_location']) {
    $weight[$vars['controls_location']]['controls'] = (isset($skin_info['controls_weight'])) ? $skin_info['controls_weight'] : $settings['controls_weight'];
  }
  
  // Put our slide counter in the right location.
  $vars['slide_counter_location'] = (isset($skin_info['slide_counter_location'])) ? $skin_info['slide_counter_location'] : $settings['slide_counter'];  
  $vars['slide_counter'] = '';
  if ($vars['slide_counter_location']) {
    $weight[$vars['slide_counter_location']]['slide_counter'] = (isset($skin_info['slide_counter_weight'])) ? $skin_info['slide_counter_weight'] : $settings['slide_counter_weight'];
  }
  
  // Build our widgets
  foreach ($weight as $location => $data) {
    // Build our top widgets
    if (!empty($data)) {
      asort($data);
      
      $vars[$location . '_widget_rendered'] = '';
      foreach ($data as $type => $order) {
        $vars[$type] = theme('views_slideshow_cycle_' . $type, $vss_id, $view, $options);
        $vars[$location . '_widget_rendered'] .= $vars[$type];
      }
    }
  }
}

/**
 * Add the HTML for the hidden slideshow elements.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_cycle_no_display_section($view, $rows, $vss_id, $mode) {
  $styles = $view->display_handler->display->display_options['style_options']['views_slideshow_cycle'];
  $styles_default = $view->display['default']->display_options['style_options']['views_slideshow_cycle'];
  
  // Retrive the number of items per frame
  if (isset($styles['items_per_slide']) && $styles['items_per_slide'] > 0) {
    $items_per_slide = $styles['items_per_slide'];
  }
  elseif (isset($styles_default['items_per_slide']) && $styles_default['items_per_slide'] > 0) {
    $items_per_slide = $styles_default['items_per_slide'];
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
  $output = '';

  // Create some attributes
  $attributes['class'] = 'views_slideshow_cycle_pager views_slideshow_pager_' . $pager_type;
  $attributes['id'] = "views_slideshow_cycle_pager_" . $vss_id;
  
  // Allow other modules change the output
  // Using foreach instead of module_invoke_all because module_invoke_all
  // doesn't support pass by reference.
  foreach (module_implements('views_slideshow_cycle_pager_theme') as $module) {
    $hook = $module . '_views_slideshow_cycle_pager_theme';
    $hook($output, $vss_id, $view, $options['views_slideshow_cycle'], $attributes);
  }

  return $output;
}

/**
 * Implementation of hook_views_slideshow_cycle_pager_theme.
 */
function views_slideshow_cycle_views_slideshow_cycle_pager_theme(&$output, $vss_id, $view, $options, $attributes) {
  switch($options['pager_type']) {
    case 'numbered':
    case 'thumbnails':
      $output = '<div' . drupal_attributes($attributes) . '></div>';
      break;
    
    case 'fields':
      $output = '<div' . drupal_attributes($attributes) . '>';
      foreach ($view->result as $count => $node) {
        $rendered_fields = '';
        foreach ($options['pager_fields'] as $field => $use) {
          if ($use !== 0 && is_object($view->field[$field])) {
            $rendered_fields .= '<div class="views-field-'. views_css_safe($view->field[$field]->field) .'">';
            if ($view->field[$field]->label()) {
              $rendered_fields .= '<label class="view-label-'. views_css_safe($view->field[$field]->field) . '">';
              $rendered_fields .= $view->field[$field]->label() . ':';
              $rendered_fields .= '</label>';
            }
            $rendered_fields .= '<div class="views-content-'. views_css_safe($view->field[$field]->field) .'">';
            $rendered_fields .=  $view->style_plugin->rendered_fields[$count][$field];
            $rendered_fields .= '</div>';
            $rendered_fields .= '</div>';
          }
        }
    
        $output .= theme('views_slideshow_cycle_pager_item', $rendered_fields, $vss_id, $count);
      }
      $output .= '</div>';
      break;
  }
}

/**
 * Views Slideshow: pager item.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_cycle_pager_item($item, $vss_id, $count) {
  $current = $count + 1;
  $classes = array(
    'views_slideshow_cycle_div_pager_item',
  );
  if (!$count) {
    $classes[] = 'views_slideshow_cycle_active_pager_item';
  }
  $classes[] = ($count % 2) ? 'views-row-even' : 'views-row-odd';

  $attributes['class'] = implode(' ', $classes);
  $attributes['id'] = 'views_slideshow_cycle_div_pager_item_' . $vss_id . '_' . $count;
  $attributes = drupal_attributes($attributes);

  return '<div' . $attributes . '>' . $item . '</div>' . "\n";
}

/**
 * Views Slideshow: slide counter.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_cycle_slide_counter($vss_id, $view, $options) {
  $attributes['class'] = 'views_slideshow_cycle_slide_counter views_slideshow_slide_counter';
  $attributes['id'] = "views_slideshow_cycle_slide_counter_" . $vss_id;
  $attributes = drupal_attributes($attributes);

  $counter = '<span class="num">1</span> ' . t('of') . ' <span class="total">1</span>';

  return "<div$attributes>$counter</div>";
}
