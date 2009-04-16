<?php
// $Id$

/**
 *  @file
 *  The default options available with Views Slideshow: SingleFrame.
 */

function views_slideshow_singleframe_views_slideshow_modes() {
  $options = array(
    'singleframe' => t('SingleFrame'),
  );
  return $options;
}

function views_slideshow_singleframe_views_slideshow_option_definition() {
  $options['singleframe'] = array();
  $options['singleframe']['hover'] = array('default' => (module_exists('hoverintent') ? 'hoverIntent' : 'hover'));
  $options['singleframe']['timer_delay'] = array('default' => 5000);
  $options['singleframe']['sort'] = array('default' => 1);
  $options['singleframe']['fade'] = array('default' => TRUE);
  $options['singleframe']['fade_speed'] = array('default' => 'slow');
  $options['singleframe']['fade_value'] = array('default' => 0.25);
  return $options;
}

function views_slideshow_singleframe_views_slideshow_options_form(&$form, &$form_state, &$view) {
  dpm($view->options);

  $form['singleframe'] = array(
    '#type' => 'fieldset',
    '#title' => t('SingleFrame rotator options'),
    '#collapsible' => TRUE,
    '#collapsed' => !($view->options['mode'] == 'singleframe'),
  );
  $options = array('hover' => t('Hover'));
  if (module_exists('hoverintent')) {
    $options['hoverIntent'] = t('HoverIntent');
  }
  $form['singleframe']['hover'] = array(
    '#type' => 'radios',
    '#title' => t('Mouse hover'),
    '#options' => $options,
    '#default_value' => $view->options['singleframe']['hover'],
    '#description' => t('The !hoverintent, if installed, adds the %hoverintent option here. Selecting it causes a delay when the mouse hovers, to stop quick flybys from triggering the behavior. Selecting %hoverdefault chooses the default mouse behavior.', array('!hoverintent' => l(t('HoverIntent module'), 'http://drupal.org/project/hoverintent'), '%hoverintent' => t('HoverIntent'), '%hoverdefault' => t('Hover'))),
  );
  $form['singleframe']['timer_delay'] = array(
    '#type' => 'textfield',
    '#title' => t('Timer delay (in milliseconds)'),
    '#default_value' => $view->options['singleframe']['timer_delay'],
  );
  $options = array(
    1 => t('Forward'),
    -1 => t('Reverse'),
    0 => t('Random'),
  );
  $form['singleframe']['sort'] = array(
    '#type' => 'radios',
    '#title' => t('Slideshow sort order'),
    '#description' => t('This option determines the sort order of the returned results within the slideshow. Note that it is not related to the View\'s sorting options, and will only affect resulting items.'),
    '#options' => $options,
    '#default_value' => $view->options['singleframe']['sort'],
  );
  $form['singleframe']['fade'] = array(
    '#type' => 'checkbox',
    '#title' => t('Fade'),
    '#default_value' => $view->options['singleframe']['fade'],
    '#description' => t('If checked, then the slideshow will fade between frames. Otherwise, the Fade speed and value, below, will be ignored.'),
  );
  $options = array(
    'slow' => t('Slow'),
    'normal' => t('Normal'),
    'fast' => t('Fast'),
  );
  $form['singleframe']['fade_speed'] = array(
    '#type' => 'radios',
    '#title' => t('Fade speed'),
    '#options' => $options,
    '#default_value' => $view->options['singleframe']['fade_speed'],
  );
  $form['singleframe']['fade_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Fade value'),
    '#description' => t('The opacity to fade to, between 0 (fully transparent) and 1 (fully opaque).'),
    '#default_value' => $view->options['singleframe']['fade_value'],
  );
}
