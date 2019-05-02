# Soundex Library

---

SoundX is a Ruby native extension that implements the Soundex algorithm

### Usage
```ruby
require 'soundx'
irb: SoundX.encode('Robert')
=> R163

irb: SoundX.encode('Rupert')
=> R163
```

### Benchmark

Tested on Core i7 Macbook Pro (2014). Ruby 2.5.3
See the benchmark folder for yet another Ruby implementation.
```
Calculating -------------------------------------
My Ruby-only version    259.275k (± 5.2%) i/s -      3.899M in  15.089488s
              SoundX      3.567M (± 4.9%) i/s -     53.464M in  15.026927s
   Text::Soundex gem    100.191k (± 4.5%) i/s -      1.507M in  15.075963s
         Soundex gem     75.599k (± 4.0%) i/s -      1.133M in  15.009973s

Comparison:
              SoundX:  3566961.2 i/s
My Ruby-only version:   259274.6 i/s - 13.76x  slower
   Text::Soundex gem:   100190.9 i/s - 35.60x  slower
         Soundex gem:    75598.6 i/s - 47.18x  slower
```

### Requirements
* Ruby 2.1+
* gcc/clang

### Developing

Simply make your changes and re-run the tests. Compilation is automatic.
```
rake test
```

### License

MIT
