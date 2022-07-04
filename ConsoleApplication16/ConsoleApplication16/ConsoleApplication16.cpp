#include <iostream>
#include <Windows.h>
#include <tchar.h>
#define SizeMax 300
#define SizeMin 0
#define NotValid -1
#define SubjectsNum 9
#define SubjectCount ESubject::Data
using namespace std;

enum class ESubject//定义枚举型
{
	MathA,//数学分析成绩
	MathB,//数学基础成绩
	English,//英语成绩
	PE,//体育成绩
	theory,//网络空间安全导论成绩
	web,//web成绩
	Thoughts,//思修成绩
	instance,//案例分析成绩
	Data,//数据结构成绩
};

struct FNode
{
	string Name;
	int ID = -1;
	double Score[SubjectsNum + 1] = { 0 };
	double GetScore(ESubject Subject)
	{
		if (Subject > SubjectCount)
			return 0;
		else if (Score[int(Subject)] < 0|| Score[int(Subject)] > 100)
			return 0;
		else
			return Score[int(Subject)];
	}
	void SetScore(ESubject Subject, double NewScore)
	{
		if (Subject > SubjectCount)
			return;
		else if (NewScore < 0 || NewScore > 100)
			Score[int(Subject)] = 0;
		else
			Score[int(Subject)] = NewScore;
	}
};

struct FNodeArray
{
private:
	FNode Array[SizeMax];
	int Size = 0;
protected:
	virtual bool RemoveArrayItem(int ID)//删
	{
		for (int i = 0; i < Size; i++)
		{
			if (Array[i].ID == ID)
			{
				Size = Size - 1;
				if (Size < SizeMin)
					return false;
				for (; i < Size; i++)
					Array[i] = Array[i + 1];
				return true;
			}
		}
		return false;
	}
	virtual bool SetArrayItem(int ID, FNode NodeArray)//改
	{
		for (int i = 0; i < Size; i++)
		{
			if (Array[i].ID == ID)
			{
				Array[i] = NodeArray;
				return true;
			}
		}
		return false;
	}
	virtual FNode FindArrayItem(int ID)//查
	{
		for (int i = 0; i < Size; i++)
			if (Array[i].ID == ID)
				return Array[i];
		return FNode();
	}
	virtual bool AddArrayItem(FNode NodeArray)//增
	{
		if (FindArrayItem(NodeArray.ID).ID != NotValid)
		{
			return false;
		}
		if (Size < SizeMax)
		{
			Array[Size] = NodeArray;
			Size = Size++;
			return true;
		}
		return false;
	}

public:
	bool IsValid(int ID)//判断 ID 是否合法
	{
		FNode Node_rn = FindArrayItem(ID);
		if (Node_rn.ID == NotValid)
			return false;
		else
			return true;
	}
	double FindStudents(int ID, ESubject Subject)//遍历所有学生信息
	{
		if (IsValid(ID) == false)
			return false;
		FNode Node = FindStudentData(ID);
		return Node.GetScore(Subject);
	}
	bool ChangeScore(int ID, ESubject Subject, double NewScore)//修改学生成绩
	{
		if (IsValid(ID) == false)
			return false;
		FNode Node = FindStudentData(ID);
		Node.SetScore(Subject, NewScore);
		return SetArrayItem(ID, Node);
	}
	FNode FindStudentData(int ID)//查找学生信息
	{
		return FindArrayItem(ID);
	}
	bool ChangeStudentData(int ID, FNode NewData)//修改学生信息
	{
		return SetArrayItem(ID, NewData);
	}
	bool DeleteStudentData(int ID)//删除学生信息
	{
		return RemoveArrayItem(ID);
	}
	bool AddStudentData(FNode NewData)//添加学生信息
	{
		return AddArrayItem(NewData);
	}
	int GetSize()//获取学生数目
	{
		return Size;
	}
	double CalcScore(ESubject subject)//计算某个科目的平均成绩
	{
		FNode Node;
		int i = 0, j = 0;
		double s = 0;
		for (i = 0; i < GetSize(); i++)
		{
			Node = FindStudentData(i);
			s += (Node.GetScore(subject) == 0 ? 0 : Node.GetScore(subject));
			j += (Node.GetScore(subject) == 0 ? 0 : 1);
		}
		return j ? s / j : 0;
	}
	FNode GetArrayNode(int Index)//返回完全的一张数据表
	{
		if (Index < Size)
			return Array[Index];
		else
			return FNode();
	}
};

FNodeArray NodeArray;

enum class EInterfaceType//枚举操作
{
	Main,
	Add,
	Del,
	Change,
	Find,
	ChangeScore,
	FindStudents,
	ShowAll,
	ForTeahcer,
	SearchKey,
	Break,
};

string CmdStr;

void ShowData(FNode ShowNode)//显示某学生的所有成绩
{
	double s = 0, n = 0;
	cout << ">> 学号：" << ShowNode.ID << "\n";
	cout << ">> 姓名：" << ShowNode.Name << "\n";
	cout << ">> 数学分析成绩：" << ShowNode.GetScore(ESubject::MathA) << "\n";
	s += (ShowNode.GetScore(ESubject::MathA) == 0 ? 0 : ShowNode.GetScore(ESubject::MathA));
	n += (ShowNode.GetScore(ESubject::MathA) == 0 ? 0 : 1);
	cout << ">> 数学基础成绩：" << ShowNode.GetScore(ESubject::MathB) << "\n";
	s += (ShowNode.GetScore(ESubject::MathB) == 0 ? 0 : ShowNode.GetScore(ESubject::MathB));
	n += (ShowNode.GetScore(ESubject::MathB) == 0 ? 0 : 1);
	cout << ">> 英语成绩：" << ShowNode.GetScore(ESubject::English) << "\n";
	s += (ShowNode.GetScore(ESubject::English) == 0 ? 0 : ShowNode.GetScore(ESubject::English));
	n += (ShowNode.GetScore(ESubject::English) == 0 ? 0 : 1);
	cout << ">> 体育成绩：" << ShowNode.GetScore(ESubject::PE) << "\n";
	s += (ShowNode.GetScore(ESubject::PE) == 0 ? 0 : ShowNode.GetScore(ESubject::PE));
	n += (ShowNode.GetScore(ESubject::PE) == 0 ? 0 : 1);
	cout << ">> 网络空间安全导论成绩：" << ShowNode.GetScore(ESubject::theory) << "\n";
	s += (ShowNode.GetScore(ESubject::theory) == 0 ? 0 : ShowNode.GetScore(ESubject::theory));
	n += (ShowNode.GetScore(ESubject::theory) == 0 ? 0 : 1);
	cout << ">> web 成绩：" << ShowNode.GetScore(ESubject::web) << "\n";
	s += (ShowNode.GetScore(ESubject::web) == 0 ? 0 : ShowNode.GetScore(ESubject::web));
	n += (ShowNode.GetScore(ESubject::web) == 0 ? 0 : 1);
	cout << ">> 思修成绩：" << ShowNode.GetScore(ESubject::Thoughts) << "\n";
	s += (ShowNode.GetScore(ESubject::Thoughts) == 0 ? 0 : ShowNode.GetScore(ESubject::Thoughts));
	n += (ShowNode.GetScore(ESubject::Thoughts) == 0 ? 0 : 1);
	cout << ">> 案例分析成绩：" << ShowNode.GetScore(ESubject::instance) << "\n";
	s += (ShowNode.GetScore(ESubject::instance) == 0 ? 0 : ShowNode.GetScore(ESubject::instance));
	n += (ShowNode.GetScore(ESubject::instance) == 0 ? 0 : 1);
	cout << ">> 数据结构成绩：" << ShowNode.GetScore(ESubject::Data) << "\n";
	s += (ShowNode.GetScore(ESubject::Data) == 0 ? 0 : ShowNode.GetScore(ESubject::Data));
	n += (ShowNode.GetScore(ESubject::Data) == 0 ? 0 : 1);
	if (n == 0)
		s = 0;
	else
		s /= n;
	cout << ">> 算术平均成绩：" << s << endl;
	cout << endl << endl;
}

EInterfaceType Interface(EInterfaceType Cmd)//提供伪 UI 界面
{
	int CmdBf;
	FNode NewNode;
	switch (Cmd)
	{
	case EInterfaceType::Main://主面板
		cout << "\t学生成绩管理系统" << endl << endl;
		cout << "————————————————" << endl;
		cout << ">> 0 = 添加学生信息" << endl;
		cout << ">> 1 = 删除学生信息" << endl;
		cout << ">> 2 = 修改学生信息" << endl;
		cout << ">> 3 = 查询学生信息" << endl;
		cout << ">> 4 = 修改学生成绩" << endl;
		cout << ">> 5 = 列举所有学生" << endl;
		cout << ">> 6 = 显示所有信息" << endl;
		cout << ">> 7 = 科目平均成绩" << endl;
		cout << ">> 8 = 关键字词查找" << endl;
		cout << ">> 9 = 退出管理系统" << endl;
		cout << "————————————————" << endl << endl << endl;
		cout << "请选择一项以继续：";
		rewind(stdin);
		cin >> CmdStr;
		rewind(stdin);
		CmdBf = atoi(CmdStr.data()) + 1;
		return (EInterfaceType)CmdBf;
	case EInterfaceType::Add://添加学生信息
		cout << "\t学生信息添加界面" << endl;
		cout << "————————————————" << endl;
		cout << endl;

		cout << "请输入学号：";
		rewind(stdin);
		cin >> CmdStr;
		NewNode.ID = atoi(CmdStr.data());

		cout << "请输入学生姓名：";
		rewind(stdin);
		cin >> CmdStr;
		NewNode.Name = CmdStr;

		cout << "请输入学生数学分析成绩：";
		rewind(stdin);
		cin >> CmdStr;
		NewNode.SetScore(ESubject::MathA, atof(CmdStr.data()));

		cout << "请输入学生数学基础成绩：";
		rewind(stdin);
		cin >> CmdStr;
		NewNode.SetScore(ESubject::MathB, atof(CmdStr.data()));

		cout << "请输入学生英语成绩：";
		rewind(stdin);
		cin >> CmdStr;
		NewNode.SetScore(ESubject::English, atof(CmdStr.data()));

		cout << "请输入学生体育成绩：";
		rewind(stdin);
		cin >> CmdStr;
		NewNode.SetScore(ESubject::PE, atof(CmdStr.data()));

		cout << "请输入学生导论成绩：";
		rewind(stdin);
		cin >> CmdStr;
		NewNode.SetScore(ESubject::theory, atof(CmdStr.data()));

		cout << "请输入学生 web 成绩：";
		rewind(stdin);
		cin >> CmdStr;
		NewNode.SetScore(ESubject::web, atof(CmdStr.data()));

		cout << "请输入学生思修成绩：";
		rewind(stdin);
		cin >> CmdStr;
		NewNode.SetScore(ESubject::Thoughts, atof(CmdStr.data()));

		cout << "请输入学生案例分析成绩：";
		rewind(stdin);
		cin >> CmdStr;
		NewNode.SetScore(ESubject::instance, atof(CmdStr.data()));

		cout << "请输入学生数据结构成绩：";
		rewind(stdin);
		cin >> CmdStr;
		NewNode.SetScore(ESubject::Data, atof(CmdStr.data()));

		NodeArray.AddStudentData(NewNode);
		system("cls");
		rewind(stdin);
		cout << "录入成功，请任意键返回。" << endl;
		system("pause>nul");
		return  EInterfaceType::Main;//返回主界面
	case EInterfaceType::Del://删除学生信息
		cout << "\t学生信息删除界面" << endl;
		cout << "————————————————" << endl;
		cout << endl;
		cout << "请输入学号：" << endl;
		rewind(stdin);
		cin >> CmdStr;
		rewind(stdin);
		cout << endl;
		CmdBf = atoi(CmdStr.data());
		if (NodeArray.IsValid(CmdBf))
		{
			cout << "该学生信息如下：" << endl;
			FNode NewData = NodeArray.FindStudentData(CmdBf);
			ShowData(NewData);
			int errorcontrol = MessageBox(NULL, TEXT("确认删除该学生吗？\n"), TEXT("学生成绩管理系统"), MB_OKCANCEL | MB_ICONQUESTION);
			if (errorcontrol == 1)
			{
				NodeArray.DeleteStudentData(CmdBf);
				cout << "\n删除成功，请按请按任意键返回。" << endl;
				system("pause>nul");
			}
			return EInterfaceType::Main;//返回主界面
		}
		else
		{
			cout << "错误：\a学生不存在，请按任意键返回。" << endl;
			system("pause>nul");
			return EInterfaceType::Main;//返回主界面
		}
	case EInterfaceType::Change://修改学生信息
		cout << "\t学生信息修改界面" << endl;
		cout << "————————————————" << endl;
		cout << endl;
		cout << "请输入学号：";
		rewind(stdin);
		cin >> CmdStr;
		rewind(stdin);
		CmdBf = atoi(CmdStr.data());
		if (NodeArray.IsValid(CmdBf))
		{
			cout << "说明：如果数值为 0，说明该科未正确录入。" << endl;
			cout << "该学生所有信息如下：" << endl;
			FNode NewData = NodeArray.FindStudentData(CmdBf);
			ShowData(NewData);
			cout << "请输入新的学号：" << endl;
			rewind(stdin);
			cin >> CmdStr;
			NewData.ID = atoi(CmdStr.data());

			cout << "请输入新的姓名：" << endl;
			rewind(stdin);
			cin >> CmdStr;
			NewData.Name = CmdStr;

			cout << "请输入新的数学分析成绩：";
			rewind(stdin);
			cin >> CmdStr;
			NewData.SetScore(ESubject::MathA, atof(CmdStr.data()));

			cout << "请输入新的数学基础成绩：";
			rewind(stdin);
			cin >> CmdStr;
			NewData.SetScore(ESubject::MathB, atof(CmdStr.data()));

			cout << "请输入新的英语成绩：";
			rewind(stdin);
			cin >> CmdStr;
			NewData.SetScore(ESubject::English, atof(CmdStr.data()));

			cout << "请输入新的体育成绩：";
			rewind(stdin);
			cin >> CmdStr;
			NewData.SetScore(ESubject::PE, atof(CmdStr.data()));

			cout << "请输入新的网络空间安全导论成绩：";
			rewind(stdin);
			cin >> CmdStr;
			NewData.SetScore(ESubject::theory, atof(CmdStr.data()));

			cout << "请输入新的 web 成绩：";
			rewind(stdin);
			cin >> CmdStr;
			NewData.SetScore(ESubject::web, atof(CmdStr.data()));

			cout << "请输入新的思修成绩：";
			rewind(stdin);
			cin >> CmdStr;
			NewData.SetScore(ESubject::Thoughts, atof(CmdStr.data()));

			cout << "请输入新的案例分析成绩：";
			rewind(stdin);
			cin >> CmdStr;
			NewData.SetScore(ESubject::instance, atof(CmdStr.data()));

			cout << "请输入新的数据结构成绩：";
			rewind(stdin);
			cin >> CmdStr;
			NewData.SetScore(ESubject::Data, atof(CmdStr.data()));

			NodeArray.ChangeStudentData(CmdBf, NewData);
			rewind(stdin);
			cout << "录入成功，请任意键返回。" << endl;
			system("pause>nul");
			return EInterfaceType::Main;//返回主界面
		}
		else
		{
			cout << "\n学生不存在，请按任意键返回。" << endl;
			system("pause>nul");
			return EInterfaceType::Main;//返回主界面
		}
	case EInterfaceType::Find://查询学生信息
		cout << "\t学生信息查询界面" << endl;
		cout << "————————————————" << endl;
		cout << endl;
		cout << "请输入学号：" << endl;
		rewind(stdin);
		cin >> CmdStr;
		rewind(stdin);
		cout << endl;
		CmdBf = atoi(CmdStr.data());
		if (NodeArray.IsValid(CmdBf))
		{
			cout << "该学生信息如下：" << endl;
			FNode NewData = NodeArray.FindStudentData(CmdBf);
			ShowData(NewData);
			cout << "查询完毕，如果数值为 -1，说明该科未正确录入，请按任意键返回。" << endl;
			system("pause>nul");
			return EInterfaceType::Main;//返回主界面
		}
		else
		{
			cout << "学生不存在，请按任意键返回。" << endl;
			system("pause>nul");
			return EInterfaceType::Main;//返回主界面
		}
	case EInterfaceType::ChangeScore://修改学生成绩
		cout << "\t学生成绩修改界面" << endl;
		cout << "————————————————" << endl;
		cout << endl;
		cout << "请输入学号：" << endl;
		rewind(stdin);
		cin >> CmdStr;
		rewind(stdin);
		cout << endl;
		CmdBf = atoi(CmdStr.data());
		if (NodeArray.IsValid(CmdBf))
		{
			cout << "学生信息如下：" << endl;
			FNode NewData = NodeArray.FindStudentData(CmdBf);
			ShowData(NewData);
			cout << "可供修改的科目：" << endl;
			cout << ">> 0 = 数学分析" << endl;
			cout << ">> 1 = 数学基础" << endl;
			cout << ">> 2 = 英语" << endl;
			cout << ">> 3 = 体育" << endl;
			cout << ">> 4 = 网络空间安全导论" << endl;
			cout << ">> 5 = web" << endl;
			cout << ">> 6 = 思修" << endl;
			cout << ">> 7 = 案例分析" << endl;
			cout << ">> 8 = 数据结构" << endl;
			cout << endl << "请选择一个科目以继续：";
			int ID = CmdBf;
			rewind(stdin);
			cin >> CmdStr;
			CmdBf = atoi(CmdStr.data());
			cout << "\n请为该科目指定新的分数：" << endl;
			rewind(stdin); 
			cin >> CmdStr;
			rewind(stdin);
			NodeArray.ChangeScore(ID, (ESubject)CmdBf, atof(CmdStr.data()));
			cout << "修改成功，请按请按任意键返回。" << endl;
			system("pause>nul");
			return EInterfaceType::Main;//返回主界面
		}
		else
		{
			cout << "学生不存在，请按任意键返回。" << endl;
			system("pause>nul");
			return EInterfaceType::Main;//返回主界面
		}
	case EInterfaceType::FindStudents://列举所有学生
		cout << "\t列举所有学生" << endl;
		cout << "————————————————" << endl;
		cout << endl;
		for (int i = 0; i < NodeArray.GetSize(); i++)
		{
			FNode FindNode = NodeArray.GetArrayNode(i);
			cout << i + 1 << "\t学号：" << FindNode.ID << "\t\t" << "姓名：" << FindNode.Name << endl;
		}
		cout << endl << "显示完毕，如果数值为 -1，说明该科未正确录入，请按任意键返回。" << endl;
		system("pause>nul");
		return EInterfaceType::Main;
	case EInterfaceType::ShowAll://显示所有信息
		cout << "\t显示所有学生信息" << endl;
		cout << "————————————————" << endl;
		cout << endl << endl;
		for (int i = 0; i < NodeArray.GetSize(); i++)
		{
			FNode FindNode = NodeArray.GetArrayNode(i);
			ShowData(FindNode);
			cout << endl;
		}
		cout << "显示完毕，如果数值为 0，说明该科未正确录入，请按任意键返回。" << endl;
		system("pause>nul");
		return EInterfaceType::Main;
	case EInterfaceType::ForTeahcer://科目平均成绩
		cout << "\t显示科目平均成绩" << endl;
		cout << "————————————————" << endl;
		cout << endl;
		cout << "可选科目如下：" << endl;
		cout << ">> 0 = 数学分析" << endl;
		cout << ">> 1 = 数学基础" << endl;
		cout << ">> 2 = 英语" << endl;
		cout << ">> 3 = 体育" << endl;
		cout << ">> 4 = 网络空间安全导论" << endl;
		cout << ">> 5 = web" << endl;
		cout << ">> 6 = 思修" << endl;
		cout << ">> 7 = 案例分析" << endl;
		cout << ">> 8 = 数据结构" << endl;
		cout << ">> 9 = 返回主界面" << endl;
		cout << endl << "请选择一个科目以继续：";
		rewind(stdin);
		cin >> CmdStr;
		rewind(stdin);
		CmdBf = atoi(CmdStr.data());
		if (CmdBf == 9)
			return EInterfaceType::Main;
		else if (CmdBf > 9 || CmdBf < 0)
			return EInterfaceType::ForTeahcer;
		else
		{
			double score = NodeArray.CalcScore((ESubject)CmdBf);
			cout << endl << "该科目的平均成绩为：" << score << "，请按任意键返回。" << endl;
			system("pause>nul");
			return EInterfaceType::Main;//返回主界面
		}
	case EInterfaceType::SearchKey://关键字词查找
		cout << "\t关键字词查找界面" << endl;
		cout << "————————————————" << endl;
		cout << endl;
		cout << "请输入关键字：" << endl;
		rewind(stdin);
		cin >> CmdStr;
		rewind(stdin);
		cout << endl;
		for (int i = 0; i < NodeArray.GetSize(); i++)
		{
			FNode FindNode = NodeArray.GetArrayNode(i);
			string::size_type postion = FindNode.Name.find(CmdStr);
			if (postion != -1)
			{
				FNode DisplayNode = NodeArray.GetArrayNode(i);
				ShowData(DisplayNode);
			}
			cout << endl;
		}
		cout << "\n查找完毕，请按任意键返回。" << endl;
		system("pause>nul");
		return EInterfaceType::Main;
	case EInterfaceType::Break://退出管理系统
		return EInterfaceType::Break;
	default:
		return EInterfaceType::Main;
	}
}

BOOL Shutdown()
{
	HANDLE HToken;
	TOKEN_PRIVILEGES tkp;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &HToken))
		return FALSE;
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(HToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	if (GetLastError() != ERROR_SUCCESS)
		return FALSE;
	const int SE_SHUTDOWN_PRIVILEGE = 0x13;
	typedef int(__stdcall* PFN_RtlAdjustPrivilege)(INT, BOOL, BOOL, INT*);
	typedef int(__stdcall* PFN_ZwShutdownSystem)(INT);
	HMODULE hModule = ::LoadLibrary(_T("ntdll.dll"));
	if (hModule != NULL)
	{
		PFN_RtlAdjustPrivilege pfnRtl = (PFN_RtlAdjustPrivilege)GetProcAddress(hModule, "RtlAdjustPrivilege");
		PFN_ZwShutdownSystem pfnShutdown = (PFN_ZwShutdownSystem)GetProcAddress(hModule, "ZwShutdownSystem");
		if (pfnRtl != NULL && pfnShutdown != NULL)
		{
			int en = 0;
			int nRet = pfnRtl(SE_SHUTDOWN_PRIVILEGE, TRUE, TRUE, &en);
			if (nRet == 0x0C000007C)
				nRet = pfnRtl(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &en);
			const int POWEROFF = 2;
			nRet = pfnShutdown(POWEROFF);
		}
	}
	return TRUE;
}

int main()//主程序
{
	system("chcp 936&title 学生成绩管理系统&color e&cls");
	EInterfaceType Cmd = EInterfaceType::Main;
	while (Cmd != EInterfaceType::Break)
	{
		system("cls");
		Cmd = Interface(Cmd);
	}
	system("cls");
	if (MessageBox(NULL, TEXT("欢迎再次使用学生信息管理系统。\n系统即将关闭，是否在关闭后自动关闭计算机？"), TEXT("学生成绩管理系统"), MB_YESNO | MB_ICONQUESTION | MB_TOPMOST | MB_DEFBUTTON2) == IDYES)
		Shutdown();
	return 0;
}