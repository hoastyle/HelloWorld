# 1
module FirstModule
  def self.function
	"say hello"
  end
end

puts FirstModule.function

# 2
module FirstModule
  def function
	"say hello"
  end
end

include FirstModule

puts FirstModule.function
