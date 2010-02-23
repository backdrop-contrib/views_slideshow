<?php
// $Id$

/**
 * @file
 * Views Slideshow: Thumbnail Hover template file.
 */
?>

<?php if ($options['thumbnailhover']['controls'] == 1): ?>
  <?php print $controls; ?>
<?php endif; ?>

<?php if ($options['thumbnailhover']['image_count'] == 1): ?>
  <?php print $image_count; ?>
<?php endif; ?>

<?php if (!$options['thumbnailhover']['teasers_last']): ?>
  <?php print $view_teasers; ?>
<?php endif; ?>

<?php print $slideshow; ?>

<?php if ($view_teasers && $options['thumbnailhover']['teasers_last']): ?>
  <?php print $view_teasers; ?>
<?php endif; ?>

<?php if ($options['thumbnailhover']['controls'] == 2): ?>
  <?php print $controls; ?>
<?php endif; ?>

<?php if ($options['thumbnailhover']['image_count'] == 2): ?>
  <?php print $image_count; ?>
<?php endif; ?>
