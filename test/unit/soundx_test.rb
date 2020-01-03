require_relative "../../lib/soundx"
require "minitest/autorun"

describe 'SoundX' do
  describe ".encode with no arguments" do
    it "returns an argument error" do
      assert_raises ArgumentError do
        SoundX.encode
      end
    end
  end

  describe ".encode given a non-string" do
    it "returns a type error" do
      assert_raises TypeError do
        SoundX.encode(-1)
      end
    end
  end

  describe ".encode given non-ascii" do
    it "returns an argument error" do
      assert_raises ArgumentError do
        SoundX.encode 'ølga'
      end

      assert_raises ArgumentError do
        SoundX.encode 128.chr
      end
    end
  end

  describe ".encode given the asciii string 'Ashcraft'" do
    it "returns the correct soundex" do
      assert_equal 'A261', SoundX.encode('Ashcraft')
    end
  end

  describe ".encode given the asciii string 'Ashcroft'" do
    it "returns the correct soundex" do
      assert_equal 'A261', SoundX.encode('Ashcroft')
    end
  end

  describe ".encode given the asciii string 'Rubin'" do
    it "returns the correct soundex" do
      assert_equal 'R150', SoundX.encode('Rubin')
    end
  end

  describe ".encode given the asciii string 'robert'" do
    it "returns the correct soundex" do
      assert_equal 'R163', SoundX.encode('robert')
    end
  end

  describe ".encode given the asciii string 'rupert'" do
    it "returns the correct soundex" do
      assert_equal 'R163', SoundX.encode('rupert')
    end
  end

  describe ".encode given the ascii string 'Tymczak'" do
    it "returns the correct soundex" do
      assert_equal 'T520', SoundX.encode('Tymczak')
    end
  end

  describe ".encode given the ascii string 'Lukasiewicz'" do
    it "returns the correct soundex" do
      assert_equal 'L200', SoundX.encode('Lukasiewicz')
    end
  end

  describe ".encode given the ascii string 'Schwarzenegger'" do
    it "returns the correct soundex" do
      assert_equal 'S625', SoundX.encode('Schwarzenegger')
    end
  end

  describe ".encode given the ascii string 'Shwarzenegger'" do
    it "returns the correct soundex" do
      assert_equal 'S625', SoundX.encode('Shwarzenegger')
    end
  end
end
