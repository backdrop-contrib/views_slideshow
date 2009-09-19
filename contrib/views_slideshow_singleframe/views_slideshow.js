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
      cleartype:(settings.cleartype),
      cleartypeNoBg:(settings.cleartypenobg)
    }
    
    if (settings.effect == 'none') {
      settings.opts.speed = 1;
    }
    else {
      settings.opts.fx = settings.effect;
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
