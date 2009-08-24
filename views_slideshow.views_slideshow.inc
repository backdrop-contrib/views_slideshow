<?php
// $Id$

/**
 *  @file
 *  The default options available with Views Slideshow.
 */


function views_slideshow_views_slideshow_option_definition() {
  $options['mode'] = array('default' => VIEWS_SLIDESHOW_DEFAULT_MODE);
  return $options;
}
