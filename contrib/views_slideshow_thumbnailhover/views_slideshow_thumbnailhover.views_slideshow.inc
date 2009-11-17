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
    'contains' => array (
      'default' => (module_exists('hoverintent') ? 'hoverIntent' : 'hover'),
      'timeout' => array('default' => 5000),
      'sort' => array('default' => 1),
      'effect' => array('default' => 'fade'),
      'speed' => array('default' => 300),
      'fade_value' => array('default' => 0.25),
      'hover_breakout' => array('default' => 'teaser'),
      'teasers_last' => array('default' => TRUE),
      'ie' => array(
        'contains' => array(
          'cleartype' => array('default' => TRUE),
          'cleartypenobg' => array('default' => FALSE),
        ),
      ),
      'advanced' => array('default' => ''),
    ),
  );
  return $options;
}

function views_slideshow_thumbnailhover_views_slideshow_options_form(&$form, &$form_state, &$view) {
  $form['thumbnailhover'] = array(
    '#type' => 'fieldset',
    '#title' => t('ThumbnailHover rotator options'),
    '#collapsible' => TRUE,
    '#attributes' => array('class' => 'thumbnailhover'),
  );
  
  if (module_exists('hoverintent')) {
    $options = array('hover' => t('Hover'));
    $options['hoverIntent'] = t('HoverIntent');
    $form['thumbnailhover']['hover'] = array(
      '#type' => 'radios',
      '#title' => t('Mouse hover'),
      '#options' => $options,
      '#default_value' => $view->options['thumbnailhover']['hover'],
      '#description' => t('The !hoverintent, if installed, adds the %hoverintent option here. Selecting it causes a delay when the mouse hovers, to stop quick flybys from triggering the behavior. Selecting %hoverdefault chooses the default mouse behavior.', array('!hoverintent' => l(t('HoverIntent module'), 'http://drupal.org/project/hoverintent'), '%hoverintent' => t('HoverIntent'), '%hoverdefault' => t('Hover'))),
    );
  }  
  $options = array(
    'teaser' => t('Teaser'),
    'full' => t('Full'),
  );
  if ($view->row_plugin->uses_fields()) {
    $options = array();
    foreach ($view->display->handler->get_handlers('field') as $field => $handler) {
      $options[$field] = $handler->ui_name();
    }
    $form['thumbnailhover']['main_fields'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Main frame fields'),
      '#options' => $options,
      '#default_value' => (!empty($view->options['thumbnailhover']['main_fields'])) ? $view->options['thumbnailhover']['main_fields'] : array(),
      '#description' => t("Choose the fields that will appear in the main slide."),
    );
    $form['thumbnailhover']['breakout_fields'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Breakout fields'),
      '#options' => $options,
      '#default_value' => (!empty($view->options['thumbnailhover']['breakout_fields'])) ? $view->options['thumbnailhover']['breakout_fields'] : array(),
      '#description' => t("Choose the fields that will appear in the breakout thumbnails."),
    );
  } 
  else {
    $form['thumbnailhover']['hover_breakout'] = array(
      '#type' => 'radios',
      '#title' => t('Hover breakout'),
      '#options' => $options,
      '#default_value' => $view->options['thumbnailhover']['hover_breakout'],
      '#description' => t("Hover breakout determines how to display the breakout element of the %thumbnail mode, either as a teaser or full node when the row style is node.", array('%thumbnail' => t('Thumbnail hover'))),
    );
  }
  $form['thumbnailhover']['teasers_last'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display teasers last'),
    '#default_value' => $view->options['thumbnailhover']['teasers_last'],
    '#description' => t('When the mode is thumbnail hover, this determines whether to print the teasers first or second.'),
  );
  $form['thumbnailhover']['timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timer delay'),
    '#default_value' => $view->options['thumbnailhover']['timeout'],
    '#description' => t('Amount of time in milliseconds between transitions.'),
  );
  $form['thumbnailhover']['delay'] = array(
    '#type' => 'textfield',
    '#title' => t('Initial slide delay offset'),
    '#default_value' => (isset($view->options['thumbnailhover']['delay'])) ? $view->options['thumbnailhover']['delay'] : 0,
    '#description' => t('Amount of time in milliseconds for the first slide to transition. This number will be added to Timer delay to create the initial delay.  For example if Timer delay is 4000 and Initial delay is 2000 then the first slide will change at 6000ms (6 seconds).  If Initial delay is -2000 then the first slide will change at 2000ms (2 seconds).')
  );
  $form['thumbnailhover']['speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Speed'),
    '#default_value' => $view->options['thumbnailhover']['speed'],
    '#description' => t('Time in milliseconds that each transition lasts. Numeric only!'),  
  );
  $form['thumbnailhover']['random'] = array(
    '#type' => 'radios',
    '#title' => t('Random'),
    '#description' => t('This option controls the order items are displayed. The default setting, False, uses the views ordering. True will cause the images to display in a random order.'),
    '#options' => array(0 => t('False'), 1 => t('True')),
    '#default_value' => isset($view->options['thumbnailhover']['random'])? $view->options['thumbnailhover']['random'] : 0,
  );
  $form['thumbnailhover']['pause'] = array(
    '#type' => 'radios',
    '#title' => t('Pause'),
    '#options' => array(1 => t('Yes'),2 => t('No')),
    '#default_value' => $view->options['thumbnailhover']['pause'],
    '#description' => t('Pause when hovering on the slideshow image.'),
  );
  $options = array('mouseover' => t('Hover'), 'click' => t('Click'));
  if ((module_exists('jq') && jq_add('hoverIntent')) || (module_exists('hoverintent') && hoverintent_add())) {
    $options['hoverIntent'] = 'hoverIntent';
  }
  $form['thumbnailhover']['pager_event'] = array(
    '#type' => 'select',
    '#title' => t('Pager Event'),
    '#options' => $options,
    '#default_value' => (isset($view->options['thumbnailhover']['pager_event']) ? $view->options['thumbnailhover']['pager_event'] : 'hover'),
    '#description' => t('Which event should be used to select an image from the breakout list.'),
  );
  $form['thumbnailhover']['controls'] = array(
    '#type' => 'select',
    '#title' => t('Controls'),
    '#options' => array(0 => t('None'),1 => t('Top'),2 => t('Bottom')),
    '#default_value' => (isset($view->options['thumbnailhover']['controls'])) ? $view->options['thumbnailhover']['controls'] : 0,
    '#description' => t('Determine if controls for the slideshow (start/stop/next/previous) should appear, and if so whether they should appear before or after the slideshow.'),
  );
  $form['thumbnailhover']['image_count'] = array(
    '#type' => 'select',
    '#title' => t('Image Counter'),
    '#options' => array(0 => t('None'),1 => t('Top'),2 => t('Bottom')),
    '#default_value' => (isset($view->options['thumbnailhover']['image_count'])) ? $view->options['thumbnailhover']['image_count'] : 0,
    '#description' => t('Determine if Image Counter (1 of 4) should be displayed and if so whether they should appear before or after the slideshow.'),
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
    'zoom' => 'zoom',
  );
  $form['thumbnailhover']['effect'] = array(
    '#type' => 'select',
    '#title' => t('Effect'),
    '#options' => $options,
    '#default_value' => $view->options['thumbnailhover']['effect'],
    '#description' => t('The transition effect that will be used to change between images. Not all options below may be relevant depending on the effect.'),
  );
  $form['thumbnailhover']['sync'] = array(
    '#type' => 'radios',
    '#title' => t('Sync'),
    '#options' => array(1 => t('Yes'), 2 => t('No')),
    '#default_value' =>$view->options['thumbnailhover']['sync'],
    '#description' => t('The sync option controls whether the slide transitions occur simultaneously. The default is yes which means that the current slide transitions out as the next slide transitions in. By setting the sync option to no you can get some interesting twists on your transitions.'),  
  );
  $form['thumbnailhover']['advanced'] = array(
    '#type' => 'textarea',
    '#title' => t('Advanced Options'),
    '#default_value' =>(isset($view->options['thumbnailhover']['advanced'])) ? $view->options['thumbnailhover']['advanced'] : '',
    '#description' => t('Add other jQuery cycle options one per line.  Ex. height: 350  !url', array('!url' => l('Click here for the additional options to add.', 'http://malsup.com/jquery/cycle/options.html'))),
  );
  $form['thumbnailhover']['ie'] = array(
    '#type' => 'fieldset',
    '#title' => t('Internet Explorer Options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['thumbnailhover']['ie']['cleartype'] = array(
    '#type' => 'radios',
    '#title' => t('ClearType'),
    '#options' => array('true' => t('True'), 'false' => t('False')),
    '#default_value' =>(isset($view->options['thumbnailhover']['ie']['cleartype'])) ? $view->options['thumbnailhover']['ie']['cleartype'] : 'true',
    '#description' => t('True if clearType corrections should be applied (for IE).  Some background issues could be fixed by setting this to false.'),
  );
  $form['thumbnailhover']['ie']['cleartypenobg'] = array(
    '#type' => 'radios',
    '#title' => t('ClearType Background'),
    '#options' => array('true' => t('True'), 'false' => t('False')),
    '#default_value' =>(isset($view->options['thumbnailhover']['ie']['cleartypenobg'])) ? $view->options['thumbnailhover']['ie']['cleartypenobg'] : 'false',
    '#description' => t('Set to true to disable extra cleartype fixing (leave false to force background color setting on slides)'),
  );
}
function views_slideshow_thumbnailhover_views_slideshow_options_form_validate(&$form, &$form_state, &$view) {
  if (!is_numeric($form_state['values']['style_options']['thumbnailhover']['speed'])) {
    form_error($form['thumbnailhover']['speed'], t('!setting must be numeric!',array('!setting' => 'Speed')));
  }
  if (!is_numeric($form_state['values']['style_options']['thumbnailhover']['timeout'])) {
    form_error($form['thumbnailhover']['timeout'],t('!setting must be numeric!',array('!setting' => 'Timeout')));
  }
}