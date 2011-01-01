(function ($) {
  Drupal.viewsSlideshow = Drupal.viewsSlideshow || {};
  
  Drupal.behaviors.viewsSlideshow = {
    attach: function (context) {
  
      // Process previous link
      $('.views_slideshow_controls_text_previous:not(.views-slideshow-controls-text-previous-processed)', context).addClass('views-slideshow-controls-text-previous-processed').each(function() {
        var uniqueID = $(this).attr('id').replace('views_slideshow_controls_text_previous_', '');
        $(this).click(function() {
          Drupal.viewsSlideshow.previousSlide(uniqueID, '');
          return false;
        });
      });
      
      // Process next link
      $('.views_slideshow_controls_text_next:not(.views-slideshow-controls-text-next-processed)', context).addClass('views-slideshow-controls-text-next-processed').each(function() {
        var uniqueID = $(this).attr('id').replace('views_slideshow_controls_text_next_', '');
        $(this).click(function() {
          Drupal.viewsSlideshow.nextSlide(uniqueID, '');
          return false;
        });
      });
      
      // Process pause link
      $('.views_slideshow_controls_text_pause:not(.views-slideshow-controls-text-pause-processed)', context).addClass('views-slideshow-controls-text-pause-processed').each(function() {
        var uniqueID = $(this).attr('id').replace('views_slideshow_controls_text_pause_', '');
        $(this).click(function() {
          if (Drupal.settings.viewsSlideshow[uniqueID].paused) {
            Drupal.viewsSlideshow.play(uniqueID, '');
          }
          else {
            Drupal.viewsSlideshow.pause(uniqueID, '');
          }
          return false;
        });
      });
      
      // Process pause on hover for pager.
      $('.views_slideshow_pager_field:not(.views-slideshow-pager-field-processed)', context).addClass('views-slideshow-pager-field-processed').each(function() {
        // Parse out the location and unique id from the full id.
        var pagerInfo = $(this).attr('id').split('_');
        var location = pagerInfo[2];
        pagerInfo.splice(0, 3);
        var uniqueID = pagerInfo.join('_');
        
        // Add the activate and pause on pager hover event to each pager item.
        if (Drupal.settings.viewsSlideshowPagerFields[uniqueID][location].activatePauseOnHover) {
          $(this).children().each(function(index, pagerItem) {
            $(pagerItem).hover(function() {
              Drupal.viewsSlideshow.goToSlide(uniqueID, '', index);
              Drupal.viewsSlideshow.pause(uniqueID, '');
            },
            function() {
              Drupal.viewsSlideshow.play(uniqueID, '');
            });
          });
        }
      });
    }
  };
  
  Drupal.viewsSlideshowControlsText = Drupal.viewsSlideshowControlsText || {};

  /**
   * Implement hook_viewsSlideshowPause for text controls.
   */
  Drupal.viewsSlideshowControlsText.pause = function (slideshowID) {
    var pauseText = Drupal.theme.prototype['viewsSlideshowControlsPause'] ? Drupal.theme('viewsSlideshowControlsPause') : '';
    $('#views_slideshow_controls_text_pause_' + slideshowID).text(pauseText);
  }
  
  /**
   * Implement hook_viewsSlideshowPlay for text controls.
   */
  Drupal.viewsSlideshowControlsText.play = function (slideshowID) {
    var playText = Drupal.theme.prototype['viewsSlideshowControlsPlay'] ? Drupal.theme('viewsSlideshowControlsPlay') : '';
    $('#views_slideshow_controls_text_pause_' + slideshowID).text(playText);
  }
  
  // Theme control pause.
  Drupal.theme.prototype.viewsSlideshowControlsPause = function () {
    return Drupal.t('Resume');
  }
  
  // Theme control pause.
  Drupal.theme.prototype.viewsSlideshowControlsPlay = function () {
    return Drupal.t('Pause');
  }
  
  Drupal.viewsSlideshowPagerFields = Drupal.viewsSlideshowPagerFields || {};
  
  /**
   * Implement hook_viewsSlidshowTransitionBegin for pager fields pager.
   */
  Drupal.viewsSlideshowPagerFields.transitionBegin = function (slideshowID, slideNum) {
    // Remove active class from pagers
    $('[id^="views_slideshow_pager_field_item_' + slideshowID + '"]').removeClass('active');
    
    // Add active class to active pager.
    $('#views_slideshow_pager_field_item_' + slideshowID + '_' + slideNum).addClass('active');
  }
  
  Drupal.viewsSlideshowSlideCounter = Drupal.viewsSlideshowSlideCounter || {};
  
  /**
   * Implement hook_viewsSlidshowTransitionBegin for pager fields pager.
   */
  Drupal.viewsSlideshowSlideCounter.transitionBegin = function (slideshowID, slideNum) {
    $('#views_slideshow_slide_counter_' + slideshowID + ' .num').text(slideNum + 1);
  }
  
  /**
   * Call this function to pause the slideshow.
   */
  Drupal.viewsSlideshow.pause = function (slideshowID, callingMethod) {
    Drupal.settings.viewsSlideshow[slideshowID].paused = 1;
    var methods = Drupal.settings.viewsSlideshow[slideshowID]['methods'];
    for (i = 0; i < methods.length; i++) {
      if (typeof Drupal[methods[i]].pause == 'function' && methods[i] != callingMethod) {
        Drupal[methods[i]].pause(slideshowID);
      }
    }
  }
  
  /**
   * Call this function to play the slideshow.
   */
  Drupal.viewsSlideshow.play = function (slideshowID, callingMethod) {
    Drupal.settings.viewsSlideshow[slideshowID].paused = 0;
    var methods = Drupal.settings.viewsSlideshow[slideshowID]['methods'];
    for (i = 0; i < methods.length; i++) {
      if (typeof Drupal[methods[i]].play == 'function' && methods[i] != callingMethod) {
        Drupal[methods[i]].play(slideshowID);
      }
    }
  }
  
  /**
   * Call this function to move the slideshow to the next slide.
   */
  Drupal.viewsSlideshow.nextSlide = function (slideshowID, callingMethod) {
    var methods = Drupal.settings.viewsSlideshow[slideshowID]['methods'];
    for (i = 0; i < methods.length; i++) {
      if (typeof Drupal[methods[i]].nextSlide == 'function' && methods[i] != callingMethod) {
        Drupal[methods[i]].nextSlide(slideshowID);
      }
    }
  }
  
  /**
   * Call this function to move the slideshow to the previous slide.
   */
  Drupal.viewsSlideshow.previousSlide = function (slideshowID, callingMethod) {
    var methods = Drupal.settings.viewsSlideshow[slideshowID]['methods'];
    for (i = 0; i < methods.length; i++) {
      if (typeof Drupal[methods[i]].previousSlide == 'function' && methods[i] != callingMethod) {
        Drupal[methods[i]].previousSlide(slideshowID);
      }
    }
  }
  
  /**
   * Call this function to go to a specific slide number.
   */
  Drupal.viewsSlideshow.goToSlide = function (slideshowID, callingMethod, slideNum) {
    var methods = Drupal.settings.viewsSlideshow[slideshowID]['methods'];
    for (i = 0; i < methods.length; i++) {
      if (typeof Drupal[methods[i]].goToSlide == 'function' && methods[i] != callingMethod) {
        Drupal[methods[i]].goToSlide(slideshowID, slideNum);
      }
    }
  }
  
  /**
   * Call this function when the slideshow transition begins.
   */
  Drupal.viewsSlideshow.transitionBegin = function (slideshowID, callingMethod, slideNum) {
    var methods = Drupal.settings.viewsSlideshow[slideshowID]['methods'];
    for (i = 0; i < methods.length; i++) {
      if (typeof Drupal[methods[i]].transitionBegin == 'function' && methods[i] != callingMethod) {
        Drupal[methods[i]].transitionBegin(slideshowID, slideNum);
      }
    }
  }
  
  /**
   * Call this function when the slideshow transition ends.
   */
  Drupal.viewsSlideshow.transitionEnd = function (slideshowID, callingMethod, slideToNum) {
    var methods = Drupal.settings.viewsSlideshow[slideshowID]['methods'];
    for (i = 0; i < methods.length; i++) {
      if (typeof Drupal[methods[i]].transitionEnd == 'function' && methods[i] != callingMethod) {
        Drupal[methods[i]].transitionEnd(slideshowID, slideToNum);
      }
    }
  }
})(jQuery);
