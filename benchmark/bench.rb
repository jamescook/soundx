#!/usr/bin/env ruby
require 'benchmark/ips'
require 'text'
require 'soundex'
require_relative '../lib/soundx'
require_relative '../benchmark/ruby_only_soundex'


str = "Samuel"
fail unless (SoundX.encode(str) == Text::Soundex.soundex(str) && SoundX.encode(str) == Soundex.new(str).soundex)
fail unless (SoundX.encode(str) == RubyOnlySoundex.soundex(str))

Benchmark.ips do |b|
  b.time = 15
  b.report("My Ruby-only version") { RubyOnlySoundex.soundex(str) }
  b.report("SoundX") { SoundX.encode(str) }
  b.report("Text::Soundex gem") { Text::Soundex.soundex(str) }
  b.report("Soundex gem") { Soundex.new(str) }
  b.compare!
end

# Test a short string
str = "Bo"
fail unless (SoundX.encode(str) == Text::Soundex.soundex(str) && SoundX.encode(str) == Soundex.new(str).soundex)

Benchmark.ips do |b|
  b.time = 15
  b.report("My Ruby-only version short") { RubyOnlySoundex.soundex(str) }
  b.report("SoundX short") { SoundX.encode(str) }
  b.report("Text::Soundex gem short") { Text::Soundex.soundex(str) }
  b.report("Soundex gem short") { Soundex.new(str) }
  b.compare!
end
