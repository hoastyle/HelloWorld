Record

print
	string and varible
	同时打印string and varible呢？多个输出，用符号,隔开

字符类型
	整数
	浮点值
	布尔值
	字符串，引号双引号都可以

type()

序列
	元组，()，不可改变
	列表，[]，可改变
序列元素的引用，通过[x, y, z]，x开始，y结束，z步长，从0开始，:符号的使用

词典，无序键值对
	{}，

字符串是特殊的元组，所以可以使用元组的操作

# 运算
## 数学运算
+, -, *, /, %, **
%求余，**乘方

## 判断(关系)
=, <, <=, >, >=

## 逻辑运算
and, or, not

python的格式
:和4个空格

循环
	for
	while
	循环中断, continue, break
	range()

函数，函数的定义def, 参数(),返回值return
可以返回多个返回值，相当于return (x, y, z)

类，类别，class
class的具体表现，object
object, 其中属性和方法
子类
self表示类的对象

特殊方法，以“__”开头和结尾
__init__()

dir(), help(), len()

# 模块
## 模块的引入 && 调用模块中的定义
* import: import module_name, call: module_name.function
* import a as b: rename module a to b
* from a import function, call: function
* from a import *: import all object in a

## 模块搜索路径
* 当前文件夹
* 标准库的安装路径
* 操作系统环境变量PYTHONPATH

## 模块包
文件夹中添加__init__.py表示该目录为模块包，可以为空

模块包的使用: import dir.module_name

# 函数参数

