(function ($) {
  Backdrop.viewsSlideshow = Backdrop.viewsSlideshow || {};

  /**
   * Views Slideshow Controls
   */
  Backdrop.viewsSlideshowControls = Backdrop.viewsSlideshowControls || {};

  /**
   * Implement the play hook for controls.
   */
  Backdrop.viewsSlideshowControls.play = function (options) {
    // Route the control call to the correct control type.
    // Need to use try catch so we don't have to check to make sure every part
    // of the object is defined.
    try {
      if (typeof Backdrop.settings.viewsSlideshowControls[options.slideshowID].top.type != "undefined" && typeof Backdrop[Backdrop.settings.viewsSlideshowControls[options.slideshowID].top.type].play == 'function') {
        Backdrop[Backdrop.settings.viewsSlideshowControls[options.slideshowID].top.type].play(options);
      }
    }
    catch(err) {
      // Don't need to do anything on error.
    }

    try {
      if (typeof Backdrop.settings.viewsSlideshowControls[options.slideshowID].bottom.type != "undefined" && typeof Backdrop[Backdrop.settings.viewsSlideshowControls[options.slideshowID].bottom.type].play == 'function') {
        Backdrop[Backdrop.settings.viewsSlideshowControls[options.slideshowID].bottom.type].play(options);
      }
    }
    catch(err) {
      // Don't need to do anything on error.
    }
  };

  /**
   * Implement the pause hook for controls.
   */
  Backdrop.viewsSlideshowControls.pause = function (options) {
    // Route the control call to the correct control type.
    // Need to use try catch so we don't have to check to make sure every part
    // of the object is defined.
    try {
      if (typeof Backdrop.settings.viewsSlideshowControls[options.slideshowID].top.type != "undefined" && typeof Backdrop[Backdrop.settings.viewsSlideshowControls[options.slideshowID].top.type].pause == 'function') {
        Backdrop[Backdrop.settings.viewsSlideshowControls[options.slideshowID].top.type].pause(options);
      }
    }
    catch(err) {
      // Don't need to do anything on error.
    }

    try {
      if (typeof Backdrop.settings.viewsSlideshowControls[options.slideshowID].bottom.type != "undefined" && typeof Backdrop[Backdrop.settings.viewsSlideshowControls[options.slideshowID].bottom.type].pause == 'function') {
        Backdrop[Backdrop.settings.viewsSlideshowControls[options.slideshowID].bottom.type].pause(options);
      }
    }
    catch(err) {
      // Don't need to do anything on error.
    }
  };


  /**
   * Views Slideshow Text Controls
   */

  // Add views slieshow api calls for views slideshow text controls.
  Backdrop.behaviors.viewsSlideshowControlsText = {
    attach: function (context) {

      // Process previous link
      $('.views_slideshow_controls_text_previous:not(.views-slideshow-controls-text-previous-processed)', context).addClass('views-slideshow-controls-text-previous-processed').each(function() {
        var uniqueID = $(this).attr('id').replace('views_slideshow_controls_text_previous_', '');
        $(this).click(function() {
          Backdrop.viewsSlideshow.action({ "action": 'previousSlide', "slideshowID": uniqueID });
          return false;
        });
      });

      // Process next link
      $('.views_slideshow_controls_text_next:not(.views-slideshow-controls-text-next-processed)', context).addClass('views-slideshow-controls-text-next-processed').each(function() {
        var uniqueID = $(this).attr('id').replace('views_slideshow_controls_text_next_', '');
        $(this).click(function() {
          Backdrop.viewsSlideshow.action({ "action": 'nextSlide', "slideshowID": uniqueID });
          return false;
        });
      });

      // Process pause link
      $('.views_slideshow_controls_text_pause:not(.views-slideshow-controls-text-pause-processed)', context).addClass('views-slideshow-controls-text-pause-processed').each(function() {
        var uniqueID = $(this).attr('id').replace('views_slideshow_controls_text_pause_', '');
        $(this).click(function() {
          if (Backdrop.settings.viewsSlideshow[uniqueID].paused) {
            Backdrop.viewsSlideshow.action({ "action": 'play', "slideshowID": uniqueID, "force": true });
          }
          else {
            Backdrop.viewsSlideshow.action({ "action": 'pause', "slideshowID": uniqueID, "force": true });
          }
          return false;
        });
      });
    }
  };

  Backdrop.viewsSlideshowControlsText = Backdrop.viewsSlideshowControlsText || {};

  /**
   * Implement the pause hook for text controls.
   */
  Backdrop.viewsSlideshowControlsText.pause = function (options) {
    var pauseText = Backdrop.theme.prototype['viewsSlideshowControlsPause'] ? Backdrop.theme('viewsSlideshowControlsPause') : '';
    $('#views_slideshow_controls_text_pause_' + options.slideshowID + ' a').text(pauseText);
    $('#views_slideshow_controls_text_pause_' + options.slideshowID).removeClass('views-slideshow-controls-text-status-play');
    $('#views_slideshow_controls_text_pause_' + options.slideshowID).addClass('views-slideshow-controls-text-status-pause');
  };

  /**
   * Implement the play hook for text controls.
   */
  Backdrop.viewsSlideshowControlsText.play = function (options) {
    var playText = Backdrop.theme.prototype['viewsSlideshowControlsPlay'] ? Backdrop.theme('viewsSlideshowControlsPlay') : '';
    $('#views_slideshow_controls_text_pause_' + options.slideshowID + ' a').text(playText);
    $('#views_slideshow_controls_text_pause_' + options.slideshowID).removeClass('views-slideshow-controls-text-status-pause');
    $('#views_slideshow_controls_text_pause_' + options.slideshowID).addClass('views-slideshow-controls-text-status-play');
  };

  // Theme the resume control.
  Backdrop.theme.prototype.viewsSlideshowControlsPause = function () {
    return Backdrop.t('Resume');
  };

  // Theme the pause control.
  Backdrop.theme.prototype.viewsSlideshowControlsPlay = function () {
    return Backdrop.t('Pause');
  };

  /**
   * Views Slideshow Pager
   */
  Backdrop.viewsSlideshowPager = Backdrop.viewsSlideshowPager || {};

  /**
   * Implement the transitionBegin hook for pagers.
   */
  Backdrop.viewsSlideshowPager.transitionBegin = function (options) {
    // Route the pager call to the correct pager type.
    // Need to use try catch so we don't have to check to make sure every part
    // of the object is defined.
    try {
      if (typeof Backdrop.settings.viewsSlideshowPager != "undefined" && typeof Backdrop.settings.viewsSlideshowPager[options.slideshowID].top.type != "undefined" && typeof Backdrop[Backdrop.settings.viewsSlideshowPager[options.slideshowID].top.type].transitionBegin == 'function') {
        Backdrop[Backdrop.settings.viewsSlideshowPager[options.slideshowID].top.type].transitionBegin(options);
      }
    }
    catch(err) {
      // Don't need to do anything on error.
    }

    try {
      if (typeof Backdrop.settings.viewsSlideshowPager != "undefined" && typeof Backdrop.settings.viewsSlideshowPager[options.slideshowID].bottom.type != "undefined" && typeof Backdrop[Backdrop.settings.viewsSlideshowPager[options.slideshowID].bottom.type].transitionBegin == 'function') {
        Backdrop[Backdrop.settings.viewsSlideshowPager[options.slideshowID].bottom.type].transitionBegin(options);
      }
    }
    catch(err) {
      // Don't need to do anything on error.
    }
  };

  /**
   * Implement the goToSlide hook for pagers.
   */
  Backdrop.viewsSlideshowPager.goToSlide = function (options) {
    // Route the pager call to the correct pager type.
    // Need to use try catch so we don't have to check to make sure every part
    // of the object is defined.
    try {
      if (typeof Backdrop.settings.viewsSlideshowPager[options.slideshowID].top.type != "undefined" && typeof Backdrop[Backdrop.settings.viewsSlideshowPager[options.slideshowID].top.type].goToSlide == 'function') {
        Backdrop[Backdrop.settings.viewsSlideshowPager[options.slideshowID].top.type].goToSlide(options);
      }
    }
    catch(err) {
      // Don't need to do anything on error.
    }

    try {
      if (typeof Backdrop.settings.viewsSlideshowPager[options.slideshowID].bottom.type != "undefined" && typeof Backdrop[Backdrop.settings.viewsSlideshowPager[options.slideshowID].bottom.type].goToSlide == 'function') {
        Backdrop[Backdrop.settings.viewsSlideshowPager[options.slideshowID].bottom.type].goToSlide(options);
      }
    }
    catch(err) {
      // Don't need to do anything on error.
    }
  };

  /**
   * Implement the previousSlide hook for pagers.
   */
  Backdrop.viewsSlideshowPager.previousSlide = function (options) {
    // Route the pager call to the correct pager type.
    // Need to use try catch so we don't have to check to make sure every part
    // of the object is defined.
    try {
      if (typeof Backdrop.settings.viewsSlideshowPager[options.slideshowID].top.type != "undefined" && typeof Backdrop[Backdrop.settings.viewsSlideshowPager[options.slideshowID].top.type].previousSlide == 'function') {
        Backdrop[Backdrop.settings.viewsSlideshowPager[options.slideshowID].top.type].previousSlide(options);
      }
    }
    catch(err) {
      // Don't need to do anything on error.
    }

    try {
      if (typeof Backdrop.settings.viewsSlideshowPager[options.slideshowID].bottom.type != "undefined" && typeof Backdrop[Backdrop.settings.viewsSlideshowPager[options.slideshowID].bottom.type].previousSlide == 'function') {
        Backdrop[Backdrop.settings.viewsSlideshowPager[options.slideshowID].bottom.type].previousSlide(options);
      }
    }
    catch(err) {
      // Don't need to do anything on error.
    }
  };

  /**
   * Implement the nextSlide hook for pagers.
   */
  Backdrop.viewsSlideshowPager.nextSlide = function (options) {
    // Route the pager call to the correct pager type.
    // Need to use try catch so we don't have to check to make sure every part
    // of the object is defined.
    try {
      if (typeof Backdrop.settings.viewsSlideshowPager[options.slideshowID].top.type != "undefined" && typeof Backdrop[Backdrop.settings.viewsSlideshowPager[options.slideshowID].top.type].nextSlide == 'function') {
        Backdrop[Backdrop.settings.viewsSlideshowPager[options.slideshowID].top.type].nextSlide(options);
      }
    }
    catch(err) {
      // Don't need to do anything on error.
    }

    try {
      if (typeof Backdrop.settings.viewsSlideshowPager[options.slideshowID].bottom.type != "undefined" && typeof Backdrop[Backdrop.settings.viewsSlideshowPager[options.slideshowID].bottom.type].nextSlide == 'function') {
        Backdrop[Backdrop.settings.viewsSlideshowPager[options.slideshowID].bottom.type].nextSlide(options);
      }
    }
    catch(err) {
      // Don't need to do anything on error.
    }
  };


  /**
   * Views Slideshow Pager Fields
   */

  // Add views slieshow api calls for views slideshow pager fields.
  Backdrop.behaviors.viewsSlideshowPagerFields = {
    attach: function (context) {
      // Process pause on hover.
      $('.views_slideshow_pager_field:not(.views-slideshow-pager-field-processed)', context).addClass('views-slideshow-pager-field-processed').each(function() {
        // Parse out the location and unique id from the full id.
        var pagerInfo = $(this).attr('id').split('_');
        var location = pagerInfo[2];
        pagerInfo.splice(0, 3);
        var uniqueID = pagerInfo.join('_');

        // Add the activate and pause on pager hover event to each pager item.
        if (Backdrop.settings.viewsSlideshowPagerFields[uniqueID][location].activatePauseOnHover) {
          $(this).children().each(function(index, pagerItem) {
            var mouseIn = function() {
              Backdrop.viewsSlideshow.action({ "action": 'goToSlide', "slideshowID": uniqueID, "slideNum": index });
              Backdrop.viewsSlideshow.action({ "action": 'pause', "slideshowID": uniqueID });
            };

            var mouseOut = function() {
              Backdrop.viewsSlideshow.action({ "action": 'play', "slideshowID": uniqueID });
            };

            if (jQuery.fn.hoverIntent) {
              $(pagerItem).hoverIntent(mouseIn, mouseOut);
            }
            else {
              $(pagerItem).hover(mouseIn, mouseOut);
            }
          });
        }
        else {
          $(this).children().each(function(index, pagerItem) {
            $(pagerItem).click(function() {
              Backdrop.viewsSlideshow.action({ "action": 'goToSlide', "slideshowID": uniqueID, "slideNum": index });
            });
          });
        }
      });
    }
  };

  Backdrop.viewsSlideshowPagerFields = Backdrop.viewsSlideshowPagerFields || {};

  /**
   * Implement the transitionBegin hook for pager fields pager.
   */
  Backdrop.viewsSlideshowPagerFields.transitionBegin = function (options) {
    for (pagerLocation in Backdrop.settings.viewsSlideshowPager[options.slideshowID]) {
      // Remove active class from pagers
      $('[id^="views_slideshow_pager_field_item_' + pagerLocation + '_' + options.slideshowID + '"]').removeClass('active');

      // Add active class to active pager.
      $('#views_slideshow_pager_field_item_'+ pagerLocation + '_' + options.slideshowID + '_' + options.slideNum).addClass('active');
    }
  };

  /**
   * Implement the goToSlide hook for pager fields pager.
   */
  Backdrop.viewsSlideshowPagerFields.goToSlide = function (options) {
    for (pagerLocation in Backdrop.settings.viewsSlideshowPager[options.slideshowID]) {
      // Remove active class from pagers
      $('[id^="views_slideshow_pager_field_item_' + pagerLocation + '_' + options.slideshowID + '"]').removeClass('active');

      // Add active class to active pager.
      $('#views_slideshow_pager_field_item_' + pagerLocation + '_' + options.slideshowID + '_' + options.slideNum).addClass('active');
    }
  };

  /**
   * Implement the previousSlide hook for pager fields pager.
   */
  Backdrop.viewsSlideshowPagerFields.previousSlide = function (options) {
    for (pagerLocation in Backdrop.settings.viewsSlideshowPager[options.slideshowID]) {
      // Get the current active pager.
      var pagerNum = $('[id^="views_slideshow_pager_field_item_' + pagerLocation + '_' + options.slideshowID + '"].active').attr('id').replace('views_slideshow_pager_field_item_' + pagerLocation + '_' + options.slideshowID + '_', '');

      // If we are on the first pager then activate the last pager.
      // Otherwise activate the previous pager.
      if (pagerNum == 0) {
        pagerNum = $('[id^="views_slideshow_pager_field_item_' + pagerLocation + '_' + options.slideshowID + '"]').length() - 1;
      }
      else {
        pagerNum--;
      }

      // Remove active class from pagers
      $('[id^="views_slideshow_pager_field_item_' + pagerLocation + '_' + options.slideshowID + '"]').removeClass('active');

      // Add active class to active pager.
      $('#views_slideshow_pager_field_item_' + pagerLocation + '_' + options.slideshowID + '_' + pagerNum).addClass('active');
    }
  };

  /**
   * Implement the nextSlide hook for pager fields pager.
   */
  Backdrop.viewsSlideshowPagerFields.nextSlide = function (options) {
    for (pagerLocation in Backdrop.settings.viewsSlideshowPager[options.slideshowID]) {
      // Get the current active pager.
      var pagerNum = $('[id^="views_slideshow_pager_field_item_' + pagerLocation + '_' + options.slideshowID + '"].active').attr('id').replace('views_slideshow_pager_field_item_' + pagerLocation + '_' + options.slideshowID + '_', '');
      var totalPagers = $('[id^="views_slideshow_pager_field_item_' + pagerLocation + '_' + options.slideshowID + '"]').length();

      // If we are on the last pager then activate the first pager.
      // Otherwise activate the next pager.
      pagerNum++;
      if (pagerNum == totalPagers) {
        pagerNum = 0;
      }

      // Remove active class from pagers
      $('[id^="views_slideshow_pager_field_item_' + pagerLocation + '_' + options.slideshowID + '"]').removeClass('active');

      // Add active class to active pager.
      $('#views_slideshow_pager_field_item_' + pagerLocation + '_' + options.slideshowID + '_' + slideNum).addClass('active');
    }
  };


  /**
   * Views Slideshow Slide Counter
   */

  Backdrop.viewsSlideshowSlideCounter = Backdrop.viewsSlideshowSlideCounter || {};

  /**
   * Implement the transitionBegin for the slide counter.
   */
  Backdrop.viewsSlideshowSlideCounter.transitionBegin = function (options) {
    $('#views_slideshow_slide_counter_' + options.slideshowID + ' .num').text(options.slideNum + 1);
  };

  /**
   * This is used as a router to process actions for the slideshow.
   */
  Backdrop.viewsSlideshow.action = function (options) {
    // Set default values for our return status.
    var status = {
      'value': true,
      'text': ''
    };

    // If an action isn't specified return false.
    if (typeof options.action == 'undefined' || options.action == '') {
      status.value = false;
      status.text =  Backdrop.t('There was no action specified.');
      return error;
    }

    // If we are using pause or play switch paused state accordingly.
    if (options.action == 'pause') {
      Backdrop.settings.viewsSlideshow[options.slideshowID].paused = 1;
      // If the calling method is forcing a pause then mark it as such.
      if (options.force) {
        Backdrop.settings.viewsSlideshow[options.slideshowID].pausedForce = 1;
      }
    }
    else if (options.action == 'play') {
      // If the slideshow isn't forced pause or we are forcing a play then play
      // the slideshow.
      // Otherwise return telling the calling method that it was forced paused.
      if (!Backdrop.settings.viewsSlideshow[options.slideshowID].pausedForce || options.force) {
        Backdrop.settings.viewsSlideshow[options.slideshowID].paused = 0;
        Backdrop.settings.viewsSlideshow[options.slideshowID].pausedForce = 0;
      }
      else {
        status.value = false;
        status.text += ' ' + Backdrop.t('This slideshow is forced paused.');
        return status;
      }
    }

    // We use a switch statement here mainly just to limit the type of actions
    // that are available.
    switch (options.action) {
      case "goToSlide":
      case "transitionBegin":
      case "transitionEnd":
        // The three methods above require a slide number. Checking if it is
        // defined and it is a number that is an integer.
        if (typeof options.slideNum == 'undefined' || typeof options.slideNum !== 'number' || parseInt(options.slideNum) != (options.slideNum - 0)) {
          status.value = false;
          status.text = Backdrop.t('An invalid integer was specified for slideNum.');
        }
      case "pause":
      case "play":
      case "nextSlide":
      case "previousSlide":
        // Grab our list of methods.
        var methods = Backdrop.settings.viewsSlideshow[options.slideshowID]['methods'];

        // if the calling method specified methods that shouldn't be called then
        // exclude calling them.
        var excludeMethodsObj = {};
        if (typeof options.excludeMethods !== 'undefined') {
          // We need to turn the excludeMethods array into an object so we can use the in
          // function.
          for (var i=0; i < excludeMethods.length; i++) {
            excludeMethodsObj[excludeMethods[i]] = '';
          }
        }

        // Call every registered method and don't call excluded ones.
        for (i = 0; i < methods[options.action].length; i++) {
          if (Backdrop[methods[options.action][i]] != undefined && typeof Backdrop[methods[options.action][i]][options.action] == 'function' && !(methods[options.action][i] in excludeMethodsObj)) {
            Backdrop[methods[options.action][i]][options.action](options);
          }
        }
        break;

      // If it gets here it's because it's an invalid action.
      default:
        status.value = false;
        status.text = Backdrop.t('An invalid action "!action" was specified.', { "!action": options.action });
    }
    return status;
  };
})(jQuery);
