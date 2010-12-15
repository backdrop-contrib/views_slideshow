Drupal.behaviors.viewsSlideshow = function (context) {
  
  // Process previous link
  $('.views_slideshow_controls_previous:not(.views-slideshow-controls-previous-processed)', context).addClass('views-slideshow-controls-previous-processed').each(function() {
    var uniqueID = $(this).attr('id').replace('views_slideshow_controls_previous_', '');
    $(this).click(function() {
      viewsSlideshowPreviousSlide(uniqueID, 'views_slideshow_controls');
      return false;
    });
  });
  
  // Process next link
  $('.views_slideshow_controls_next:not(.views-slideshow-controls-next-processed)', context).addClass('views-slideshow-controls-next-processed').each(function() {
    var uniqueID = $(this).attr('id').replace('views_slideshow_controls_next_', '');
    $(this).click(function() {
      viewsSlideshowNextSlide(uniqueID, 'views_slideshow_controls');
      return false;
    });
  });
  
  // Process pause link
  $('.views_slideshow_controls_pause:not(.views-slideshow-controls-pause-processed)', context).addClass('views-slideshow-controls-pause-processed').each(function() {
    var uniqueID = $(this).attr('id').replace('views_slideshow_controls_pause_', '');
    $(this).click(function() {
      if (Drupal.settings.viewsSlideshow[uniqueID].paused) {
        var playText = Drupal.theme.prototype['viewsSlideshowControlsPlay'] ? Drupal.theme('viewsSlideshowControlsPlay') : '';
        $(this).text(playText);
        viewsSlideshowPlay(uniqueID, 'views_slideshow_controls');
      }
      else {
        var pauseText = Drupal.theme.prototype['viewsSlideshowControlsPause'] ? Drupal.theme('viewsSlideshowControlsPause') : '';
        $(this).text(pauseText);
        viewsSlideshowPause(uniqueID, 'views_slideshow_controls');
      }
      return false;
    });
  });
}

// Theme control pause.
Drupal.theme.prototype.viewsSlideshowControlsPause = function () {
  return Drupal.t('Resume');
}

// Theme control pause.
Drupal.theme.prototype.viewsSlideshowControlsPlay = function () {
  return Drupal.t('Pause');
}

/**
 * Implement hook_viewsSlidshowTransitionBegin for pager fields pager.
 */
function views_slideshow_pager_fields_viewsSlideshowTransitionBegin(slideshowID, slideNum) {
  // Remove active class from pagers
  $('[id^="views_slideshow_pager_field_item_' + slideshowID + '"]').removeClass('active');
  
  // Add active class to active pager.
  $('#views_slideshow_pager_field_item_' + slideshowID + '_' + slideNum).addClass('active');
}

/**
 * Implement hook_viewsSlidshowTransitionBegin for pager fields pager.
 */
function views_slideshow_slide_counter_viewsSlideshowTransitionBegin(slideshowID, slideNum) {
  $('#views_slideshow_slide_counter_' + slideshowID + ' .num').text(slideNum + 1);
}

/**
 * Call this function to pause the slideshow.
 */
viewsSlideshowPause = function (slideshowID, callingMethod) {
  Drupal.settings.viewsSlideshow[slideshowID].paused = 1;
  var methods = Drupal.settings.viewsSlideshow[slideshowID]['methods'];
  for (i = 0; i < methods.length; i++) {    
    if (typeof window[methods[i] + '_viewsSlideshowPause'] == 'function' && methods[i] != callingMethod) {
      window[methods[i] + '_viewsSlideshowPause'](slideshowID);
    }
  }
}

/**
 * Call this function to play the slideshow.
 */
viewsSlideshowPlay = function (slideshowID, callingMethod) {
  Drupal.settings.viewsSlideshow[slideshowID].paused = 0;
  var methods = Drupal.settings.viewsSlideshow[slideshowID]['methods'];
  for (i = 0; i < methods.length; i++) {
    if (typeof window[methods[i] + '_viewsSlideshowPlay'] == 'function' && methods[i] != callingMethod) {
      window[methods[i] + '_viewsSlideshowPlay'](slideshowID);
    }
  }
}

/**
 * Call this function to move the slideshow to the next slide.
 */
viewsSlideshowNextSlide = function (slideshowID, callingMethod) {
  var methods = Drupal.settings.viewsSlideshow[slideshowID]['methods'];
  for (i = 0; i < methods.length; i++) {
    if (typeof window[methods[i] + '_viewsSlideshowNextSlide'] == 'function' && methods[i] != callingMethod) {
      window[methods[i] + '_viewsSlideshowNextSlide'](slideshowID);
    }
  }
}

/**
 * Call this function to move the slideshow to the previous slide.
 */
viewsSlideshowPreviousSlide = function (slideshowID, callingMethod) {
  var methods = Drupal.settings.viewsSlideshow[slideshowID]['methods'];
  for (i = 0; i < methods.length; i++) {
    if (typeof window[methods[i] + '_viewsSlideshowPreviousSlide'] == 'function' && methods[i] != callingMethod) {
      window[methods[i] + '_viewsSlideshowPreviousSlide'](slideshowID);
    }
  }
}

/**
 * Call this function to go to a specific slide number.
 */
viewsSlideshowGoToSlide = function (slideshowID, slideNum) {
  var methods = Drupal.settings.viewsSlideshow[slideshowID]['methods'];
  for (i = 0; i < methods.length; i++) {
    if (typeof window[methods[i] + '_viewsSlideshowGoToSlide'] == 'function' && methods[i] != callingMethod) {
      window[methods[i] + '_viewsSlideshowGoToSlide'](slideshowID, slideNum);
    }
  }
}

/**
 * Call this function when the slideshow transition begins.
 */
viewsSlideshowTransitionBegin = function (slideshowID, callingMethod, slideNum) {
  var methods = Drupal.settings.viewsSlideshow[slideshowID]['methods'];
  for (i = 0; i < methods.length; i++) {
    if (typeof window[methods[i] + '_viewsSlideshowTransitionBegin'] == 'function' && methods[i] != callingMethod) {
      window[methods[i] + '_viewsSlideshowTransitionBegin'](slideshowID, slideNum);
    }
  }
}

/**
 * Call this function when the slideshow transition ends.
 */
function viewsSlideshowTransitionEnd(slideshowID, callingMethod, slideToNum) {
  var methods = Drupal.settings.viewsSlideshow[slideshowID]['methods'];
  for (i = 0; i < methods.length; i++) {
    if (typeof window[methods[i] + '_viewsSlideshowTransitionEnd'] == 'function' && methods[i] != callingMethod) {
      window[methods[i] + '_viewsSlideshowTransitionEnd'](slideshowID, slideToNum);
    }
  }
}
