<?php
// $Id$

/**
 * @file
 * Theme & preprocess functions for the Views Slideshow: ThumbnailHover module.
 */

/**
 * Implements template_preprocess_hook_THEMENAME().
 */
function template_preprocess_views_slideshow_thumbnailhover(&$vars) {
  $module_path = drupal_get_path('module', 'views_slideshow_thumbnailhover');
  drupal_add_js($module_path . '/views_slideshow.js', 'module');
  drupal_add_css($module_path . '/views_slideshow.css', 'module');

  $options = $vars['options'];
  $id = $vars['id'];
  $view = $vars['view'];
  $rows = $vars['rows'];

  $settings = array_merge(
    array(
      'num_divs' => sizeof($vars['rows']),
      'teasers_last' => ($options['thumbnailhover']['teasers_last']) ? 'true' : 'false',
      'id_prefix' => '#views_slideshow_thumbnailhover_main_',
      'div_prefix' => '#views_slideshow_thumbnailhover_div_',
      'id' => $vars['id'],
    ),
    $options['thumbnailhover']
  );

  drupal_add_js(array('viewsSlideshowThumbnailHover' => array(
    "#views_slideshow_thumbnailhover_main_$id" => $settings)), 'setting');

  // Add the hoverIntent plugin.
  if ($settings['pager_event'] == 'hoverIntent') {
    if (module_exists('jq')) {
      $loaded_plugins = jq_plugins();
      if (!empty($loaded_plugins['hoverIntent'])) {
        jq_add('hoverIntent');
      }
    }
    if (module_exists('hoverintent')) {
      hoverintent_add();
    }
  }

  $teaser = ($options['thumbnailhover']['hover_breakout'] == 'teaser') ? TRUE : FALSE;
  $hidden_elements = theme('views_slideshow_thumbnailhover_no_display_section', $view, $rows, $id, $options, $teaser);

  $vars['controls'] = theme('views_slideshow_thumbnailhover_controls', $id, $view, $options);
  $vars['image_count'] = theme('views_slideshow_thumbnailhover_image_count', $id, $view, $options);
  $vars['view_teasers'] = theme('views_slideshow_thumbnailhover_breakout_teasers', $view, $rows, $id, $options);
  $vars['slideshow'] = theme('views_slideshow_main_section', $id, $hidden_elements, 'thumbnailhover');
}

/**
 * Add the jQuery Cycle plugin the HTML for the hidden slideshow elements.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_thumbnailhover_no_display_section($view, $rows, $id, $options, $teaser = TRUE) {
  // If the jQ module is installed, use that to add the jQuery Cycle plugin.
  // This allows different versions of the plugin to be used.
  $js = FALSE;
  if (module_exists('jq')) {
    $loaded_plugins = jq_plugins();
    if (!empty($loaded_plugins['cycle'])) {
      $js = jq_add('cycle');
    }
  }

  // Otherwise, we'll add the version included with this module.
  if (!$js) {
    drupal_add_js(drupal_get_path('module', 'views_slideshow') . '/js/jquery.cycle.all.min.js');
  }

  // Add the slideshow elements.
  $attributes['id'] = "views_slideshow_thumbnailhover_teaser_section_$id";
  $attributes['class'] = 'views_slideshow_thumbnailhover_teaser_section views_slideshow_teaser_section';
  $attributes = drupal_attributes($attributes);

  $output = "<div$attributes>";
  foreach ($view->result as $count => $node) {
    if ($view->display_handler->uses_fields()) {
      $rendered = '';
      foreach ($options['thumbnailhover']['main_fields'] as $field => $use) {
        $rendered_field = $view->field[$field]->theme($node);
        if (($use !== 0) && !empty($rendered_field)) {
          $rendered .= '<div class="views-field-'. views_css_safe($view->field[$field]->field) .'">';
          $rendered .=  $rendered_field;
          $rendered .= '</div>';
        }
      }
    }
    else {
      $rendered = node_view(node_load($node->nid), $teaser, FALSE, FALSE);
    }
    $output .= theme('views_slideshow_thumbnailhover_no_display_teaser', $rendered, $id, $count);
  }
  $output .= "</div>";
  return $output;
}

/**
 * Views Slideshow: active element.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_thumbnailhover_no_display_teaser($item, $id, $count) {
  $current = $count + 1;

  $classes = array(
    'views_slideshow_thumbnailhover_slide',
    "views_slideshow_slide views-row-$current",
  );

  if ($count) {
    $classes[] = 'views_slideshow_thumbnailhover_hidden';
  }
  $classes[] = ($count % 2) ? 'views-row-even' : 'views-row-odd';

  $attributes['id'] = "views_slideshow_thumbnailhover_div_${id}_${count}";
  $attributes['class'] = implode(' ', $classes);
  $attributes = drupal_attributes($attributes);

  return "<div$attributes>$item</div>";
}

/**
 * Views Slideshow: pager in the form of node teasers.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_thumbnailhover_breakout_teasers($view, $items, $id, $options) {
  $attributes['id'] = "views_slideshow_thumbnailhover_breakout_teasers_$id";
  $attributes['class'] = 'views_slideshow_thumbnailhover_breakout_teasers clear-block';
  $attributes = drupal_attributes($attributes);

  $output = "<div$attributes>";
  if ($view->display_handler->uses_fields()) {
    foreach ($view->result as $count => $node) {
      $rendered_fields = '';
      foreach ($options['thumbnailhover']['breakout_fields'] as $field => $use) {
        $rendered_field = $view->field[$field]->theme($node);
        if (($use !== 0) && !empty($rendered_field)) {
          $rendered_fields .= '<div class="views-field-'. views_css_safe($view->field[$field]->field) .'">';
          $rendered_fields .=  $rendered_field;
          $rendered_fields .= '</div>';
        }
      }
      $output .= theme('views_slideshow_thumbnailhover_breakout_teaser', $rendered_fields, $id, $count);
    }
  }
  else {
    foreach ($items as $count => $item) {
      $output .= theme('views_slideshow_thumbnailhover_breakout_teaser', $item, $id, $count);
    }
  }
  $output .= "</div>\n";

  return $output;
}

/**
 * Views Slideshow: breakout teaser.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_thumbnailhover_breakout_teaser($item, $id, $count) {
  $current = $count + 1;
  $classes = array(
    'views_slideshow_thumbnailhover_div_breakout_teaser',
  );
  if (!$count) {
    $classes[] = 'views_slideshow_thumbnailhover_active_teaser';
  }
  $classes[] = ($count % 2) ? 'views-row-even' : 'views-row-odd';

  $attributes['class'] = implode(' ', $classes);
  $attributes['id'] = "views_slideshow_thumbnailhover_div_breakout_teaser_${id}_${count}";
  $attributes = drupal_attributes($attributes);

  return "<div$attributes>$item</div>\n";
}

/**
 * Views Slideshow: slideshow controls.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_thumbnailhover_controls($id, $view, $options) {
  $classes = array(
    'views_slideshow_thumbnailhover_controls',
    'views_slideshow_controls',
  );

  $attributes['class'] = implode(' ', $classes);

  $attributes['id'] = "views_slideshow_thumbnailhover_controls_$id";
  $attributes = drupal_attributes($attributes);

  $output = "<div$attributes>";
  $output .= theme('views_slideshow_thumbnailhover_control_previous', $id, $view, $options);
  $output .= theme('views_slideshow_thumbnailhover_control_pause', $id, $view, $options);
  $output .= theme('views_slideshow_thumbnailhover_control_next', $id, $view, $options);
  $output .= "</div>\n";
  return $output;
}

/**
 * Views Slideshow: "previous" control.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_thumbnailhover_control_previous($id, $view, $options) {
  return l(t('Previous'), '#', array('attributes' => array(
    'class' => 'views_slideshow_thumbnailhover_previous views_slideshow_previous',
    'id' => "views_slideshow_thumbnailhover_prev_$id",
  )));
}

/**
 * Views Slideshow: "pause" control.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_thumbnailhover_control_pause($id, $view, $options) {
  return l(t('Pause'), '#', array('attributes' => array(
    'class' => 'views_slideshow_thumbnailhover_pause views_slideshow_pause',
    'id' => "views_slideshow_thumbnailhover_playpause_$id",
  )));
}

/**
 * Views Slideshow: "next" control.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_thumbnailhover_control_next($id, $view, $options) {
  return l(t('Next'), '#', array('attributes' => array(
    'class' => 'views_slideshow_thumbnailhover_next views_slideshow_next',
    'id' => "views_slideshow_thumbnailhover_next_$id",
  )));
}

/**
 * Views Slideshow: image counter.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_thumbnailhover_image_count($id, $view, $options) {
  $attributes['class'] = 'views_slideshow_thumbnailhover_image_count views_slideshow_image_count';
  $attributes['id'] = "views_slideshow_thumbnailhover_image_count_$id";
  $attributes = drupal_attributes($attributes);

  $counter = '<span class="num"></span> ' . t('of') .' <span class="total"></span>';

  return "<div$attributes>$counter</div>";
}
