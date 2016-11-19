# Views Slideshow

This is a port to Backdrop of the Drupal contributed module 'Views Slideshow'. 

Views Slideshow can be used to create a slideshow of any content (not just images)
that can appear in a View. Powered by jQuery, it is heavily customizable: 
you may choose slideshow settings for each View you create.

This module contains an api module "Views Slideshow" and one implementation of
that api in "Views Slideshow Cycle".

It requires the Libraries API module to be installed, together with the
jQuery cycle library. http://malsup.com/jquery/cycle; also for advanced features
the json2.js library, see http://javascript.crockford.com/jsmin.html


## Status
This port is working with the jQuery cycle library. It has not been
tested with the json2 library. 
In release 1.x-3.1.1 an issue with the pager widget has been corrected 
and classes have been added to provide responsive images.

## Installation

Install as usual, then add the required javascript libraries to their own directories 
jquery.cycle and (optionally) json2 within the site's libraries folder.

## License

This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.
    
    
## Current Maintainers

### For Drupal:
+ zhou xiukun (xiukun.zhou)
+ wangqizhong
+ Adam Moore (redndahead)
+ Richard Burford (psynaptic)

### Port to Backdrop:
+ Graham Oliver github.com/Graham-72

## Acknowledgements

The original author was Aaron Winborn sponsored by Advomatic
Current supporters are DAVYIN Internet Solutions
