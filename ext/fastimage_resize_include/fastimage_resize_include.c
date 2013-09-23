#include <ruby.h>
#include <gd.h>

static VALUE fir_resize_image(VALUE self, VALUE raw_filename_in, VALUE raw_filename_out, VALUE raw_width, VALUE raw_height, VALUE raw_image_type, VALUE raw_jpeg_quality) {
  gdImagePtr im_in, im_out;
  FILE *in, *out;
  char *filename_in; char *filename_out;
  int w; int h; int image_type; int jpeg_quality;
  int trans = 0, x = 0, y = 0, f = 0;

  filename_in = RSTRING_PTR(raw_filename_in);
  filename_out = RSTRING_PTR(raw_filename_out);
  w = NUM2INT(raw_width);
  h = NUM2INT(raw_height);
  image_type = NUM2INT(raw_image_type);
  jpeg_quality = NUM2INT(raw_jpeg_quality);

  in = fopen(filename_in, "rb");
  if (!in) return Qnil;

  switch(image_type) {
    case 0: im_in = gdImageCreateFromJpeg(in);
            break;
    case 1: im_in = gdImageCreateFromPng(in);
            break;
    case 2: im_in = gdImageCreateFromGif(in);
            trans = gdImageGetTransparent(im_in);
            /* find a transparent pixel, then turn off transparency
               so that it copies correctly */
            if (trans >= 0) {
              for (x=0; x<gdImageSX(im_in); x++) {
                for (y=0; y<gdImageSY(im_in); y++) {
                  if (gdImageGetPixel(im_in, x, y) == trans) {
                    f = 1;
                    break;
                  }
                }
                if (f) break;
              }
              gdImageColorTransparent(im_in, -1);
              if (!f) trans = -1;  /* no transparent pixel found */
            }
            break;
    default: return Qnil;
  }

  if (w == 0 || h == 0) {
    int originalWidth  = gdImageSX(im_in);
    int originalHeight = gdImageSY(im_in);
    if (w == 0) {
      w = (int)(h * originalWidth / originalHeight);
    } else {
      h = (int)(w * originalHeight / originalWidth);
    }
  }

  im_out = gdImageCreateTrueColor(w, h);  /* must be truecolor */

  if (image_type == 1) {
    gdImageAlphaBlending(im_out, 0);  /* handle transparency correctly */
    gdImageSaveAlpha(im_out, 1);
  }
  
  fclose(in);
  
  /* Now copy the original */
  gdImageCopyResampled(im_out, im_in, 0, 0, 0, 0,
    gdImageSX(im_out), gdImageSY(im_out),
    gdImageSX(im_in), gdImageSY(im_in));

  out = fopen(filename_out, "wb");
  if (out) {
    switch(image_type) {
      case 0: gdImageJpeg(im_out, out, jpeg_quality);
              break;
      case 1: gdImagePng(im_out, out);
              break;
      case 2: gdImageTrueColorToPalette(im_out, 0, 256);
              if (trans >= 0) {
                trans = gdImageGetPixel(im_out, x, y);  /* get the color index of our transparent pixel */
                gdImageColorTransparent(im_out, trans); /* may not always work as hoped */
              }
              gdImageGif(im_out, out);
              break;
    }
    fclose(out);
  }
  gdImageDestroy(im_in);
  gdImageDestroy(im_out);
  return Qnil;
}

void Init_fastimage_resize_include(void) {
  VALUE mFastImageResizeInclude = rb_define_module("FastImageResizeInclude");
  rb_define_method(mFastImageResizeInclude, "resize_image", fir_resize_image, 6);
}
