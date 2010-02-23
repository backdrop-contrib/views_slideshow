<?php
// $Id$

/**
 * @file
 * Views Slideshow: Thumbnail Hover template file.
 */

// Add controls, image count and teasers above the main slideshow.
if ($options['thumbnailhover']['controls'] == 1) {
  print $controls;
}
if ($options['thumbnailhover']['image_count'] == 1) {
  print $image_count;
}
if (!$options['thumbnailhover']['teasers_last']) {
  print $view_teasers;
}

// The main slideshow including all the hidden elements.
print $slideshow;

// Add controls, image count and teasers below the main slideshow.
if ($view_teasers && $options['thumbnailhover']['teasers_last']) {
  print $view_teasers;
}
if ($options['thumbnailhover']['controls'] == 2) {
  print $controls;
}
if ($options['thumbnailhover']['image_count'] == 2) {
  print $image_count;
}
