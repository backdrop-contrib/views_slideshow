<?php

/**
 * @file
 * Contains the list style plugin.
 */

/**
 * Style plugin to render each item in a slideshow of an ordered or unordered list.
 *
 * @ingroup views_style_plugins
 */
class views_slideshow_plugin_style_slideshow extends views_plugin_style_list {

  // Set default options
  function option_definition() {
    $options = parent::option_definition();
    
    // Load all include files from views slideshow addons.
    module_load_all_includes('views_slideshow.inc');
    
    // call every module using hook_views_slideshow_option_definition and merge
    // it's return value with the other default options.
    return array_merge($options, module_invoke_all('views_slideshow_option_definition'));
  }

  // Build the settings form for the view.
  function options_form(&$form, &$form_state) {
    // load up all views slideshow modules functions.
    module_load_all_includes('views_slideshow.inc');
    parent::options_form($form, $form_state);
    
    
    // Style
    $form['slideshow_skin_header'] = array(
      '#markup' => '<h2>' . t('Style') . '</h2>',
    );
    
    // Get a list of all available skins.
    $skin_info = $this->views_slideshow_get_skins();
    foreach ($skin_info as $skin => $info) {
      $skins[$skin] = $info['title'];
    }
    asort($skins);
  
    // Create the drop down box so users can choose an available skin.
    $form['slideshow_skin'] = array(
      '#type' => 'select',
      '#title' => t('Skin'),
      '#options' => $skins,
      '#default_value' => $this->options['slideshow_skin'],
      '#description' => t('Select the skin to use for this display.  Skins allow for easily swappable layouts of things like next/prev links and thumbnails.  Note that not all skins support all widgets, so a combination of skins and widgets may lead to unpredictable results in layout.'),
    );
    
    /**
     * Slides
     */
    $form['slides_header'] = array(
      '#markup' => '<h2>' . t('Slides') . '</h2>',
    );
    
    // Get all slideshow types.
    $modules = module_invoke_all('views_slideshow_slideshow_types');

    if ($modules) { 
      
      $form['slideshow_type'] = array(
        '#type' => 'select',
        '#title' => t('Slideshow Type'),
        '#options' => $modules,
        '#default_value' => $this->options['slideshow_type'],
      );
      
      $arguments = array(
        &$form,
        &$form_state,
        &$this,
      );
      
      foreach (module_implements('views_slideshow_slideshow_type_form') as $module) {
        $form[$module] = array(
          '#type' => 'fieldset',
          '#title' => t('!module options', array('!module' => $modules[$module])),
          '#collapsible' => TRUE,
          '#attributes' => array('class' => array($module)),
          '#states' => array(
            'visible' => array(
              ':input[name="style_options[slideshow_type]"]' => array('value' => $module),
            ),
          ),
        );

        $function = $module . '_views_slideshow_slideshow_type_form';
        call_user_func_array($function, $arguments);
      }
    }
    else {
      $form['enable_module'] = array(
        '#markup' => t('There is no Views Slideshow plugin enabled. Go to the !modules and enable a Views Slideshow plugin module. For example Views Slideshow Singleframe.', array('!modules' => l('Modules Page', 'admin/build/modules'))),
      );
    }
    
    /**
     * Widgets
     */
    $form['widgets_header'] = array(
      '#markup' => '<h2>' . t('Widgets') . '</h2>',
    );
    
    // Loop through all locations so we can add header for each location.
    $location = array('top' => t('Top'), 'bottom' => t('Bottom'));
    foreach ($location as $location_id => $location_name) {
      // Widget Header
      $form['widgets'][$location_id]['header'] = array(
        '#markup' => '<h3>' . t('!location Widgets', array('!location' => $location_name)) . '</h3>',
      );
    }
    
    // Get all widgets that are registered.
    // If we have widgets then build it's form fields.
    $widgets = module_invoke_all('views_slideshow_widget_info');
    if (!empty($widgets)) {
      
      // Build our weight values by number of widgets
      $weights = array();
      for ($i = 1; $i <= count($widgets); $i++) {
        $weights[$i] = $i;
      }
      
      // Loop through our widgets and locations to build our form values for
      // each widget.
      foreach ($widgets as $widget_id => $widget_name) {
        foreach ($location as $location_id => $location_name) {
          $widget_dependency = 'style_options[widgets][' . $location_id . '][' . $widget_id . ']';
          // Use Widget Checkbox
          $form['widgets'][$location_id][$widget_id]['enable'] = array(
            '#type' => 'checkbox',
            '#title' => t($widget_name),
            '#default_value' => $this->options['widgets'][$location_id][$widget_id]['enable'],
            '#description' => t('Should a !name be rendered at the !location of the slides.', array('!name' => $widget_name, '!location' => $location_name)),
          );
          
          // Widget weight
          // We check to see if the default value is greater than the number of
          // widgets just in case a widget has been removed and the form hasn't
          // hasn't been saved again.
          $form['widgets'][$location_id][$widget_id]['weight'] = array(
            '#type' => 'select',
            '#title' => t('Weight of the !name', array('!name' => $widget_name)),
            '#default_value' => ($this->options['widgets'][$location_id][$widget_id]['weight'] > count($widgets)) ? count($widgets) : $this->options['widgets'][$location_id][$widget_id]['weight'],
            '#options' => $weights,
            '#description' => t('Determines in what order the !name appears.  A lower weight will cause the !name to be above higher weight items.', array('!name' => $widget_name)),
            '#states' => array(
              'visible' => array(
                ':input[name="style_options[widgets][' . $location_id . '][' . $widget_id . '][enable]"]' => array('value' => $module),
              ),
            ),
          );
          
          // Add all the widget settings.
          if (function_exists($widget_id . '_views_slideshow_widget_form_options')) {
            $arguments = array(
              &$form['widgets'][$location_id][$widget_id],
              &$form_state,
              &$this,
              $this->options['widgets'][$location_id][$widget_id],
              $widget_dependency,
            );
            call_user_func_array($widget_id . '_views_slideshow_widget_form_options', $arguments);
          }
        }
      }
    }
  }
  
  // Run any validation on the form settings.
  function options_validate(&$form, &$form_state) {
    module_load_all_includes('views_slideshow.inc');
    
    $arguments = array(
      &$form,
      &$form_state,
      &$this,
    );
    
    // Call all modules that use hook_views_slideshow_options_form_validate
    foreach (module_implements('views_slideshow_options_form_validate') as $module) {
      $function = $module . '_views_slideshow_options_form_validate';
      call_user_func_array($function, $arguments);
    }
  }
  
  // Run any necessary actions on submit.
  function options_submit(&$form, &$form_state) {
    module_load_all_includes('views_slideshow.inc');
    
    $arguments = array(
      $form,
      &$form_state,
    );
    
    // Call all modules that use hook_views_slideshow_options_form_submit
    foreach (module_implements('views_slideshow_options_form_submit') as $module) {
      $function = $module . '_views_slideshow_options_form_submit';
      call_user_func_array($function, $arguments);
    }
    
    // In addition to the skin, we also pre-save the definition that
    // correspond to it.  That lets us avoid a hook lookup on every page.
    $skins = $this->views_slideshow_get_skins();
    $form_state['values']['style_options']['skin_info'] = $skins[$form_state['values']['style_options']['slideshow_skin']];
  }
  
  /**
   * Retrieve a list of all available skins in the system.
   */
  function views_slideshow_get_skins() {
    static $skins;
  
    if (empty($skins)) {
      $skins = array();
      
      // Call all modules that use hook_views_slideshow_skins
      foreach (module_implements('views_slideshow_skins') as $module) {
        $skin_items = call_user_func($module . '_views_slideshow_skins');
        if (isset($skin_items) && is_array($skin_items)) {
          foreach (array_keys($skin_items) as $skin) {
            // Ensure that the definition is complete, so we don't need lots
            // of error checking later.
            $skin_items[$skin] += array(
              'class' => 'default',
              'title' => t('Untitled skin'),
              'module' => $module,
              'path' => '',
              'stylesheets' => array(),
            );
          }
          $skins = array_merge($skins, $skin_items);
        }
      }
    }
  
    return $skins;
  }
}
