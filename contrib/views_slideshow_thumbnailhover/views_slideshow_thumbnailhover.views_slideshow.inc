<?php
// $Id$

/**
 *  @file
 *  The default options available with Views Slideshow: ThumbnailHover.
 */

function views_slideshow_thumbnailhover_views_slideshow_modes() {
  $options = array(
    'thumbnailhover' => t('ThumbnailHover'),
  );
  return $options;
}

function views_slideshow_thumbnailhover_views_slideshow_option_definition() {
  $options['thumbnailhover'] = array(
    'hover' => module_exists('hoverintent') ? 'hoverIntent' : 'hover',
    'timer_delay' => 5000,
    'sort' => 1,
    'fade' => TRUE,
    'fade_speed' => 'slow',
    'fade_value' => 0.25,
    'hover_breakout' => 'teaser',
    'teasers_last' => TRUE,
  );

  return $options;
}

function views_slideshow_thumbnailhover_views_slideshow_options_form(&$form, &$form_state, &$view) {
  dpm($view->options);

  $form['thumbnailhover'] = array(
    '#type' => 'fieldset',
    '#title' => t('ThumbnailHover rotator options'),
    '#collapsible' => TRUE,
    '#collapsed' => !($view->options['mode'] == 'thumbnailhover'),
  );
  $options = array('hover' => t('Hover'));
  if (module_exists('hoverintent')) {
    $options['hoverIntent'] = t('HoverIntent');
  }
  $form['thumbnailhover']['hover'] = array(
    '#type' => 'radios',
    '#title' => t('Mouse hover'),
    '#options' => $options,
    '#default_value' => $view->options['thumbnailhover']['hover'],
    '#description' => t('The !hoverintent, if installed, adds the %hoverintent option here. Selecting it causes a delay when the mouse hovers, to stop quick flybys from triggering the behavior. Selecting %hoverdefault chooses the default mouse behavior.', array('!hoverintent' => l(t('HoverIntent module'), 'http://drupal.org/project/hoverintent'), '%hoverintent' => t('HoverIntent'), '%hoverdefault' => t('Hover'))),
  );
  $form['thumbnailhover']['timer_delay'] = array(
    '#type' => 'textfield',
    '#title' => t('Timer delay (in milliseconds)'),
    '#default_value' => $view->options['thumbnailhover']['timer_delay'],
  );
  $options = array(
    1 => t('Forward'),
    -1 => t('Reverse'),
    0 => t('Random'),
  );
  $form['thumbnailhover']['sort'] = array(
    '#type' => 'radios',
    '#title' => t('Slideshow sort order'),
    '#description' => t('This option determines the sort order of the returned results within the slideshow. Note that it is not related to the View\'s sorting options, and will only affect resulting items.'),
    '#options' => $options,
    '#default_value' => $view->options['thumbnailhover']['sort'],
  );
  $form['thumbnailhover']['fade'] = array(
    '#type' => 'checkbox',
    '#title' => t('Fade'),
    '#default_value' => $view->options['thumbnailhover']['fade'],
    '#description' => t('If checked, then the slideshow will fade between frames. Otherwise, the Fade speed and value, below, will be ignored.'),
  );
  $options = array(
    'slow' => t('Slow'),
    'normal' => t('Normal'),
    'fast' => t('Fast'),
  );
  $form['thumbnailhover']['fade_speed'] = array(
    '#type' => 'radios',
    '#title' => t('Fade speed'),
    '#options' => $options,
    '#default_value' => $view->options['thumbnailhover']['fade_speed'],
  );
  $form['thumbnailhover']['fade_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Fade value'),
    '#description' => t('The opacity to fade to, between 0 (fully transparent) and 1 (fully opaque).'),
    '#default_value' => $view->options['thumbnailhover']['fade_value'],
  );

  $options = array(
    'teaser' => t('Teaser'),
    'full' => t('Full'),
  );
  $form['thumbnailhover']['hover_breakout'] = array(
    '#type' => 'radios',
    '#title' => t('Hover breakout'),
    '#options' => $options,
    '#default_value' => $view->options['hover_breakout'],
    '#description' => t("Hover breakout determines how to display the breakout element of the %thumbnail mode, either as a teaser or full node. It is ignored in %single mode.", array('%thumbnail' => t('Thumbnail hover'), '%single' => t('Single frame'))),
  );
  $form['thumbnailhover']['teasers_last'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display teasers last'),
    '#default_value' => $view->options['teasers_last'],
    '#description' => t('When the mode is thumbnail hover, this determines whether to print the teasers first or second.'),
  );
}
