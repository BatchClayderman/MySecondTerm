x = -1
On Error Resume Next
x = int(inputbox("请输入去往的楼层数：","InputBox","0"))
if err.number <> 0 Then
x = -1
End if
if x = vbEmpty Then
x = -1
End if
Set fso = CreateObject("Scripting.FileSystemObject")
Set f = fso.CreateTextFile("E:\我的文档\学习\暨南大学\学术文件\第二学期\数据结构\C程序\ConsoleApplication9\Debug\InputBox.txt",True)
f.write x
f.close 