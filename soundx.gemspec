require_relative "./lib/soundx/version"

Gem::Specification.new do |s|
  s.name    = "soundx"
  s.version = SoundX::VERSION
  s.summary = "Soundex library written in C"
  s.author  = "James Cook"
  s.platform = Gem::Platform::RUBY
  s.homepage = "https://github.com/jamescook/soundx"

  s.files = Dir.glob("ext/**/*.{c,h,rb}") +
            Dir.glob("lib/**/*.{rb}")

  s.extensions << "ext/soundx/extconf.rb"
  s.licenses << "MIT"

  s.add_development_dependency "rake-compiler", "~> 1"
  s.add_development_dependency "minitest-line", "~> 0.6"
  s.add_development_dependency "minitest", "~> 5.11"
  s.required_ruby_version = '> 2.1'
end
