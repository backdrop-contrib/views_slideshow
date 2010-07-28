<?php
// $Id$

/**
 * @file
 * Views Slideshow: Single Frame template file.
 */
?>

<?php if ($controls_location == 'top' || $pager_location == 'top' || $slide_counter_location == 'top'): ?>
  <div class="views-slideshow-controls-top clear-block">
    <?php if ($slide_counter_location == 'top') { ?>
      <?php print $slide_counter; ?>
    <?php } ?>
    
    <?php if ($controls_location == 'top') { ?>
      <?php print $controls; ?>
    <?php } ?>
    
    <?php if ($pager_location == 'top') { ?>
      <?php print $pager; ?>
    <?php } ?>
  </div>
<?php endif; ?>

<?php print $slideshow; ?>

<?php if ($controls_location == 'bottom' || $pager_location == 'bottom' || $slide_counter_location == 'bottom'): ?>
  <div class="views-slideshow-controls-bottom clear-block">
    <?php if ($pager_location == 'bottom') { ?>
      <?php print $pager; ?>
    <?php } ?>
    
    <?php if ($controls_location == 'bottom') { ?>
      <?php print $controls; ?>
    <?php } ?>
    
    <?php if ($slide_counter_location == 'bottom') { ?>
      <?php print $slide_counter; ?>
    <?php } ?>
  </div>
<?php endif; ?>
