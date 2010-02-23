<?php
// $Id$

/**
 * The current element of the slideshow.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_main_section($id, $hidden_elements, $plugin) {
  $attributes['id'] = "views_slideshow_${plugin}_main_${id}";
  $attributes['class'] = "views_slideshow_${plugin}_main views_slideshow_main";
  $attributes = drupal_attributes($attributes);

  return "<div$attributes>$hidden_elements</div>";
}
