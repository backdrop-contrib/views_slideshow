<?php
// $Id$

/**
 * @file
 * Views Slideshow: Thumbnail Hover template file.
 */
?>

<?php if ($controls_top || $image_count_top || $teasers_top): ?>
  <div class="views-slideshow-controls-top clear-block">
    <?php print $controls_top; ?>
    <?php print $pager_top; ?>
    <?php print $teasers_top; ?>
  </div>
<?php endif; ?>

<?php print $slideshow; ?>

<?php if ($teasers_bottom || $controls_bottom || $image_count_bottom): ?>
  <div class="views-slideshow-controls-bottom clear-block">
    <?php print $teasers_bottom; ?>
    <?php print $controls_bottom; ?>
    <?php print $image_count_bottom; ?>
  </div>
<?php endif; ?>
