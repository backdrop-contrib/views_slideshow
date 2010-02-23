<?php
// $Id$

/**
 * @file
 * Views Slideshow: Single Frame template file.
 */
?>

<?php if ($options['singleframe']['controls'] == 1): ?>
  <?php print $controls; ?>
<?php endif; ?>

<?php if ($options['singleframe']['pager'] == 1): ?>
  <?php print $pager; ?>
<?php endif; ?>

<?php if ($options['singleframe']['image_count'] == 1): ?>
  <?php print $image_count; ?>
<?php endif; ?>

<?php print $slideshow; ?>

<?php if ($options['singleframe']['controls'] == 2): ?>
  <?php print $controls; ?>
<?php endif; ?>

<?php if ($options['singleframe']['pager'] == 2): ?>
  <?php print $pager; ?>
<?php endif; ?>

<?php if ($options['singleframe']['image_count'] == 2): ?>
  <?php print $image_count; ?>
<?php endif; ?>
