// $Id$

/**
 *  @file
 *  A simple jQuery SingleFrame Div Slideshow Rotator.
 */

/**
 *  This will set our initial behavior, by starting up each individual slideshow.
 */
Drupal.behaviors.viewsSlideshowSingleFrame = function (context) {
  $('.views_slideshow_singleframe_main:not(.viewsSlideshowSingleFrame-processed)', context).addClass('viewsSlideshowSingleFrame-processed').each(function() {
    var fullId = '#' + $(this).attr('id');
    var settings = Drupal.settings.viewsSlideshowSingleFrame[fullId];
    settings.targetId = '#' + $(fullId + " :first").attr('id');

    settings.opts = {
      speed:settings.speed,
      timeout:parseInt(settings.timeout),
      delay:parseInt(settings.delay),
      sync:settings.sync==1,
      random:settings.random==1,
      pause:settings.pause==1,
      prev:(settings.controls > 0)?'#views_slideshow_singleframe_prev_' + settings.id:null,
      next:(settings.controls > 0)?'#views_slideshow_singleframe_next_' + settings.id:null,
      pager:(settings.pager > 0)?'#views_slideshow_singleframe_pager_' + settings.id:null,
      after:function(curr, next, opts) {
        // Used for Image Counter.
        if (settings.image_count) {
          $('#views_slideshow_singleframe_image_count_' + settings.id + ' span.num').html(opts.currSlide + 1);
          $('#views_slideshow_singleframe_image_count_' + settings.id + ' span.total').html(opts.slideCount);
        }
      },
      cleartype:(settings.ie.cleartype),
      cleartypeNoBg:(settings.ie.cleartypenobg)
    }
    
    if (settings.effect == 'none') {
      settings.opts.speed = 1;
    }
    else {
      settings.opts.fx = settings.effect;
    }
    
    /**
     * Add additional settings.
     */
    var advanced = settings.advanced.split("\n");
    for (i=0; i<advanced.length; i++) {
      var prop = '';
      var value = '';
      var property = advanced[i].split(":");
      for (j=0; j<property.length; j++) {
        if (j == 0) {
          prop = property[j];
        }
        else if (j == 1) {
          value = property[j];
        }
        else {
          value += ":" + property[j];
        }
      }
      settings.opts[prop] = value;
    }
    
    $(settings.targetId).cycle(settings.opts);
    
    if (settings.controls > 0) {
      // Show controls for people who have js enabled browsers.
      $('#views_slideshow_singleframe_controls_' + settings.id).show();
      
      $('#views_slideshow_singleframe_playpause_' + settings.id).click(function(e) {
      	if (settings.paused) {
      	  $(settings.targetId).cycle('resume');
      	  $('#views_slideshow_singleframe_playpause_' + settings.id).addClass('views_slideshow_singleframe_pause').removeClass('views_slideshow_singleframe_play').text('Pause');
      	  settings.paused = false;
      	}
      	else {
      	  $(settings.targetId).cycle('pause');
      	  $('#views_slideshow_singleframe_playpause_' + settings.id).addClass('views_slideshow_singleframe_play').removeClass('views_slideshow_singleframe_pause').text('Resume');
      	  settings.paused = true;
      	}
        e.preventDefault();
      });
    }
  });
}
