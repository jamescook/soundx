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

Tested on Core i7 Macbook Pro (2014). Ruby 2.6.3
See the benchmark folder for yet another Ruby implementation.
```
Calculating -------------------------------------
My Ruby-only version    254.744k (± 5.1%) i/s -      3.811M in  15.003116s
              SoundX      6.474M (± 4.7%) i/s -     97.079M in  15.032826s
   Text::Soundex gem     91.562k (± 3.8%) i/s -      1.376M in  15.051172s
         Soundex gem     66.860k (± 7.3%) i/s -    999.939k in  15.039989s

Comparison:
              SoundX:  6473685.9 i/s
My Ruby-only version:   254743.6 i/s - 25.41x  slower
   Text::Soundex gem:    91562.5 i/s - 70.70x  slower
         Soundex gem:    66860.3 i/s - 96.82x  slower
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
