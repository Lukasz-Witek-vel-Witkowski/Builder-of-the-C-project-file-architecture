#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> f_load(std::string file);
void f_write_class(std::vector<std::string> Tab);
bool f_write_file_h(std::string name);
bool f_write_file_cpp(std::string name);
std::string f_transformate(std::string name);
std::string m_transform_h(std::string name);
std::string m_transform_cpp(std::string name);
int main()
{
	std::vector<std::string> Tabela;
	std::string file = "plik.bin";
		Tabela=f_load(file);
		f_write_class(Tabela);
	return 0;
}
std::vector<std::string> f_load(std::string file) {
	std::vector<std::string> Tab;
	std::ifstream File;
	File.open(file.c_str());
	if (File.good())
	{
		std::string data;
		do 
		{
			File >> data;
			if ((data == "END#FILE")) break;
			Tab.push_back(data);
		} while (1);
		File.close();
	}
	return Tab;
}
void f_write_class(std::vector<std::string> Tab) {
	int i;
	for (i = 0; i < Tab.size(); i++)
	{
		if (f_write_file_h(Tab[i]))
			std::cout << "Poprawne zapisanie pliku: " << Tab[i] << ".hpp\n";
		if (f_write_file_cpp(Tab[i]))
			std::cout << "Poprawne zapisanie pliku:" << Tab[i] << ".cpp\n";
	}
}
bool f_write_file_h(std::string name) {
	int i;
	std::ofstream File;
	File.open(m_transform_h(name).c_str());
	if (File.good())
	{
		File << "#ifndef " + f_transformate(m_transform_h(name)) + "\n";
		File << "#define " + f_transformate(m_transform_h(name)) + "\n";
		File << "class " + name + "\n";
		File << "{\n";
		File << "public:\n";
		File << name + "(); //konstruktor bezparametrowy\n" ;
		File << name + "(const " + name + "& data); //konstruktor kopiujacy\n";
		File << name + "& operator=(const " + name + "& data); //operator przypisania =\n";
		File << "bool operator==(const " + name + "& data); //operator porownania ==\n";
		File << "bool operator!=(const " + name + "& data); //operator porownania !=\n";
		File << "~" + name + "(); //destruktor\n";
		File << "};\n";
		File << "#endif // !" + name;
		File.close();
		return true;
	}
	return false;
}
std::string f_transformate(std::string name) {
	int i;
	for (i = 0; i < name.size(); i++)
	{
		if (name[i] >= 'a'&&name[i] <= 'z')
		{
			name[i] = (char)name[i] - 32;
			continue;
		}
		else if (name[i] == '_' || (name[1] >= '0'&&name[1] <= '9'))
		{
			continue;
		}
		else if (name[i] == '.')
		{
			name[i] = '_';
			continue;
		}
	}
	return name;
}
bool f_write_file_cpp(std::string name) {
	int i;
	std::ofstream File;
	File.open(m_transform_cpp(name).c_str());
	if (File.good())
	{
		File << "#include \""+name+".hpp\"\n";
		File << name + "::" + name + "(){}\n";
		File << name + "::" + name + "(const " + name + "& data){\nif(this!=&data) *this=data;\n}\n";
		File << name + "& " + name + "::operator=(const " + name + "& data){\nif(this==&data) return *this;\n" +
			"if(*this == data) return *this;\n//proces kopiowania\nreturn *this;\n}\n";
		File << "bool " + name + "::operator==(const " + name + "& data){\n//if(==) return true;\nreturn false;\n}\n";
		File << "bool " + name + "::operator!=(const " + name + "& data){\n//if(!=) return true;\nreturn false;\n}\n";
		File << name + "::~" + name + "(){}\n";
		File.close();
		return true;
	}
	return false;
}
std::string m_transform_h(std::string name){
return name+=".hpp";
}
std::string m_transform_cpp(std::string name){
return name+=".cpp";
}