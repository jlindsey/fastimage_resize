require 'mkmf'
if pkg_config('gdlib')
  create_makefile('fastimage_resize_include')
else
  puts "Unable to find libgd"
end
