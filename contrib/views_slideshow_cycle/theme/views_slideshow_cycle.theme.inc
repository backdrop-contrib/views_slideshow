<?php

/**
 * @file
 * Theme & preprocess functions for the Views Slideshow: cycle module.
 */

/**
 * Views Slideshow: Theme the main frame wrapper.
 *
 * @ingroup themeable
 */

function _views_slideshow_cycle_preprocess_views_slideshow_cycle_main_frame(&$vars) {
  $settings = $vars['settings'];
  $rows = $vars['rows'];
  $view = $vars['view'];
  $vss_id = $vars['vss_id'];

  // Cast the strings into int or bool as necessary.
  $new_settings = array();
  foreach ($settings as $key => $value) {
    if (is_string($value)) {
      $value = str_replace("\n", ' ', $value);

      $value = trim($value);

      if (is_numeric($value)) {
        $value = (int)$value;
      }
      elseif (strtolower($value) == 'true') {
        $value = TRUE;
      }
      elseif (strtolower($value) == 'false') {
        $value = FALSE;
      }
    }

    $new_settings[$key] = $value;
  }

  $settings = array_merge(
    array(
      'num_divs' => sizeof($rows),
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
  $current_settings = backdrop_add_js();
  foreach ($current_settings['settings']['data'] AS $current_setting) {
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

  // Load jQuery Cycle library
  backdrop_add_library('views_slideshow_cycle','cycle');

  // Load our cycle js
  $module_path = backdrop_get_path('module', 'views_slideshow_cycle');
  backdrop_add_js($module_path . '/js/views_slideshow_cycle.js');


  // Load our cycle css
  backdrop_add_css($module_path . '/views_slideshow_cycle.css', 'file');

  backdrop_add_js(array('viewsSlideshowCycle' => array('#views_slideshow_cycle_main_' . $vss_id => $settings)), 'setting');


  // Add the slideshow elements.
  $vars['classes'][] = 'views_slideshow_cycle_teaser_section';

  $styles = '';
  if (isset($view->display_handler->display->display_options['style_options']['views_slideshow_cycle'])) {
    $styles = $view->display_handler->display->display_options['style_options']['views_slideshow_cycle'];
  }

  $styles_default = '';
  if (isset($view->display['default']->display_options['style_options']['views_slideshow_cycle'])) {
    $styles_default = $view->display['default']->display_options['style_options']['views_slideshow_cycle'];
  }

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

  $vars['items_per_slide'] = $items_per_slide;

  //backdrop_set_message(var_export($vars['options']['widgets'],TRUE));
  $widgets = $vars['options']['widgets'];
  if (isset($options['top']['views_slideshow_pager']['enabled']) && $options['top']['views_slideshow_pager']['enabled']) {
    $aria = "aria-labelledby='views_slideshow_pager_field_item_top_${vss_id}_";
  }
  else {
    $aria = "aria-labelledby='views_slideshow_pager_field_item_bottom_${vss_id}_";
  }

  $items = array();
  $slideshow_count = 0;
  $rendered_rows = '';
  foreach ($rows as $count => $item) {
    $items[] = $item;
    if (count($items) == $items_per_slide || $count == (count($rows)-1)) {
      $rendered_rows .= theme(views_theme_functions('views_slideshow_cycle_main_frame_row', $vars['view'], $vars['view']->display[$vars['view']->current_display]), array('vss_id' => $vss_id, 'items' => $items, 'count' => $slideshow_count, 'view' => $vars['view'], 'aria' => $aria . $slideshow_count . "'",));
      $items = array();
      $slideshow_count++;
    }
  }

  $vars['rendered_rows'] = $rendered_rows;
}

/**
 * Views Slideshow slideshow rows.
 *
 * @ingroup themeable
 */
function _views_slideshow_cycle_preprocess_views_slideshow_cycle_main_frame_row(&$vars) {
  $current = $vars['count'] + 1;
  $vars['classes'][] = 'views_slideshow_cycle_slide';
  $vars['classes'][] = 'views_slideshow_slide views-row-' . $current;

  if ($vars['count']) {
    $vars['classes'][] =  'views_slideshow_cycle_hidden';
  }
  $vars['classes'][] = ($vars['count'] % 2) ? 'views-row-even' : 'views-row-odd';

  $vars['rendered_items'] = '';
  foreach ($vars['items'] as $item_count => $item) {
    $vars['rendered_items'] .= theme(views_theme_functions('views_slideshow_cycle_main_frame_row_item', $vars['view'], $vars['view']->display[$vars['view']->current_display]), array('item' => $item, 'item_count' => $item_count, 'count' => $vars['count'], 'view' => $vars['view'], 'length' => count($vars['view']->result)));
  }
}

function _views_slideshow_cycle_preprocess_views_slideshow_cycle_main_frame_row_item(&$vars) {
  $vars['classes'][] = 'views-row views-row-' . $vars['count'];
  $vars['classes'][] = ($vars['count'] % 2) ? 'views-row-even' : 'views-row-odd';
  if ($vars['count'] == 0) {
    $vars['classes'][] = 'views-row-first';
  }
  elseif ($vars['count'] == $vars['length'] - 1) {
    $vars['classes'][] = 'views-row-last';
  }

  /**
   * Support custom row classes.
   */
  if ($row_class = $vars['view']->style_plugin->get_row_class($vars['count'])) {
    $vars['classes'][] = $row_class;
  }
}

/**
 * Implements hook_preprocess_views_slideshow_pager_fields()
 */
function views_slideshow_cycle_preprocess_views_slideshow_pager_fields(&$vars) {
  $slide_count = count($vars['view']->result);
  $items_per_slide = $vars['view']->style_options['views_slideshow_cycle']['items_per_slide'];

  if ($vars['view']->style_options['slideshow_type'] == 'views_slideshow_cycle') {
    $slide_count = $slide_count / $items_per_slide;
    $slide_count = ceil($slide_count);
  }

  $vars['rendered_field_items'] = '';
  if (empty($vars['settings']['hide_on_single_slide']) || $slide_count > 1) {
    foreach ($vars['view']->result as $count => $node) {
      if ($count < $slide_count) {
        $rendered_fields = '';
        foreach ($vars['settings']['views_slideshow_pager_fields_fields'] as $field => $use) {
          if ($use !== 0 && is_object($vars['view']->field[$field])) {
            $rendered_fields .= theme(views_theme_functions('views_slideshow_pager_field_field', $vars['view'], $vars['view']->display[$vars['view']->current_display]), array('view' => $vars['view'], 'field' => $field, 'count' => $count));
          }
        }
        $vars['rendered_field_items'] .= theme(views_theme_functions('views_slideshow_pager_field_item', $vars['view'], $vars['view']->display[$vars['view']->current_display]), array('vss_id' => $vars['vss_id'], 'item' => $rendered_fields, 'count' => $count, 'location' => $vars['location']));
      }
    }
  }
}

/**
 * Implement hook_preprocess_views_slideshow_slide_counter()
 */
function views_slideshow_cycle_preprocess_views_slideshow_slide_counter(&$vars) {
  if ($vars['view']->style_options['slideshow_type'] == 'views_slideshow_cycle') {
    $vars['slide_count'] = $vars['slide_count'] / $vars['view']->style_options['views_slideshow_cycle']['items_per_slide'];
    $vars['slide_count'] = ceil($vars['slide_count']);
  }
}