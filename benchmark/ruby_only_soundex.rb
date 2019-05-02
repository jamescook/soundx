# Just for fun, let's write a pure-ruby version to see
# how it stacks up.
 
class RubyOnlySoundex
=begin
b, f, p, v → 1
c, g, j, k, q, s, x, z → 2
d, t → 3
l → 4
m, n → 5
r → 6
=end

  MAPPING = {
    "a"=>nil,   "b"=>1,  "c"=>2,  "d"=>3, "e"=>nil,
    "f"=>nil, "g"=>2, "h"=>nil, "i"=>nil,
    "j"=>2, "k"=>2, "l"=>4, "m"=>5,
    "n"=>5, "o"=>nil, "p"=>1,   "q"=>2,
    "r"=>6, "s"=>2, "t"=>3, "u"=>nil,
    "v"=>1, "w"=>nil, "x"=>2, "y"=>nil, "z"=>2
  }.freeze

  def self.soundex(string)

    i, w = 0, 1
    copy = string.dup
    output = "#{copy[0].upcase}000"
    copy.downcase!

    copy.each_char do |chr|
      if i == 0
        i = i + 1
        next
      end

      break if w == 4

      key = MAPPING[chr]

      if key.nil?
        next
      end

      # Skip vowels & 
      # no duplicate digits
      if key == nil || key == chr[w-1]
        i = i + 1
      else
        output[w] = key.to_s
        i = i + 1
        w = w + 1
      end

    end

    output
  end
end
