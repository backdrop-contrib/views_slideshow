// $Id$

/**
 *  @file
 *  A simple jQuery SingleFrame Div Slideshow Rotator.
 */

/**
 *  This will set our initial behavior, by starting up each individual slideshow.
 */
Drupal.behaviors.viewsSlideshowSingleFrame = function (context) {
  $('.views_slideshow_main:not(.viewsSlideshowSingleFrame-processed)', context).addClass('viewsSlideshowSingleFrame-processed').each(function() {
    var fullId = '#' + $(this).attr('id');
    var settings = Drupal.settings.viewsSlideshowSingleFrame[fullId];
    settings.targetId = '#' + $(fullId + " :first").attr('id');

    $(settings.targetId).cycle({
      fx:settings.effect,
      speed:settings.speed,
      timeout:parseInt(settings.timeout),
      sync:settings.sync==1,
      random:settings.random==1,
      pause:settings.pause==1,
      prev:(settings.controls > 0)?'#views_slideshow_prev_' + settings.id:null,
      next:(settings.controls > 0)?'#views_slideshow_next_' + settings.id:null,
      pager:(settings.pager > 0)?'#views_slideshow_pager_' + settings.id:null,
      cleartype:(settings.cleartype),
      cleartypeNoBg:(settings.cleartypenobg)
    });
    
    if (settings.controls > 0) {
      $('#views_slideshow_playpause_' + settings.id).click(function(e) {
      	if (settings.paused) {
      	  $(settings.targetId).cycle('resume');
      	  $('#views_slideshow_playpause_' + settings.id).addClass('views_slideshow_pause').removeClass('views_slideshow_play').text('Pause');
      	  settings.paused = false;
      	}
      	else {
      	  $(settings.targetId).cycle('pause');
      	  $('#views_slideshow_playpause_' + settings.id).addClass('views_slideshow_play').removeClass('views_slideshow_pause').text('Resume');
      	  settings.paused = true;
      	}
        e.preventDefault();
      });
    }
  });
}
