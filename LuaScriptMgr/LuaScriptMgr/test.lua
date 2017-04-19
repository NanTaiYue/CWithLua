
function Add(x, y)
	return x + y
end

local a = 10
local b = 20

print(Add(10,20))
print("hello,world!")
LogInfo("ÄãÃÇºÃ")
LogInfo(123456789)

function TellMe(num, str, str2)
	LogInfo(num)
	LogInfo(str)
	return num, str,str2;
end

function SayHello()
	print("SayHello")
end

local obj = Person.New()
print(obj:__tostring())

print(obj:get_name())
obj:set_name("zz")
print(obj:get_name())

print(obj:get_age())
obj:set_age(20)
print(obj:get_age())

print(obj:get_id())
obj:set_id(511119)
print(obj:get_id())

print(obj:get_sex())
obj:set_sex(2)
print(obj:get_sex())

print(obj:get_bornDay())
obj:set_bornDay("1993-07-05")
print(obj:get_bornDay())

print(obj:__tostring())

obj = nil