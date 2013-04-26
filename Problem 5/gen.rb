n = (rand() * 100).to_i
out = ""

puts n

n.times do |x|
    out = "#{out}#{(rand() * 100).to_i}"
    if x < n
        out  = "#{out} "
    end
end

puts out
