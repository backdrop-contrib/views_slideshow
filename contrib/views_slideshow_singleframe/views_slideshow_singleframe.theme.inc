<?php
// $Id$

/**
 * @file
 * Theme & preprocess functions for the Views Slideshow: SingleFrame module.
 */

/**
 * Implements template_preprocess_hook_THEMENAME().
 */
function template_preprocess_views_slideshow_singleframe(&$vars) {
  $options = $vars['options'];
  $id = $vars['id'];
  $rows = $vars['rows'];
  $view = $vars['view'];

  $settings = array_merge(
    array(
      'num_divs' => sizeof($vars['rows']),
      'id_prefix' => '#views_slideshow_singleframe_main_',
      'div_prefix' => '#views_slideshow_singleframe_div_',
      'id' => $vars['id'],
      'view_id' => $view->name . '-' . $view->current_display,
    ),
    $options['views_slideshow_singleframe']
  );

  drupal_add_js(array('viewsSlideshowSingleFrame' => array('#views_slideshow_singleframe_main_'. $vars['id'] => $settings)), 'setting');

  $hidden_elements = theme('views_slideshow_singleframe_no_display_section', $view, $rows, $id, $options['mode']);
  $vars['slideshow'] = theme('views_slideshow_main_section', $id, $hidden_elements, 'views_slideshow_singleframe');

  $singleframe = $vars['options']['views_slideshow_singleframe'];

  // Only show controls when there is more than one result.
  if ($settings['num_divs'] > 1) {
    if ($singleframe['controls'] == 1) {
      $vars['controls_top'] = theme('views_slideshow_singleframe_controls', $id, $view, $options);
    }
    elseif ($singleframe['controls'] == 2) {
      $vars['controls_bottom'] = theme('views_slideshow_singleframe_controls', $id, $view, $options);
    }
  }

  if ($singleframe['pager'] == 1) {
    $vars['pager_top'] = theme('views_slideshow_singleframe_pager', $id, $view, $options);
  }
  elseif ($singleframe['pager'] == 2) {
    $vars['pager_bottom'] = theme('views_slideshow_singleframe_pager', $id, $view, $options);
  }
  
  if ($singleframe['image_count'] == 1) {
    $vars['image_count_top'] = theme('views_slideshow_singleframe_image_count', $id, $view, $options);
  }
  elseif ($singleframe['image_count'] == 2) {
    $vars['image_count_bottom'] = theme('views_slideshow_singleframe_image_count', $id, $view, $options);
  }
}

/**
 * Add the HTML for the hidden slideshow elements.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_singleframe_no_display_section($view, $rows, $id, $mode) {
  // Add the slideshow elements.
  $attributes['id'] = "views_slideshow_singleframe_teaser_section_$id";
  $attributes['class'] = 'views_slideshow_singleframe_teaser_section';
  $attributes = drupal_attributes($attributes);

  $output = "<div$attributes>";
  foreach ($rows as $count => $item) {
    $output .= theme('views_slideshow_singleframe_no_display_teaser', $item, $id, $count);
  }
  $output .= "</div>\n";

  return $output;
}

/**
 * Views Slideshow slideshow elements.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_singleframe_no_display_teaser($item, $id, $count) {
  $current = $count + 1;
  $classes = array(
    'views_slideshow_singleframe_slide',
    "views_slideshow_slide views-row-$current",
  );
  if ($count) {
    $classes[] = 'views_slideshow_singleframe_hidden';
  }
  $classes[] = ($count % 2) ? 'views-row-even' : 'views-row-odd';

  $attributes['class'] = implode(' ', $classes);
  $attributes['id'] = "views_slideshow_singleframe_div_${id}_${count}";
  $attributes = drupal_attributes($attributes);

  return "<div$attributes>$item</div>\n";
}

/**
 * The slideshow controls.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_singleframe_controls($id, $view, $options) {
  $classes = array(
    'views_slideshow_singleframe_controls',
    'views_slideshow_controls',
  );

  $attributes['class'] = implode(' ', $classes);
  $attributes['id'] = "views_slideshow_singleframe_controls_$id";
  $attributes = drupal_attributes($attributes);

  $output = "<div$attributes>";
  $output .= theme('views_slideshow_singleframe_control_previous', $id, $view, $options);
  if ($options['views_slideshow_singleframe']['timeout']) {
    $output .= theme('views_slideshow_singleframe_control_pause', $id, $view, $options);
  }
  $output .= theme('views_slideshow_singleframe_control_next', $id, $view, $options);
  $output .= "</div>\n";
  return $output;
}

/**
 * Views Slideshow: "previous" control.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_singleframe_control_previous($id, $view, $options) {
  return l(t('Previous'), '#', array(
    'attributes' => array(
      'class' => 'views_slideshow_singleframe_previous views_slideshow_previous',
      'id' => "views_slideshow_singleframe_prev_$id",
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
function theme_views_slideshow_singleframe_control_pause($id, $view, $options) {
  return l(t('Pause'), '', array(
    'attributes' => array(
      'class' => 'views_slideshow_singleframe_pause views_slideshow_pause',
      'id' => "views_slideshow_singleframe_playpause_$id",
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
function theme_views_slideshow_singleframe_control_next($id, $view, $options) {
  return l(t('Next'), '#', array(
    'attributes' => array(
      'class' => 'views_slideshow_singleframe_next views_slideshow_next',
      'id' => "views_slideshow_singleframe_next_$id",
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
function theme_views_slideshow_singleframe_pager($id, $view, $options) {
  $pager_type = $options['views_slideshow_singleframe']['pager_type'];

  $attributes['class'] = "views_slideshow_singleframe_pager views_slideshow_pager$pager_type";
  $attributes['id'] = "views_slideshow_singleframe_pager_$id";
  $attributes = drupal_attributes($attributes);

  return "<div$attributes></div>";
}

/**
 * Views Slideshow: image counter.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_singleframe_image_count($id, $view, $options) {
  $attributes['class'] = 'views_slideshow_singleframe_image_count views_slideshow_image_count';
  $attributes['id'] = "views_slideshow_singleframe_image_count_$id";
  $attributes = drupal_attributes($attributes);

  $counter = '<span class="num">1</span> ' . t('of') . ' <span class="total">1</span>';

  return "<div$attributes>$counter</div>";
}
