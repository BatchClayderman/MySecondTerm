strings = inputbox("输入示例："&vbCrLf&">> 到达：（A 粤RG9957 11:40）或（A 1 5）"&vbCrLf&">> 离开：（粤RYH068 17:35）或（D 1 15）"&vbCrLf&">> 结束：E 0 0（或点击“取消”）"&vbCrLf&""&vbCrLf&"请输入事件：","停车场控制台","A 粤RG9957 11:40")
if (not strings<>false) Then
strings = "E 0 0"
End if
Set fso = CreateObject("Scripting.FileSystemObject")
Set f = fso.CreateTextFile("E:\我的文档\学习\暨南大学\学术文件\第二学期\数据结构\C程序\ConsoleApplication26\Release\InputBox.txt",True)
f.write strings
f.close