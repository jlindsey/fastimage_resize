require "bundler/gem_tasks"
require 'rake/clean'
require 'rake/extensiontask'
require 'rake/testtask'

CLEAN.include 'ext/**/*.{o,log,bundle,so}'
CLEAN.include 'ext/**/Makefile'
CLEAN.include 'ext/**/.RUBYARCHDIR.time'
CLEAN.include 'lib/**/*.{bundle,so}'

Rake::ExtensionTask.new('fastimage_resize_include') do |ext|
  ext.lib_dir = 'lib'
end

Rake::TestTask.new do |t|
  t.libs << 'test'
  t.test_files = FileList['test/test*.rb']
  t.verbose = true
end
task :test => [:clean, :compile]
