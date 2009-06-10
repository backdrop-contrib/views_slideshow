// $Id$

/**
 *  @file
 *  A simple jQuery ThumbnailHover Div Slideshow Rotator.
 */

/**
 *  This will set our initial behavior, by starting up each individual slideshow.
 */
Drupal.behaviors.viewsSlideshowThumbnailHover = function (context) {
  $('.views_slideshow_main:not(.viewsSlideshowThumbnailHover-processed)', context).addClass('viewsSlideshowThumbnailHover-processed').each(function() {
    var fullId = '#' + $(this).attr('id');

    // Make sure we're working from
    Drupal.settings.viewsSlideshowThumbnailHover[fullId]._current_div = Drupal.settings.viewsSlideshowThumbnailHover[fullId]._current_div ? Drupal.settings.viewsSlideshowThumbnailHover[fullId]._current_div : 0;

    var settings = Drupal.settings.viewsSlideshowThumbnailHover[fullId];

    // If we only have a single div, then we have nothing to do.
    // Thus, only turn on our slideshow if we have more than one slide.
    if (settings.num_divs > 1) {
      // This turns on the timer.
      views_slideshow_timer(fullId, true);

      // This sets up the mouseover & mouseout to pause on the main element.
      $(fullId).hover(
        function() {
          views_slideshow_pause(fullId);
        },
        function() {
          views_slideshow_resume(fullId);
        }
      );
    }
  });
}

/**
 *  Set the timer on or off.
 */
function views_slideshow_timer(slideshow_main, slideshow_status) {
  // Stop the current timer.
  clearTimeout(Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main]._timer_id);

  // Start a new timer, if slideshow_status is true, unless we're currently paused.
  if (slideshow_status && !Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main]._pause) { // !slideshow_data[slideshow_main]._pause) {
    // Our timer will call views_slideshow_switch, which fades out the current slide.
    Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main]._timer_id = setTimeout("views_slideshow_switch('" + slideshow_main + "', views_slideshow_next_div('" + slideshow_main + "'))", Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].timer_delay);
  }
}

function views_slideshow_pause(slideshow_main) {
  Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main]._pause = true;
  views_slideshow_timer(slideshow_main, false);
}

function views_slideshow_resume(slideshow_main) {
  Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main]._pause = false;
  views_slideshow_timer(slideshow_main, true);
}

/**
 *  Fade out to the new div indicated.
 */
function views_slideshow_switch(slideshow_main, new_div) {
  // Turn off our timer.
  views_slideshow_timer(slideshow_main, false);

  // Check to see if we fade or not.
  if (Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].fade) {
    // Fade out -- at the end, switch to the next slide in the slideshow.
    $(slideshow_main).fadeTo(Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].fade_speed, Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].fade_value, function() { views_slideshow_set_div(slideshow_main, new_div); });
  }
  else {
    // If we don't have a fade, then just switch without fading.
    views_slideshow_set_div(slideshow_main, new_div);
  }
}

/**
 *  Set the main div html to the new node.
 *  We come here at the bottom of the fade.
 */
function views_slideshow_set_div(slideshow_main, new_div_number) {
  // If the new div is greater than length, wrap to the first.
  // If it's less than zero, wrap to the last.
  if (new_div_number >= Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].num_divs) {
    new_div_number = 0;
  }
  else if (new_div_number < 0) {
    new_div_number = Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].num_divs - 1;
  }

  // Grab the ID's for the two slides.
  _old_breakout = Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].div_prefix + Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].id + "_" + Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main]._current_div;
  _new_breakout = Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].div_prefix + Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].id + "_" + new_div_number;

  // Hide our old slide and display the new one.
  $(_old_breakout).hide();
  $(_new_breakout).show();

  // Set the current_div number to the new node.
  Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main]._current_div = new_div_number;

  // Check to see if we faded here or not.
  if (Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].fade) {
    // Fade in -- at the end, turn on our timer.
    $(slideshow_main).fadeTo(Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].fade_speed, 1, function() { views_slideshow_timer(slideshow_main, true); });
  }
  else {
    // If we don't have a fade, then just turn on our timer without fading.
    views_slideshow_timer(slideshow_main, true);
  }
}

/**
 *  Get the next node div in our sequence.
 */
function views_slideshow_next_div(slideshow_main) {
  if (Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].sort) {
    // Select the next div, in forward or reverse order.
    new_div_number = Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main]._current_div + Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].sort;
  }
  else {
    // Select a random div, but make sure we don't repeat ourselves, unless there's only one div.
    do {
      new_div_number = Math.floor(Math.random() * Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].num_divs);
    } while (Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].num_divs > 1 && (new_div_number == Drupal.settings.viewsSlideshowThumbnailHover[slideshow_main].num_divs - 1));
  }
  return new_div_number;
}

