x = 0
On Error Resume Next
x = int(inputbox("请输入一个整型元素：","InputBox","0"))
if err.number <> 0 Then
x = 0
End if
Set fso = CreateObject("Scripting.FileSystemObject")
Set f = fso.CreateTextFile("E:\我的文档\学习\暨南大学\学术文件\第二学期\数据结构\C程序\ConsoleApplication25\Release\InputBox.txt",True)
f.write x
f.close 