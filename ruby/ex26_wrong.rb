module Ex2

  # This function will break up words for us.
  # missing parenthesis
  def self.break_words(stuff)
    words = stuff.split(' ')
  # wrong var
    return words
  end

  # Sorts the words.
  # incorrect function name, missing underscore
  def self.sort_words(words)
    return words.sort
  end

  # Prints the first word after popping it off.
  # incorrect key word def
  def self.print_first_word(words)
    word = words.pop(1)
  # incorrect var wor
    puts word
  end

  # Prints the last word after popping it off.
  def self.print_last_word(words)
    word = words.pop
    puts word
  end

  # Takes in a full sentence and returns the sorted words.
  def self.sort_sentence(sentence)
    words = break_words(sentence)
    return sort_words(words)
  # incorrect key word
  end

  # Prints the first and last words of the sentence.
  # missing parenthesis
  def self.print_first_and_last(sentence)
  # incorrect var sentenc
    words = break_words(sentence)
  # wrong function name print_first_wrd and var word
    print_first_word(words)
    print_last_word(words)
  end

  # Sorts the words then prints the first and last one.
  def self.print_first_and_last_sorted(sentence)
    words = sort_sentence(sentence)
  # incorrect function name print_first_word
    print_first_word(words)
    print_last_word(words)
  end
end

include(Ex2)

puts "Let's practice everything."
puts 'You\'d need to know \'bout escapes with \\ that do \n newlines and \t tabs.'

poem = <<END
\tThe lovely world
with logic so firmly planted
cannot discern \n the needs of love
nor comprehend passion from intuition
and requires an explanation
\n\t\twhere there is none.
# wrong key word ENDED
END

puts "--------------"
puts poem
puts "--------------"


five = 10 - 2 + 3 - 6
# missing close brace
puts "This should be five: #{five}"

def secret_formula(started)
  jelly_beans = started * 500
  jars = jelly_beans / 1000
  # incorrect var name crate
  crates = jars / 100
  return jelly_beans, jars, crates
end


start_point = 10000
beans, jars, crates = secret_formula(start_point)

puts "With a starting point of: #{start_point}"
puts "We'd have #{beans} beans, #{jars} jars, and #{crates} crates."

start_point = start_point / 10

sentence = "All good things come to those who wait."
words = break_words(sentence)
sorted_words = sort_words(words)
print_first_word(wrds)
print_last_word(words)
print_first_word(sorted_words)
print_last_word(sorted_words)
sorted_words = sort_sentence(sentence)
print_first_and_last(sentence)
print_first_and_last_sorted(sentence)
