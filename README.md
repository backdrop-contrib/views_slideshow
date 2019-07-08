# Views Slideshow

This is a port to Backdrop of the Drupal contributed module 'Views Slideshow' v7.x-3.x

It provides an API module Views Slideshow and one implementation of
that API in a submodule Views Slideshow Cycle.

Views Slideshow Cycle can be used to create a slideshow of any content (not just images)
that can appear in a View. Powered by jQuery, it is heavily customizable: 
you may choose slideshow settings for each View you create.

For example, using the Views UI when extended by this module, a slideshow can be
created either from a set of images uploaded to a single node, or from a set of nodes
each having one image for inclusion in the slideshow.

The submodule now includes the jQuery Cycle library from http://malsup.com/jquery/cycle.

Other modules that can be installed separately to use this API are
+ Views Slideshow: Galleria
+ Views Slideshow: Cycle2

## Installation

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules.

- If upgrading from a previous release, the Libraries module is no longer required
by this module, nor is the separate copy of the jQuery Cycle library.

## Configuration

The module adds settings to the Views UI, providing a 'slideshow' view style that displays 
rows as a jQuery slideshow. 

The included submodule Views Slideshow Cycle provides an option 'Cycle' for the slideshow 
with various settings. Other slideshow options can be added by other contributed modules.

## License

This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.
    
    
## Current Maintainers

### For Drupal:
+ Nick Wilde (NickWilde)
+ Vincent Bouchet (vbouchet)
+ Adam Moore (redndahead)
+ Richard Burford (psynaptic)

### Port to Backdrop:
+ Graham Oliver github.com/Graham-72

## Acknowledgements

The original author was Aaron Winborn sponsored by Advomatic
Current supporters are DAVYIN Internet Solutions
