def addDigits(input)
  total = 0
  inputDigits = input.split(//)
  inputDigits.each { |x| total += x.to_i }
  $input = total.to_s
end

$input = STDIN.gets

while ($input.to_i > 10)
    addDigits($input)
end

puts $input