<?php
// $Id$

/**
 * @file
 * Views Slideshow: Single Frame template file.
 */

// Add controls, pager and image count above the main slideshow.
if ($options['singleframe']['controls'] == 1) {
  print $controls;
}
if ($options['singleframe']['pager'] == 1) {
  print $pager;
}
if ($options['singleframe']['image_count'] == 1) {
  print $image_count;
}

// The main slideshow elements.
print $slideshow;

// Add controls, pager and image counter below the main slideshow.
if ($options['singleframe']['controls'] == 2) {
  print $controls;
}
if ($options['singleframe']['pager'] == 2) {
  print $pager;
}
if ($options['singleframe']['image_count'] == 2) {
  print $image_count;
}
