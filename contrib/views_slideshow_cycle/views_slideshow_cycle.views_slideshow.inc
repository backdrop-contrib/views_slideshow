<?php
// $Id$

/**
 * @file
 * The default options available with Views Slideshow: cycle.
 */

function views_slideshow_cycle_views_slideshow_modes() {
  $options = array(
    'views_slideshow_cycle' => t('Cycle'),
  );
  return $options;
}

function views_slideshow_cycle_views_slideshow_option_definition() {
  $options['views_slideshow_cycle'] = array(
    'contains' => array(
      // Transition
      'effect' => array('default' => 'fade'),
      'transition_advanced' => array('default' => 0),
      'timeout' => array('default' => 5000),
      'speed' => array('default' => 700), //normal
      'delay' => array('default' => 0),
      'sync' => array('default' => 1),
      'random' => array('default' => 0),
      
      // Action
      'pause' => array('default' => 1),
      'pause_on_click' => array('default' => 0),
      'transition_advanced' => array('default' => 0),
      'start_paused' => array('default', 0),
      'remember_slide' => array('default' => 0),
      'remember_slide_days' => array('default' => 1),
      'pause_when_hidden' => array('default' => 0),
      'pause_when_hidden_type' => array('default' => 'full'),
      'amount_allowed_visible' => array('default' => ''),
      'nowrap' => array('default' => 0),
      'fixed_height' => array('default' => 1),
      'items_per_slide' => array('default' => 1),

      // Pager and Controls
      'pager' => array('default' => 0),
      'pager_type' => array('default' => 'numbered'),
      'pager_fields' => array('default' => array()),
      'pager_hover' => array('default' => 0),
      'pager_click_to_page' => array('default' => 0),
      'controls' => array('default' => 0),
      'slide_counter' => array('default' => 0),

      // Internet Explorer Tweaks
      'cleartype' => array('default' => 'true'),
      'cleartypenobg' => array('default' => 'false'),

      // Advanced
      'advanced' => array('default' => ''),
    ),
  );
  return $options;
}

function views_slideshow_cycle_views_slideshow_options_form(&$form, &$form_state, &$view) {
  
  // Transition
  $form['views_slideshow_cycle']['transition'] = array(
    '#value' => '<h2>' . t('Transition') . '</h2>',
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
  $form['views_slideshow_cycle']['effect'] = array(
    '#type' => 'select',
    '#title' => t('Effect'),
    '#options' => $options,
    '#default_value' => $view->options['views_slideshow_cycle']['effect'],
    '#description' => t('The transition effect that will be used to change between images. Not all options below may be relevant depending on the effect.'),
  );
   
  // Transition advanced options
  $form['views_slideshow_cycle']['transition_advanced'] = array(
    '#type' => 'checkbox',
    '#title' => t('View Transition Advanced Options'),
    '#default_value' => $view->options['views_slideshow_cycle']['transition_advanced'], 
  );
  $form['views_slideshow_cycle']['timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timer delay'),
    '#default_value' => $view->options['views_slideshow_cycle']['timeout'],
    '#description' => t('Amount of time in milliseconds between transitions. Set the value to 0 to not rotate the slideshow automatically.'),
    '#process' => array('views_process_dependency'),
    '#dependency' => array('edit-style-options-views-slideshow-cycle-transition-advanced' => array(1)),
  );
  $form['views_slideshow_cycle']['speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Speed'),
    '#default_value' => $view->options['views_slideshow_cycle']['speed'],
    '#description' => t('Time in milliseconds that each transition lasts. Numeric only!'),
    '#process' => array('views_process_dependency'),
    '#dependency' => array('edit-style-options-views-slideshow-cycle-transition-advanced' => array(1)),
  );
  $form['views_slideshow_cycle']['delay'] = array(
    '#type' => 'textfield',
    '#title' => t('Initial slide delay offset'),
    '#default_value' => $view->options['views_slideshow_cycle']['delay'],
    '#description' => t('Amount of time in milliseconds for the first slide to transition. This number will be added to Timer delay to create the initial delay.  For example if Timer delay is 4000 and Initial delay is 2000 then the first slide will change at 6000ms (6 seconds).  If Initial delay is -2000 then the first slide will change at 2000ms (2 seconds).'),
    '#process' => array('views_process_dependency'),
    '#dependency' => array('edit-style-options-views-slideshow-cycle-transition-advanced' => array(1)),
  );
  $form['views_slideshow_cycle']['sync'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sync'),
    '#default_value' => $view->options['views_slideshow_cycle']['sync'],
    '#description' => t('The sync option controls whether the slide transitions occur simultaneously. The default is selected which means that the current slide transitions out as the next slide transitions in. By unselecting this option you can get some interesting twists on your transitions.'),
    '#process' => array('views_process_dependency'),
    '#dependency' => array('edit-style-options-views-slideshow-cycle-transition-advanced' => array(1)),
  );
  $form['views_slideshow_cycle']['random'] = array(
    '#type' => 'checkbox',
    '#title' => t('Random'),
    '#description' => t('This option controls the order items are displayed. The default setting, unselected, uses the views ordering. Selected will cause the images to display in a random order.'),
    '#default_value' => $view->options['views_slideshow_cycle']['random'],
    '#process' => array('views_process_dependency'),
    '#dependency' => array('edit-style-options-views-slideshow-cycle-transition-advanced' => array(1)),
  );
  
  // Action
  $form['views_slideshow_cycle']['action'] = array(
    '#value' => '<h2>' . t('Action') . '</h2>',
  );
  $form['views_slideshow_cycle']['pause'] = array(
    '#type' => 'checkbox',
    '#title' => t('Pause on hover'),
    '#default_value' => $view->options['views_slideshow_cycle']['pause'],
    '#description' => t('Pause when hovering on the slideshow image.'),
  );
  $form['views_slideshow_cycle']['pause_on_click'] = array(
    '#type' => 'checkbox',
    '#title' => t('Pause On Click'),
    '#default_value' => $view->options['views_slideshow_cycle']['pause_on_click'],
    '#description' => t('Pause when the slide is clicked.'),
  );
  
  // Action Advanced Options
  $form['views_slideshow_cycle']['action_advanced'] = array(
    '#type' => 'checkbox',
    '#title' => t('View Action Advanced Options'),
    '#default_value' => $view->options['views_slideshow_cycle']['action_advanced'], 
  );
  $form['views_slideshow_cycle']['start_paused'] = array(
    '#type' => 'checkbox',
    '#title' => t('Start Slideshow Paused'),
    '#default_value' => $view->options['views_slideshow_cycle']['start_paused'],
    '#description' => t('Start the slideshow in the paused state.'),
    '#process' => array('views_process_dependency'),
    '#dependency' => array('edit-style-options-views-slideshow-cycle-action-advanced' => array(1)),
  );
  $form['views_slideshow_cycle']['remember_slide'] = array(
    '#type' => 'checkbox',
    '#title' => t('Start On Last Slide Viewed'),
    '#default_value' => $view->options['views_slideshow_cycle']['remember_slide'],
    '#description' => t('When the user leaves a page with a slideshow and comes back start them on the last slide viewed.'),
    '#process' => array('views_process_dependency'),
    '#dependency' => array('edit-style-options-views-slideshow-cycle-action-advanced' => array(1)),
  );
  $form['views_slideshow_cycle']['remember_slide_days'] = array(
    '#type' => 'textfield',
    '#title' => t('Length of Time to Remember Last Slide'),
    '#default_value' => $view->options['views_slideshow_cycle']['remember_slide_days'],
    '#description' => t('The number of days to have the site remember the last slide. Default is 1'),
    '#size' => 4,
    '#process' => array('views_process_dependency'),
    '#dependency_count' => 2,
    '#dependency' => array(
      'edit-style-options-views-slideshow-cycle-action-advanced' => array(1),
      'edit-style-options-views-slideshow-cycle-remember-slide' => array(1),
    ),
  );
  $form['views_slideshow_cycle']['pause_when_hidden'] = array(
    '#type' => 'checkbox',
    '#title' => t('Pause When the Slideshow is Not Visible'),
    '#default_value' => $view->options['views_slideshow_cycle']['pause_when_hidden'],
    '#description' => t('When the slideshow is scrolled out of view or when a window is resized that hides the slideshow, this will pause the slideshow.'),
    '#process' => array('views_process_dependency'),
    '#dependency' => array('edit-style-options-views-slideshow-cycle-action-advanced' => array(1)),
  );
  $form['views_slideshow_cycle']['pause_when_hidden_type'] = array(
    '#type' => 'select',
    '#title' => t('How to Calculate Amount of Slide that Needs to be Shown'),
    '#options' => array(
      'full' => t('Entire slide'),
      'vertical' => t('Set amount of vertical'),
      'horizontal' => t('Set amount of horizontal'),
      'area' => t('Set total area of the slide'),
    ),
    '#default_value' => $view->options['views_slideshow_cycle']['pause_when_hidden_type'],
    '#description' => t('Choose how to calculate how much of the slide has to be shown. Entire Slide: All the slide has to be shown. Vertical: Set amount of height that has to be shown. Horizontal: Set amount of width that has to be shown. Area: Set total area that has to be shown.'),
    '#process' => array('views_process_dependency'),
    '#dependency_count' => 2,
    '#dependency' => array(
      'edit-style-options-views-slideshow-cycle-action-advanced' => array(1),
      'edit-style-options-views-slideshow-cycle-pause-when-hidden' => array(1),
    ),
  );
  $form['views_slideshow_cycle']['amount_allowed_visible'] = array(
    '#type' => 'textfield',
    '#title' => t('Amount of Slide Needed to be Shown'),
    '#default_value' => $view->options['views_slideshow_cycle']['amount_allowed_visible'],
    '#description' => t("The amount of the slide that needs to be shown to have it rotate. You can set the value in percentage (ex: 50%) or in pixels (ex: 250). The slidehsow will not rotate until it's height/width/total area, depending on the calculation method you have chosen above, is less than the value you have entered in this field."),
    '#size' => 4,
    '#process' => array('views_process_dependency'),
    '#dependency_count' => 3,
    '#dependency' => array(
      'edit-style-options-views-slideshow-cycle-action-advanced' => array(1),
      'edit-style-options-views-slideshow-cycle-pause-when-hidden' => array(1),
      'edit-style-options-views-slideshow-cycle-pause-when-hidden-type' => array(
        'vertical',
        'horizontal',
        'area',
      ),
    ),
  );
  $form['views_slideshow_cycle']['nowrap'] = array(
    '#type' => 'checkbox',
    '#title' => t('End slideshow after last slide'),
    '#default_value' => $view->options['views_slideshow_cycle']['nowrap'],
    '#description' => t('If selected the slideshow will end when it gets to the last slide.'),
    '#process' => array('views_process_dependency'),
    '#dependency' => array('edit-style-options-views-slideshow-cycle-action-advanced' => array(1)),
  );
  $form['views_slideshow_cycle']['fixed_height'] = array(
    '#type' => 'checkbox',
    '#title' => t('Make the slide window height fit the largest slide'),
    '#default_value' => $view->options['views_slideshow_cycle']['fixed_height'],
    '#description' => t('If unselected then if the slides are different sizes the height of the slide area will change as the slides change.'),
    '#process' => array('views_process_dependency'),
    '#dependency' => array('edit-style-options-views-slideshow-cycle-action-advanced' => array(1)),
  );
  $form['views_slideshow_cycle']['items_per_slide'] = array(
    '#type' => 'textfield',
    '#title' => t('Items per slide'),
    '#default_value' => $view->options['views_slideshow_cycle']['items_per_slide'],
    '#description' => t('The number of items per slide'),
    '#size' => 4,
    '#process' => array('views_process_dependency'),
    '#dependency' => array('edit-style-options-views-slideshow-cycle-action-advanced' => array(1)),
  );
  
  // Pager and Controls
  $form['views_slideshow_cycle']['pager_and_controls'] = array(
    '#value' => '<h2>' . t('Pager and Controls') . '</h2>',
  );
  $form['views_slideshow_cycle']['pager'] = array(
    '#type' => 'select',
    '#title' => t('Pager'),
    '#options' => array(
      0 => t('None'),
      'top' => t('Top'),
      'bottom' => t('Bottom'),
    ),
    '#default_value' => $view->options['views_slideshow_cycle']['pager'],
    '#description' => t('Determine if a pager should appear and if so whether they should appear before or after the slideshow.'),
  );
  
  // Get all the pager info from other modules.
  // hook_views_slideshow_pager_settings($view, $option_values, $dependency_prefix)
  $pagers = module_invoke_all('views_slideshow_cycle_pager_settings', $view, $view->options['views_slideshow_cycle'], 'edit-style-options-views-slideshow-cycle-pager');
  
  // Prep the pager options and the fields
  $options = array();
  $pager_fields = array();
  foreach ($pagers as $pager_key => $pager_info) {
    $options[$pager_key] = $pager_info['title'];
    if (isset($pager_info['fields'])) {
      foreach ($pager_info['fields'] as $pager_field_key => $pager_field) {
        $pager_field['#dependency']['edit-style-options-views-slideshow-cycle-pager'] = array('top', 'bottom');
        $pager_field['#dependency']['edit-style-options-views-slideshow-cycle-pager-type'] = array($pager_key);
        $pager_field['#dependency_count'] = count($pager_field['#dependency']);
        if (!isset($pager_field['#process']) || !in_array('views_process_dependency', $pager_field['#process'])) {
          $pager_field['#process'][] = 'views_process_dependency';
        }
        
        $pager_fields[$pager_field_key] = $pager_field;
      }
    }
  }
  
  // Sort the options alphabetically.
  asort($options);
  $form['views_slideshow_cycle']['pager_type'] = array(
    '#type' => 'select',
    '#title' => t('Pager Type'),
    '#options' => $options,
    '#default_value' => $view->options['views_slideshow_cycle']['pager_type'],
    '#description' => t('Style of the pager.'),
    '#process' => array('views_process_dependency'),
    '#dependency' => array('edit-style-options-views-slideshow-cycle-pager' => array('top', 'bottom')),
  );
  
  // Add user defined pager fields to the form.
  $form['views_slideshow_cycle'] = array_merge($form['views_slideshow_cycle'], $pager_fields);
  
  $form['views_slideshow_cycle']['pager_hover'] = array(
    '#type' => 'checkbox',
    '#title' => t('Activate Slide and Pause on Pager Hover'),
    '#default_value' => $view->options['views_slideshow_cycle']['pager_hover'],
    '#description' => t('Should the slide be activated and paused when hovering over a pager item.'),
    '#process' => array('views_process_dependency'),
    '#dependency' => array('edit-style-options-views-slideshow-cycle-pager' => array('top', 'bottom')),
  );
  $form['views_slideshow_cycle']['controls'] = array(
    '#type' => 'select',
    '#title' => t('Controls'),
    '#options' => array(
      0 => t('None'),
      'top' => t('Top'),
      'bottom' => t('Bottom'),
    ),
    '#default_value' => $view->options['views_slideshow_cycle']['controls'],
    '#description' => t('Determine if controls for the slideshow (start/stop/next/previous) should appear, and if so whether they should appear before or after the slideshow.'),
  );
  $form['views_slideshow_cycle']['slide_counter'] = array(
    '#type' => 'select',
    '#title' => t('Slide Counter'),
    '#options' => array(
      0 => t('None'),
      'top' => t('Top'),
      'bottom' => t('Bottom'),
    ),
    '#default_value' => $view->options['views_slideshow_cycle']['slide_counter'],
    '#description' => t('Determine if the Slide Counter (1 of 4) should be displayed and if so whether they should appear before or after the slideshow.'),
  );
  
  // Internet Explorer Tweaks
  $form['views_slideshow_cycle']['ie_tweaks'] = array(
    '#value' => '<h2>' . t('Internet Explorer Tweaks') . '</h2>',
  );
  $form['views_slideshow_cycle']['cleartype'] = array(
    '#type' => 'checkbox',
    '#title' => t('ClearType'),
    '#default_value' => $view->options['views_slideshow_cycle']['cleartype'],
    '#description' => t('Select if clearType corrections should be applied (for IE).  Some background issues could be fixed by unselecting this option.'),
  );
  $form['views_slideshow_cycle']['cleartypenobg'] = array(
    '#type' => 'checkbox',
    '#title' => t('ClearType Background'),
    '#default_value' => $view->options['views_slideshow_cycle']['cleartypenobg'],
    '#description' => t('Select to disable extra cleartype fixing.  Unselect to force background color setting on slides)'),
  );
  
  // Advanced Options
  $form['views_slideshow_cycle']['advanced_options'] = array(
    '#value' => '<h2>' . t('jQuery Cycle Custom Options') . '</h2>',
  );
  $form['views_slideshow_cycle']['cycle_options'] = array(
    '#type' => 'checkbox',
    '#title' => t('View All jQuery Cycle Options'),
    '#default_value' => $view->options['views_slideshow_cycle']['cycle_options'], 
  );
  $form['views_slideshow_cycle']['advanced'] = array(
    '#type' => 'textarea',
    '#title' => t('Advanced Options'),
    '#default_value' => $view->options['views_slideshow_cycle']['advanced'],
    '#description' => t('Add other jQuery cycle options one per line.  Ex. height: 350  !url', array('!url' => l(t('Click here for the additional options to add.'), 'http://malsup.com/jquery/cycle/options.html'))),
    '#process' => array('views_process_dependency'),
    '#dependency' => array('edit-style-options-views-slideshow-cycle-cycle-options' => array(1)),
  );
}

/**
 * Implementation of hook_views_slideshow_cycle_pager_settings
 */
function views_slideshow_cycle_views_slideshow_cycle_pager_settings($view, $option_values, $dependency_prefix) {
  // Settings for Numbered Pager
  $return_value['numbered'] = array(
    'title' => t('Numbered'),
    'fields' => array(
      'numbered_pager_click_to_page' => array(
        '#type' => 'checkbox',
        '#title' => t('Make Pager Linked to Slide Link'),
        '#default_value' => $option_values['numbered_pager_click_to_page'],
        '#description' => t('Should the pager use the main frame link so when it is clicked it goes to the same url that the main frame goes to when clicked.'),
      ),
    ),
  );
  
  // Settings for Thumbnails pager.
  $return_value['thumbnails'] = array(
    'title' => t('Thumbnails'),
    'fields' => array(
      'thumbnails_pager_click_to_page' => array(
        '#type' => 'checkbox',
        '#title' => t('Make Pager Linked to Slide Link'),
        '#default_value' => $option_values['thumbnails_pager_click_to_page'],
        '#description' => t('Should the pager use the main frame link so when it is clicked it goes to the same url that the main frame goes to when clicked.'),
      ),
    ),
  );
  
  if ($view->row_plugin->uses_fields()) {
    $options = array();
    foreach ($view->display->handler->get_handlers('field') as $field => $handler) {
      $options[$field] = $handler->ui_name();
    }
    $return_value['fields'] = array(
      'title' => t('Fields'),
      'fields' => array(
        'pager_fields' => array(
          '#type' => 'checkboxes',
          '#title' => t('Pager fields'),
          '#options' => $options,
          '#default_value' => $option_values['pager_fields'],
          '#description' => t("Choose the fields that will appear in the pager."),
          '#prefix' => '<div id="edit-style-options-views-slideshow-cycle-pager-fields-wrapper"><div id="edit-style-options-views-slideshow-cycle-pager-fields">',
          '#process' => array(
            'expand_checkboxes',
          ),
          '#suffix' => '</div></div>',
        ),
      ),
    );
  }
  
  return $return_value;
}

function views_slideshow_cycle_views_slideshow_options_form_validate(&$form, &$form_state, &$view) {
  if (!is_numeric($form_state['values']['style_options']['views_slideshow_cycle']['speed'])) {
    form_error($form['views_slideshow_cycle']['speed'], t('!setting must be numeric!',array('Speed')));
  }
  if (!is_numeric($form_state['values']['style_options']['views_slideshow_cycle']['timeout'])) {
    form_error($form['views_slideshow_cycle']['speed'], t('!setting must be numeric!',array('timeout')));
  }
  if (!is_numeric($form_state['values']['style_options']['views_slideshow_cycle']['remember_slide_days'])) {
    form_error($form['views_slideshow_cycle']['remember_slide_days'], t('!setting must be numeric!',array('Slide days')));
  }
}
