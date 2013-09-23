# -*- encoding: utf-8 -*-
require 'rake'

Gem::Specification.new do |s|
  s.name = %q{fastimage_resize}
  s.version = "2.0.4"

  s.authors = ["Stephen Sykes"]
  s.description = %q{FastImage Resize is an extremely light solution for resizing images in ruby by using libgd.}
  s.email = %q{sdsykes@gmail.com}
  s.extra_rdoc_files = [
    "README",
     "README.textile"
  ]
  s.files = FileList['lib/**/*', 'ext/**/*.{c,h,rb}']
  s.homepage = %q{http://github.com/sdsykes/fastimage_resize}
  s.require_paths = ["lib"]
  s.extensions    = FileList['ext/**/extconf.rb']
  s.requirements = ["libgd, see www.libgd.org"]
  s.summary = %q{FastImage Resize - Image resizing fast and simple}
  s.test_files = [
    "test/test.rb"
  ]

  s.add_runtime_dependency 'fastimage', '~> 1.2.9'
  
  s.add_development_dependency "pry"
  s.add_development_dependency "rake-compiler"
  s.add_development_dependency "fakeweb"
end

