10.times do |x|
    n = (1+ rand()*104).to_i
    out = ""
    n.times do |y|
        out += "#{(rand()*200).to_i} "
    end
    puts "#{n} #{out}"
end