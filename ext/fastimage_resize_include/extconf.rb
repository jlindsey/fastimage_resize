require 'mkmf'
if find_library('gd', 'gdImageCreateFromJpeg')
  create_makefile('fastimage_resize_include')
else
  puts "Unable to find libgd"
end
