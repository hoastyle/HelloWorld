file = ARGV.first
prompt = '> '

txt = File.open(file)
puts "Here is your input file: #{file}"
puts txt.read()

puts "type the filename again"
print prompt
file = STDIN.gets.chomp()
txt = File.open(file)
puts txt.read()
