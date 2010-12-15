<?php
// $Id$

/**
 * @file
 * The default options available with Views Slideshow: cycle.
 */

function views_slideshow_cycle_views_slideshow_slideshow_types() {
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

      // Internet Explorer Tweaks
      'cleartype' => array('default' => 'true'),
      'cleartypenobg' => array('default' => 'false'),

      // Advanced
      'cycle_options' => array('default' => 0),
      'advanced_use_fx' => array('default' => 0),
      'advanced_fx' => array('default' => 'fade'),
      'advanced_use_timeout' => array('default' => 0),
      'advanced_timeout' => array('default' =>  4000),
      'advanced_use_timeoutFn' => array('default' => 0),
      'advanced_timeoutFn' => array('default' =>  NULL),
      'advanced_use_continuous' => array('default' => 0),
      'advanced_continuous' => array('default' =>  0),
      'advanced_use_speed' => array('default' => 0),
      'advanced_speed' => array('default' =>  1000),
      'advanced_use_speedIn' => array('default' => 0),
      'advanced_speedIn' => array('default' =>  NULL),
      'advanced_use_speedOut' => array('default' => 0),
      'advanced_speedOut' => array('default' =>  NULL),
      'advanced_use_next' => array('default' => 0),
      'advanced_next' => array('default' =>  NULL),
      'advanced_use_prev' => array('default' => 0),
      'advanced_prev' => array('default' =>  NULL),
      'advanced_use_prevNextClick' => array('default' => 0),
      'advanced_prevNextClick' => array('default' =>  NULL),
      'advanced_use_prevNextEvent' => array('default' => 0),
      'advanced_prevNextEvent' => array('default' =>  'click.cycle'),
      'advanced_use_pager' => array('default' => 0),
      'advanced_pager' => array('default' =>  NULL),
      'advanced_use_pagerClick' => array('default' => 0),
      'advanced_pagerClick' => array('default' =>  NULL),
      'advanced_use_pagerEvent' => array('default' => 0),
      'advanced_pagerEvent' => array('default' =>  'click.cycle'),
      'advanced_use_allowPagerClickBubble' => array('default' => 0),
      'advanced_allowPagerClickBubble' => array('default' => 0),
      'advanced_use_pagerAnchorBuilder' => array('default' => 0),
      'advanced_pagerAnchorBuilder' => array('default' =>  NULL),
      'advanced_use_before' => array('default' => 0),
      'advanced_before' => array('default' =>  NULL),
      'advanced_use_after' => array('default' => 0),
      'advanced_after' => array('default' =>  NULL),
      'advanced_use_end' => array('default' => 0),
      'advanced_end' => array('default' =>  NULL),
      'advanced_use_easing' => array('default' => 0),
      'advanced_easing' => array('default' =>  NULL),
      'advanced_use_easeIn' => array('default' => 0),
      'advanced_easeIn' => array('default' =>  NULL),
      'advanced_use_easeOut' => array('default' => 0),
      'advanced_easeOut' => array('default' =>  NULL),
      'advanced_use_shuffle' => array('default' => 0),
      'advanced_shuffle' => array('default' =>  NULL),
      'advanced_use_animIn' => array('default' => 0),
      'advanced_animIn' => array('default' =>  NULL),
      'advanced_use_animOut' => array('default' => 0),
      'advanced_animOut' => array('default' =>  NULL),
      'advanced_use_cssBefore' => array('default' => 0),
      'advanced_cssBefore' => array('default' =>  NULL),
      'advanced_use_cssAfter' => array('default' => 0),
      'advanced_cssAfter' => array('default' =>  NULL),
      'advanced_use_fxFn' => array('default' => 0),
      'advanced_fxFn' => array('default' =>  NULL),
      'advanced_use_height' => array('default' => 0),
      'advanced_height' => array('default' =>  'auto'),
      'advanced_use_startingSlide' => array('default' => 0),
      'advanced_startingSlide' => array('default' =>  0),
      'advanced_use_sync' => array('default' => 0),
      'advanced_sync' => array('default' =>  1),
      'advanced_use_random' => array('default' => 0),
      'advanced_random' => array('default' =>  0),
      'advanced_use_fit' => array('default' => 0),
      'advanced_fit' => array('default' =>  0),
      'advanced_use_containerResize' => array('default' => 0),
      'advanced_containerResize' => array('default' =>  1),
      'advanced_use_pause' => array('default' => 0),
      'advanced_pause' => array('default' =>  0),
      'advanced_use_pauseOnPagerHover' => array('default' => 0),
      'advanced_pauseOnPagerHover' => array('default' =>  0),
      'advanced_use_autostop' => array('default' => 0),
      'advanced_autostop' => array('default' =>  0),
      'advanced_use_autostopCount' => array('default' => 0),
      'advanced_autostopCount' => array('default' =>  0),
      'advanced_use_delay' => array('default' => 0),
      'advanced_delay' => array('default' =>  0),
      'advanced_use_slideExpr' => array('default' => 0),
      'advanced_slideExpr' => array('default' =>  NULL),
      'advanced_use_cleartype' => array('default' => 0),
      'advanced_cleartype' => array('default' => 1),
      'advanced_use_cleartypeNoBg' => array('default' => 0),
      'advanced_cleartypeNoBg' => array('default' => 0),
      'advanced_use_nowrap' => array('default' => 0),
      'advanced_nowrap' => array('default' =>  0),
      'advanced_use_fastOnEvent' => array('default' => 0),
      'advanced_fastOnEvent' => array('default' =>  0),
      'advanced_use_randomizeEffects' => array('default' => 0),
      'advanced_randomizeEffects' => array('default' =>  1),
      'advanced_use_rev' => array('default' => 0),
      'advanced_rev' => array('default' =>  0),
      'advanced_use_manualTrump' => array('default' => 0),
      'advanced_manualTrump' => array('default' =>  1),
      'advanced_use_requeueOnImageNotLoaded' => array('default' => 0),
      'advanced_requeueOnImageNotLoaded' => array('default' => 1),
      'advanced_use_requeueTimeout' => array('default' => 0),
      'advanced_requeueTimeout' => array('default' =>  250),
      'advanced_use_activePagerClass' => array('default' => 0),
      'advanced_activePagerClass' => array('default' =>  'activeSlide'),
      'advanced_use_updateActivePagerLink' => array('default' => 0),
      'advanced_updateActivePagerLink' => array('default' =>  NULL),
    ),
  );
  return $options;
}

function views_slideshow_cycle_views_slideshow_slideshow_type_form(&$form, &$form_state, &$view) {
  
  // Transition
  $form['views_slideshow_cycle']['transition'] = array(
    '#value' => '<h2>' . t('Transition') . '</h2>',
  );
  
  $effects = array(
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
    '#options' => $effects,
    '#default_value' => $view->options['views_slideshow_cycle']['effect'],
    '#description' => t('The transition effect that will be used to change between images. Not all options below may be relevant depending on the effect. ' . l('Follow this link to see examples of each effect.', 'http://jquery.malsup.com/cycle/browser.html', array('attributes' => array('target' => '_blank')))),
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
  
  // All the jquery cycle options according to
  // http://malsup.com/jquery/cycle/options.html
  $cycle_options = array(
    'activePagerClass' => t('class name used for the active pager link'),
    'after' => t('transition callback (scope set to element that was shown):     function(currSlideElement, nextSlideElement, options, forwardFlag)  Do not enter the function in this box.  Only enter what you would have entered within the function.'),
    'allowPagerClickBubble' => t('allows or prevents click event on pager anchors from bubbling'),
    'animIn' => t('properties that define how the slide animates in'),
    'animOut' => t('properties that define how the slide animates out'),
    'autostop' => t('true to end slideshow after X transitions (where X == slide count)'),
    'autostopCount' => t('number of transitions (optionally used with autostop to define X)'),
    'before' => t('transition callback (scope set to element to be shown):     function(currSlideElement, nextSlideElement, options, forwardFlag)  Do not enter the function in this box.  Only enter what you would have entered within the function.'),
    'cleartype' => t('true if clearType corrections should be applied (for IE)'),
    'cleartypeNoBg' => t('set to true to disable extra cleartype fixing (leave false to force background color setting on slides)'),
    'containerResize' => t('resize container to fit largest slide'),
    'continuous' => t('true to start next transition immediately after current one completes'),
    'cssAfter' => t('properties that defined the state of the slide after transitioning out'),
    'cssBefore' => t('properties that define the initial state of the slide before transitioning in'),
    'delay' => t('additional delay (in ms) for first transition (hint: can be negative)'),
    'easing' => t('easing method for both in and out transitions'),
    'easingIn' => t('easing for "in" transition'),
    'easingOut' => t('easing for "out" transition'),
    'end' => t('callback invoked when the slideshow terminates (use with autostop or nowrap options): function(options)  Do not enter the function in this box.  Only enter what you would have entered within the function.'),
    'fastOnEvent' => t('force fast transitions when triggered manually (via pager or prev/next); value == time in ms'),
    'fit' => t('force slides to fit container'),
    'fx' => t('name of transition effect (or comma separated names, ex: fade,scrollUp,shuffle)'),
    'fxFn' => t('function used to control the transition: function(currSlideElement, nextSlideElement, options, afterCalback, forwardFlag)  Do not enter the function in this box.  Only enter what you would have entered within the function.'),
    'height' => t('container height'),
    'manualTrump' => t('causes manual transition to stop an active transition instead of being ignored'),
    'next' => t('selector for element to use as click trigger for next slide'),
    'nowrap' => t('true to prevent slideshow from wrapping'),
    'pager' => t('selector for element to use as pager container'),
    'pagerAnchorBuilder' => t('callback fn for building anchor links:  function(index, DOMelement)  Do not enter the function in this box.  Only enter what you would have entered within the function.'),
    'pagerClick' => t('callback fn for pager clicks:    function(zeroBasedSlideIndex, slideElement)  Do not enter the function in this box.  Only enter what you would have entered within the function.'),
    'pagerEvent' => t('name of event which drives the pager navigation'),
    'pause' => t('true to enable "pause on hover"'),
    'pauseOnPagerHover' => t('true to pause when hovering over pager link'),
    'prev' => t('selector for element to use as click trigger for previous slide'),
    'prevNextClick' => t('callback fn for prev/next clicks:    function(isNext, zeroBasedSlideIndex, slideElement)  Do not enter the function in this box.  Only enter what you would have entered within the function.'),
    'prevNextEvent' => t('event which drives the manual transition to the previous or next slide'),
    'random' => t('true for random, false for sequence (not applicable to shuffle fx)'),
    'randomizeEffects' => t('valid when multiple effects are used; true to make the effect sequence random'),
    'requeueOnImageNotLoaded' => t('requeue the slideshow if any image slides are not yet loaded'),
    'requeueTimeout' => t('ms delay for requeue'),
    'rev' => t('causes animations to transition in reverse'),
    'shuffle' => t('coords for shuffle animation, ex: { top:15, left: 200 }'),
    'slideExpr' => t('expression for selecting slides (if something other than all children is required)'),
    'speed' => t('speed of the transition (any valid fx speed value)'),
    'speedIn' => t('speed of the "in" transition'),
    'speedOut' => t('speed of the "out" transition'),
    'startingSlide' => t('zero-based index of the first slide to be displayed'),
    'sync' => t('true if in/out transitions should occur simultaneously'),
    'timeout' => t('milliseconds between slide transitions (0 to disable auto advance)'),
    'timeoutFn' => t('callback for determining per-slide timeout value:  function(currSlideElement, nextSlideElement, options, forwardFlag)  Do not enter the function in this box.  Only enter what you would have entered within the function.'),
    'updateActivePagerLink' => t('callback fn invoked to update the active pager link (adds/removes activePagerClass style)'),
  );
  
  foreach ($cycle_options as $name => $description) {
    $lower_name = strtolower($name);
    // fx
    $form['views_slideshow_cycle']['advanced_use_' . $lower_name] = array(
      '#type' => 'checkbox',
      '#title' => t('Override !name setting', array('!name' => $name)),
      '#default_value' => $view->options['views_slideshow_cycle']['advanced_use_' . $lower_name],
      '#process' => array('views_process_dependency'),
      '#dependency' => array('edit-style-options-views-slideshow-cycle-cycle-options' => array(1)),
    );
    
    $form['views_slideshow_cycle']['advanced_' . $lower_name] = array(
      '#type' => 'textarea',
      '#title' => t('!lower_name', array('!lower_name' => $lower_name)),
      '#default_value' => $view->options['views_slideshow_cycle']['advanced_' . $lower_name],
      '#description' => $description,  // Don't need to wrap in t() since it's done above.
      '#process' => array('views_process_dependency'),
      '#dependency_count' => 2,
      '#dependency' => array(
        'edit-style-options-views-slideshow-cycle-cycle-options' => array(1),
        'edit-style-options-views-slideshow-cycle-advanced-use-' . $lower_name => array(1),
      ),
    );
  }
}

function views_slideshow_cycle_views_slideshow_options_form_validate(&$form, &$form_state, &$view) {
  if (!is_numeric($form_state['values']['style_options']['views_slideshow_cycle']['speed'])) {
    form_error($form['views_slideshow_cycle']['speed'], t('!setting must be numeric!', array('Speed')));
  }
  if (!is_numeric($form_state['values']['style_options']['views_slideshow_cycle']['timeout'])) {
    form_error($form['views_slideshow_cycle']['speed'], t('!setting must be numeric!', array('timeout')));
  }
  if (!is_numeric($form_state['values']['style_options']['views_slideshow_cycle']['remember_slide_days'])) {
    form_error($form['views_slideshow_cycle']['remember_slide_days'], t('!setting must be numeric!', array('Slide days')));
  }
}
