<?php
// $Id$

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
  /**
   * Set default options
   */
  function option_definition() {
    module_load_all_includes('views_slideshow.inc');
    $options = parent::option_definition();

    $options = array_merge($options, module_invoke_all('views_slideshow_option_definition'));

    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    module_load_all_includes('views_slideshow.inc');
    parent::options_form($form, $form_state);
    
    $modules = module_invoke_all('views_slideshow_modes');

    if ($modules) {
      $form['main_wrapper'] = array(
        '#value' => '<script type="text/javascript">' .
          "$('#views-slideshow-main-wrapper select#edit-style-options-mode option').each(function() {
            $('#views-slideshow-main-wrapper fieldset.' + $(this).val()).hide();
          });
           $('#views-slideshow-main-wrapper fieldset.' + $('#views-slideshow-main-wrapper select#edit-style-options-mode :selected').val()).show();
          
          $('#views-slideshow-main-wrapper select#edit-style-options-mode').change(function() {
            $('#views-slideshow-main-wrapper select#edit-style-options-mode option').each(function() {
              $('#views-slideshow-main-wrapper fieldset.' + $(this).val()).hide();
            });
            $('#views-slideshow-main-wrapper fieldset.' + $('#views-slideshow-main-wrapper select#edit-style-options-mode :selected').val()).show();
          });
          </script>" . 
        '<div id="views-slideshow-main-wrapper">',
      );
      
      $form['mode'] = array(
        '#type' => 'select',
        '#title' => t('Slideshow mode'),
        '#options' => $modules,
        '#default_value' => $this->options['mode'],
      );
      foreach (module_implements('views_slideshow_options_form') as $module) {
        $function = $module .'_views_slideshow_options_form';
        call_user_func_array($function, array(&$form, &$form_state, &$this));
      }
      
      $form['main_wrapper_close'] = array(
        '#value' => '</div>',
      );
    }
    else {
      $form['enable_module'] = array(
        '#value' => t('There is no Views Slideshow plugin enabled. Go to the !modules and enable a Views Slideshow plugin module. For example Views Slideshow Singleframe.', array('!modules' => l('Modules Page', 'admin/build/modules'))),
      );
    }
  }
  
  function options_validate(&$form, &$form_state) {
    module_load_all_includes('views_slideshow.inc');
    foreach (module_implements('views_slideshow_options_form_validate') as $module) {
      $function = $module . '_views_slideshow_options_form_validate';
      call_user_func_array($function, array(&$form, &$form_state, &$this));
    }
  }
}
