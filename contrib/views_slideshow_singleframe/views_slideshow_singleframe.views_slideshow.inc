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
  $options['singleframe'] =array(
    'contains' => array(
      'timeout' => array('default' => 5000),
      'sort' => array('default' => 1),
      'effect' => array('default' => 'fade'),
      'speed' => array('default' => 700) //normal
    )
  );
  return $options;
}

function views_slideshow_singleframe_views_slideshow_options_form(&$form, &$form_state, &$view) {
  $form['singleframe'] = array(
    '#type' => 'fieldset',
    '#title' => t('SingleFrame rotator options'),
    '#collapsible' => TRUE,
    '#collapsed' => !($view->options['mode'] == 'singleframe'),
  );
  $form['singleframe']['timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timer delay'),
    '#default_value' => (isset($view->options['singleframe']['timeout'])) ? $view->options['singleframe']['timeout'] : 1000,
    '#description' => t('Amount of time in milliseconds between transitions.')
  );
  $form['singleframe']['speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Speed'),
    '#default_value' => (isset($view->options['singleframe']['speed'])) ? $view->options['singleframe']['speed'] : 700,
    '#description' => t('Time in milliseconds that each transition lasts. Numeric only!'),  
  );
  $form['singleframe']['random'] = array(
    '#type' => 'radios',
    '#title' => t('Random'),
    '#description' => t('This option controls the order items are displayed. The default setting, False, uses the views ordering. True will cause the images to display in a random order.'),
    '#options' => array(0 => t('False'), 1 => t('True')),
    '#default_value' => isset($view->options['singleframe']['random'])? $view->options['singleframe']['random'] : 0,
  );
  $form['singleframe']['pause'] = array(
    '#type' => 'radios',
    '#title' => t('Pause'),
    '#options' => array(1 => t('Yes'),2 => t('No')),
    '#default_value' => (isset($view->options['singleframe']['pause'])) ? $view->options['singleframe']['pause'] : 1,
    '#description' => t('Pause when hovering on the slideshow image.'),
  );
  $form['singleframe']['controls'] = array(
    '#type' => 'select',
    '#title' => t('Controls'),
    '#options' => array(0 => t('None'),1 => t('Top'),2 => t('Bottom')),
    '#default_value' => (isset($view->options['singleframe']['controls'])) ? $view->options['singleframe']['controls'] : 0,
    '#description' => t('Determine if controls for the slideshow (start/stop/next/previous) should appear, and if so whether they should appear before or after the slideshow.'),
  );
  $form['singleframe']['pager'] = array(
    '#type' => 'select',
    '#title' => t('Pager'),
    '#options' => array(0 => t('None'),1 => t('Top'),2 => t('Bottom')),
    '#default_value' => (isset($view->options['singleframe']['pager'])) ? $view->options['singleframe']['pager'] : 0,
    '#description' => t('Determine if a pager for the slideshow (1|2|3) should appear, and if so whether they should appear before or after the slideshow.'),
  );
  $options = array(
    'none' => 'none',
    'blindX' => 'blindX',
    'blindY' => 'blindY',
    'blindZ' => 'blindZ',
    'cover' => 'cover',
    'curtainX' => 'curtainX',
    'curtainY' => 'curtainY',
    'fade' => 'fade',
    'fadeZoom' => 'fadeZoom',
    'growX' => 'growX',
    'growY' => 'growY',
    'scrollUp' => 'scrollUp',
    'scrollDown' => 'scrollDown',
    'scrollLeft' => 'scrollLeft',
    'scrollRight' => 'scrollRight',
    'scrollHorz' => 'scrollHorz',
    'scrollVert' => 'scrollVert',
    'shuffle' => 'shuffle',
    'slideX' => 'slideX',
    'slideY' => 'slideY',
    'toss' => 'toss',
    'turnUp' => 'turnUp',
    'turnDown' => 'turnDown',
    'turnLeft' => 'turnLeft',
    'turnRight' => 'turnRight',
    'uncover' => 'uncover',
    'wipe' => 'wipe',
    'zoom' => 'zoom' 
  );
  $form['singleframe']['effect'] = array(
    '#type' => 'select',
    '#title' => t('Effect'),
    '#options' => $options,
    '#default_value' => (isset($view->options['singleframe']['effect'])) ? $view->options['singleframe']['effect'] : 'fade',
    '#description' => t('The transition effect that will be used to change between images. Not all options below may be relevant depending on the effect.'),
  );
  $form['singleframe']['sync'] = array(
    '#type' => 'radios',
    '#title' => t('Sync'),
    '#options' => array(1 => t('Yes'), 2 => t('No')),
    '#default_value' =>(isset($view->options['singleframe']['sync'])) ? $view->options['singleframe']['sync'] : 1,
    '#description' => t('The sync option controls whether the slide transitions occur simultaneously. The default is yes which means that the current slide transitions out as the next slide transitions in. By setting the sync option to no you can get some interesting twists on your transitions.'),  
  );
}

function views_slideshow_singleframe_views_slideshow_options_form_validate(&$form, &$form_state, &$view) {
  if (!is_numeric($form_state['values']['style_options']['singleframe']['speed'])) {
    form_error($form['singleframe']['speed'], t('!setting must be numeric!',array('Speed')));
  }
  if (!is_numeric($form_state['values']['style_options']['singleframe']['timeout'])) {
    form_error($form['singleframe']['speed'], t('!setting must be numeric!',array('timeout')));
  }
}