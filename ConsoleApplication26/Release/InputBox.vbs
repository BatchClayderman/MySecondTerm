strings = inputbox("����ʾ����"&vbCrLf&">> �����A ��RG9957 11:40����A 1 5��"&vbCrLf&">> �뿪������RYH068 17:35����D 1 15��"&vbCrLf&">> ������E 0 0��������ȡ������"&vbCrLf&""&vbCrLf&"�������¼���","ͣ��������̨","A ��RG9957 11:40")
if (not strings<>false) Then
strings = "E 0 0"
End if
Set fso = CreateObject("Scripting.FileSystemObject")
Set f = fso.CreateTextFile("E:\�ҵ��ĵ�\ѧϰ\���ϴ�ѧ\ѧ���ļ�\�ڶ�ѧ��\���ݽṹ\C����\ConsoleApplication26\Release\InputBox.txt",True)
f.write strings
f.close