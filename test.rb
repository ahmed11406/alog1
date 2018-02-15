a=0
while a<10
  a += 1
	unless a == 4	
		print a+3 
		print" "
		else print "There's no 4 baby "
	end
end 
print"\n"
b=0
until b==10; b+=1 
  c = b+5
	print c ; print " "
end
hight = 5
case hight 
  when 5; print "\nit's safe to fly"
	else puts "\nDANGER DO NOT TAKE OFF"
end
x= "helllo"
case x
  when "helllo"; puts "\nyou're welcome dude"
  else puts "outta here"	
end
for i in 0..5
	i +=0.5
	puts i 
end 
def sum(t,m) 
	s =t+m
	return "\nthe sum of #{t} and #{m} is: #{s}" #interpolating variables into a string with ""
end
puts sum(3,5)

# lstrip removes the indent spaces while strip only removes the spaces at the beginning and at the ending
my_name= "    ahmed "; print my_name.strip.capitalize # removes the spaces in a string var and capitalize the 1st liter
my_name= my_name.strip; #to change the value of my name to an array of "ahmed" only without space so it contains 4 indexs
my_name[1]= "mm"; print my_name.strip #change the second liter to D note that the variable now is an array of liters 
weather= %Q{   It's good for your health  }; aaa = weather.sub! "good", "bad"; puts aaa.strip

weather=%Q{get out of here}; puts weather.strip; weather.lines do |change_inn_lines|
	change_inn_lines= weather.sub("out of") { "in" }
	puts change_inn_lines.strip.capitalize
end 
# by using blocks block_name{statements}: the block name is a name of a method that includes a yield command...
#...the block statemsnts will replace the yield command.
caution=%Q{      Watch your hands  }; puts caution.strip.capitalize  
caution.lines{line_change=caution.sub("hands") {"head"}
puts line_change.strip.capitalize}

("hellolololgg44".include? "44hhssss") ? a2="I'm happy" : a2="Come again plz" ; puts a2 # put the whole expression between bracts 
puts "Please Enter your name and age: "                                                  # to get evaluated as a whole exp.   
#namee, age= gets.strip, gets_to_i 
#print "your name is #{namee.capitalize} and you're #{age} old" 
#ARRAYS
array1=[1,"a",:three.upcase,"NOON".downcase,25]; puts array1.size; array2=%w{ hello great men }; puts array2[-2]#by nagative num.
puts array1[0,2]; puts array1[0..2]# by range 
puts array1.join(", ")# joins arrays elements together. 
arr3=[5,25,36,48,54,6554,6,0.5]
puts arr3.sort!.reverse!.sample(3)# random 3 nums as sample
puts "the new array3 has changed in order : #{arr3}"
puts arr3.push(3, 54854) #pushs 3, 54854 at the end of arrays
puts arr3.shift(5)#gives the first 5  elements 
puts "this is arr3 now :#{arr3}"
puts arr3.pop(2)
arr4=[5,2,3,1,8,9,7,4,10]; arr4.each{|elements| print elements}
print arr4.select{|num| num<9}
print arr4.reject { |num| num<8 }
arr4_multi_by5= arr4.map{|elem| elem * 5 }; print arr4_multi_by5
def test
   yield 5
   puts "You are in the method test"
   yield 100
end
test {|i| puts "You are in the block #{i}"}
#OBJECT ORIENTED PROGRAMMING
class Person #MUST START WITH CAPITAL, instances:name age job id
	@@no_of_Persons = 20 #class-specified var
	$name_of_depart = "personnel"#global variable
	attr_reader :name
	attr_reader :job
	attr_reader :id
  attr_reader :age 
	def initialize(name,age,job,id)
	if name.is_a? String ; @name = name.strip.capitalize; else @name=nil end 
	self.age = age # self.method_name is directing the flow of the programe to the age=(new_age) method.
	@job = job.strip.capitalize
	@id = id.strip.capitalize 
  end
	def name=(new_name) # we could have used attr_accssor for both setting and getting, but it in this case it will take whatever value passed into this object variable without any conditions.
		  @name= new_name if new_name >="a" and new_name<="z" # we dont use end because of IF is in the middle.
	end 
	def age=(new_age)
		@age ||= 18 #set a defult value = 18 for the first time when setting the first age"intializing it", or the first entity is false.
		if (new_age.is_a? Numeric and new_age <= 120 and new_age >= 18); @age= new_age
		 end # we use end because of if is in beginning.
	  #this if checks for the proper date type required for age instance and the limit of the age.
	end
end

person1=Person.new("ahmed","20","engineer","11D3568"); # person1 is now a defined object pertaining to the class: Person.
puts "\nHere's #{person1.name} information:\nAge: #{person1.age}\nJob: #{person1.job}\nID: #{person1.id}"
# because of age being 150 the value rigistered for person1.age will be the default value which is 18 years by default.
person1.name="Adel".downcase ; puts person1.name.strip.capitalize #can read it and write over it as we used getter and setter techniques
person1.age=121; puts person1.age # can read it and write over it as we used...for this instance(object) variable inside the class
puts person1.job # can only read it but not change it as we only set it 
puts $name_of_depart;

